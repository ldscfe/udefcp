#ifndef _LDUR_STR_H_
#define _LDUR_STR_H_
/*
 ***************************************************
    Explain: �Զ����ַ�����
    Problem:
    Author : adaM
    Date   : 2010-4-26
    History:
 ***************************************************
*/
#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

namespace ldur
{
using namespace std;

#define CHARMAX 65536
/* Macro Define */
#define umax(a,b) (a>b)?a:b
#define umin(a,b) (a>b)?b:a
// Function Statement
string isNULL( const string& str1 );                                                      // �ַ���Ϊ�գ��������Ŀո�, string str1
string isNULL( const string& str1, const string& str2 );                                  // �ַ���Ϊ�գ����� str2
string strInstr ( const string& source, const char& instr, const int serial  );           // ���ݷָ�����ָ������λ�ã������ַ�����
string strInstr ( const string& source, const string& instr, const int serial );
string strInstrRemain ( const string& source, char instr, int serial  );                  // ���ݷָ�����ָ������λ�ã�����ʣ�µ��ַ�����
//string strInstrRemain ( const string& source, const string& instr, int serial );
string strGet ( const string&, const string&, const string& );                            // ���ݷָ��������ַ���
string strCut ( const string&, const string&, const string& );                            // �������м��������ַ�
string strRep( string context, const string& from, const string& to );                    // �滻Դ�ַ����е��ַ���
string str2asc( const string& src );                                                      // ascii to string	sample: "097098" --> "ab"
string asc2str( const string& src );                                                      // string to ascii	sample: "ab" --> "097098"
string trim( const string& str );
string ltrim( const string& str );
string rtrim( const string& str );
string lower( const string & str );                         //��ĸת��ΪСд
string upper( const string & str );                         //��ĸת��Ϊ��д

string to_str( const long& num );                           //��ֵת��Ϊ�ַ���



// Explain: ����ԭ�ַ��������Ŀո��ַ���Ϊ�գ��������Ŀո�
// Problem:
// Author : adaM
// Date   : 2010-4-26
// History:
string isNULL( const string& str1 )
{
//    if ( str1.length() == 0 )
//        return "��";
//    else
//        return str1;
    return ( str1.length()==0?"��":str1 );
}
// Explain: �ַ���Ϊ�գ�������һ���ַ���
// Problem:
// Author : adaM
// Date   : 2019-12-4
// History:
string isNULL( const string& str1, const string& str2 )
{
    return ( str1.length()==0?str2:str1 );
}


// Explain: ���ݷָ�����ָ������λ�ã������ַ�����( �ָ�������Ϊ�ַ��������ַ� )
// Problem:
// Author : adaM
// Date   : 2010-4-26
// History:
string strInstr ( const string& source, const char& instr, int serial  )
{
    using namespace std;
    int i;
    int pos1;
    int pos2;
    int step;
    step = 1;

    pos1 = -step;
    for ( i=0; i<serial-1; i++ )                           // ���ȡ��һ���ָ�������ôpos1ֵΪ-1.
    {
        pos1 = source.find(instr, pos1+step);
        if ( pos1 == -1 )
            break;
    }

    if ( serial > 1 && pos1 == -1 )
        return "";

    pos2 = source.find(instr, pos1+step );

    if ( pos2 == -1 )
        return source.substr ( pos1+step );
    else
        return source.substr ( pos1+step, pos2 - pos1 - step );
}
string strInstr ( const string& source, const string& instr, int serial  )
{
    int i;
    int pos1;
    int pos2;
    int step;
    step = instr.length();

    pos1 = -step;
    for ( i=0; i<serial-1; i++ )
    {
        pos1 = source.find(instr, pos1+step );
        if ( pos1 == -1 )
            break;
    }

    if ( serial > 1 && pos1 == -1 )
        return "";

    pos2 = source.find(instr, pos1+step );

    if ( pos2 == -1 )
        return source.substr ( pos1+step );
    else
        return source.substr ( pos1+step, pos2 - pos1 - step );
}



// Explain: ���ݷָ�����ָ������λ�ã�����ʣ�µ��ַ�����( �ָ�������Ϊ�ַ��������ַ� )
// Problem:
// Author : adaM
// Date   : 2010-4-26
// History:
string strInstrRemain ( const string& source, char instr, int serial  )
{
    using namespace std;
    int i;
    int pos1;                                              // �ָ�����serial�γ��ֵ�λ��
    int step;
    step = 1;                                              // �ַ��ͳ���Ϊ1���ַ���ȡ�䳤��

    pos1 = -step;
    for ( i=1; i<=serial; i++ )
    {
        pos1 = source.find( instr, pos1 + step );
        if ( pos1 == -1 )
            break;
    }

    if ( pos1 == -1 )
        return "";

    return source.substr ( pos1 + step );
}



// Explain: ���ݷָ��������ַ�����
// Problem:
// Author : adaM
// Date   : 2017-4-14
// History:
string strGet ( const string& source, const string& strB, const string& strE  )
{
   int pos1;
   int pos2;
   int step1, step2;

   step1 = strB.length();
   step2 = strE.length();

   pos1 = source.find(strB, 0);
   pos2 = source.find(strE, 0);

   if ( pos1 == -1 )
       pos1 = 0;
   if ( pos2 == -1 )
       return source.substr(pos1);

   return source.substr(pos1+step1, pos2-pos1-step1-step2+1);
}



// Explain: �������м��������ַ�
// Problem:
// Author : adaM
// Date   : 2017-4-14
// History:
string strCut ( const string& source, const string& strB, const string& strE  )
{
   int pos1;
   int pos2;
   string target;
   int step = strE.length();

   target = source;

   while (pos1 != -1)
   {
      pos1 = target.find(strB, 0);
      pos2 = target.find(strE, 0);

      if ( pos1 == -1 )
          continue;
      if ( pos2 == -1 )
          target = target.substr(0, pos1);

      target = target.substr(0, pos1) + target.substr(pos2+step);
   }
   return target;
}



// Explain: ����ֵ���滻Դ�ַ����е��ַ�����ԭ�ַ������޸ġ�
// Problem:
// Author : adaM
// Date   : 2010-9-12
// History:
string strRep( string context, const string& from, const string& to )
{
    using namespace std;
    size_t begin = 0;
    size_t pos;
    while(( pos = context.find( from, begin )) != string::npos )
    {
          context.replace( pos, from.size(), to );
          begin = pos + to.size();
    }
    return context;
}

//string to ascii
//  sample: ab --> 097098
//  adaM
//  2011-6-21
string str2asc( const string& src )
{
    using namespace std;
    string str_asc;
    unsigned int i;
    int i_asc;
    char c_asc[3];


    for( i=0; i<src.length(); i++ )
    {
        i_asc  = src[i];
        sprintf( c_asc, "%03d", i_asc );
        str_asc += c_asc;
    }
    return str_asc;
}


//ascii to string
//  sample: 097098 --> ab
//  adaM
//  2011-6-21
string asc2str( const string& src )
{
    using namespace std;
    string str;
    unsigned int i;
    char ch;
    string str_tmp;

    for( i=0; i<src.length(); i+=3 )
    {
        str_tmp = src.substr( i, 3 );
        ch = atoi( str_tmp.c_str());
        str +=ch;
    }
    return str;
}


//trim
//  sample: " ab" --> "ab"
//  adaM
//  2011-9-12
string trim( const string& str )
{
    return ltrim( rtrim( str ));
}
string ltrim( const string& str )
{
    int i,start;

    for (i=0; (str[i]!=0 && str[i]<=32); )
        i++;
    start=i;

    return str.substr(start,str.length()-start);
}
string rtrim( const string& str )
{
    int i,j,end;

    for(i=0,j=0; str[i]!=0; i++)
        j = ((str[i]<=32)? j+1 : 0);
    end=i-j;

    return str.substr(0,end);
}



//num2str
//  sample: 123 --> "123"
//  adaM
//  2013-6-8
string num2str( const long num )
{
    string str;
    char cNum[50];
    sprintf( cNum, "%ld", num );
    str = cNum;
    return str;
}
string num2str( const int num )
{
    string str;
    char cNum[50];
    sprintf( cNum, "%d", num );
    str = cNum;
    return str;
}


//��ĸת��ΪСд
string lower( const string& str )
{
	string result;
	char tmp[CHARMAX];
	char* p = tmp;

	strcpy(tmp, str.c_str());
	for (unsigned int i=0; i<str.length(); i++)
	{
	   if ((*p > 64) && (*p < 91))
	   	*p+=32;
	   p++;
	}
	result = tmp;
	return result;
}                      


//��ĸת��Ϊ��д
string upper( const string& str )
{
	string result;
	char tmp[CHARMAX];
	char* p = tmp;

	strcpy(tmp, str.c_str());
	for (unsigned int i=0; i<str.length(); i++)
	{
	   if ((*p > 64+32) && (*p < 91+32))
	   	*p-=32;
	   p++;
	}
	result = tmp;
	return result;
}                      


//��ֵת��Ϊ�ַ���
string to_str( const long& num )
{
	string result;
	char tmp[128];
	sprintf(tmp, "%ld", num);
	result = tmp;
	
	return result;
}                    

} // namespace usr
#endif
