#ifndef _DLL_CRYPTO_SUM_EXPORT_H_
#define _DLL_CRYPTO_SUM_EXPORT_H_
#if defined(_MSC_VER) || defined(__BORLANDC__)
#if defined(VALIDATIONSUM_EXPORTS) || defined (CHECKSUM_EXPORTS)
#define VALIDATIONSUM_API __declspec(dllexport)
#else
#define VALIDATIONSUM_API __declspec(dllimport)
#endif // VALIDATIONSUM_EXPORTS
#else  // defined(_MSC_VER) || defined(__BORLANDC__)
// define empty for non-windows environment
#define VALIDATIONSUM_API
#endif // defined(_MSC_VER) || defined(__BORLANDC__)
#endif // _DLL_CRYPTO_SUM_EXPORT_H_