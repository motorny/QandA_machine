#ifndef __QA_DATABASE__
#define __QA_DATABASE__
#pragma once

#include "IDatabase.h"

class QADatabase : public IDatabase
{
public:
    
    QADatabase(std::string username, std::string password, uint16_t flags=0);

	virtual bool select(std::string query) override;

	virtual bool insert(std::string query) override;

	virtual bool del(std::string query) override;

    virtual bool update(std::string query) override;

	virtual bool droptable(std::string query) override;

	~QADatabase();

private:

    std::string username;
    std::string password;
    uint16_t flags;
};

#endif // !__QA_DATABASE__
