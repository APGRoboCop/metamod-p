// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
/*
 * Copyright (c) 2004-2006 Jussi Kivilinna
 *
 *    This file is part of "Metamod All-Mod-Support"-patch for Metamod.
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

#ifdef __linux__
 // enable extra routines in system header files, like dladdr
#  ifndef _GNU_SOURCE
#    define _GNU_SOURCE
#  endif
#include <dlfcn.h>			// dlopen, dladdr, etc
#endif /* __linux__ */

#include <extdll.h>			// always

#include "osdep_p.h"			// me
#include "support_meta.h"		// STRNCPY

#ifdef _WIN32
// MSVC doesn't provide "dirent.h" header. These functions wrap opendir/readdir/closedir
// functions to FindFirst/FindNext/FindClose win32api-functions.
DIR* DLLINTERNAL my_opendir(const char* path)
{
	char search_path[MAX_PATH];

	// Add wildcards to path
	safevoid_snprintf(search_path, sizeof(search_path), "%s\\*.*", path);

	// Get memory for new DIR object
	DIR* dir = static_cast<my_DIR*>(calloc(1, sizeof(DIR)));

	// Start searching
	dir->handle = FindFirstFileA(search_path, &dir->find_data);
	if (dir->handle == INVALID_HANDLE_VALUE) {
		free(dir);
		return nullptr;
	}

	// Found file
	dir->not_found = 0;

	return dir;
}

dirent* DLLINTERNAL my_readdir(DIR* dir)
{
	// If not found stop
	if (!dir || dir->not_found)
		return nullptr;

	// Set filename
	STRNCPY(dir->ent.d_name, dir->find_data.cFileName, sizeof(dir->ent.d_name));

	// Search next
	dir->not_found = !FindNextFileA(dir->handle, &dir->find_data);

	return&dir->ent;
}

void DLLINTERNAL my_closedir(DIR* dir)
{
	if (!dir)
		return;

	FindClose(dir->handle);
	free(dir);
}
#endif /* _WIN32 */

//get module handle of memptr
#ifdef __linux__
DLHANDLE DLLINTERNAL get_module_handle_of_memptr(const void* memptr)
{
    Dl_info dli;
    memset(&dli, 0, sizeof(dli));

    if (dladdr(memptr, &dli))
        return static_cast<DLHANDLE>(dlopen(dli.dli_fname, RTLD_NOW));
    else
        return nullptr;
}
#else
DLHANDLE DLLINTERNAL get_module_handle_of_memptr(const void* memptr)
{
	MEMORY_BASIC_INFORMATION MBI;

	if (!VirtualQuery(memptr, &MBI, sizeof(MBI)))
		return nullptr;
	if (MBI.State != MEM_COMMIT)
		return nullptr;
	if (!MBI.AllocationBase)
		return nullptr;

	return static_cast<DLHANDLE>(MBI.AllocationBase);
}
#endif /* __linux__ */