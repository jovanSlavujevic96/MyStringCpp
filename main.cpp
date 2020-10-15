#include "string.h"

#include <iostream>

int main()
{
	jovanStd::string String("1204");
	try 
	{
		String -= 1205;
	}
	catch (jovanStd::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	std::cout << (const char*)("string: %s\n", *String);
	(void)getchar();

	return 0;
}

