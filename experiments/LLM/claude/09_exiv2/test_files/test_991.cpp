#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include <regex>

// We need to test the `output` function from version.cpp.
// Since it's a static function in the .cpp file, we need to either:
// 1. Include the .cpp file directly (not ideal but necessary for testing static functions)
// 2. Or test through the public interface that uses it.
//
// Since the function is static (file-local), we need to replicate the testing context.
// We'll include the necessary headers and test through the public API if available,
// or we test the observable behavior through Exiv2's version/info functions.

// For the purpose of this test, we'll test the public API that uses these internal functions.
// Exiv2 exposes version information through public functions.

#include <exiv2/version.hpp>
#include <exiv2/exiv2.hpp>

class VersionTest_991 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that Exiv2 version string is not empty
TEST_F(VersionTest_991, VersionStringNotEmpty_991) {
    std::string version = Exiv2::versionString();
    EXPECT_FALSE(version.empty());
}

// Test that version number components are non-negative
TEST_F(VersionTest_991, VersionNumberComponentsNonNegative_991) {
    EXPECT_GE(Exiv2::versionNumber(), 0);
}

// Test that major version is reasonable
TEST_F(VersionTest_991, MajorVersionReasonable_991) {
    int major = EXIV2_MAJOR_VERSION;
    EXPECT_GE(major, 0);
    EXPECT_LE(major, 100);
}

// Test that minor version is reasonable
TEST_F(VersionTest_991, MinorVersionReasonable_991) {
    int minor = EXIV2_MINOR_VERSION;
    EXPECT_GE(minor, 0);
    EXPECT_LE(minor, 100);
}

// Test that patch version is reasonable
TEST_F(VersionTest_991, PatchVersionReasonable_991) {
    int patch = EXIV2_PATCH_VERSION;
    EXPECT_GE(patch, 0);
    EXPECT_LE(patch, 1000);
}

// Test version string format contains dots
TEST_F(VersionTest_991, VersionStringContainsDots_991) {
    std::string version = Exiv2::versionString();
    EXPECT_NE(version.find('.'), std::string::npos);
}

// Test that testVersion works for current version
TEST_F(VersionTest_991, TestVersionCurrentVersion_991) {
    bool result = Exiv2::testVersion(EXIV2_MAJOR_VERSION, EXIV2_MINOR_VERSION, EXIV2_PATCH_VERSION);
    EXPECT_TRUE(result);
}

// Test that testVersion returns true for older version
TEST_F(VersionTest_991, TestVersionOlderVersion_991) {
    bool result = Exiv2::testVersion(0, 0, 0);
    EXPECT_TRUE(result);
}

// Test that testVersion returns false for a future major version
TEST_F(VersionTest_991, TestVersionFutureMajorVersion_991) {
    bool result = Exiv2::testVersion(EXIV2_MAJOR_VERSION + 100, 0, 0);
    EXPECT_FALSE(result);
}

// Test that testVersion returns false for a future minor version with same major
TEST_F(VersionTest_991, TestVersionFutureMinorVersion_991) {
    bool result = Exiv2::testVersion(EXIV2_MAJOR_VERSION, EXIV2_MINOR_VERSION + 100, 0);
    EXPECT_FALSE(result);
}

// Test that testVersion returns false for a future patch version with same major and minor
TEST_F(VersionTest_991, TestVersionFuturePatchVersion_991) {
    bool result = Exiv2::testVersion(EXIV2_MAJOR_VERSION, EXIV2_MINOR_VERSION, EXIV2_PATCH_VERSION + 1000);
    EXPECT_FALSE(result);
}

// Test version number macro consistency
TEST_F(VersionTest_991, VersionMacroConsistency_991) {
    int computed = EXIV2_MAKE_VERSION(EXIV2_MAJOR_VERSION, EXIV2_MINOR_VERSION, EXIV2_PATCH_VERSION);
    EXPECT_EQ(computed, EXIV2_VERSION);
}

// Test that version number matches the EXIV2_VERSION macro
TEST_F(VersionTest_991, VersionNumberMatchesMacro_991) {
    EXPECT_EQ(Exiv2::versionNumber(), EXIV2_VERSION);
}

// Test EXIV2_MAKE_VERSION with zero values
TEST_F(VersionTest_991, MakeVersionZero_991) {
    int ver = EXIV2_MAKE_VERSION(0, 0, 0);
    EXPECT_EQ(ver, 0);
}

// Test EXIV2_MAKE_VERSION with specific values
TEST_F(VersionTest_991, MakeVersionSpecificValues_991) {
    int ver = EXIV2_MAKE_VERSION(1, 2, 3);
    // Based on typical version encoding: major * 0x10000 + minor * 0x100 + patch
    // or similar scheme
    EXPECT_GT(ver, 0);
}

// Test that dumpLibraryInfo outputs to a stream
TEST_F(VersionTest_991, DumpLibraryInfoProducesOutput_991) {
    std::ostringstream os;
    Exiv2::dumpLibraryInfo(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

// Test that dumpLibraryInfo contains version information
TEST_F(VersionTest_991, DumpLibraryInfoContainsVersion_991) {
    std::ostringstream os;
    Exiv2::dumpLibraryInfo(os);
    std::string output = os.str();
    // The output should contain some recognizable content
    EXPECT_NE(output.find("exiv2"), std::string::npos);
}

// Test dumpLibraryInfo with grep patterns
TEST_F(VersionTest_991, DumpLibraryInfoWithGreps_991) {
    std::ostringstream os;
    std::vector<std::regex> greps;
    greps.push_back(std::regex("version"));
    Exiv2::dumpLibraryInfo(os, greps);
    std::string output = os.str();
    // With a grep for "version", we should get filtered output
    // It could be empty if no lines match, or contain matching lines
    // We just verify it doesn't crash
    SUCCEED();
}

// Test dumpLibraryInfo with empty grep vector
TEST_F(VersionTest_991, DumpLibraryInfoEmptyGreps_991) {
    std::ostringstream os;
    std::vector<std::regex> greps;
    Exiv2::dumpLibraryInfo(os, greps);
    std::string output = os.str();
    // Empty greps should output everything
    EXPECT_FALSE(output.empty());
}

// Test dumpLibraryInfo with non-matching grep
TEST_F(VersionTest_991, DumpLibraryInfoNonMatchingGrep_991) {
    std::ostringstream os;
    std::vector<std::regex> greps;
    greps.push_back(std::regex("zzzzz_nonexistent_pattern_zzzzz"));
    Exiv2::dumpLibraryInfo(os, greps);
    std::string output = os.str();
    // Non-matching grep may result in empty or minimal output
    // Just ensure no crash
    SUCCEED();
}

// Test that version string matches version components
TEST_F(VersionTest_991, VersionStringMatchesComponents_991) {
    std::string version = Exiv2::versionString();
    std::string expected = std::to_string(EXIV2_MAJOR_VERSION) + "." +
                           std::to_string(EXIV2_MINOR_VERSION) + "." +
                           std::to_string(EXIV2_PATCH_VERSION);
    EXPECT_EQ(version, expected);
}

// Boundary: testVersion with zero values
TEST_F(VersionTest_991, TestVersionZeroValues_991) {
    bool result = Exiv2::testVersion(0, 0, 0);
    EXPECT_TRUE(result);
}

// Boundary: testVersion with maximum possible values
TEST_F(VersionTest_991, TestVersionMaxValues_991) {
    bool result = Exiv2::testVersion(255, 255, 255);
    // This should be false unless the library version is somehow 255.255.255
    EXPECT_FALSE(result);
}
