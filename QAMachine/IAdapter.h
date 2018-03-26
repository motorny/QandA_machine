#ifndef __QA_ADAPTER_INTERFACE__
#define __QA_ADAPTER_INTERFACE__
#pragma once

template <class Type>
class IAdapter
{
public:
	virtual Type convert(void) = 0;

	virtual ~IAdapter() { }
};

#endif // !__QA_ADAPTER_INTERFACE__
