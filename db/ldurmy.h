#ifndef _LDUR_MY_H_
#define _LDUR_MY_H_

#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/metadata.h>
#include <cppconn/prepared_statement.h>

#include <iostream>           //string, cerr, endl, auto_ptr

#include "ldurmap.h"          // get
#include "ldurstr.h"          // to_str



/*
 ***************************************************
   Explain: 常用SQL语句操作封装(MySQL)
   Usage  :
   IN     : str_con: user/passwd@//host:port/instant
   OUT    :
   Problem:
   Author : adaM
   Date   : 2018-4-10
   MEMO   : 安装 mysql-connector-c++。支持字符串返回值<4000，支持数组返回一千行
          : 使用 boost, yum install boost-devel [boost, boost-doc]
   History:
   Ver        Date        Author           Description
   ---------  ----------  ---------------  ------------------------------------
   1.0        2018-04-10  Adam             Create.
   1.2        2018-12-12  Adam             error() Add update msg, code
 ***************************************************
*/

namespace ldur
{
   using std::string;
   using std::cerr;
   using std::endl;
   using std::auto_ptr;
   using ldur::isNULL;
   using ldur::LDURMAP;


//MySQL Class
class SQLMY {
   private:
      sql::Driver* driver;
      sql::Connection* dbConn;
      static const int ResultNum = 1000;          //Result Max rows
      void error(sql::SQLException &e);
   public:
      bool status;                                //connect status, 0=false
      string msg, code;
      int cols;                                   //column count

      sql::Statement* stmt;
      sql::ResultSet* res;

      long num;                                   // result data number
      string val[2][ResultNum];                   // result data, key-value

      /* function */
      SQLMY(){
         status = false;
         driver = NULL;
         dbConn = NULL;
         stmt = NULL;
         res = NULL;
      };
      ~SQLMY(){
         delete res;
         delete stmt;
         delete dbConn;
         //delete driver;
      };
      
      int conn(LDURMAP& conn);                                                                                            //connect db: -1=Error
      int conn(const string& host, const string& port, const string& user, const string& passwd, const string& db);       //connect db: -1=Error
      int schema(const string& db);
      int value(string& result, const string& str_sql);                         //Result: string
      int value(long& result, const string& str_sql);                           //Result: long
      int value(const string& str_sql);                                         //Result: num=counts, key-value[][]

