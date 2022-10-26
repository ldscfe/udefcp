#ifndef _LDUR_MAP_H_
#define _LDUR_MAP_H_
/******************************************************************************
   Name     : ldurmap.h
   Purpose  : �ֵ��ࣺkey, value
   Author   : Adam
   Uses     : map, -std=c++11
   Memo     : ��ͬ��key�������value�滻ǰ��

   Revisions:
   Ver        Date        Author           Description
   ---------  ----------  ---------------  ------------------------------------
   1.0        2010/04/29  Adam             Create.
   1.1        2020/07/15  Adam             set ���� json ��ʽ�ַ���ת�ֵ�

******************************************************************************/
#include <iostream>
#include <map>

namespace ldur
{
   using std::string;                   //iostream
   using std::map;                      //map

class LDURMAP {
   private:
      map<string,string>::iterator _p, _h;       // mapָ��
      map<string,string> _md;                    // map����
   public:
      unsigned int size;
      unsigned int errs;

      void init();
      void begin();
      string get();
      string get(const string& key);
      string key(const string& val);
      bool set(const string& key, const string& value);
      bool set(const string& d_val);
      LDURMAP() {init();}
      ~LDURMAP() {init();}
};




void LDURMAP::init()
{
   _md.clear();
   _p = _md.begin();
   errs = size = 0;
}

void LDURMAP::begin()
{
   _p = _md.begin();
}

string LDURMAP::get()
{
   string str = "";
   if ( _p != _md.end() )
   {
      str = _p->second;
      if (_p != _md.end())
         _p++;
   }
   return str;
}


string LDURMAP::get(const string& key)
{
   _p = _md.find(key);
   if (_p != _md.end())
      return _p->second;
   return "";
}


string LDURMAP::key(const string& val)
{
   for (_h = _md.begin(); _h != _md.end(); _h++)
   {
      if (_h->second == val)
         return _h->first;
   }

   return "";
}

bool LDURMAP::set(const string& key, const string& value)
{
   //��ͬ��key�������value�滻ǰ�档
   unsigned int tmp;
   _md[key] = value;
   tmp = _md.size();
   if (size == tmp)
   {
      errs++;
      return false;
   }else{
      size = tmp;
      return true;
   }
}

// json ��ʽ�ַ���ת�ֵ�
bool LDURMAP::set(const string& d_val)
{
   bool b_f1;                // ���ű�ʶ
   bool b_fk;                // key ��ʶ

   string key, val;

   b_f1 = false;
   b_fk = true;
   for(auto c : d_val)
   {
      if(c == '\'')
      {
         b_f1 = !b_f1;
         continue;
      }

      if(b_f1)   //����������
      {
         if(b_fk)
            key += c;
         else
            val += c;
      }
      else
      {
         if(c == ' ' or c == '{')
            continue;

         if(c == ':')
         {
            b_fk = false;
            continue;
         }

         if(c == '}')
         {
            set(key, val);
            key = val = "";
            b_fk = true;
            break;
         }
         if(c == ',')
         {
            set(key, val);
            key = val = "";
            b_fk = true;
            continue;
         }

         if(b_fk)
            key += c;
         else
            val += c;
      }

   }


   return true;
}




}

#endif   // _LDUR_MAP_H_
