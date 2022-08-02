#pragma once
#if defined(_MSC_VER) || defined(__BORLANDC__)
#include <wincrypt.h>
#endif

namespace ifd::crypto::sum {
    constexpr size_t    SIZE32K = 32768;
    constexpr size_t    SIZE8K  = 8192;
    constexpr size_t    SIZE4K  = 4096;
    constexpr DWORD     dwZero = 0;
    class CryptoProvider {
        static HCRYPTPROV m_hProv;
        static size_t     m_blockSize;

    public:
        static int init();

        static void destroy();

        static HCRYPTPROV get();

        static size_t getBlockSize();

        static size_t setBlockSize(size_t newSize);
    };
}