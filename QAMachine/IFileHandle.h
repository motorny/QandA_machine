#ifndef __QAFILE_HANDLE_INTERFACE__
#define __QAFILE_HANDLE_INTERFACE__
#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <array>

#include "IAdapter.h"

class IFileHandle
{
public:
	
	virtual bool open(std::string filename) = 0;

	virtual bool close(void) = 0;

	virtual bool read(void) = 0;

	virtual ~IFileHandle() { }

protected:

	virtual bool validate(void) = 0;

	virtual bool batch_validate(size_t batchSize) = 0;
};

#endif // __QAFILE_INTERFACE__

