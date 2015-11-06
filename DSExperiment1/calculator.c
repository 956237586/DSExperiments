// 我真诚地保证：

// 我自己独立地完成了整个程序从分析、设计到编码的所有工作。
// 如果在上述过程中，我遇到了什么困难而求教于人，那么，我将在程序实习报告中
// 详细地列举我所遇到的问题，以及别人给我的提示。

// 在此，我感谢 XXX, …, XXX对我的启发和帮助。下面的报告中，我还会具体地提到
// 他们在各个方法对我的帮助。

// 我的程序里中凡是引用到其他程序或文档之处，
// 例如教材、课堂笔记、网上的源代码以及其他参考书上的代码段,
// 我都已经在程序的注释里很清楚地注明了引用的出处。

// 我从未没抄袭过别人的程序，也没有盗用别人的程序，
// 不管是修改式的抄袭还是原封不动的抄袭。

// 我编写这个程序，从来没有想过要去破坏或妨碍其他计算机系统的正常运转。

// 黄永亮

/*/
文件名称：calculator.c
项目名称：DSExperiment1
创建者：黄永亮
创建时间：201.9.12
最后修改时间：2015.9.17
功能：计算器程序主文件
文件中的函数名称和简单功能描述：见下面
文件中定义的全局变量和简单功能描述：见下面
文件中用到的他处定义的全局变量及其出处：无
与其他文件的依赖关系：calculator.h
//*/


#include "calculator.h"

/*/
函数名称：calculator
函数功能描述：计算器入口函数
返回值（如果有的话）：成功返回1，失败返回-1
函数的输入参数：(可选)要运算的表达式字符串，传入NULL将要求用户输入
//*/
int calculator(char * string) {
	char* s = NULL;
	char* p = NULL;
	Stack* numbers = createStack(MAXSIZE);
	Stack* operators = createStack(MAXSIZE);
	double t;
	
	if (numbers == NULL	|| operators == NULL) {
		errorWarning("初始化错误");
		return -1;
	}

	if (string == NULL) {
		p = s = (char*)malloc(MAXSIZE);
		if (s == NULL) {
			errorWarning("初始化错误");
			return -1;
		}
		printf("\n请输入表达式：");
		scanf("%[^\n]%*c", s);
	} else {
		s = string;
	}

	printf("\n您输入的表达式是:\n%s\n", s);
	s = preTreat(&s);
	//printf("preTreated\n%s\n", s);

	if (string == NULL)free(p);
	
	if (!check(s)) {
		errorWarning("输入错误");
		return -1;
	}

	p = s;
	while (*p != '#') {
		if (isOperator(*p)) {//如果是运算符
			if (*p == ')') {
				while (decode(seek(operators)) != '(')
					merge(numbers, operators);
				pop(operators, NULL);
				//printf("pop operator (\n");
			} else {
				if (*p != '(')
					while (canCalculate(*p, operators))//如果可计算
						merge(numbers, operators);
				push(operators, encode(*p));
				//printf("push operator %c\n\n", *p);
			}
			p++;
		} else if (isNumber(*p)) {//如果是运算数
			t = parseNum(&p);
			push(numbers, t);
		}
	}
	while (!isEmpty(operators))
		merge(numbers, operators);
	pop(numbers, &t);

	if (t - (int)t == 0)printf("\n结果是 %d\n", (int)t);
	else printf("\n结果是 %.5lf\n", t);

	//system("pause");
	return 1;
}


/*/
函数名称：check
函数功能描述：输入合法性检查
函数调用之前的预备条件：必须是经过预处理的表达式字符串
返回值（如果有的话）：符合条件返回1，否则返回0
函数的输入参数：要检查的字符串
//*/
int check(char* s) {
	char* p = s;
	int t = 0;//括号判定

	//检查开头第一位是否为运算符
	if ((*p != '(' && isOperator(*p))||
		*p == '.')
		return 0;

	//终结符检查
	while (*p != 0 && *p != '#')p++;
	if (*p == 0 || *(p + 1) != 0)return 0;
	//循环退出的条件只有两个，等于0或者#
	//这里借用了下代码短路，如果*p等于0满足
	//后面的条件语句就不会被执行，不用担心指针非法访问

	//检查结尾是否为运算符
	p--;
	if (*p != ')' && isOperator(*p)||
		*p == '.')
		return 0;
	p = s;

	//括号匹配检查
	while (*p != 0) {
		if (*p == '(')t++;
		else if (*p == ')') {
			if (--t < 0)	return 0;
		}
		p++;
	}
	if (t != 0)return 0;;
	p = s;

	//括号合法性检查 )(
	while (*p != 0) {
		if (*p == ')' && *(p + 1) == '(')
			return 0;
		p++;
	}
	p = s;

	//检查运算符左右是否没有数字
	//能执行到这说明肯定有终结符
	//并且开头和结尾都是合法的，没有运算符出现
	while (*p != '#') {
		if (isOperator(*p) && *p != '('
			&& *p != ')') {
			if (!isNumber(*(p - 1))
				&& *(p - 1) != ')')
				return 0;
			if (!isNumber(*(p + 1))
				&& *(p + 1) != '(')
				return 0;
		}
		p++;
	}

	return 1;
}

