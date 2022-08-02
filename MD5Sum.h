#pragma once
#if defined(_MSC_VER) || defined(__BORLANDC__)
#define MD5_DIGEST_LENGTH 16
#else // defined(_MSC_VER) || defined(__BORLANDC__)
#include <openssl/md5.h>
#ifndef HCRYPTHASH
#define HCRYPTHASH MD5_CTX
#endif // HCRYPTHASH
#endif // defined(_MSC_VER) || defined(__BORLANDC__)
#include "CheckSum.h"
namespace ifd::crypto::sum {

	class VALIDATIONSUM_API MD5Sum : public CheckSum {
	protected:
		static constexpr const size_t MD5_STR_LEN = MD5_DIGEST_LENGTH * 2;
		HCRYPTHASH m_hHash;
		unsigned char md5_bin[MD5_DIGEST_LENGTH];
		char m_file_md5[MD5_STR_LEN+1];
	public:
		MD5Sum();
		MD5Sum(const MD5Sum& orig) = delete;
		const MD5Sum& operator=(const MD5Sum& orig) = delete;
		virtual ~MD5Sum();
		int initSum();
		int appendSum(const void* data, size_t dataLen);
		int finalizeSum();
		const char* c_str();
		void clear();
		// errno_t computeFileSum(const std::string& fileName);
	};

} // namespace crypto