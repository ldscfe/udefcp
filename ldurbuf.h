#ifndef _LDUR_BUF_H_
#define _LDUR_BUF_H_
#include <pthread.h>

namespace ldur
{
class UBUF {
   private:
      static pthread_mutex_t ubuf_lock;
      static const unsigned int UBUF_MAX = 65535;
      void init(const string& _part);
   public:
      unsigned short flag;                        //0=null, 1=use, 2=finish
      unsigned short top;
      unsigned short bottom;
      unsigned int len;
      unsigned short cols;                        //str_content字段数，以part分隔 =0为自动计算
      string part;                                //分隔串
      string str_content[UBUF_MAX];

      /* function */

      int push(string& str1);
      int pop(string& str1);

   UBUF() {
      init('5');
   }
   UBUF(const string& _part) {
      init(part);
   }
   ~UBUF() { flag = 0; pthread_mutex_destroy(&ubuf_lock);}
};

void UBUF::init(const string& _part)
{
	pthread_mutex_init(&ubuf_lock, NULL);
   flag = len = top = bottom = 0;
   part = _part;
   cols = 0;
}
	

int UBUF::push(string& str1)
{
   if (len < UBUF_MAX) {
   	str_content[bottom] = str1;
   	if ( bottom >= UBUF_MAX - 1 )
   		bottom = 0;
      else
   		bottom++;

   	pthread_mutex_lock(&ubuf_lock);
      len++;
      pthread_mutex_unlock(&ubuf_lock);


   	return 0;
   }
   else
   {
     return 1;
   }
}
int UBUF::pop(string& str1)
{
   if (len > 0) {
      str1 = str_content[top];
      if ( top >= UBUF_MAX - 1 )
      	top = 0;
      else
      	top++;

   	pthread_mutex_lock(&ubuf_lock);
      len--;
      pthread_mutex_unlock(&ubuf_lock);

   	return 0;
   }
   else
   {
     return 1;
   }
}

} // namespace
#endif
