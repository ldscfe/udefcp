#ifndef _LDURCONV_H_
#define _LDURCONV_H_

#include <string.h>
#include <iconv.h>            //code change

namespace ldur
{

using std::string;
//int cnNumConvert();                                                             // 中文数字转换阿拉伯数字

const int LDUR_CONV_MAX = 32000;

class LDURCONV
{
   private:
   	string out;
      iconv_t ic;
      size_t i, o;
      int result;
      char inbuf[LDUR_CONV_MAX+1], outbuf[LDUR_CONV_MAX+1];
      char* pi;
      char* po;

   public:
      string conv(const string& in);
      int set(const string& out, const string& in);
      
      LDURCONV() : ic(iconv_open("gb18030","utf-8")) {}
      LDURCONV(const char* to, const char* from) : ic(iconv_open(to,from)) {}
      LDURCONV(const string& to, const string& from) : ic(iconv_open(to.c_str(),from.c_str())) {}
      //LDURCONV(const string& to, const string& from) {set(to,from);}
      ~LDURCONV() {iconv_close(ic);}

};

string LDURCONV::conv( const string& in )
{   
   pi = inbuf;
   po = outbuf;

   o = (size_t) LDUR_CONV_MAX;
   i = (size_t)(in.size() + 1);

   strcpy(inbuf, in.c_str());
   memset(outbuf, 0, LDUR_CONV_MAX);


   result = iconv(ic , &pi, &i, &po, &o);
   if ((size_t)-1 == iconv(ic , &pi, &i, &po, &o))
      out = in;
   else
      out = outbuf;

   return out;
}



int LDURCONV::set(const string& out, const string& in) {
	iconv_close(ic);
	strcpy(inbuf, in.c_str());
	strcpy(outbuf, out.c_str());
	ic = iconv_open( outbuf, inbuf );
	return 0;
}


} // namespace usr
#endif
