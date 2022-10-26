#ifndef _LDUR_INFO_H_
#define _LDUR_INFO_H_
#include <unistd.h>
#include "ldurstr.h"

namespace ldur
{

string pid()
{
   return to_str(getpid()) + "," + to_str(getppid());
}

void udebug(const string& info, const int& i, const int& debug)
{
   if ((debug - i) >= 0)
      cout << info << endl;
}


} // namespace ldur

#endif