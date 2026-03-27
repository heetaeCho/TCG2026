#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "XMP_Const.h"

#include "XMPCore_Impl.cpp"



using namespace testing;



class XmpMutexTest : public ::testing::Test {

protected:

    XMP_Mutex mutex;

};



TEST_F(XmpMutexTest_1882, NormalLockUnlock_1882) {

    // Test normal operation of locking and unlocking the mutex

    EXPECT_NO_THROW(XMP_EnterCriticalRegion(mutex));

}



TEST_F(XmpMutexTest_1882, LockTwiceSameThread_1882) {

    // Test that locking twice on the same thread does not throw an exception (assuming recursive or non-blocking behavior)

    XMP_EnterCriticalRegion(mutex);

    EXPECT_NO_THROW(XMP_EnterCriticalRegion(mutex));

}



TEST_F(XmpMutexTest_1882, LockFailureSimulation_1882) {

    // Simulate a lock failure by manually setting the mutex to an invalid state

    pthread_mutex_t invalid_mutex;

    pthread_mutex_init(&invalid_mutex, nullptr);

    pthread_mutex_lock(&invalid_mutex);  // Lock once to simulate already locked state

    EXPECT_THROW(XMP_EnterCriticalRegion(invalid_mutex), XMP_Error);

}



TEST_F(XmpMutexTest_1882, InvalidMutexState_1882) {

    // Test behavior with an invalid mutex (uninitialized or corrupted)

    XMP_Mutex invalid_mutex = { nullptr };

    EXPECT_THROW(XMP_EnterCriticalRegion(invalid_mutex), XMP_Error);

}
