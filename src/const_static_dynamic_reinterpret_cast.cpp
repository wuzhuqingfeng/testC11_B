#include <iostream>
using namespace std;

/*
	Const�ô�
	//���������const��
	1ָ��������������������Ч����ߴ���ɶ��ԣ�����bug��
	2����ķ��������������������

���ۣ�
	C�����е�const����
		C������const������ֻ�����������Լ��Ĵ洢�ռ�

	C++�е�const����
		���ܷ���洢�ռ�,Ҳ���ܲ�����洢�ռ�
		��const����Ϊȫ�֣�������Ҫ�������ļ���ʹ�ã������洢�ռ�
		��ʹ��&��������ȡconst�����ĵ�ַʱ�������洢�ռ�
		��const int &a = 10; const��������ʱ��Ҳ�����洢�ռ�

*/
#if 0
void test()
{
	{
		const int a = 10;
		int const b = 10;//��һ���ڶ�����˼һ�� ����һ����������

		const int* c = &a;//������ c��һ��ָ����������ָ��(��ָ����ڴ����ݲ��ܱ��޸ģ����Ǳ�������޸�)
		//*c = 100;//err
		int arr[10] = { 1,2 };
		int* const d = arr;//���ĸ� d ��ָ�루ָ��������ܱ��޸ģ���������ָ���ڴ�ռ���Ա��޸ģ�

		//const int* const e; //����� eһ��ָ�����εĳ�ָ�루ָ�������ָ����ڴ�ռ䣬�����ܱ��޸ģ�
	}

	/*
	* C�С�ð�ƻ���
	*
	C++��������const�����Ĵ���
	��������������ʱ���ڷ��ű��з��볣�� =?���⣺������ν���ȡ��ַ
	���������������ʹ�ó�����ֱ���Է��ű��е�ֵ�滻
	��������������ֶ�constʹ����extern����&�������������Ӧ�ĳ�������洢�ռ䣨����C��

	*/
	{
		//int& c = 1;// ������ 1 û�е�ַ��û�е�ַ�������� error C2440: 'initializing': cannot convert from 'int' to 'int &'

		const int a = 10;
		int* p = (int*)&a;
		printf("a = %d\n", a);//a =10
		*p = 11;
		printf("a = %d\n", a);//a = 10 C++��������Ȼ����Ϊconst��������ռ䣬������ʹ����洢�ռ��е�ֵ��ֱ��ʹ�ó������е�ֵ
		const int& b = a;	//����,ȡ����a�ĵ�ַ��*a �ڴ��е�ֵ�Ѿ��ı���
		std::cout << "b = " << b << std::endl;//b = 11


		const int& d = 100;//ok
		std::cout << "d = " << d << std::endl;//d = 100
		printf("Hello......\n");
	}
}

#endif

/*
* �Աȼ���
	C++�е�const���������ں궨��
	const int c = 5; �� #define c 5
	C++�е�const������궨�岻ͬ
	const�������ɱ���������ģ��ṩ���ͼ�����������
	�궨����Ԥ�����������������ı��滻
*/

//��func1����a����func2����ʹ��
//��func1�ж����b����func2�в���
#if 0
void fun1()
{
#define a 10
	//#undef a
	const int b = 20;
}

void fun2()
{
	printf("a = %d\n", a);
	//printf("b = %d\n", b);
}

void test()
{
	fun1();
	fun2();
}
#endif

/*
	������һ���е�ַ�������ǳ���

	���õı���
	1��������C++�е��ڲ�ʵ����һ����ָ��
	Type& name  <=> Type* const name
	2��C++�������ڱ��������ʹ�ó�ָ����Ϊ���õ��ڲ�ʵ�֣����������ռ�õĿռ��С��ָ����ͬ��
	3����ʹ�õĽǶȣ����û����������ֻ��һ��������û���Լ��Ĵ洢�ռ䡣����C++Ϊ��ʵ���Զ�������ϸ������

	4��	����ϸ�Աȼ�Ӹ�ֵ��������������
	1������������ ��һ��ʵ��һ���βΣ�
	2�������� ʵ��ȡ��ַ�����β�
	3*p�β�ȥ��ӵ��޸�ʵ�ε�ֵ

	���ý���
	1��������ʵ���ϣ�ֻ�����ǰѣ���Ӹ�ֵ���������������ĺ������Ͷ�Ϊһ
	//��ʵ�δ����β����õ�ʱ��ֻ������c++�����������ǳ���Ա�ֹ�ȡ��һ��ʵ�ε�ַ���������β����ã�����ָ�룩
	2��������ʹ�������﷨��ʱ�����ǲ�ȥ���ı�������������ô����
	�����Ƿ�����ֵ��﷨�����ʱ�����ǲ�ȥ����c++����������ô����

*/
#if 0
struct Teacer {
	int& a; //�ȼ��� int*const a;
	int& b;
};

