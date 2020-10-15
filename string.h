#pragma once

#include <cstdint>
#include <exception>

namespace jovanStd
{
	class exception;
	class string;
}

class jovanStd::exception : public std::exception
{
public:
	exception(const char* exception);
	~exception();
	const char* what() const throw ();
private:
	char* m_exception = NULL;
};

class jovanStd::string
{
public:
	explicit string() = delete;
	explicit string(const string& str) = delete;
	explicit string(const char* str);
	~string();

	string& operator+=(const char* str);
	string& operator+=(char character);
	string& operator-=(int num);
	string& operator+=(int num);
	string& operator+=(string str2);
	const char* operator*() const;

	uint16_t size() const;
	const char* c_str() const;

private:
	char* m_str = NULL;
	uint16_t m_size = 0;
};