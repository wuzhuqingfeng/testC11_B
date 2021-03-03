#include <iostream>
using namespace std;

#include <iostream>
#include <vector>
#include <list>
/*
C++ 11 引入了 `auto` 和 `decltype` 这两个关键字实现了类型推导
 `auto` 不能用于函数传参，因此下面的做法是无法通过编译的（考虑重载的问题，我们应该使用模板）
 `auto` 还不能用于推导数组类型
*/
int test()
{
    //普通的数组, 一旦申请，不能再扩增
    int ary[5] = { 1, 2, 3, 4, 5 };
    //auto muAry = arr;//error

	int* pAry = new int[5];
	for (int i = 0; i < sizeof(ary); i++) {
		std::cout << ary[i] << std::endl;
	}

    //容器---动态数组 不用指定其大小，会根据数组当前的使用情况进行动态的扩容
    //模板类型
    std::vector<int> v;

    //插入数据
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);

    //for (int i = 0; i < v.size(); i++){
    //    std::cout << v[i] << std::endl;
    //}

    //使用迭代器的方式遍历数组
    std::vector<int>::iterator it; //迭代器，模板类中的内部类
    for (it = v.begin(); it != v.end(); it++) {
        std::cout << *it << std::endl; //* it 来访问模板类的具体的值
    }

    //统一的遍历方式 链表
    std::list<std::string> l;
    l.push_back("hello1");
    l.push_back("hello2");
    l.push_back("hello3");

    //for (std::list<std::string>::iterator it2 = l.begin(); it2 != l.end(); it2++) {
    //    std::cout << (*it2).c_str() << std::endl; //* it 来访问模板类的具体的值
    //}

    //auto 类型推导关键字
    for (auto it2 = l.begin(); it2 != l.end(); it2++) {
        std::cout << (*it2).c_str() << std::endl; //* it 来访问模板类的具体的值
    }


    //for(std::string str : l){
    //    std::cout << str.c_str() << std::endl;
    //}

    for (auto str : l) {
        std::cout << str.c_str() << std::endl;
    }

	auto i = 5;             // i 被推导为 int
    auto arr = new int(10); // arr 被推导为 int *

    return 0;
}


int main(void)
{
	test();
	system("pause");
	return 0;
}