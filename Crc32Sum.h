#pragma once
#include "CheckSum.h"
#include <cstdint>
#define NULLCRC32 (uint32_t)0xFFFFFFFF

namespace ifd { namespace crypto { namespace sum {

class VALIDATIONSUM_API Crc32Sum : public CheckSum {
	static constexpr const size_t CRC32_STR_LEN = sizeof(uint32_t) * 2;
	uint32_t m_crc32;
	char m_crc32Str[CRC32_STR_LEN + 1];
public:
  Crc32Sum();
  Crc32Sum(const Crc32Sum &orig);
  Crc32Sum& operator=(const Crc32Sum &orig);
  ~Crc32Sum() override;
  int initSum() override;;
  int appendSum(const void *data, size_t dataLen) override;
  int finalizeSum() override { return 0; };
  void clear() override;
  inline uint32_t getCrc32() const { return ~m_crc32;};
  const char* c_str();
};

} } } // namespace crypto