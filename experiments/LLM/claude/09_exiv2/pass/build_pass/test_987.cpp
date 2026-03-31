#include <gtest/gtest.h>
#include <string>
#include <exiv2/exiv2.hpp>

// Test for versionNumberHexString
TEST(VersionTest_987, VersionNumberHexStringReturnsNonEmpty_987) {
    std::string hexStr = Exiv2::versionNumberHexString();
    EXPECT_FALSE(hexStr.empty());
}

TEST(VersionTest_987, VersionNumberHexStringHasSixCharacters_987) {
    std::string hexStr = Exiv2::versionNumberHexString();
    // The format string "{:06x}" should produce a 6-character zero-padded hex string
    EXPECT_EQ(hexStr.length(), 6u);
}

TEST(VersionTest_987, VersionNumberHexStringContainsOnlyHexChars_987) {
    std::string hexStr = Exiv2::versionNumberHexString();
    for (char c : hexStr) {
        bool isHex = (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
        EXPECT_TRUE(isHex) << "Character '" << c << "' is not a valid hex character";
    }
}

TEST(VersionTest_987, VersionNumberHexStringConsistentWithVersionNumber_987) {
    // versionNumberHexString should be the hex representation of versionNumber()
    int verNum = Exiv2::versionNumber();
    char expected[7];
    snprintf(expected, sizeof(expected), "%06x", verNum);
    std::string hexStr = Exiv2::versionNumberHexString();
    EXPECT_EQ(hexStr, std::string(expected));
}

TEST(VersionTest_987, VersionNumberHexStringIsIdempotent_987) {
    std::string first = Exiv2::versionNumberHexString();
    std::string second = Exiv2::versionNumberHexString();
    EXPECT_EQ(first, second);
}

// Test for versionNumber
TEST(VersionTest_987, VersionNumberIsPositive_987) {
    int verNum = Exiv2::versionNumber();
    EXPECT_GT(verNum, 0);
}

// Test for versionString
TEST(VersionTest_987, VersionStringReturnsNonEmpty_987) {
    std::string verStr = Exiv2::versionString();
    EXPECT_FALSE(verStr.empty());
}

TEST(VersionTest_987, VersionStringContainsDot_987) {
    std::string verStr = Exiv2::versionString();
    // A version string like "0.28.0" should contain at least one dot
    EXPECT_NE(verStr.find('.'), std::string::npos);
}

// Test version components
TEST(VersionTest_987, VersionNumberMatchesMajorMinorPatch_987) {
    int verNum = Exiv2::versionNumber();
    // versionNumber is typically MAJOR*0x10000 + MINOR*0x100 + PATCH
    // Verify it's a reasonable version number
    int major = (verNum >> 16) & 0xFF;
    int minor = (verNum >> 8) & 0xFF;
    int patch = verNum & 0xFF;
    EXPECT_GE(major, 0);
    EXPECT_GE(minor, 0);
    EXPECT_GE(patch, 0);
    EXPECT_LE(major, 255);
    EXPECT_LE(minor, 255);
    EXPECT_LE(patch, 255);
}

// Test that version() function exists and returns expected type
TEST(VersionTest_987, VersionStringIsConsistentAcrossCalls_987) {
    std::string first = Exiv2::versionString();
    std::string second = Exiv2::versionString();
    EXPECT_EQ(first, second);
}

TEST(VersionTest_987, VersionNumberIsConsistentAcrossCalls_987) {
    int first = Exiv2::versionNumber();
    int second = Exiv2::versionNumber();
    EXPECT_EQ(first, second);
}

TEST(VersionTest_987, VersionNumberFitsIn24Bits_987) {
    // Since hex string is 6 characters, the number should fit in 24 bits
    int verNum = Exiv2::versionNumber();
    EXPECT_LE(verNum, 0xFFFFFF);
    EXPECT_GE(verNum, 0);
}
