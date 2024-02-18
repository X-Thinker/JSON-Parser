#include "CppJSON.h"

namespace JSON
{
	//全局异常
	CppJSON_Error* error = new CppJSON_Error;

	/*----------类成员函数模块----------*/
	CppJSON::~CppJSON() {}
	CppJSON& CppJSON::operator [] (int pos) const { error->throw_exception(CppJSON_Error::Invalid_Type); return *error; }
	CppJSON& CppJSON::operator [] (const std::string key_name) const { error->throw_exception(CppJSON_Error::Invalid_Type); return *error; }
	void CppJSON::push_back(CppJSON* item) { error->throw_exception(CppJSON_Error::Invalid_Type); }
	void CppJSON::insert(CppJSON* item, int pos) { error->throw_exception(CppJSON_Error::Invalid_Type); }
	void CppJSON::split(int pos) { error->throw_exception(CppJSON_Error::Invalid_Type); }
	void CppJSON::split(const std::string& key_name) { error->throw_exception(CppJSON_Error::Invalid_Type); }


	//数组通过下标访问内部元素
	CppJSON& CppJSON_Array::operator [] (int pos) const
	{
		CppJSON* location = this->return_child();
		while (location != nullptr && pos > 0)
			location = location->return_next(), --pos;
		//越界异常，返回错误类型
		if (pos != 0 || location == nullptr)
		{
			error->throw_exception(CppJSON_Error::Out_Range);
			return *error;
		}
		return *location;
	}
	//对象通过关键字访问内部元素
	CppJSON& CppJSON_Object::operator [] (const std::string key_name) const
	{
		CppJSON* location = this->return_child();
		while (location != nullptr && key_name != location->return_key())
			location = location->return_next();
		//找不到关键字，返回错误类型
		if (location == nullptr)
		{
			error->throw_exception(CppJSON_Error::Invalid_Key);
			return *error;
		}
		return *location;
	}

	//在数组尾部加入新元素
	void CppJSON_Array::push_back(CppJSON* item)
	{
		CppJSON* preloc = this->return_child(), * loc = this->return_child();
		//空数组
		if (loc == nullptr) { this->set_child(item); return; }
		//非空数组
		while (loc != nullptr)
			preloc = loc, loc = loc->return_next();
		preloc->set_next(item);
		item->set_prev(preloc);
		return;
	}
	//在对象尾部加入新元素
	void CppJSON_Object::push_back(CppJSON* item)
	{
		CppJSON* preloc = this->return_child(), * loc = this->return_child();
		//空对象
		if (loc == nullptr) { this->set_child(item); return; }
		//非空对象
		while (loc != nullptr)
			preloc = loc, loc = loc->return_next();
		preloc->set_next(item);
		item->set_prev(preloc);
		return;
	}

	//在数组指定位置插入新元素
	void CppJSON_Array::insert(CppJSON* item, int pos)
	{
		//在头部插入
		if (pos == 0)
		{
			item->set_next(this->return_child());
			if (this->return_child() != nullptr)
				this->return_child()->set_prev(item);
			this->set_child(item);
			return;
		}
		CppJSON* prev_loc = &(*this)[pos - 1];
		//如果上述过程抛出异常直接退出
		if (typeid(*error) == typeid(*prev_loc))
			return;
		//如果pos-1的位置为队尾则退化成push_back
		if (prev_loc->return_next() != nullptr)
		{
			CppJSON* next_loc = prev_loc->return_next();
			prev_loc->set_next(item), item->set_prev(prev_loc);
			item->set_next(next_loc), next_loc->set_prev(item);
		}
		else
			prev_loc->set_next(item), item->set_prev(prev_loc);
		return;
	}

