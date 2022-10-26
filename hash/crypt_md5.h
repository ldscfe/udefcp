#ifndef _CRYPT_MD5_H_
#define _CRYPT_MD5_H_
/*
 ***************************************************
    Explain: hash to string, MD5
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
using namespace std;

#include <string.h>

#include "md5.h"



string md5File( string strFilename )
{
    char md5_char[33];
    char filename[1024];

    strcpy( filename, strFilename.c_str() );

    if ( getMD5File( md5_char, filename) == -1 )
    {
        cout << "Can't Open Input File " << strFilename << endl;
        return "";
    }

    return md5_char;
}

string md5Str( string strIN )
{
    char md5_char[33];
    char str1[1024];

    strcpy( str1, strIN.c_str() );

    getMD5Str( md5_char, str1);

    return md5_char;
}


#endif


