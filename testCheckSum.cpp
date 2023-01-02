#include "pch.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <string>
//#if defined(_MSC_VER) || defined(__BORLANDC__)
//#include <windows.h>
//#include <wincrypt.h>
//#endif
#include "CheckSum.h"
#include "MD5Sum.h"
#include "Crc32Sum.h"
#include "fileSum.h"

constexpr const char* szTestString = "Bush hid the facts";
int test1Mem()
{
	ifd::crypto::sum::Crc32Sum sum32;
	ifd::crypto::sum::MD5Sum sum5;
	sum32.initSum();
	sum32.appendSum(szTestString, strlen(szTestString));
	std::cout << "CRC32:" << std::hex << std::setw(8) << sum32.getCrc32() << std::endl;
	sum5.initSum();
	sum5.appendSum(szTestString, strlen(szTestString));
	sum5.finalizeSum();
	std::cout << "MD5:" << sum5.c_str() << std::endl;
	return EXIT_SUCCESS;
}

int main(int argc, char* argv[])
{
	if (test1Mem() != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}