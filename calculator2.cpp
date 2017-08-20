//银行同期贷款
#include<iostream>
using namespace std;

class Bank
{
private:
	double loans;//金额
	int in_year;
	int in_month;
	int in_day;
	int start;//起始时间
	int end;//截止时间
	int out_year;
	int out_month;
	int out_day;

	int cday;//起始日期间隔天数
	int lday;//同期间隔

	const double ll[100][100] = 
	{	//6个月以内，6个月至1年，1年至3年，3年至5年，
		//5年以上，公积金<5年，公积金>5年
		{ 20151024,4.35,4.35,4.75,4.75,4.95,2.75,3.25,10000},	//20151024
		{ 20150826,4.60,4.60,5.00,5.00,5.15,2.75,3.25,59},	//20150826
		{ 20150628,4.85,4.85,5.25,5.25,5.40,3.00,3.50,59},	//20150628
		{ 20150511,5.10,5.10,5.50,5.50,5.65,3.25,3.75,48},	//20150511
		{ 20150301,5.35,5.35,5.75,5.75,5.90,3.50,4.00,71},	//20150301
		{ 20141122,5.60,5.60,6.00,6.00,6.15,3.75,4.25,99},	//20141122
		{ 20120706,5.60,6.00,6.15,6.40,6.55,4.00,4.50,869},	//20120706
		{ 20120608,5.85,6.31,6.40,6.65,6.30,4.20,4.70,28},	//20120608
		{ 20110707,6.10,6.56,6.65,6.90,7.05,4.45,4.90,337},	//20110707
		{ 20110406,5.85,6.31,6.40,6.65,6.80,4.20,4.70,92},	//20110406
		{ 20110209,5.60,6.06,6.10,6.45,6.60,4.00,4.50,56},	//20110209
		{ 20101226,5.35,5.81,5.85,6.22,6.40,3.75,4.30,45},	//20101226
		{ 20101020,5.10,5.56,5.60,5.96,6.14,3.50,4.05,67},	//20101020
		{ 20081223,4.86,5.31,5.40,5.76,5.94,3.33,3.87,666},	//20081223
		{ 20081127,5.04,5.58,5.67,5.94,6.12,3.51,4.05,26},	//20081127
		{ 20081030,6.03,6.66,6.75,7.02,7.20,4.05,4.59,28},	//20081030
		{ 20081030,6.12,6.93,7.02,7.29,7.47,4.32,4.86,21},	//20081009
		{ 20081030,6.21,7.20,7.29,7.56,7.74,4.59,5.13,23},	//20080916
		{ 20081030,6.57,7.47,7.56,7.74,7.83,4.77,5.22,270}	//20071221
	};

public:
	void inputLoans(void) ;
	int	 calday(void) ;
	bool IsLeap(int) ;
	int dayInYear(int, int, int);
	int* timeswap(int ) ;
	void inputdate(void) ;
	void calpart(void);
	int day_day(int, int, int, int, int, int );

};

void Bank::inputdate(void) {

	int* ymd;
	cout << "------------------------------------" << endl;
	cout << "请输入起始时间：";
	cin >> start;

	ymd=timeswap(start);
	in_year = ymd[0];
	in_month = ymd[1];
	in_day = ymd[2];
	
	cout << "请输入截止时间：" ;
	cin >> end;

	ymd = timeswap(end);
	out_year = ymd[0];
	out_month = ymd[1];
	out_day = ymd[2];
	cout <<"------------------------------------"<<endl;
	cout << "您输入的起始日期为:" << in_year << "年" << in_month << "月" << in_day << "日" << endl;
	cout << "您输入的截止日期为:" << out_year << "年" << out_month << "月" << out_day << "日" << endl;

}

int* Bank::timeswap(int x) {
	int year;
	int month;
	int day;
	int ymd[3];
	year = x / 10000;
	month = (x - year * 10000) / 100;
	day = x - year * 10000 - 100 * month;
	ymd[0] = year;
	ymd[1] = month;
	ymd[2] = day;
	return ymd;
}	  
 
bool Bank::IsLeap(int year) { 
	return  (year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0); 
}

int Bank::dayInYear(int year, int month, int day) {
	int DAY[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };  
	if (IsLeap(year))   DAY[1] = 29;  
	for (int i = 0; i<month - 1; ++i)
		day += DAY[i];   
	return day; 
}

