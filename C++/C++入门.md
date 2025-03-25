## C++入门

## 1. 命名空间

> 在C/C++中，变量、函数和后面要学到的类都是大量存在的，这些变量、函数和类的名称将都存 在于全局作用域中，可能会导致很多冲突。使用命名空间的**目的是对标识符的名称进行本地化， 以避免命名冲突或名字污染**，namespace关键字的出现就是针对这种问题的。
>
> ```cpp
> #include <stdio.h>
>  #include <stdlib.h>
>  int rand = 10;
>  // C语言没办法解决类似这样的命名冲突问题，所以C++提出了namespace来解决
> int main()
>  {
>     printf("%d\n", rand);
>  	return 0;
>  }
>  // 编译后后报错：error C2365: “rand”: 重定义；以前的定义是“函数”
> ```

### 1.1 命名空间的定义

> 定义命名空间，需要使用到**namespace关键字**，后面跟**命名空间的名字**，然**后接一对{}**即可，{} 中即为命名空间的成员。
>
> ```cpp
>  // project是命名空间的名字，一般开发中是用项目名字做命名空间名。
>  // 1. 正常的命名空间定义
> namespace project{
>     // 命名空间中可以定义变量/函数/类型
>     int rand = 10;
>     int Add(int left, int right)
>     {
>         return left + right;
>     }
> 	struct Node{
> 		struct Node* next;
> 		int val;
> 	};
> }
>  //2. 命名空间可以嵌套
>  // test.cpp
> namespace N1 {
> 	int a;
> 	int b;
> 	int Add(int left, int right){
> 		return left + right;
>  	}
> 	namespace N2 {
> 		int c;
> 		int d;
> 		int Sub(int left, int right){
> 			return left - right;
>     	}
> 	}
> }
> 
>  //3. 同一个工程中允许存在多个相同名称的命名空间,编译器最后会合成同一个命名空间中。
> // ps：一个工程中的test.h和上面test.cpp中两个N1会被合并成一个
> // test.h
> namespace N1{
> 	int Mul(int left, int right) {
> 		return left * right;
> 	}
> }
> ```
>
> 注意：**一个命名空间就定义了一个新的作用域**，命名空间中的所有内容都局限于该命名空间中

### 2.2 命名空间的使用

> 命名空间中成员应该怎么使用呢？
>
> 命名空间的使用有三种方式：
>
> - **加命名空间名称及作用域限定符**
>
> ```cpp
> int main() {
> 	printf("%d\n", N::a);
> 	return 0;    
> }
> ```
>
> - **使用using将命名空间中某个成员引入**
>
> ```cpp
> using N::b;
> int main() {
> 	printf("%d\n", N::a);
> 	printf("%d\n", b);
> 	return 0;    
> }
> ```
>
> - **使用using namespace 命名空间名称引入**
>
> ```cpp
> using namespace N;
> int main() {
>     printf("%d\n", a);
>     printf("%d\n", b);
>     return 0;
> }
> ```

## 2. cpp的输入输出

```cpp
#include<iostream>
 // std是C++标准库的命名空间名，C++将标准库的定义实现都放到这个命名空间中
using namespace std;
int main() {
	cout<<"Hello world!!!"<<endl;
	return 0;
}
```

> 说明： 
>
> 1. 使用**cout标准输出对象(控制台)**和**cin标准输入对象(键盘)**时，必须**包含< iostream >头文件**以及按命名空间使用方法使用std。
> 2.  cout和cin是全局的流对象，endl是特殊的C++符号，表示换行输出，他们都包含在包含<  iostream >头文件中。 
> 3. **<<是流插入运算符，>>是流提取运算符。**
> 4. 使用C++输入输出更方便，不需要像printf/scanf输入输出时那样，需要手动控制格式。 C++的输入输出可以自动识别变量类型。 
> 5. 实际上cout和cin分别是ostream和istream类型的对象，>>和<<也涉及运算符重载等知识， 这些知识我们我们后续才会学习，所以我们这里只是简单学习他们的使用。后面我们还有有 一个章节更深入的学习IO流用法及原理。
>
> 注意：早期标准库将所有功能在全局域中实现，声明在.h后缀的头文件中，使用时只需包含对应 头文件即可，后来将其实现在std命名空间下，为了和C头文件区分，也为了正确使用命名空间， 规定C++头文件不带.h；旧编译器(vc 6.0)中还支持<iostream.h>格式，后续编译器已不支持，因此推荐使用<iostream>+std的方式。

