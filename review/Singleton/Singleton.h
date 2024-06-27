#ifndef __REVIEW_SINGLETON_H__
#define __REVIEW_SINGLETON_H__

#include <stdlib.h>
#include <pthread.h>

#include <string>
#include <mutex>

class Singleton
{
public:
    static Singleton & get_instance(const std::string & name);
    static void destroy();

private:
    static void init(const std::string & name);
    Singleton(const std::string & name);
    ~Singleton();
    Singleton(const Singleton &) = delete;
    Singleton & operator=(const Singleton &) = delete;

private:
    static Singleton * p_instance_;
    static std::once_flag flag_;
private:
    std::string name_;
};

#endif // __REVIEW_SINGLETON_H__
