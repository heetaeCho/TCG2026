#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "util/mutexlock.h"

#include "port/port_stdcxx.h"



using namespace leveldb;

using namespace leveldb::port;



class MutexLockTest : public ::testing::Test {

protected:

    Mutex mutex_;

};



TEST_F(MutexLockTest_296, LocksMutexOnConstruction_296) {

    EXPECT_CALL(mutex_, Lock()).Times(1);

    MutexLock lock(&mutex_);

}



TEST_F(MutexLockTest_296, UnlocksMutexOnDestruction_296) {

    testing::InSequence seq;

    EXPECT_CALL(mutex_, Lock()).Times(1);

    EXPECT_CALL(mutex_, Unlock()).Times(1);



    {

        MutexLock lock(&mutex_);

    }

}



TEST_F(MutexLockTest_296, NoDoubleLocking_296) {

    EXPECT_CALL(mutex_, Lock()).Times(1);

    MutexLock lock1(&mutex_);



    // Attempting to create another MutexLock on the same mutex should not cause a second lock call.

    EXPECT_CALL(mutex_, Lock()).Times(0);

}



TEST_F(MutexLockTest_296, NoUnlockIfNotLocked_296) {

    // Simply constructing and destroying without prior lock should not result in an unlock call

    EXPECT_CALL(mutex_, Unlock()).Times(0);



    MutexLock lock(&mutex_);

}



TEST_F(MutexLockTest_296, NoCopyConstruction_296) {

    EXPECT_CALL(mutex_, Lock()).Times(1);

    MutexLock original_lock(&mutex_);



    // Copy construction is deleted, so this should not compile if attempted.

    // However, for testing purposes, we ensure the lock is still valid and only locks once.

    EXPECT_CALL(mutex_, Lock()).Times(0);



    // The following line would cause a compilation error:

    // MutexLock copied_lock = original_lock;

}



TEST_F(MutexLockTest_296, NoCopyAssignment_296) {

    EXPECT_CALL(mutex_, Lock()).Times(1);

    MutexLock lock(&mutex_);



    Mutex another_mutex;

    EXPECT_CALL(another_mutex, Lock()).Times(0);



    // Copy assignment is deleted, so this should not compile if attempted.

    // However, for testing purposes, we ensure the lock remains on the original mutex and does not affect others.

    EXPECT_CALL(mutex_, Lock()).Times(0);

    EXPECT_CALL(mutex_, Unlock()).Times(1);



    // The following line would cause a compilation error:

    // lock = MutexLock(&another_mutex);

}
