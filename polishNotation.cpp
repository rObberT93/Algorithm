#include<iostream>
#include<string>
#include<cmath>
#include<vector>
using namespace std;
string s;
// 数值栈 
vector<int> nums; 
// 运算符栈 
vector<char> ops;
// 存储波兰表达式
vector<char>bolan;

int calc(int l, int r) // 递归求解中缀表达式的值
{
	for (int i = r, j = 0; i >= l; i--) // 寻找未被任何括号包含的最后一个加减号
    {
		if (s[i] == '(') j++;
		if (s[i] == ')') j--;
		if (j == 0 && s[i] == '+') return calc(l, i - 1) + calc(i + 1, r);
		if (j == 0 && s[i] == '-') return calc(l, i - 1) - calc(i + 1, r);
	}
	
	for (int i = r, j = 0; i >= l; i--) // 寻找未被任何括号包含的最后一个乘除号
    {
		if (s[i] == '(') j++;
		if (s[i] == ')') j--;
		if (j == 0 && s[i] == '*') return calc(l, i - 1) * calc(i + 1, r);
		if (j == 0 && s[i] == '/') return calc(l, i - 1) / calc(i + 1, r);
	}
	for (int i = r, j = 0; i >= l; i--) //计算平方
    {
		if (s[i] == '(') j++;
		if (s[i] == ')') j--;
		if (j == 0 && s[i] == '^') return pow(calc(l, i - 1),calc(i + 1, r));
	}
	// 首尾是括号
	if (s[l] == '('&&s[r] == ')') return calc(l + 1, r - 1);
	// 是一个数
	int ans = 0;
	for (int i = l; i <= r; i++) ans = ans * 10 + s[i] - '0';
	return ans;
}

// 后缀表达式转中缀表达式，同时求值，O(n)
// 优先级 
int grade(char op) 
{
	switch (op) {
	case '(':
		return 1;
	case '+':
	case '-':
		return 2;
	case '*':
	case '/':
		return 3;
	}
	return 0;
}

// 处理后缀表达式中的一个运算符 
void calc(char op) 
{
	// 从栈顶取出两个数 
	int y = *nums.rbegin();
	nums.pop_back();
	int x = *nums.rbegin();
	nums.pop_back();
	int z;
	switch (op) {
	case '+':
		z = x + y;
		break;
	case '-':
		z = x - y;
		break;
	case '*':
		z = x * y;
		break;
	case '/':
		z = x / y;
		break;
	}
	// 把运算结果放回栈中 
	nums.push_back(z);	
}

int solve(string s) 
{
	nums.clear();
	ops.clear();
	int top = 0, val = 0;
	for (int i = 0; i < s.size(); i++) 
    {
		if (s[i] >= '0' && s[i] <= '9') 
        {
            bolan.push_back(s[i]);// 扫描到数字，输出该数
			val = val * 10 + s[i] - '0';
			if (s[i+1] >= '0' && s[i+1] <= '9') continue;
			 
			nums.push_back(val);// 遇到数字，入栈
			val = 0;
		}
		// 扫描遇到左括号，将左括号入栈
		else if (s[i] == '(') ops.push_back(s[i]);
		// 遇到右括号，不断取出栈顶元素并且输出，直到栈顶为左括号，弹出左括号舍弃
		else if (s[i] == ')') 
        {
			while (*ops.rbegin() != '(') 
            {
				// 处理后缀表达式的一个运算符 
				calc(*ops.rbegin());
                bolan.push_back(ops.back());
				ops.pop_back();
			}
            bolan.push_back(ops.back());
			ops.pop_back();
		}
        // 遇到运算符，如果栈顶的运算符优先级大于当前扫描到的运算符，就不断取出栈顶的元素，最后将新符号入栈
		else 
        {
			while (ops.size() && grade(*ops.rbegin()) >= grade(s[i])) 
            {
				calc(*ops.rbegin());
                bolan.push_back(ops.back());
				ops.pop_back();
			}
			ops.push_back(s[i]);
		}
	}
	while (ops.size())
    {
		calc(*ops.rbegin());
        bolan.push_back(ops.back());
		ops.pop_back();
	}
	// 后缀表达式栈中最后剩下的数就是答案 
	return *nums.begin();
}
int main()
{
    s="(2+3)-4";
    int res=calc(0,s.length()-1);
    cout<<res<<endl;
    
    int change=solve(s);
    cout<<change<<endl;

    for(int i=0;i<bolan.size();i++) cout<<bolan[i];
    cout<<endl;
    return 0;
}