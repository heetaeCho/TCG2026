#include <gtest/gtest.h>
#include <cstring>
#include "BuiltinFont.h"
#include "BuiltinFontWidth.h"

// Mock class for GetWidthFunction
class MockGetWidthFunction {
public:
    MOCK_METHOD(BuiltinFontWidth*, operator(),(const char* n, size_t len), (const));
};

class BuiltinFontTest_1966 : public ::testing::Test {
protected:
    BuiltinFont font;
    MockGetWidthFunction mockGetWidth;

    void SetUp() override {
        // Assign mockGetWidth to the BuiltinFont f member function
        font.f = [this](const char* n, size_t len) {
            return mockGetWidth(n, len);
        };
    }
};

// Normal Operation: Test that getWidth returns true and sets width correctly
TEST_F(BuiltinFontTest_1966, GetWidthReturnsTrueAndSetsWidth_1966) {
    const char* name = "A";
    unsigned short expectedWidth = 100;
    BuiltinFontWidth mockWidth = {expectedWidth};

    // Expect the mock to return a pointer to mockWidth when called with "A"
    EXPECT_CALL(mockGetWidth, operator()(name, strlen(name)))
        .WillOnce(testing::Return(&mockWidth));

    unsigned short width = 0;
    bool result = font.getWidth(name, &width);

    // Verify that the result is true and width is set correctly
    EXPECT_TRUE(result);
    EXPECT_EQ(width, expectedWidth);
}

// Boundary Condition: Test with empty string as the font name
TEST_F(BuiltinFontTest_1966, GetWidthReturnsFalseForEmptyString_1966) {
    const char* name = "";
    unsigned short width = 0;

    // Expect that f will return nullptr for an empty string
    EXPECT_CALL(mockGetWidth, operator()(name, strlen(name)))
        .WillOnce(testing::Return(nullptr));

    bool result = font.getWidth(name, &width);

    // Verify that the result is false and no width is set
    EXPECT_FALSE(result);
    EXPECT_EQ(width, 0);
}

// Exceptional Case: Test when f() function is null (edge case)
TEST_F(BuiltinFontTest_1966, GetWidthReturnsFalseWhenFIsNull_1966) {
    const char* name = "A";
    unsigned short width = 0;

    // Set the f pointer to nullptr to simulate an error scenario
    font.f = nullptr;

    bool result = font.getWidth(name, &width);

    // Verify that the result is false and no width is set
    EXPECT_FALSE(result);
    EXPECT_EQ(width, 0);
}

// Boundary Condition: Test with a very long string
TEST_F(BuiltinFontTest_1966, GetWidthHandlesLongStrings_1966) {
    const char* name = "A very long font name that exceeds normal length";
    unsigned short expectedWidth = 120;
    BuiltinFontWidth mockWidth = {expectedWidth};

    // Expect the mock to return a pointer to mockWidth for the long string
    EXPECT_CALL(mockGetWidth, operator()(name, strlen(name)))
        .WillOnce(testing::Return(&mockWidth));

    unsigned short width = 0;
    bool result = font.getWidth(name, &width);

    // Verify that the result is true and width is set correctly
    EXPECT_TRUE(result);
    EXPECT_EQ(width, expectedWidth);
}

// Verification of external interaction: Test mocking the callback function interaction
TEST_F(BuiltinFontTest_1966, GetWidthVerifiesCallbackInteraction_1966) {
    const char* name = "B";
    unsigned short expectedWidth = 200;
    BuiltinFontWidth mockWidth = {expectedWidth};

    // Expect the mock to return a pointer to mockWidth when called
    EXPECT_CALL(mockGetWidth, operator()(name, strlen(name)))
        .WillOnce(testing::Return(&mockWidth));

    unsigned short width = 0;
    bool result = font.getWidth(name, &width);

    // Verify the mock function was called correctly and the width is set
    EXPECT_TRUE(result);
    EXPECT_EQ(width, expectedWidth);
}