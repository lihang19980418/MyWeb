#include"pch.h"
#include<iostream>
#include<cstring>
#include<vector>
#include<stack>
#include<iomanip>
#define max 100
using namespace std;
int nump;//文法行数
#define max 100
int k;
static vector<vector<char>> grammer;//原文法
static vector<vector<char>> product;//处理后的文法
static vector<char> non_terminal;//非终结符
static vector<char> terminal;//终结符
static vector<char> sentence;//输入句子
//static char sentence[max];
static vector<char> remain;//剩余串
//static char relation[6][6];
static vector<vector<char>> relation;
//stack s;
/*
vector<generator> first;//first集
vector<generator> last;//last集
*/
char s[max];
static int M;
static int first[4][7];
static int last[4][7];
//static vector<vector<int>> first;//first集
//static vector<vector<int>> last;//last集
//static vector<vector<char>> relation;//优先算符表
int numf = 0;//非终结符计数
int num = 0;//终结符计数
int judge(char *p, int k, char *psc);
int find_terminal(char s);//获取终结符所在位置函数
int find_non_terminal(char s);//获取非终结符所在位置函数
void transport(int n);//处理原文法
int judge_non(char s);//判断一个字符是不是非终结符
void terminal_display();//终结符显示
void non_terminal_display();//非终结符显示
void product_display();//变换文法显示
void creatrelation();//创建优先矩阵
//char charcomplete(char a, char b);//只显示终结符
void transport(int n);
void firstvt();
void lastvt();
void creatrelation();
void relationdisplay();
//void scan();//规约过程
//void creatremain();//显示剩余子串
//char charcomplete(char a,char b);
//void relationtrans();
int main()
{
	int nump;
	cout << "输入文法总行数" << endl;
	cin >> nump;
	cout << "请输入文法" << endl;
	for (int i = 0;i < nump;i++)
	{
		char ch;

		vector<char> vec;
		cin >> ch;
		while (ch != '#')
		{
			if (ch != ' ')
				vec.push_back(ch);
			cin >> ch;
		}
		grammer.push_back(vec);
		//product.push_back(vec);
	}
	cout << "原文法是" << endl;
	vector<vector<char>>::iterator it;//it是一个vector
	for (it = grammer.begin();it != grammer.end();it++)
	{
		for (vector<char>::iterator it_1 = it->begin(); it_1 != it->end(); it_1++) {
			cout << *it_1;
		}
		cout << endl;
	}

	transport(nump);
	terminal_display();
	non_terminal_display();
	product_display();
	//numf = non_terminal.size();
	//num = terminal.size();
	firstvt();
	lastvt();
	creatrelation();
	//relationtrans();
	relationdisplay();
	//int i, j;
	int t;
	//int k;
	/*cout << "输入一个字符串" << endl;
	char ch1;
	cin >> ch1;
	while (ch1 != '*')
	{
		sentence.push_back(ch1);
		cin >> ch1;
	}

	//cin.getline(sentence,10);
	cout << "步骤" << endl;
	k = 0;
	s[k] = '#';
	s[k + 1] = '\0';
	//j = strlen(sentence);
	j = sentence.size();
	for (t = 0;t < j;t++)
	{
		remain.push_back(sentence[t]);
	}
	remain.push_back('\0');
	scan();*/
	int  k;                   //栈顶指针
	char s[30] = { '\0' };      //分析栈
	char *ss;
	char in_c[50] = { '\0' };   //输入串
	char *psc;                //指向当前输入符号
	int  j;
	char q;
	int  flag;
	int  n;
	while (1)
	{


		cout << "输入句子" << endl;
		cin >> in_c;
		//scanf("%s", in_c);

		n = 1;          //记录步骤
		k = 1;
		s[k] = '#';
		s[k + 1] = '\0';    //初始化
		ss = s + 1;       //指向栈底
		psc = in_c;


		cout << "步骤" << endl;
		cout << "步骤" << setw(10) << "栈内符号" << setw(10) << "优先关系" << setw(10) << "当前符号" << setw(10) << "剩余串" << setw(10) << "移进或规约" << endl;
		//printf("\n步骤\t栈内字符\t\t优先关系\t当前符号\t剩余输入串\t\t\t移进或归约\n");
		while (1)
		{
			if (judge(s, k, psc) == 0)
			{
				cout << "出错" << endl;
				break;
			}

			if (find_terminal(s[k]) >= 0)
				j = k;
			else
				j = k - 1;

			//flag = find(in_vt(s[j]), in_vt(*psc));
			if (relation[find_terminal(s[j])][find_terminal(*psc)] == '>')  //如果s[j] > 当前输入字符
			{
				do
				{
					q = s[j];
					if (find_terminal(s[j - 1]) >= 0)
						j--;
					else
						j = j - 2;
				} while (relation[find_terminal(s[j])][find_terminal(q)] != '<');
				cout << n++ << setw(10) << ss << setw(10) << ">" << setw(10) << *psc << setw(10) << psc + 1 << setw(10) << "规约" << endl;
				//printf("(%d)\t%-24s>\t\t%c\t\t%-32s归约\n", n++, ss, *psc, psc + 1);
				k = j + 1;
				s[k] = 'N';
				s[k + 1] = '\0';
				continue;
			}
			else if (relation[find_terminal(s[j])][find_terminal(*psc)] == '<')
			{
				cout << n++ << setw(10) << ss << setw(10) << "<" << setw(10) << *psc << setw(10) << psc + 1 << setw(10) << "规约222" << endl;
				//printf("(%d)\t%-24s<\t\t%c\t\t", n++, ss, *psc);
				k++;
				s[k] = *psc;
				s[k + 1] = '\0';
				psc++;
				//cout << setw(10) << psc << setw(10) << "移进" << endl;
				//printf("%-32s移进\n", psc);
				continue;
			}
			else if (relation[find_terminal(s[j])][find_terminal(*psc)] == '=')
			{
				if (s[j] == '#')
				{
					cout << n << setw(10) << ss << setw(10) << "=" << setw(10) << "#" << setw(20) << "接受" << endl;
					cout << "规约成功" << endl;
					//printf("(%d)\t%-24s=\t\t#\t\t\t\t\t\t接受\n", n, ss);
					//printf("\n归约成功！\n");
					break;
				}
				else
				{
					cout << n++ << setw(10) << ss << setw(10) << "=" << setw(10) << *psc;
					//printf("(%d)\t%-24s=\t\t%c\t\t", n++, ss, *psc);
					k++;
					s[k] = *psc;
					s[k + 1] = '\0';
					psc++;
					cout << setw(10) << psc << setw(10) << "移进" << endl;
					//printf("%-32s移进\n", psc);
					continue;
				}
			}
			else
			{
				cout << n++ << setw(10) << ss << setw(10) << "$" << setw(10) << *psc << setw(10) << psc + 1 << endl;
				cout << "错误" << endl;
				//printf("(%d)\t%-24s无\t\t%c\t\t%-32s\\\n", n++, ss, *psc, psc + 1);
				//printf("\n错误！\n");
				break;
			}



		}

	}


	return 0;
}
int judge(char *p, int k, char *psc)
{

	if (k == 1 && p[k] == '#' && (*psc == '+' || *psc == '*'))
	{
		printf("\n运算符前面没有操作数！\n");
		return 0;
	}
	if ((*psc == '+' || *psc == '*') && (*(psc + 1) == '+' || *(psc + 1) == '*'))
	{
		printf("\n运算符号相邻！\n");
		return 0;
	}
	if (*psc == '#' && (*(psc - 1) == '+' || *(psc - 1) == '*'))
	{
		printf("\n运算符后面没有操作数！\n");
		return 0;
	}
	return 1;
}

