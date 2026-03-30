#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "db/version_set.h"

#include "leveldb/slice.h"

#include "db/dbformat.h"



namespace leveldb {



class ComparatorMock : public Comparator {

public:

    MOCK_CONST_METHOD1(Name, const char*());

    MOCK_CONST_METHOD2(Compare, int(const Slice&, const Slice&));

    MOCK_METHOD2(FindShortestSeparator, void(std::string*, const Slice&));

    MOCK_METHOD1(FindShortSuccessor, void(std::string*));

};



class FileMetaDataMock : public FileMetaData {

public:

    MOCK_CONST_METHOD0(smallest, InternalKey());

    MOCK_CONST_METHOD0(largest, InternalKey());

};



class SomeFileOverlapsRangeTest_134 : public ::testing::Test {

protected:

    ComparatorMock comparator;

    InternalKeyComparator icmp{&comparator};

};



TEST_F(SomeFileOverlapsRangeTest_134, NoFilesProvided_134) {

    std::vector<FileMetaData*> files;

    EXPECT_FALSE(SomeFileOverlapsRange(icmp, false, files, nullptr, nullptr));

}



TEST_F(SomeFileOverlapsRangeTest_134, SingleFileNoOverlap_134) {

    FileMetaDataMock file_mock;

    std::vector<FileMetaData*> files{&file_mock};



    Slice smallest_user_key("a");

    Slice largest_user_key("c");



    EXPECT_CALL(comparator, Compare(_, _))

        .WillOnce(::testing::Return(-1))  // AfterFile

        .WillOnce(::testing::Return(1));   // BeforeFile



    EXPECT_FALSE(SomeFileOverlapsRange(icmp, false, files, &smallest_user_key, &largest_user_key));

}



TEST_F(SomeFileOverlapsRangeTest_134, SingleFileOverlap_134) {

    FileMetaDataMock file_mock;

    std::vector<FileMetaData*> files{&file_mock};



    Slice smallest_user_key("a");

    Slice largest_user_key("c");



    EXPECT_CALL(comparator, Compare(_, _))

        .WillOnce(::testing::Return(0))  // Not AfterFile

        .WillOnce(::testing::Return(0));  // Not BeforeFile



    EXPECT_TRUE(SomeFileOverlapsRange(icmp, false, files, &smallest_user_key, &largest_user_key));

}



TEST_F(SomeFileOverlapsRangeTest_134, MultipleFilesNoOverlap_134) {

    FileMetaDataMock file_mock1;

    FileMetaDataMock file_mock2;

    std::vector<FileMetaData*> files{&file_mock1, &file_mock2};



    Slice smallest_user_key("a");

    Slice largest_user_key("c");



    EXPECT_CALL(comparator, Compare(_, _))

        .WillOnce(::testing::Return(-1))  // AfterFile for file1

        .WillOnce(::testing::Return(1))   // BeforeFile for file1

        .WillOnce(::testing::Return(-1))  // AfterFile for file2

        .WillOnce(::testing::Return(1));   // BeforeFile for file2



    EXPECT_FALSE(SomeFileOverlapsRange(icmp, false, files, &smallest_user_key, &largest_user_key));

}



TEST_F(SomeFileOverlapsRangeTest_134, MultipleFilesOverlap_134) {

    FileMetaDataMock file_mock1;

    FileMetaDataMock file_mock2;

    std::vector<FileMetaData*> files{&file_mock1, &file_mock2};



    Slice smallest_user_key("a");

    Slice largest_user_key("c");



    EXPECT_CALL(comparator, Compare(_, _))

        .WillOnce(::testing::Return(0))  // Not AfterFile for file1

        .WillOnce(::testing::Return(0));  // Not BeforeFile for file1



    EXPECT_TRUE(SomeFileOverlapsRange(icmp, false, files, &smallest_user_key, &largest_user_key));

}



TEST_F(SomeFileOverlapsRangeTest_134, DisjointSortedFilesNoOverlap_134) {

    FileMetaDataMock file_mock1;

    FileMetaDataMock file_mock2;

    std::vector<FileMetaData*> files{&file_mock1, &file_mock2};



    Slice smallest_user_key("a");

    Slice largest_user_key("c");



    EXPECT_CALL(comparator, Compare(_, _))

        .WillOnce(::testing::Return(-1))  // AfterFile for file1

        .WillOnce(::testing::Return(0))   // Not BeforeFile for file1 (smallest_user_key in range)

        .WillOnce(::testing::Return(-1));  // AfterFile for file2 (largest_user_key not in range)



    EXPECT_FALSE(SomeFileOverlapsRange(icmp, true, files, &smallest_user_key, &largest_user_key));

}



TEST_F(SomeFileOverlapsRangeTest_134, DisjointSortedFilesOverlap_134) {

    FileMetaDataMock file_mock1;

    FileMetaDataMock file_mock2;

    std::vector<FileMetaData*> files{&file_mock1, &file_mock2};



    Slice smallest_user_key("a");

    Slice largest_user_key("c");



    EXPECT_CALL(comparator, Compare(_, _))

        .WillOnce(::testing::Return(0))   // Not AfterFile for file1 (smallest_user_key in range)

        .WillOnce(::testing::Return(0));   // Not BeforeFile for file1



    EXPECT_TRUE(SomeFileOverlapsRange(icmp, true, files, &smallest_user_key, &largest_user_key));

}



TEST_F(SomeFileOverlapsRangeTest_134, NullSmallestUserKey_134) {

    FileMetaDataMock file_mock;

    std::vector<FileMetaData*> files{&file_mock};



    Slice largest_user_key("c");



    EXPECT_CALL(comparator, Compare(_, _))

        .WillOnce(::testing::Return(0))   // Not BeforeFile for file1



    EXPECT_TRUE(SomeFileOverlapsRange(icmp, false, files, nullptr, &largest_user_key));

}



TEST_F(SomeFileOverlapsRangeTest_134, NullLargestUserKey_134) {

    FileMetaDataMock file_mock;

    std::vector<FileMetaData*> files{&file_mock};



    Slice smallest_user_key("a");



    EXPECT_CALL(comparator, Compare(_, _))

        .WillOnce(::testing::Return(0));   // Not AfterFile for file1



    EXPECT_TRUE(SomeFileOverlapsRange(icmp, false, files, &smallest_user_key, nullptr));

}



TEST_F(SomeFileOverlapsRangeTest_134, BothNullUserKeys_134) {

    FileMetaDataMock file_mock;

    std::vector<FileMetaData*> files{&file_mock};



    EXPECT_TRUE(SomeFileOverlapsRange(icmp, false, files, nullptr, nullptr));

}



}  // namespace leveldb
