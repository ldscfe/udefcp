#ifndef _LDUR_ORA_H_
#define _LDUR_ORA_H_

#define OTL_ORA19C                                                              /* Compile OTL 4/OCI9 */
#include <db/otlv4.h>

#include <iostream>

#include "ldurmap.h"          // get

/*
 ***************************************************
    Explain: 常用SQL语句操作封装(Oracle)
    Usage  :
    IN     : str_con: user/passwd@//host:port/instant
    OUT    :
    Problem:
    Author : adaM
    Date   : 2010-4-29
    MEMO   : 支持字符串返回值<65536, 支持数组返回一千行
    History:
 ***************************************************
*/

namespace ldur
{
   using std::string;
   using std::cerr;
   using std::endl;

class SQLORA {
   private:
      static const int ResultNum = 1000;
      static const int TmpCharLen = 65536;
      char strTmp[TmpCharLen+1];
      void error(otl_exception& err);
   public:
      bool status;
      string msg, code;                                                         // result info
      unsigned buf;

      long num;                                                                 // result data number from 0
      string val[2][ResultNum];                                                 // result data from 0

      otl_connect dbConn;                                                       // connect object
      otl_stream rs;

      /* function */
      SQLORA(){status = false;};
      ~SQLORA(){dbConn.logoff();};

      int conn(const string& str_con);                                          //连接数据库，1=Error
      int conn(const string& host, const string& port, const string& user, const string& passwd, const string& db);
      int value(string& result, const string& strSql);                          // 取得SQL语句的一个字符串返回值
      int value(int& result, const string& strSql);                             // 取得SQL语句的一个整型返回值
      int value(const string& strSql);                                          // 取得SQL语句单列多行字符串结果, num数据个数, val[]数据。

      long exec(const string& strSql);                                          // 执行SQL语句，返回影响的数据个数。

      int query(const string& sql);                                             //执行SQL

      otl_datetime odt(const string& strSql);                                   // 转换日期型数据 yyyy-mm-dd hh24:mi:ss
};


int SQLORA::conn(const string& str_con)
{
   char oraConnStr[1024];
   strcpy( oraConnStr, str_con.c_str());
   otl_connect::otl_initialize();                                             /* initialize OCI environment */

   try
   {
      dbConn.rlogon(oraConnStr);                                             /* connect to Oracle */
   }
   catch(otl_exception& p)                                                    /* intercept OTL exceptions */
   {
      error(p);
      return -1;
   }
   buf = 1000;
   status = true;
   return 0;
}

int SQLORA::conn(const string& host, const string& port, const string& user, const string& passwd, const string& db)
{
   string str_con = user + "/" + passwd + "@" + "//" + host + ":" + port + "/" + db;

   int i = conn(str_con);
   return i;
}
void SQLORA::error(otl_exception& err)
{
    cerr<<err.msg<<endl;                                                       /* print out error message */
    cerr<<err.stm_text<<endl;                                                  /* print out SQL that caused the error */
    cerr<<err.var_info<<endl;                                                  /* print out the variable that caused the error */
}

/* 正常返回值为0, -1为错误。 */

// Explain: 取得SQL语句的一个字符串返回值
// Problem: 只能返回一个结果，多结果返回一个。
// Author : adaM
// Date   : 2010-4-21
// History:
int SQLORA::value(string &result, const string& strSql)
{
   result = "";
   num = -1;
   if (!status) return -1;
   try
   {
      otl_stream dbExec(buf, strSql.c_str(), dbConn);                         /* run sql script */

      dbExec >> strTmp;
      result = strTmp;
   }
   catch(otl_exception& p)                                                    /* intercept OTL exceptions */
   {
      error(p);
      return -1;
   }
   num = 1;
   return 0;
}
// Explain: 取得SQL语句的一个整形返回值
// Problem: 只能返回一个结果，多结果返回一个。
// Author : adaM
// Date   : 2010-4-21
// History:
int SQLORA::value(int &result, const string& strSql)
{
   result = -1;
   num = -1;
   if (!status) {
      return -1;
   }
   try
   {
      otl_stream dbExec(buf, strSql.c_str(), dbConn);                         /* run sql script */
      dbExec >> result;
   }
   catch(otl_exception& p)                                                    /* intercept OTL exceptions */
   {
      error(p);
      return -1;
   }
   num = 1;
   return 0;
}


// Explain: 取得SQL语句单列多行字符串结果 num数据个数，value[]数据。
// Problem: 结果数据最多为ResultNum个。
// Author : adaM
// Date   : 2010-4-21
// History:
int SQLORA::value(const string& strSql)
{
   num = -1;
   if (!status) return -1;

   try
   {
      otl_stream dbExec(buf, strSql.c_str(), dbConn);                         /* run sql script */

      int i = 0;
      while(!dbExec.eof() || i >= ResultNum )
      {
         dbExec >> strTmp;
         val[0][i] = strTmp;
         dbExec >> strTmp;
         val[1][i] = strTmp;
         i++;
      }
      num = i - 1;
   }
   catch(otl_exception& p)                                                    /* intercept OTL exceptions */
   {
      error(p);
      return -1;
   }

   return 0;
}


// Explain: 执行SQL语句，返回影响的数据个数。
// Problem:
// Author : adaM
// Date   : 2010-4-22
// History:
long SQLORA::exec(const string& strSql)
{
   num = -1;
   if (!status) return -1;

   try
   {
      num = otl_cursor::direct_exec (dbConn, strSql.c_str());
   }
   catch(otl_exception& p)                                                    /* intercept OTL exceptions */
   {
      error(p);
      return -1;
   }
   return num;
}


//执行SQL
int SQLORA::query(const string& sql)
{
   num = -1;
   if (!status) return -1;

   try
   {
     rs.open(buf, sql.c_str(), dbConn);
     num = 1;
   }
   catch(otl_exception& p)                                                    /* intercept OTL exceptions */
   {
      error(p);
      return -1;
   }
   return num;
}

/* 转换日期型数据 yyyy-mm-dd hh24:mi:ss */
otl_datetime SQLORA::odt(const string& str)
{
   otl_datetime tm;
   char d[20];
   strcpy(d, str.c_str());
   int i = 0;
   tm.year  = (((d[i]-48)*10 + (d[i+1]-48))*10 + (d[i+2]-48))*10 + (d[i+3]-48);
   i+=4;
   tm.month = (d[i+1]-48)*10 + (d[i+2]-48);
   i+=3;
   tm.day   = (d[i+1]-48)*10 + (d[i+2]-48);
   i+=3;
   tm.hour  = (d[i+1]-48)*10 + (d[i+2]-48);
   i+=3;
   tm.minute= (d[i+1]-48)*10 + (d[i+2]-48);
   i+=3;
   tm.second= (d[i+1]-48)*10 + (d[i+2]-48);

   return tm;
}

} // namespace ldur

#endif
