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
#ifndef RET_TYPE_H
#define RET_TYPE_H

#include "new_baseclass.h"

class class_ret_t : public class_metamod_new {
public:
	// Construction
	class_ret_t() = default;
	class_ret_t(const float f) { data.f = f; }
	class_ret_t(void* p) { data.p = p; }
	class_ret_t(const char* pc) { data.pc = pc; }
	class_ret_t(const int i) { data.i = i; }
	class_ret_t(const short s) { data.i = s; }
	class_ret_t(const char c) { data.i = c; }
	class_ret_t(const unsigned int ui) { data.ui = ui; }
	class_ret_t(const unsigned long ui) { data.ui = ui; }
	class_ret_t(const unsigned short us) { data.ui = us; }
	class_ret_t(const unsigned char uc) { data.ui = uc; }

	// Reading/Writing
	void* getptr() { return&data; }

#define SET_RET_CLASS(ret,type,x) \
		*(type*)((ret).getptr()) = (type)(x)
#define GET_RET_CLASS(ret,type) \
		(*(type*)((ret).getptr()))
private:
	//Data (select data size of largest type) (x86: 32bit, x86_64: 64bit)
	union {
		void* p;
		const char* pc;
		float f;
		long i;
		unsigned long ui;
	} data;
};

#endif /*RET_TYPE_H*/
