/*************************************************************************
	> File Name: template_demo.h
	> Author: 
	> Mail: 
	> Created Time: 二  6/28 18:59:54 2016
 ************************************************************************/
#ifndef _TEMPLATE_DEMO_H
#define _TEMPLATE_DEMO_H

#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <map>
#include <string>

template<class P, class Loader> class DoubleBuf {
    public:
        DoubleBuf(int interval, Loader loader) :
            interval_(interval),
            loader_(loader),
            paramValid_(0)
        {}
        bool Run();
        P& getParam() { return params_[paramValid_]; }
    private:
        Loader loader_;
        P params_[2];
        int paramValid_;
        int interval_;
        static void* threadRun(void *arg);
        pthread_t calThread_;

};

class P {
    public:
        std::map<std::string, std::string> dict;
};

class Loader {
    public:
        bool load(P& param) {
            const time_t t = time(NULL);     
            struct tm* cur_time = localtime(&t);
            char tmp[1024];
            memset(tmp, 0, sizeof(tmp));
            sprintf(tmp, "%d-%d-%d %d:%d:%d", cur_time->tm_year + 1900, 
                    cur_time->tm_mon + 1, cur_time->tm_mday, cur_time->tm_hour, 
                    cur_time->tm_min, cur_time->tm_sec);
            std::string stime = tmp;
            param.dict["time"] = stime;
            return true;
        }
};
#endif
