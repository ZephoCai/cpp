#include<iostream>
#include<string>
#include<stack>
using namespace std;

int priority(char operate);
int compute(string str);
string in2post(string s);

int main() {
	string str;
	cin >> str;
	string str1 = in2post(str);
	cout << "suffix: " << str1 << endl;
	cout << compute(str1) << endl;
	return 0;
}

string in2post(string s) {
	string res;
	stack<char> st;
	int size = s.size();
	for (int i = 0; i < size; i++) {
		if (s[i] != '+' && s[i] != '-' && s[i] != '*' && s[i] != '/' && s[i] != '(' && s[i] != ')')
			res += s[i];
		if (s[i] == '(')
			st.push(s[i]);
		if (s[i] == ')') {
			while (st.top() != '(') {
				res += st.top();
				st.pop();
			}
			st.pop();
		}
		if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') {
			if (st.empty())
				st.push(s[i]);
			else 
			while (1) {
				char tmp = st.top();
				if (priority(s[i]) > priority(tmp)) {
					st.push(s[i]);
					break;
				}
				else {
					res += tmp;
					st.pop();
					if (st.empty()) {
						st.push(s[i]);
						break;
					}
				}
			}
		}
	}
	while (!st.empty()) {
		res += st.top();
		st.pop();
	}
	return res;
}

int compute(string str) {
	stack<double> st;
	int size = str.size();
	for (int i = 0; i < size; i++) {
		if (str[i] != '+' && str[i] != '-' && str[i] != '*' && str[i] != '/')
			st.push(str[i] - '0');
		if (str[i] == '+') {
			double a = st.top();
			st.pop();
			double b = st.top();
			st.pop();
			st.push(a + b);
		}
		if (str[i] == '-') {
			double a = st.top();
			st.pop();
			double b = st.top();
			st.pop();
			st.push(b - a);
		}
		if (str[i] == '*') {
			double a = st.top();
			st.pop();
			double b = st.top();
			st.pop();
			st.push(a * b);
		}
		if (str[i] == '/') {
			double a = st.top();
			st.pop();
			double b = st.top();
			st.pop();
			st.push(b/a);
		}
	}
	return st.top();
}

int priority(char operate) {
	switch (operate) {
	case '+':
	case '-':
		return 2;
	case '*':
	case'/':
		return 3;
	case'(':
	case')':
		return 1;
	default:
		return 0;
	}
}
