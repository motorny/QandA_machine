#include "QACsvHandle.h"
#include "QAPlainTextHandle.h"

//QACsvHandle::QACsvHandle(std::string filename) 
//{
//}

bool QACsvHandle::read(void)
{
    return false;
}

bool QACsvHandle::close(void)
{
    return false;
}

bool QACsvHandle::open(std::string filename)
{
    return false;
}

QACsvHandle::~QACsvHandle()
{
}

bool QACsvHandle::validate(void)
{
    return false;
}

bool QACsvHandle::batch_validate(size_t batchSize)
{
    return !!batchSize;
}

IFileHandle * QACsvHandleFactory::createHandle(std::string file)
{
    return new QACsvHandle(file);
}

template<class DatabaseQuery>
inline DatabaseQuery QACsvHandle::QAAdapterToDb<DatabaseQuery>::convert()
{
    return DatabaseQuery();
}

template<class DatabaseQuery>
inline QACsvHandle::QAAdapterToDb<DatabaseQuery>::~QAAdapterToDb()
{
}
