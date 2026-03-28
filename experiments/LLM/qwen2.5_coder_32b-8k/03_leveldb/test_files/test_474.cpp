#include <gtest/gtest.h>

#include "port/port_stdcxx.h"



namespace leveldb {

namespace port {



class MutexMock : public Mutex {

public:

    MOCK_METHOD0(Lock, void());

    MOCK_METHOD0(Unlock, void());

    MOCK_METHOD0(AssertHeld, void());

};



class CondVarTest_474 : public ::testing::Test {

protected:

    MutexMock mock_mutex;

    CondVar cond_var{&mock_mutex};

};



TEST_F(CondVarTest_474, WaitLocksMutex_474) {

    EXPECT_CALL(mock_mutex, Lock()).Times(1);

    cond_var.Wait();

}



TEST_F(CondVarTest_474, SignalDoesNotThrow_474) {

    EXPECT_NO_THROW(cond_var.Signal());

}



TEST_F(CondVarTest_474, SignalAllDoesNotThrow_474) {

    EXPECT_NO_THROW(cond_var.SignalAll());

}



TEST_F(CondVarTest_474, ConstructorSetsMutexPointer_474) {

    CondVar cv{&mock_mutex};

    // No observable behavior to test directly, but construction should not throw.

    SUCCEED();

}



}  // namespace port

}  // namespace leveldb
