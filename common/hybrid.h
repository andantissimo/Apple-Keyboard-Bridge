/**
 *  Managed/Unmanaged hybrid assistant
 *  
 *  @author  MALU
 *  @version $Id: hybrid.h 64 2012-09-24 09:26:38Z malu $
 */

#pragma once

#ifndef _MANAGED

#define nopadding __declspec(align(1))

#define ref_struct struct
#define val_struct struct

#define fixed_array(_type, _size, _name) _type _name[_size]

#else/*!_MANAGED*/

#define nopadding \
	[System::Runtime::InteropServices::StructLayout( \
		System::Runtime::InteropServices::LayoutKind::Sequential)]

#define ref_struct ref struct
#define val_struct value struct

#define fixed_array(_type, _size, _name) \
	[System::Runtime::InteropServices::MarshalAs( \
		System::Runtime::InteropServices::UnmanagedType::ByValArray, \
		SizeConst=_size)] \
	array<_type>^ _name;

#endif/*_MANAGED*/
