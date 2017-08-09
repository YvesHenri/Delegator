#ifndef DELEGATOR_API_H
#define DELEGATOR_API_H

#if defined(_WIN32) 
	#define PLATFORM_WINDOWS
#elif defined(__APPLE__) && defined(__MACH__)
	#include "TargetConditionals.h" // Requires "Command Line Tools for Xcode" package
	#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
		#define PLATFORM_IOS
	#elif TARGET_OS_MAC
		#define PLATFORM_MACOS
	#else
		#error This Apple operating system is not supported by Delegator library
	#endif
#elif defined(__unix__)
	#if defined(__ANDROID__)
		#define PLATFORM_ANDROID
	#elif defined(__linux__)
		#define PLATFORM_LINUX
	#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
		#define PLATFORM_FREEBSD
	#else
		#error This UNIX operating system is not supported by Delegator library
	#endif
#else
	#error This operating system is not supported by Delegator library
#endif

// If DELEGATOR_STATIC is defined as a "Preprocessor Definition", static libs are created instead (does not require .dll)
#if !defined(DELEGATOR_STATIC)
	// Windows
	#if defined(PLATFORM_WINDOWS)
		#define DELEGATOR_API		 __declspec(dllexport)
		#define DELEGATOR_API_IMPORT __declspec(dllimport)

		// For Visual C++ compilers, we also need to turn off this annoying C4251 warning:
		// "Needs to have dll-interface to be used by clients of class"
		#ifdef _MSC_VER
			#pragma warning(disable: 4251)
		#endif
	// Linux, FreeBSD, Mac OS X
	#else
		#if __GNUC__ >= 4
			// GCC 4 has special keywords for showing/hidding symbols, the same keyword is used for both importing and exporting
			#define DELEGATOR_API		 __attribute__ ((__visibility__ ("default")))
			#define DELEGATOR_API_IMPORT __attribute__ ((__visibility__ ("default")))
		#else
			// GCC < 4 has no mechanism to explicitely hide symbols, everything's exported
			#define DELEGATOR_API
			#define DELEGATOR_API_IMPORT
		#endif
	#endif
#else
	// Static build doesn't need import/export macros
	#define DELEGATOR_API
	#define DELEGATOR_API_IMPORT
#endif

#endif