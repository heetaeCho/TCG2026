#include <gtest/gtest.h>

#include "db/version_set.h"

#include <set>



using namespace leveldb;



class VersionTest_149 : public ::testing::Test {

protected:

    void SetUp() override {

        version = new Version(nullptr);

    }



    void TearDown() override {

        delete version;

    }



    Version* version;

};



TEST_F(VersionTest_149, UpdateStats_NullSeekFile_149) {

    GetStats stats{nullptr, 0};

    EXPECT_FALSE(version->UpdateStats(stats));

}



TEST_F(VersionTest_149, UpdateStats_AllowedSeeksGreaterThanZero_149) {

    FileMetaData file;

    file.allowed_seeks = 5;

    GetStats stats{&file, 0};

    EXPECT_FALSE(version->UpdateStats(stats));

}



TEST_F(VersionTest_149, UpdateStats_AllowedSeeksEqualToZero_149) {

    FileMetaData file;

    file.allowed_seeks = 0;

    GetStats stats{&file, 0};

    EXPECT_TRUE(version->UpdateStats(stats));

    EXPECT_EQ(file_to_compact(), &file);

}



TEST_F(VersionTest_149, UpdateStats_AllowedSeeksLessThanZero_149) {

    FileMetaData file;

    file.allowed_seeks = -1;

    GetStats stats{&file, 0};

    EXPECT_TRUE(version->UpdateStats(stats));

    EXPECT_EQ(file_to_compact(), &file);

}



TEST_F(VersionTest_149, UpdateStats_FileToCompactAlreadySet_149) {

    FileMetaData file1;

    file1.allowed_seeks = 0;

    version->UpdateStats(GetStats{&file1, 0});

    FileMetaData file2;

    file2.allowed_seeks = 0;

    GetStats stats{&file2, 0};

    EXPECT_FALSE(version->UpdateStats(stats));

}



FileMetaData* VersionTest_149::file_to_compact() {

    return version->file_to_compact_;

}

```


