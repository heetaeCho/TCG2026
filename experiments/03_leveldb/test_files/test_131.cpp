#include <gtest/gtest.h>

#include "db/version_set.cc"

#include "leveldb/slice.h"

#include "db/dbformat.h"



namespace leveldb {



class FindFileTest_131 : public ::testing::Test {

protected:

    InternalKeyComparator icmp;

    std::vector<FileMetaData*> files;



    FindFileTest_131() : icmp(new Comparator()) {}



    ~FindFileTest_131() {

        for (auto file : files) {

            delete file;

        }

    }



    void SetUp() override {

        // Setup test data if necessary

    }



    void TearDown() override {

        // Cleanup test data if necessary

    }

};



TEST_F(FindFileTest_131, EmptyFiles_131) {

    Slice key("test_key");

    EXPECT_EQ(0, FindFile(icmp, files, key));

}



TEST_F(FindFileTest_131, SingleFileMatch_131) {

    FileMetaData* file = new FileMetaData();

    file->largest.Encode() = "z";

    files.push_back(file);



    Slice key("a");

    EXPECT_EQ(0, FindFile(icmp, files, key));



    key = "z";

    EXPECT_EQ(1, FindFile(icmp, files, key));

}



TEST_F(FindFileTest_131, MultipleFilesMatch_131) {

    FileMetaData* file1 = new FileMetaData();

    file1->largest.Encode() = "b";



    FileMetaData* file2 = new FileMetaData();

    file2->largest.Encode() = "d";



    files.push_back(file1);

    files.push_back(file2);



    Slice key("a");

    EXPECT_EQ(0, FindFile(icmp, files, key));



    key = "c";

    EXPECT_EQ(1, FindFile(icmp, files, key));



    key = "e";

    EXPECT_EQ(2, FindFile(icmp, files, key));

}



TEST_F(FindFileTest_131, BoundaryCondition_131) {

    FileMetaData* file1 = new FileMetaData();

    file1->largest.Encode() = "b";



    FileMetaData* file2 = new FileMetaData();

    file2->largest.Encode() = "d";



    files.push_back(file1);

    files.push_back(file2);



    Slice key("b");

    EXPECT_EQ(1, FindFile(icmp, files, key));



    key = "d";

    EXPECT_EQ(2, FindFile(icmp, files, key));

}



} // namespace leveldb