int Bank::calday(void) {
	

	if (out_year < in_year) {
		cout << "输入年份有误！";
		return -1;
	}

	else if (out_year==in_year&&out_month<in_month){
		cout << "输入月份有误！";
		return -1;
	}

	else if (out_year == in_year&&out_month==in_month&&out_day<=in_day) {
		cout << "输入日期有误！";
		return -1;
	}

	else if (out_year == in_year&&out_month == in_month&&out_day > in_day) {
		//年月相同
		cday = out_day - in_day+1;
		return cday;
	}

	else if (out_year == in_year&&out_month > in_month) {
		//年相同

		cday = dayInYear(out_year, out_month, out_day) - dayInYear(in_year, in_month, in_day) + 1;
		return cday;
	}
	else {

		int d1, d2, d3;   
		if (IsLeap(in_year))    
			d1 = 366 - dayInYear(in_year, in_month, in_day);
		else
			d1 = 365 - dayInYear(in_year, in_month, in_day);
		d2 = dayInYear(out_year, out_month, out_day);
		d3 = 0;
		for (int year = in_year + 1; year < out_year; year++) {
			if (IsLeap(year))
				d3 += 366;
			else      d3 += 365; 
		}       
			cday=d1 + d2 + d3+1;
			return cday;
	}
	
}

void Bank::inputLoans(void) {
	cout << "请输入金额:";
	cin >> loans;
}

int Bank::day_day(int year1, int month1, int day1, int year2, int month2, int day2)
{
	

	if (year2 == year1&&month2 == month1&&day2 > day1) {
		//年月相同
		lday = day2 - day1+1;
		return lday;
	}

	else if (year2 == year1&&month2 > month1&&day2 > day1) {
		//年相同
		lday = dayInYear(year2, month2, day2) - dayInYear(year1, month1, day1) + 1;
		return lday;
	}
	else {
		int d1, d2, d3;
		if (IsLeap(year1))
			d1 = 366 - dayInYear(year1, month1, day1);
		else
			d1 = 365 - dayInYear(year1, month1, day1);
		d2 = dayInYear(year2, month2, day2);
		d3 = 0;
		for (int year = year1 + 1; year < year2; year++) {
			if (IsLeap(year))
				d3 += 366;
			else      d3 += 365;
		}
		lday = d1 + d2 + d3 + 1;
		return lday;

	}
}

void Bank::calpart(void) {
	
	int date_f, type_f;
	double gg;
	int ccday = cday;
	if (cday <= 180)
		type_f = 1;
	if (cday > 180 && cday <= 365)
		type_f = 2;
	if (cday > 365 && cday <= 1095)
		type_f = 3;
	if (cday > 1095 && cday <= 1825)
		type_f = 4;
	if ( cday > 1825)
		type_f = 5;

	//公积金略
	for (date_f = 0; date_f <= 19&& start <= ll[date_f][0]; date_f++)
	{
		//if (start > ll[date_f][0])	break;
	
	}
	//此时ll[date_f][type_f]为第一阶段利率
//	cout<<ll[date_f][type_f];
	int* tmp = timeswap(ll[date_f][0]);
	int year_f = tmp[0];
	int month_f = tmp[1];
	int day_f = tmp[2];
	int dd = day_day(year_f, month_f, day_f,in_year, in_month, in_day )-1;//计算开始日期与第一阶段利率间隔
//	cout<<"????????" << dd;
	int firstday = ll[date_f][8] - dd;//计算第一阶段适用天数
//	cout << firstday;
	if (cday < firstday) {

		cout<<start<<"到"<<end << "利息为：" << (loans*cday*ll[date_f][type_f] / 100 / 365) << endl;

	}
	else {
		int sy = cday-firstday;

		gg = (loans*firstday*ll[date_f][type_f] / 100 / 365);//第一阶段
		cout << start << "到" <<(int) ll[date_f - 1][0] << "利息为：" << gg<<endl;
//		cout << endl <<gg<< sy;

		while (sy != 0) {
			if (sy < ll[date_f - 1][8]) {
				gg += loans*sy*ll[date_f - 1][type_f] / 100 / 365;
				cout << (int)ll[date_f - 1][0] << "到" << end << "利息为：" << loans*sy*ll[date_f - 1][type_f] / 100 / 365 << endl;
				sy = 0;
				cout << "利息为：" << gg<<endl;
			}
			else {
				date_f -= 1;
				
				gg+= loans*ll[date_f][8] *ll[date_f ][type_f] / 100 / 365;
				cout << (int)ll[date_f ][0] << "到" << (int)ll[date_f - 1][0] << "利息为：" << loans*ll[date_f][8] * ll[date_f][type_f] / 100 / 365<<endl;
				sy -= ll[date_f ][8]; 

//				cout << endl<<gg<<sy;

			}
		}
	
	}



	int day_sy = 0;

}
int main() {

	while(true){
		Bank counter;
		counter.inputLoans();
		counter.inputdate();

		cout << "起止日期的间隔为：" << counter.calday()<<"天" << endl;
		cout << "------------------------------------" << endl;
		counter.calpart();

		cout << "------------------------------------" << endl<<endl<<endl<<endl;
	}
	/*Bank counter;
	counter.inputLoans();
	counter.inputdate();

	cout<<"起止日期的间隔为："<< counter.calday()<<endl;
	cout << "------------------------------------" << endl;
	counter.calpart();
	cout << endl;*/
	return 0;
}