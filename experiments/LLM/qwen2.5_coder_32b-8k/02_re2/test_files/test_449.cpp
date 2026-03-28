#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mocking dependencies if needed

class CacheMutexMock : public re2::CacheMutex {

public:

    MOCK_METHOD(void, ReaderUnlock, (), (override));

    MOCK_METHOD(void, WriterLock, (), (override));

};



using ::testing::Return;

using ::testing::_;



namespace {



class DFA_RWLockerTest_449 : public ::testing::Test {

protected:

    CacheMutexMock cache_mutex_mock_;

    re2::DFA::RWLocker rw_locker_;



    DFA_RWLockerTest_449() : rw_locker_(&cache_mutex_mock_) {}

};



TEST_F(DFA_RWLockerTest_449, LockForWriting_UnlockedState_LocksWriter_449) {

    EXPECT_CALL(cache_mutex_mock_, ReaderUnlock()).Times(1);

    EXPECT_CALL(cache_mutex_mock_, WriterLock()).Times(1);



    rw_locker_.LockForWriting();

}



TEST_F(DFA_RWLockerTest_449, LockForWriting_AlreadyLockedState_DoesNotReLockWriter_449) {

    // Simulate that the locker is already in a writing state

    rw_locker_.LockForWriting();



    EXPECT_CALL(cache_mutex_mock_, ReaderUnlock()).Times(0);

    EXPECT_CALL(cache_mutex_mock_, WriterLock()).Times(0);



    rw_locker_.LockForWriting();

}



}  // namespace
