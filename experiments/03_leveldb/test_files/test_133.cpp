#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/comparator.h"

#include "db/dbformat.h"



namespace leveldb {



class ComparatorMock : public Comparator {

public:

    MOCK_METHOD2(Compare, int(const Slice&, const Slice&));

    MOCK_CONST_METHOD0(Name, const char*());

    MOCK_METHOD2(FindShortestSeparator, void(std::string*, const Slice&));

    MOCK_METHOD1(FindShortSuccessor, void(std::string*));

};



class FileMetaDataTest_133 : public ::testing::Test {

protected:

    ComparatorMock comparator_mock;

    Slice user_key;

    std::unique_ptr<FileMetaData> file_meta;



    void SetUp() override {

        user_key = Slice("test_key");

        file_meta.reset(new FileMetaData());

        file_meta->smallest.user_key() = user_key;

    }

};



TEST_F(FileMetaDataTest_133, BeforeFile_UserKeyBeforeSmallest_133) {

    EXPECT_CALL(comparator_mock, Compare(user_key, file_meta->smallest.user_key()))

        .WillOnce(::testing::Return(-1));



    bool result = BeforeFile(&comparator_mock, &user_key, file_meta.get());

    EXPECT_TRUE(result);

}



TEST_F(FileMetaDataTest_133, BeforeFile_UserKeyEqualSmallest_133) {

    EXPECT_CALL(comparator_mock, Compare(user_key, file_meta->smallest.user_key()))

        .WillOnce(::testing::Return(0));



    bool result = BeforeFile(&comparator_mock, &user_key, file_meta.get());

    EXPECT_FALSE(result);

}



TEST_F(FileMetaDataTest_133, BeforeFile_UserKeyAfterSmallest_133) {

    EXPECT_CALL(comparator_mock, Compare(user_key, file_meta->smallest.user_key()))

        .WillOnce(::testing::Return(1));



    bool result = BeforeFile(&comparator_mock, &user_key, file_meta.get());

    EXPECT_FALSE(result);

}



TEST_F(FileMetaDataTest_133, BeforeFile_UserKeyNull_133) {

    Slice null_user_key;



    bool result = BeforeFile(&comparator_mock, nullptr, file_meta.get());

    EXPECT_FALSE(result);

}



} // namespace leveldb
