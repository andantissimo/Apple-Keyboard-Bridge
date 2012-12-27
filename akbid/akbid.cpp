/**
 *  Apple Keyboard Bridge - Device ID Enumerator
 *  
 *  @author  MALU
 *  @version $Id: akbid.cpp 64 2012-09-24 09:26:38Z malu $
 */

#define  WINVER       0x0501
#define _WIN32_WINNT  0x0501
#define  WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <tchar.h>

#include "../akb/winapi.h"

enum
{
	VID_APPLE = 0x05AC,
};

struct WinAPI_Initializer
{
	WinAPI_Initializer() { WinAPI_Initialize(); }
	~WinAPI_Initializer() { WinAPI_Uninitialize(); }
};

#include <list>
#include <sstream>
#include <algorithm>

std::list<WORD> EnumHID(WORD VenderID)
{
	std::list<WORD> ProductIDs;
	
	GUID guid;
	WinAPI.HID.GetHidGuid(&guid);
	HDEVINFO hDevInfo = WinAPI.Setup.GetClassDevs(&guid, NULL, NULL, DIGCF_DEVICEINTERFACE);
	if (!hDevInfo)
		return ProductIDs;
	SP_DEVICE_INTERFACE_DATA diData = { sizeof diData };
	for (DWORD index = 0;
	     WinAPI.Setup.EnumDeviceInterfaces(hDevInfo, NULL, &guid, index, &diData);
	     index++)
	{
		BYTE diDetailImpl[sizeof(DWORD) + sizeof(TCHAR) * MAX_PATH];
		PSP_DEVICE_INTERFACE_DETAIL_DATA pdiDetail
			= reinterpret_cast<PSP_DEVICE_INTERFACE_DETAIL_DATA>(diDetailImpl);
		pdiDetail->cbSize = sizeof*pdiDetail;
		DWORD sizeDetail;
		if (WinAPI.Setup.GetDeviceInterfaceDetail(hDevInfo,
		    &diData, pdiDetail, sizeof diDetailImpl, &sizeDetail, NULL))
		{
			HANDLE hDevice = CreateFile(pdiDetail->DevicePath,
				GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
				NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
			if (hDevice == INVALID_HANDLE_VALUE)
				continue;
			HIDD_ATTRIBUTES attr = { sizeof attr };
			if (WinAPI.HID.GetAttributes(hDevice, &attr) && attr.VenderID == VenderID) {
				ProductIDs.push_back(attr.ProductID);
			}
			CloseHandle(hDevice);
		}
	}
	WinAPI.Setup.DestroyDeviceInfoList(hDevInfo);
	
	ProductIDs.erase(std::unique(ProductIDs.begin(), ProductIDs.end()), ProductIDs.end());
	return ProductIDs;
}

int APIENTRY _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	WinAPI_Initializer Initializer;
	
	std::list<WORD> ProductIDs = EnumHID(VID_APPLE);
	if (ProductIDs.empty()) {
		::MessageBox(NULL, TEXT("No Apple Keyboard found"), TEXT("akbid"), MB_ICONWARNING);
		return 0;
	}
	for (std::list<WORD>::iterator it = ProductIDs.begin(); it != ProductIDs.end(); ++it) {
		std::basic_stringstream<TCHAR> ss;
		ss << TEXT("Product ID: 0x") << std::hex << *it;
		::MessageBox(NULL, ss.str().c_str(), TEXT("akbid"), MB_ICONINFORMATION);
	}
	return 0;
}
