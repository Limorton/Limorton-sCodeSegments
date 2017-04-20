#ifndef INFIX2POSTFIX_H_INCLUDED
#define INFIX2POSTFIX_H_INCLUDED
#include <iostream>
#include <stack>
#include <string>

using namespace std;
//--------- 将中缀表达式转换为后缀表达式，后缀表达式是编译器进行数字计算的表达形式 -----------
//将中缀表达式exp转换为后缀表达式
string postfix(string exp);
//驱动程序
void showRPN(){
	string infixExp;	//中缀表达式
	cout << "NOTE: Enter # for infix expression to stop.\n";
	for (;;){
		cout << "\nInfix expression: ";
		getline(cin, infixExp);

		if (infixExp == "#") break;

		cout << "Postfix expression is: " << postfix(infixExp) << endl;
	}
}
//将中缀表达式exp转换为后缀表达式
string postfix(string exp){
	char token,	//exp中的字符
		topToken;	//opStack栈顶的标记
	stack<char> opStack;	//运算符栈
	string postfixExp;	//后缀表达式
	const string BLANK = " ";
	for (unsigned int i = 0; i < exp.length(); i++)
	{
		token = exp[i];
		switch (token)
		{
		case ' ': break;	//不做任何事--跳过空白字符
		case '(':	opStack.push(token); break;
		case ')':	for (;;){
			assert(!opStack.empty());
			topToken = opStack.top();
			opStack.pop();
			if (topToken == '(') break;
			postfixExp.append(BLANK + topToken);
		}
					break;
		case '+':
		case '-':
		case '*':
		case '/':
		case '%':	for (;;){
			if (opStack.empty() || opStack.top() == '(' || (token == '*' ||
				token == '/' || token == '-')){
				opStack.push(token);
				break;
			}
			else{
				topToken = opStack.top();
				opStack.pop();
				postfixExp.append(BLANK + topToken);
			}
		}
					break;
		default:	//操作数
			postfixExp.append(BLANK + token);
			for (;;){
				if (!isalnum(exp[i + 1])) break;	//标识符结尾
				i++;
				token = exp[i];
				postfixExp.append(1, token);
			}
		}
	}
	//弹出栈中剩余的运算符
	for (;;){
		if (opStack.empty()) break;
		topToken = opStack.top();
		opStack.pop();
		if (topToken != '('){
			postfixExp.append(BLANK + topToken);
		}
		else{
			cout << "*** Error in infix expression ***\n";
			break;
		}
	}
	return postfixExp;
}
//将后缀表达式的计算
class postfixEval{
public:
    postfix(){}
    //设置后缀表达式
    void setPostfixExp(const string& postfixExp){postfix = postfixExp;};
    //计算后缀表达式
    int evaluate();
private:
    string postfix; //待求的后缀表达式
    stack<int> stk; //存放操作数的堆栈
    void getOperands(int& left, int& right);    //从堆栈中取得左右操作数
    int compute(int left, int right, char op) const;    //计算表达式“left op right”的值
    bool isOperator(char ch) const; //判断是否为运算符
};

// 计算后缀表达式并返回其值
int postfixEval::evaluate()
{
	int left, right, expValue;
	char ch;
	unsigned int i;
	// 扫描后缀表达式直至表达式结束
	for (i=0; i < postfix.length(); i++)
	{
		// 取得当前字符
        ch = postfix[ i ];
        //操作数压入操作数堆栈
		if ( isdigit(ch) )
			stk.push(ch - '0');
		// 若为运算符则取出其前两个操作数执行运算，并将结果压入操作数栈
		else if (isOperator(ch))
		{
			getOperands(left, right);
			stk.push(compute(left, right, ch));
		}// end if
	}// end for
	// 操作数的栈顶即为最后的运算结果
	expValue = stk.top();
	stk.pop();
	return expValue;
}
// 从堆栈中取得左右操作数
void postfixEval::getOperands(int& left, int& right)
{
    // 取得右操作数
	right = stk.top();
	stk.pop();
    // 取得左操作数
	left = stk.top();
	stk.pop();
}

// 计算 "left op right"
int postfixEval::compute(int left, int right, char op) const
{
	int value;
	switch(op)
	{
		case '+':	value = left + right;
					break;
		case '-':	value = left - right;
					break;
		case '*':	value = left * right;
					break;
		case '/':	if (right == 0)
					   cout << "postfixEval出现除0错误 " << endl;
					value = left / right;
					break;
		case '%':	if (right == 0)
					   cout << "postfixEval出现除0错误" << endl;
					value = left % right;
					break;
		case '^':	if (left == 0 && right == 0)
					   cout << "postfixEval出现未定义的0^0 现象" << endl;
					value = 1;
					while (right > 0)
					{
						value *= left;
						right--;
					}
					break;
	}//end switch
	return value;
}

// 判断是否为运算符
bool postfixEval::isOperator(char ch) const
{
	return ch == '+' || ch == '-' || ch == '*' ||
           ch == '/' || ch == '%' || ch == '^';
}
#endif // INFIX2POSTFIX_H_INCLUDED
