#include <gtest/gtest.h>

#include "db/version_set.h"

#include "db/dbformat.h"



using namespace leveldb;



class VersionSetTest_160 : public ::testing::Test {

protected:

    Options options;

    TableCache table_cache{nullptr, 10};

    InternalKeyComparator icmp{BytewiseComparator()};

    VersionSet vset{"dbname", &options, &table_cache, &icmp};



    std::vector<FileMetaData*> base_files[config::kNumLevels];

    FileSet added_files[config::kNumLevels];

    Version* base_version = new Version(&vset);

    Version* target_version = new Version(&vset);



    void SetUp() override {

        for (int level = 0; level < config::kNumLevels; ++level) {

            levels_[level].added_files = &added_files[level];

        }

    }



    void TearDown() override {

        delete base_version;

        delete target_version;



        for (auto& files : added_files) {

            for (FileMetaData* file : files) {

                delete file;

            }

        }



        for (int level = 0; level < config::kNumLevels; ++level) {

            for (FileMetaData* file : base_files[level]) {

                delete file;

            }

        }

    }



    Builder builder{&vset, base_version};



    LevelState levels_[config::kNumLevels];

};



TEST_F(VersionSetTest_160, SaveTo_EmptyFiles_160) {

    builder.SaveTo(target_version);

    for (int level = 0; level < config::kNumLevels; ++level) {

        EXPECT_TRUE(target_version->files_[level].empty());

    }

}



TEST_F(VersionSetTest_160, SaveTo_AddedFilesOnly_160) {

    FileMetaData* file1 = new FileMetaData();

    added_files[0].insert(file1);

    builder.SaveTo(target_version);



    EXPECT_EQ(target_version->files_[0].size(), 1);

    EXPECT_EQ(target_version->files_[0][0], file1);

}



TEST_F(VersionSetTest_160, SaveTo_BaseFilesOnly_160) {

    FileMetaData* base_file = new FileMetaData();

    base_files[0].push_back(base_file);

    builder.SaveTo(target_version);



    EXPECT_EQ(target_version->files_[0].size(), 1);

    EXPECT_EQ(target_version->files_[0][0], base_file);

}



TEST_F(VersionSetTest_160, SaveTo_MixedFiles_160) {

    FileMetaData* file1 = new FileMetaData();

    added_files[0].insert(file1);



    FileMetaData* base_file = new FileMetaData();

    base_files[0].push_back(base_file);

    builder.SaveTo(target_version);



    EXPECT_EQ(target_version->files_[0].size(), 2);

    EXPECT_TRUE(std::find(target_version->files_[0].begin(), target_version->files_[0].end(), file1) != target_version->files_[0].end());

    EXPECT_TRUE(std::find(target_version->files_[0].begin(), target_version->files_[0].end(), base_file) != target_version->files_[0].end());

}



TEST_F(VersionSetTest_160, SaveTo_MultipleLevels_160) {

    FileMetaData* file1 = new FileMetaData();

    added_files[0].insert(file1);



    FileMetaData* file2 = new FileMetaData();

    added_files[1].insert(file2);

    builder.SaveTo(target_version);



    EXPECT_EQ(target_version->files_[0].size(), 1);

    EXPECT_TRUE(std::find(target_version->files_[0].begin(), target_version->files_[0].end(), file1) != target_version->files_[0].end());



    EXPECT_EQ(target_version->files_[1].size(), 1);

    EXPECT_TRUE(std::find(target_version->files_[1].begin(), target_version->files_[1].end(), file2) != target_version->files_[1].end());

}



TEST_F(VersionSetTest_160, SaveTo_BaseFilesAlreadySorted_160) {

    FileMetaData* base_file1 = new FileMetaData();

    InternalKey key1;

    key1.SetFrom(ParsedInternalKey{"key1", 1, kTypeValue});

    base_file1->smallest = key1;



    FileMetaData* base_file2 = new FileMetaData();

    InternalKey key2;

    key2.SetFrom(ParsedInternalKey{"key2", 2, kTypeValue});

    base_file2->smallest = key2;



    base_files[0].push_back(base_file1);

    base_files[0].push_back(base_file2);



    builder.SaveTo(target_version);



    EXPECT_EQ(target_version->files_[0].size(), 2);

    EXPECT_TRUE(std::find(target_version->files_[0].begin(), target_version->files_[0].end(), base_file1) != target_version->files_[0].end());

    EXPECT_TRUE(std::find(target_version->files_[0].begin(), target_version->files_[0].end(), base_file2) != target_version->files_[0].end());



    // Ensure order is maintained

    EXPECT_EQ(target_version->files_[0][0], base_file1);

    EXPECT_EQ(target_version->files_[0][1], base_file2);

}



TEST_F(VersionSetTest_160, SaveTo_AddedFilesAlreadySorted_160) {

    FileMetaData* file1 = new FileMetaData();

    InternalKey key1;

    key1.SetFrom(ParsedInternalKey{"key1", 1, kTypeValue});

    file1->smallest = key1;



    FileMetaData* file2 = new FileMetaData();

    InternalKey key2;

    key2.SetFrom(ParsedInternalKey{"key2", 2, kTypeValue});

    file2->smallest = key2;



    added_files[0].insert(file1);

    added_files[0].insert(file2);



    builder.SaveTo(target_version);



    EXPECT_EQ(target_version->files_[0].size(), 2);

    EXPECT_TRUE(std::find(target_version->files_[0].begin(), target_version->files_[0].end(), file1) != target_version->files_[0].end());

    EXPECT_TRUE(std::find(target_version->files_[0].begin(), target_version->files_[0].end(), file2) != target_version->files_[0].end());



    // Ensure order is maintained

    EXPECT_EQ(target_version->files_[0][0], file1);

    EXPECT_EQ(target_version->files_[0][1], file2);

}



TEST_F(VersionSetTest_160, SaveTo_BaseFilesInterleavedWithAddedFiles_160) {

    FileMetaData* base_file1 = new FileMetaData();

    InternalKey key1;

    key1.SetFrom(ParsedInternalKey{"key1", 1, kTypeValue});

    base_file1->smallest = key1;



    FileMetaData* file2 = new FileMetaData();

    InternalKey key2;

    key2.SetFrom(ParsedInternalKey{"key2", 2, kTypeValue});

    file2->smallest = key2;



    FileMetaData* base_file3 = new FileMetaData();

    InternalKey key3;

    key3.SetFrom(ParsedInternalKey{"key3", 3, kTypeValue});

    base_file3->smallest = key3;



    added_files[0].insert(file2);

    base_files[0].push_back(base_file1);

    base_files[0].push_back(base_file3);



    builder.SaveTo(target_version);



    EXPECT_EQ(target_version->files_[0].size(), 3);

    EXPECT_TRUE(std::find(target_version->files_[0].begin(), target_version->files_[0].end(), file2) != target_version->files_[0].end());

    EXPECT_TRUE(std::find(target_version->files_[0].begin(), target_version->files_[0].end(), base_file1) != target_version->files_[0].end());

    EXPECT_TRUE(std::find(target_version->files_[0].begin(), target_version->files_[0].end(), base_file3) != target_version->files_[0].end());



    // Ensure order is maintained

    EXPECT_EQ(target_version->files_[0][0], base_file1);

    EXPECT_EQ(target_version->files_[0][1], file2);

    EXPECT_EQ(target_version->files_[0][2], base_file3);

}