int find_terminal(char s)//获取终结符所在位置函数
{
	int p = -1;
	//if (find(s) == terminal.end())
	//	terminal.push_back(s);
	int j = terminal.size();
	if (j == 0)
	{
		terminal.push_back(s);
		p = terminal.size();
	}
	else
	{
		for (size_t i = 0;i < terminal.size();i++)
		{
			if (terminal[i] == s)
				p = i;
		}
	}
	//else terminal.push_back(s);
	return p;
}
int find_non_terminal(char s)//获取非终结符所在位置函数
{
	int p = -1;
	int j = non_terminal.size();
	if (j == 0)
	{
		non_terminal.push_back(s);
		p = non_terminal.size();
	}
	else
	{
		for (size_t i = 0;i < non_terminal.size();i++)
		{
			if (non_terminal[i] == s)
				p = i;
		}
	}
	//non_terminal.push_back(s);
	return p;
}
void transport(int n)//处理原文法
{
	int x = 0, y = 0;
	int j;

	for (int i = 0;i < n;i++)
	{
		//for (int j = 0;grammer[i][j] != '\0';j++)
		//{
		if (!(judge_non(grammer[i][0])))
		{
			cout << "该文法不是算符文法" << endl;//如果首字母不是非终结符，不是算符文法
			return;
		}
		else
		{
			if (find_non_terminal(grammer[i][0]) < 0)
				non_terminal.push_back(grammer[i][0]);//如果没有找到非终结符，插入
		}
		/*if ((judge_non(grammer[i][j])) && (judge_non(grammer[i][j + 1])))
		{
			cout << "该文法不是算符文法" << endl;
			return;//两个非终结符不行
		}*/
		//}

	}
	for (int i = 0;i < n;i++)
	{
		for (int j = 0;j < grammer[i].size();j++)
		{
			if (judge_non(grammer[i][j]))
			{
				j++;
				j--;
			}
			else
			{
				if ((!(judge_non(grammer[i][j]))) && (grammer[i][j] != '-') && (grammer[i][j] != '>') && (grammer[i][j] != '|'))
				{
					if (find_terminal(grammer[i][j]) < 0)
						terminal.push_back(grammer[i][j]);//如果没有找到终结符，插入
				}
			}
		}
	}
	terminal.push_back('#');
	terminal.push_back('\0');
	//开始转换表达式
	for (int l = 0;l < 6;l++)
	{
		product.push_back(vector<char>());
	}

	for (int i = 0;i < n;i++)//扫描每一行
	{
		//product.push_back(vector<char>());
		product[x].push_back(grammer[i][0]);//product【0】没分配空间
		//product[x][y] = grammer[i][0];//把每一个首字母放在非终结符
		//y++;
		for (int j = 1;j < grammer[i].size();j++)
		{
			if (grammer[i][j] == '|')
			{
				/*product[x].push_back('@');
				product[x].push_back('@');
				product[x].push_back('@');*/
				product[x].push_back('\0');
				//product[x].push_back('\n');
				//product[x][y] = '\0';
				x++;
				//y = 0;
				product[x].push_back(grammer[i][0]);
				product[x].push_back('-');
				product[x].push_back('>');
				//	product[x][y] = grammer[i][0];
					//y++;
					//product[x][y++] = '-';
					//product[x][y++] = '>';
			}
			else
			{
				product[x].push_back(grammer[i][j]);
				//product[x][y] = grammer[i][j];
				//y++;
			}
		}
		/*product[x].push_back('@');
		product[x].push_back('@');
		product[x].push_back('@');*/
		product[x].push_back('\0');
		x++;
		//y++;//每一行末尾加\0

	}
	M = x;//产生式的行数
}
int judge_non(char s)//判断一个字符是不是非终结符
{
	if (s >= 'A'&&s <= 'Z')
		return 1;
	else
		return 0;
}
void terminal_display()//终结符显示
{
	cout << "产生的终结符：" << endl;
	vector<char>::iterator it;
	for (it = terminal.begin();it != terminal.end();it++)
	{
		cout << *it;
	}
	cout << endl;
}
void non_terminal_display()//非终结符显示
{
	cout << "产生的非终结符：" << endl;
	vector<char>::iterator it;
	for (it = non_terminal.begin();it != non_terminal.end();it++)
	{
		cout << *it;
	}
	cout << endl;
}
void product_display()//变换文法显示
{
	cout << "变换后的文法：" << endl;
	/*for (int i = 0;i < 10;i++)
	{
		for (int j = 0;j < 20;j++)
		{
			cout << product[i][j];
		}
		cout << endl;
	}*/
	vector<vector<char>>::iterator it;
	for (it = product.begin();it != product.end();it++)
	{
		for (vector<char>::iterator it_2 = it->begin();it_2 != it->end();it_2++)
		{
			cout << *it_2;
		}
		cout << endl;
	}
}
int find(vector<char>a, char ch)//查找一个字符是不是在数组里
{
	for (size_t i = 0;i < a.size();i++)
	{
		if (ch == a[i])
		{
			return 1;
			break;
		}
	}
	return 0;
}
/*
void firstfind(char ch)//求一个非终结符的first集
{
	int x=find_non_terminal(ch);
	for(int i=0;i<product列数;i++)
	{
		if(product[i][0]==ch)
		{
			if(!(judge_non(product[i][3]))
			{
				if(!(find(first[x],product[i][3])))
				first[x].push_back(product[i][3]);
			}
			else
			{
				if(!(judge_non(product[i][4]))
				{
				 if(!(find(first[x],product[i][4])))
				 first[x].push_back(product[i][4]);
				}
			}
			else
			{
				firstfind(product[i][3]);
				int y=find_non_terminal(product[i][3]);
				for(size_t j=0;j<first[y].size();y++)
				   {
					   if(!(find(first[x],first[y][i])))
					   first[x].push_back(first[y][i]);
				   }
			}

		}
	}
}
*/
void firstvt()
{
	/*int mm = non_terminal.size();
	int nn = terminal.size();
	int first [mm][nn];*/
	/*for (int l = 0;l < non_terminal.size();l++)
	{
		first.push_back(vector<ch>());
	}*/
	for (int i = 0;i < non_terminal.size();i++)
	{
		for (int j = 0;j < terminal.size();j++)
		{
			first[i][j] = 0;
		}
	}
	for (int i = 0;i < M;i++)
	{
		int r1 = find_non_terminal(product[i][0]);//首字母（非终结符的位置）
		int x = find_terminal(product[i][3]);//右部第一个字母
		int y = find_terminal(product[i][4]);//右部第二个字母
		if (x >= 0)//第一个字母是终结符，插入first
		{
			first[r1][x] = 1;
			//first[r1].push_back(product[i][3]);
		}
		else
		{
			if (y >= 0)
			{
				first[r1][y] = 1;
				//first[r1].push_back(product[i][3]);
			}
		}
	}

	for (int i = M - 1;i >= 0;i--)
	{
		int y = find_terminal(product[i][3]);
		if (y < 0)
		{
			int m = find_non_terminal(product[i][0]);
			int n = find_non_terminal(product[i][3]);
			if (m != n)
			{
				//for(int t=0;t<first[n].size();t++)
				//{
				  //  if(!(find(first[m],first[n][t])))
					//first[m].push_back(first[n][t]);
				//}
				for (int t = 0;t < terminal.size();t++)
				{
					if (first[n][t] != 0)
						first[m][t] = first[n][t];
				}
			}
		}
	}
	cout << "非终结符的first集" << endl;
	for (int i = 0;i < non_terminal.size();i++)
	{
		cout << non_terminal[i] << " ";
		for (int j = 0;j < terminal.size();j++)
		{
			if (first[i][j] != 0)
			{
				cout << terminal[j] << " ";
			}
		}
		cout << endl;
	}
}
void lastvt()
{
	int d;
	/*int mm = non_terminal.size();
	int nn = terminal.size();
	int last[mm][nn];*/
	for (int i = 0;i < non_terminal.size();i++)
	{
		for (int j = 0;j < terminal.size();j++)
			last[i][j] = 0;//初始化
	}
	for (int i = 0;i < M;i++)
	{
		int r = find_non_terminal(product[i][0]);
		//int c=product[i].size();//每一行长度
		//for (int c = 0;c<product[i].size();c++)
		//{
		//	d = c;
		//}
		d = product[i].size() - 2;//最后一个是'\0'
		int x = find_terminal(product[i][d]);//最后一个字符
		int y = find_terminal(product[i][d - 1]);//倒数第二个字符
		if (x >= 0)
		{
			last[r][x] = 1;
		}
		else
			if (y >= 0)
			{
				last[r][y] = 1;
			}
	}
	for (int i = M - 1;i >= 0;i--)
	{
		int y = find_non_terminal(product[i][3]);
		if (y >= 0)
		{
			int m = find_non_terminal(product[i][0]);
			int n = find_non_terminal(product[i][3]);
			if (m != n)
			{
				for (int t = 0;t < terminal.size();t++)
				{
					if (last[n][t] != 0)
					{
						last[m][t] = last[n][t];
					}
				}
			}
		}
	}
	/*int m = find_non_terminal(product[i][0]);
	int z = product[i].size() - 2;

	int n = find_non_terminal(product[i][z]);
	if (n >= 0)
	{
		if (m != n)
		{
			for (int t = 0;t < terminal.size();t++)
			{
				if (!last[n][t])
				{
					last[m][t] = last[n][t];
				}
			}
		}
	}*/
	//}
	cout << "非终结符的last集" << endl;
	for (int i = 0;i < non_terminal.size();i++)
	{
		cout << non_terminal[i] << " ";
		for (int j = 0;j < terminal.size();j++)
		{
			if (last[i][j] != 0)
			{
				cout << terminal[j] << " ";
			}
		}
		cout << endl;
	}
}
void creatrelation()
{
	int x, y, xm, ym, f;
	int a = terminal.size();
	for (int i = 0;i < a - 1;i++)
	{
		relation.push_back(vector<char>());
		for (int j = 0;j < a;j++)
		{
			relation[i].push_back('$');
		}
	}
	for (int m = 0;m < M;m++)
	{
		for (int n = 3;n < product[m].size() - 2;n++)
		{
			x = find_terminal(product[m][n]);
			xm = find_non_terminal(product[m][n]);
			y = find_terminal(product[m][n + 1]);
			ym = find_non_terminal(product[m][n + 1]);
			f = find_terminal(product[m][n + 2]);
			if (x >= 0 && y >= 0)
			{
				relation[x][y] = '=';//p->..ab..
			}
			/*else if (x >= 0 && f >= 0 && y < 0)
			{
				relation[x][f] = '=';//p->..aQb.
			}*/
			else if (x >= 0 && y < 0)
			{
				for (int h = 0;h < terminal.size() - 1;h++)
				{
					if (first[ym][h] == 1)
					{
						relation[x][h] = '<';
					}		if (f >= 0)
					{
						relation[x][f] = '=';//p->..aQb.
					}
				}

			}
			else if (x < 0 && y >= 0)
			{
				for (int g = 0;g < terminal.size() - 1;g++)
				{
					if (last[xm][g] == 1)
					{
						relation[g][y] = '>';
					}
				}
			}
		}
		int a = terminal.size() - 2;
		for (int i = 0;i < a;i++)
		{
			relation[a][i] = '<';
			relation[i][a] = '>';
		}
		relation[a][a] = '=';
	}
}
/*for(int i=0;i<terminal.size();i++)
int x, xm, y, ym, f;
int a = non_terminal.size();
int b = terminal.size();
int c = product.size();
for (int i = 0;i < c;i++)
{
	int j = product[i].size()-2;
	for (int v = 3;v < j;v++)
	{
		x = find_terminal(product[i][v]);
		xm = find_non_terminal(product[i][v]);
		y = find_terminal(product[i][v + 1]);
		ym = find_non_terminal(product[i][v+1]);
		f = find_terminal(product[i][v + 2]);
		if (x >= 0 && y >= 0)
		{
			relation[x][y] = '=';//p->..ab..
		}
		else if (v <= j && x >= 0 && f >= 0 && y < 0)
		{
			relation[x][f] = '=';//p->..aQb.
		}
		else if (x>= 0 && y== 0)
		{
			for (int h = 0;h < b;h++)
			{
				if (first[ym][h] == 1)
				{
					relation[x][h] = '<';
				}
			}
		}
		else if (x >= 0 && y > 0)
		{
			for (int g = 0;g < b;g++)
			{
				if (last[xm][g] == 1)
				{
					relation[g][y] = '>';
				}
			}
		}
	}*/
	//}