	//删除指定数组元素
	void CppJSON_Array::split(int pos)
	{
		CppJSON* detath_item = &(*this)[pos];
		if (typeid(*error) == typeid(*detath_item))
			return;
		//删除首元素
		if (pos == 0)
		{
			this->set_child(detath_item->return_next());
			if (detath_item->return_next() != nullptr)
				detath_item->return_next()->set_prev(nullptr);
			detath_item->set_next(nullptr);
			delete detath_item;
			return;
		}
		//非首元素
		detath_item->return_prev()->set_next(detath_item->return_next());
		if (detath_item->return_next() != nullptr)
			detath_item->return_next()->set_prev(detath_item->return_prev());
		detath_item->set_next(nullptr), detath_item->set_prev(nullptr);
		delete detath_item;
		return;
	}
	//删除指定对象元素
	void CppJSON_Object::split(const std::string& key_name)
	{
		CppJSON* detath_item = &(*this)[key_name];
		if (typeid(*error) == typeid(*detath_item))
			return;
		//删除首元素
		if (this->return_child() == detath_item)
		{
			this->set_child(detath_item->return_next());
			if (detath_item->return_next() != nullptr)
				detath_item->return_next()->set_prev(nullptr);
			detath_item->set_next(nullptr);
			delete detath_item;
			return;
		}
		//非首元素
		detath_item->return_prev()->set_next(detath_item->return_next());
		if (detath_item->return_next() != nullptr)
			detath_item->return_next()->set_prev(detath_item->return_prev());
		detath_item->set_next(nullptr), detath_item->set_prev(nullptr);
		delete detath_item;
		return;
	}
	/*----------类成员函数模块----------*/



	/*----------异常模块----------*/
	//对不同错误类型抛出不同异常
	void CppJSON_Error::throw_exception(Error_Type type)
	{
		switch (type)
		{
		case Invalid_Type: exception = "This procedure triggers an error \"Invalid type\""; break;
		case Out_Range: exception = "This procedure triggers an error \"Subscript out of range\""; break;
		case Invalid_Key: exception = "This procedure triggers an error \"Invalid key\""; break;
		case Invalid_Json_Text: exception = "This procedure triggers an error \"Invalid json texts\""; break;
		case Bad_Allocate: exception = "This procedure triggers an error \"Bad allocated\""; break;
		case Open_File_Fail: exception = "This procedure triggers an error \"Fail to open the file\""; break;
		default: exception = "This procedure triggers an unknown error"; break;
		}
		error_type = type;
		std::cout << exception << std::endl;
		return;
	}
	//错误类型的[]运算符重载，处理后续数组和对象在进行连续的[]访问中抛出的异常
	CppJSON& CppJSON_Error::operator [] (int pos) { throw_exception(Invalid_Type); return *error; }
	CppJSON& CppJSON_Error::operator [] (std::string key_name) { throw_exception(Invalid_Type); return *error; }
	//内存分配失败抛出异常
	CppJSON* bad_allocated() { error->throw_exception(CppJSON_Error::Bad_Allocate); return error; }
	//无效的Json文本抛出异常
	CppJSON* invalid_json_text(std::stringstream& message) 
	{
		error->throw_exception(CppJSON_Error::Invalid_Json_Text); 
		std::string fail_pos;
		getline(message, fail_pos);
		fail_pos += "(...omit...)";
		//把解析失败的行内容输出，方便用户检查json文本错误
		std::cout << "Parsing failed: " << fail_pos << std::endl;
		return error;
	}
	/*----------异常模块----------*/



