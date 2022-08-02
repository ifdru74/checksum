#include "pch.h"
#include "CheckSum.h"
#include "CryptoProvider.h"


namespace ifd { namespace crypto { namespace sum
{
	VALIDATIONSUM_API CheckSum::CheckSum() : m_data_size(0)
	{
	}


	VALIDATIONSUM_API CheckSum::~CheckSum()
	{
		m_data_size = -1;
	}

	VALIDATIONSUM_API size_t CheckSum::getBlockSize()
	{ 
		return CryptoProvider::getBlockSize();
	}
	VALIDATIONSUM_API size_t CheckSum::setBlockSize(size_t newSize)
	{ 
		return CryptoProvider::setBlockSize(newSize);
	}

} } }