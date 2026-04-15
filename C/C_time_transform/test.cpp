#include <stdio.h>
#include <time.h>

time_t time_cnt;
struct tm time_data;
char* time_str;

int main() {
    // time_cnt = time(NULL);
    time(&time_cnt);
    printf("%d\n",time_cnt);

    // time_data = *gmtime(&time_cnt);
    time_data = *localtime(&time_cnt);
    printf("%d\n",time_data.tm_year + 1900);
    printf("%d\n",time_data.tm_mon + 1);
    printf("%d\n",time_data.tm_mday);
    printf("%d\n",time_data.tm_hour);
    printf("%d\n",time_data.tm_min);
    printf("%d\n",time_data.tm_sec);

    time_cnt = mktime(&time_data); // 依据当地时间计算不是伦敦时间
    printf("%d\n",time_cnt);

    time_str = ctime(&time_cnt);
    printf(time_str);

    time_str = asctime(&time_data);
    printf(time_str);

    char t[50];
    strftime(t,50,"%H-%h-%S",&time_data);
    printf(t);

    return 0;
}