#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stack>
#include <math.h>
#include <iostream>
#define N 100000
#define OPERATOR 0
#define NUMBER 1
#define BRACKET 2
#define eps 1e-9
using std::cin, std::cout, std::endl;
using std::stack, std::pow;
char str[N + 5];
int n;
void illegal()
{
	throw "ILLEGAL";
	// exit(0);
}
bool isDigit(char ch)
{
	return ch >= '0' && ch <= '9';
}
double stringToDouble(int &l, int R)
{
	int Neg = 1;
	double result = 0.0;
	if (str[l] == '-')
		Neg = -1, l++;
	if (l > R || !isDigit(str[l]))
		illegal();
	while (l <= R && isDigit(str[l]))
		result = result * 10 + (str[l++] - '0');
	if (l > R)
		return Neg * result;
	if (str[l] == '.')
	{
		l++;
		if (l > R || !isDigit(str[l]))
			illegal();
		double fractionalPart = 0.0;
		double divisor = 10.0;
		while (l <= R && isDigit(str[l]))
		{
			fractionalPart += (str[l++] - '0') / divisor;
			divisor *= 10.0;
		}
		result += fractionalPart;
		if (l > R)
			return Neg * result;
	}
	if (str[l] == 'e' || str[l] == 'E')
	{
		l++;
		int expNeg = 1;
		if (l <= R && str[l] == '-')
		{
			expNeg = -1;
			l++;
		}
		if (l > R || !isDigit(str[l]))
			illegal();
		int exponent = 0;
		while (l <= R && isDigit(str[l]))
			exponent = exponent * 10 + (str[l++] - '0');
		result *= pow(10, expNeg * exponent);
	}
	return Neg * result;
}
double cal(double a, double b, char ch)
{
	if (ch == '+')
		return a + b;
	if (ch == '-')
		return a - b;
	if (ch == '*')
		return a * b;
	if (ch == '/')
	{
		if (abs(b) < eps)
			illegal();
		return a / b;
	}
	illegal();
}
void print(auto &num, auto &op)
{
	printf("num-stack is: ");
	while (!num.empty())
	{
		printf("%.2lf ", num.top());
		num.pop();
	}
	printf("\nop-stack is: ");
	while (!op.empty())
	{
		printf("%c ", op.top());
		op.pop();
	}
	exit(0);
}
void update(auto &num, auto &op)
{
	if (num.size() < 2 || op.empty())
		illegal();
	double a = num.top();
	num.pop();
	double b = num.top();
	num.pop();
	num.push(cal(b, a, op.top()));
	op.pop();
}
double calculate(int l, int r)
{
	stack<double> num;
	stack<char> op;
	while (!num.empty())
		num.pop();
	while (!op.empty())
		op.pop();
	int top = 0;
	int state = OPERATOR;
	for (int i = l; i <= r; i++)
	{
		if (str[i] == '(')
		{
			if (state != OPERATOR)
				illegal();
			int now = i;
			top++;
			while (top > 0 && (++now) <= r)
			{
				if (str[now] == '(')
					top++;
				else if (str[now] == ')')
					top--;
			}
			if (top > 0)
				illegal();
			num.push(calculate(i + 1, now - 1));
			i = now;
			state = BRACKET;
		}
		else if (str[i] == ')')
			illegal();
		else if (state == OPERATOR)
		{
			num.push(stringToDouble(i, r));
			i--;
			state = NUMBER;
		}
		else
		{
			if (str[i] == '+' || str[i] == '-')
				while (!op.empty() && (op.top() == '*' || op.top() == '-'))
					update(num, op);

			op.push(str[i]);
			state = OPERATOR;
		}
	}
	while (!op.empty())
		update(num, op);
	if (num.size() > 1)
		illegal();

	return num.top();
}
int main()
{
	freopen("main.in", "r", stdin);
	freopen("main.out", "w", stdout);
	while (!feof(stdin))
	{
		fgets(str + 1, sizeof(str), stdin);
		int n = strlen(str + 1);
		if (str[n] == '\n')
			str[n--] = 0;
		else
			str[n + 1] = 0;
		try
		{
			printf("Answer = %.2lf\n", calculate(1, n));
		}
		catch (const char *err)
		{
			printf("%s\n", err);
		}
	}
	return 0;
}