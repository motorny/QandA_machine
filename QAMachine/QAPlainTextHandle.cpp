#include "QAPlainTextHandle.h"

//QAPlainTextHandle::QAPlainTextHandle(std::string filename)
//{
//}

//QAPlainTextHandle::QAPlainTextHandle(std::string filename)
//{
//}

QAPlainTextHandle::QAPlainTextHandle(const QAPlainTextHandle & obj)
{
    obj;
}

bool QAPlainTextHandle::read(void)
{
    return false;
}

bool QAPlainTextHandle::close(void)
{
    return false;
}

bool QAPlainTextHandle::open(std::string filename)
{
    return false;
}

//QAPlainTextHandle::~QAPlainTextHandle()
//{
//}


bool QAPlainTextHandle::validate(void)
{
    return false;
}

bool QAPlainTextHandle::batch_validate(size_t batchSize)
{
    return !!batchSize;
}

IFileHandle * QAPlainTextHandleFactory::createHandle(std::string filename)
{
    return new QAPlainTextHandle(filename);
}

//template<class DatabaseQuery>
//QAPlainTextHandle::QAAdapterToDb<DatabaseQuery>::QAAdapterToDb()
//{
//}
//
//template<class DatabaseQuery>
//DatabaseQuery QAPlainTextHandle::convert()
//{
//}
