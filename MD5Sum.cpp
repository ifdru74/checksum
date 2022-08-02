#include "pch.h"
#include <iostream>
#include <fstream>
#if defined(_MSC_VER) || defined(__BORLANDC__)
#include <wincrypt.h>
#endif
#include "MD5Sum.h"
#include "CryptoProvider.h"
constexpr DWORD    MD5Sum_dwZero = (DWORD)0;

using namespace ifd::crypto::sum;

    VALIDATIONSUM_API MD5Sum::MD5Sum() :
        m_hHash{ 0 }, md5_bin{ 0 }, m_file_md5{ 0 }
    {
    }

    VALIDATIONSUM_API MD5Sum::~MD5Sum() {
        clear();
    }

    VALIDATIONSUM_API int MD5Sum::initSum() {
        clear();
#if !defined(_MSC_VER) && !defined(__BORLANDC__)
        return MD5_Init( &m_hHash );
#else
        DWORD	dwStatus = MD5Sum_dwZero;
        // Get handle to the crypto provider
        if (CryptoProvider::init() != 0)
        {
        }
        else
        {
            if (!CryptCreateHash(CryptoProvider::get(), CALG_MD5, 0, 0, &m_hHash))
            {
                dwStatus = GetLastError();
                m_hHash = 0;
                //return dwStatus;
            }
        }
        return (int)dwStatus;
#endif // !WIN32
    }

    VALIDATIONSUM_API int MD5Sum::appendSum(const void *data, size_t dataLen) {
        m_data_size += dataLen;
#if !defined(_MSC_VER) && !defined(__BORLANDC__)
        return MD5_Update( &m_hHash, data, dataLen );
#else
        DWORD	dwStatus = MD5Sum_dwZero;
        if (!CryptHashData(m_hHash, (const BYTE*)data, (DWORD)dataLen, 0))
        {
            dwStatus = GetLastError();
            CryptDestroyHash(m_hHash);
            m_hHash = 0;
        }
        return (int)dwStatus;
#endif // !WIN32
    }

    VALIDATIONSUM_API int MD5Sum::finalizeSum() {
        DWORD dwStatus = MD5Sum_dwZero;
#if !defined(_MSC_VER) && !defined(__BORLANDC__)
        MD5_Final( md5_bin, &m_hHash );
#else
        DWORD	cbHash = MD5_DIGEST_LENGTH;
        if (!CryptGetHashParam(m_hHash, HP_HASHVAL, md5_bin, &cbHash, 0))
        {
            dwStatus = GetLastError();
        }
        CryptDestroyHash(m_hHash);
        m_hHash = 0;
#endif // !WIN32
        return (int) dwStatus;
    }

    VALIDATIONSUM_API const char* MD5Sum::c_str()
    {
        int   nRet = finalizeSum();
        if (finalizeSum() == 0)
        {
            unsigned char szLocal[MD5_STR_LEN+1] = { 0 };
            size_t pos = 0;
            for (size_t n = 0; n < MD5_DIGEST_LENGTH; n++) {
                for (size_t d = 0; d < 2; d++) {
                    if (d) {
                        szLocal[pos+d] = (md5_bin[n] & 0xf) + 0x30;
                    } else {
                        szLocal[pos + d] = ((md5_bin[n] & 0xf0) >> 4) + 0x30;
                    }
                    if (szLocal[pos + d] > 0x39)
                        szLocal[pos + d] += 7;
                }
                pos += 2;
                if (pos > MD5_STR_LEN)
                    break;
            }
#if !defined(_MSC_VER) && !defined(__BORLANDC__)
            strncpy(m_file_md5, (const char*)szLocal, sizeof(m_file_md5));
#else
            strncpy_s(m_file_md5, sizeof(m_file_md5), (const char*)szLocal, MD5_STR_LEN);
#endif // _MSC_VER || __BORLANDC__
        }
        else
        {
            int* pInt = (int*)m_file_md5;
            *pInt = 0;
        }
        return m_file_md5;
    }

    VALIDATIONSUM_API void MD5Sum::clear() {
#if defined(_MSC_VER) || defined(__BORLANDC__)
        if (m_hHash != 0)
        {
            CryptDestroyHash(m_hHash);
            m_hHash = 0;
        }
#else
        ::memset( &m_hHash, 0, sizeof( MD5_CTX ));
#endif
        ::memset( md5_bin, 0, MD5_DIGEST_LENGTH );
        m_data_size = 0;
        ::memset(m_file_md5, 0, sizeof(m_file_md5));
    }
