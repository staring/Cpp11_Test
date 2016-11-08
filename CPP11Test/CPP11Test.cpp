// CPP11Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "bindTest.h"

int _tmain(int argc, _TCHAR* argv[])
{
	//lambda
	/*
		
		�����﷨
		[=, &b](int c)->int {return b += a + c;}

		����˵��Lambda����Ҳ����һ�������������﷨�������£�
		[capture](parameters) mutable ->return-type{statement}

		1.[capture]����׽�б���׽�б����ǳ�����Lambda�����Ŀ�ʼ����ʵ���ϣ�[]��Lambda�����������������ݸ��������жϽ������Ĵ����Ƿ���Lambda������
					 ��׽�б��ܹ���׽�������еı����Թ�Lambda����ʹ��;
		
		2.(parameters)�������б�����ͨ�����Ĳ����б�һ�¡��������Ҫ�������ݣ��������ͬ���š�()��һ��ʡ��;
		
		3.mutable��mutable���η���Ĭ������£�Lambda��������һ��const������mutable����ȡ���䳣���ԡ���ʹ�ø����η�ʱ�������б���ʡ�ԣ���ʹ����Ϊ�գ�;
		
		4.->return-type���������͡���׷�ٷ���������ʽ���������ķ������͡����ǿ����ڲ���Ҫ����ֵ��ʱ��Ҳ������ͬ���š�->��һ��ʡ�ԡ�
						 ���⣬�ڷ���������ȷ������£�Ҳ����ʡ�Ըò��֣��ñ������Է������ͽ����Ƶ�;
		
		5.{statement}�������塣��������ͨ����һ�����������˿���ʹ�ò���֮�⣬������ʹ�����в���ı�����
					   ����ͨ�������������ǣ����˿���ʹ�ò������⣬Lambda����������ͨ�������б����һЩ�������е����ݡ�
					   ����أ���׽�б�����������������Щ���ݿ��Ա�Lambdaʹ�ã��Լ�ʹ�÷�ʽ����ֵ���ݵķ�ʽ�����ô��ݵķ�ʽ����
		
		�﷨�ϣ��ڡ�[]�������������ǲ�׽�б���׽�б��ɶ����׽����ɣ����Զ��ŷָ�����׽�б������¼�����ʽ��

		1.[var]		��ʾֵ���ݷ�ʽ��׽����var;
		2.[=]		��ʾֵ���ݷ�ʽ��׽���и�������ı���(����this);
		3.[&var]	��ʾ���ô��ݲ�׽����var;
		4.[&]		��ʾ���ô��ݷ�ʽ��׽���и�������ı���(����this);
		5.[this]	��ʾֵ���ݷ�ʽ��׽��ǰ��thisָ�롣
	*/

	{
		std::vector<int> vecInt;
		vecInt.push_back(1);
		vecInt.push_back(2);
		vecInt.push_back(3);
		std::for_each( vecInt.begin(),vecInt.end(),[](int x){ std::cout << x + 2 << std::endl; } );
	}

	//�հ�ʾ��
	{
		//eg1 ֱ�����hello lambda. 
		//β����()ʹ��lambda���ʽ������ִ��
		//ǰ���lambda���ʽ����һ���������� ��Ϻ����()�൱��һ���ޅ��ĺ�������
		[]{ std::cout << "hello lambda." << std::endl; }();

		cout << [](const std::string& str)->std::string{ return "helloWorld" + str; }("-qwer").c_str() << endl;

		cout << [](int t)->int{ return t+2; }(1);

		//eg2 ��lambda���ʽ����һ��const std::string&���͵Ĳ���
		//����һ��std::string���͵�ֵ ���������lambda_return������
		//β����("hahaya")��ʾ����һ��"hahaya"����ʹlambda���ʽ����ִ��
		std::string lambda_return = [](const std::string &str)->std::string{
			return "hello " + str; }("hahaya");
		std::cout << lambda_return << std::endl;

		//eg3 ��lambda���ʽ����һ��const std::string&���͵Ĳ���
		//lambda��ʾʽ�ķ���ֵͨ��return����Ƶ�
		//lambda���ʽ����һ���������� ������func������
		auto func = [](const std::string &str){ return "hello " + str; };
		std::cout << func("ToSmile") << std::endl;
		std::cout << func("C++") << std::endl;

		//eg4 ����ֵ�ķ�ʽ�����ⲿ���� 
		//��Ҫ����mutable�ؼ��� ��������lambda���ʽ���޸�total��ֵ
		//�����Ǵ�ֵ��ʽ  ������lambda���ʽ�ⲿtotal��ֵ��û�иı� ������lambda���ʽ�ڲ��ı���
		int total = 0;
		[total](int num)mutable{ total += num; std::cout << total << std::endl; }(2);
		std::cout << "capture by value:" << total << std::endl;

		//eg5 �������õķ�ʽ�����ⲿ����
		//����Ҫ����mutable�ؼ���
		//�����Ǵ����÷�ʽ ������lambda���ʽ�ڲ����ⲿ����total��ֵ�ı���
		[&total](int num){ total += num; std::cout << total << std::endl; }(2);
		std::cout << "capture by reference:" << total << std::endl;

		//eg6 lambda��stl�����ʹ��
		std::vector<int> vecInt;
		vecInt.push_back(1);
		vecInt.push_back(2);
		vecInt.push_back(3);
		std::for_each(vecInt.begin(), vecInt.end(), [](int val){std::cout << val + 2 << std::endl; });
		std::cout << std::endl;
		std::vector<int> secInt;
		secInt.push_back(7);
		secInt.push_back(8);

		//eg7 lambda��stl�����ʹ�� �ȱ���������������
		auto add_func = [](int val){std::cout << val + 2 << std::endl; };
		std::for_each(secInt.begin(), secInt.end(), add_func);
	}

	{
		std::cout << "-----------------------" << std::endl;
		//std::reference_wrapper��װint��������
		int number = 1;
		std::reference_wrapper<int> rw(number);
		std::cout << "Number:" << rw.get() << std::endl;
		std::vector<int> vecInt;
		vecInt.push_back(1);
		vecInt.push_back(2);
		vecInt.push_back(3);
		//std::refֻ��������ֵ ������һ�д���ֱ��ʹ��std::ref����lambda���ʽĿǰ�Ǳ��벻����(lambda���ʽ����ֵ)
		//��������auto func���󱣴�lambda���ʽ���صıհ����� ��std::for_each�ٶ�func��������
		auto func = [](int val){std::cout << val + 2 << std::endl; };
		std::for_each(vecInt.begin(), vecInt.end(), std::ref(func));
		//std::for_each(vecInt.begin(), vecInt.end(),
		//std::ref( [](int val){std::cout << val + 2 << std::endl;} ));
	}

	//bind Test
	{
		//����ͨ����
		//ʹ��auto����std::bind�ķ���ֵ
		std::cout << "����ͨ����" << std::endl;
		auto bind_comm_func = std::bind(get_number, std::placeholders::_1);
		std::cout << bind_comm_func(2) << std::endl;
		
		//ʹ��std::function����std::bind�ķ���ֵ
		std::function<int(int)> bind_comm_func_1 = std::bind(get_number, std::placeholders::_1);
		std::cout << bind_comm_func_1(22) << std::endl;
		std::cout << "����ͨ����" << std::endl;
		
		//�󶨴������ò�������ͨ����
		std::cout << "�󶨴������ò�������ͨ����" << std::endl;
		int value = 22222;
		//auto
		auto bind_ref_func = std::bind(display, std::placeholders::_1, std::ref(value));
		bind_ref_func(1111);


		//std::bind
		std::function<void(int)> bind_ref_func_1 = std::bind(display, std::placeholders::_1, std::ref(value));
		bind_ref_func_1(22222);
		std::cout << "�󶨴������ò�������ͨ����" << std::endl;

		//�󶨾�̬��Ա����
		std::cout << "�󶨾�̬��Ա����" << std::endl;
		//auto
		auto bind_static_member_func = std::bind(&Test::say_hello);
		bind_static_member_func();


		//std::function
		std::function<void(void)> bind_static_member_func_1 = std::bind(&Test::say_hello);
		bind_static_member_func();
		std::cout << "�󶨾�̬��Ա����" << std::endl;
		
		//�󶨳�Ա���� ��Ҫ�ഫ��һ���������� ������Ҫ������������
		std::cout << "�󶨳�Ա����" << std::endl;
		//auto
		Test test(2);
		auto bind_member_func = std::bind(&Test::print_add, test, std::placeholders::_1);
		bind_member_func(2);


		//std::function
		std::function<void(int)> bind_member_func_1 = std::bind(&Test::print_add, test, std::placeholders::_1);
		bind_member_func_1(3);


		std::cout << "�󶨳�Ա����" << std::endl;
		//��public��Ա����
		std::cout << "��public��Ա����" << std::endl;
		//auto
		auto bind_member_data = std::bind(&Test::num_, std::placeholders::_1);
		std::cout << bind_member_data(test) << std::endl;
		//int a = bind_member_data(test);
		//std::cout << "a" <<  a << std::endl;
		//std::function
		std::function<int(Test)> bind_member_data_1 = std::bind(&Test::num_, std::placeholders::_1);
		std::cout << bind_member_data_1(test) << std::endl;
		std::cout << "��public��Ա����" << std::endl;
	}

	{
		
		auto polly = std::bind(Polly(), std::placeholders::_1, "confusing");
		std::cout << polly(4) << polly(std::string(" this is ")) << std::endl;
	}

	{
		// ��ȫ�ֺ���  
		auto add2 = std::bind(add1, std::placeholders::_1, std::placeholders::_2, 10);
		// ����add2 = ��add1����������1���䣬����2���䣬����3�̶�Ϊ10.  
		std::cout << typeid(add2).name() << std::endl;
		std::cout << "add2(1,2) = " << add2(1, 2) << std::endl;

		std::cout << "\n---------------------------" << std::endl;

		// �󶨳�Ա����  
		Utils utils("Vicky");
		auto sayHello = std::bind(&Utils::sayHello, utils/*������*/, std::placeholders::_1/*����1*/);
		sayHello("Jack");

		auto sayHelloToLucy = std::bind(&Utils::sayHello, utils/*������*/, "Lucy"/*�̶�����1*/);
		sayHelloToLucy();

		// �󶨾�̬��Ա����  
		auto getId = std::bind(&Utils::getId);
		std::cout << getId() << std::endl;

		std::cout << "\n---------------------------" << std::endl;

		// ��operator����  
		auto add100 = std::bind(&Utils::operator (), utils, std::placeholders::_1, std::placeholders::_2, 100);
		std::cout << "add100(1, 2) = " << add100(1, 2) << std::endl;

		// ע�⣺�޷�ʹ��std::bind()��һ�����غ���  
	}

	{
		// ������ע�ᵽ�����У�ͨ������ֱ�ӵ��� 
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
			��������ӷǳ���Ȥ��ʹ����2�ַ�������һ��������ע�ᵽһ������ / �º����У�����ͨ��һ������ / �º�����ֱ�ӵ��õ��á�
			�����Զ��׼��ģ���2�ַ������Ѽ�࣬���ҶԴ��ݲ�������ȷ���жϣ����������ͻ���������ȷ��ʱ�򣬱�����������ʧ�ܡ�
			���ַ��������Խ���ĳ�Ա����ֱ����Ϊ�����Ĳ���ʹ�ã����ߣ����ң�
			http ://blog.csdn.NET/eclipser1987/article/details/23926395
			��ƪ�����У��޷�ֱ�ӵ��ýű������࣬���˺õĽ���취������ҽ���󲹳䡣
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
		f_2 f2 = std::mem_fn(&int_div::int_div_fun);            // ָ���Ա����

		int_div int_div_object;
		int v = f2(&int_div_object, 5);  // �ڶ���x���ò���5����X::foo()
		std::function<int(int)> ff = std::bind(f2, &int_div_object, std::placeholders::_1);    // f�ĵ�һ��������&x
		v = ff(5);                // ����x.foo(5)
	}


	{
		{
			std::cout << "int: ";
			check<int>(); //��������  
			std::cout << "MyClass: ";
			check<MyClass>(); //������  
			std::cout << "MyStruct: ";
			MyStruct s;
			checkT(s); //������  
			std::cout << "MyUnion: ";
			check<MyUnion>(); //������  
			std::cout << "enum: ";
			checkT(e); //��������  
			std::cout << "myfunc():";
			checkT(myfunc); //��������  
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

		// ���޵�map
		// 	std::map<char, int(*)(int, int)> binops_limit;
		// 	binops_limit.insert({ '+', add });
		// 	binops_limit.insert({ '%', mod });
		// ����	1	error C2664: ��void std::_Tree<std::_Tmap_traits<_Kty,_Ty,_Pr,_Alloc,false>>::insert(std::initializer_list<std::pair<const _Kty,_Ty>>)��: �޷������� 1 �ӡ�initializer-list��ת��Ϊ��std::pair<const _Kty,_Ty> &&��
		// binops_limit.insert({ '%', divide() });

		// ������map
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

	// auto for�÷�
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

