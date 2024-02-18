#ifndef CppJSON_h
#define CppJSON_h

#include <iostream>
#include <sstream>
#include <typeinfo>
#include <fstream>
#include <memory>

namespace JSON
{
	/*----------JSON����----------*/
	//�������CppJSON������ʵ����
	class CppJSON
	{
	public:
		//����ö�٣�����JSON��������
		enum CppJSON_Type { JSON_Initial, JSON_Error, JSON_NULL, JSON_Bool, JSON_Number, JSON_String, JSON_Array, JSON_Object };

		//���캯�����������������캯��ʹ�ó�ʼ���б�,�����������麯��
		CppJSON(CppJSON_Type ini = JSON_Initial, CppJSON* left = nullptr, CppJSON* right = nullptr,
			const std::string& key_name = "name") :type(ini), prev(left), next(right), child(nullptr), key("name") {}
		virtual ~CppJSON() = 0;

		//�޸�JSON���ݽṹ�ڲ���Ա����
		void set_prev(CppJSON* left) { prev = left; }
		void set_next(CppJSON* right) { next = right; }
		void set_key(const std::string& name) { key = name; }
		void set_child(CppJSON* first) { child = first; }

		//����JSON���ݽṹ�ڲ���Ա����
		CppJSON* return_prev() const { return prev; }
		CppJSON* return_next() const { return next; }
		const std::string return_key() const { return key; }
		CppJSON* return_child() const { return child; }
		CppJSON_Type return_type()const { return type; }

		//���麯��������array��object��Ҫ��д
		virtual CppJSON& operator [] (int pos) const;
		virtual CppJSON& operator [] (const std::string key_name) const;
		virtual void push_back(CppJSON* item);
		virtual void insert(CppJSON* item, int pos);
		virtual void split(int pos);
		virtual void split(const std::string& key_name);

	private:
		CppJSON_Type type;
		//ͬһ�ṹ�е�ǰһ��Ԫ�����һ��Ԫ��
		CppJSON* prev, * next, * child;
		std::string key;

		//���ÿ������캯���븳ֵ��������أ���Ϊprivate������ʵ�֣�
		CppJSON(const CppJSON& rhs) {}
		CppJSON& operator = (const CppJSON& rhs) {}
	};
	//�����������Դ����쳣���
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
	//ֵΪnull����������
	class CppJSON_NULL :public CppJSON
	{
	public:
		CppJSON_NULL() :CppJSON(JSON_NULL) {}
		~CppJSON_NULL() {}
	};
	//ֵΪfalse��true����������
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
	//ֵΪ��ֵ����������
	class CppJSON_Number :public CppJSON
	{
	public:
		CppJSON_Number() :CppJSON(JSON_Number), valueint(0), valuedouble(0.0), numbertype(false) {}
		~CppJSON_Number() {}

		//�޸�/��ѯ��ֵ��JSON����ֵ
		void set_valueint(int vi) { valueint = vi; }
		int return_valueint() const { return valueint; }
		void set_valuedouble(double vd) { valuedouble = vd; }
		double return_valuedouble() const { return valuedouble; }
		void set_numbertype(bool nt) { numbertype = nt; }
		bool return_numbertype() const { return numbertype; }

	private:
		int valueint;
		double valuedouble;
		bool numbertype;//��ֵ����Ĭ��Ϊfalse��int�ͣ���Ϊtrue��Ϊdouble��
	};
	//ֵΪ�ַ�������������
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
	//ֵΪ�������������
	class CppJSON_Array :public CppJSON
	{
	public:
		CppJSON_Array() :CppJSON(JSON_Array) {}
		~CppJSON_Array() {}

		//���� [] �������ʹ�������Ϳ���ͨ���±�ֱ�ӷ������ڲ�Ԫ��
		CppJSON& operator [] (int pos) const override;

		void push_back(CppJSON* item) override;
		void insert(CppJSON* item, int pos) override;
		void split(int pos) override;
	};
	//ֵΪ�������������
	class CppJSON_Object :public CppJSON
	{
	public:
		CppJSON_Object() :CppJSON(JSON_Object) {}
		~CppJSON_Object() {}

		//���� [] �����ʹ�������Ϳ���ͨ��keyֱ�ӷ������ڲ�Ԫ��
		CppJSON& operator [] (const std::string key_name) const override;

		void push_back(CppJSON* item) override;
		void split(const std::string& key_name) override;
	};
	/*----------JSON����----------*/



	/*----------����ӿ�----------*/
	//��������
	enum parser_mode { file, text };
	std::shared_ptr<CppJSON> parser(std::string str, parser_mode mode);
	std::shared_ptr<CppJSON> parser(char* str, parser_mode mode);
	//ѹ��json�ı���ɾ���ո񡢿��С�ע�ͣ�
	std::string minify(std::stringstream& message);
	std::string minify(std::string& msg);
	//���� << ������������
	std::ostream& operator << (std::ostream& os, CppJSON* JSON_Print);
	/*----------����ӿ�----------*/
}

#endif
