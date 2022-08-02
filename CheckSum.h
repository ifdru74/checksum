#pragma once
#include "dll_export.h"

namespace ifd::crypto::sum {
	class VALIDATIONSUM_API CheckSum {
	protected:
	  size_t m_data_size;

	public:
	  CheckSum();
	  CheckSum(const CheckSum &orig) = delete;
	  const CheckSum &operator=(const CheckSum &orig) = delete;
	  virtual ~CheckSum();
	  virtual int initSum() = 0;
	  virtual int appendSum(const void *data, size_t dataLen) = 0;
	  virtual int finalizeSum() = 0;
	  virtual void clear() = 0;
	  virtual const char* c_str() = 0;
	  virtual size_t getDataSize() { return m_data_size; };
	  static size_t getBlockSize();
	  static size_t setBlockSize(size_t newSize);
	};

} // namespace crypto