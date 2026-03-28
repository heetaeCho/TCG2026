#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <algorithm>

// We need to access the getLoadedLibraries function.
// Since it's a static function in version.cpp, we need to include it or
// use a workaround. We'll test it through whatever public interface exposes it.
// Based on exiv2's public API, the version information is typically exposed
// through Exiv2 namespace functions.

#include "exiv2/version.hpp"

// The getLoadedLibraries is a static (file-scope) function in version.cpp,
// which means it's not directly accessible from outside. However, exiv2
// exposes version-related functionality through its public API.
// We'll test what's publicly available.

class VersionTest_994 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that Exiv2 version string is not empty
TEST_F(VersionTest_994, VersionStringIsNotEmpty_994) {
    std::string version = Exiv2::version();
    EXPECT_FALSE(version.empty());
}

// Test that version components are non-negative
TEST_F(VersionTest_994, VersionMajorIsNonNegative_994) {
    EXPECT_GE(Exiv2::versionNumber(), 0);
}

// Test that versionString returns a valid format
TEST_F(VersionTest_994, VersionStringFormat_994) {
    std::string ver = Exiv2::version();
    // Version string should contain at least one dot (e.g., "0.28.0")
    EXPECT_NE(ver.find('.'), std::string::npos);
}

// Test that version number is consistent
TEST_F(VersionTest_994, VersionNumberIsPositive_994) {
    int vn = Exiv2::versionNumber();
    EXPECT_GT(vn, 0);
}

// Test versionNumberHexString
TEST_F(VersionTest_994, VersionNumberHexStringNotEmpty_994) {
    std::string hexStr = Exiv2::versionNumberHexString();
    EXPECT_FALSE(hexStr.empty());
}

// Test testVersion with current version - should return true
TEST_F(VersionTest_994, TestVersionWithCurrentVersionReturnsTrue_994) {
    int major = EXIV2_MAJOR_VERSION;
    int minor = EXIV2_MINOR_VERSION;
    int patch = EXIV2_PATCH_VERSION;
    EXPECT_TRUE(Exiv2::testVersion(major, minor, patch));
}

// Test testVersion with version 0.0.0 - current should be >= 0.0.0
TEST_F(VersionTest_994, TestVersionWithZeroReturnsTrue_994) {
    EXPECT_TRUE(Exiv2::testVersion(0, 0, 0));
}

// Test testVersion with a very high version - should return false
TEST_F(VersionTest_994, TestVersionWithHighVersionReturnsFalse_994) {
    EXPECT_FALSE(Exiv2::testVersion(999, 999, 999));
}

// Test testVersion with major version higher than current
TEST_F(VersionTest_994, TestVersionWithHigherMajorReturnsFalse_994) {
    int major = EXIV2_MAJOR_VERSION + 1;
    EXPECT_FALSE(Exiv2::testVersion(major, 0, 0));
}

// Test testVersion with same major but higher minor
TEST_F(VersionTest_994, TestVersionWithHigherMinorReturnsFalse_994) {
    int major = EXIV2_MAJOR_VERSION;
    int minor = EXIV2_MINOR_VERSION + 100;
    EXPECT_FALSE(Exiv2::testVersion(major, minor, 0));
}

// Test testVersion with same major, same minor but higher patch
TEST_F(VersionTest_994, TestVersionWithHigherPatchReturnsFalse_994) {
    int major = EXIV2_MAJOR_VERSION;
    int minor = EXIV2_MINOR_VERSION;
    int patch = EXIV2_PATCH_VERSION + 100;
    EXPECT_FALSE(Exiv2::testVersion(major, minor, patch));
}

// Test testVersion with lower major version
TEST_F(VersionTest_994, TestVersionWithLowerMajorReturnsTrue_994) {
    if (EXIV2_MAJOR_VERSION > 0) {
        EXPECT_TRUE(Exiv2::testVersion(EXIV2_MAJOR_VERSION - 1, 0, 0));
    }
}

// Test that version macro values are consistent with function return
TEST_F(VersionTest_994, VersionMacrosConsistentWithFunctions_994) {
    // The version number is typically computed as major*10000 + minor*100 + patch
    // or similar encoding
    int expectedNumber = EXIV2_MAKE_VERSION(EXIV2_MAJOR_VERSION, EXIV2_MINOR_VERSION, EXIV2_PATCH_VERSION);
    EXPECT_EQ(Exiv2::versionNumber(), expectedNumber);
}

// Test that version string contains the major version number
TEST_F(VersionTest_994, VersionStringContainsMajorVersion_994) {
    std::string ver = Exiv2::version();
    std::string majorStr = std::to_string(EXIV2_MAJOR_VERSION);
    EXPECT_NE(ver.find(majorStr), std::string::npos);
}

// Boundary: testVersion with exact current version
TEST_F(VersionTest_994, TestVersionExactCurrentVersion_994) {
    EXPECT_TRUE(Exiv2::testVersion(EXIV2_MAJOR_VERSION, EXIV2_MINOR_VERSION, EXIV2_PATCH_VERSION));
}
