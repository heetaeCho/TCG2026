#include <gtest/gtest.h>

#include "db/version_set.h"

#include "leveldb/slice.h"



using namespace leveldb;



class VersionTest_150 : public ::testing::Test {

protected:

    Version version;

};



TEST_F(VersionTest_150, RecordReadSample_ValidInternalKey_150) {

    Slice internal_key("valid_internal_key");

    EXPECT_TRUE(version.RecordReadSample(internal_key));

}



TEST_F(VersionTest_150, RecordReadSample_InvalidInternalKey_150) {

    Slice invalid_internal_key("invalid_key");

    EXPECT_FALSE(version.RecordReadSample(invalid_internal_key));

}



TEST_F(VersionTest_150, RecordReadSample_NoMatchingFiles_150) {

    Slice internal_key("no_matching_files");

    EXPECT_FALSE(version.RecordReadSample(internal_key));

}



TEST_F(VersionTest_150, RecordReadSample_OneMatchingFile_150) {

    Slice internal_key("one_matching_file");

    EXPECT_FALSE(version.RecordReadSample(internal_key));

}



TEST_F(VersionTest_150, RecordReadSample_TwoMatchingFiles_150) {

    Slice internal_key("two_matching_files");

    EXPECT_TRUE(version.RecordReadSample(internal_key));

}



TEST_F(VersionTest_150, RecordReadSample_BoundaryCondition_EmptyKey_150) {

    Slice empty_key("");

    EXPECT_FALSE(version.RecordReadSample(empty_key));

}
