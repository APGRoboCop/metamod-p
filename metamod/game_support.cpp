// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
// vi: set ts=4 sw=4 :
// vim: set tw=75 :

// game_support.cpp - info to recognize different HL mod "games"

/*
 * Copyright (c) 2001-2013 Will Day <willday@hpgx.net>
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
#include <cstring>

#include <fcntl.h>          // open, write

#include <extdll.h>			// always

#include "game_support.h"	// me
#include "log_meta.h"		// META_LOG, etc
#include "types_meta.h"		// mBOOL
#include "osdep.h"			// win32 snprintf, etc
#include "game_autodetect.h"	// autodetect_gamedll
#include "support_meta.h"	// MIN

 // Adapted from adminmod h_export.cpp:
 //! this structure contains a list of supported mods and their dlls names
 //! To add support for another mod add an entry here, and add all the
 //! exported entities to link_func.cpp
const game_modlist_t known_games = {
	// name/gamedir	 linux_so			win_dll			desc
	//
	// Previously enumerated in this sourcefile, the list is now kept in a
	// separate file, generated based on game information stored in a
	// convenient db.
	//
//#include "games.h"

//#if defined(__x86_64__) || defined(__amd64__)
//#  define MODARCH "_amd64"
//#else
//#  define MODARCH "_i386"
//#endif

	{ "action", "ahl_i386.so", "ahl.dll", "Action Half-Life" },
	{ "ag",                "ag_i386.so",           "ag.dll",            "Adrenaline Gamer Steam" },
	{ "ag3",               "hl_i386.so",           "hl.dll",            "Adrenalinegamer 3.x" },
	{ "aghl",              "ag_i386.so",           "ag.dll",            "Adrenalinegamer 4.x" },
	{ "arg",               "arg_i386.so",          "hl.dll",            "Arg!" },
	{ "asheep",            "hl_i386.so",           "hl.dll",            "Azure Sheep" },
	{ "hcfrenzy",          "hcfrenzy.so",              "hcfrenzy.dll",      "Headcrab Frenzy" },
	{ "bdef",              "../cl_dlls/server.so",     "../cl_dlls/server.dll", "Base Defense [Modification]" },
	{ "bdef",              "server.so",            "server.dll",        "Base Defense [Steam Version]" },
	{ "bg",                "bg_i386.so",           "bg.dll",            "The Battle Grounds" },
	{ "bhl",               "none",                     "bhl.dll",           "Brutal Half-Life" },
	{ "bot",               "bot_i386.so",          "bot.dll",           "Bot" },
	{ "brainbread",        "bb_i386.so",           "bb.dll",            "BrainBread" },
	{ "bshift",            "bshift.so",                "hl.dll",                    "Half-Life: Blue Shift" },
	{ "bumpercars",        "hl_i386.so",           "hl.dll",            "Bumper Cars" },
	{ "buzzybots",         "bb_i386.so",           "bb.dll",            "BuzzyBots" },
	{ "ckf3",              "none",                     "mp.dll",            "Chicken Fortress 3" },
	{ "cs10",              "none",                    "mp.dll",                    "Counter-Strike 1.0" },
	{ "cs13",              "cs_i386.so",           "mp.dll",            "Counter-Strike 1.3" },
	{ "cstrike",           "cs.so",           "mp.dll",            "Counter-Strike" },
	{ "csv15",             "cs_i386.so",           "mp.dll",            "CS 1.5 for Steam" },
	{ "czero",             "cs.so",           "mp.dll",            "Counter-Strike:Condition Zero" },
	{ "dcrisis",           "dc_i386.so",           "dc.dll",            "Desert Crisis" },
	{ "decay",             "none",                   "decay.dll",                 "Half-Life: Decay" },
	{ "dmc",               "dmc.so",          "dmc.dll",           "Deathmatch Classic" },
	{ "dod",               "dod.so",          "dod.dll",           "Day of Defeat" },
	{ "dpb",               "pb.i386.so",               "pb.dll",            "Digital Paintball" },
	{ "dragonmodz",        "hl_i386.so",           "mp.dll",            "Dragon Mod Z" },
	{ "esf",               "hl_i386.so",           "hl.dll",            "Earth's Special Forces" },
	{ "existence",         "ex_i386.so",           "existence.dll",     "Existence" },
	{ "firearms",          "fa_i386.so",           "firearms.dll",      "Firearms" },
	{ "firearms25",        "fa_i386.so",           "firearms.dll",      "Retro Firearms" },
	{ "freeze",            "mp_i386.so",           "mp.dll",            "Freeze" },
	{ "frontline",         "front_i386.so",        "frontline.dll",     "Frontline Force" },
	{ "gangstawars",       "gangsta_i386.so",      "gwars27.dll",       "Gangsta Wars" },
	{ "gangwars",          "mp_i386.so",           "mp.dll",            "Gangwars" },
	{ "gearbox",           "opfor.so",        	"opfor.dll",         "Opposing Force" },
	{ "globalwarfare",     "gw_i386.so",           "mp.dll",            "Global Warfare" },
	{ "goldeneye",         "golden_i386.so",       "mp.dll",            "Goldeneye" },
	{ "hl15we",            "hl_i386.so",           "hl.dll",            "Half-Life 1.5: Weapon Edition" },
	{ "HLAinGOLDSrc",      "none",                 "hl.dll",            "Half-Life Alpha in GOLDSrc" },
	{ "hlrally",           "hlr_i386.so",          "hlrally.dll",       "HL-Rally" },
	{ "holywars",          "hl_i386.so",           "holywars.dll",      "Holy Wars" },
	{ "hostileintent",     "hl_i386.so",           "hl.dll",            "Hostile Intent" },
	{ "ios",               "ios_i386.so",          "ios.dll",           "International Online Soccer" },
	{ "judgedm",           "judge_i386.so",        "mp.dll",            "Judgement" },
	{ "kanonball",         "hl_i386.so",           "kanonball.dll",     "Kanonball" },
	{ "monkeystrike",      "ms_i386.so",           "monkey.dll",        "Monkeystrike" },
	{ "MorbidPR",          "morbid_i386.so",       "morbid.dll",        "Morbid Inclination" },
	{ "movein",            "hl_i386.so",           "hl.dll",            "Move In!" },
	{ "msc",               "none",                 "ms.dll",            "Master Sword Continued" },
	{ "ns",                "ns.so",					"ns.dll",            "Natural Selection" },
	{ "nsp",               "ns_i386.so",           "ns.dll",            "Natural Selection Beta" },
	{ "oel",               "hl_i386.so",           "hl.dll",            "OeL Half-Life" },
	{ "og",                "og_i386.so",           "og.dll",            "Over Ground" },
	{ "ol",                "ol_i386.so",           "hl.dll",            "Outlawsmod" },
	{ "ops1942",           "spirit_i386.so",       "spirit.dll",        "Operations 1942" },
	{ "osjb",              "osjb_i386.so",         "jail.dll",          "Open-Source Jailbreak" },
	{ "outbreak",          "none",					"hl.dll",            "Out Break" },
	{ "oz",                "mp_i386.so",           "mp.dll",            "Oz Deathmatch" },
	{ "paintball",         "pb_i386.so",           "mp.dll",            "Paintball" },
	{ "penemy",            "pe_i386.so",           "pe.dll",            "Public Enemy" },
	{ "phineas",           "phineas_i386.so",      "phineas.dll",       "Phineas Bot" },
	{ "ponreturn",         "ponr_i386.so",         "mp.dll",            "Point of No Return" },
	{ "pvk",               "hl_i386.so",           "hl.dll",            "Pirates, Vikings and Knights" },
	{ "rc2",               "rc2_i386.so",          "rc2.dll",           "Rocket Crowbar 2" },
	{ "recbb2",            "recb_i386.so",         "recb.dll",          "Resident Evil : Cold Blood" },
	{ "retrocs",           "rcs_i386.so",          "rcs.dll",           "Retro Counter-Strike" },
	{ "rewolf",            "hl_i386.so",           "gunman.dll",        "Gunman Chronicles" },
	{ "ricochet",          "ricochet.so",     "mp.dll",            "Ricochet" },
	{ "rockcrowbar",       "rc_i386.so",           "rc.dll",            "Rocket Crowbar" },
	{ "rspecies",          "hl_i386.so",           "hl.dll",            "Rival Species" },
	{ "scihunt",           "shunt.so",                 "shunt.dll",         "Scientist Hunt" },
	{ "sdm",               "sdmmod_i386.so",       "sdmmod.dll",        "Special Death Match" },
	{ "Ship",              "ship_i386.so",         "ship.dll",          "The Ship" },
	{ "si",                "si.so",           "si.dll",            "Science & Industry" },
	{ "snow",              "snow_i386.so",         "snow.dll",          "Snow-War" },
	{ "stargatetc",        "hl.so",                    "hl.dll",                    "StargateTC (Leaacy v1.x)" },
	{ "stargatetc",        "stc_i386.so",              "hl.dll",                    "StargateTC (v2.x)" },
	{ "stargatetc",        "stc_i386_opt.so",          "hl.dll",                    "StargateTC (v2.x, optimised binary)" },
	{ "svencoop",          "hl_i386.so",           "hl.dll",            "Sven Coop [Modification]" },
	//	{ "svencoop",          "server.so",                "server.dll",        "Sven Coop [Steam Version]" },
	{ "swarm",             "swarm_i386.so",        "swarm.dll",         "Swarm" },
	{ "tfc",               "tfc.so",          "tfc.dll",           "Team Fortress Classic" },
	{ "thewastes",         "thewastes_i386.so",    "thewastes.dll",     "The Wastes" },
	{ "timeless",          "pt_i386.so",           "timeless.dll",      "Project Timeless" },
	{ "tod",               "hl_i386.so",           "hl.dll",            "Tour of Duty" },
	{ "trainhunters",      "th_i386.so",           "th.dll",            "Train Hunters" },
	{ "trevenge",          "trevenge.so",              "trevenge.dll",      "The Terrorist Revenge" },
	{ "ts",                "ts_i686.so",           "mp.dll",            "The Specialists" },
	{ "tt",                "tt_i386.so",           "tt.dll",            "The Trenches" },
	{ "underworld",        "uw_i386.so",           "uw.dll",            "Underworld Bloodline" },
	{ "valve",             "hl.so",				"hl.dll",            "Half-Life Deathmatch" },
	{ "vs",                "vs_i386.so",           "mp.dll",            "VampireSlayer" },
	{ "wantedhl",          "hl_i386.so",           "wanted.dll",        "Wanted!" },
	{ "wasteland",         "whl_linux.so",             "mp.dll",            "Wasteland" },
	{ "weapon_wars",       "ww_i386.so",           "hl.dll",            "Weapon Wars" },
	{ "wizardwars",        "wizardwars_i486.so",       "wizardwars.dll",            "Wizard Wars (Steam)" },
	{ "wizardwars_beta",   "wizardwars_i486.so",       "wizardwars.dll",            "Wizard Wars Beta (Steam)" },
	{ "wizwars",           "mp.so",                    "hl.dll",                    "Wizard Wars (Legacy)" },
	{ "wormshl",           "wormshl_i586.so",          "wormshl.dll",               "WormsHL (Legacy)" },
	{ "wormshl",           "wormshl_i686.so",          "wormshl.dll",               "WormsHL (Steam)" },
	{ "zp",                "none",                     "mp.dll",            "Zombie Panic" },

	// End of list terminator:
	{nullptr, nullptr, nullptr, nullptr}
};

// Find a modinfo corresponding to the given game name.
const game_modinfo_t* DLLINTERNAL lookup_game(const char* name) {
	for (int i = 0; known_games[i].name; i++) {
		const game_modinfo_t* imod = &known_games[i];
		// If there are 2 or more same names check next dll file if doesn't exist
		if (strcasematch(imod->name, name)) {
			char check_path[NAME_MAX];
			safevoid_snprintf(check_path, sizeof(check_path), "dlls/%s",
#ifdef _WIN32
			                  imod->win_dll);
#elif defined(__linux__)
				imod->linux_so);
#endif

			if (!valid_gamedir_file(check_path)) {
				continue;
			}

			return imod;
		}
	}
	// no match found
	return nullptr;
}

// Installs gamedll from Steam cache
mBOOL DLLINTERNAL install_gamedll(char* from, const char* to) {
	int length_in;

	if (!from)
		return mFALSE;
	if (!to)
		to = from;

	// If the file seems to exist in the cache.
	if (byte* cachefile = LOAD_FILE_FOR_ME(from, &length_in)) {
		const int fd = open(to, O_WRONLY | O_CREAT | O_EXCL | O_BINARY, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

		if (fd < 0) {
			META_DEBUG(3, ("Installing gamedll from cache: Failed to create file %s: %s", to, strerror(errno)));
			FREE_FILE(cachefile);
			return mFALSE;
		}

		const int length_out = write(fd, cachefile, length_in);
		FREE_FILE(cachefile);
		close(fd);

		// Writing the file was not successfull
		if (length_out != length_in) {
			META_DEBUG(3, ("Installing gamedll from chache: Failed to write all %d bytes to file, only %d written: %s", length_in, length_out, strerror(errno)));
			// Let's not leave a mess but clean up nicely.
			if (length_out >= 0)
				unlink(to);

			return mFALSE;
		}

		META_LOG("Installed gamedll %s from cache.", to);
	}
	else {
		META_DEBUG(3, ("Failed to install gamedll from cache: file %s not found in cache.", from));
		return mFALSE;
	}

	return mTRUE;
}

// Set all the fields in the gamedll struct, - based either on an entry in
// known_games matching the current gamedir, or on one specified manually
// by the server admin.
//
// meta_errno values:
//  - ME_NOTFOUND	couldn't recognize game
mBOOL DLLINTERNAL setup_gamedll(gamedll_t* gamedll) {
#ifdef __x86_64__
	static char fixname_amd64[NAME_MAX]; // pointer is given outside function
#endif
	static char override_desc_buf[NAME_MAX]; // pointer is given outside function
	static char autodetect_desc_buf[NAME_MAX]; // pointer is given outside function
	const game_modinfo_t* known;

#ifdef __linux__
	char* strippedfn;
#endif
	const char* cp, * autofn = nullptr, * knownfn = nullptr, * usedfn = nullptr;
	int override = 0;

	// Check for old-style "metagame.ini" file and complain.
	if (valid_gamedir_file(OLD_GAMEDLL_TXT))
		META_WARNING("File '%s' is no longer supported; instead, specify override gamedll in %s or with '+localinfo mm_gamedll <dllfile>'", OLD_GAMEDLL_TXT, CONFIG_INI);
	// First, look for a known game, based on gamedir.
	if ((known = lookup_game(gamedll->name))) {
#ifdef _WIN32
		knownfn = known->win_dll;
#elif defined(__linux__)
		knownfn = known->linux_so;
#ifdef __x86_64__
		//AMD64: convert _i386.so to _amd64.so
		if (((cp = strstr(knownfn, "_i386.so"))) ||
			((cp = strstr(knownfn, "_i486.so"))) ||
			((cp = strstr(knownfn, "_i586.so"))) ||
			((cp = strstr(knownfn, "_i686.so")))) {
			//make sure that it's the ending that has "_iX86.so"
			if (cp[strlen("_i386.so")] == 0) {
				STRNCPY(fixname_amd64, known->linux_so,
					MIN(((size_t)cp - (size_t)knownfn) + 1,
						sizeof(fixname_amd64)));
				strncat(fixname_amd64, "_amd64.so", sizeof(fixname_amd64) - strlen(fixname_amd64) - 1);

				knownfn = fixname_amd64;
			}
		}
#endif /*__x86_64__*/
#else
#error "OS unrecognized"
#endif /* _WIN32 */

		// Do this before autodetecting gamedll from "dlls/*.dll"
		if (!Config->gamedll) {
#ifdef __linux__
			// The engine changed game dll lookup behaviour in that it strips
			// anything after the last '_' from the name and tries to load the
			// resulting name. The DSO names were changed and do not have the
			// '_i386' part in them anymore, so cs_i386.so became cs.so. We
			// have to adapt to that and try to load the DSO name without the
			// '_*' part first, to see if we have a new version file available.
			char temp_str[NAME_MAX];

			STRNCPY(temp_str, knownfn, sizeof(temp_str));
			strippedfn = temp_str;

			const char* loc = strrchr(strippedfn, '_');

			// A small safety net here: make sure that we are dealing with
			// a file name at least four characters long and ending in
			// '.so'. This way we can be sure that we can safely overwrite
			// anything from the '_' on with '.so'.
			unsigned size = 0;
			const char* ext = nullptr;
			if (nullptr != loc) {
				size = strlen(strippedfn);
				ext = strippedfn + (size - 3);
			}

			if (nullptr != loc && size > 3 && 0 == strcasecmp(ext, ".so")) {
				strcpy(const_cast<char*>(loc), ".so");
				META_DEBUG(4, ("Checking for new version game DLL name '%s'.\n", strippedfn));

				// Again, as above, I abuse the real_pathname member to store the full pathname
				// and the pathname member to store the relative name to pass it to the
				// install_gamedll function to save stack space. They are going
				// to get overwritten later on, so that's ok.
				safevoid_snprintf(gamedll->pathname, sizeof(gamedll->pathname), "dlls/%s",
					strippedfn);
				// Check if the gamedll file exists. If not, try to install it from
				// the cache.
				mBOOL ok = mTRUE;
				if (!valid_gamedir_file(gamedll->pathname)) {
					safevoid_snprintf(gamedll->real_pathname, sizeof(gamedll->real_pathname), "%s/dlls/%s",
						gamedll->gamedir, strippedfn);
					ok = install_gamedll(gamedll->pathname, gamedll->real_pathname);
				}
				if (ok)
					usedfn = strippedfn;
			}
			else {
				META_DEBUG(4, ("Known game DLL name does not qualify for checking for a stripped version, skipping: '%s'.\n",
					strippedfn));
			}
#endif /* __linux__ */
			// If no file to be used was found, try the old known DLL file
			// name.
			if (nullptr == usedfn) {
				META_DEBUG(4, ("Checking for old version game DLL name '%s'.\n", knownfn));
				safevoid_snprintf(gamedll->pathname, sizeof(gamedll->pathname), "dlls/%s", knownfn);
				// Check if the gamedll file exists. If not, try to install it from
				// the cache.
				if (!valid_gamedir_file(gamedll->pathname)) {
					safevoid_snprintf(gamedll->real_pathname, sizeof(gamedll->real_pathname), "%s/dlls/%s",
						gamedll->gamedir, knownfn);
					install_gamedll(gamedll->pathname, gamedll->real_pathname);
				}
			}
			else {
				knownfn = usedfn;
			}
		}
	}

	// Then, autodetect gamedlls in "gamedir/dlls/"
	// autodetect_gamedll returns 0 if knownfn exists and is valid gamedll.
	if (Config->autodetect && ((autofn = autodetect_gamedll(gamedll, knownfn)))) {
		// If knownfn is set and autodetect_gamedll returns non-null
		// then knownfn doesn't exists and we should use autodetected
		// dll instead.
		if (knownfn) {
			// Whine loud about fact that known-list dll doesn't exists!
			//META_LOG(plapla);
			knownfn = autofn;
		}
	}

	// Neither override nor known-list nor auto-detect found a gamedll.
	if (!known && !Config->gamedll && !autofn)
		RETURN_ERRNO(mFALSE, ME_NOTFOUND);

	// Use override-dll if specified.
	if (Config->gamedll) {
		STRNCPY(gamedll->pathname, Config->gamedll,
			sizeof(gamedll->pathname));
		override = 1;

		// If the path is relative, the gamedll file will be missing and
		// it might be found in the cache file.
		if (!is_absolute_path(gamedll->pathname)) {
			char install_path[NAME_MAX];
			safevoid_snprintf(install_path, sizeof(install_path),
			                  "%s/%s", gamedll->gamedir, gamedll->pathname);
			// If we could successfully install the gamedll from the cache we
			// rectify the pathname to be a full pathname.
			if (install_gamedll(gamedll->pathname, install_path))
				STRNCPY(gamedll->pathname, install_path, sizeof(gamedll->pathname));
		}
	}
	// Else use Known-list dll.
	else if (known) {
		safevoid_snprintf(gamedll->pathname, sizeof(gamedll->pathname), "%s/dlls/%s",
			gamedll->gamedir, knownfn);
	}
	// Else use Autodetect dll.
	else {
		safevoid_snprintf(gamedll->pathname, sizeof(gamedll->pathname), "%s/dlls/%s",
			gamedll->gamedir, autofn);
	}

	// get filename from pathname
	cp = strrchr(gamedll->pathname, '/');
	if (cp)
		cp++;
	else
		cp = gamedll->pathname;
	gamedll->file = cp;

	// If found, store also the supposed "real" dll path based on the
	// gamedir, in case it differs from the "override" dll path.
	if (known && override)
		safevoid_snprintf(gamedll->real_pathname, sizeof(gamedll->real_pathname),
			"%s/dlls/%s", gamedll->gamedir, knownfn);
	else if (known && autofn)
		safevoid_snprintf(gamedll->real_pathname, sizeof(gamedll->real_pathname),
			"%s/dlls/%s", gamedll->gamedir, knownfn);
	else // !known or (!override and !autofn)
		STRNCPY(gamedll->real_pathname, gamedll->pathname,
			sizeof(gamedll->real_pathname));

	if (override) {
		// generate a desc
		safevoid_snprintf(override_desc_buf, sizeof(override_desc_buf), "%s (override)", gamedll->file);
		gamedll->desc = override_desc_buf;
		// log result
		META_LOG("Overriding game '%s' with dllfile '%s'", gamedll->name, gamedll->file);
	}
	else if (known && autofn) {
		// dll in known-list doesn't exists but we found new one with autodetect.

		// generate a desc
		safevoid_snprintf(autodetect_desc_buf, sizeof(autodetect_desc_buf), "%s (autodetect-override)", gamedll->file);
		gamedll->desc = autodetect_desc_buf;
		META_LOG("Recognized game '%s'; Autodetection override; using dllfile '%s'", gamedll->name, gamedll->file);
	}
	else if (autofn) {
		// generate a desc
		safevoid_snprintf(autodetect_desc_buf, sizeof(autodetect_desc_buf), "%s (autodetect)", gamedll->file);
		gamedll->desc = autodetect_desc_buf;
		META_LOG("Autodetected game '%s'; using dllfile '%s'", gamedll->name, gamedll->file);
	}
	else if (known) {
		gamedll->desc = known->desc;
		META_LOG("Recognized game '%s'; using dllfile '%s'", gamedll->name, gamedll->file);
	}
	return mTRUE;
}