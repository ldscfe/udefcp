#ifndef _LDUR_DEBUG_H_
#define _LDUR_DEBUG_H_
/*
   ����U_DEBUG


*/
namespace ldur
{

//�������ʱ��
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