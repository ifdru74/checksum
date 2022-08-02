#ifndef PCH_H
#define PCH_H
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>
#if defined(_MSC_VER) || defined(__BORLANDC__)
// windows staff
#define WIN32_LEAN_AND_MEAN // suppress rarely used components
// Windows includes
// add headers that you want to pre-compile here
#include "framework.h"
#else // defined(_MSC_VER) || defined(__BORLANDC__)
#define DWORD uint32_t
#define HCRYPTPROV int
#define HCRYPTHASH MD5_CTX
#ifndef NOERROR
#define NOERROR 0
#endif
#ifndef errno_t
#define errno_t int
#endif
#endif // defined(_MSC_VER) || defined(__BORLANDC__)
// class names mapping
#ifdef _UNICODE
#define STDSTRING std::wstring
#else // _UNICODE
#define STDSTRING std::string
#endif //_UNICODE
#include "tchar_port.h"
#endif //PCH_H
