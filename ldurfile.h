#ifndef _LDUR_FILE_H_
#define _LDUR_FILE_H_
/*
 ***************************************************
    Explain: 读文件
           :
    Usage  :
    IN     :
    OUT    :
    Problem:
    Author : adaM
    Date   : 2011-6-20
    History:
 ***************************************************
*/
#include <iostream>
#include <fstream>

namespace ldur
{
using namespace std;

// Function Statement
string readFile( const string& );                                               // 将文件内容读至变量中，返回string
int writeFile( const string&, const string& );                                  // 将变量内容写入文件中，返回 1=成功 0=失败

// Explain: 将文件内容读至变量中，返回string
// Problem:
// Author : adaM
// Date   : 2011-6-20
// History:
string readFile( const string& filename )
{
    ifstream fin1;                                                             /* in FILE stream */
    string str1;
    string str_tmp;

    fin1.open( filename.c_str(), ios_base::in );                               /* open fin1 */
    if(!fin1)                                                                  // open file error
    {
        cerr << "Error opening " << filename << " for input" << endl;
        return "";
    }

    getline( fin1, str_tmp );
    while(fin1){
        str1 +=str_tmp;
        str1.append( "\n" );
        getline( fin1, str_tmp );
    }
    fin1.close();
    return str1;
}


// Explain: 将变量内容写入文件中，返回 1=成功 0=失败
// Problem:
// Author : adaM
// Date   : 2011-6-20
// History: 无后缀，加.txt
int writeFile( const string& filename, const string& str )
{
    ofstream fout;                                                             /* in FILE stream */
    string file;

    file = filename;
    if ( file.find( '.' ) == string::npos )
        file += ".txt";

    fout.open( file.c_str(), ios_base::out );                                  // open fin1
    if(!fout)                                                                  // open file error
    {
        cerr << "Error opening " << file << " for output" << endl;
        return 0;
    }

    fout << str;
    fout.close();

    return 1;
}



} // namespace usr
#endif
