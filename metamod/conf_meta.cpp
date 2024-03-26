// vi: set ts=4 sw=4 :
// vim: set tw=75 :

// conf_meta.cpp - configfile reading routines

/*
 * Copyright (c) 2001-2006 Will Day <willday@hpgx.net>
 *
 *    This file is part of Metamod.
 *
 *    Metamod is free software; you can redistribute it and/or modify it
 *    under the terms of the GNU General Public License as published by the
 *    Free Software Foundation; either version 2 of the License, or (at
 *    your option) any later version.
 *
 *    Metamod is distributed in the hope that it will be useful, but
 *    WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with Metamod; if not, write to the Free Software Foundation,
 *    Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *    In addition, as a special exception, the author gives permission to
 *    link the code of this program with the Half-Life Game Engine ("HL
 *    Engine") and Modified Game Libraries ("MODs") developed by Valve,
 *    L.L.C ("Valve").  You must obey the GNU General Public License in all
 *    respects for all of the code used other than the HL Engine and MODs
 *    from Valve.  If you modify this file, you may extend this exception
 *    to your version of the file, but you are not obligated to do so.  If
 *    you do not wish to do so, delete this exception statement from your
 *    version.
 *
 */

#include <cstdio>			// FILE,
#include <cstdlib>			// atoi
#include <cctype>			// isdigit

#include <extdll.h>			// always

#include "conf_meta.h"		// me
#include "support_meta.h"	// strmatch
#include "osdep.h"			// strtok,

MConfig::MConfig()
	: list(nullptr), filename(nullptr), debuglevel(0), gamedll(nullptr),
	plugins_file(nullptr), exec_cfg(nullptr), autodetect(0), clientmeta(0),
	slowhooks(0), slowhooks_whitelist(nullptr)
{
}

// Initialize default values from the stored options struct.  Has to happen
// _after_ constructor, so that all the fields are allocated (d'oh).
void DLLINTERNAL MConfig::init(option_t* global_options) {
	list = global_options;
	for (option_t* optp = list; optp->name; optp++)
		set(optp, optp->init);
}

option_t* DLLINTERNAL MConfig::find(const char* lookup) const
{
	option_t* optp;

	for (optp = list; optp->name && !strmatch(optp->name, lookup); optp++);
	if (optp->name)
		return(optp);
	RETURN_ERRNO(NULL, ME_NOTFOUND);
}

mBOOL DLLINTERNAL MConfig::set(const char* key, const char* value) const
{
	option_t* optp = find(key);
	if (optp)
		return(set(optp, value));
	RETURN_ERRNO(mFALSE, ME_NOTFOUND);
}

mBOOL DLLINTERNAL MConfig::set(option_t* setp, const char* setstr) {
	char pathbuf[PATH_MAX];
	int* optval = (int*)setp->dest;
	char** optstr = (char**)setp->dest;
	// cvar_t *optcvar = (cvar_t *) setp->dest;
	// SETOPT_FN optcmd = (SETOPT_FN) setp->dest;

	if (!setstr)
		return(mTRUE);

	switch (setp->type) {
	case CF_INT:
		if (!isdigit(setstr[0])) {
			META_WARNING("option '%s' invalid format '%s'", setp->name, setstr);
			RETURN_ERRNO(mFALSE, ME_FORMAT);
		}
		*optval = atoi(setstr);
		META_DEBUG(3, ("set config int: %s = %d", setp->name, *optval));
		break;
	case CF_BOOL:
		if (strcasematch(setstr, "true")
			|| strcasematch(setstr, "yes")
			|| strmatch(setstr, "1"))
		{
			*optval = 1;
		}
		else if (strcasematch(setstr, "false")
			|| strcasematch(setstr, "no")
			|| strmatch(setstr, "0"))
		{
			*optval = 0;
		}
		else {
			META_WARNING("option '%s' invalid format '%s'", setp->name, setstr);
			RETURN_ERRNO(mFALSE, ME_FORMAT);
		}
		META_DEBUG(3, ("set config bool: %s = %s", setp->name, *optval ? "true" : "false"));
		break;
	case CF_STR:
		//			if(*optstr)
		free(*optstr);
		*optstr = strdup(setstr);
		META_DEBUG(3, ("set config string: %s = %s", setp->name, *optstr));
		break;
	case CF_PATH:
		//			if(*optstr)
		free(*optstr);
		full_gamedir_path(setstr, pathbuf);
		*optstr = strdup(pathbuf);
		META_DEBUG(3, ("set config path: %s = %s", setp->name, *optstr));
		break;
#if 0
	case CF_CVAR:
		CVAR_SET_STRING(optcvar->name, setstr);
		META_DEBUG(3, ("set config cvar: %s = %s", optcvar->name, setstr));
		break;
	case CF_CMD:
		optcmd(setp->name, setstr);
		META_DEBUG(3, ("set config command: %s, %s", optcvar->name, setstr));
		break;
#endif
	default:
		META_WARNING("unrecognized config type '%d'", setp->type);
		RETURN_ERRNO(mFALSE, ME_ARGUMENT);
	//case CF_NONE:
	//	break;
	}
	return(mTRUE);
}

