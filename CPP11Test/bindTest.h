#pragma once

//带有引用参数的普通函数
void display(int first, int &second)
{
	std::cout << "first: " << first << " second:" << second << std::endl;
}
//普通函数
int get_number(int number)
{
	return number;
}
class Test
{
public:
	Test(int num) : num_(num)
	{ }
	//静态成员函数
	static void say_hello()
	{
		std::cout << "hello" << std::endl;
	}
	//成员函数
	void print_add(int value)
	{
		std::cout << "add:" << value + num_ << std::endl;
	}
public:
	int num_;
};

struct Polly
{
	template<typename T, typename U>
	auto operator()(T t, U u) const -> decltype(t + u)
	{
		return t + u;
	}
};


int add1(int i, int j, int k) {
	return i + j + k;
}
class Utils {
public:
	Utils(const char* name) {
		strcpy(_name, name);
	}

	void sayHello(const char* name) const {
		std::cout << _name << " say: hello " << name << std::endl;
	}

	static int getId() {
		return 10001;
	}

	int operator()(int i, int j, int k) const {
		return i + j + k;
	}

private:
	char _name[32];
};



void sayHello() {
	std::cout << "Hello world !" << std::endl;
}
int sum(int i, int j, int k) {
	return i + j + k;
}

template <typename T>
class Func {
public:

	Func(T fun) {
		if (!fun) {
			throw "fun nullptr";
		}
		_fun = fun;
	}

	template<typename R, typename A1, typename A2, typename A3, typename A4, typename A5>
	R Call(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) {
		return _fun(a1, a2, a3, a4, a5);
	}

	template<typename R, typename A1, typename A2, typename A3, typename A4>
	R Call(A1 a1, A2 a2, A3 a3, A4 a4) {
		return _fun(a1, a2, a3, a4);
	}

	template<typename R, typename A1, typename A2, typename A3>
	R Call(A1 a1, A2 a2, A3 a3) {
		return _fun(a1, a2, a3);
	}

	template<typename R, typename A1, typename A2>
	R Call(A1 a1, A2 a2) {
		return _fun(a1, a2);
	}

	template<typename R, typename A1>
	R Call(A1 a1) {
		return _fun(a1);
	}

	template<typename R>
	R Call() {
		return _fun();
	}

	void Call() {
		_fun();
	}

private:
	T _fun;
};

template<typename R = void, typename... Args>
class Fn {
public:
	Fn(std::function<R(Args...)> fun) : _fun(fun) {
	}

	R operator()(Args... args) {
		return _fun(args...);
	}
private:
	std::function<R(Args...) > _fun;
};



template<typename... Args>
class Fns
{
private:

	std::list<std::function<void(Args...)> > _calls;

public:

	virtual ~Fns()
	{
		_calls.clear();
	}

	void connect(std::function<void(Args...)> fct)
	{
		_calls.push_back(fct);
	}

	template<typename Object>
	void connect(Object* object, void (Object::*method)(Args...))
	{
		_calls.push_back([object, method](Args... args){(*object.*method)(args...); });
	}

	template<typename Object>
	void connect(Object* object, void (Object::*method)(Args...) const)
	{
		_calls.push_back([object, method](Args... args){(*object.*method)(args...); });
	}

	template<typename Object>
	void connect(const Object* object, void (Object::*method)(Args...) const)
	{
		_calls.push_back([object, method](Args... args){(*object.*method)(args...); });
	}

	void emit(Args... args)
	{
		for (auto call : _calls)
			call(args...);
	}
};
class Foo
{
public:

	void bar(int x, int y)
	{
		printf("Foo::bar(%d, %d)\n", x, y);
	}
};

void foobar(int x, int y)
{
	printf("foobar(%d, %d)\n", x, y);
}

struct int_div {        // 构造一个可以使用"()"进行调用的函数对象类型  
	float operator() (int x, int y) const
	{
		return ((float)x) / y;
	}
	int int_div_fun(int x)
	{
		return x;
	}
};
typedef std::function<int(int_div*, int)> f_2;


template <class T>
struct MyIter
{
	typedef T value_type;
	T* ptr;
	MyIter(T* p = 0) : ptr(p) {}
	T& operator*() const { return *ptr; }
};

template <class I>
struct iterator_traits_
{
	typedef typename I::value_type value_type_;
};

template <class T>
struct iterator_traits_<T*>
{
	typedef T value_type_;
};