## 3. 缺省参数

### 3.1 缺省参数概念

> 缺省参数是**声明或定义函数**时为函数的参数指定一个缺省值。在调用该函数时，如果没有指定实 参则采用该形参的缺省值，否则使用指定的实参。
>
> ```cpp
> void Func(int a = 0)
> {
> 	cout<<a<<endl;
> }
> int main()
> {
> 	Func();     // 没有传参时，使用参数的默认值
> 	Func(10);   // 传参时，使用指定的实参
> 	return 0;	
> }
> ```

### 3.2 缺省参数的分类

> - 全缺省参数
>
> ```cpp
> void Func(int a = 10, int b = 20, int c = 30)
> {
> 	cout << "a = " << a << endl;
> 	cout << "b = " << b << endl;
> 	cout << "c = " << c << endl;
> }
> ```
>
> - 半缺省参数(缺省部分参数)
>
> ```cpp
> void Func2(int a, int b = 10, int c = 20)
> {
> 	cout << "a = " << a << endl;
> 	cout << "b = " << b << endl;
> 	cout << "c = " << c << endl;
> }
> ```
>
> **注意**：
>
> 1. 半缺省参数必须**从右往左依次来给出**，不能间隔着给
> 2. 缺省参数不能在函数声明和定义中同时出现
>
> ```cpp
> //a.h
> void Func(int a = 10);
> 
> // a.cpp
> void Func(int a = 20)
> {
> }
> 
> // 注意：如果声明与定义位置同时出现，恰巧两个位置提供的值不同，那编译器就无法确定到底该用那个缺省值。
> ```
>
> 3. 缺省值必须是常量或者全局变量
> 4. C语言不支持（编译器不支持）

## 4. 函数重载

### 4.1 函数重载概念

> **函数重载**：是函数的一种特殊情况，C++允许在**同一作用域**中声明几个功能类似的**同名函数**，这些同名函数的**形参列表(参数个数 或 类型 或 类型顺序)不同**，常用来处理实现功能类似数据类型不同的问题。
>
> ```cpp
> // 1、参数类型不同
> int Add(int left, int right) {
> 	cout << "int Add(int left, int right)" << endl;
> 
> 	return left + right;
> }
> double Add(double left, double right) {
> 	cout << "double Add(double left, double right)" << endl;
> 
> 	return left + right;
> }
> 
> // 2、参数个数不同
> void f()
> {
> 	cout << "f()" << endl;
> }
> void f(int a) 
> {
> 	cout << "f(int a)" << endl;
> }
> 
> // 3、参数类型顺序不同
> void f(int a, char b)
> {
> 	cout << "f(int a,char b)" << endl;
> }
> void f(char b, int a)
> {
> 	cout << "f(char b, int a)" << endl;
> }
> 
> int main()
> {
> 	Add(10, 20);
> 	Add(10.1, 20.2);
> 
> 	f();
> 	f(10);
> 
> 	f(10, 'a');
> 	f('a', 10);
> 
> 	return 0;
> }
> ```
>
> //注：只是返回值不同无法构成重载

### 4.2 C++是如何支持函数重载的--名字修饰(name Managing)