void func(int& a)
{
	a = 5;
}

void func(int*const a)
{
	*a = 5;
}

void test()
{
	int a = 10;
	int& b = a;
	b = 11;

	cout << "b--->" << a << endl;
	printf("a:%d\n", a);
	printf("b:%d\n", b);
	printf("&a:%d\n", &a);
	printf("&b:%d\n", &b);  //��˼������ͬһ�ڴ�ռ����ȡ�ü�������

	printf("sizeof(Teacher) %d\n", sizeof(Teacer));//sizeof(Teacher) 8
}
#endif

/*
	ǿ������ת������һ�����յģ��е�ת������һ����ȫ�����������ֵת����ָ�룬
	�ѻ���ָ��ת����������ָ�룬��һ�ֺ���ָ��ת������һ�ֺ���ָ�룬
	�ѳ���ָ��ת���ɷǳ���ָ��ȡ�

	ǿ��ת�������

	C++ ���������ֹ��ܲ�ͬ��ǿ������ת��������Խ���ǿ������ת����
	- const_cast
	- static_cast
	- reinterpret_cast
	- dynamic_cast

	C����ǿ������ת��ȱ�㣺

	��Ҫ��Ϊ�˿˷�C����ǿ������ת������������ȱ�㡣

	- û�д���ʽ������ת�����ܺͷ��յĲ�ͬ��
		  ���磬�� int ǿ��ת���� double ��û�з��յģ���������ָ��ת���ɷǳ���ָ�룬
		  ������ָ��ת����������ָ�붼�Ǹ߷��յģ����Һ����ߴ����ķ��ղ�ͬ������������
		  ��ͬ����Ĵ��󣩣�C���Ե�ǿ������ת����ʽ����Щ��ͬ�����������֡�

	- ����̬����ָ��ת����������ָ��ʱ����鰲ȫ�ԣ����޷��ж�ת�����ָ���Ƿ�ȷʵָ��һ�����������

	- �����ڳ�����Ѱ�ҵ���ʲô�ط�������ǿ������ת����

	  ǿ������ת����������������ʱ�����һ��ԭ������ڳ������ʱ�����ܾͻ��뵽�ǲ�������Щǿ������ת���������⡣
*/

/*
	const_cast
	�����ڽ���ȥ�� const ���Ե�ת������Ҳ���ĸ�ǿ������ת���������Ψһ�ܹ�ȥ�� const ���Ե��������

	������������ǻ����������Ͳ�����ת��Ϊ�ǳ�������ֻ��ͨ��ָ����������޸�
*/
#if 0
void test()
{
	const int n = 5;
	const std::string s = "hello";

	//std::string t = const_cast<std::string>(s);
	//int k = const_cast<int>(n);//error C2440: 'const_cast': cannot convert from 'const int' to 'int'

	std::string& t = const_cast<std::string&>(s);//ת��������
	t = "123456";
	std::cout << "s = " << s << " t = " << t << std::endl;//s = 123456 t = 123456

	int* k = const_cast<int*>(&n);//ת����ָ��
	*k = 10;
	std::cout << "n = " << n << " *k = " << *k << std::endl;//n = 5 *k = 10 nΪʲô���ǵ���5 �� n��ֵ �Ǵӳ��������õ���
}
#endif

/*
	const_cast
	����Ա������ȥ��thisָ���const����
*/
#if 1
class CTest
{
public:
	
	CTest() :m_i(2) { std::cout << m_i << std::endl; }
public:

