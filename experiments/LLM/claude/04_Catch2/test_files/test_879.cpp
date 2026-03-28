#include <gtest/gtest.h>
#include <sstream>
#include "catch2/catch_version.hpp"

class CatchVersionTest_879 : public ::testing::Test {
protected:
    const Catch::Version& version = Catch::libraryVersion();
};

// Test that libraryVersion returns the expected major version
TEST_F(CatchVersionTest_879, MajorVersionIs3_879) {
    EXPECT_EQ(version.majorVersion, 3u);
}

// Test that libraryVersion returns the expected minor version
TEST_F(CatchVersionTest_879, MinorVersionIs8_879) {
    EXPECT_EQ(version.minorVersion, 8u);
}

// Test that libraryVersion returns the expected patch number
TEST_F(CatchVersionTest_879, PatchNumberIs1_879) {
    EXPECT_EQ(version.patchNumber, 1u);
}

// Test that libraryVersion returns an empty branch name
TEST_F(CatchVersionTest_879, BranchNameIsEmpty_879) {
    ASSERT_NE(version.branchName, nullptr);
    EXPECT_STREQ(version.branchName, "");
}

// Test that libraryVersion returns zero build number
TEST_F(CatchVersionTest_879, BuildNumberIsZero_879) {
    EXPECT_EQ(version.buildNumber, 0u);
}

// Test that libraryVersion returns the same instance (singleton behavior)
TEST_F(CatchVersionTest_879, ReturnsSameInstance_879) {
    const Catch::Version& v1 = Catch::libraryVersion();
    const Catch::Version& v2 = Catch::libraryVersion();
    EXPECT_EQ(&v1, &v2);
}

// Test that the Version can be streamed to an ostream
TEST_F(CatchVersionTest_879, StreamOutputContainsVersionNumbers_879) {
    std::ostringstream oss;
    oss << version;
    std::string output = oss.str();
    
    // The output should contain the version numbers
    EXPECT_FALSE(output.empty());
    // Should contain "3" for major version
    EXPECT_NE(output.find("3"), std::string::npos);
    // Should contain "8" for minor version
    EXPECT_NE(output.find("8"), std::string::npos);
    // Should contain "1" for patch version
    EXPECT_NE(output.find("1"), std::string::npos);
}

// Test that streaming produces a consistent result on multiple calls
TEST_F(CatchVersionTest_879, StreamOutputIsConsistent_879) {
    std::ostringstream oss1, oss2;
    oss1 << version;
    oss2 << version;
    EXPECT_EQ(oss1.str(), oss2.str());
}

// Test that the stream output likely follows "major.minor.patch" format
TEST_F(CatchVersionTest_879, StreamOutputContainsDotSeparators_879) {
    std::ostringstream oss;
    oss << version;
    std::string output = oss.str();
    
    // Expect at least two dots for "major.minor.patch" format
    size_t dotCount = 0;
    for (char c : output) {
        if (c == '.') dotCount++;
    }
    EXPECT_GE(dotCount, 2u);
}

// Test Version struct with a custom constructed instance to verify constructor behavior
TEST_F(CatchVersionTest_879, CustomVersionConstruction_879) {
    Catch::Version customVersion(1, 2, 3, "test-branch", 42);
    EXPECT_EQ(customVersion.majorVersion, 1u);
    EXPECT_EQ(customVersion.minorVersion, 2u);
    EXPECT_EQ(customVersion.patchNumber, 3u);
    EXPECT_STREQ(customVersion.branchName, "test-branch");
    EXPECT_EQ(customVersion.buildNumber, 42u);
}

// Test Version with zero values
TEST_F(CatchVersionTest_879, ZeroVersionConstruction_879) {
    Catch::Version zeroVersion(0, 0, 0, "", 0);
    EXPECT_EQ(zeroVersion.majorVersion, 0u);
    EXPECT_EQ(zeroVersion.minorVersion, 0u);
    EXPECT_EQ(zeroVersion.patchNumber, 0u);
    EXPECT_STREQ(zeroVersion.branchName, "");
    EXPECT_EQ(zeroVersion.buildNumber, 0u);
}

// Test Version with large values (boundary)
TEST_F(CatchVersionTest_879, LargeVersionNumbers_879) {
    Catch::Version largeVersion(999, 999, 999, "release", 9999);
    EXPECT_EQ(largeVersion.majorVersion, 999u);
    EXPECT_EQ(largeVersion.minorVersion, 999u);
    EXPECT_EQ(largeVersion.patchNumber, 999u);
    EXPECT_STREQ(largeVersion.branchName, "release");
    EXPECT_EQ(largeVersion.buildNumber, 9999u);
}

// Test that custom version with branch name streams properly
TEST_F(CatchVersionTest_879, CustomVersionWithBranchStreams_879) {
    Catch::Version customVersion(2, 5, 0, "dev", 10);
    std::ostringstream oss;
    oss << customVersion;
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    // Should contain the branch name when it's non-empty
    EXPECT_NE(output.find("dev"), std::string::npos);
}

// Test that version with empty branch name does not have extra decorations
TEST_F(CatchVersionTest_879, VersionWithEmptyBranchStreamOutput_879) {
    Catch::Version v(3, 8, 1, "", 0);
    std::ostringstream oss;
    oss << v;
    std::string output = oss.str();
    // Should start with the version number pattern
    EXPECT_EQ(output.substr(0, 5), "3.8.1");
}
