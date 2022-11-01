#ifndef _LDUR_TIME_H_
#define _LDUR_TIME_H_
/*
******************************************************************************
  Name     : ldurtime
  Purpose  : get secs, date, time,...
  Author   : Adam

  Revisions:
   Ver       Date      Author           Description
   --------  --------  ---------------  ------------------------------------
   1.0       20100908  Adam             Create
   1.2       20190926  Adam             Add msecs()
   1.21      20221010  Adam             Add getTime(int n=0)
   1.22      20221101  Adam             Add updateTimeVar

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

// Explain: secs since 1970-1-1
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

// Explain: microsecs since 1970-1-1
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


// Explain: days of the month
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
   time_t now = time(0);                          // secs since 1970-1-1
   now -= n;
   
   tm *ltm = localtime(&now);                     // secs since 1970-1-1
 
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


// update string date variable
// now = yyyymmdd
// yesterday(now-1), now-2, ...
string updateTimeVar(string& str1)
{
   string s1, s2, t1;
   long n1;
   for (int i=0; i<10; i++)
   {
      s1 = strInstr(str1, "%", 2);
      if (s1 == "")
          break;

      t1 = strInstr(s1, "-", 1);
      n1 = atoi(strInstr(s1, "-", 2).c_str());
      if (t1 == "yesterday")
           n1 = getTime((n1+1)*24*3600);
      else if (t1 == "now")
           n1 = getTime(n1*24*3600);
      s2 = num2str(n1);

      str1 = strRep(str1, "%" + s1 + "%", s2.substr(0,8));

   }
   return str1;
}

} // namespace usr
#endif
