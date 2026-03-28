#include <gtest/gtest.h>

#include <sstream>

#include "catch2/catch_version.hpp"



using namespace Catch;



class VersionTest_878 : public ::testing::Test {

protected:

    void SetUp() override {

        version = new Version(1, 2, 3, "dev", 456);

    }



    void TearDown() override {

        delete version;

    }



    Version* version;

};



TEST_F(VersionTest_878, OutputMajorMinorPatch_878) {

    std::ostringstream oss;

    oss << *version;

    EXPECT_EQ("1.2.3", oss.str());

}



TEST_F(VersionTest_878, OutputWithBranchNameAndBuildNumber_878) {

    std::ostringstream oss;

    version->branchName = "dev";

    version->buildNumber = 456;

    oss << *version;

    EXPECT_EQ("1.2.3-dev.456", oss.str());

}



TEST_F(VersionTest_878, OutputWithoutBranchNameAndBuildNumber_878) {

    std::ostringstream oss;

    version->branchName = "";

    version->buildNumber = 0;

    oss << *version;

    EXPECT_EQ("1.2.3", oss.str());

}



TEST_F(VersionTest_878, BoundaryConditionZeroValues_878) {

    Version zeroVersion(0, 0, 0, "", 0);

    std::ostringstream oss;

    oss << zeroVersion;

    EXPECT_EQ("0.0.0", oss.str());

}



TEST_F(VersionTest_878, BoundaryConditionMaxUnsignedInt_878) {

    Version maxVersion(UINT_MAX, UINT_MAX, UINT_MAX, "branch", UINT_MAX);

    std::ostringstream oss;

    oss << maxVersion;

    EXPECT_EQ(std::to_string(UINT_MAX) + "." + std::to_string(UINT_MAX) + "." + std::to_string(UINT_MAX) + "-branch." + std::to_string(UINT_MAX), oss.str());

}
