#ifndef _LDUR_CRYPT_H_
#define _LDUR_CRYPT_H_
/*
 ***************************************************
    Explain: ×Ö·û´®¼ÓÃÜ
    Usage  :
    IN     :
    OUT    :
    Problem:
    Author : adaM
    Date   : 2011-4-16
    History:
 ***************************************************
*/
#include <iostream>
#include <fstream>
namespace ldur
{


using namespace std;

#include <string.h>

#include "base64.h"
#include "des.h"

string crypt( string str1 )
{
    char c1[1024] = "";
    char c2[1024] = "";

    strcpy (c1, str1.c_str());

    DESEncrypt( c2, c1 );

    return BASE64Encode( c2, strlen(c2) );
}

string decrypt( string str1 )
{
    char c1[1024] = "";
    char c2[1024] = "";
    string str2;

    strcpy (c1, str1.c_str());

    str2 = BASE64Decode( c1, strlen(c1));
    strcpy (c1, str2.c_str());
    DESDecrypt( c2, c1 );

    return c2;
}


} // namespace usr
#endif


