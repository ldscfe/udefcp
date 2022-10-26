#ifndef _LDUR_SSMTP_H_
#define _LDUR_SSMTP_H_
/*
 ***************************************************
    Explain: linux ssmtp 邮件发送
    Usage  :
    IN     :
    OUT    :
    Problem:
    Author : adaM(lds@tom.com)
    Date   : 2010-9-8
    History:
 ***************************************************
*/
#include <iostream>
#include <fstream>
#include <ldurrand.h>

namespace ldur
{
using namespace std;

int ssmtp( const string& writer, const string& maillist, const string& subject, const string& message )
{

    ofstream fout1;         /* out FILE stream */
    string filename;        /* file name */

    string strTmp;
    char tmp[100];

    //rand filename
    usr::randLower(tmp, 12);
    filename = "/tmp/";
    filename += tmp;

    fout1.open( filename.c_str(), ios_base::out);
    if(!fout1){
        cerr << "Error opening " << filename << " for output" << endl;
        exit(-1);
    }
    fout1 << "ssmtp "<< maillist << " << EOF" << endl;
    fout1 << "From: "<< writer << endl;
    fout1 << "To: " << maillist << endl;
    fout1 << "Subject: " << subject << endl;
    fout1 << message << endl;
    fout1 << "EOF" << endl;
    fout1.close();

    strTmp = "chmod 755 " + filename;
    system(strTmp.c_str());

    system(filename.c_str());

    strTmp = "rm " + filename;
    system(strTmp.c_str());


    return 0;
}


} // namespace usr
#endif
