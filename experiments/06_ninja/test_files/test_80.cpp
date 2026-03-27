#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "version.h"

#include "version.cc"  // Assuming this is how we include the function for testing



using ::testing::HasSubstr;



class VersionCheckTest_80 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize any necessary state before each test

    }

};



TEST_F(VersionCheckTest_80, CompatibleVersions_80) {

    EXPECT_NO_FATAL_FAILURE(CheckNinjaVersion("1.5"));

}



TEST_F(VersionCheckTest_80, BinMinorGreater_80) {

    EXPECT_NO_FATAL_FAILURE(CheckNinjaVersion("1.3"));

}



TEST_F(VersionCheckTest_80, BinMajorLess_80) {

    EXPECT_DEATH(CheckNinjaVersion("2.5"), HasSubstr("ninja version ("));

}



TEST_F(VersionCheckTest_80, BinMinorLess_80) {

    EXPECT_DEATH(CheckNinjaVersion("1.6"), HasSubstr("ninja version ("));

}



TEST_F(VersionCheckTest_80, SameMajorDifferentMinor_80) {

    EXPECT_NO_FATAL_FAILURE(CheckNinjaVersion("1.5"));  // Assuming kNinjaVersion is "1.4"

}



TEST_F(VersionCheckTest_80, SameVersions_80) {

    EXPECT_NO_FATAL_FAILURE(CheckNinjaVersion("1.4"));  // Assuming kNinjaVersion is "1.4"

}



TEST_F(VersionCheckTest_80, BinMajorGreaterFileMinorLess_80) {

    EXPECT_NO_FATAL_FAILURE(CheckNinjaVersion("2.3"));  // Assuming kNinjaVersion is "2.5"

}