template <class I>
typename iterator_traits_<I>::value_type_ func(I ite)
{
	return *ite;
}



/*************************************************
示例程序能够识别的类型：
第一为基础句柄(为用CloseHandle释放的)
第二个为网络通信SOCKET，需要用closesocket释放
可以根据实际需要自己添加实现，例子程序就只实现这两个功能
*************************************************/

//基础句柄类(CloseHandle释放类型)
class CCommomHandleObject
{
public:
	void clear(HANDLE hCommhandle)
	{
		if (INVALID_HANDLE_VALUE != hCommhandle)
		{
			CloseHandle(hCommhandle);
		}
	}
};

//套接字类(closesocket释放类型)
class CSOCKETObject
{
public:
	void clear(SOCKET m_hSocket)
	{
		if (INVALID_SOCKET != m_hSocket)
		{
			closesocket(m_hSocket);
		}
	}
};

//C++萃取基础类
template<class _xTypeShow>
class CTraitsBaseObject
{
};

//根据HANDLE识别出CCommomHandleObject类
template<>
class CTraitsBaseObject<HANDLE>
{
public:
	typedef CCommomHandleObject _data_type_show;
};

//根据SOCKET识别出CSOCKETObject
template<>
class CTraitsBaseObject<SOCKET>
{
public:
	typedef CSOCKETObject _data_type_show;
};
/****************************************************************************
资源释放类，本例的重点，需要根据每个须释放的资源绑定一个CContainerClass对象
然后对象析构时会根据CTraitsBaseObject<_xType>::_data_type_show识别出是否为
自己认识的数据类型，如不认识则直接报错，然后创建临时对象调用clear，
根据实际情况销毁绑定的资源。
****************************************************************************/
template<class _xType>
class CContainerClass
{
public:
	CContainerClass(_xType &_tay){ m_hTay = _tay; }
	~CContainerClass(void){ clear(); }
private:
	CContainerClass(){}
	CContainerClass(CContainerClass &tay){}

	void clear()
	{
		CTraitsBaseObject<_xType>::_data_type_show().clear(m_hTay);
	}
private:
	_xType m_hTay;
};



template<long... nums>
struct Multiply;

template<long first, long... last>
struct Multiply<first, last...>
{
	static const long val = first * Multiply<last...>::val;
};

template<>
struct Multiply<>
{
	static const long val = 1;
};

// 普通函数
int add(int i, int j)
{
	return i + j;
}
// lambda表达式
auto mod = [](int i, int j)
{
	return i % j;
};

auto mul = [](int i, int j)
{
	return i*j;
};
// 函数对象类
struct divide
{
	int operator() (int denominator, int divisor)
	{
		return denominator / divisor;
	}
};

void print_num(int i)
{
	std::cout << i << '\n';
}

class Foo_F {
public:
	Foo_F(int num) : num_(num) {}
	static void print_add(Foo_F& a, int i)   { std::cout << i << '\n'; }
	int num_;
};

struct PrintNum {
	void operator()(int i) const
	{
		std::cout << i << '\n';
	}
};


//第二个参数为空
template<typename T>
class IsClassT{  //确定某个类型是否为类类型  
private:
	typedef char One;
	typedef struct
	{
		char a[2];
	} Two;
	template<typename C>
	static One test(int C::*); //C是类类型时使用这个版本，函数参数是一个C的成员指针  
	template<typename C>
	static Two test(...); //C是非类类型时使用这个版本  
public:
	enum { Yes = sizeof(test<T>(0)) == 1 }; //是类类型则Yes为1，不是类类型时Yes为0  
	enum { No = !Yes };
};



template<typename T>
void check()
{ //检查T是否是类类型：以模板实参方式传递类型  
	if (IsClassT<T>::Yes)
	{
		std::cout << " IsClassT(flag=" << IsClassT<T>::Yes << ")" << std::endl;
	}
	else
	{
		std::cout << " !IsClassT(flag=" << IsClassT<T>::Yes << ")" << std::endl;
	}
}
template<typename T>
void checkT(T& a)
{  //检查T是否是类类型：以函数调用实参方式传递类型  
	check<T>();
}
class MyClass
{ //类类型  
};
struct MyStruct
{ //类类型  
};

union MyUnion
{//类类型  
};

void myfunc()
{ //非类类型  
}
enum E{ e1 }e; //非类类型  