> **为什么C++支持函数重载，而C语言不支持函数重载呢？**
>
> 在C/C++中，一个程序要运行起来，需要经历以下几个阶段：**预处理、编译、汇编、链接。**
>
> ![image-20241130201547696](../image/image-20241130201547696.png)
>
> 1. 实际项目通常是由多个头文件和多个源文件构成，而通过C语言阶段学习的编译链接，我们 可以知道，【当前a.cpp中调用了b.cpp中定义的Add函数时】，编译后链接前，a.o的目标 文件中没有Add的函数地址，因为Add是在b.cpp中定义的，所以Add的地址在b.o中。那么怎么办呢？
>
> 2. 所以链接阶段就是专门处理这种问题，**链接器看到a.o调用Add，但是没有Add的地址，就 会到b.o的符号表中找Add的地址，然后链接到一起。**
>
> 3. 那么链接时，面对Add函数，链接接器会使用哪个名字去找呢？这里每个编译器都有自己的函数名修饰规则。
>
> 4. **通过下面我们可以看出gcc的函数修饰后名字不变。而g++的函数修饰后变成【_Z+函数长度 +函数名+类型首字母】**。
>
> 	- **采用gcc编译**
>
> 	![image-20241130202107060](../image/image-20241130202107060.png)
>
> 	结论：**在linux下，采用gcc编译完成后，函数名字的修饰没有发生改变**。
>
> 	- **采用C++编译器编译后结果**
>
> 	![image-20241130202417108](../image/image-20241130202417108.png)

### 4.3 extern "C"

> 当我们的库用C++实现，如果我们要求C和C++都能够使用这个库
>
> ```cpp
> extern "C" void* tcmalloc(size_t n);
> ```
>
> extern "C" 表示编译器用C语言的规则来编译

## 5. 引用

### 5.1 引用的概念

> **引用**不是新定义一个变量，**而是给已存在变量取了一个别名**，编译器不会为引用变量开辟内存空间，它和它引用的变量**共用同一块内存空间**。
>
> ```cpp
> int main() {
> 	int a = 1;
> 	int& ra = a; // ra是a的引用，就是a再取了一个名称ra
> 	int& b = a;
> 	int& c = b;
> 
> 	c = 2;
> 
> 	return 0;
> }
> ```
>
> 注意：**引用类型**必须和引用**实体**是**同种类型**的

### 5.2 引用的特性

> 1. 引用必须在**定义的时候初始化**
> 2. 一个变量可以有多个引用
> 3. 一个引用一旦引用了一个实体，就不能再引用其他实体
>
> ```cpp
> void TestRef()
> {
> 	int a = 10;
> 	// int& ra;   // 该条语句编译时会出错
> 	int& ra = a;
> 	int& rra = a;
> 	printf("%p  %p  %p\n", &a, &ra, &rra);
> }
> ```

### 5.3 常引用

> ```cpp
> int main() {
> 	const int a = 0;
> 	//int& b = a; // b的类型是int，编译不通过
> 	//原因：a只读，b的类型是int，可读写
> 	const int& b = a;
> 
> 	int c = 1;
> 	int& d = c;
> 	const int& e = c;//可行
> 	//总结：引用取别名的时候，变量访问的权限可以缩小，不能放大
> 	d = 2;
> 	cout << "c = " << d << endl;// 2
> 	cout << "e = " << e << endl;// 2
> 
> 	return 0;
> }
> ```

### 5.4 类型转换

> ```cpp
> int main() {
>     int i = 0;
>     double db = i; // 隐式类型转换
>     //double& rd = i;  // 不行
>     const double rd = i; // 可以
> }
> ```
>
> 第三行把i赋给db时，是先产生了一个double类型的临时变量，再赋给db
>
> 临时变量具有常性

### 5.5 使用场景

