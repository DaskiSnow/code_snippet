#include <stdlib.h>
#include <pthread.h>

#include <iostream>
#include <mutex>
#include <chrono>
#include <thread>
#include <functional>

#include "Singleton.h"

Singleton & Singleton::get_instance(const std::string & name)
{
    std::call_once(flag_, std::bind(init, std::cref(name)));
    return *p_instance_;
}

void Singleton::destroy()
{
    if (p_instance_)
    {
        delete p_instance_;
        p_instance_ = nullptr;
    }
}

void Singleton::init(const std::string & name)
{
    if (nullptr == p_instance_)
    {
        p_instance_ = new Singleton(name);
        atexit(destroy);
    }
}

Singleton::Singleton(const std::string & name)
: name_(name)
{
    std::cout << "Singleton(" << name_ << ")" << std::endl;
}

Singleton::~Singleton()
{
    std::cout << "~Singleton()" << std::endl;
}
Singleton * Singleton::p_instance_ = nullptr;
std::once_flag Singleton::flag_;

void exit_func()
{
    while(1)
    {
        std::cout << "exit_func()" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}


int main()
{
    Singleton & singleton = Singleton::get_instance("snow");
    Singleton & singleton2 = Singleton::get_instance("snow2");
    Singleton & singleton3 = Singleton::get_instance("yuki");
    return 0;
}

