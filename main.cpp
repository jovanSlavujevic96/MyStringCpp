#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <memory.h>
#include <cstdint>

namespace jovanStd
{
	class string;
}

class jovanStd::string
{
public:
	int16_t strlen(const char* str)
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

	string() = delete;

	string(const string& str)
	{
		this->m_str = str.m_str;
		this->m_size = str.m_size;
		this->m_reference = true;
	}

	string(const char* str)
	{
		this->m_size = (uint16_t)strlen(str);
		this->m_str = (char*)malloc(this->m_size);
		if (this->m_str != NULL)
		{
			memcpy(this->m_str, str, this->m_size);
			this->m_str[this->m_size] = '\0';
		}
	}

	~string()
	{
		if (!m_reference)
		{
			free(this->m_str);
		}
	}
	
	static uint8_t getSumOfDigits(uint64_t num)
	{
		return (uint8_t)( (ceil(log10((double)num)) + 1) * sizeof(char) -1);
	}

	static char* getStringOfDigits(int num, uint8_t sumOfDigits)
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
		snprintf(string, tmpSum, "%d", num);
		string[sumOfDigits] = '\0';
		return string;
	}

	string& operator+=(const char* str)
	{
		auto strLen = strlen(str);
		if (-1 == strLen)
		{
			return *this;
		}
		char* cheat = this->m_str;
		this->m_str = (char*)realloc((void*)cheat, this->m_size + strLen);
		if (this->m_str != NULL)
		{
			memcpy(this->m_str+this->m_size, str, strLen);
			this->m_size += strLen;
			m_str[m_size] = '\0';
		}
		else
		{
			this->m_str = cheat;
		}
		return *this;
	}

	string& operator+=(char character)
	{
		m_size++;
		char* cheat = m_str;
		m_str = (char*)realloc((void*)cheat, m_size);
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

	string& operator-=(int num)
	{
		uint64_t strVal = 0;
		uint64_t tmp = 1;
		
		for (int32_t i = m_size-1; i > -1; --i)
		{
			if (m_str[i] >= '0' && m_str[i] <= '9')
			{
				strVal += ((uint64_t)m_str[i] - '0') * tmp;
				tmp *= 10;
			}
			else
			{
				printf("Exception happened :: %c of %s is not a number!\n", m_str[i], m_str);
				exit(-1);
			}
		}

		if ((strVal = strVal - num) < 0)
		{
			printf("Exception happened :: %d is bigger than %s!\n", num, m_str);
			exit(-1);
		}
		tmp = getSumOfDigits((int)strVal);
		char* tmpVar = getStringOfDigits((int)strVal, (uint8_t)tmp);
		if (tmpVar != NULL)
		{
			free(m_str);
			m_str = tmpVar;
			m_size = (uint16_t)tmp;
		}
		return *this;
	}

	string& operator+=(int num) 
	{		
		if (NULL == this->m_str)
		{
			return *this;
		}
		uint8_t allNums = (size_t)getSumOfDigits(num);
		char* cheat = this->m_str;
		this->m_str = (char*)realloc((void*)cheat, (size_t)this->m_size + allNums);
		const char* numStr = getStringOfDigits(num, allNums);
		if (this->m_str != NULL)
		{
			memcpy(this->m_str + this->m_size, numStr, allNums);
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

	string& operator+=(string str2)
	{
		char* cheat = this->m_str;
		this->m_str = (char*)realloc((void*)cheat, (size_t)this->m_size + str2.m_size);
		if (this->m_str != NULL)
		{
			memcpy(this->m_str + this->m_size, str2.m_str, str2.m_size);
			this->m_size += str2.m_size;
		}
		else
		{
			this->m_str = cheat;
		}
		return *this;
	}

	constexpr uint16_t size() const
	{
		return this->m_size;
	}

	constexpr char* c_str() const
	{
		return this->m_str;
	}

private:
	char* m_str = NULL;
	uint16_t m_size = 0;
	bool m_reference = false;
};

int main()
{
	jovanStd::string String("1096");
	String -= 11;
	printf("nase a svetsko: %s\n", String.c_str());

	(void)getchar();

	return 0;
}

