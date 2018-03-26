#ifndef __QA_FILE_HANDLE_FACTORY__
#define __QA_FILE_HANDLE_FACTORY__
#pragma once

#include "IFileHandle.h"

class IFileHandleFactory
{
public:

	virtual IFileHandle* createHandle(std::string file) = 0;

	virtual ~IFileHandleFactory() { }

};

#endif // !__QA_FILE_HANDLE_FACTORY__