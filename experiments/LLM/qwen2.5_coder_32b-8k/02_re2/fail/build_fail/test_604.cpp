#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/re2/re2/dfa.h"



namespace re2 {

    class DFA;

    class CacheMutex;



    class MockCacheMutex : public CacheMutex {

    public:

        MOCK_METHOD(void, ReaderLock, (), (override));

        MOCK_METHOD(void, LockForWriting, (), (override));

    };



    class DFATest_604 : public ::testing::Test {

    protected:

        std::unique_ptr<MockCacheMutex> mock_cache_mutex_;

        std::unique_ptr<DFA::RWLocker> rw_locker_;



        void SetUp() override {

            mock_cache_mutex_ = std::make_unique<MockCacheMutex>();

            rw_locker_ = std::make_unique<DFA::RWLocker>(mock_cache_mutex_.get());

        }

    };



    TEST_F(DFATest_604, ConstructorLocksForReading_604) {

        EXPECT_CALL(*mock_cache_mutex_, ReaderLock()).Times(1);

    }



    TEST_F(DFATest_604, LockForWritingCallsMutexMethod_604) {

        EXPECT_CALL(*mock_cache_mutex_, LockForWriting()).Times(1);

        rw_locker_->LockForWriting();

    }

}
