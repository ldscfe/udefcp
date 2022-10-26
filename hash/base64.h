#ifndef _BASE64_H_
#define _BASE64_H_
/******************************************************************************
   Name     : base64.h
   Purpose  : hash - base64
   Author   : Adam
   Uses     : 
   Memo     : 

   Revisions:
   Ver        Date        Author           Description
   ---------  ----------  ---------------  ------------------------------------
   1.0        2010/04/18  Adam             Create
   1.1        2020/07/19  Adam             define base64/base64d

******************************************************************************/
#include <iostream>
#include <string>
using namespace std;


string base64(const string str1);
string base64d(const string str1);

string BASE64Encode(const char *Data, int DataByte)
{
	//Base64 Code
	const char EncodeTable[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	string strEncode;

	unsigned char Tmp[3]={0};
	int LineLength=0;

	for(int i=0;i<(int)(DataByte / 3);i++)
	{
        Tmp[1] = *Data++;
        Tmp[2] = *Data++;
        Tmp[3] = *Data++;

        strEncode+= EncodeTable[Tmp[1] >> 2];
        strEncode+= EncodeTable[((Tmp[1] << 4) | (Tmp[2] >> 4)) & 0x3F];
        strEncode+= EncodeTable[((Tmp[2] << 2) | (Tmp[3] >> 6)) & 0x3F];
        strEncode+= EncodeTable[Tmp[3] & 0x3F];
		if(LineLength+=4,LineLength==76) {strEncode+="\r\n";LineLength=0;}
	}

	//对剩余数据进行编码
	int Mod=DataByte % 3;
	if(Mod==1)
	{
        Tmp[1] = *Data++;
        strEncode+= EncodeTable[(Tmp[1] & 0xFC) >> 2];
        strEncode+= EncodeTable[((Tmp[1] & 0x03) << 4)];
        strEncode+= "==";
	}
	else if(Mod==2)
	{
		Tmp[1] = *Data++;
		Tmp[2] = *Data++;
		strEncode+= EncodeTable[(Tmp[1] & 0xFC) >> 2];
		strEncode+= EncodeTable[((Tmp[1] & 0x03) << 4) | ((Tmp[2] & 0xF0) >> 4)];
		strEncode+= EncodeTable[((Tmp[2] & 0x0F) << 2)];
		strEncode+= "=";
	}
	
	return strEncode;
}

string BASE64Decode(const char* Data, int DataByte)
{
	//解码表
	const char DecodeTable[] =
	{
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		62, 																		// '+'
		0, 0, 0,
		63, // '/'
		52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 						// '0'-'9'
		0, 0, 0, 0, 0, 0, 0,
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
		13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 		// 'A'-'Z'
		0, 0, 0, 0, 0, 0,
		26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
		39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 		// 'a'-'z'
	};

	//返回值
	string strDecode;

    int nValue;
    int i= 0;
 
    while (i < DataByte)
    {
        if (*Data != '\r' && *Data!='\n')
        {
            nValue = DecodeTable[(unsigned)*Data++] << 18;
            nValue += DecodeTable[(unsigned)*Data++] << 12;
				strDecode+=(nValue & 0x00FF0000) >> 16;
 
            if (*Data != '=')
            {
                nValue += DecodeTable[(unsigned)*Data++] << 6;
				    strDecode+=(nValue & 0x0000FF00) >> 8;
 
                if (*Data != '=')
                {
                    nValue += DecodeTable[(unsigned)*Data++];
					     strDecode+=nValue & 0x000000FF;
                }
            }
            i += 4;
        }
        else// 回车换行,跳过
        {
            Data++;
            i++;
        }
     }
	return strDecode;
}

string base64(const string str1)
{
   return BASE64Decode(str1.c_str(), str1.size());
}

string base64d(const string str1)
{
   return BASE64Decode(str1.c_str(), str1.size());
}

#endif
