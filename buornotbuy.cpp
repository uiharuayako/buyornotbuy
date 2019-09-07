#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <stdlib.h>

using namespace std;
double zc;
double price;
double m, t, h, c, re, e1, e2, e;
double p = 0;
string yd1, yd2, yd3, yd4, yd5, yd6;
//m为目的判据
//s为深思熟虑判据
//t为真正的价格判据
double s = 1;
int pd1, pd2, pd3, pd4, pd5, pd6, pd7, pd8,pd9,pd10;
//IsLeap函数判断一个年份是否为闰年，方法如下:
bool IsLeap(int year)
{
	return (year % 4 == 0 || year % 400 == 0) && (year % 100 != 0);
}
//上面的StringToDate函数用于取出日期中的年月日并判断日期是否合法
//从字符中最得年月日 规定日期的格式是yyyy-mm-dd
bool StringToDate(string date, int& year, int& month, int& day)
{
	year = atoi((date.substr(0, 4)).c_str());
	month = atoi((date.substr(5, 2)).c_str());
	day = atoi((date.substr(8, 2)).c_str());
	int DAY[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	if (IsLeap(year)) {
		DAY[1] = 29;
	}
	return year >= 0 && month <= 12 && month > 0 && day <= DAY[month] && day > 0;
}
//DayInYear能根据给定的日期，求出它在该年的第几天，代码如下
int DayInYear(int year, int month, int day)
{
	//int _day = 0;
	int DAY[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	if (IsLeap(year))
		DAY[1] = 29;
	for (int i = 0; i < month - 1; ++i)
	{
		day += DAY[i];
	}
	return day;
}
int DaysBetween2Date(string date1, string date2)
{
	//取出日期中的年月日
	int year1, month1, day1;
	int year2, month2, day2;
	if (!StringToDate(date1, year1, month1, day1) || !StringToDate(date2, year2, month2, day2))
	{
		cout << "输入的日期格式不正确";
		return -1;
	}
	if (year1 == year2 && month1 == month2)
	{
		return day1 > day2 ? day1 - day2 : day2 - day1;

		//如果年相同
	}
	else if (year1 == year2)
	{
		int d1, d2;
		d1 = DayInYear(year1, month1, day1);
		d2 = DayInYear(year2, month2, day2);
		return d1 > d2 ? d1 - d2 : d2 - d1;

		//年月都不相同
	}
	else {
		//确保year1年份比year2早
		if (year1 > year2)
		{
			//swap进行两个值的交换
			swap(year1, year2);
			swap(month1, month2);
			swap(day1, day2);
		}
		int d1, d2, d3;
		if (IsLeap(year1))
			d1 = 366 - DayInYear(year1, month1, day1); //取得这个日期在该年还于下多少天
		else
			d1 = 365 - DayInYear(year1, month1, day1);
		d2 = DayInYear(year2, month2, day2); //取得在当年中的第几天
		cout << "d1:" << d1 << ", d2:" << d2;

		d3 = 0;
		for (int year = year1 + 1; year < year2; year++)
		{
			if (IsLeap(year))
				d3 += 366;
			else
				d3 += 365;
		}
		return d1 + d2 + d3;
	}
}
void moneychange()
{
	ofstream zichan;
	zichan.open("zichan.txt");
	cout << "请输入您目前的总资产\n";
	cin >> zc;
	zichan << zc<<endl;
	zichan.close();
}
void moneyread()
{
	ifstream zcf;
	zcf.open("zichan.txt");
	cout << "\n从文件中读取当前资产" << endl;
	zcf >> zc;
	zcf.close();
	cout << "当前资产为" << zc << endl;
	cout << "按任意键以继续..." << endl;
	cin.get();
	cin.get();
}
void goalpd()
{
	cout << "\n请输入您的购买目的\n 1.生存 2.发展 3.享受 4.既是发展又是享受\n";
	cin >> pd1;
	switch (pd1)//目的判据
	{
	case 1:
		m = 1.0;
		yd1 = "生存";
		break;
	case 2:
		m = 1.2;
		yd1 = "发展";
		break;
	case 3:
		m = 0.8;
		yd1 = "享受";
		break;
	case 4:
		m = 0.96;
		yd1 = "发展和享受";
		break;
	}
	switch (pd1)//发展补正
	{
	case 2:
		t = t + 0.5;
		break;
	case 4:
		t = t + 0.3;
		break;
	}
}
void pricepd()
{
	cout << "\n请输入您目标商品的价格\n";
	cin >> price;
	//价格判据开始
	if (price <= 5)
	{
		t = 1.5;
	}
	if (20 > price > 5)
	{
		t = 1.2;
	}
	if (50 >= price >= 20)
	{
		t = 1;
	}
	if (100 >= price > 50)
	{
		t = 0.7;
	}
	if (200 > price > 100)
	{
		t = 0.5;
	}
	if (price >= 200)
	{
		t = 0.4;
	}
	//价格判据结束
}
void think()
{
	if (price >= 50)
	{
		string d1, d2;
		int db;
		cout << "您购买的物品数额较大，需要计算思考天数" << endl;
		cout << "\n输入立项购买日期(YYYY-MM-DD)" << endl;
		cin >> d1;
		cout << "\n输入今天日期(YYYY-MM-DD)" << endl;
		cin >> d2;
		db = DaysBetween2Date(d1, d2);
		if (db >= 50)
		{
			s = 1.2;
		}
		if (50 > db >= 30)
		{
			s = 1;
		}
		if (30 > db > 10)
		{
			s = 0.8;
		}
		if (10 >= db > 1)
		{
			s = 0.6;
		}
		if (db <= 1)
		{
			s = 0.5;
		}
	}
}
void helpd()
{
	cout << "\n该商品对您健康的潜在影响？\n1.有好处 2.无影响 3.有坏处\n";
	cin >> pd2;
	switch (pd2)//健康判据
	{
	case 1:
		h = 1.2;
		yd2 = "有益健康";
		break;
	case 2:
		h = 1;
		yd2 = "不影响健康";
		break;
	case 3:
		h = 0.9;
		yd2 = "有害健康";
		break;
	}
}
void emopd()
{
	cout << "\n心情影响程度\n 1.超级开心 2.很开心 3.开心 4.对心情无影响 5.悲伤 \n";
	cin >> pd5;
	switch (pd5)
	{
	case 1:
		e1 = 2;
		yd4 = "超级开心";
		break;
	case 2:
		e1 = 1.5;
		yd4 = "很开心";
		break;
	case 3:
		e1 = 1.2;
		yd4 = "开心";
		break;
	case 4:
		e1 = 1.0;
		yd4 = "有点开心";
		break;
	case 5:
		e1 = 0.8;
		yd4 = "悲伤";
		break;
	}
}
void emotpd()
{
	cout << "\n心情影响持续时间\n 1.永远 2.超过三年 3.1 - 3年 4.一年内 5.半年内 6.3月内 7.一月内 8.一周内 9.一天内 10.半天内 11.一会儿 12.瞬间\n";
	cin >> pd6;
	switch (pd6)
	{
	case 1:
		e2 = 2.5;
		yd3 = "永久";
		break;
	case 2:
		e2 = 2;
		yd3 = "超过三年";
		break;
	case 3:
		e2 = 1.8;
		yd3 = "1-3年";
		break;
	case 4:
		e2 = 1.6;
		yd3 = "整整一年";
		break;
	case 5:
		e2 = 1.2;
		yd3 = "大概半年";
		break;
	case 6:
		e2 = 1.1;
		yd3 = "三个月";
		break;
	case 7:
		e2 = 1;
		yd3 = "一月";
		break;
	case 8:
		e2 = 0.98;
		yd3 = "一周";
		break;
	case 9:
		e2 = 0.95;
		yd3 = "一天";
		break;
	case 10:
		e2 = 0.9;
		yd3 = "半天";
		break;
	case 11:
		e2 = 0.85;
		yd3 = "一小段时间";
		break;
	case 12:
		e2 = 0.8;
		yd3 = "一刹那的时间";
		break;
	}
	e = e1 * e2;
}
void howtobuy()
{
	cout << "\n该商品的购买途径？\n1.便利店或共享单车 2.实体店 3.网店\n";
	cin >> pd7;
	switch (pd7)
	{
	case 1:
		s = 1.2;
		yd5 = "便利店或者共享单车扫码";
		break;
	case 2:
		s = 1;
		yd5 = "实体店";
		break;
	case 3:
		s = 0.95;
		yd5 = "网购";
		break;
	}
}
void howtosell()
{
	cout << "\n该商品能否二次出售？\n1.加价 2.原价 3.降价少 4.降价多 5.不出售\n";
	cin >> pd3;
	switch (pd3)//二次出售判据
	{
	case 1:
		c = 1.5;
		yd6 = "将来它甚至会升值";
		break;
	case 2:
		c = 1.2;
		yd6 = "而且它的价格可能长期不变";
		break;
	case 3:
		c = 1;
		yd6 = "以后我降一点价就能把它卖出去";
		break;
	case 4:
		c = 0.9;
		yd6 = "不过如果我想回血，就得降多点了";
		break;
	case 5:
		c = 0.8;
		yd6 = "我以后不会把它卖出去的";
		break;
	}
}
void enough()
{
	//个人原因判据
	if (pd4 == 1)
	{
		p = -0.3;
	}
	if (zc - price <= 0)
	{
		p = -0.8;
	}
}
void saveornot()
{
	ifstream save;
	save.open("save.txt");
	save >> pd4;
	save.close();
	if (pd4 == 1)
	{
		cout << "正在节约中\n";
	}
	if (pd4 == 0)
	{
		cout << "未在节约或save.txt被删除\n";
	}
	cout << "按任意键以继续..." << endl;
	cin.get();
	cin.get();
}
int savechange()
{
	ifstream save;
	save.open("save.txt");
	save >> pd4;
	save.close();
	ofstream save1;
	if (pd4 == 1)
	{
		cout << "已从节约切换为不节约\n";
		pd4 = 0;
		save1.open("save.txt");
		save1 << pd4 << endl;
		save1.close();
		cout << "按任意键以继续..." << endl;
		cin.get();
		cin.get();
		return 0;
	}
	if (pd4 == 0)
	{
		cout << "已从不节约切换为节约\n";
		pd4 = 1;
		save1.open("save.txt");
		save1 << pd4 << endl;
		save1.close();
		cout << "按任意键以继续..." << endl;
		cin.get();
		cin.get();
		return 0;
	}

}
void change()
{
	cout << "修改何种数据？\n1.购买目的 2.目标价格 3.健康影响\n";
	cout << "4.情绪影响 5.物品使用时间 6.购买方式 7.二次出售情况\n";
	cout << "请输入：";
	cin >> pd10;
	switch (pd10)
	{
	case 1:
		goalpd();
		break;
	case 2:
		pricepd();
		if (price < 50)
		{
			s = 1;
		}
		break;
	case 3:
		helpd();
		break;
	case 4:
		emopd();
		break;
	case 5:
		emotpd();
		break;
	case 6:
		howtobuy();
		break;
	case 7:
		howtosell();
		break;
	}
}
void result()
{
	ifstream zcf;
	zcf.open("zichan.txt");
	zcf >> zc;
	zcf.close();
	re = m * t * h * c * e + p - (price / zc - 0.5);
	cout << endl;
	system("CLS");
	cout << "==========结果==========\n";
	cout << "我现在共有:" << zc << "元" << endl;
	cout << "结论:这是一个售价为" << price << "的物品\n";
	cout << "我预计为了" << yd1 << "而购买它\n";
	cout << "而它不仅" << yd2 << "还将在" << yd3 << "内" << "使我变得" << yd4<<endl;
	cout << "我可能会通过" << yd5 << "的方式购买它," << yd6 << endl;
	cout << "最终得分：" << 100 * re * s << endl;
	cout << "按任意键以继续..." << endl;
	cin.get();
	cin.get();
}
void calc()
{
	goalpd();
	pricepd();
	think();
	helpd();
	emopd();
	emotpd();
	howtobuy();
	howtosell();
	enough();
	system("CLS");
	result();
	int i=0;
	while (i==0)
	{
		if (i == 0)
		{
			cout << "1.重新计算(再次输入数据) 2.修改数据 3.再次计算 4.返回主界面 5.退出程序：";
			cin >> pd9;
		}
		switch (pd9)
		{
		case 1:
			calc();
			break;
		case 2:
			change();
			break;
		case 3:
			result();
			break;
		case 4:
			i = 1;
			break;
		case 5:
			exit(0);
			break;
		}
	}
}
int main()
{
	while (1) 
	{
		cout << "---------------------------------\n";
		cout << "------购买决策程序 ver.0.06------\n";
		cout << "---------------------------------\n";
		cout << "1.执行程序 2.查询资产 3.修改资产 4.查询节约状态 5.更改节约状态 6.退出 请输入：";
		cin >> pd8;//判断使用者目的
		switch (pd8)
		{
		case 1:
			calc();
			break;
		case 2:
			moneyread();
			break;
		case 3:
			moneychange();
			break;
		case 4:
			saveornot();
			break;
		case 5:
			savechange();
			break;
		case 6:
			exit(0);
			break;
		}
		system("CLS");
	}
	return 0;
}