> 1. 做参数
>
> ```cpp
> void swap_c(int* r1, int* r2) {
>     int tmp = *r1;
>     *r1 = *r2;
>     *r2 = tmp;
> }
> 
> void swap_cpp(int& r1, int& r2) {
> 	int tmp = r1;
> 	r1 = r2;
> 	r2 = tmp;
> }
> 
> int main() {
>     int a = 0, b = 1;
>     swap_c(&a, &b);
>     swap_cpp(a, b);
>     
>     return 0;
> }
> ```
>
> 2. 做返回值
>
> ```cpp
> int Count1() {
> 	static int n = 0;
> 	n++;
> 
> 	return n;
> }
> //返回一个临时变量tmp, int tmp = n;
> 
> int& Count2() {
> 	static int n = 0;
> 	n++;
> 
> 	return n;
> }
> //同样返回tmp,tmp是n的别名, int& tmp = n;
> 
> int main() {
>     int& r1 = Count1(); //编译不通过，（临时变量具有常性）
>     const int& r3 = Count1();
>     int& r2 = Count2();
>     
>     return 0;
> }
> ```
>
> ```cpp
> int& Add(int a, int b) {
>     int c = a + b;
>     return c;
> }
> 
> int main() {
>     int& ret = Add(1, 2);
>     Add2(3, 4);
>     cout << " " << ret << endl; //得到的是7
>     
>     return 0;
> }
> ```
>
> 如果返回变量c是一个局部变量时，引用返回是不安全的。
>
> ```cpp
> int& Add(int a, int b) {
>     static int c = a + b;
>     return c;
> }
> // 解决这个问题，static把变量放在静态区，而不是在之前的栈区
> // static 定义只在第一次出现的时候执行，后面就不执行这段代码了
> ```
>
> 总结：一个函数要使用引用返回，返回变量出了这个函数的作用域还存在，就可以使用引用返回，否则就是不安全的。
>
> - 使用引用返回的好处：少创建一个临时对象，提高效率
>
> - ...

### 5.6 引用和指针的区别

> 在**语法概念**上引用就是一个别名，没有独立空间，和其引用实体共用同一块空间。
>
> ```cpp
> int main()
> {
> 	int a = 10;
> 	int& ra = a;
> 	cout << "&a = " << &a << endl;
> 	cout << "&ra = " << &ra << endl;
> 	return 0;
> }
> ```
>
> 在**底层实现**上实际是有空间的，因为**引用是按照指针方式来实现**的。
>
> 引用和指针的不同点：
>
> 1. 引用概念上定义一个变量的别名，指针存储一个变量地址。
> 2. **引用**在定义时**必须初始化**，指针没有要求
> 3. **引用**在初始化时引用一个实体后，**就不能再引用其他实体**，而指针可以在任何时候指向**任何一个同类型实体**
> 4. 没有**NULL**引用，但有**NULL指针**
> 5. **在sizeof中含义不同**：引用结果为引用类型的大小，但指针始终是地址空间所占字节个数(32 位平台下占4个字节)
> 6. 引用自加即引用的实体增加1，指针自加即指针向后偏移一个类型的大小
> 7. **有多级指针，但是没有多级引用**
> 8. 访问实体方式不同，**指针需要显式解引用，引用编译器自己处理**
> 9. **引用比指针使用起来相对更安全**

## 6. 内联函数

### 6.1 概念

> 当我们在频繁调用某一个函数的时候，由于需要不断建立栈帧，所以是有消耗的。
>
> 如何解决？
>
> 1. C语言使用宏函数
> 2. C++使用内联函数
>
> ```cpp
> void Swap(int& a, int& b) {
>     int tmp = a;
>     a = b;
>     b = tmp;
> }
> 
> inline void Swap(int& a, int& b) { //在调用的地方展开
>     int tmp = a;
>     a = b;
>     b = tmp;
> }
> 
> int main() {
>     int a = 0, b = 2;
>     Swap(a, b);
>     
>     return 0;
> }
> ```
>
> 以**inline修饰**的函数叫做内联函数，**编译时**C++编译器会在**调用内联函数的地方展开**，没有函数调用建立栈帧的开销，内联函数提升程序运行的效率。

