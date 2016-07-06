#include<iostream>
#include "template_demo.h"

template<class P, class Loader> 
void* DoubleBuf<P, Loader>::threadRun(void* arg) {
    DoubleBuf<P, Loader> *model = (DoubleBuf<P, Loader> *)arg;
    while(1) {
        sleep(model->interval_);
        int x = (model->paramValid_ + 1) % 2;
        bool ret = model->loader_.load(model->params_[x]);
        if(ret) {
            model->paramValid_ = x;
            //std::cout<<model->paramValid_<<std::endl;
        }
    }
    return NULL;
}
template<class P, class Loader>
bool DoubleBuf<P, Loader>::Run() {
    bool ret = this->loader_.load(params_[paramValid_]);
    if(ret == false) {
        return false;
    }
    int i = pthread_create(&this->calThread_, NULL, DoubleBuf<P, Loader>::threadRun, (void *)this);
    if (0 == i) {
        return true;
    } else {
        return false;
    }
}

int main() {
    Loader loader;
    //每三秒更新一次时间戳
    DoubleBuf<P, Loader> model(3, loader);
    model.Run();
    while(1) {
        std::cout<<model.getParam().dict["time"]<<std::endl;
        sleep(1);
    }
    return 0;
}
