#include <gtest/gtest.h>
#include <string_view>

namespace Exiv2 {
    namespace Internal {
        struct StringTagDetails {
            public:
                std::string_view val_;
                bool operator==(std::string_view key) const {
                    return key == val_;
                }
        };
    }
}

// Test Fixture for StringTagDetails
class StringTagDetailsTest_177 : public ::testing::Test {
protected:
    Exiv2::Internal::StringTagDetails tag;

    // Set up a common value for each test case
    void SetUp() override {
        tag.val_ = "test";
    }
};

// Test for normal operation (matching string_view)
TEST_F(StringTagDetailsTest_177, EqualityOperator_Match_177) {
    std::string_view key = "test";
    EXPECT_TRUE(tag == key);  // Expecting equality
}

// Test for normal operation (non-matching string_view)
TEST_F(StringTagDetailsTest_177, EqualityOperator_NoMatch_177) {
    std::string_view key = "mismatch";
    EXPECT_FALSE(tag == key);  // Expecting inequality
}

// Test for empty string view comparison
TEST_F(StringTagDetailsTest_177, EqualityOperator_EmptyKey_177) {
    std::string_view key = "";
    EXPECT_FALSE(tag == key);  // Expecting inequality
}

// Test for empty val_ comparison (empty tag)
TEST_F(StringTagDetailsTest_177, EqualityOperator_EmptyVal_177) {
    tag.val_ = "";
    std::string_view key = "test";
    EXPECT_FALSE(tag == key);  // Expecting inequality
}

// Test boundary case with a large string (boundary condition)
TEST_F(StringTagDetailsTest_177, EqualityOperator_LargeString_177) {
    std::string_view large_val = "a" * 10000;  // 10k characters
    tag.val_ = large_val;
    EXPECT_TRUE(tag == large_val);  // Expecting equality with large string
}

// Test with string of one character
TEST_F(StringTagDetailsTest_177, EqualityOperator_OneCharacter_177) {
    tag.val_ = "t";
    std::string_view key = "t";
    EXPECT_TRUE(tag == key);  // Expecting equality for single character match
}

// Test case with different string type (non-std::string_view input)
TEST_F(StringTagDetailsTest_177, EqualityOperator_DifferentStringType_177) {
    const char* key = "test";
    EXPECT_TRUE(tag == key);  // Expecting equality when comparing with C-string
}