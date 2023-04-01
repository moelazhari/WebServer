#include <iostream>
#include <ctime>
#include <string>

int main()
{
	std::time_t now = time(0);
	// struct tm tstruct;
	char *buf;
	buf = std::asctime();
	// tstruct = *localtime(&now);
	// strftime(buf, sizeof(buf), "%a, %d %b %Y %X %Z", &tstruct);
	std::cout << now << std::endl;
}