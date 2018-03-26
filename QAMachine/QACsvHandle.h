#ifndef __QA_CSV_HANDLE__
#define __QA_CSV_HANDLE__
#pragma once

#include "IFileHandle.h"
#include "IFileHandleFactory.h"

class QACsvHandle : public IFileHandle
{
public:
    QACsvHandle():adapter() {};
    QACsvHandle(std::string filename) :adapter(){};
    //QACsvHandle(const QACsvHandle &obj) { ret};

	virtual bool read(void) override;

	virtual bool close(void) override;

	virtual bool open(std::string filename);

	virtual ~QACsvHandle();

protected:
	
	template <class DatabaseQuery>
	class QAAdapterToDb : public IAdapter<DatabaseQuery>
	{
    public:
        QAAdapterToDb() {};
        DatabaseQuery convert() override;
         
        virtual ~QAAdapterToDb();
	};

	// std::string for now
	QAAdapterToDb<std::string> adapter;

	virtual bool validate(void) override;

	virtual bool batch_validate(size_t batchSize) override;

};

class QACsvHandleFactory : public IFileHandleFactory
{
public:
    virtual IFileHandle *createHandle(std::string file);
};

#endif // !__QA_CSV_HANDLE__
