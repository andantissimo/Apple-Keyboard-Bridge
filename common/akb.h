/**
 *  Apple Keyboard Bridge
 *  
 *  @author  MALU
 *  @version $Id: akb.h 64 2012-09-24 09:26:38Z malu $
 */

#pragma once

#ifndef _MANAGED
#define  WINVER       0x0501
#define _WIN32_WINNT  0x0501
#define  WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <tchar.h>
#else
#include "wincli.h"
#endif

#include "hybrid.h"

#ifndef _MANAGED
const struct App
{
	LPCTSTR Class;
	LPCTSTR Title;
} App =
{
	TEXT("APPLE_KEYBOARD_BRIDGE"),
	TEXT("Apple Keyboard Bridge"),
};
#else
public value struct App
{
	literal System::String^ Class = L"APPLE_KEYBOARD_BRIDGE";
	literal System::String^ Title = L"Apple Keyboard Bridge";
};
#endif

enum
{
	WM_APP_RELOAD = WM_APP + 1,
};

enum
{
	CONFIG_SIGNATURE = ('A' | 'K' << 8 | 'B' << 16),
	CONFIG_NUM_CMDS  = 8,
};
typedef nopadding ref_struct Config
{
	DWORD Signature;
	val_struct Key
	{
		WORD Power, Eject, Alnum, Kana;
	} Key;
	val_struct Fn
	{
		WORD F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12;
		WORD Del, Up, Down, Left, Right, Eject;
	} Fn;
	fixed_array(WORD, CONFIG_NUM_CMDS, cbCmds);
} Config;

enum
{
	FIRE_NOTHING  = 0xFFFF,
	FIRE_POWER    = 0xFFFE,
	FIRE_EJECT    = 0xFFFD,
	FIRE_FLIP3D   = 0xFFFC,
	FIRE_ALPHA_UP = 0xFFFB,
	FIRE_ALPHA_DN = 0xFFFA,
	FIRE_CMD_0    = 0xFF00,
};
enum
{
	/* single action keys */
	CONFIG_INIT_KEY_POWER = FIRE_POWER,
	CONFIG_INIT_KEY_EJECT = VK_F13,
	CONFIG_INIT_KEY_ALNUM = VK_NONCONVERT,
	CONFIG_INIT_KEY_KANA  = VK_CONVERT,
	/* Fn combination keys */
	CONFIG_INIT_FN_F1     = FIRE_ALPHA_DN,
	CONFIG_INIT_FN_F2     = FIRE_ALPHA_UP,
	CONFIG_INIT_FN_F3     = FIRE_FLIP3D,
	CONFIG_INIT_FN_F4     = FIRE_NOTHING,
	CONFIG_INIT_FN_F5     = FIRE_NOTHING,
	CONFIG_INIT_FN_F6     = FIRE_NOTHING,
	CONFIG_INIT_FN_F7     = VK_MEDIA_PREV_TRACK,
	CONFIG_INIT_FN_F8     = VK_MEDIA_PLAY_PAUSE,
	CONFIG_INIT_FN_F9     = VK_MEDIA_NEXT_TRACK,
	CONFIG_INIT_FN_F10    = VK_VOLUME_MUTE,
	CONFIG_INIT_FN_F11    = VK_VOLUME_DOWN,
	CONFIG_INIT_FN_F12    = VK_VOLUME_UP,
	CONFIG_INIT_FN_DEL    = VK_DELETE,
	CONFIG_INIT_FN_UP     = VK_PRIOR,
	CONFIG_INIT_FN_DOWN   = VK_NEXT,
	CONFIG_INIT_FN_LEFT   = VK_HOME,
	CONFIG_INIT_FN_RIGHT  = VK_END,
	CONFIG_INIT_FN_EJECT  = FIRE_EJECT,
};

enum
{
	ALPHA_DELTA = 0xFF / 5
};
