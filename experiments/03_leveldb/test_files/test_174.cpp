#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "db/version_set.h"

#include "db/dbformat.h"



using namespace leveldb;



class FindLargestKeyTest_174 : public ::testing::Test {

protected:

    InternalKeyComparator icmp;

    FileMetaData file1, file2, file3;

    std::vector<FileMetaData*> files;



    FindLargestKeyTest_174() : icmp(BytewiseComparator()) {

        file1.smallest = InternalKey("a", 1, kTypeValue);

        file1.largest = InternalKey("z", 1, kTypeValue);



        file2.smallest = InternalKey("b", 2, kTypeValue);

        file2.largest = InternalKey("y", 2, kTypeValue);



        file3.smallest = InternalKey("c", 3, kTypeValue);

        file3.largest = InternalKey("x", 3, kTypeValue);

    }

};



TEST_F(FindLargestKeyTest_174, SingleFile_174) {

    files.push_back(&file1);

    InternalKey largest_key;

    EXPECT_TRUE(FindLargestKey(icmp, files, &largest_key));

    EXPECT_EQ(largest_key.user_key().ToString(), "z");

}



TEST_F(FindLargestKeyTest_174, MultipleFiles_174) {

    files.push_back(&file1);

    files.push_back(&file2);

    files.push_back(&file3);

    InternalKey largest_key;

    EXPECT_TRUE(FindLargestKey(icmp, files, &largest_key));

    EXPECT_EQ(largest_key.user_key().ToString(), "z");

}



TEST_F(FindLargestKeyTest_174, EmptyFiles_174) {

    InternalKey largest_key;

    EXPECT_FALSE(FindLargestKey(icmp, files, &largest_key));

}



TEST_F(FindLargestKeyTest_174, LargestInMiddle_174) {

    files.push_back(&file2);

    files.push_back(&file3);

    files.push_back(&file1);

    InternalKey largest_key;

    EXPECT_TRUE(FindLargestKey(icmp, files, &largest_key));

    EXPECT_EQ(largest_key.user_key().ToString(), "z");

}



TEST_F(FindLargestKeyTest_174, LargestAtEnd_174) {

    files.push_back(&file2);

    files.push_back(&file3);

    files.push_back(&file1);

    InternalKey largest_key;

    EXPECT_TRUE(FindLargestKey(icmp, files, &largest_key));

    EXPECT_EQ(largest_key.user_key().ToString(), "z");

}



TEST_F(FindLargestKeyTest_174, LargestAtStart_174) {

    files.push_back(&file1);

    files.push_back(&file2);

    files.push_back(&file3);

    InternalKey largest_key;

    EXPECT_TRUE(FindLargestKey(icmp, files, &largest_key));

    EXPECT_EQ(largest_key.user_key().ToString(), "z");

}