	/*---------功能函数模块---------*/
	//删除整个json结构
	void delete_json(CppJSON* detach_json)
	{
		CppJSON* next = detach_json;
		while (detach_json)
		{
			next = detach_json->return_next();
			if (detach_json->return_child() != nullptr)
				delete_json(detach_json->return_child());
			delete detach_json;
			detach_json = next;
		}
		return;
	}
	//压缩json文本，去除空白格与格式
	std::string minify(std::stringstream& message) 
	{
		std::string msg = message.str(); 
		return minify(msg);
	}
	std::string minify(std::string& msg)
	{
		int point_write = 0, point_read = 0;
		while (msg[point_read] != '\0')
		{
			switch (msg[point_read])
			{
			case ' ': ++point_read; break;
			case '\n': ++point_read; break;
			case '\r': ++point_read; break;
			case '\t': ++point_read; break;//跳过空白格
			case '\"':
				msg[point_write++] = msg[point_read++];
				while (msg[point_read] != '\0' && msg[point_read] != '\"')
					msg[point_write++] = msg[point_read++];
				msg[point_write++] = msg[point_read++];
				break;
			default: msg[point_write++] = msg[point_read++]; break;
			}
		}
		msg[point_write] = '\0';
		std::string res(msg, 0, ++point_write);
		std::cout << res << std::endl;
		return res;
	}
	//跳过空白格
	std::stringstream& skip_whitespace(std::stringstream& message) { while (message.peek() > 0 && message.peek() <= 32) message.ignore(); return message; }
	//获取一个元素的key值
	bool get_keyname(std::string& kn, std::stringstream& message)
	{
		if (message.peek() != '\"')
			return false;
		message.ignore();
		kn.clear();
		getline(message, kn, '\"');
		if (kn.size())
			return true;
		else
			return false;
	}
	/*---------功能函数模块---------*/



	/*----------解析模块----------*/
	//前置声明
	CppJSON* parse_object(std::stringstream& message);
	//以string参数进行解析
	std::shared_ptr<CppJSON> parser(std::string path, parser_mode mode)
	{
		std::stringstream json_text;
		if (mode == file)
		{
			std::ifstream fin(path);
			//文件打开失败抛出异常
			if (!fin.is_open())
			{
				error->throw_exception(CppJSON_Error::Open_File_Fail);
				return std::shared_ptr<CppJSON>(error);
			}
			//将fin流中内容输入到json_text
			json_text << fin.rdbuf();
			fin.close();
		}
		else if (mode == text)
			json_text << path;
		else//如果解析模式错误则会抛出未知错误
		{
			error->throw_exception(CppJSON_Error::Unknown_Error);
			return std::shared_ptr<CppJSON>(error);
		}
		CppJSON* res = parse_object(skip_whitespace(json_text));
		//在json文本后有除终止符外的其他非空白字符
		if (skip_whitespace(json_text).peek() != -1)
		{
			invalid_json_text(json_text);
			return std::shared_ptr<CppJSON>(error);
		}
		if (typeid(*res) == typeid(*error)) 
			return std::shared_ptr<CppJSON>(error);
		std::shared_ptr<CppJSON> ptr(res, delete_json);
		std::cout << ptr.get() << std::endl;
		return ptr;
	}
	//以char*参数进行解析，兼容C
	std::shared_ptr<CppJSON> parser(char* path, parser_mode mode)
	{
		//把char*的内容导入string后用parser的string重载完成解析
		std::string ps(path);
		return parser(ps, mode);
	}

	//解析函数
	//前置声明
	CppJSON* parse_null(std::stringstream& message);
	CppJSON* parse_bool(std::stringstream& message);
	CppJSON* parse_string(std::stringstream& message);
	CppJSON* parse_number(std::stringstream& message);
	CppJSON* parse_array(std::stringstream& message);
	CppJSON* parse_object(std::stringstream& message);

