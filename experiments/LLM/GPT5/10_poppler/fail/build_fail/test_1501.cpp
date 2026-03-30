#include <gtest/gtest.h>
#include <string>
#include <functional>

// The class to be tested
#include "./TestProjects/poppler/poppler/NameToCharCode.h"

class NameToCharCodeTest_1501 : public ::testing::Test {
protected:
    // SetUp and TearDown can be added if necessary for common test setup or cleanup
    void SetUp() override {}
    void TearDown() override {}
};

// Test normal operation with a string input
TEST_F(NameToCharCodeTest_1501, StringInputNormal_1501) {
    NameToCharCode hasher;

    std::string test_string = "hello";
    size_t result = hasher(test_string);

    // Verify the hash is a valid size_t (any valid hash value)
    ASSERT_NE(result, 0);
}

// Test normal operation with an empty string input
TEST_F(NameToCharCodeTest_1501, EmptyStringInput_1501) {
    NameToCharCode hasher;

    std::string test_string = "";
    size_t result = hasher(test_string);

    // Verify the hash is a valid size_t (any valid hash value)
    ASSERT_NE(result, 0);
}

// Test boundary condition with a long string input
TEST_F(NameToCharCodeTest_1501, LongStringInput_1501) {
    NameToCharCode hasher;

    std::string test_string = std::string(1000, 'a');  // A string of 1000 'a' characters
    size_t result = hasher(test_string);

    // Verify the hash is a valid size_t (any valid hash value)
    ASSERT_NE(result, 0);
}

// Test boundary condition with a string consisting of special characters
TEST_F(NameToCharCodeTest_1501, SpecialCharactersInput_1501) {
    NameToCharCode hasher;

    std::string test_string = "!@#$%^&*()_+";
    size_t result = hasher(test_string);

    // Verify the hash is a valid size_t (any valid hash value)
    ASSERT_NE(result, 0);
}

// Test exceptional case with a nullptr input (if the function is expected to handle it)
TEST_F(NameToCharCodeTest_1501, NullptrInput_1501) {
    NameToCharCode hasher;

    const char* test_string = nullptr;
    ASSERT_ANY_THROW(hasher(test_string));  // Expect an exception or error if nullptr is not handled properly
}

// Test interaction with external object by mocking the behavior (optional)
TEST_F(NameToCharCodeTest_1501, ExternalInteractionMock_1501) {
    // Mock behavior is not necessary here as no external dependencies are clearly defined for the operator().
    // But in case it were necessary, Google Mock could be used here to simulate interactions with external objects
}