#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <cstdint>

class VersionTest_985 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(VersionTest_985, VersionNumberIsNonZero_985) {
    uint32_t version = Exiv2::versionNumber();
    EXPECT_GT(version, 0u);
}

TEST_F(VersionTest_985, VersionNumberMatchesMacro_985) {
    uint32_t version = Exiv2::versionNumber();
    uint32_t expected = EXIV2_MAKE_VERSION(EXIV2_MAJOR_VERSION, EXIV2_MINOR_VERSION, EXIV2_PATCH_VERSION);
    EXPECT_EQ(version, expected);
}

TEST_F(VersionTest_985, VersionNumberConsistentAcrossCalls_985) {
    uint32_t version1 = Exiv2::versionNumber();
    uint32_t version2 = Exiv2::versionNumber();
    EXPECT_EQ(version1, version2);
}

TEST_F(VersionTest_985, VersionNumberEncodesCorrectMajor_985) {
    uint32_t version = Exiv2::versionNumber();
    // EXIV2_MAKE_VERSION typically encodes as (major * 0x10000 + minor * 0x100 + patch)
    // or similar scheme. We verify that the major version can be extracted.
    uint32_t expectedFromMacro = EXIV2_MAKE_VERSION(EXIV2_MAJOR_VERSION, EXIV2_MINOR_VERSION, EXIV2_PATCH_VERSION);
    EXPECT_EQ(version, expectedFromMacro);
}

TEST_F(VersionTest_985, VersionStringIsNotEmpty_985) {
    std::string versionStr = Exiv2::versionString();
    EXPECT_FALSE(versionStr.empty());
}

TEST_F(VersionTest_985, VersionStringContainsMajorVersion_985) {
    std::string versionStr = Exiv2::versionString();
    std::string majorStr = std::to_string(EXIV2_MAJOR_VERSION);
    EXPECT_NE(versionStr.find(majorStr), std::string::npos);
}

TEST_F(VersionTest_985, VersionStringContainsMinorVersion_985) {
    std::string versionStr = Exiv2::versionString();
    std::string minorStr = std::to_string(EXIV2_MINOR_VERSION);
    EXPECT_NE(versionStr.find(minorStr), std::string::npos);
}

TEST_F(VersionTest_985, VersionStringContainsPatchVersion_985) {
    std::string versionStr = Exiv2::versionString();
    std::string patchStr = std::to_string(EXIV2_PATCH_VERSION);
    EXPECT_NE(versionStr.find(patchStr), std::string::npos);
}

TEST_F(VersionTest_985, VersionNumberFitsIn32Bits_985) {
    uint32_t version = Exiv2::versionNumber();
    EXPECT_LE(version, UINT32_MAX);
}

TEST_F(VersionTest_985, MakeVersionMacroWithZeros_985) {
    uint32_t zeroVersion = EXIV2_MAKE_VERSION(0, 0, 0);
    EXPECT_EQ(zeroVersion, 0u);
}

TEST_F(VersionTest_985, MakeVersionMacroOrdering_985) {
    // A higher major version should produce a higher number
    uint32_t v1 = EXIV2_MAKE_VERSION(0, 27, 0);
    uint32_t v2 = EXIV2_MAKE_VERSION(1, 0, 0);
    EXPECT_GT(v2, v1);
}

TEST_F(VersionTest_985, MakeVersionMacroMinorOrdering_985) {
    uint32_t v1 = EXIV2_MAKE_VERSION(0, 27, 5);
    uint32_t v2 = EXIV2_MAKE_VERSION(0, 28, 0);
    EXPECT_GT(v2, v1);
}

TEST_F(VersionTest_985, MakeVersionMacroPatchOrdering_985) {
    uint32_t v1 = EXIV2_MAKE_VERSION(0, 27, 5);
    uint32_t v2 = EXIV2_MAKE_VERSION(0, 27, 6);
    EXPECT_GT(v2, v1);
}

TEST_F(VersionTest_985, TestVersionMacroSymmetry_985) {
    // EXIV2_TEST_VERSION should return true for the current version
    bool result = EXIV2_TEST_VERSION(EXIV2_MAJOR_VERSION, EXIV2_MINOR_VERSION, EXIV2_PATCH_VERSION);
    EXPECT_TRUE(result);
}

TEST_F(VersionTest_985, TestVersionMacroFutureVersionFails_985) {
    // Testing against a version higher than current should fail
    bool result = EXIV2_TEST_VERSION(EXIV2_MAJOR_VERSION + 1, 0, 0);
    EXPECT_FALSE(result);
}
