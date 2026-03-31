#include <gtest/gtest.h>
#include <sstream>
#include "catch2/catch_version.hpp"

class VersionTest_878 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

// Test normal version output without branch name
TEST_F(VersionTest_878, NormalVersionWithoutBranch_878) {
    Catch::Version version(2, 13, 7, "", 0);
    oss << version;
    EXPECT_EQ(oss.str(), "2.13.7");
}

// Test version output with branch name
TEST_F(VersionTest_878, VersionWithBranchName_878) {
    Catch::Version version(2, 13, 7, "develop", 5);
    oss << version;
    EXPECT_EQ(oss.str(), "2.13.7-develop.5");
}

// Test version with all zeros
TEST_F(VersionTest_878, AllZeroVersion_878) {
    Catch::Version version(0, 0, 0, "", 0);
    oss << version;
    EXPECT_EQ(oss.str(), "0.0.0");
}

// Test version with large numbers
TEST_F(VersionTest_878, LargeVersionNumbers_878) {
    Catch::Version version(999, 888, 777, "", 0);
    oss << version;
    EXPECT_EQ(oss.str(), "999.888.777");
}

// Test version with large numbers and branch name
TEST_F(VersionTest_878, LargeVersionNumbersWithBranch_878) {
    Catch::Version version(999, 888, 777, "release", 666);
    oss << version;
    EXPECT_EQ(oss.str(), "999.888.777-release.666");
}

// Test version with branch name and build number zero
TEST_F(VersionTest_878, BranchNameWithBuildNumberZero_878) {
    Catch::Version version(1, 0, 0, "feature", 0);
    oss << version;
    EXPECT_EQ(oss.str(), "1.0.0-feature.0");
}

// Test version with single digit numbers
TEST_F(VersionTest_878, SingleDigitVersion_878) {
    Catch::Version version(1, 2, 3, "", 0);
    oss << version;
    EXPECT_EQ(oss.str(), "1.2.3");
}

// Test version with branch name containing special characters
TEST_F(VersionTest_878, BranchNameWithSpecialChars_878) {
    Catch::Version version(1, 0, 0, "feature-xyz_123", 42);
    oss << version;
    EXPECT_EQ(oss.str(), "1.0.0-feature-xyz_123.42");
}

// Test that operator<< returns the stream reference (chaining)
TEST_F(VersionTest_878, OperatorChainingWithoutBranch_878) {
    Catch::Version version(3, 1, 4, "", 0);
    oss << "Version: " << version << " end";
    EXPECT_EQ(oss.str(), "Version: 3.1.4 end");
}

// Test that operator<< returns the stream reference with branch (chaining)
TEST_F(VersionTest_878, OperatorChainingWithBranch_878) {
    Catch::Version version(3, 1, 4, "beta", 1);
    oss << "Version: " << version << " end";
    EXPECT_EQ(oss.str(), "Version: 3.1.4-beta.1 end");
}

// Test version with only major version non-zero
TEST_F(VersionTest_878, OnlyMajorVersionNonZero_878) {
    Catch::Version version(5, 0, 0, "", 0);
    oss << version;
    EXPECT_EQ(oss.str(), "5.0.0");
}

// Test version with only minor version non-zero
TEST_F(VersionTest_878, OnlyMinorVersionNonZero_878) {
    Catch::Version version(0, 5, 0, "", 0);
    oss << version;
    EXPECT_EQ(oss.str(), "0.5.0");
}

// Test version with only patch number non-zero
TEST_F(VersionTest_878, OnlyPatchNumberNonZero_878) {
    Catch::Version version(0, 0, 5, "", 0);
    oss << version;
    EXPECT_EQ(oss.str(), "0.0.5");
}

// Test branch name with single character
TEST_F(VersionTest_878, SingleCharBranchName_878) {
    Catch::Version version(1, 0, 0, "a", 1);
    oss << version;
    EXPECT_EQ(oss.str(), "1.0.0-a.1");
}

// Test that empty branch name (null terminator at start) does not append extra info
TEST_F(VersionTest_878, EmptyBranchNameNoExtraOutput_878) {
    Catch::Version version(2, 0, 0, "", 99);
    oss << version;
    // Even though buildNumber is 99, since branchName is empty, it should not appear
    EXPECT_EQ(oss.str(), "2.0.0");
}
