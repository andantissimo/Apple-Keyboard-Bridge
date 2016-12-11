/**
 * Apple Keyboard Bridge https://github.com/andantissimo/Apple-Keyboard-Bridge
 */
#pragma once

typedef System::UInt32 DWORD, ULONG, UINT;
typedef System::UInt16 WORD, USHORT;
typedef System::Byte   BYTE;
typedef System::Int32  BOOL;
typedef System::IntPtr HANDLE, HWND;
typedef System::IntPtr LRESULT, WPARAM, LPARAM;

enum
{
	FALSE = 0, TRUE = 1
};

enum
{
	WM_APP = 0x8000,
};

enum
{
	BCM_SETSHIELD = 0x160C,
};

enum
{
	VK_KANJI      = 0x19,
	VK_CONVERT    = 0x1C,
	VK_NONCONVERT = 0x1D,

	VK_PRIOR      = 0x21, // Page Up
	VK_NEXT       = 0x22, // Page Down
	VK_END        = 0x23,
	VK_HOME       = 0x24,

	VK_SNAPSHOT   = 0x2C, // Print Screen
	VK_INSERT     = 0x2D,
	VK_DELETE     = 0x2E,

	VK_F1         = 0x70,
	VK_F2         = 0x71,
	VK_F3         = 0x72,
	VK_F4         = 0x73,
	VK_F5         = 0x74,
	VK_F6         = 0x75,
	VK_F7         = 0x76,
	VK_F8         = 0x77,
	VK_F9         = 0x78,
	VK_F10        = 0x79,
	VK_F11        = 0x7A,
	VK_F12        = 0x7B,
	VK_F13        = 0x7C,
	VK_F14        = 0x7D,
	VK_F15        = 0x7E,
	VK_F16        = 0x7F,
	VK_F17        = 0x80,
	VK_F18        = 0x81,
	VK_F19        = 0x82,
	VK_F20        = 0x83,
	VK_F21        = 0x84,
	VK_F22        = 0x85,
	VK_F23        = 0x86,
	VK_F24        = 0x87,

	VK_BROWSER_BACK      = 0xA6,
	VK_BROWSER_FORWARD   = 0xA7,
	VK_BROWSER_REFRESH   = 0xA8,
	VK_BROWSER_STOP      = 0xA9,
	VK_BROWSER_SEARCH    = 0xAA,
	VK_BROWSER_FAVORITES = 0xAB,
	VK_BROWSER_HOME      = 0xAC,
	VK_VOLUME_MUTE       = 0xAD,
	VK_VOLUME_DOWN       = 0xAE,
	VK_VOLUME_UP         = 0xAF,
	VK_MEDIA_NEXT_TRACK  = 0xB0,
	VK_MEDIA_PREV_TRACK  = 0xB1,
	VK_MEDIA_STOP        = 0xB2,
	VK_MEDIA_PLAY_PAUSE  = 0xB3,
	VK_LAUNCH_MAIL       = 0xB4,
};

[System::Runtime::InteropServices::DllImport("user32.dll", CharSet=System::Runtime::InteropServices::CharSet::Auto)]
HWND FindWindow(System::String^, System::String^);

[System::Runtime::InteropServices::DllImport("user32.dll", CharSet=System::Runtime::InteropServices::CharSet::Auto)]
LRESULT PostMessage(HWND, UINT, WPARAM, LPARAM);

[System::Runtime::InteropServices::DllImport("user32.dll", CharSet=System::Runtime::InteropServices::CharSet::Auto)]
LRESULT SendMessage(HWND, UINT, WPARAM, LPARAM);
