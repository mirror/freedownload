#pragma once

// define to import implementation from a common DLL module
//#define VMSCL_IMPL_IMPORT
// define in common DLL module (if any)
//#define VMSCL_IMPL_EXPORT

#ifndef VMSCL_IMPL_IMPORT

#if defined (VMSCL_IMPL_EXPORT)
	#define VMSCL_EXPORTABLE __declspec (dllexport)
#else
	#define VMSCL_EXPORTABLE
#endif

#endif // VMSCL_IMPL_IMPORT