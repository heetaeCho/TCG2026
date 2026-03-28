#include <gtest/gtest.h>
#include <string>
#include <regex>

// Include the necessary exiv2 headers
#include <exiv2/version.hpp>
#include <exiv2/exiv2.hpp>

class VersionTest_986 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that versionString returns a non-empty string
TEST_F(VersionTest_986, VersionStringIsNotEmpty_986) {
    std::string version = Exiv2::versionString();
    EXPECT_FALSE(version.empty());
}

// Test that versionString follows the semantic versioning format "major.minor.patch"
TEST_F(VersionTest_986, VersionStringMatchesSemanticFormat_986) {
    std::string version = Exiv2::versionString();
    std::regex semver_pattern(R"(\d+\.\d+\.\d+)");
    EXPECT_TRUE(std::regex_match(version, semver_pattern))
        << "Version string '" << version << "' does not match expected format 'X.Y.Z'";
}

// Test that versionString is consistent across multiple calls
TEST_F(VersionTest_986, VersionStringIsConsistent_986) {
    std::string version1 = Exiv2::versionString();
    std::string version2 = Exiv2::versionString();
    EXPECT_EQ(version1, version2);
}

// Test that the version string matches the compile-time version macros
TEST_F(VersionTest_986, VersionStringMatchesMacros_986) {
    std::string version = Exiv2::versionString();
    
    // Extract major, minor, patch from the version string
    int major = -1, minor = -1, patch = -1;
    size_t pos1 = version.find('.');
    ASSERT_NE(pos1, std::string::npos);
    size_t pos2 = version.find('.', pos1 + 1);
    ASSERT_NE(pos2, std::string::npos);
    
    major = std::stoi(version.substr(0, pos1));
    minor = std::stoi(version.substr(pos1 + 1, pos2 - pos1 - 1));
    patch = std::stoi(version.substr(pos2 + 1));
    
    EXPECT_EQ(major, EXIV2_MAJOR_VERSION);
    EXPECT_EQ(minor, EXIV2_MINOR_VERSION);
    EXPECT_EQ(patch, EXIV2_PATCH_VERSION);
}

// Test that version components are non-negative
TEST_F(VersionTest_986, VersionComponentsAreNonNegative_986) {
    std::string version = Exiv2::versionString();
    
    size_t pos1 = version.find('.');
    ASSERT_NE(pos1, std::string::npos);
    size_t pos2 = version.find('.', pos1 + 1);
    ASSERT_NE(pos2, std::string::npos);
    
    int major = std::stoi(version.substr(0, pos1));
    int minor = std::stoi(version.substr(pos1 + 1, pos2 - pos1 - 1));
    int patch = std::stoi(version.substr(pos2 + 1));
    
    EXPECT_GE(major, 0);
    EXPECT_GE(minor, 0);
    EXPECT_GE(patch, 0);
}

// Test that the version string contains exactly two dots
TEST_F(VersionTest_986, VersionStringContainsExactlyTwoDots_986) {
    std::string version = Exiv2::versionString();
    int dotCount = 0;
    for (char c : version) {
        if (c == '.') {
            dotCount++;
        }
    }
    EXPECT_EQ(dotCount, 2);
}

// Test that the version string does not contain leading or trailing whitespace
TEST_F(VersionTest_986, VersionStringHasNoWhitespace_986) {
    std::string version = Exiv2::versionString();
    EXPECT_EQ(version.find(' '), std::string::npos);
    EXPECT_EQ(version.find('\t'), std::string::npos);
    EXPECT_EQ(version.find('\n'), std::string::npos);
}

// Test that the version string only contains digits and dots
TEST_F(VersionTest_986, VersionStringContainsOnlyDigitsAndDots_986) {
    std::string version = Exiv2::versionString();
    for (char c : version) {
        EXPECT_TRUE(std::isdigit(c) || c == '.')
            << "Unexpected character '" << c << "' in version string '" << version << "'";
    }
}

// Test that EXIV2_MAJOR_VERSION macro is defined and reasonable
TEST_F(VersionTest_986, MajorVersionMacroIsReasonable_986) {
    EXPECT_GE(EXIV2_MAJOR_VERSION, 0);
    EXPECT_LE(EXIV2_MAJOR_VERSION, 99);
}

// Test that EXIV2_MINOR_VERSION macro is defined and reasonable
TEST_F(VersionTest_986, MinorVersionMacroIsReasonable_986) {
    EXPECT_GE(EXIV2_MINOR_VERSION, 0);
    EXPECT_LE(EXIV2_MINOR_VERSION, 99);
}

// Test that EXIV2_PATCH_VERSION macro is defined and reasonable
TEST_F(VersionTest_986, PatchVersionMacroIsReasonable_986) {
    EXPECT_GE(EXIV2_PATCH_VERSION, 0);
    EXPECT_LE(EXIV2_PATCH_VERSION, 99);
}
