/**
 * Apple Keyboard Bridge https://github.com/andantissimo/Apple-Keyboard-Bridge
 */
#pragma once

#include <shellapi.h>
#include <setupapi.h>
#include <mmsystem.h>
#include <wbemidl.h>

#ifdef UNICODE
#define WINAPI_SUFFIX "W"
#else
#define WINAPI_SUFFIX "A"
#endif

#ifdef NDEBUG
#ifdef RtlZeroMemory
#undef RtlZeroMemory
EXTERN_C VOID WINAPI RtlZeroMemory(LPVOID, DWORD);
#endif
#endif

#pragma pack(push, 1)

typedef struct HIDD_ATTRIBUTES
{
	DWORD Size;
	WORD  VenderID;
	WORD  ProductID;
	WORD  VersionNumber;
} HIDD_ATTRIBUTES;

#define PHYSICAL_MONITOR_DESCRIPTION_SIZE 128

typedef struct PHYSICAL_MONITOR
{
	HANDLE hPhysicalMonitor;
	WCHAR szPhysicalMonitorDescription[PHYSICAL_MONITOR_DESCRIPTION_SIZE];
} PHYSICAL_MONITOR;

#pragma pack(pop)

static struct WinAPI
{
	struct Setup
	{
		HMODULE hDLL;
		HDEVINFO (WINAPI *GetClassDevs)(LPGUID, PCSTR, HWND, DWORD);
		BOOL     (WINAPI *DestroyDeviceInfoList)(HDEVINFO);
		BOOL     (WINAPI *EnumDeviceInterfaces)(HDEVINFO, PSP_DEVINFO_DATA,
		                                        LPGUID, DWORD, PSP_DEVICE_INTERFACE_DATA);
		BOOL     (WINAPI *GetDeviceInterfaceDetail)(HDEVINFO, PSP_DEVICE_INTERFACE_DATA,
		                                            PSP_DEVICE_INTERFACE_DETAIL_DATA,
		                                            DWORD, PDWORD, PSP_DEVINFO_DATA);
	} Setup;

	struct HID
	{
		HMODULE hDLL;
		VOID    (WINAPI *GetHidGuid)(LPGUID);
		BOOLEAN (WINAPI *GetAttributes)(HANDLE, HIDD_ATTRIBUTES *);
		BOOLEAN (WINAPI *GetInputReport)(HANDLE, LPVOID, DWORD);
	} HID;

	struct MCI
	{
		HMODULE hDLL;
		MCIERROR (WINAPI *SendCommand)(MCIDEVICEID, UINT, DWORD, DWORD_PTR);
	} MCI;
} WinAPI;

void WinAPI_Initialize(void)
{
#define PROC_(p) *(FARPROC *)&(p)

	WinAPI.Setup.hDLL = LoadLibrary(TEXT("setupapi.dll"));
	PROC_(WinAPI.Setup.GetClassDevs)
		= GetProcAddress(WinAPI.Setup.hDLL, "SetupDiGetClassDevs" WINAPI_SUFFIX);
	PROC_(WinAPI.Setup.DestroyDeviceInfoList)
		= GetProcAddress(WinAPI.Setup.hDLL, "SetupDiDestroyDeviceInfoList");
	PROC_(WinAPI.Setup.EnumDeviceInterfaces)
		= GetProcAddress(WinAPI.Setup.hDLL, "SetupDiEnumDeviceInterfaces");
	PROC_(WinAPI.Setup.GetDeviceInterfaceDetail)
		= GetProcAddress(WinAPI.Setup.hDLL, "SetupDiGetDeviceInterfaceDetail" WINAPI_SUFFIX);

	WinAPI.HID.hDLL = LoadLibrary(TEXT("hid.dll"));
	PROC_(WinAPI.HID.GetHidGuid)
		= GetProcAddress(WinAPI.HID.hDLL, "HidD_GetHidGuid");
	PROC_(WinAPI.HID.GetAttributes)
		= GetProcAddress(WinAPI.HID.hDLL, "HidD_GetAttributes");

	WinAPI.MCI.hDLL = LoadLibrary(TEXT("winmm.dll"));
	PROC_(WinAPI.MCI.SendCommand)
		= GetProcAddress(WinAPI.MCI.hDLL, "mciSendCommand" WINAPI_SUFFIX);

#undef PROC_
}

void WinAPI_Uninitialize(void)
{
	FreeLibrary(WinAPI.Setup.hDLL);
	FreeLibrary(WinAPI.HID.hDLL);
	FreeLibrary(WinAPI.MCI.hDLL);
}
