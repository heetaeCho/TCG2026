#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/iterator.h"

#include "db/c.cc"



using namespace leveldb;

using ::testing::Return;

using ::testing::_;



class MockIterator : public Iterator {

public:

    MOCK_METHOD(bool, Valid, (), (const override));

    MOCK_METHOD(void, SeekToFirst, (), (override));

    MOCK_METHOD(void, SeekToLast, (), (override));

    MOCK_METHOD(void, Seek, (const Slice &), (override));

    MOCK_METHOD(void, Next, (), (override));

    MOCK_METHOD(void, Prev, (), (override));

    MOCK_METHOD(const Slice, key, (), (const override));

    MOCK_METHOD(const Slice, value, (), (const override));

    MOCK_METHOD(const Status, status, (), (const override));

};



class IteratorTest_243 : public ::testing::Test {

protected:

    MockIterator mock_iterator;

    leveldb_iterator_t iter = {&mock_iterator};

    char* errptr = nullptr;



    void TearDown() override {

        if (errptr != nullptr) {

            free(errptr);

            errptr = nullptr;

        }

    }

};



TEST_F(IteratorTest_243, GetError_NoError_243) {

    EXPECT_CALL(mock_iterator, status())

        .WillOnce(Return(Status::OK()));

    

    leveldb_iter_get_error(&iter, &errptr);



    ASSERT_EQ(errptr, nullptr);

}



TEST_F(IteratorTest_243, GetError_NonEmptyError_243) {

    std::string error_message = "An error occurred";

    EXPECT_CALL(mock_iterator, status())

        .WillOnce(Return(Status::Corruption(error_message)));



    leveldb_iter_get_error(&iter, &errptr);



    ASSERT_NE(errptr, nullptr);

    ASSERT_STREQ(errptr, error_message.c_str());

}



TEST_F(IteratorTest_243, GetError_MultipleCalls_243) {

    std::string first_error = "First error";

    std::string second_error = "Second error";



    EXPECT_CALL(mock_iterator, status())

        .WillOnce(Return(Status::Corruption(first_error)))

        .WillOnce(Return(Status::NotFound(second_error)));



    leveldb_iter_get_error(&iter, &errptr);

    ASSERT_STREQ(errptr, first_error.c_str());

    free(errptr);

    errptr = nullptr;



    leveldb_iter_get_error(&iter, &errptr);

    ASSERT_STREQ(errptr, second_error.c_str());

}
