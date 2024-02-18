#ifndef CppJSON_h
#define CppJSON_h

#include <iostream>
#include <sstream>
#include <typeinfo>
#include <fstream>
#include <memory>

namespace JSON
{
	/*----------JSON类型----------*/
	//抽象基类CppJSON，不可实例化
	class CppJSON
	{
	public:
		//类内枚举，定义JSON数据类型
		enum CppJSON_Type { JSON_Initial, JSON_Error, JSON_NULL, JSON_Bool, JSON_Number, JSON_String, JSON_Array, JSON_Object };

		//构造函数与析构函数，构造函数使用初始化列表,析构函数是虚函数
		CppJSON(CppJSON_Type ini = JSON_Initial, CppJSON* left = nullptr, CppJSON* right = nullptr,
			const std::string& key_name = "name") :type(ini), prev(left), next(right), child(nullptr), key("name") {}
		virtual ~CppJSON() = 0;

		//修改JSON数据结构内部成员变量
		void set_prev(CppJSON* left) { prev = left; }
		void set_next(CppJSON* right) { next = right; }
		void set_key(const std::string& name) { key = name; }
		void set_child(CppJSON* first) { child = first; }

		//返回JSON数据结构内部成员变量
		CppJSON* return_prev() const { return prev; }
		CppJSON* return_next() const { return next; }
		const std::string return_key() const { return key; }
		CppJSON* return_child() const { return child; }
		CppJSON_Type return_type()const { return type; }

		//纯虚函数，后续array和object需要覆写
		virtual CppJSON& operator [] (int pos) const;
		virtual CppJSON& operator [] (const std::string key_name) const;
		virtual void push_back(CppJSON* item);
		virtual void insert(CppJSON* item, int pos);
		virtual void split(int pos);
		virtual void split(const std::string& key_name);

	private:
		CppJSON_Type type;
		//同一结构中的前一个元素与后一个元素
		CppJSON* prev, * next, * child;
		std::string key;

		//禁用拷贝构造函数与赋值运算符重载（设为private并不予实现）
		CppJSON(const CppJSON& rhs) {}
		CppJSON& operator = (const CppJSON& rhs) {}
	};
	//错误类型用以处理异常情况
	class CppJSON_Error :public CppJSON
	{
	public:
		enum Error_Type { No_Error, Invalid_Type, Out_Range, Invalid_Key, Invalid_Json_Text, Bad_Allocate, Open_File_Fail, Unknown_Error };
		CppJSON_Error() :CppJSON(JSON_Error), error_type(No_Error), exception() {}
		~CppJSON_Error() {}
		CppJSON& operator [] (int pos);
		CppJSON& operator [] (std::string key_name);
		void throw_exception(Error_Type type);
	private:
		Error_Type error_type;
		std::string exception;
	};
	//值为null的数据类型
	class CppJSON_NULL :public CppJSON
	{
	public:
		CppJSON_NULL() :CppJSON(JSON_NULL) {}
		~CppJSON_NULL() {}
	};
	//值为false或true的数据类型
	class CppJSON_Bool :public CppJSON
	{
	public:
		CppJSON_Bool() :CppJSON(JSON_Bool), valuebool(false) {}
		~CppJSON_Bool() {}
		void set_valuebool(bool vb) { valuebool = vb; }
		bool return_valuebool() const { return valuebool; }
	private:
		bool valuebool;
	};
	//值为数值的数据类型
	class CppJSON_Number :public CppJSON
	{
	public:
		CppJSON_Number() :CppJSON(JSON_Number), valueint(0), valuedouble(0.0), numbertype(false) {}
		~CppJSON_Number() {}

		//修改/查询数值型JSON的数值
		void set_valueint(int vi) { valueint = vi; }
		int return_valueint() const { return valueint; }
		void set_valuedouble(double vd) { valuedouble = vd; }
		double return_valuedouble() const { return valuedouble; }
		void set_numbertype(bool nt) { numbertype = nt; }
		bool return_numbertype() const { return numbertype; }

	private:
		int valueint;
		double valuedouble;
		bool numbertype;//数值类型默认为false即int型，若为true则为double型
	};
	//值为字符串的数据类型
	class CppJSON_String :public CppJSON
	{
	public:

		CppJSON_String() :CppJSON(JSON_String) {}
		~CppJSON_String() {}

		void set_valuestring(const std::string& vs) { valuestring = vs; }
		std::string return_valuestring() const { return valuestring; }

	private:
		std::string valuestring;
	};
	//值为数组的数据类型
	class CppJSON_Array :public CppJSON
	{
	public:
		CppJSON_Array() :CppJSON(JSON_Array) {}
		~CppJSON_Array() {}

		//重载 [] 运算符，使数组类型可以通过下标直接访问其内部元素
		CppJSON& operator [] (int pos) const override;

		void push_back(CppJSON* item) override;
		void insert(CppJSON* item, int pos) override;
		void split(int pos) override;
	};
	//值为对象的数据类型
	class CppJSON_Object :public CppJSON
	{
	public:
		CppJSON_Object() :CppJSON(JSON_Object) {}
		~CppJSON_Object() {}

		//重载 [] 运算符使对象类型可以通过key直接访问其内部元素
		CppJSON& operator [] (const std::string key_name) const override;

		void push_back(CppJSON* item) override;
		void split(const std::string& key_name) override;
	};
	/*----------JSON类型----------*/



	/*----------对外接口----------*/
	//解析函数
	enum parser_mode { file, text };
	std::shared_ptr<CppJSON> parser(std::string str, parser_mode mode);
	std::shared_ptr<CppJSON> parser(char* str, parser_mode mode);
	//压缩json文本（删除空格、空行、注释）
	std::string minify(std::stringstream& message);
	std::string minify(std::string& msg);
	//重载 << 运算符方便输出
	std::ostream& operator << (std::ostream& os, CppJSON* JSON_Print);
	/*----------对外接口----------*/
}

#endif
