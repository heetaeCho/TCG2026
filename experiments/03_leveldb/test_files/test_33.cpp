#include <gtest/gtest.h>

#include "port/port_stdcxx.h"



using namespace leveldb::port;



class CondVarTest_33 : public ::testing::Test {

protected:

    Mutex mutex;

    CondVar cond_var;



    CondVarTest_33() : cond_var(&mutex) {}

};



TEST_F(CondVarTest_33, WaitDoesNotCrash_33) {

    mutex.Lock();

    cond_var.Wait();

    mutex.Unlock();

}



TEST_F(CondVarTest_33, SignalDoesNotCrash_33) {

    mutex.Lock();

    cond_var.Signal();

    mutex.Unlock();

}



TEST_F(CondVarTest_33, SignalAllDoesNotCrash_33) {

    mutex.Lock();

    cond_var.SignalAll();

    mutex.Unlock();

}
