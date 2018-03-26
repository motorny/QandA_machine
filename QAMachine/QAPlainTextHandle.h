#ifndef __QA_PLAIN_TEXT_HANDLE__
#define __QA_PLAIN_TEXT_HANDLE__
#pragma once

#include "IFileHandle.h"
#include "IFileHandleFactory.h"

class QAPlainTextHandle : public IFileHandle
{
public:

    QAPlainTextHandle(std::string filename) : adapter() {};

    QAPlainTextHandle(const QAPlainTextHandle & obj);

	virtual bool read(void) override;

	virtual bool close(void) override;

	virtual bool open(std::string filename) override;

    ~QAPlainTextHandle() {};

protected:

	template <class DatabaseQuery>
	class QAAdapterToDb : public IAdapter<DatabaseQuery>
	{
    public:
        QAAdapterToDb() {};
        DatabaseQuery convert() override { return DatabaseQuery(); };

        ~QAAdapterToDb() {};
	};
	
	// std::string for now 
	QAAdapterToDb<std::string> adapter;

	virtual bool validate(void) override;

	virtual bool batch_validate(size_t batchSize) override;

};

class QAPlainTextHandleFactory : public IFileHandleFactory
{
public:
    virtual IFileHandle *createHandle(std::string file) override;
};

#endif // !__QA_PLAIN_TEXT_HANDLE__
