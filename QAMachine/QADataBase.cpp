#include "QADataBase.h"

QADatabase::QADatabase(std::string username, std::string password, uint16_t flags) : username(username), password(password), flags(flags)
{
}

bool QADatabase::select(std::string query)
{
    return false;
}

bool QADatabase::insert(std::string query)
{
    return false;
}

bool QADatabase::del(std::string query)
{
    return false;
}

bool QADatabase::update(std::string query)
{
    return false;
}

bool QADatabase::droptable(std::string query)
{
    return false;
}

QADatabase::~QADatabase()
{
}
