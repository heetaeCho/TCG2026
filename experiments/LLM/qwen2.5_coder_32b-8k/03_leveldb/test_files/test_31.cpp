#include <gtest/gtest.h>

#include "port/port_stdcxx.h"



using namespace leveldb::port;



class MutexTest_31 : public ::testing::Test {

protected:

    Mutex mutex_;

};



TEST_F(MutexTest_31, LockUnlocksSuccessfully_31) {

    // Test normal operation: Lock should not throw and allow unlocking

    EXPECT_NO_THROW(mutex_.Lock());

}



// Since the Unlock function is not provided in the initial code snippet,

// we assume it exists based on the known or inferred dependencies.

TEST_F(MutexTest_31, UnlockAfterLockDoesNotThrow_31) {

    mutex_.Lock();

    EXPECT_NO_THROW(mutex_.Unlock());

}



// Assuming AssertHeld is a debugging function that asserts if the mutex is not held,

// we can test it by locking and then calling AssertHeld.

TEST_F(MutexTest_31, AssertHeldAfterLockDoesNotThrow_31) {

    mutex_.Lock();

    EXPECT_NO_THROW(mutex_.AssertHeld());

}



// Test boundary conditions: Locking twice in a row without unlocking should not throw

// (though it's generally undefined behavior and not recommended)

TEST_F(MutexTest_31, DoubleLockDoesNotThrow_31) {

    mutex_.Lock();

    EXPECT_NO_THROW(mutex_.Lock());

}



// Test boundary conditions: Unlocking without locking should not throw

// (though it's generally undefined behavior and not recommended)

TEST_F(MutexTest_31, UnlockWithoutLockDoesNotThrow_31) {

    EXPECT_NO_THROW(mutex_.Unlock());

}
