#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/iterator.h"

#include "table/iterator_wrapper.h"



using namespace leveldb;

using ::testing::_;

using ::testing::Return;



class MockIterator : public Iterator {

public:

    MOCK_METHOD(void, SeekToLast, (), (override));

    MOCK_METHOD(bool, Valid, (), (const, override));

};



class IteratorWrapperTest_386 : public ::testing::Test {

protected:

    std::unique_ptr<MockIterator> mock_iter;

    IteratorWrapper wrapper;



    void SetUp() override {

        mock_iter = std::make_unique<MockIterator>();

        wrapper.Set(mock_iter.get());

    }

};



TEST_F(IteratorWrapperTest_386, SeekToLast_CallsSeekToLastOnIterator_386) {

    EXPECT_CALL(*mock_iter, SeekToLast()).Times(1);

    wrapper.SeekToLast();

}



TEST_F(IteratorWrapperTest_386, SeekToLast_DoesNotCrashWithNullIterator_386) {

    wrapper.Set(nullptr);

    wrapper.SeekToLast();  // Should not crash

}



TEST_F(IteratorWrapperTest_386, SeekToLast_ReturnsCorrectlyBasedOnIteratorValidity_386) {

    EXPECT_CALL(*mock_iter, Valid()).WillOnce(Return(true));

    wrapper.SeekToLast();

    EXPECT_TRUE(wrapper.Valid());



    EXPECT_CALL(*mock_iter, Valid()).WillOnce(Return(false));

    wrapper.SeekToLast();

    EXPECT_FALSE(wrapper.Valid());

}
