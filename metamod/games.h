// vi: set ts=4 sw=4 :
// vim: set tw=75 :
 
// games.h - list of supported game mods and their data
 
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
 
// This list is now kept in a separate file to facilitate generating the
// list from game data stored in a convenient db.

#if defined(__x86_64__) || defined(__amd64__)
#  define MODARCH "_amd64"
#else
#  define MODARCH "_i386"
#endif

	{"action", "ahl_i386.so", "ahl.dll", "Action Half-Life"},
	{ "ag",                "ag_i386.so",           "ag.dll",            "Adrenaline Gamer Steam" },
	{ "ag3",               "hl_i386.so",           "hl.dll",            "Adrenalinegamer 3.x" },
	{ "aghl",              "ag_i386.so",           "ag.dll",            "Adrenalinegamer 4.x" },
	{ "arg",               "arg_i386.so",          "hl.dll",            "Arg!" },
	{ "asheep",            "hl_i386.so",           "hl.dll",            "Azure Sheep" },
	{ "hcfrenzy",          "hcfrenzy.so",              "hcfrenzy.dll",      "Headcrab Frenzy" },
	{ "bdef",              "../cl_dlls/server.so",     "../cl_dlls/server.dll", "Base Defense [Modification]" },
	{ "bdef",              "server.so",                     "server.dll",        "Base Defense [Steam Version]" },
	{ "bg",                "bg_i386.so",           "bg.dll",            "The Battle Grounds" },
	{ "bhl",               "none",                     "bhl.dll",           "Brutal Half-Life" },
	{ "bot",               "bot_i386.so",          "bot.dll",           "Bot" },
	{ "brainbread",        "bb_i386.so",           "bb.dll",            "BrainBread" },
	{ "bumpercars",        "hl_i386.so",           "hl.dll",            "Bumper Cars" },
	{ "buzzybots",         "bb_i386.so",           "bb.dll",            "BuzzyBots" },
	{ "ckf3",              "none",                     "mp.dll",            "Chicken Fortress 3" },
	{ "cs13",              "cs_i386.so",           "mp.dll",            "Counter-Strike 1.3" },
	{ "cstrike",           "cs.so",           "mp.dll",            "Counter-Strike" },
	{ "csv15",             "cs_i386.so",           "mp.dll",            "CS 1.5 for Steam" },
	{ "czero",             "cs.so",           "mp.dll",            "Counter-Strike:Condition Zero" },
	{ "dcrisis",           "dc_i386.so",           "dc.dll",            "Desert Crisis" },
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
	{ "HLAinGOLDSrc",      "none",                     "hl.dll",            "Half-Life Alpha in GOLDSrc" },
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
	{ "outbreak",          "none",                     "hl.dll",            "Out Break" },
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
	{ "stargatetc",        "hl_i386.so",           "hl.dll",            "StargateTC" },
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
	{ "valve",             "hl.so",           "hl.dll",            "Half-Life Deathmatch" },
	{ "vs",                "vs_i386.so",           "mp.dll",            "VampireSlayer" },
	{ "wantedhl",          "hl_i386.so",           "wanted.dll",        "Wanted!" },
	{ "wasteland",         "whl_linux.so",             "mp.dll",            "Wasteland" },
	{ "weapon_wars",       "ww_i386.so",           "hl.dll",            "Weapon Wars" },
	{ "wizwars",           "mp_i386.so",           "hl.dll",            "Wizard Wars" },
	{ "wormshl",           "wormshl_i586.so",          "wormshl.dll",       "WormsHL" },
	{ "zp",                "none",                     "mp.dll",            "Zombie Panic" },
