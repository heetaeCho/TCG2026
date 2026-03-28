#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/dfa.h"



namespace re2 {

namespace {



class DFA_RWLockerTest : public ::testing::Test {

protected:

    DFA::RWLocker* rw_locker_;

    CacheMutex mock_cache_mutex_;



    void SetUp() override {

        rw_locker_ = new DFA::RWLocker(&mock_cache_mutex_);

    }



    void TearDown() override {

        delete rw_locker_;

    }

};



TEST_F(DFA_RWLockerTest_LockForWriting_NonZeroInitial_M450, LockForWriting_UnlocksReader_M450) {

    EXPECT_CALL(mock_cache_mutex_, ReaderUnlock()).Times(1);

    delete rw_locker_;

}



TEST_F(DFA_RWLockerTest_LockForWriting_ZeroInitial_M450, LockForWriting_LocksWriter_M450) {

    EXPECT_CALL(mock_cache_mutex_, WriterLock()).Times(1);

    rw_locker_->LockForWriting();

}



TEST_F(DFA_RWLockerTest_Destructor_WritingTrue_M450, Destructor_UnlocksWriter_M450) {

    testing::InSequence seq;

    EXPECT_CALL(mock_cache_mutex_, WriterLock()).Times(1);

    rw_locker_->LockForWriting();



    EXPECT_CALL(mock_cache_mutex_, WriterUnlock()).Times(1);

}



TEST_F(DFA_RWLockerTest_Destructor_WritingFalse_M450, Destructor_UnlocksReader_M450) {

    EXPECT_CALL(mock_cache_mutex_, ReaderUnlock()).Times(1);

}



}  // namespace

}  // namespace re2
