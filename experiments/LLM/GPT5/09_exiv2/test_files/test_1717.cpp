#include <gtest/gtest.h>
#include <string>

// Partial code from ./TestProjects/exiv2/src/xmpsidecar.cpp
namespace Exiv2 {
    static bool matchi(const std::string& key, const char* substr) {
        return Internal::contains(Internal::lower(key), substr);
    }
}

// Mocking necessary internal methods for testing
namespace Internal {
    bool contains(const std::string& str, const std::string& substr) {
        return str.find(substr) != std::string::npos;
    }

    std::string lower(const std::string& str) {
        std::string lowerStr = str;
        std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
        return lowerStr;
    }
}

class XmpsidecarTest_1717 : public ::testing::Test {
protected:
    // Any common setup for the tests can go here.
    void SetUp() override {
        // No setup needed in this case.
    }
    
    void TearDown() override {
        // Clean-up code if required.
    }
};

// Test case for normal operation
TEST_F(XmpsidecarTest_1717, MatchiReturnsTrueWhenSubstringIsPresent_1717) {
    std::string key = "Exif.PentaxDng.Date";
    const char* substr = "pentax";

    bool result = Exiv2::matchi(key, substr);

    EXPECT_TRUE(result) << "Expected matchi to return true when the substring is present (case-insensitive).";
}

// Test case for normal operation with different case
TEST_F(XmpsidecarTest_1717, MatchiReturnsTrueWithCaseInsensitiveMatching_1717) {
    std::string key = "Exif.PentaxDng.Date";
    const char* substr = "EXIF";

    bool result = Exiv2::matchi(key, substr);

    EXPECT_TRUE(result) << "Expected matchi to return true with case-insensitive substring match.";
}

// Test case for normal operation where substring is not present
TEST_F(XmpsidecarTest_1717, MatchiReturnsFalseWhenSubstringIsNotPresent_1717) {
    std::string key = "Exif.PentaxDng.Date";
    const char* substr = "sony";

    bool result = Exiv2::matchi(key, substr);

    EXPECT_FALSE(result) << "Expected matchi to return false when the substring is not present.";
}

// Test case for boundary condition: empty string as key
TEST_F(XmpsidecarTest_1717, MatchiReturnsFalseForEmptyKey_1717) {
    std::string key = "";
    const char* substr = "sony";

    bool result = Exiv2::matchi(key, substr);

    EXPECT_FALSE(result) << "Expected matchi to return false when the key is empty.";
}

// Test case for boundary condition: empty substring
TEST_F(XmpsidecarTest_1717, MatchiReturnsTrueForEmptySubstring_1717) {
    std::string key = "Exif.PentaxDng.Date";
    const char* substr = "";

    bool result = Exiv2::matchi(key, substr);

    EXPECT_TRUE(result) << "Expected matchi to return true when the substring is empty.";
}

// Test case for exceptional case: null pointer as substring
TEST_F(XmpsidecarTest_1717, MatchiReturnsFalseForNullSubstring_1717) {
    std::string key = "Exif.PentaxDng.Date";
    const char* substr = nullptr;

    bool result = Exiv2::matchi(key, substr);

    EXPECT_FALSE(result) << "Expected matchi to return false when the substring is null.";
}

// Test case to verify external interaction (mocked function: Internal::contains)
TEST_F(XmpsidecarTest_1717, MatchiVerifiesContainsCall_1717) {
    std::string key = "Exif.PentaxDng.Date";
    const char* substr = "pentax";

    // Mock the Internal::contains function call
    EXPECT_CALL(*this, contains(testing::StrEq("Exif.PentaxDng.Date"), testing::StrEq("pentax")))
        .WillOnce(testing::Return(true));

    bool result = Exiv2::matchi(key, substr);

    EXPECT_TRUE(result) << "Expected matchi to return true, and contains to be called as expected.";
}

// Mocking the Internal::contains method
MOCK_METHOD(bool, contains, (const std::string& str, const std::string& substr), ());