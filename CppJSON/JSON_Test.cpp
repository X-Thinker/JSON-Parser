#include "CppJSON.h"

//���Ժ���
void parser_test();
void minify_test();
void array_memberfun_test();
void object_memberfun_test();

//��������
std::string get_content(std::string path);//�����ļ�����ȡ�ļ�����

int main(void)
{
	parser_test();/*�����ļ�����*/
	minify_test();/*JSON�ı�ѹ������*/
	array_memberfun_test();/*�����Ա��������*/
	object_memberfun_test();/*�����Ա��������*/

	return 0;
}

void parser_test()
{
	/*�����ļ����� ��ʼ*/
	//JSON::parser("tests/test1", JSON::file);
	//JSON::parser("tests/test2", JSON::file);
	//JSON::parser("tests/test3", JSON::file);
	//JSON::parser("tests/test4", JSON::file);
	//JSON::parser("tests/test5", JSON::file);
	/*�����ļ����� ����*/
}
void minify_test()
{
	/*JSON�ı�ѹ������(minify) ��ʼ*/
	//std::string content;
	//JSON::minify(content = get_content("tests/test"));
	//JSON::minify(content = get_content("tests/test2"));
	//JSON::minify(content = get_content("tests/test3"));
	//JSON::minify(content = get_content("tests/test4"));
	//JSON::minify(content = get_content("tests/test5"));
	/*JSON�ı�ѹ������(minify) ����*/
}
void array_memberfun_test()
{
	//std::cout << "JSON�����ı����£�" << std::endl;
	//std::shared_ptr<JSON::CppJSON> js = JSON::parser("tests/test6", JSON::file);

	/*�������±��������JSONֵ���� ��ʼ
	std::cout << "����Ϊkeys��ֵΪ��" << std::endl;
	std::cout << &(*js)["keys"] << std::endl;
	std::cout << "keysֵ�ڵ�һ��ֵΪ��" << std::endl;
	std::cout << &(*js)["keys"][0] << std::endl;
	std::cout << "keysֵ�ڵڶ���ֵΪ��" << std::endl;
	std::cout << &(*js)["keys"][1] << std::endl;
	std::cout << "keysֵ�ڵ�����ֵΪ������û�е�����ֵ���Ի��׳��쳣����" << std::endl;
	std::cout << &(*js)["keys"][2] << std::endl;
	�������±��������JSONֵ���� ����*/

	/*�����ڲ�����Ԫ�ز��� ��ʼ
	JSON::CppJSON* null_item = new JSON::CppJSON_NULL;
	std::cout << "��keys����β������һ��ֵΪnull��Ԫ�أ�" << std::endl;
	(*js)["keys"].push_back(null_item);
	std::cout << js << std::endl;
	//
	JSON::CppJSON* string_item = new JSON::CppJSON_String;
	dynamic_cast<JSON::CppJSON_String*>(string_item)->set_valuestring("This is a new item");
	std::cout << "��keys�����λ��0����һ��ֵΪstring��Ԫ�أ�" << std::endl;
	(*js)["keys"].insert(string_item, 0);
	std::cout << js << std::endl;
	//
	std::cout << "��keys�����λ��5����һ��ֵΪstring��Ԫ�أ�Խ���쳣����" << std::endl;
	(*js)["keys"].insert(string_item, 5);
	�����ڲ�����Ԫ�ز��� ����*/

	/*����ɾ��Ԫ�ز��� ��ʼ
	std::cout << "ɾ��keys����λ��1��Ԫ�أ�" << std::endl;
	(*js)["keys"].split(1);
	std::cout << js << std::endl;
	//
	std::cout << "ɾ��keys����λ��0��Ԫ�أ�" << std::endl;
	(*js)["keys"].split(0);
	std::cout << js << std::endl;
	//
	std::cout << "ɾ��keys����λ��0��Ԫ�أ�Խ���쳣����" << std::endl;
	(*js)["keys"].split(0);
	����ɾ��Ԫ�ز��� ����*/
}
void object_memberfun_test()
{
	//std::cout << "JSON�����ı����£�" << std::endl;
	//std::shared_ptr<JSON::CppJSON> js = JSON::parser("tests/test6", JSON::file);

	/*��keyֵ�±���ʶ���JSONֵ���� ��ʼ
	std::cout << "����Ϊkeys��ֵΪ��" << std::endl;
	std::cout << &(*js)["keys"] << std::endl;
	std::cout << "keysֵ������Ϊname1��ֵΪ��" << std::endl;
	std::cout << &(*js)["keys"][0]["name1"] << std::endl;
	std::cout << "keysֵ������Ϊurl1��ֵΪ��" << std::endl;
	std::cout << &(*js)["keys"][0]["url1"] << std::endl;
	std::cout << "keysֵ������Ϊurl0��ֵΪ������û������Ϊurl0��ֵ���Ի��׳��쳣����" << std::endl;
	std::cout << &(*js)["keys"][0]["url0"] << std::endl;
	��keyֵ�±���ʶ���JSONֵ���� ����*/

	/*�����ڲ�����Ԫ�ز��� ��ʼ
	JSON::CppJSON* number_item = new JSON::CppJSON_Number;
	number_item->set_key("new string item");
	dynamic_cast<JSON::CppJSON_Number*>(number_item)->set_valueint(1024);
	std::cout << "��js����β������һ������Ϊnew string item��ֵΪ1024��Ԫ�أ�" << std::endl;
	(*js).push_back(number_item);
	std::cout << js << std::endl;
	//
	JSON::CppJSON* bool_item = new JSON::CppJSON_Bool;
	bool_item->set_key("new bool item");
	dynamic_cast<JSON::CppJSON_Bool*>(bool_item)->set_valuebool(true);
	std::cout << "��js����β������һ������Ϊnew bool item��ֵΪtrue��Ԫ�أ�" << std::endl;
	(*js).push_back(bool_item);
	std::cout << js << std::endl;
	�����ڲ�����Ԫ�ز��� ����*/

	/*����ɾ��Ԫ�ز��� ��ʼ
	std::cout << "ɾ��js������Ϊkeys��Ԫ�أ�" << std::endl;
	(*js).split("keys");
	std::cout << js << std::endl;
	//
	std::cout << "ɾ��js������ΪnooneԪ�أ�Խ���쳣����" << std::endl;
	(*js).split("noone");
	����ɾ��Ԫ�ز��� ����*/
}

std::string get_content(std::string path)
{
	std::stringstream res;
	std::ifstream fin(path);
	if (!fin.is_open())
	{
		std::cout << "�޷����ļ���" << path << std::endl;
		return "open_file_error";
	}
	res << fin.rdbuf();
	fin.close();
	return res.str();
}
