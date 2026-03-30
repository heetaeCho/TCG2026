// File: to_lower_tests_590.cpp
#include <gtest/gtest.h>
#include <string>

// If the real declaration header is available, prefer including it instead:
//   #include <catch2/internal/catch_string_manip.hpp>
// For robustness in this standalone snippet, we forward-declare the function:
namespace Catch {
    std::string toLower(std::string const& s);
}

// Test suite focused on observable behavior of Catch::toLower
// Naming rule: <Behavior>_590
class StringManipToLowerTest_590 : public ::testing::Test {};

TEST_F(StringManipToLowerTest_590, EmptyStringReturnsEmpty_590) {
    const std::string input = "";
    const std::string out = Catch::toLower(input);
    EXPECT_TRUE(out.empty());
    // verify original is not modified (by interface it is const&, but we assert anyway)
    EXPECT_EQ(input, "");
}

TEST_F(StringManipToLowerTest_590, UppercaseAsciiBecomesLowercase_590) {
    const std::string input = "ABCXYZ";
    const std::string out = Catch::toLower(input);
    EXPECT_EQ(out, "abcxyz");
    EXPECT_EQ(input, "ABCXYZ"); // input must remain unchanged
}

TEST_F(StringManipToLowerTest_590, AlreadyLowercaseRemainsUnchanged_590) {
    const std::string input = "lorem ipsum dolor sit amet";
    const std::string out = Catch::toLower(input);
    EXPECT_EQ(out, "lorem ipsum dolor sit amet");
    EXPECT_EQ(input, "lorem ipsum dolor sit amet");
}

TEST_F(StringManipToLowerTest_590, NonAlphabeticCharactersUnchanged_590) {
    const std::string input = "12345 !@#$_-+=[](){}.,;:/?";
    const std::string out = Catch::toLower(input);
    EXPECT_EQ(out, "12345 !@#$_-+=[](){}.,;:/?");
    EXPECT_EQ(input, "12345 !@#$_-+=[](){}.,;:/?");
}

TEST_F(StringManipToLowerTest_590, MixedCaseAndSymbolsAreLowercasedWhereApplicable_590) {
    const std::string input = "HeLLo-World_2025";
    const std::string out = Catch::toLower(input);
    EXPECT_EQ(out, "hello-world_2025"); // letters downcased, digits/symbols preserved
    EXPECT_EQ(input, "HeLLo-World_2025");
}

TEST_F(StringManipToLowerTest_590, InputIsNotModifiedAfterCall_590) {
    std::string input = "MaKE_IT_LOWER";
    const std::string orig = input; // copy to verify immutability from caller perspective
    const std::string out = Catch::toLower(input);
    EXPECT_EQ(input, orig);           // original should be unchanged
    EXPECT_EQ(out, "make_it_lower");  // observable lowercasing on the returned value
}
