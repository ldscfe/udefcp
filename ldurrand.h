#ifndef _LDUR_RAND_H_
#define _LDUR_RAND_H_
/*
 ***************************************************
    Explain: �������
    Usage  :
    IN     :
    OUT    :
    Problem: ���str1�ĳ���С��len���ᷢ��дδ֪�ڴ档
    Author : adaM(lds@tom.com)
    Date   : 2007-10-15
    History:
 ***************************************************
*/
#include <stdlib.h>     /* srand, rand */
#include "utime.h"

namespace ldur
{
using namespace std;

void randLower();                                                               /* ȡСд�ַ��� */
void randUpper();                                                               /* ȡСд�ַ��� */
void randStr();                                                                 /* ȡ����ַ��� */
void randNum();                                                                 /* ȡ�����ַ��� */

string randLower( int );                                                        /* ȡСд�ַ��� */
string randUpper( int );                                                        /* ȡСд�ַ��� */
string randStr( int );                                                          /* ȡ����ַ��� */
string randNum( int );                                                          /* ȡ�����ַ��� */

/* private function */
void randChar( char *str1, int len, int min, int max )
{
    int i;
    int str1_len;
    int c1;

    str1_len = len;

    srand(randMillisecs());
    for( i=0; i<str1_len; i++)
    {
        c1 = min + rand()%(max - min + 1);
        str1[i] = (char)c1;
    }
    str1[i] = '\0';
}

string randLower( int len )
{
    char str1[1024];
    randChar(str1, len, 97, 122);
    return str1;
}

string randUpper( int len )
{
    char str1[1024];
    randChar(str1, len, 65, 90);
    return str1;
}

string randStr( int len )
{
    char str1[1024];
    randChar(str1, len, 32, 126);
    return str1;
}

string randNum( int len )
{
    char str1[1024];
    randChar(str1, len, 48, 57);
    return str1;
}

void randLower(char *str1, int len)
{
    randChar(str1, len, 97, 122);
}


void randUpper(char *str1, int len)
{
    randChar(str1, len, 65, 90);
}


void randStr(char *str1, int len)
{
    randChar(str1, len, 32, 126);
}


void randNum(char *str1, int len)
{
    randChar(str1, len, 48, 57);
}



} // namespace usr
#endif