### 6.2 特性

> 1. inline是一种以**空间换时间**的做法，如果编译器将函数当成内联函数处理，在**编译阶段，会用函数体替换函数调用**，
>   缺陷：可能会使目标文件变大，优势：少了调用开销，提高程序运行效率。
> 2. **inline对于编译器而言只是一个建议，不同编译器关于inline实现机制可能不同**，一般建议：**将函数规模较小**(即函数不是很长，具体没有准确的说法，取决于编译器内部实现)、**不是递归、且频繁调用**的函数采用inline修饰，否则编译器会忽略inline特性。
> 3. inline不能声明和定义分离，分离会导致链接错误。因为内联函数没有地址，链接就找不到。

## 7. auto关键字(C++ 11)

### 7.1 auto的基础使用

```cpp
int main() {
	int a = 0;
	auto b = a; //b的类型是根据a的类型推导的
	auto& c = a;
	auto d = &a;

	cout << typeid(a).name() << endl;
	cout << typeid(b).name() << endl;

	return 0;
}
```

### 7.2 auto的用法

> 1. **auto与指针和引用结合起来使用**
> 	**用auto声明指针类型时，用auto和auto*没有任何区别，但用auto声明引用类型时则必须 加&**
>
> ```cpp
> int main()
> {
> 	int x = 10;
> 	auto a = &x;
> 	auto* b = &x;
> 	auto& c = x;
> 	cout << typeid(a).name() << endl;
> 	cout << typeid(b).name() << endl;
> 	cout << typeid(c).name() << endl;
> 	*a = 20;
> 	*b = 30;
> 	c = 40;
> 
> 	return 0;
> }
> ```
>
> 2. **在同一行定义多个变量**
> 	**当在同一行声明多个变量时，这些变量必须是相同的类型，否则编译器将会报错，因为编译 器实际只对第一个类型进行推导，然后用推导出来的类型定义其他变量。**
>
> ```cpp
> void TestAuto()
> {
> 	auto a = 1, b = 2;
> 	auto c = 3, d = 4.0;  // 该行代码会编译失败，因为c和d的初始化表达式类型不同
> }
> ```

### 7.3 auto不能推导的场景

> 1. **auto不能作为函数的参数**
> 2. **auto不能直接用来声明数组**
> 3. 为了避免与C++98的



## 8. 基于范围的for循环(C++ 11)

### 8.1 范围for的语法

> 对于一个**有范围的集合**而言，由程序员来说明循环的范围是多余的，有时候还会容易犯错误。因此C++11中引入了基于范围的for循环。**for循环后的括号由冒号“  ：”分为两部分：第一部分是范围内用于迭代的变量，第二部分则表示被迭代的范围。**
>
> ```cpp
> void TestFor()
> {
> 	int array[] = { 1, 2, 3, 4, 5 };
> 	for (int i = 0; i < sizeof(array) / sizeof(array[0]); ++i)
> 		array[i] *= 2;
> 	for (int* p = array; p < array + sizeof(array) / sizeof(array[0]); ++p)
> 		cout << *p << endl;
> }
> 
> 
> void TestFor()
> {
> 	int array[] = { 1, 2, 3, 4, 5 };
> 	for (auto& e : array)
> 		e *= 2;
> 	for (auto e : array)
> 		cout << e << " ";
> 	return 0;
> }
> ```

### 8.3 范围for的使用条件

> 1. **for循环迭代的范围必须是确定的**
>
> 	**对于数组而言，就是数组中第一个元素和最后一个元素的范围**；对于类而言，应该提供 begin和end的方法，begin和end就是for循环迭代的范围。
>
> 2. **迭代的对象要实现++和==的操作。**

## 9. 指针空值

```cpp
int main() {
    // C
    int* p = NULL;
    
    //C++ 11 中，推荐像下面这样用
    int* p2 = nullptr;
}
```

