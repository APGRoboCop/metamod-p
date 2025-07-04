// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
// vi: set ts=4 sw=4 :
// vim: set tw=75 :

// sdk_util.cpp - utility routines from HL SDK util.cpp

// Selected portions of dlls/util.cpp from SDK 2.1.
// Functions copied from there as needed...
// And modified to avoid buffer overflows (argh).
// Also modified to remove dependency on CBaseEntity class.

/***
*
*	Copyright (c) 1999, 2000 Valve LLC. All rights reserved.
*
*	This product contains software technology licensed from Id
*	Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc.
*	All Rights Reserved.
*
*   Use, distribution, and modification of this source code and/or resulting
*   object code is restricted to non-commercial enhancements to products from
*   Valve LLC.  All other use, distribution, or modification is prohibited
*   without written permission from Valve LLC.
*
****/
/*

===== util.cpp ========================================================

  Utility code.  Really not optional after all.

*/

#include <extdll.h>
#include "sdk_util.h"

#include <cstring>			// for strncpy(), etc

#include "osdep.h"			// win32 vsnprintf, etc

const char* DLLINTERNAL META_UTIL_VarArgs(const char* format, ...)
{
	va_list argptr;
	static char string[4096];

	va_start(argptr, format);
	safevoid_vsnprintf(string, sizeof(string), format, argptr);
	va_end(argptr);

	return string;
}

short DLLINTERNAL FixedSigned16(const float value, const float scale)
{
	int output = static_cast<int>(value * scale);

	if (output > 32767)
		output = 32767;

	if (output < -32768)
		output = -32768;

	return static_cast<short>(output);
}

unsigned short DLLINTERNAL FixedUnsigned16(const float value, const float scale)
{
	int output = static_cast<int>(value * scale);
	if (output < 0)
		output = 0;
	if (output > 0xFFFF)
		output = 0xFFFF;

	return static_cast<unsigned short>(output);
}

void DLLINTERNAL META_UTIL_HudMessage(edict_t* pEntity, const hudtextparms_t& textparms, const char* pMessage)
{
	if (fast_FNullEnt(pEntity) || pEntity->free)
		return;

	MESSAGE_BEGIN(MSG_ONE, SVC_TEMPENTITY, nullptr, pEntity);
	WRITE_BYTE(TE_TEXTMESSAGE);
	WRITE_BYTE(textparms.channel & 0xFF);

	WRITE_SHORT(FixedSigned16(textparms.x, 1 << 13));
	WRITE_SHORT(FixedSigned16(textparms.y, 1 << 13));
	WRITE_BYTE(textparms.effect);

	WRITE_BYTE(textparms.r1);
	WRITE_BYTE(textparms.g1);
	WRITE_BYTE(textparms.b1);
	WRITE_BYTE(textparms.a1);

	WRITE_BYTE(textparms.r2);
	WRITE_BYTE(textparms.g2);
	WRITE_BYTE(textparms.b2);
	WRITE_BYTE(textparms.a2);

	WRITE_SHORT(FixedUnsigned16(textparms.fadeinTime, 1 << 8));
	WRITE_SHORT(FixedUnsigned16(textparms.fadeoutTime, 1 << 8));
	WRITE_SHORT(FixedUnsigned16(textparms.holdTime, 1 << 8));

	if (textparms.effect == 2)
		WRITE_SHORT(FixedUnsigned16(textparms.fxTime, 1 << 8));

	if (strlen(pMessage) < 512)
	{
		WRITE_STRING(pMessage);
	}
	else
	{
		char tmp[512];
		strncpy(tmp, pMessage, 511);
		tmp[511] = 0;
		WRITE_STRING(tmp);
	}
	MESSAGE_END();
}