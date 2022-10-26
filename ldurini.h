#ifndef _LDUR_INI_H_
#define _LDUR_INI_H_

/*
    读取INI文件
    INI文件格式：变量＝值
    可以允许以#开头的注释和空行，相同的变量，后面的替换前面。
*/

#include <iostream>
#include <fstream>
#include <map>
#include <cstring>
#include "ldurstr.h"
#include "ldurmap.h"

namespace ldur
{
using namespace std;
using ldur::strGet;
using ldur::LDURMAP;

#define NOTE        "#"
#define EQU         "="
#define SPACE       " "                                    //0x20
#define CR          "\r"                                   //0x0d
#define CRLF        "\r\n"                                 //0xod0a
#define TYP         "["


class LDURINI {
   private:
		static const int LineMax = 65536;
		LDURMAP _mp;
    public:
		int size;

		int set( string filename );
		string get( string str1, string str2 );
};


/* 读INI文件，返回记录数 */
int LDURINI::set( string filename )
{
    ifstream fin1;                                          /* in FILE stream */
    string str_line;                                        /* line from ini file */

    char line[LineMax];
    string s0;
    string s1;
    string s2;
    char *c1, *c2;

    fin1.open( filename.c_str(), ios_base::in );                                /* open fin1 */
    if(!fin1)                                                                   /* Cannot open file, output error infomation */
    {
        //cout << "Error opening " << filename << " for input" << endl;
        size = 0;
        return size;
    }

    s0 = "";
    while(fin1){
        getline( fin1, str_line );                                              /* get line from ini file */
        strcpy( line, str_line.c_str() );
        /* 去掉空行、注释行、仅回车、仅回车换行 */
        if ( !strlen(line) || !strncmp(line,NOTE,1) || !strcmp(line,CR) || !strcmp(line,CRLF) )
        {
            continue;
        }
        if(!strncmp(line,TYP,1))
        {
           s0 = strGet(line, "[", "]");
        }
        c1 = strtok( line, EQU );
        c2 = strtok( NULL, CRLF);

        if ( !c2 )
        {
            c2 = strtok( NULL, CR);                                             /*判断每行有没有回车符*/
        }
        if ( !c1 || !c2 )
        {
            continue;
        }
        s1 = c1;
        s2 = c2;

        _mp.set(s0+"|"+s1, s2);

    }
    size = _mp.size;
    return size;
}


string LDURINI::get( string s0, string s1 )
{
    return _mp.get(s0+"|"+s1);
}



} // namespace usr
#endif
