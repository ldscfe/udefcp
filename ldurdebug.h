#ifndef _LDUR_DEBUG_H_
#define _LDUR_DEBUG_H_
/*
   定义U_DEBUG


*/
namespace ldur
{

//输出运行时间
int clock_begin = 0;
int runtimes()
{
    int clock2 = clock();
    int msecs = (clock2 - clock_begin)/1000;
    clock_begin = clock2;
    printf("msec: %10d ", msecs);
    return msecs;
}


} // namespace
#endif