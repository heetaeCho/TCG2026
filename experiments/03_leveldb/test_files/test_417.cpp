#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/iterator.h"

#include "leveldb/options.h"



using namespace leveldb;

using ::testing::_;

using ::testing::Return;



class MockIterator : public Iterator {

public:

    MOCK_METHOD0(Valid, bool());

    MOCK_METHOD0(SeekToFirst, void());

    MOCK_METHOD0(SeekToLast, void());

    MOCK_METHOD1(Seek, void(const Slice& target));

    MOCK_METHOD0(Next, void());

    MOCK_METHOD0(Prev, void());

    MOCK_METHOD0(key, const Slice());

    MOCK_METHOD0(value, const Slice());

    MOCK_METHOD0(status, Status());

};



class MockBlockFunction {

public:

    MOCK_METHOD3(Call, Iterator*(void*, const ReadOptions&, const Slice&));

};



TEST_F(MockIteratorTest_417, Valid_ReturnsFalseInitially_417) {

    MockIterator mock_index_iter;

    EXPECT_CALL(mock_index_iter, Valid()).WillOnce(Return(false));



    MockBlockFunction block_function_mock;

    ReadOptions options;



    Iterator* two_level_iterator = NewTwoLevelIterator(&mock_index_iter, 

                                                        [](void* arg, const ReadOptions& options, const Slice& target) {

                                                            return static_cast<MockBlockFunction*>(arg)->Call(arg, options, target);

                                                        }, 

                                                        &block_function_mock, 

                                                        options);



    EXPECT_FALSE(two_level_iterator->Valid());

    delete two_level_iterator;

}



TEST_F(MockIteratorTest_417, SeekToFirst_CallsIndexIterSeekToFirst_417) {

    MockIterator mock_index_iter;

    EXPECT_CALL(mock_index_iter, SeekToFirst()).Times(1);



    MockBlockFunction block_function_mock;

    ReadOptions options;



    Iterator* two_level_iterator = NewTwoLevelIterator(&mock_index_iter, 

                                                        [](void* arg, const ReadOptions& options, const Slice& target) {

                                                            return static_cast<MockBlockFunction*>(arg)->Call(arg, options, target);

                                                        }, 

                                                        &block_function_mock, 

                                                        options);



    two_level_iterator->SeekToFirst();

    delete two_level_iterator;

}



TEST_F(MockIteratorTest_417, Seek_CallsIndexIterSeek_417) {

    MockIterator mock_index_iter;

    EXPECT_CALL(mock_index_iter, Seek(_)).Times(1);



    MockBlockFunction block_function_mock;

    ReadOptions options;



    Iterator* two_level_iterator = NewTwoLevelIterator(&mock_index_iter, 

                                                        [](void* arg, const ReadOptions& options, const Slice& target) {

                                                            return static_cast<MockBlockFunction*>(arg)->Call(arg, options, target);

                                                        }, 

                                                        &block_function_mock, 

                                                        options);



    Slice target("target_key");

    two_level_iterator->Seek(target);

    delete two_level_iterator;

}



TEST_F(MockIteratorTest_417, Status_ReturnsOkInitially_417) {

    MockIterator mock_index_iter;

    EXPECT_CALL(mock_index_iter, status()).WillOnce(Return(Status::OK()));



    MockBlockFunction block_function_mock;

    ReadOptions options;



    Iterator* two_level_iterator = NewTwoLevelIterator(&mock_index_iter, 

                                                        [](void* arg, const ReadOptions& options, const Slice& target) {

                                                            return static_cast<MockBlockFunction*>(arg)->Call(arg, options, target);

                                                        }, 

                                                        &block_function_mock, 

                                                        options);



    EXPECT_TRUE(two_level_iterator->status().ok());

    delete two_level_iterator;

}
