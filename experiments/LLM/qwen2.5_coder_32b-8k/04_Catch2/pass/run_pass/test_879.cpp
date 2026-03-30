#include <gtest/gtest.h>

#include "catch2/catch_version.hpp"



namespace {



class CatchVersionTest_879 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup can be used to initialize objects if necessary

    }



    void TearDown() override {

        // Cleanup can be performed here if necessary

    }

};



TEST_F(CatchVersionTest_879, LibraryVersionReturnsCorrectMajorVersion_879) {

    const Catch::Version& version = Catch::libraryVersion();

    EXPECT_EQ(version.majorVersion, 3);

}



TEST_F(CatchVersionTest_879, LibraryVersionReturnsCorrectMinorVersion_879) {

    const Catch::Version& version = Catch::libraryVersion();

    EXPECT_EQ(version.minorVersion, 8);

}



TEST_F(CatchVersionTest_879, LibraryVersionReturnsCorrectPatchNumber_879) {

    const Catch::Version& version = Catch::libraryVersion();

    EXPECT_EQ(version.patchNumber, 1);

}



TEST_F(CatchVersionTest_879, LibraryVersionReturnsCorrectBranchName_879) {

    const Catch::Version& version = Catch::libraryVersion();

    EXPECT_STREQ(version.branchName, "");

}



TEST_F(CatchVersionTest_879, LibraryVersionReturnsCorrectBuildNumber_879) {

    const Catch::Version& version = Catch::libraryVersion();

    EXPECT_EQ(version.buildNumber, 0);

}



} // namespace
