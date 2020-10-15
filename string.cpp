#include "string.h"

#include <stdio.h> 
#include <stdlib.h>	// malloc/realloc/free
#include <math.h>	// ceil, log10
#include <memory.h> //memcpy

#include <memory> //smart pointers

namespace
{
	class stringFactory
	{
	public:
		static int16_t strlen(const char* str);
		static uint8_t getSumOfDigits(uint64_t num);
		static char* getStringOfDigits(int num, uint8_t sumOfDigits);
	};
}

int16_t stringFactory::strlen(const char* str)
{
	if (NULL == str)
	{
		return -1;
	}
	int8_t index = 0;
	while (str[index] != '\0')
	{
		index++;
	}
	return index;
}

uint8_t stringFactory::getSumOfDigits(uint64_t num)
{
	return (uint8_t)((ceil(log10((double)num)) + 1) * sizeof(char) - 1);
}

char* stringFactory::getStringOfDigits(int num, uint8_t sumOfDigits)
{
	static uint8_t tmpSum = 0;
	if (0 == sumOfDigits)
	{
		return NULL;
	}
	tmpSum = sumOfDigits + 1;
	char* string = new char[tmpSum];
	if (NULL == string)
	{
		return NULL;
	}
	snprintf(string, (size_t)tmpSum, "%d", num);
	string[sumOfDigits] = '\0';
	return string;
}

/* --exception-- */

jovanStd::exception::exception(const char* exception)
{
	int16_t exceptionLen = ::stringFactory::strlen(exception);
	this->m_exception = (char*)malloc((size_t)exceptionLen);
	if (this->m_exception != NULL)
	{
		memcpy((void*)this->m_exception, (void*)exception, (size_t)exceptionLen);
		this->m_exception[(size_t)exceptionLen] = '\0';
	}
}

jovanStd::exception::~exception()
{
	if (this->m_exception != NULL)
	{
		free((void*)this->m_exception);
	}
}

const char* jovanStd::exception::what() const throw ()
{
	return this->m_exception;
}

/* --string-- */

jovanStd::string::string(const char* str)
{
	this->m_size = (uint16_t)::stringFactory::strlen(str);
	this->m_str = (char*)malloc((size_t)this->m_size);
	if (this->m_str != NULL)
	{
		memcpy(this->m_str, str, this->m_size);
		this->m_str[this->m_size] = '\0';
	}
}

jovanStd::string::~string()
{
	free((void*)this->m_str);
}

jovanStd::string& jovanStd::string::operator+=(const char* str)
{
	auto strLen = ::stringFactory::strlen(str);
	if (-1 == strLen)
	{
		return *this;
	}
	char* cheat = this->m_str;
	this->m_str = (char*)realloc((void*)cheat, (size_t)this->m_size + strLen);
	if (this->m_str != NULL)
	{
		memcpy((void*)(this->m_str + this->m_size), (void*)str, (size_t)strLen);
		this->m_size += (uint16_t)strLen;
		m_str[m_size] = '\0';
	}
	else
	{
		this->m_str = cheat;
	}
	return *this;
}

jovanStd::string& jovanStd::string::operator+=(char character)
{
	m_size++;
	char* cheat = m_str;
	m_str = (char*)realloc((void*)cheat, (size_t)m_size);
	if (this->m_str != NULL)
	{
		m_str[m_size - 1] = character;
		m_str[m_size] = '\0';
	}
	else
	{
		this->m_str = cheat;
	}
	return *this;
}

jovanStd::string& jovanStd::string::operator-=(int num)
{
	int64_t strVal = 0;
	uint32_t tmp = 1;

	for (int32_t i = m_size - 1; i > -1; --i)
	{
		if (m_str[i] >= '0' && m_str[i] <= '9')
		{
			strVal += ((int64_t)m_str[i] - '0') * tmp;
			tmp *= 10;
		}
		else
		{
			throw jovanStd::exception("Exception happened :: Can't do subtraction because this string is not a number!");
		}
	}

	if ((strVal = strVal - num) < 0)
	{
		throw jovanStd::exception("Exception happened :: The minuend is smaller than subtrahend! String has left unchanged!");
	}
	tmp = ::stringFactory::getSumOfDigits((int)strVal);
	char* tmpVar = ::stringFactory::getStringOfDigits((int)strVal, (uint8_t)tmp);
	if (tmpVar != NULL)
	{
		free((void*)m_str);
		m_str = tmpVar;
		m_size = (uint16_t)tmp;
	}
	return *this;
}

jovanStd::string& jovanStd::string::operator+=(int num)
{
	if (NULL == this->m_str)
	{
		return *this;
	}
	uint8_t allNums = (size_t)::stringFactory::getSumOfDigits(num);
	char* cheat = this->m_str;
	this->m_str = (char*)realloc((void*)cheat, (size_t)this->m_size + allNums);
	const char* numStr = ::stringFactory::getStringOfDigits(num, allNums);
	if (this->m_str != NULL)
	{
		memcpy((void*)(this->m_str + this->m_size), (void*)numStr, (size_t)allNums);
		this->m_size += allNums;
		this->m_str[this->m_size] = '\0';
	}
	else
	{
		this->m_str = cheat;
	}
	if (numStr != NULL)
	{
		delete[] numStr;
	}
	return *this;
}

jovanStd::string& jovanStd::string::operator+=(string str2)
{
	char* cheat = this->m_str;
	this->m_str = (char*)realloc((void*)cheat, (size_t)this->m_size + str2.m_size);
	if (this->m_str != NULL)
	{
		memcpy((void*)(this->m_str + this->m_size), (void*)str2.m_str, (size_t)str2.m_size);
		this->m_size += str2.m_size;
		this->m_str[this->m_size] = '\0';
	}
	else
	{
		this->m_str = cheat;
	}
	return *this;
}

const char* jovanStd::string::operator*() const
{
	return this->m_str;
}

uint16_t jovanStd::string::size() const
{
	return this->m_size;
}

const char* jovanStd::string::c_str() const
{
	return this->m_str;
}