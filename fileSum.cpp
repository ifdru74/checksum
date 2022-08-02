//
// Created by ifdru on 20.06.2022.
//
#include "pch.h"
#include "fileSum.h"
#include <cstdio>
#include <cstring>
#include "CryptoProvider.h"

using namespace ifd::crypto::sum;

errno_t openFile(FILE** f, const TCHAR* fileName)
{
    errno_t ret;
#if defined(_MSC_VER) || defined(__BORLANDC__)
    ret = _tfopen_s(f, fileName, _T("rb"));
#else
#ifdef _UNICODE
    STDSTRING   s1(fileName);
    std::string mbFIleName(s1.begin(), s1.end());
    *f = fopen(mbFIleName.c_str(), "rb");
#else
    *f = fopen(fileName, "rb");
#endif
    if (f != nullptr)
    {
        ret = NOERROR;
    }
    else
    {
        ret = errno;
    }
#endif
    return ret;
}

VALIDATIONSUM_API int  fileSum(ifd::crypto::sum::CheckSum& sum, const TCHAR* fileName)
{
    int ret;
    FILE*	f;

    sum.clear();
    if((ret=openFile(&f, fileName))==NOERROR && f!=nullptr)
    {
        size_t  n;
        char    buf[ifd::crypto::sum::SIZE32K]={0};
        do
        {
            ::memset(buf, 0, CheckSum::getBlockSize());
#if defined(_MSC_VER) || defined(__BORLANDC__)
            n = fread_s(buf, CheckSum::getBlockSize(), 1, CheckSum::getBlockSize(), f);
#else
            n = fread(buf, 1, CheckSum::getBlockSize(), f);
#endif
            if (n > 0)
            {
                sum.appendSum(buf, n);
            }
            else
            {
                ret = errno;
                break;
            }
        } while (n >= CheckSum::getBlockSize());
        fclose(f);
    }
    return ret;
}