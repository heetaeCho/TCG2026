#include <gtest/gtest.h>
#include <string>

// Declaration of the function under test
namespace Exiv2 {
void urldecode(std::string& str);
}

class UrldecodeTest_1802 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Normal operation tests

TEST_F(UrldecodeTest_1802, EmptyString_1802) {
    std::string str;
    Exiv2::urldecode(str);
    EXPECT_EQ("", str);
}

TEST_F(UrldecodeTest_1802, NoEncodedCharacters_1802) {
    std::string str = "hello world";
    Exiv2::urldecode(str);
    EXPECT_EQ("hello world", str);
}

TEST_F(UrldecodeTest_1802, PlusReplacedBySpace_1802) {
    std::string str = "hello+world";
    Exiv2::urldecode(str);
    EXPECT_EQ("hello world", str);
}

TEST_F(UrldecodeTest_1802, MultiplePlusReplacedBySpaces_1802) {
    std::string str = "hello+beautiful+world";
    Exiv2::urldecode(str);
    EXPECT_EQ("hello beautiful world", str);
}

TEST_F(UrldecodeTest_1802, PercentEncodedSpace_1802) {
    std::string str = "hello%20world";
    Exiv2::urldecode(str);
    EXPECT_EQ("hello world", str);
}

TEST_F(UrldecodeTest_1802, PercentEncodedSlash_1802) {
    std::string str = "path%2Fto%2Ffile";
    Exiv2::urldecode(str);
    EXPECT_EQ("path/to/file", str);
}

TEST_F(UrldecodeTest_1802, PercentEncodedPercent_1802) {
    std::string str = "100%25";
    Exiv2::urldecode(str);
    EXPECT_EQ("100%", str);
}

TEST_F(UrldecodeTest_1802, PercentEncodedAtSign_1802) {
    std::string str = "user%40example.com";
    Exiv2::urldecode(str);
    EXPECT_EQ("user@example.com", str);
}

TEST_F(UrldecodeTest_1802, MultipleEncodings_1802) {
    std::string str = "%48%65%6C%6C%6F";
    Exiv2::urldecode(str);
    EXPECT_EQ("Hello", str);
}

TEST_F(UrldecodeTest_1802, MixedEncodedAndPlain_1802) {
    std::string str = "a%20b+c%21d";
    Exiv2::urldecode(str);
    EXPECT_EQ("a b c!d", str);
}

TEST_F(UrldecodeTest_1802, LowercaseHexDigits_1802) {
    std::string str = "%2f%2a";
    Exiv2::urldecode(str);
    EXPECT_EQ("/*", str);
}

TEST_F(UrldecodeTest_1802, UppercaseHexDigits_1802) {
    std::string str = "%2F%2A";
    Exiv2::urldecode(str);
    EXPECT_EQ("/*", str);
}

TEST_F(UrldecodeTest_1802, NullByteEncoded_1802) {
    std::string str = "abc%00def";
    Exiv2::urldecode(str);
    std::string expected = std::string("abc") + '\0' + "def";
    EXPECT_EQ(expected, str);
}

// Boundary condition tests

TEST_F(UrldecodeTest_1802, SingleCharacter_1802) {
    std::string str = "a";
    Exiv2::urldecode(str);
    EXPECT_EQ("a", str);
}

TEST_F(UrldecodeTest_1802, SinglePlus_1802) {
    std::string str = "+";
    Exiv2::urldecode(str);
    EXPECT_EQ(" ", str);
}

TEST_F(UrldecodeTest_1802, SinglePercentEncoding_1802) {
    std::string str = "%41";
    Exiv2::urldecode(str);
    EXPECT_EQ("A", str);
}

TEST_F(UrldecodeTest_1802, AllPlusSigns_1802) {
    std::string str = "+++";
    Exiv2::urldecode(str);
    EXPECT_EQ("   ", str);
}

TEST_F(UrldecodeTest_1802, EncodedAtEnd_1802) {
    std::string str = "test%21";
    Exiv2::urldecode(str);
    EXPECT_EQ("test!", str);
}

TEST_F(UrldecodeTest_1802, EncodedAtBeginning_1802) {
    std::string str = "%21test";
    Exiv2::urldecode(str);
    EXPECT_EQ("!test", str);
}

TEST_F(UrldecodeTest_1802, ConsecutiveEncodings_1802) {
    std::string str = "%20%20%20";
    Exiv2::urldecode(str);
    EXPECT_EQ("   ", str);
}

TEST_F(UrldecodeTest_1802, EncodedSpecialChars_1802) {
    std::string str = "%3C%3E%22";
    Exiv2::urldecode(str);
    EXPECT_EQ("<>\"", str);
}

TEST_F(UrldecodeTest_1802, FullURL_1802) {
    std::string str = "http%3A%2F%2Fexample.com%2Fpath%3Fquery%3Dvalue%26key%3Dval";
    Exiv2::urldecode(str);
    EXPECT_EQ("http://example.com/path?query=value&key=val", str);
}

TEST_F(UrldecodeTest_1802, EncodedFormData_1802) {
    std::string str = "name=John+Doe&age=30&city=New+York";
    Exiv2::urldecode(str);
    EXPECT_EQ("name=John Doe&age=30&city=New York", str);
}

TEST_F(UrldecodeTest_1802, HighByteValues_1802) {
    std::string str = "%FF";
    Exiv2::urldecode(str);
    EXPECT_EQ(1u, str.size());
    EXPECT_EQ('\xFF', str[0]);
}

TEST_F(UrldecodeTest_1802, EncodedFF_1802) {
    std::string str = "%ff";
    Exiv2::urldecode(str);
    EXPECT_EQ(1u, str.size());
    EXPECT_EQ('\xFF', str[0]);
}

TEST_F(UrldecodeTest_1802, StringWithNoSpecialChars_1802) {
    std::string str = "abcdefghijklmnopqrstuvwxyz0123456789";
    std::string original = str;
    Exiv2::urldecode(str);
    EXPECT_EQ(original, str);
}

TEST_F(UrldecodeTest_1802, LongEncodedString_1802) {
    std::string str;
    std::string expected;
    for (int i = 0; i < 100; ++i) {
        str += "%20";
        expected += " ";
    }
    Exiv2::urldecode(str);
    EXPECT_EQ(expected, str);
}

TEST_F(UrldecodeTest_1802, MixedCaseHex_1802) {
    std::string str = "%4a%4A";
    Exiv2::urldecode(str);
    EXPECT_EQ("JJ", str);
}
