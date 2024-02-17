#include "CppJSON.h"
int main(void)
{
	JSON::parser("tests/test111.txt", JSON::file);
	/*std::stringstream buf;
	std::ifstream filein("tests/test111.txt");
	if (filein.is_open())
		std::cout << "success" << std::endl;
	buf << filein.rdbuf();
	std::string res = JSON::minify(buf);
	std::cout << res << std::endl;*/
	return 0;
}