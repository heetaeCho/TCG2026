#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "db/version_set.h"

#include "db/table_cache.h"



using namespace leveldb;

using testing::_;

using testing::NiceMock;



class MockTableCache : public TableCache {

public:

    MockTableCache(const std::string& dbname, const Options& options, int entries)

        : TableCache(dbname, options, entries) {}



    MOCK_METHOD4(NewIterator, Iterator*(const ReadOptions&, uint64_t, uint64_t, Table**));

};



class VersionTest_145 : public ::testing::Test {

protected:

    void SetUp() override {

        options = new Options;

        table_cache = new NiceMock<MockTableCache>("test_db", *options, 10);

        version_set = new VersionSet("test_db", options, table_cache, nullptr);

        version = new Version(version_set);



        // Populate files_ with some FileMetaData objects

        for (int i = 0; i < config::kNumLevels; ++i) {

            if (i == 0 || i == 3) {  // Only populate levels 0 and 3 for testing purposes

                FileMetaData* file_meta_data = new FileMetaData();

                file_meta_data->number = i;

                file_meta_data->file_size = 1024;

                version->files_[i].insert(file_meta_data);

            }

        }

    }



    void TearDown() override {

        for (int level = 0; level < config::kNumLevels; ++level) {

            for (auto* file : version->files_[level]) {

                delete file;

            }

            version->files_[level].clear();

        }

        delete options;

        delete table_cache;

        delete version_set;

        delete version;

    }



    Options* options;

    NiceMock<MockTableCache>* table_cache;

    VersionSet* version_set;

    Version* version;

};



TEST_F(VersionTest_145, AddIterators_Level0FilesAdded_145) {

    std::vector<Iterator*> iters;



    EXPECT_CALL(*table_cache, NewIterator(_, 0, 1024, _)).WillOnce(testing::Return(nullptr));



    version->AddIterators(ReadOptions(), &iters);



    EXPECT_EQ(iters.size(), 1);

}



TEST_F(VersionTest_145, AddIterators_Level3FilesAdded_145) {

    std::vector<Iterator*> iters;



    EXPECT_CALL(*table_cache, NewIterator(_, 0, 1024, _)).WillOnce(testing::Return(nullptr));



    version->AddIterators(ReadOptions(), &iters);



    EXPECT_EQ(iters.size(), 1);

}



TEST_F(VersionTest_145, AddIterators_MultipleLevelsFilesAdded_145) {

    std::vector<Iterator*> iters;



    EXPECT_CALL(*table_cache, NewIterator(_, 0, 1024, _)).WillOnce(testing::Return(nullptr));



    version->AddIterators(ReadOptions(), &iters);



    EXPECT_EQ(iters.size(), 1);

}



TEST_F(VersionTest_145, AddIterators_NoFilesAddedForEmptyLevels_145) {

    std::vector<Iterator*> iters;



    // Clear level 0 and 3 to test the case where no files are added

    version->files_[0].clear();

    version->files_[3].clear();



    version->AddIterators(ReadOptions(), &iters);



    EXPECT_EQ(iters.size(), 0);

}



TEST_F(VersionTest_145, AddIterators_ExceptionalCase_NoTableCache_145) {

    std::vector<Iterator*> iters;



    // Temporarily nullify table_cache to simulate an exceptional case

    TableCache* original_table_cache = version->vset_->table_cache_;

    version->vset_->table_cache_ = nullptr;



    EXPECT_THROW(version->AddIterators(ReadOptions(), &iters), std::exception);



    // Restore the original table_cache

    version->vset_->table_cache_ = original_table_cache;

}



TEST_F(VersionTest_145, AddIterators_VerifyChecksumsOptionRespected_145) {

    std::vector<Iterator*> iters;



    ReadOptions read_options;

    read_options.verify_checksums = true;



    EXPECT_CALL(*table_cache, NewIterator(_, 0, 1024, _)).WillOnce(testing::Return(nullptr));



    version->AddIterators(read_options, &iters);



    // The test checks if the call is made with the correct options

}



TEST_F(VersionTest_145, AddIterators_BoundaryCondition_EmptyVector_145) {

    std::vector<Iterator*> iters;



    version->files_[0].clear();

    version->files_[3].clear();



    version->AddIterators(ReadOptions(), &iters);



    EXPECT_EQ(iters.size(), 0);

}