/*/
函数名称：preTreat
函数功能描述：表达式字符串预处理，过滤无效字符后过滤重复的小数点
函数调用之前的预备条件：有带有终结符0的字符串
返回值（如果有的话）：成功返回1，失败返回0
函数的输入参数：带有终结符0的字符串的双重指针
//*/
char* preTreat(char** s) {
	char* ps = *s;
	char* t1 = (char*)malloc(MAXSIZE);
	char* t2 = (char*)malloc(MAXSIZE);
	char* pt1 = t1;
	char* pt2 = t2;

	while (*ps != 0) {
		if ((isOperator(*ps) || isNumber(*ps)
			|| *ps == '.' || *ps == '#')) {
			*pt1++ = *ps;
		}
		ps++;
	}
	*pt1 = 0;
	pt1 = t1;

	while (*pt1 != 0) {
		if (*pt1 == '.' && *(pt1 + 1) == '.')pt1++;
		else *pt2++ = *pt1++;
	}
	*pt2 = 0;
	free(t1);
	*s = t2;
	return t2;
}


/*/
函数名称：calcu
函数功能描述：默认传给入口函数NULL参数，让用户手动输入表达式
函数调用之前的预备条件：无
返回值（如果有的话）：成功返回1，失败返回-1
//*/
int calcu() {
	return calculator(NULL);
}


/*/
函数名称：errorWarning
函数功能描述：错误警告
函数调用之前的预备条件：无
返回值（如果有的话）：无
函数的输入参数：错误警告语句
//*/
void errorWarning(char* warning) {
	printf("%s\n\n", warning);
	//system("pause");
}


/*/
函数名称：isOperator
函数功能描述：判断字符是否为合法操作符
函数调用之前的预备条件：无
返回值（如果有的话）：是返回1，不是返回0
函数的输入参数：要判断的字符c
//*/
int isOperator(char c) {
	return c == '+' || c == '-' || c == '*'
		|| c == '/' || c == '(' || c == ')';
}


/*/
函数名称：isNumber
函数功能描述：判断字符是否为数字
函数调用之前的预备条件：无
返回值（如果有的话）：是返回1，不是返回0
函数的输入参数：要判断的字符c
//*/
int isNumber(char c) {
	return c >= '0' && c <= '9';
}

/*/
函数名称：encode
函数功能描述：操作符编码，方便入栈
函数调用之前的预备条件：字符c必须经过合法性检查
返回值（如果有的话）：编码结果
函数的输入参数：要编码的字符c
//*/
double encode(char c) {
	double t;
	switch (c) {
	case '+':t = 0; break;
	case '-':t = 1; break;
	case '*':t = 2; break;
	case '/':t = 3; break;
	case '(':t = 4; break;
	case ')':t = 5; break;
	}
	return t;
}


/*/
函数名称：decode
函数功能描述：操作符解码，方便出栈后比较
函数调用之前的预备条件：字符c必须是经过编码的值
返回值（如果有的话）：解码结果
函数的输入参数：要解码的字符c
//*/
char decode(double d) {
	char c;
	switch ((int)d) {
	case 0:c = '+'; break;
	case 1:c = '-'; break;
	case 2:c = '*'; break;
	case 3:c = '/'; break;
	case 4:c = '('; break;
	case 5:c = ')'; break;
	}
	return c;
}


/*/
函数名称：priority
函数功能描述：判断运算优先级
函数调用之前的预备条件：字符c必须是经过合法性检测
返回值（如果有的话）：优先级
函数的输入参数：要判断的运算符c
//*/
int priority(char c) {
	int t;
	switch (c) {
	case '(':t = 0; break;
	case '+':
	case '-':t = 1; break;
	case '*':
	case '/':t = 2; break;
	}
	return t;
}

/*/
函数名称：merge
函数功能描述：进行一次运算
函数调用之前的预备条件：可以进行一次合法运算
返回值（如果有的话）：无
函数的输入参数：操作数栈和操作符栈
//*/
void merge(Stack* numbers, Stack* operators) {
	double num1, num2, t;
	//printf("\n");
	pop(operators, &t);
	//printf("pop operator %c\n\n", decode(t));
	pop(numbers, &num2);//这里要注意，先pop出来的是num2
	pop(numbers, &num1);//如果写反了减法和除法就会出错
	t = calculate(decode(t), num1, num2);
	push(numbers, t);
}

/*/
函数名称：calculate
函数功能描述：进行一次实际运算
函数调用之前的预备条件：运算符经过合法检查
返回值（如果有的话）：运算结果
函数的输入参数：2个操作数和操作符
//*/
double calculate(char operate, double num1, double num2) {
	double t;
	switch (operate) {
	case '+':t = num1 + num2; break;
	case '-':t = num1 - num2; break;
	case '*':t = num1 * num2; break;
	case '/':
		if (num2 != 0)t = num1 / num2;
		else errorWarning("除数不能为0");
		break;
	}
	return t;
}


/*/
函数名称：parseNum
函数功能描述：从字符串解析一个操作数
函数调用之前的预备条件：字符串经过预处理和合法性检查
返回值（如果有的话）：解析结果
函数的输入参数：要识别的字符串双重指针
//*/
double parseNum(char** s) {
	double t = 0;
	sscanf(*s, "%lf", &t);
	//这里如果有多个小数点，认为用户输入的是对的
	//只看一个，多余的小数点后面数字部分自动丢弃
	while (isNumber(**s) || **s == '.')(*s)++;
	return t;
}

/*/
函数名称：canCalculate
函数功能描述：与当前栈顶元素比较优先级
函数调用之前的预备条件：c是合法运算符
返回值（如果有的话）：可进行合法计算返回1，否则返回0
函数的输入参数：要入栈的运算符，运算符栈
//*/
int canCalculate(char c, Stack* operators) {
	return !isEmpty(operators) &&
		priority(c) <= priority(decode(seek(operators)));
}