	CppJSON* parse_value(std::stringstream& message)
	{
		char ch_mes = message.peek();
		if (ch_mes == 'n')
			return parse_null(message);
		else if (ch_mes == 'f' || ch_mes == 't')
			return parse_bool(message);
		else if (ch_mes == '\"')
			return parse_string(message);
		else if (ch_mes == '-' || ch_mes == '+' || isdigit(ch_mes))
			return parse_number(message);
		else if (ch_mes == '[')
			return parse_array(message);
		else if (ch_mes == '{')
			return parse_object(message);
		else//如果出现错误情况，抛出无效Json文本异常
			return invalid_json_text(message);
	}
	CppJSON* parse_null(std::stringstream& message)
	{
		//检查是否为有效的null值
		if (message.peek() != 'n')
			return invalid_json_text(message);
		CppJSON_NULL* item_null = new CppJSON_NULL;
		//分配失败抛出异常
		if (item_null == nullptr)
			return bad_allocated();
		message.ignore(4);//null四个字符
		return item_null;
	}
	CppJSON* parse_bool(std::stringstream& message)
	{
		char ch = message.peek();
		if (ch != 'f' && ch != 't')
			return invalid_json_text(message);
		CppJSON_Bool* item_bool = new CppJSON_Bool;
		if (item_bool == nullptr)
			return bad_allocated();
		//设置bool的类型
		if (ch == 'f') item_bool->set_valuebool(false), message.ignore(5);
		else item_bool->set_valuebool(true), message.ignore(4);
		return item_bool;
	}
	CppJSON* parse_string(std::stringstream& message)
	{
		if (message.peek() != '\"')
			return invalid_json_text(message);
		CppJSON_String* item_string = new CppJSON_String;
		if (item_string == nullptr)
			return bad_allocated();
		std::string vs;
		message.ignore();
		//以"为分割符,将string值抽出
		getline(message, vs, '\"');
		item_string->set_valuestring(vs);
		return item_string;
	}
	CppJSON* parse_number(std::stringstream& message)
	{
		char ch_mes = message.peek();
		if (ch_mes != '-' && ch_mes != '+' && !isdigit(ch_mes))
			return invalid_json_text(message);
		std::string num_string;
		bool num_type = false;
		//值为number的所有可能出现的字符
		while (ch_mes == '-' || ch_mes == '+' || ch_mes == 'e' || ch_mes == 'E' || ch_mes == '.' || isdigit(ch_mes))
			num_string.push_back(message.get()), ch_mes = message.peek(), num_type = (ch_mes == '.' || ch_mes == 'e' || ch_mes == 'E') ? true : false;
		CppJSON_Number* item_number = new CppJSON_Number;
		if (item_number == nullptr)
			return bad_allocated();
		//根据数字中是否出现小数点或者科学计数法来判断数值为double或int
		item_number->set_numbertype(num_type);
		if (num_type)
			item_number->set_valuedouble(std::stod(num_string));
		else
			item_number->set_valueint(std::stoi(num_string));
		return item_number;
	}
	CppJSON* parse_array(std::stringstream& message)
	{
		if (message.peek() != '[')
			return invalid_json_text(message);
		message.ignore();
		CppJSON_Array* item_array = new CppJSON_Array;
		if (item_array == nullptr)
			return bad_allocated();
		CppJSON* item_child = parse_value(skip_whitespace(message));
		//解析失败抛出异常
		if (typeid(*item_child) == typeid(*error))
			return error;
		//连接子结点
		item_array->set_child(item_child);

		CppJSON* item_otherchild = nullptr;
		while (skip_whitespace(message).peek() == ',')
		{
			message.ignore();
			item_otherchild = parse_value(skip_whitespace(message));
			if (typeid(*item_otherchild) == typeid(*error))
				return error;
			//连接各子结点
			item_child->set_next(item_otherchild), item_otherchild->set_prev(item_child);
			item_child = item_otherchild;
		}

		if (message.peek() != ']')
			return invalid_json_text(message);
		message.ignore();
		return item_array;
	}
	CppJSON* parse_object(std::stringstream& message)
	{
		if (message.peek() != '{')
			return invalid_json_text(message);
		message.ignore();
		CppJSON* item_object = new CppJSON_Object;
		if (item_object == nullptr)
			return bad_allocated();
		//对象中为key-value键值对，所以首先应该出现key或者 }（空的对象）
		if (skip_whitespace(message).peek() == '}')
			return item_object;
		if (message.peek() != '\"')
			return invalid_json_text(message);

		//message.ignore();
		std::string item_keyname;
		//key值解析失败
		if (!get_keyname(item_keyname, message))
			return invalid_json_text(message);
		if (skip_whitespace(message).peek() != ':')
			return invalid_json_text(message);

		message.ignore();
		CppJSON* item_child = parse_value(skip_whitespace(message));
		if (typeid(*item_child) == typeid(*error))
			return error;
		item_child->set_key(item_keyname);
		item_object->set_child(item_child);

		CppJSON* item_otherchild = nullptr;
		while (skip_whitespace(message).peek() == ',')
		{
			message.ignore(), skip_whitespace(message);
			if (!get_keyname(item_keyname, message))
				return invalid_json_text(message);
			if (skip_whitespace(message).peek() != ':')
				return invalid_json_text(message);
			message.ignore();
			item_otherchild = parse_value(skip_whitespace(message));
			if (typeid(*item_otherchild) == typeid(*error))
				return error;
			item_otherchild->set_key(item_keyname);
			item_child->set_next(item_otherchild), item_otherchild->set_prev(item_child);
			item_child = item_otherchild;
		}

		if (message.peek() != '}')
			return invalid_json_text(message);
		message.ignore();
		return item_object;
	}
	/*----------解析模块----------*/



