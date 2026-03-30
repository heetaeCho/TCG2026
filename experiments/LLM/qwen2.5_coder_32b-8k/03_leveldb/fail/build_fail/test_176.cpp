#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "db/version_set.h"

#include "db/dbformat.h"

#include "db/version_edit.h"



using namespace leveldb;

using ::testing::ElementsAre;



class AddBoundaryInputsTest_176 : public ::testing::Test {

protected:

    InternalKeyComparator icmp;

    std::vector<FileMetaData*> level_files;

    std::vector<FileMetaData*> compaction_files;



    AddBoundaryInputsTest_176() : icmp(nullptr) {}



    ~AddBoundaryInputsTest_176() override {

        for (auto file : level_files) {

            delete file;

        }

        for (auto file : compaction_files) {

            delete file;

        }

    }



    void SetUp() override {

        // Setup some FileMetaData instances for testing

        auto* f1 = new FileMetaData();

        f1->smallest.DecodeFrom(Slice("a"));

        f1->largest.DecodeFrom(Slice("b"));

        level_files.push_back(f1);



        auto* f2 = new FileMetaData();

        f2->smallest.DecodeFrom(Slice("c"));

        f2->largest.DecodeFrom(Slice("d"));

        level_files.push_back(f2);



        auto* f3 = new FileMetaData();

        f3->smallest.DecodeFrom(Slice("e"));

        f3->largest.DecodeFrom(Slice("f"));

        level_files.push_back(f3);

    }

};



TEST_F(AddBoundaryInputsTest_176, NoCompactionFilesInitially_176) {

    compaction_files.clear();

    AddBoundaryInputs(icmp, level_files, &compaction_files);

    EXPECT_TRUE(compaction_files.empty());

}



TEST_F(AddBoundaryInputsTest_176, SingleFileInCompactionFiles_176) {

    auto* f = new FileMetaData();

    f->smallest.DecodeFrom(Slice("a"));

    f->largest.DecodeFrom(Slice("b"));

    compaction_files.push_back(f);



    AddBoundaryInputs(icmp, level_files, &compaction_files);

    EXPECT_EQ(compaction_files.size(), 2);

    EXPECT_EQ(compaction_files[1]->smallest.user_key().ToString(), "c");

}



TEST_F(AddBoundaryInputsTest_176, MultipleFilesInCompactionFiles_176) {

    auto* f1 = new FileMetaData();

    f1->smallest.DecodeFrom(Slice("a"));

    f1->largest.DecodeFrom(Slice("b"));

    compaction_files.push_back(f1);



    auto* f2 = new FileMetaData();

    f2->smallest.DecodeFrom(Slice("c"));

    f2->largest.DecodeFrom(Slice("d"));

    compaction_files.push_back(f2);



    AddBoundaryInputs(icmp, level_files, &compaction_files);

    EXPECT_EQ(compaction_files.size(), 3);

    EXPECT_EQ(compaction_files[2]->smallest.user_key().ToString(), "e");

}



TEST_F(AddBoundaryInputsTest_176, LargestKeyNotFoundInLevelFiles_176) {

    auto* f = new FileMetaData();

    f->smallest.DecodeFrom(Slice("x"));

    f->largest.DecodeFrom(Slice("y"));

    compaction_files.push_back(f);



    AddBoundaryInputs(icmp, level_files, &compaction_files);

    EXPECT_EQ(compaction_files.size(), 1);

}



TEST_F(AddBoundaryInputsTest_176, OverlappingFilesInLevelFiles_176) {

    auto* f = new FileMetaData();

    f->smallest.DecodeFrom(Slice("b"));

    f->largest.DecodeFrom(Slice("d"));

    compaction_files.push_back(f);



    AddBoundaryInputs(icmp, level_files, &compaction_files);

    EXPECT_EQ(compaction_files.size(), 3);

    EXPECT_EQ(compaction_files[1]->smallest.user_key().ToString(), "c");

}



TEST_F(AddBoundaryInputsTest_176, CompactionFilesLargestKeyEqualToLevelFileSmallestKey_176) {

    auto* f = new FileMetaData();

    f->smallest.DecodeFrom(Slice("a"));

    f->largest.DecodeFrom(Slice("c"));

    compaction_files.push_back(f);



    AddBoundaryInputs(icmp, level_files, &compaction_files);

    EXPECT_EQ(compaction_files.size(), 3);

    EXPECT_EQ(compaction_files[1]->smallest.user_key().ToString(), "c");

}



TEST_F(AddBoundaryInputsTest_176, NoFilesInLevelFiles_176) {

    level_files.clear();

    auto* f = new FileMetaData();

    f->smallest.DecodeFrom(Slice("a"));

    f->largest.DecodeFrom(Slice("b"));

    compaction_files.push_back(f);



    AddBoundaryInputs(icmp, level_files, &compaction_files);

    EXPECT_EQ(compaction_files.size(), 1);

}
