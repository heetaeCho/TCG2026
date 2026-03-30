#include <gtest/gtest.h>
#include <string_view>

namespace Exiv2 {
    namespace Internal {
        constexpr bool contains(std::string_view s, auto c) {
            #ifdef __cpp_lib_string_contains
                return s.contains(c);
            #else
                return s.find(c) != std::string_view::npos;
            #endif
        }
    }
}

TEST_F(ContainsTest_76, NormalOperation_76) {
    // Test case to check if character is found within the string
    std::string_view testStr = "Hello, world!";
    char testChar = 'o';

    bool result = Exiv2::Internal::contains(testStr, testChar);

    EXPECT_TRUE(result) << "The character should be found in the string.";
}

TEST_F(ContainsTest_77, CharacterNotFound_77) {
    // Test case to check if character is not found within the string
    std::string_view testStr = "Hello, world!";
    char testChar = 'z';

    bool result = Exiv2::Internal::contains(testStr, testChar);

    EXPECT_FALSE(result) << "The character should not be found in the string.";
}

TEST_F(ContainsTest_78, EmptyString_78) {
    // Test case for an empty string
    std::string_view testStr = "";
    char testChar = 'o';

    bool result = Exiv2::Internal::contains(testStr, testChar);

    EXPECT_FALSE(result) << "The character should not be found in an empty string.";
}

TEST_F(ContainsTest_79, EmptyCharacter_79) {
    // Test case for empty character input (invalid case)
    std::string_view testStr = "Hello, world!";
    char testChar = '\0';  // Null character

    bool result = Exiv2::Internal::contains(testStr, testChar);

    EXPECT_FALSE(result) << "The null character should not be found in the string.";
}

TEST_F(ContainsTest_80, BoundaryTest_80) {
    // Boundary test case for a single character string
    std::string_view testStr = "A";
    char testChar = 'A';

    bool result = Exiv2::Internal::contains(testStr, testChar);

    EXPECT_TRUE(result) << "The character should be found in the single character string.";
}

TEST_F(ContainsTest_81, SpecialCharacter_81) {
    // Test case for special characters in the string
    std::string_view testStr = "Hello! How are you?";
    char testChar = '!';

    bool result = Exiv2::Internal::contains(testStr, testChar);

    EXPECT_TRUE(result) << "The special character should be found in the string.";
}

TEST_F(ContainsTest_82, CaseSensitivity_82) {
    // Test case for case-sensitive search
    std::string_view testStr = "Hello, World!";
    char testCharUpper = 'H';
    char testCharLower = 'h';

    bool resultUpper = Exiv2::Internal::contains(testStr, testCharUpper);
    bool resultLower = Exiv2::Internal::contains(testStr, testCharLower);

    EXPECT_TRUE(resultUpper) << "The uppercase character 'H' should be found.";
    EXPECT_FALSE(resultLower) << "The lowercase character 'h' should not be found.";
}

TEST_F(ContainsTest_83, FindNonExistentCharacter_83) {
    // Test case for character that doesn't exist
    std::string_view testStr = "Exiv2";
    char testChar = 'z';

    bool result = Exiv2::Internal::contains(testStr, testChar);

    EXPECT_FALSE(result) << "The character 'z' should not be found in the string.";
}

TEST_F(ContainsTest_84, LargeString_84) {
    // Test case for very large string
    std::string_view testStr = std::string(10000, 'x') + "y";
    char testChar = 'y';

    bool result = Exiv2::Internal::contains(testStr, testChar);

    EXPECT_TRUE(result) << "The character 'y' should be found in the large string.";
}

TEST_F(ContainsTest_85, EmptyCharacterRange_85) {
    // Test case for empty character range (edge case)
    std::string_view testStr = "Hello, world!";
    char testChar = ' ';

    bool result = Exiv2::Internal::contains(testStr, testChar);

    EXPECT_TRUE(result) << "The space character should be found in the string.";
}