      long exec(const string& str_sql);                                         //execute SQL, stmt->getUpdateCount()
      int query(const string& str_sql);                                         //run SQL
};

int SQLMY::conn(LDURMAP& m_conn)
{
   string port, opt_reconnect, db;
   
   port = m_conn.get("port");
   port = isNULL(port.c_str(), "3306");
   
   int i_port = atol(port.c_str());
   opt_reconnect = m_conn.get("opt_reconnect");
   bool b_reconn = (opt_reconnect.c_str()==0)?true:false;
   db = m_conn.get("db");
   
   sql::ConnectOptionsMap connection_properties;

   connection_properties["hostName"] = m_conn.get("host");
   connection_properties["userName"] = m_conn.get("user");
   connection_properties["password"] = m_conn.get("passwd");
   connection_properties["port"    ] = i_port;
   connection_properties["OPT_RECONNECT"] = b_reconn;

   try
   {
      driver = get_driver_instance();
      dbConn = driver->connect(connection_properties);
      stmt = dbConn->createStatement();
      if (!db.empty())
         schema(db);
   }
   catch (sql::SQLException &e)
   {
      error(e);
      status = false;
      return -1;
   }
   msg = "";
   code = "";
   status = true;
   return 0;
}

int SQLMY::conn(const string& host, const string& port, const string& user, const string& passwd, const string& db)
{
   sql::ConnectOptionsMap connection_properties;
   int i_port = atol(port.c_str());

   connection_properties["hostName"] = host;
   connection_properties["port"    ] = i_port;
   connection_properties["userName"] = user;
   connection_properties["password"] = passwd;
   connection_properties["OPT_RECONNECT"] = true;

   try
   {
      driver = get_driver_instance();
      dbConn = driver->connect(connection_properties);
      stmt = dbConn->createStatement();
      if (!db.empty())
         schema(db);
   }
   catch (sql::SQLException &e)
   {
      error(e);
      status = false;
      return -1;
   }
   msg = "";
   code = "";
   status = true;
   return 0;
}

int SQLMY::schema(const string& db)
{
   try
   {
      dbConn->setSchema(db);
   }
   catch (sql::SQLException &e)
   {
      error(e);
      return -1;
   }
   status = true;
   return 0;
}


void SQLMY::error(sql::SQLException &e)                                       /* intercept OTL exceptions */
{
   /*
     MySQL Connector/C++ throws three different exceptions:

     - sql::MethodNotImplementedException (derived from sql::SQLException)
     - sql::InvalidArgumentException (derived from sql::SQLException)
     - sql::SQLException (derived from std::runtime_error)
   */
   //cerr << "# ERR: SQLException in " << __FILE__;
   //cerr << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
   /* what() (derived from std::runtime_error) fetches error message */
   //cerr << "# ERR: " << e.what();
   //cerr << " (MySQL error code: " << e.getErrorCode();
   //cerr << ", SQLState: " << e.getSQLState() << " )" << endl;
   msg = strRep(e.what(), "'", " ");
   code = to_str(e.getErrorCode());
}

/* 正常返回值为0, -1为错误。 */

// Explain: 取得SQL语句的一个字符串返回值
// Problem: 只能返回一个结果，多结果返回一个。
// Author : adaM
// Date   : 2018-4-10
// History:
int SQLMY::value(string &result, const string& str_sql)
{
   num = -1;
   if (!status)
   {
      result = "";
      return -1;
   }
    try
    {
       //auto_ptr<sql::Statement> stmt(dbConn->createStatement());
       //auto_ptr<sql::ResultSet>  res(stmt->executeQuery( str_sql ));
       res = stmt->executeQuery( str_sql );
       res->next();
       result = res->getString(1);
    }
    catch(sql::SQLException &e)
    {
       error(e);
       return -1;
    }
   num = 1;
   return 0;
}



// Explain: 取得SQL语句的一个整形返回值
// Problem: 只能返回一个结果，多结果返回第一个。
// Author : adaM
// Date   : 2018-4-10
// History:
int SQLMY::value(long& result, const string& str_sql)
{
   num = -1;
   result = -1;
   string str_tmp;
   if (!status)
   {
      return -1;
   }
   try
   {
      //auto_ptr<sql::Statement> stmt(dbConn->createStatement());
      //auto_ptr<sql::ResultSet>  res(stmt->executeQuery( str_sql ));
      res = stmt->executeQuery( str_sql );
      res->next();
      str_tmp = res->getString(1);
      result = atol(str_tmp.c_str());
   }
   catch(sql::SQLException &e)
   {
      error(e);
      return -1;
   }
   num = 1;
   return 0;
}



// Explain: 取得SQL语句单列多行字符串结果 num数据个数，value[]数据。
// Problem: 结果数据最多为ResultNum个。
// Author : adaM
// Date   : 2018-4-10
// History:
int SQLMY::value(const string& str_sql)
{
   int i = 0;
   num = -1;
   string str_tmp;
   if (!status)
   {
      return -1;
   }
   try
   {
      //auto_ptr<sql::Statement> stmt(dbConn->createStatement());
       //auto_ptr<sql::ResultSet>  res(stmt->executeQuery( str_sql ));
      res = stmt->executeQuery( str_sql );
      i = 0;
      while (res->next() || i >= ResultNum)
      {
         val[0][i++] = res->getString(1);
         val[1][i++] = res->getString(2);
      }
   }
   catch(sql::SQLException &e)
   {
       error(e);
       return -1;
   }
   num = i - 1;
   return 0;
}


// Explain: 执行SQL语句，返回影响的数据个数。
// Problem:
// Author : adaM
// Date   : 2018-4-10
// History:
long SQLMY::exec(const string& str_sql)
{
   num = -1;
   if (!status) return -1;

   try
   {
      //auto_ptr<sql::Statement> stmt(dbConn->createStatement());
      stmt->execute(str_sql);
      num = stmt->getUpdateCount();
   }
   catch(sql::SQLException &e)
   {
      error(e);
      return -1;
   }
   return num;
}


//ִrun SQL
int SQLMY::query(const string& str_sql)
{
   cols = -1;
   num = -1;
   if (!status) return -1;

   try
   {
      res = stmt->executeQuery( str_sql );
      cols = res->getMetaData()->getColumnCount();
   }
   catch(sql::SQLException &e)
   {
      error(e);
      return -1;
   }
   num = 0;
   return 0;
}

} // namespace ldur

#endif
