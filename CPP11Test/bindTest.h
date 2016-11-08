#pragma once

//�������ò�������ͨ����
void display(int first, int &second)
{
	std::cout << "first: " << first << " second:" << second << std::endl;
}
//��ͨ����
int get_number(int number)
{
	return number;
}
class Test
{
public:
	Test(int num) : num_(num)
	{ }
	//��̬��Ա����
	static void say_hello()
	{
		std::cout << "hello" << std::endl;
	}
	//��Ա����
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

struct int_div {        // ����һ������ʹ��"()"���е��õĺ�����������  
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
ʾ�������ܹ�ʶ������ͣ�
��һΪ�������(Ϊ��CloseHandle�ͷŵ�)
�ڶ���Ϊ����ͨ��SOCKET����Ҫ��closesocket�ͷ�
���Ը���ʵ����Ҫ�Լ����ʵ�֣����ӳ����ֻʵ������������
*************************************************/

//���������(CloseHandle�ͷ�����)
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

//�׽�����(closesocket�ͷ�����)
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

//C++��ȡ������
template<class _xTypeShow>
class CTraitsBaseObject
{
};

//����HANDLEʶ���CCommomHandleObject��
template<>
class CTraitsBaseObject<HANDLE>
{
public:
	typedef CCommomHandleObject _data_type_show;
};

//����SOCKETʶ���CSOCKETObject
template<>
class CTraitsBaseObject<SOCKET>
{
public:
	typedef CSOCKETObject _data_type_show;
};
/****************************************************************************
��Դ�ͷ��࣬�������ص㣬��Ҫ����ÿ�����ͷŵ���Դ��һ��CContainerClass����
Ȼ���������ʱ�����CTraitsBaseObject<_xType>::_data_type_showʶ����Ƿ�Ϊ
�Լ���ʶ���������ͣ��粻��ʶ��ֱ�ӱ���Ȼ�󴴽���ʱ�������clear��
����ʵ��������ٰ󶨵���Դ��
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

// ��ͨ����
int add(int i, int j)
{
	return i + j;
}
// lambda���ʽ
auto mod = [](int i, int j)
{
	return i % j;
};

auto mul = [](int i, int j)
{
	return i*j;
};
// ����������
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


//�ڶ�������Ϊ��
template<typename T>
class IsClassT{  //ȷ��ĳ�������Ƿ�Ϊ������  
private:
	typedef char One;
	typedef struct
	{
		char a[2];
	} Two;
	template<typename C>
	static One test(int C::*); //C��������ʱʹ������汾������������һ��C�ĳ�Աָ��  
	template<typename C>
	static Two test(...); //C�Ƿ�������ʱʹ������汾  
public:
	enum { Yes = sizeof(test<T>(0)) == 1 }; //����������YesΪ1������������ʱYesΪ0  
	enum { No = !Yes };
};



template<typename T>
void check()
{ //���T�Ƿ��������ͣ���ģ��ʵ�η�ʽ��������  
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
{  //���T�Ƿ��������ͣ��Ժ�������ʵ�η�ʽ��������  
	check<T>();
}
class MyClass
{ //������  
};
struct MyStruct
{ //������  
};

union MyUnion
{//������  
};

void myfunc()
{ //��������  
}
enum E{ e1 }e; //��������  