	/*----------输出模块----------*/
	//静态全局变量deep用来反映输出时的递归深度以格式化输出
	static int print_deep = 0;
	//输出函数
	std::ostream& print_bool(std::ostream& os, CppJSON_Bool* pb) { pb->return_valuebool() ? os << "true" : os << "false"; return os; }
	std::ostream& print_null(std::ostream& os, CppJSON_NULL* pn) { os << "null"; return os; }
	std::ostream& print_string(std::ostream& os, CppJSON_String* ps) { os << '\"' << ps->return_valuestring() << '\"'; return os; }
	std::ostream& print_number(std::ostream& os, CppJSON_Number* pn) { pn->return_numbertype() ? os << pn->return_valuedouble() : os << pn->return_valueint(); return os; }
	std::ostream& print_array(std::ostream& os, CppJSON_Array* pa)
	{
		os << '[';
		CppJSON* pa_child = pa->return_child();
		while (pa_child != nullptr)
		{
			os << pa_child;
			pa_child = pa_child->return_next();
			if (pa_child != nullptr)
				os << ", ";
		}
		os << ']';
		return os;
	}
	std::ostream& print_object(std::ostream& os, CppJSON_Object* po)
	{
		++print_deep, os << '{';
		CppJSON* po_child = po->return_child();
		if (po_child != nullptr) os << '\n';
		while (po_child != nullptr)
		{
			for (int i = 1; i <= print_deep; i++)
				os << '\t';
			os << '\"' << po_child->return_key() << "\":\t";
			os << po_child;
			po_child = po_child->return_next();
			if (po_child != nullptr)
				os << ',';
			os << '\n';
		}
		for (int i = 1; i <= print_deep - 1; i++) os << '\t';
		--print_deep, os << '}';
		return os;
	}
	std::ostream& operator << (std::ostream& os, CppJSON* JSON_Print)
	{
		switch (JSON_Print->return_type())
		{
		case CppJSON::JSON_Bool: return print_bool(os, dynamic_cast<CppJSON_Bool*>(JSON_Print)); break;
		case CppJSON::JSON_NULL:return print_null(os, dynamic_cast<CppJSON_NULL*>(JSON_Print)); break;
		case CppJSON::JSON_String: return print_string(os, dynamic_cast<CppJSON_String*>(JSON_Print)); break;
		case CppJSON::JSON_Number: return print_number(os, dynamic_cast<CppJSON_Number*>(JSON_Print)); break;
		case CppJSON::JSON_Array: return print_array(os, dynamic_cast<CppJSON_Array*>(JSON_Print)); break;
		case CppJSON::JSON_Object: return print_object(os, dynamic_cast<CppJSON_Object*>(JSON_Print)); break;
		default: error->throw_exception(CppJSON_Error::Invalid_Type); return os; break;
		}
	}
	/*----------输出模块----------*/
}