#ifndef _LDUR_TIME_H_
#define _LDUR_TIME_H_
/*
******************************************************************************
  Name     : ldurtime
  Purpose  : 时间函数
  Author   : Adam

  Revisions:
   Ver        Date        Author           Description
   --------  --------  ---------------  ------------------------------------
   1.0       20100908  Adam             Create
   1.2       20190926  Adam             Add msecs()
   1.21      20221010  Adam             Add getTime(int n=0)

******************************************************************************
*/
#include <ctime>
#include <sys/time.h>
#include <chrono>                      //with the -std=c++11 or -std=gnu++11 compiler options.

#ifndef CLOCKS_PER_SEC
#define CLOCKS_PER_SEC 1000000
#endif

namespace ldur
{
using namespace std;

// Explain: 自1970/1/1 以来秒计数
// Problem:
// Author : adaM
// Date   : 2010-9-8
// History:
long timesecs()
{
   time_t lt;
   lt = time(NULL);

   return lt;
}

// Explain: 自1970/1/1 以来毫秒计数
// Author : adaM
// Date   : 2019/9/26
long msecs()
{
   using namespace std::chrono;
   
   typedef duration<double,std::ratio<1, 1000>> days_type;   
   time_point<system_clock,days_type> today = time_point_cast<days_type>(system_clock::now());
   
   return (long)today.time_since_epoch().count();
}

long timeMicroSecs1()
{
   int per = 1000000 / CLOCKS_PER_SEC;
	unsigned long t1 = clock() * per;

   return t1;
}

long timeMicroSecs()
{
   timeval tim;
   gettimeofday( &tim, NULL );
   long t1 = tim.tv_usec;

   return t1;
}

long randMillisecs()
{
   timeval tim;
   gettimeofday( &tim, NULL );
   long t1 = tim.tv_sec;

   t1 -= t1 / 1000000 * 1000000;
   t1 = t1 * 1000 + tim.tv_usec / 1000;

   return t1;
}


// Explain: 取本月天数
// Problem:
// Author : adaM
// Date   : 2006.6.1
// History: int getMonthDays(int yyyymm);
int getMonthDays( int date )
{
	int year;
	int month;

	int days;

	year = date / 100;
	month = date - year * 100;

	switch(month)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		days = 31;
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		days = 30;
		break;
	case 2:
		if(year%400 == 0||(year%4 == 0&&year%100 != 0))
			days = 29;
		else
			days = 28;
		break;
	}

	return days;
}


//get current time, yyyymmddhh24miss
unsigned long getTime(int n=0)
{
   time_t now = time(0);                          //1970 到目前经过秒数
   now -= n;
   
   tm *ltm = localtime(&now);                     //设置 tm 结构的各个组成部分
 
   unsigned long i;
   
   i = 1900 + ltm->tm_year;
   i *= 100;
   i += ( 1 + ltm->tm_mon );
   i *= 100;
   i += ltm->tm_mday;
   i *= 100;
   i += ltm->tm_hour;
   i *= 100;
   i += ltm->tm_min;
   i *= 100;
   i += ltm->tm_sec;
   
   return i;
}


} // namespace usr
#endif