	/*
		const���ں�����ĩβ
		���Ƕ�������Ե�
		����Ա���������ı����ĳ�Ա������Ҳ�����������κη�const��Ա����

		��const��Ա������,this��������һ��ָ��const�����Ͷ���� constָ��,
		�Ȳ��ܸı�this��ָ��Ķ���,Ҳ���ܸı�this������ĵ�ַ
	*/
	void foo(int n) const// const ���ε���this  <==> void foo(const CTest * pThis)
	{
		{
			//m_i = n;//error C3490: 'm_i' cannot be modified because it is being accessed through a const object
		}

		{	
			const_cast<CTest*>(this)->m_i = n;//��const CTest * pThis  ָ����ָ������ݲ��ܸı�
			std::cout << "m_i = " << m_i << std::endl;
		}
		
		{
			//myPrint();//error C2662: 'void CTest::myPrint(void)': cannot convert 'this' pointer from 'const CTest' to 'CTest &'
			//this->myP
			//myPrint()�ĺ���ԭ��Ϊ                   <==>  void myPrint(CTest* pThis) 
			//��const��Ա������ thisָ����  const CTest* pThis    �� ��ͨ�ķ�const ��Ա����myPrint �� void myPrint(CTest* pThis)
			//�������Ͳ�ƥ������ const CTest* pThis --> CTest* pThis   ������ from 'const CTest' to 'CTest &'
			const_cast<CTest*>(this)->myPrint();
		}
	}

	/*
		����ͨ�ķ�const ��Ա�����У�this��������һ��ָ�������͵�constָ��,
		�ȼ��� this  <==>  CTest *
		���Ըı�this��ָ���ֵ,�����ܸı�this������ĵ�ַ
	*/
	void myPrint() //<==>     void foo(const CTest* pThis) -->   void myPrint(CTest* pThis)  
	{
		std::cout << "myPrint(��m_i = " << m_i << std::endl;
	}
	int m_i;
};

void test()
{
	CTest obj;
	obj.foo(10);
}
#endif

/*
	static_cast
	�����ȼ�����ʽת����һ������ת�����������ʹ������Ҫ��ȷ��ʽת���ĵط���
	
	�������ڵͷ��յ�ת����
		- ���ͺ͸�����
		- �ַ�������
		- ת�������
		-��ָ��ת��Ϊ�κ�Ŀ�����͵�ָ��

	������������սϸߵ�ת��
		- ��ͬ���͵�ָ��֮�以��ת��
		- ���ͺ�ָ��֮��Ļ���ת��
		- ��ͬ���͵�����֮���ת��
*/
#if 0
class CInt
{
public:
	CInt(int i):m_n(i)
	{
	}
	//ת������c++ plus 416ҳ
	/*
	 ����ת��Ϊ typeName ���ͣ�����
	 operator typeName()
	 1 ת�������������෽��
	 2 ת����������ָ����������
	 3 ת�����������в���

	 typeName ָ����Ҫת���ɵ�����,��˲���Ҫָ���������ͣ�
	 ת���������෽��������Ҫͨ�������������,�Ӷ���֪����Ҫת����ֵ��
	 ��˺�������Ҫ����
	*/
	operator int()
	{
		m_n = 32.123;
		std::cout << m_n << std::endl;
		return m_n;
	}

public:
	int m_n;
};

void test()
{
	int n = 5;
	double dbl = n;
	char ch = 'a';

	//c11 ���͸����� ��ʾ����ʿת��
	dbl = static_cast<double>(n);

	//�������ַ���
	ch = static_cast<char>(n);

	//ת�������

	CInt nObj(1);
	int i = int(nObj);
	int j = nObj;     //����һ��  ���������� ��� ��int ���� �Ҳ� �� CInt ����,��˱������鿴�����Ƿ���ת������ 

	int k = static_cast<int>(nObj);
	std::cout << k << std::endl;

}
#endif
/*
	static_cast���ڻ������������ת�������У�����û������ʱ���ͼ�顣
*/
#if 0
class CFather
{
public:
	CFather() 
	{
		m_nTest = 3;
	}

	virtual void foo()
	{
		std::cout << "CFather()::void foo()" << std::endl;
	}

	int m_nTest;
};

