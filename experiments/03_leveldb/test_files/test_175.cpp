#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "db/version_set.h"

#include "leveldb/comparator.h"

#include "db/dbformat.h"



using namespace leveldb;



class MockComparator : public Comparator {

public:

    MOCK_METHOD2(Compare, int(const Slice&, const Slice&));

    MOCK_CONST_METHOD0(Name, const char*());

    MOCK_METHOD2(FindShortestSeparator, void(std::string*, const Slice&));

    MOCK_METHOD1(FindShortSuccessor, void(std::string*));

};



class VersionSetTest_175 : public ::testing::Test {

protected:

    MockComparator mock_comparator;

    InternalKeyComparator icmp{ &mock_comparator };

    std::vector<FileMetaData*> level_files;



    void SetUp() override {

        // Setup some default FileMetaData instances for testing

        level_files.push_back(new FileMetaData());

        level_files.push_back(new FileMetaData());

        level_files.push_back(new FileMetaData());



        // Assign some mock InternalKey values

        level_files[0]->smallest = InternalKey(Slice("key1"), 1, kTypeValue);

        level_files[0]->largest = InternalKey(Slice("key3"), 3, kTypeValue);



        level_files[1]->smallest = InternalKey(Slice("key2"), 2, kTypeValue);

        level_files[1]->largest = InternalKey(Slice("key4"), 4, kTypeValue);



        level_files[2]->smallest = InternalKey(Slice("key3"), 3, kTypeValue);

        level_files[2]->largest = InternalKey(Slice("key5"), 5, kTypeValue);

    }



    void TearDown() override {

        for (auto file : level_files) {

            delete file;

        }

        level_files.clear();

    }

};



TEST_F(VersionSetTest_175, FindSmallestBoundaryFile_NormalOperation_175) {

    InternalKey largest_key(Slice("key3"), 3, kTypeValue);

    EXPECT_CALL(mock_comparator, Compare(_, _))

        .WillOnce(::testing::Return(-1)) // key1 vs key3

        .WillOnce(::testing::Return(0))  // key2 vs key3

        .WillOnce(::testing::Return(1));  // key3 vs key3



    FileMetaData* result = FindSmallestBoundaryFile(icmp, level_files, largest_key);

    EXPECT_EQ(result->smallest.user_key().ToString(), "key3");

}



TEST_F(VersionSetTest_175, FindSmallestBoundaryFile_BoundaryCondition_NoMatch_175) {

    InternalKey largest_key(Slice("key0"), 0, kTypeValue);

    EXPECT_CALL(mock_comparator, Compare(_, _))

        .WillOnce(::testing::Return(-1)) // key1 vs key0

        .WillOnce(::testing::Return(-1)) // key2 vs key0

        .WillOnce(::testing::Return(-1)); // key3 vs key0



    FileMetaData* result = FindSmallestBoundaryFile(icmp, level_files, largest_key);

    EXPECT_EQ(result, nullptr);

}



TEST_F(VersionSetTest_175, FindSmallestBoundaryFile_BoundaryCondition_AllMatch_175) {

    InternalKey largest_key(Slice("key2"), 2, kTypeValue);

    EXPECT_CALL(mock_comparator, Compare(_, _))

        .WillOnce(::testing::Return(-1)) // key1 vs key2

        .WillOnce(::testing::Return(0))  // key2 vs key2

        .WillOnce(::testing::Return(-1)); // key3 vs key2



    FileMetaData* result = FindSmallestBoundaryFile(icmp, level_files, largest_key);

    EXPECT_EQ(result->smallest.user_key().ToString(), "key2");

}



TEST_F(VersionSetTest_175, FindSmallestBoundaryFile_ExceptionalCase_EmptyList_175) {

    std::vector<FileMetaData*> empty_list;

    InternalKey largest_key(Slice("key3"), 3, kTypeValue);



    FileMetaData* result = FindSmallestBoundaryFile(icmp, empty_list, largest_key);

    EXPECT_EQ(result, nullptr);

}
