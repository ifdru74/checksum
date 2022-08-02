//
// Created by ifdru on 20.06.2022.
//

#ifndef CHECKSUM_FILESUM_H
#define CHECKSUM_FILESUM_H
#include "dll_export.h"
#include "CheckSum.h"
#include <string>
namespace ifd::crypto::sum {
    VALIDATIONSUM_API int  fileSum(ifd::crypto::sum::CheckSum& sum, const TCHAR* fileName);
}

#endif //CHECKSUM_FILESUM_H
