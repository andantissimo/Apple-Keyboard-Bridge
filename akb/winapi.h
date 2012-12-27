/**
 *  WinAPI dynamic loader
 *  
 *  @author  MALU
 *  @version $Id: winapi.h 64 2012-09-24 09:26:38Z malu $
 */

#pragma once

#include <setupapi.h>
#pragma warning (disable: 4201)
#include <mmsystem.h>
#pragma warning (default: 4201)

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

#include <pshpack1.h>
typedef struct HIDD_ATTRIBUTES
{
	DWORD Size;
	WORD  VenderID;
	WORD  ProductID;
	WORD  VersionNumber;
} HIDD_ATTRIBUTES;
#include <poppack.h>

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
	struct DWM
	{
		HMODULE hDLL;
		VOID (WINAPI *Flip3D)(VOID);
	} DWM;
} WinAPI;

void WinAPI_Initialize(void)
{
#define PROC_(p) *(FARPROC *)&(p)
	
	WinAPI.Setup.hDLL = LoadLibrary(TEXT("setupapi.dll"));
	PROC_(WinAPI.Setup.GetClassDevs)             = GetProcAddress(WinAPI.Setup.hDLL, "SetupDiGetClassDevs" WINAPI_SUFFIX);
	PROC_(WinAPI.Setup.DestroyDeviceInfoList)    = GetProcAddress(WinAPI.Setup.hDLL, "SetupDiDestroyDeviceInfoList");
	PROC_(WinAPI.Setup.EnumDeviceInterfaces)     = GetProcAddress(WinAPI.Setup.hDLL, "SetupDiEnumDeviceInterfaces");
	PROC_(WinAPI.Setup.GetDeviceInterfaceDetail) = GetProcAddress(WinAPI.Setup.hDLL, "SetupDiGetDeviceInterfaceDetail" WINAPI_SUFFIX);
	
	WinAPI.HID.hDLL = LoadLibrary(TEXT("hid.dll"));
	PROC_(WinAPI.HID.GetHidGuid)    = GetProcAddress(WinAPI.HID.hDLL, "HidD_GetHidGuid");
	PROC_(WinAPI.HID.GetAttributes) = GetProcAddress(WinAPI.HID.hDLL, "HidD_GetAttributes");
	
	WinAPI.MCI.hDLL = LoadLibrary(TEXT("winmm.dll"));
	PROC_(WinAPI.MCI.SendCommand) = GetProcAddress(WinAPI.MCI.hDLL, "mciSendCommand" WINAPI_SUFFIX);
	
	/* Vista or later */
	WinAPI.DWM.hDLL = LoadLibrary(TEXT("dwmapi.dll"));
	PROC_(WinAPI.DWM.Flip3D) = GetProcAddress(WinAPI.DWM.hDLL, (LPCSTR)105);
	
#undef PROC_
}

void WinAPI_Uninitialize(void)
{
	FreeLibrary(WinAPI.Setup.hDLL);
	FreeLibrary(WinAPI.HID.hDLL);
	FreeLibrary(WinAPI.MCI.hDLL);
	FreeLibrary(WinAPI.DWM.hDLL);
}
