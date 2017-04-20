#ifndef INFIX2POSTFIX_H_INCLUDED
#define INFIX2POSTFIX_H_INCLUDED
#include <iostream>
#include <stack>
#include <string>

using namespace std;
//--------- ����׺���ʽת��Ϊ��׺���ʽ����׺���ʽ�Ǳ������������ּ���ı����ʽ -----------
//����׺���ʽexpת��Ϊ��׺���ʽ
string postfix(string exp);
//��������
void showRPN(){
	string infixExp;	//��׺���ʽ
	cout << "NOTE: Enter # for infix expression to stop.\n";
	for (;;){
		cout << "\nInfix expression: ";
		getline(cin, infixExp);

		if (infixExp == "#") break;

		cout << "Postfix expression is: " << postfix(infixExp) << endl;
	}
}
//����׺���ʽexpת��Ϊ��׺���ʽ
string postfix(string exp){
	char token,	//exp�е��ַ�
		topToken;	//opStackջ���ı��
	stack<char> opStack;	//�����ջ
	string postfixExp;	//��׺���ʽ
	const string BLANK = " ";
	for (unsigned int i = 0; i < exp.length(); i++)
	{
		token = exp[i];
		switch (token)
		{
		case ' ': break;	//�����κ���--�����հ��ַ�
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
		default:	//������
			postfixExp.append(BLANK + token);
			for (;;){
				if (!isalnum(exp[i + 1])) break;	//��ʶ����β
				i++;
				token = exp[i];
				postfixExp.append(1, token);
			}
		}
	}
	//����ջ��ʣ��������
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
//����׺���ʽ�ļ���
class postfixEval{
public:
    postfix(){}
    //���ú�׺���ʽ
    void setPostfixExp(const string& postfixExp){postfix = postfixExp;};
    //�����׺���ʽ
    int evaluate();
private:
    string postfix; //����ĺ�׺���ʽ
    stack<int> stk; //��Ų������Ķ�ջ
    void getOperands(int& left, int& right);    //�Ӷ�ջ��ȡ�����Ҳ�����
    int compute(int left, int right, char op) const;    //������ʽ��left op right����ֵ
    bool isOperator(char ch) const; //�ж��Ƿ�Ϊ�����
};

// �����׺���ʽ��������ֵ
int postfixEval::evaluate()
{
	int left, right, expValue;
	char ch;
	unsigned int i;
	// ɨ���׺���ʽֱ�����ʽ����
	for (i=0; i < postfix.length(); i++)
	{
		// ȡ�õ�ǰ�ַ�
        ch = postfix[ i ];
        //������ѹ���������ջ
		if ( isdigit(ch) )
			stk.push(ch - '0');
		// ��Ϊ�������ȡ����ǰ����������ִ�����㣬�������ѹ�������ջ
		else if (isOperator(ch))
		{
			getOperands(left, right);
			stk.push(compute(left, right, ch));
		}// end if
	}// end for
	// ��������ջ����Ϊ����������
	expValue = stk.top();
	stk.pop();
	return expValue;
}
// �Ӷ�ջ��ȡ�����Ҳ�����
void postfixEval::getOperands(int& left, int& right)
{
    // ȡ���Ҳ�����
	right = stk.top();
	stk.pop();
    // ȡ���������
	left = stk.top();
	stk.pop();
}

// ���� "left op right"
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
					   cout << "postfixEval���ֳ�0���� " << endl;
					value = left / right;
					break;
		case '%':	if (right == 0)
					   cout << "postfixEval���ֳ�0����" << endl;
					value = left % right;
					break;
		case '^':	if (left == 0 && right == 0)
					   cout << "postfixEval����δ�����0^0 ����" << endl;
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

// �ж��Ƿ�Ϊ�����
bool postfixEval::isOperator(char ch) const
{
	return ch == '+' || ch == '-' || ch == '*' ||
           ch == '/' || ch == '%' || ch == '^';
}
#endif // INFIX2POSTFIX_H_INCLUDED
