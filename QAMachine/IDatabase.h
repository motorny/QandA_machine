#ifndef __QA_DATABASE_INTERFACE__
#define __QA_DATABASE_INTERFACE
#pragma once

#include <string>

class IDatabase
{
public:

	virtual bool select(std::string query) = 0;
	
	virtual bool insert(std::string query) = 0;

	virtual bool del(std::string query) = 0;

	virtual bool update(std::string query) = 0;

	virtual bool droptable(std::string query) = 0;

    virtual ~IDatabase() { }
};

#endif // !__QA_DATABASE_INTERFACE__