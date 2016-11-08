// CPP11Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "bindTest.h"

int _tmain(int argc, _TCHAR* argv[])
{
	//lambda
	/*
		
		基本语法
		[=, &b](int c)->int {return b += a + c;}

		简单来说，Lambda函数也就是一个函数，它的语法定义如下：
		[capture](parameters) mutable ->return-type{statement}

		1.[capture]：捕捉列表。捕捉列表总是出现在Lambda函数的开始处。实际上，[]是Lambda引出符。编译器根据该引出符判断接下来的代码是否是Lambda函数。
					 捕捉列表能够捕捉上下文中的变量以供Lambda函数使用;
		
		2.(parameters)：参数列表。与普通函数的参数列表一致。如果不需要参数传递，则可以连同括号“()”一起省略;
		
		3.mutable：mutable修饰符。默认情况下，Lambda函数总是一个const函数，mutable可以取消其常量性。在使用该修饰符时，参数列表不可省略（即使参数为空）;
		
		4.->return-type：返回类型。用追踪返回类型形式声明函数的返回类型。我们可以在不需要返回值的时候也可以连同符号”->”一起省略。
						 此外，在返回类型明确的情况下，也可以省略该部分，让编译器对返回类型进行推导;
		
		5.{statement}：函数体。内容与普通函数一样，不过除了可以使用参数之外，还可以使用所有捕获的变量。
					   与普通函数最大的区别是，除了可以使用参数以外，Lambda函数还可以通过捕获列表访问一些上下文中的数据。
					   具体地，捕捉列表描述了上下文中哪些数据可以被Lambda使用，以及使用方式（以值传递的方式或引用传递的方式）。
		
		语法上，在“[]”包括起来的是捕捉列表，捕捉列表由多个捕捉项组成，并以逗号分隔。捕捉列表有以下几种形式：

		1.[var]		表示值传递方式捕捉变量var;
		2.[=]		表示值传递方式捕捉所有父作用域的变量(包括this);
		3.[&var]	表示引用传递捕捉变量var;
		4.[&]		表示引用传递方式捕捉所有父作用域的变量(包括this);
		5.[this]	表示值传递方式捕捉当前的this指针。
	*/

	{
		std::vector<int> vecInt;
		vecInt.push_back(1);
		vecInt.push_back(2);
		vecInt.push_back(3);
		std::for_each( vecInt.begin(),vecInt.end(),[](int x){ std::cout << x + 2 << std::endl; } );
	}

	//闭包示例
	{
		//eg1 直接输出hello lambda. 
		//尾部的()使该lambda表达式可立即执行
		//前面的lambda表达式产生一个匿名对象 结合后面的()相当与一个无參的函数调用
		[]{ std::cout << "hello lambda." << std::endl; }();

		cout << [](const std::string& str)->std::string{ return "helloWorld" + str; }("-qwer").c_str() << endl;

		cout << [](int t)->int{ return t+2; }(1);

		//eg2 该lambda表达式接收一个const std::string&类型的参数
		//返回一个std::string类型的值 结果保存在lambda_return变量中
		//尾部的("hahaya")表示传入一个"hahaya"参数使lambda表达式立即执行
		std::string lambda_return = [](const std::string &str)->std::string{
			return "hello " + str; }("hahaya");
		std::cout << lambda_return << std::endl;

		//eg3 该lambda表达式接收一个const std::string&类型的参数
		//lambda表示式的返回值通过return语句推导
		//lambda表达式产生一个匿名对象 保存在func对象中
		auto func = [](const std::string &str){ return "hello " + str; };
		std::cout << func("ToSmile") << std::endl;
		std::cout << func("C++") << std::endl;

		//eg4 按传值的方式捕获外部变量 
		//需要加上mutable关键字 否则不能在lambda表达式中修改total的值
		//由于是传值方式  所以在lambda表达式外部total的值并没有改变 但是在lambda表达式内部改变了
		int total = 0;
		[total](int num)mutable{ total += num; std::cout << total << std::endl; }(2);
		std::cout << "capture by value:" << total << std::endl;

		//eg5 按传引用的方式捕获外部变量
		//不需要加上mutable关键字
		//由于是传引用方式 所以在lambda表达式内部和外部都在total的值改变了
		[&total](int num){ total += num; std::cout << total << std::endl; }(2);
		std::cout << "capture by reference:" << total << std::endl;

		//eg6 lambda和stl的配合使用
		std::vector<int> vecInt;
		vecInt.push_back(1);
		vecInt.push_back(2);
		vecInt.push_back(3);
		std::for_each(vecInt.begin(), vecInt.end(), [](int val){std::cout << val + 2 << std::endl; });
		std::cout << std::endl;
		std::vector<int> secInt;
		secInt.push_back(7);
		secInt.push_back(8);

		//eg7 lambda和stl的配合使用 先保存匿名对象后调用
		auto add_func = [](int val){std::cout << val + 2 << std::endl; };
		std::for_each(secInt.begin(), secInt.end(), add_func);
	}

	{
		std::cout << "-----------------------" << std::endl;
		//std::reference_wrapper封装int内置类型
		int number = 1;
		std::reference_wrapper<int> rw(number);
		std::cout << "Number:" << rw.get() << std::endl;
		std::vector<int> vecInt;
		vecInt.push_back(1);
		vecInt.push_back(2);
		vecInt.push_back(3);
		//std::ref只能用于左值 最下面一行代码直接使用std::ref引用lambda表达式目前是编译不过的(lambda表达式是右值)
		//所以先用auto func对象保存lambda表达式返回的闭包对象 再std::for_each再对func进行引用
		auto func = [](int val){std::cout << val + 2 << std::endl; };
		std::for_each(vecInt.begin(), vecInt.end(), std::ref(func));
		//std::for_each(vecInt.begin(), vecInt.end(),
		//std::ref( [](int val){std::cout << val + 2 << std::endl;} ));
	}

	//bind Test
	{
		//绑定普通函数
		//使用auto接收std::bind的返回值
		std::cout << "绑定普通函数" << std::endl;
		auto bind_comm_func = std::bind(get_number, std::placeholders::_1);
		std::cout << bind_comm_func(2) << std::endl;
		
		//使用std::function接收std::bind的返回值
		std::function<int(int)> bind_comm_func_1 = std::bind(get_number, std::placeholders::_1);
		std::cout << bind_comm_func_1(22) << std::endl;
		std::cout << "绑定普通函数" << std::endl;
		
		//绑定带有引用参数的普通函数
		std::cout << "绑定带有引用参数的普通函数" << std::endl;
		int value = 22222;
		//auto
		auto bind_ref_func = std::bind(display, std::placeholders::_1, std::ref(value));
		bind_ref_func(1111);


		//std::bind
		std::function<void(int)> bind_ref_func_1 = std::bind(display, std::placeholders::_1, std::ref(value));
		bind_ref_func_1(22222);
		std::cout << "绑定带有引用参数的普通函数" << std::endl;

		//绑定静态成员函数
		std::cout << "绑定静态成员函数" << std::endl;
		//auto
		auto bind_static_member_func = std::bind(&Test::say_hello);
		bind_static_member_func();


		//std::function
		std::function<void(void)> bind_static_member_func_1 = std::bind(&Test::say_hello);
		bind_static_member_func();
		std::cout << "绑定静态成员函数" << std::endl;
		
		//绑定成员函数 需要多传递一个函数对象 故先需要创建函数对象
		std::cout << "绑定成员函数" << std::endl;
		//auto
		Test test(2);
		auto bind_member_func = std::bind(&Test::print_add, test, std::placeholders::_1);
		bind_member_func(2);


		//std::function
		std::function<void(int)> bind_member_func_1 = std::bind(&Test::print_add, test, std::placeholders::_1);
		bind_member_func_1(3);


		std::cout << "绑定成员函数" << std::endl;
		//绑定public成员变量
		std::cout << "绑定public成员变量" << std::endl;
		//auto
		auto bind_member_data = std::bind(&Test::num_, std::placeholders::_1);
		std::cout << bind_member_data(test) << std::endl;
		//int a = bind_member_data(test);
		//std::cout << "a" <<  a << std::endl;
		//std::function
		std::function<int(Test)> bind_member_data_1 = std::bind(&Test::num_, std::placeholders::_1);
		std::cout << bind_member_data_1(test) << std::endl;
		std::cout << "绑定public成员变量" << std::endl;
	}

	{
		
		auto polly = std::bind(Polly(), std::placeholders::_1, "confusing");
		std::cout << polly(4) << polly(std::string(" this is ")) << std::endl;
	}

	{
		// 绑定全局函数  
		auto add2 = std::bind(add1, std::placeholders::_1, std::placeholders::_2, 10);
		// 函数add2 = 绑定add1函数，参数1不变，参数2不变，参数3固定为10.  
		std::cout << typeid(add2).name() << std::endl;
		std::cout << "add2(1,2) = " << add2(1, 2) << std::endl;

		std::cout << "\n---------------------------" << std::endl;

		// 绑定成员函数  
		Utils utils("Vicky");
		auto sayHello = std::bind(&Utils::sayHello, utils/*调用者*/, std::placeholders::_1/*参数1*/);
		sayHello("Jack");

		auto sayHelloToLucy = std::bind(&Utils::sayHello, utils/*调用者*/, "Lucy"/*固定参数1*/);
		sayHelloToLucy();

		// 绑定静态成员函数  
		auto getId = std::bind(&Utils::getId);
		std::cout << getId() << std::endl;

		std::cout << "\n---------------------------" << std::endl;

		// 绑定operator函数  
		auto add100 = std::bind(&Utils::operator (), utils, std::placeholders::_1, std::placeholders::_2, 100);
		std::cout << "add100(1, 2) = " << add100(1, 2) << std::endl;

		// 注意：无法使用std::bind()绑定一个重载函数  
	}

	{
		// 将函数注册到对象中，通过对象直接调用 
		Func<void(*)() > sayHelloFunc(sayHello);
		sayHelloFunc.Call();


		Func<int(*)(int, int, int) > sumFunc(sum);
		std::cout << "sumFunc.Call<int>(1, 2, 3) : " << sumFunc.Call<int>(1, 2, 3) << std::endl;


		std::cout << "\n---------------------------" << std::endl;

		Fn<> sayHelloFn(sayHello);
		sayHelloFn();

		Fn<int, int, int, int> sumFn(sum);
		std::cout << "sumFn(1, 2, 3) : " << sumFn(1, 2, 3) << std::endl;

		std::cout << "\n---------------------------" << std::endl;

		/*
			Hello world !
			sumFunc.Call<int>(1, 2, 3) : 6

			-------------------------- -
			Hello world !
			sumFn(1, 2, 3) : 6

			-------------------------- -
			上面的例子非常有趣，使用了2种方案，将一个函数，注册到一个对象 / 仿函数中，并且通过一个对象 / 仿函数来直接调用调用。
			例子显而易见的，第2种方案更佳简洁，并且对传递参数有明确的判断，当参数类型或数量不正确的时候，编译器将导致失败。
			这种方案，可以将类的成员变量直接作为函数的参数使用，或者，如我：
			http ://blog.csdn.NET/eclipser1987/article/details/23926395
			这篇文章中，无法直接调用脚本函数类，有了好的解决办法。这个我将随后补充。
		*/
	}

	{
		Foo foo;
		Fns<int, int> s;

		// Connect a function  
		s.connect(foobar);
		// Connect a class method  
		s.connect(&foo, &Foo::bar);
		// Create and connect some lambda expression  
		s.connect([&foo](int x, int y){
			printf("lambda::"); foo.bar(x, y);
		});
		// Emit the signal !  
		s.emit(4, 2);

		/*
		foobar(4, 2)
		Foo::bar(4, 2)
		lambda::Foo::bar(4, 2)
		*/
	}


	{
		vector< int> vec;
		for (int i = 0; i < 10; ++i)
		{
			vec.push_back(i + 1);
		}
		/// 1. simple lambda
		auto it = std::find_if(vec.begin(), vec.end(), [](int i) { return i > 50; });

		class A
		{
		public:
			bool operator()(int i) const { 
				return i > 50; 
			}
		};
		auto it1 = std::find_if(vec.begin(), vec.end(), A() );

		/// 2. lambda return syntax
		std::function< int(int)> square = [](int i) -> int { return i * i; };

	   /// 3. lambda expr: capture of local variable
	  {
			int min_val = 10;
			int max_val = 1000;

			auto it = std::find_if(vec.begin(), vec.end(), [=](int i) {
				return i > min_val && i < max_val;
			});

			auto it2 = std::find_if(vec.begin(), vec.end(), [&](int i) {
				return i > min_val && i < max_val;
			});

			auto it3 = std::find_if(vec.begin(), vec.end(), [=, &max_val](int i) {
				return i > min_val && i < max_val;
			});
		}

		/// 4. lambda expr: capture of class member
		class A1
		{
		public:
			/// 4.1 capture member by this
			void DoSomething()
			{
				auto it = std::find_if(m_vec.begin(), m_vec.end(), [this](int i){
					return i > m_min_val && i < m_max_val; });
			}
			/// 4.2 capture member by default pass-by-value
			void DoSomething1()
			{
				auto it = std::find_if(m_vec.begin(), m_vec.end(), [=](int i){
					return i > m_min_val && i < m_max_val; });
			}

			/// 4.3 capture member by default pass-by-reference
			void DoSomething2()
			{
				auto it = std::find_if(m_vec.begin(), m_vec.end(), [&](int i){
					return i > m_min_val && i < m_max_val; });
			}

		private:
			std::vector<int>  m_vec;
			int               m_min_val;
			int               m_max_val;
		};
	}

	{
		f_2 f2 = std::mem_fn(&int_div::int_div_fun);            // 指向成员函数

		int_div int_div_object;
		int v = f2(&int_div_object, 5);  // 在对象x上用参数5调用X::foo()
		std::function<int(int)> ff = std::bind(f2, &int_div_object, std::placeholders::_1);    // f的第一个参数是&x
		v = ff(5);                // 调用x.foo(5)
	}


	{
		{
			std::cout << "int: ";
			check<int>(); //非类类型  
			std::cout << "MyClass: ";
			check<MyClass>(); //类类型  
			std::cout << "MyStruct: ";
			MyStruct s;
			checkT(s); //类类型  
			std::cout << "MyUnion: ";
			check<MyUnion>(); //类类型  
			std::cout << "enum: ";
			checkT(e); //非类类型  
			std::cout << "myfunc():";
			checkT(myfunc); //非类类型  
		}

		// store a free function
		std::function<void(int)> f_display = print_num;
		f_display(-9);

		// store a lambda
		std::function<void()> f_display_42 = []() { print_num(42); };
		f_display_42();

		// store the result of a call to std::bind
		std::function<void()> f_display_31337 = std::bind(print_num, 31337);
		f_display_31337();

		// store a call to a member function
		Foo_F foo(314159);
		std::function<void(Foo_F&, int)> f_add_display = &Foo_F::print_add;

		f_add_display(foo, 1);

		// store a call to a member function and object
		using std::placeholders::_1;
		std::function<void(int)> f_add_display2 = std::bind(&Foo_F::print_add, foo, _1);
		f_add_display2(2);

		// store a call to a function object
		std::function<void(int)> f_display_obj = PrintNum();
		f_display_obj(18);

		// 受限的map
		// 	std::map<char, int(*)(int, int)> binops_limit;
		// 	binops_limit.insert({ '+', add });
		// 	binops_limit.insert({ '%', mod });
		// 错误	1	error C2664: “void std::_Tree<std::_Tmap_traits<_Kty,_Ty,_Pr,_Alloc,false>>::insert(std::initializer_list<std::pair<const _Kty,_Ty>>)”: 无法将参数 1 从“initializer-list”转换为“std::pair<const _Kty,_Ty> &&”
		// binops_limit.insert({ '%', divide() });

		// 更灵活的map
		std::map<char, function<int(int, int)>> binops =
		{
			{ '+', add },
			{ '-', minus<int>() },
			{ '*', mul },
			{ '/', divide() },
			{ '%', mod },
		};
		cout << binops['+'](10, 5) << endl;
		cout << binops['-'](10, 5) << endl;
		cout << binops['*'](10, 5) << endl;
		cout << binops['/'](10, 5) << endl;
		cout << binops['%'](10, 5) << endl;

		cout << Multiply<2, 3, 4, 5>::val << endl;
		cout << Multiply<22, 44, 66, 88, 9>::val << endl;
	}

	// auto for用法
	{
		typedef struct xx{
			int a;
			int b;
		}tag_xx;
		std::vector<tag_xx> vecint;
		for (int i = 0; i < 10; ++i)
		{
			tag_xx aa;
			aa.a = i;
			aa.b = i + 1;
			vecint.push_back(aa);
		}
		for (auto &e : vecint)
		{
			e.a += 2;
			cout << e.a << endl;
		}
	}

	return 0;
}

