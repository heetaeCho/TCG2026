#include <gtest/gtest.h>
#include <cstring>

// Forward declare the function from the Exiv2 namespace
namespace Exiv2 {
    const char* version();
}

// Test that version() returns a non-null pointer
TEST(VersionTest_988, ReturnsNonNull_988) {
    const char* ver = Exiv2::version();
    ASSERT_NE(ver, nullptr);
}

// Test that version() returns a non-empty string
TEST(VersionTest_988, ReturnsNonEmptyString_988) {
    const char* ver = Exiv2::version();
    ASSERT_NE(ver, nullptr);
    EXPECT_GT(std::strlen(ver), 0u);
}

// Test that version() returns the same pointer on multiple calls (it's a constant)
TEST(VersionTest_988, ReturnsSamePointerOnMultipleCalls_988) {
    const char* ver1 = Exiv2::version();
    const char* ver2 = Exiv2::version();
    EXPECT_EQ(ver1, ver2);
}

// Test that version() returns the same string content on multiple calls
TEST(VersionTest_988, ReturnsConsistentStringContent_988) {
    const char* ver1 = Exiv2::version();
    const char* ver2 = Exiv2::version();
    ASSERT_NE(ver1, nullptr);
    ASSERT_NE(ver2, nullptr);
    EXPECT_STREQ(ver1, ver2);
}

// Test that version string contains only valid version characters (digits, dots, alphanumeric, hyphens)
TEST(VersionTest_988, ContainsValidVersionCharacters_988) {
    const char* ver = Exiv2::version();
    ASSERT_NE(ver, nullptr);
    std::string version_str(ver);
    for (char c : version_str) {
        bool valid = std::isalnum(static_cast<unsigned char>(c)) || c == '.' || c == '-' || c == '_' || c == '+';
        EXPECT_TRUE(valid) << "Unexpected character '" << c << "' in version string: " << version_str;
    }
}

// Test that the version string length is within a reasonable range
TEST(VersionTest_988, VersionStringLengthIsReasonable_988) {
    const char* ver = Exiv2::version();
    ASSERT_NE(ver, nullptr);
    size_t len = std::strlen(ver);
    // A version string should be at least 1 character and less than 256 characters
    EXPECT_GE(len, 1u);
    EXPECT_LT(len, 256u);
}