mBOOL DLLINTERNAL MConfig::load(const char* fn) {
	char loadfile[PATH_MAX];
	char line[MAX_CONF_LEN];
	char* optname, * optval;
	option_t* optp;

	// Make full pathname (from gamedir if relative, collapse "..",
	// backslashes, etc).
	full_gamedir_path(fn, loadfile);

	FILE* fp = fopen(loadfile, "r");
	if (!fp) {
		META_WARNING("unable to open config file '%s': %s", loadfile,
			strerror(errno));
		RETURN_ERRNO(mFALSE, ME_NOFILE);
	}

	META_DEBUG(2, ("Loading from config file: %s", loadfile));
	for (int ln = 1; !feof(fp) && fgets(line, sizeof(line), fp); ln++) {
		if (line[0] == '#')
			continue;
		if (line[0] == ';')
			continue;
		if (strnmatch(line, "//", 2))
			continue;
		if (!((optname = strtok(line, " \t\r\n")))) {
			META_WARNING("'%s' line %d: bad config format: missing option",
				loadfile, ln);
			continue;
		}
		if (!((optval = strtok(nullptr, "\r\n")))) {
			META_WARNING("'%s' line %d: bad config format: missing value",
				loadfile, ln);
			continue;
		}

		if (!((optp = find(optname)))) {
			META_WARNING("'%s' line %d: unknown option name '%s'",
				loadfile, ln, optname);
			continue;
		}

		if (!set(optp, optval)) {
			META_WARNING("'%s' line %d: unable to set option '%s' value '%s'",
				loadfile, ln, optname, optval);
			continue;
		}
	}
	filename = strdup(loadfile);
	fclose(fp);
	return(mTRUE);
}

void DLLINTERNAL MConfig::show() const
{
	if (filename)
		META_CONS("%s and %s:", "Config options from localinfo", filename);
	else
		META_CONS("%s:", "Config options from localinfo");
	for (option_t* optp = list; optp->name; optp++) {
		const int* optval = (int*)optp->dest;
		char** optstr = (char**)optp->dest;
		// cvar_t *optcvar = (cvar_t *) optp->dest;
		// SETOPT_FN optcmd = (SETOPT_FN) optp->dest;
		switch (optp->type) {
		case CF_INT:
			META_CONS("   %-20s\t%d\n", optp->name, *optval);
			break;
		case CF_BOOL:
			META_CONS("   %-20s\t%s\n", optp->name,
				*optval ? "true" : "false");
			break;
		case CF_STR:
		case CF_PATH:
			META_CONS("   %-20s\t%s\n", optp->name,
				*optstr ? *optstr : "");
			break;
#if 0
		case CF_CVAR:
			META_CONS("   %-20s\tstores in: %s\n", optp->name, optcvar->name);
			break;
		case CF_CMD:
			META_CONS("   %-20s\tparsed by: %d\n", optp->name, (int)optcmd);
			break;
#endif
		case CF_NONE:
			break;
		}
	}
}
