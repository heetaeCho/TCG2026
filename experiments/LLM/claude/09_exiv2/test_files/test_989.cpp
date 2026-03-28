#include <gtest/gtest.h>
#include <exiv2/version.hpp>
#include <cstdint>

// Test ID: 989

class VersionTest_989 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that testVersion returns true for the current version
TEST_F(VersionTest_989, CurrentVersionReturnsTrue_989) {
    EXPECT_TRUE(Exiv2::testVersion(EXIV2_MAJOR_VERSION, EXIV2_MINOR_VERSION, EXIV2_PATCH_VERSION));
}

// Test that testVersion returns true for version 0.0.0 (any version should be >= 0.0.0)
TEST_F(VersionTest_989, ZeroVersionReturnsTrue_989) {
    EXPECT_TRUE(Exiv2::testVersion(0, 0, 0));
}

// Test that testVersion returns false for a very high major version
TEST_F(VersionTest_989, FutureMajorVersionReturnsFalse_989) {
    EXPECT_FALSE(Exiv2::testVersion(99, 0, 0));
}

// Test that testVersion returns false for a very high minor version with current major
TEST_F(VersionTest_989, FutureMinorVersionReturnsFalse_989) {
    EXPECT_FALSE(Exiv2::testVersion(EXIV2_MAJOR_VERSION, 99, 0));
}

// Test that testVersion returns false for a very high patch version with current major and minor
TEST_F(VersionTest_989, FuturePatchVersionReturnsFalse_989) {
    EXPECT_FALSE(Exiv2::testVersion(EXIV2_MAJOR_VERSION, EXIV2_MINOR_VERSION, 99));
}

// Test that testVersion returns true for a lower major version
TEST_F(VersionTest_989, LowerMajorVersionReturnsTrue_989) {
    if (EXIV2_MAJOR_VERSION > 0) {
        EXPECT_TRUE(Exiv2::testVersion(EXIV2_MAJOR_VERSION - 1, 0, 0));
    }
}

// Test that testVersion returns true for a lower minor version with same major
TEST_F(VersionTest_989, LowerMinorVersionReturnsTrue_989) {
    if (EXIV2_MINOR_VERSION > 0) {
        EXPECT_TRUE(Exiv2::testVersion(EXIV2_MAJOR_VERSION, EXIV2_MINOR_VERSION - 1, 0));
    }
}

// Test that testVersion returns true for a lower patch version with same major and minor
TEST_F(VersionTest_989, LowerPatchVersionReturnsTrue_989) {
    if (EXIV2_PATCH_VERSION > 0) {
        EXPECT_TRUE(Exiv2::testVersion(EXIV2_MAJOR_VERSION, EXIV2_MINOR_VERSION, EXIV2_PATCH_VERSION - 1));
    }
}

// Test versionNumber returns the expected encoded version number
TEST_F(VersionTest_989, VersionNumberMatchesMacro_989) {
    uint32_t expected = EXIV2_MAKE_VERSION(EXIV2_MAJOR_VERSION, EXIV2_MINOR_VERSION, EXIV2_PATCH_VERSION);
    EXPECT_EQ(Exiv2::versionNumber(), expected);
}

// Test versionString is not empty
TEST_F(VersionTest_989, VersionStringNotEmpty_989) {
    std::string ver = Exiv2::versionString();
    EXPECT_FALSE(ver.empty());
}

// Test versionNumberHexString is not empty
TEST_F(VersionTest_989, VersionNumberHexStringNotEmpty_989) {
    std::string hexVer = Exiv2::versionNumberHexString();
    EXPECT_FALSE(hexVer.empty());
}

// Test that testVersion with exactly the current version returns true (boundary)
TEST_F(VersionTest_989, ExactCurrentVersionBoundary_989) {
    EXPECT_TRUE(Exiv2::testVersion(EXIV2_MAJOR_VERSION, EXIV2_MINOR_VERSION, EXIV2_PATCH_VERSION));
}

// Test that testVersion with one patch above current returns false (boundary)
TEST_F(VersionTest_989, OnePatchAboveCurrentReturnsFalse_989) {
    EXPECT_FALSE(Exiv2::testVersion(EXIV2_MAJOR_VERSION, EXIV2_MINOR_VERSION, EXIV2_PATCH_VERSION + 1));
}

// Test that testVersion with one minor above current returns false
TEST_F(VersionTest_989, OneMinorAboveCurrentReturnsFalse_989) {
    EXPECT_FALSE(Exiv2::testVersion(EXIV2_MAJOR_VERSION, EXIV2_MINOR_VERSION + 1, 0));
}

// Test that testVersion with one major above current returns false
TEST_F(VersionTest_989, OneMajorAboveCurrentReturnsFalse_989) {
    EXPECT_FALSE(Exiv2::testVersion(EXIV2_MAJOR_VERSION + 1, 0, 0));
}

// Test that lower major version with high minor and patch still returns true
TEST_F(VersionTest_989, LowerMajorHighMinorPatchReturnsTrue_989) {
    if (EXIV2_MAJOR_VERSION > 0) {
        EXPECT_TRUE(Exiv2::testVersion(EXIV2_MAJOR_VERSION - 1, 99, 99));
    }
}

// Test EXIV2_MAKE_VERSION macro consistency
TEST_F(VersionTest_989, MakeVersionMacroConsistency_989) {
    uint32_t v = EXIV2_MAKE_VERSION(0, 0, 0);
    EXPECT_EQ(v, 0u);
}

// Test that EXIV2_MAKE_VERSION produces ordered values
TEST_F(VersionTest_989, MakeVersionOrdering_989) {
    EXPECT_LT(EXIV2_MAKE_VERSION(0, 0, 0), EXIV2_MAKE_VERSION(0, 0, 1));
    EXPECT_LT(EXIV2_MAKE_VERSION(0, 0, 1), EXIV2_MAKE_VERSION(0, 1, 0));
    EXPECT_LT(EXIV2_MAKE_VERSION(0, 1, 0), EXIV2_MAKE_VERSION(1, 0, 0));
}

// Test versionString contains expected format (major.minor.patch)
TEST_F(VersionTest_989, VersionStringContainsDots_989) {
    std::string ver = Exiv2::versionString();
    // Version string should contain at least one dot
    EXPECT_NE(ver.find('.'), std::string::npos);
}
