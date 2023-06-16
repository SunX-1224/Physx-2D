#pragma once
/*
	This is the core of application where dll interface is defined.
*/

#ifdef PHSX_PLATFORM_WINDOWS
	#ifdef PHSX_BUILD_DLL
		#define PHYSX2D_API _declspec(dllexport)
	#else
		#define	PHYSX2D_API _declspec(dllimport)
	#endif
#else
	#error ONLY_WINDOWS_SUPPORTED
#endif

