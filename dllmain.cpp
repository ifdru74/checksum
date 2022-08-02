// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "CryptoProvider.h"
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        ifd::crypto::sum::CryptoProvider::init();
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        ifd::crypto::sum::CryptoProvider::destroy();
        break;
    }
    return TRUE;
}

