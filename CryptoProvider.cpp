#include "pch.h"
#if defined(_MSC_VER) || defined(__BORLANDC__)
#include <wincrypt.h>
#endif
#include "CryptoProvider.h"
using namespace ifd::crypto::sum;
HCRYPTPROV    CryptoProvider::m_hProv = 0;
size_t	CryptoProvider::m_blockSize = ifd::crypto::sum::SIZE4K;

int CryptoProvider::init() {
    DWORD dwStatus = 0;
#if defined(_MSC_VER) || defined(__BORLANDC__)
    if (CryptoProvider::m_hProv == 0)
    {
        // Get handle to the crypto provider
        if (!CryptAcquireContext(&CryptoProvider::m_hProv,
            NULL,
            NULL,
            PROV_RSA_FULL,
            CRYPT_VERIFYCONTEXT))
        {
            dwStatus = GetLastError();
        }

    }
#endif // WIN32
    return (int)dwStatus;
}

void CryptoProvider::destroy() {
#if defined(_MSC_VER) || defined(__BORLANDC__)
    if (CryptoProvider::m_hProv != 0)
    {
        CryptReleaseContext(CryptoProvider::m_hProv, 0);
        CryptoProvider::m_hProv = 0;
    }
#endif // WIN32
}

HCRYPTPROV CryptoProvider::get()
{
    CryptoProvider::init();
    return CryptoProvider::m_hProv;
}

size_t CryptoProvider::getBlockSize()
{
    return CryptoProvider::m_blockSize;
};

size_t CryptoProvider::setBlockSize(size_t newSize)
{
    CryptoProvider::m_blockSize = newSize;
    return CryptoProvider::m_blockSize;
};
