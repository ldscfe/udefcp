#ifndef _LDUR_INI_H_
#define _LDUR_INI_H_

/*
    ��ȡINI�ļ�
    INI�ļ���ʽ��������ֵ
    ����������#��ͷ��ע�ͺͿ��У���ͬ�ı�����������滻ǰ�档
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


/* ��INI�ļ������ؼ�¼�� */
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
        /* ȥ�����С�ע���С����س������س����� */
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
            c2 = strtok( NULL, CR);                                             /*�ж�ÿ����û�лس���*/
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