class CSon : public CFather
{
public:
	CSon()
	{
		m_son = 66;
	}

	virtual void foo() override
	{
		std::cout << "CSon::void foo()" << std::endl;
	}
public:
	int m_son;
};
void test()
{
	CFather f;
	CSon s;
	CFather* pFather = &f;
	CSon* pSon = &s;

	pFather = pSon;//���ำֵ������ 
	pFather = static_cast<CFather*>(pSon);//����ת���� ��ȫ ����û������ʱ���ͼ�顣

	//pSon = pFather;//error C2440: '=': cannot convert from 'CFather *' to 'CSon *'
	pSon = static_cast<CSon*>(pFather);//����ת���� ����ȫ ����û������ʱ���ͼ�顣

}
#endif

/*
	dynamic_cast
	���ھ����麯���Ļ�����������֮���ָ������õ�ת����

	-�������߱��麯��
		ԭ��dynamic_cast��  ����ʱ���ͼ��  ����Ҫ����ʱ������Ϣ(RTTI)���������Ϣ�Ǵ洢�����
		�麯����  ��ϵ���ܣ�ֻ��һ���ඨ�����麯�����Ż����麯����

	-����ʱ��飬ת�Ͳ��ɹ��򷵻�һ����ָ��
	-�Ǳ�Ҫ��Ҫʹ��dynamic_cast���ж���ĺ�������

	������ת����ʽ��
	- ����ָ������� ת������ָ�루����ʹ��dynamic_cast��
	- ������ָ������� ת����ָ�루����ʹ��dynamic_cast,���Ǹ��Ƽ�ʹ��static_cast��
*/
#if 0
class CFather
{
public:
	CFather()
	{
		m_nTest = 3;
	}

	virtual void foo()
	{
		std::cout << "CFather()::void foo()" << std::endl;
	}

	int m_nTest;
};

class CSon : public CFather
{
public:
	CSon()
	{
		m_son = 66;
	}

	virtual void foo() override
	{
		std::cout << "CSon::void foo()" << std::endl;
	}
public:
	int m_son;
};
void test()
{
	CFather f;
	CSon s;
	CFather* pFather = &f;
	CSon* pSon = &s;

	//����ת���ࣨ����ȫ��
	//pSon = pFather;
	pSon = dynamic_cast<CSon*>(pFather); //����ʱ�ļ��,���ؿ�
	//pSon->foo(); //����ʱ��pSonΪNULL �������

	//pFather = static_cast<CFather* >(&s); //����ת���࣬��ȫ ����ʹ��
	pFather = dynamic_cast<CFather*>(&s); //����ת����Ҳ����ͨ��dynamic_cast�������Ǳ���� ���ڴ濪��
	
	//��֤ ����ת���� static_cast ���� dynamic_cast���ǿ��Եģ�
	pSon = dynamic_cast<CSon*>(pFather); //����ʱ�ļ��,����ͨ�����ͼ��
	pSon->foo();

}
#endif

/*
	reinterpret_cast
	���ڽ��и��ֲ�ͬ���͵�ת��
		-��ͬ����ָ��֮��
		-��ͬ��������֮��
		-ָ���������ָ�����������֮���ת��
	�����ڴ���,ִ�е������ֽڸ��ƵĲ���
	��������ʽǿת������Ը�
*/
#if 0
void foo() 
{
	cout << "foo()" << endl;
}

void test()
{
	int nTemp = 0;

	// ָ��ת����
	int nTemp1 = reinterpret_cast<int>(&nTemp);
	cout << hex << nTemp1 << '\n';

	//����תָ��
	int* p1 = reinterpret_cast<int*>(nTemp1);
	cout << *p1 << '\n';

	//������תΪָ��
	unsigned int nTemp2 = 0x00500000;
	int* pTemp = reinterpret_cast<int*>(nTemp2);

	//��һ������תΪһ������ָ�벢ת��
	void(*fp1)() = reinterpret_cast<void(*)()>(foo);	//void(*)()
	int(*fp2)() = reinterpret_cast<int(*)()>(fp1);		//int(*)()

	cout << dec << fp2() << '\n';
}
#endif
int main(void)
{
	test();
	system("pause");
	return 0;
}