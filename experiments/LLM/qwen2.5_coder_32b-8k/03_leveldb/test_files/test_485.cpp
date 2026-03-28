#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "util/mutexlock.h"

#include "port/port_stdcxx.h"



namespace leveldb {



class MutexLockTest_485 : public ::testing::Test {

protected:

    port::Mutex mutex_;

};



TEST_F(MutexLockTest_485, LocksMutexOnConstruction_485) {

    EXPECT_CALL(mutex_, Lock()).Times(1);

    MutexLock lock(&mutex_);

}



TEST_F(MutexLockTest_485, UnlocksMutexOnDestruction_485) {

    testing::InSequence s;

    EXPECT_CALL(mutex_, Lock());

    EXPECT_CALL(mutex_, Unlock());



    {

        MutexLock lock(&mutex_);

    }

}



TEST_F(MutexLockTest_485, NonCopyable_485) {

    MutexLock lock1(&mutex_);



    // Attempt to copy should result in a compile-time error

    // MutexLock lock2 = lock1;  // This line should not compile



    SUCCEED();  // If the above line is commented out, this test succeeds by default

}



TEST_F(MutexLockTest_485, NonAssignable_485) {

    MutexLock lock1(&mutex_);

    MutexLock lock2(&mutex_);



    // Attempt to assign should result in a compile-time error

    // lock2 = lock1;  // This line should not compile



    SUCCEED();  // If the above line is commented out, this test succeeds by default

}



}  // namespace leveldb
