#include "CppJSON.h"

//测试函数
void parser_test();
void minify_test();
void array_memberfun_test();
void object_memberfun_test();

//辅助函数
std::string get_content(std::string path);//根据文件名获取文件内容

int main(void)
{
	parser_test();/*解析文件测试*/
	minify_test();/*JSON文本压缩测试*/
	array_memberfun_test();/*数组成员函数测试*/
	object_memberfun_test();/*对象成员函数测试*/

	return 0;
}

void parser_test()
{
	/*解析文件测试 开始*/
	//JSON::parser("tests/test1", JSON::file);
	//JSON::parser("tests/test2", JSON::file);
	//JSON::parser("tests/test3", JSON::file);
	//JSON::parser("tests/test4", JSON::file);
	//JSON::parser("tests/test5", JSON::file);
	/*解析文件测试 结束*/
}
void minify_test()
{
	/*JSON文本压缩测试(minify) 开始*/
	//std::string content;
	//JSON::minify(content = get_content("tests/test"));
	//JSON::minify(content = get_content("tests/test2"));
	//JSON::minify(content = get_content("tests/test3"));
	//JSON::minify(content = get_content("tests/test4"));
	//JSON::minify(content = get_content("tests/test5"));
	/*JSON文本压缩测试(minify) 结束*/
}
void array_memberfun_test()
{
	//std::cout << "JSON解析文本如下：" << std::endl;
	//std::shared_ptr<JSON::CppJSON> js = JSON::parser("tests/test6", JSON::file);

	/*用数字下标访问数组JSON值测试 开始
	std::cout << "名称为keys的值为：" << std::endl;
	std::cout << &(*js)["keys"] << std::endl;
	std::cout << "keys值内第一个值为：" << std::endl;
	std::cout << &(*js)["keys"][0] << std::endl;
	std::cout << "keys值内第二个值为：" << std::endl;
	std::cout << &(*js)["keys"][1] << std::endl;
	std::cout << "keys值内第三个值为（由于没有第三个值所以会抛出异常）：" << std::endl;
	std::cout << &(*js)["keys"][2] << std::endl;
	用数字下标访问数组JSON值测试 结束*/

	/*数组内插入新元素测试 开始
	JSON::CppJSON* null_item = new JSON::CppJSON_NULL;
	std::cout << "在keys数组尾部插入一个值为null的元素：" << std::endl;
	(*js)["keys"].push_back(null_item);
	std::cout << js << std::endl;
	//
	JSON::CppJSON* string_item = new JSON::CppJSON_String;
	dynamic_cast<JSON::CppJSON_String*>(string_item)->set_valuestring("This is a new item");
	std::cout << "在keys数组的位置0插入一个值为string的元素：" << std::endl;
	(*js)["keys"].insert(string_item, 0);
	std::cout << js << std::endl;
	//
	std::cout << "在keys数组的位置5插入一个值为string的元素（越界异常）：" << std::endl;
	(*js)["keys"].insert(string_item, 5);
	数组内插入新元素测试 结束*/

	/*数组删除元素测试 开始
	std::cout << "删除keys数组位置1的元素：" << std::endl;
	(*js)["keys"].split(1);
	std::cout << js << std::endl;
	//
	std::cout << "删除keys数组位置0的元素：" << std::endl;
	(*js)["keys"].split(0);
	std::cout << js << std::endl;
	//
	std::cout << "删除keys数组位置0的元素（越界异常）：" << std::endl;
	(*js)["keys"].split(0);
	数组删除元素测试 结束*/
}
void object_memberfun_test()
{
	//std::cout << "JSON解析文本如下：" << std::endl;
	//std::shared_ptr<JSON::CppJSON> js = JSON::parser("tests/test6", JSON::file);

	/*用key值下标访问对象JSON值测试 开始
	std::cout << "名称为keys的值为：" << std::endl;
	std::cout << &(*js)["keys"] << std::endl;
	std::cout << "keys值内名称为name1的值为：" << std::endl;
	std::cout << &(*js)["keys"][0]["name1"] << std::endl;
	std::cout << "keys值内名称为url1的值为：" << std::endl;
	std::cout << &(*js)["keys"][0]["url1"] << std::endl;
	std::cout << "keys值内名称为url0的值为（由于没有名称为url0的值所以会抛出异常）：" << std::endl;
	std::cout << &(*js)["keys"][0]["url0"] << std::endl;
	用key值下标访问对象JSON值测试 结束*/

	/*对象内插入新元素测试 开始
	JSON::CppJSON* number_item = new JSON::CppJSON_Number;
	number_item->set_key("new string item");
	dynamic_cast<JSON::CppJSON_Number*>(number_item)->set_valueint(1024);
	std::cout << "在js对象尾部插入一个名称为new string item的值为1024的元素：" << std::endl;
	(*js).push_back(number_item);
	std::cout << js << std::endl;
	//
	JSON::CppJSON* bool_item = new JSON::CppJSON_Bool;
	bool_item->set_key("new bool item");
	dynamic_cast<JSON::CppJSON_Bool*>(bool_item)->set_valuebool(true);
	std::cout << "在js对象尾部插入一个名称为new bool item的值为true的元素：" << std::endl;
	(*js).push_back(bool_item);
	std::cout << js << std::endl;
	对象内插入新元素测试 结束*/

	/*对象删除元素测试 开始
	std::cout << "删除js中名称为keys的元素：" << std::endl;
	(*js).split("keys");
	std::cout << js << std::endl;
	//
	std::cout << "删除js中名称为noone元素（越界异常）：" << std::endl;
	(*js).split("noone");
	对象删除元素测试 结束*/
}

std::string get_content(std::string path)
{
	std::stringstream res;
	std::ifstream fin(path);
	if (!fin.is_open())
	{
		std::cout << "无法打开文件：" << path << std::endl;
		return "open_file_error";
	}
	res << fin.rdbuf();
	fin.close();
	return res.str();
}
