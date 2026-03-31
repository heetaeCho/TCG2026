#include <gtest/gtest.h>
#include <string>

// Forward declare the function under test
namespace Catch {
    void toLowerInPlace(std::string& s);
}

// Normal operation tests

TEST(CatchStringManipTest_589, EmptyString_589) {
    std::string s = "";
    Catch::toLowerInPlace(s);
    EXPECT_EQ(s, "");
}

TEST(CatchStringManipTest_589, AllLowercase_589) {
    std::string s = "hello";
    Catch::toLowerInPlace(s);
    EXPECT_EQ(s, "hello");
}

TEST(CatchStringManipTest_589, AllUppercase_589) {
    std::string s = "HELLO";
    Catch::toLowerInPlace(s);
    EXPECT_EQ(s, "hello");
}

TEST(CatchStringManipTest_589, MixedCase_589) {
    std::string s = "HeLLo WoRLd";
    Catch::toLowerInPlace(s);
    EXPECT_EQ(s, "hello world");
}

TEST(CatchStringManipTest_589, SingleUpperChar_589) {
    std::string s = "A";
    Catch::toLowerInPlace(s);
    EXPECT_EQ(s, "a");
}

TEST(CatchStringManipTest_589, SingleLowerChar_589) {
    std::string s = "a";
    Catch::toLowerInPlace(s);
    EXPECT_EQ(s, "a");
}

// Boundary conditions

TEST(CatchStringManipTest_589, DigitsUnchanged_589) {
    std::string s = "12345";
    Catch::toLowerInPlace(s);
    EXPECT_EQ(s, "12345");
}

TEST(CatchStringManipTest_589, SpecialCharsUnchanged_589) {
    std::string s = "!@#$%^&*()";
    Catch::toLowerInPlace(s);
    EXPECT_EQ(s, "!@#$%^&*()");
}

TEST(CatchStringManipTest_589, MixedAlphaNumericSpecial_589) {
    std::string s = "Test123!@#ABC";
    Catch::toLowerInPlace(s);
    EXPECT_EQ(s, "test123!@#abc");
}

TEST(CatchStringManipTest_589, WhitespaceUnchanged_589) {
    std::string s = "  \t\n  ";
    Catch::toLowerInPlace(s);
    EXPECT_EQ(s, "  \t\n  ");
}

TEST(CatchStringManipTest_589, BoundaryCharA_589) {
    std::string s = "A";
    Catch::toLowerInPlace(s);
    EXPECT_EQ(s, "a");
}

TEST(CatchStringManipTest_589, BoundaryCharZ_589) {
    std::string s = "Z";
    Catch::toLowerInPlace(s);
    EXPECT_EQ(s, "z");
}

TEST(CatchStringManipTest_589, CharBeforeA_589) {
    // '@' is the character before 'A' in ASCII
    std::string s = "@";
    Catch::toLowerInPlace(s);
    EXPECT_EQ(s, "@");
}

TEST(CatchStringManipTest_589, CharAfterZ_589) {
    // '[' is the character after 'Z' in ASCII
    std::string s = "[";
    Catch::toLowerInPlace(s);
    EXPECT_EQ(s, "[");
}

TEST(CatchStringManipTest_589, AllAlphabetUppercase_589) {
    std::string s = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    Catch::toLowerInPlace(s);
    EXPECT_EQ(s, "abcdefghijklmnopqrstuvwxyz");
}

TEST(CatchStringManipTest_589, AllAlphabetLowercase_589) {
    std::string s = "abcdefghijklmnopqrstuvwxyz";
    Catch::toLowerInPlace(s);
    EXPECT_EQ(s, "abcdefghijklmnopqrstuvwxyz");
}

TEST(CatchStringManipTest_589, InPlaceModification_589) {
    std::string s = "TEST";
    std::string* addr = &s;
    Catch::toLowerInPlace(s);
    EXPECT_EQ(&s, addr); // Verify it's the same string object
    EXPECT_EQ(s, "test");
}

TEST(CatchStringManipTest_589, LongString_589) {
    std::string s(1000, 'A');
    Catch::toLowerInPlace(s);
    std::string expected(1000, 'a');
    EXPECT_EQ(s, expected);
}

TEST(CatchStringManipTest_589, NullCharInString_589) {
    std::string s("AB\0CD", 5);
    Catch::toLowerInPlace(s);
    std::string expected("ab\0cd", 5);
    EXPECT_EQ(s, expected);
}
