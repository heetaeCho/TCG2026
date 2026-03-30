#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "port/port_stdcxx.h"



using namespace leveldb::port;



class MutexTest_32 : public ::testing::Test {

protected:

    Mutex mutex;

};



TEST_F(MutexTest_32, LockAndUnlockBasicOperation_32) {

    // Test normal operation of locking and unlocking

    mutex.Lock();

    mutex.Unlock();

}



TEST_F(MutexTest_32, DoubleLockSameThreadBoundaryCondition_32) {

    // Test boundary condition: double lock on the same thread

    mutex.Lock();

    EXPECT_DEATH(mutex.Lock(), ".*");

    mutex.Unlock();

}



TEST_F(MutexTest_32, UnlockWithoutLockExceptionalCase_32) {

    // Test exceptional case: unlock without prior lock

    EXPECT_DEATH(mutex.Unlock(), ".*");

}



TEST_F(MutexTest_32, LockUnlockOrderBoundaryCondition_32) {

    // Test boundary condition: correct order of lock and unlock

    mutex.Lock();

    mutex.AssertHeld();  // Assuming this asserts if the lock is not held

    mutex.Unlock();

}