//}
/*
void relationtrans()
{
	for (int i = 0;i < terminal.size();i++)
	{
		for (int j = 0;j < terminal.size();j++)
		{
			relation[i][j]=charcomplete(terminal[i], terminal[j]);
		}
	}
}*/
void relationdisplay()
{
	cout << " ";
	for (int i = 0;i < terminal.size() - 1;i++)
	{
		cout << terminal[i] << " ";
	}
	cout << endl;
	for (int j = 0;j < terminal.size() - 1;j++)
	{
		cout << terminal[j] << " ";
		for (int h = 0;h < terminal.size() - 1;h++)
		{
			cout << relation[j][h] << " ";
		}
		cout << endl;
	}
}
/*
void guiyue()
{
	stack<char> s;
	int k;
	k = 1;
	char Q,N;
	int j;
	s[k] = '#';
	char a;
	char c[10] = "i+i#";
	int n = 0;
	a = c[n];
	do
	{
		if (find_terminal(s[k]) >= 0)
			j = k;
		else
			j = k - 1;
		if (relation[s[j]][a] == '>')
		{
			do {
				Q = s[j];
				if (find_terminal(s[j - 1]))
					j = j - 1;
				else
					j = j - 2;
			} while (relation[s[j]][Q] == '=');
			for (int i = 0;i < M;i++)
			{
				for (int l = 3;product[i][l] != '\0';l++)
				{
					if (product[i][l] == s[j + 1])
					{
						j++;
					}
					else
						break;
				}
				N = product[i][0];
			}
			k = j + 1;
			s[k] = N;

		}
		else
		{
			if ((relation[s[j]][a] == '<') || (relation[s[j]][a] == '='))
			{
				k = k + 1;
				s[k] = a;
			}
			else
				cout << "error" << endl;
		}
		a = c[n++];
	} while (a != '#');
	if (j < 0)
		cout << "error" << endl;
	else if (s[0] == '#'&&s[1] == 'E'&&s[2] == '#')
		cout << "yes" << endl;
}*/
/*
void scan()
{
	int step = 0;
	char p1, Q, p2;
	char a;
	int j;
	//int l1;
	int k=0;
	//int l = strlen(sentence);
	int l = sentence.size();
	for (int i = 0;i<l;i++)
	{
		int l1;
		a = sentence[i];
		if (find_terminal(s[k]) >= 0)
			//find_terminal(s[k]);
			j = k;
		else
			j = k - 1;
		int h1 = find_terminal(s[j]);
		if (find_terminal(a) >= 0)
			//find_terminal(a);
		 l1 = find_terminal(a);
		else
		{
			cout << "error 不合法" << endl;
			break;
		}
		p1 = relation[h1][l1];
		if (p1 == '>')
		{
		loop:
			Q = s[j];
			if (find_terminal(s[j - 1]))
				j = j - 1;
			else
				j = j - 2;
			int h2 = find_terminal(s[j]);
			int l2 = find_terminal(Q);
			int p2 = relation[h2][l2];
			if (p2 == '<')//规约
			{
				k = j + 1;
				creatremain();//当前符拿出来，输出剩下的串
				step++;
				//cout << step << setw(10) << s << setw(10) << p1 << setw(10) << a << "     ";
				cout << step << setw(10) << s << setw(10) << p1 << setw(10) << a << "   ";
				vector<char>::iterator it;
				for (it = remain.begin();it != remain.end();it++)
				{
					cout << *it;
				}
				cout << setw(10) << "规约" << endl;
				i--;//当前符不变
				s[k] = 'F';//规约为F
				int r1 = strlen(s);
				for (int r2 = k + 1;r2 < r1;r2++)
				{
					s[r2] = '\0';

				}//清空F后面的
				int y1 = remain.size()-1;
				for (int y2 = 0;y2 < y1;y2++)

					remain[y1 - y2] = remain[y1 - y2 - 1];//把第一个空出来，是空格，下一次显示的时候creatremain后还是现在的样子，相当于把空格拿出来，但是不用显示
				remain[0] = 'i';//剩余串得加上当前符，因为刚才是显示，要是显示下一次，就得恢复原来的样子，和s[k]一样

			}
			else
				goto
				loop;

		}
		else
		{
			if (p1 == '<')
			{
				creatremain();
				//product[l] = '0';//剩余字符串少1
				step++;
				cout << step << setw(10) << s << setw(10) << p1 << setw(10) << a << "   ";
				vector<char>::iterator it;
				for (it = remain.begin();it !=remain.end();it++)
				{
					cout << *it;
				}
				cout<<setw(10) << "移进" << endl;
				k++;
				s[k] = a;

			}
			else
			{
				if (p1 == '=')
				{
					int h3 = find_terminal(s[j]);
					int l3 = find_terminal('#');
					int p2 = relation[h3][l3];
					if (p2 == '=')
					{
						creatremain();
						step++;
						//cout << step << setw(10) << s << setw(10) << p1 << setw(10) << a << setw(10) << remain << setw(10) << "接受" << endl;
						cout << step << setw(10) << s << setw(10) << p1 << setw(10) << a << "   ";
						vector<char>::iterator it;
						for (it = remain.begin();it != remain.end();it++)
						{
							cout << *it;
						}
						cout << setw(10) << "接受" << endl;
						cout << "合法" << endl;
						break;
					}
					else
					{
						k++;
						s[k] = a;
					}
				}

				else
				{
					cout << "该字符串不能被接受error" << endl;
					break;
				}
			}
		}

	}
}
	/*char charcomplete(char a, char b)
	{
		char r;
		int x = find_terminal(a);
		int y = find_terminal(b);
		if (relation[x][y] != ' ')
			r = relation[x][y];
		else r = '$';
		/*if (x >= 0 && y >= 0 && (relation[x][y]!=' '))
		{
			r = relation[x][y];
		}
		else
			r = '$';*/
			//return r;
		//}
		/*void creatremain()
		{

			int i = remain.size()-1;
			//if (remain[0] == '\0')
				//remain[0] = '#';
			//else
			//{
			for (int j = 0;j < i;j++)
				remain[j] = remain[j + 1];
			remain[i - 1] = '\0';
			//}
		}
		*/
		/*
		void lastfind(char ch)//求一个非终结符的last集
		{

		}
		void creatrelation()//创建优先矩阵
		char charcomplete(char a, char b)//只显示终结符
		*/