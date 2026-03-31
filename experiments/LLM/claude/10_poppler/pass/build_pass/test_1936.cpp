#include <gtest/gtest.h>
#include "PageLabelInfo_p.h"
#include "GooString.h"

class ToLatinTest_1936 : public ::testing::Test {
protected:
    GooString str;
    
    void SetUp() override {
    }
    
    void TearDown() override {
    }
    
    std::string getResult() {
        return str.toStr();
    }
};

// Test number 1 uppercase -> 'A'
TEST_F(ToLatinTest_1936, Number1Uppercase_1936) {
    toLatin(1, &str, true);
    EXPECT_EQ(getResult(), "A");
}

// Test number 1 lowercase -> 'a'
TEST_F(ToLatinTest_1936, Number1Lowercase_1936) {
    toLatin(1, &str, false);
    EXPECT_EQ(getResult(), "a");
}

// Test number 26 uppercase -> 'Z'
TEST_F(ToLatinTest_1936, Number26Uppercase_1936) {
    toLatin(26, &str, true);
    EXPECT_EQ(getResult(), "Z");
}

// Test number 26 lowercase -> 'z'
TEST_F(ToLatinTest_1936, Number26Lowercase_1936) {
    toLatin(26, &str, false);
    EXPECT_EQ(getResult(), "z");
}

// Test number 2 uppercase -> 'B'
TEST_F(ToLatinTest_1936, Number2Uppercase_1936) {
    toLatin(2, &str, true);
    EXPECT_EQ(getResult(), "B");
}

// Test number 27 uppercase -> 'AA' (wraps around, count=2, letter='A')
TEST_F(ToLatinTest_1936, Number27Uppercase_1936) {
    toLatin(27, &str, true);
    EXPECT_EQ(getResult(), "AA");
}

// Test number 28 uppercase -> 'BB' (count=2, letter='B')
TEST_F(ToLatinTest_1936, Number28Uppercase_1936) {
    toLatin(28, &str, true);
    EXPECT_EQ(getResult(), "BB");
}

// Test number 52 uppercase -> 'ZZ' (count=2, letter='Z')
TEST_F(ToLatinTest_1936, Number52Uppercase_1936) {
    toLatin(52, &str, true);
    EXPECT_EQ(getResult(), "ZZ");
}

// Test number 53 uppercase -> 'AAA' (count=3, letter='A')
TEST_F(ToLatinTest_1936, Number53Uppercase_1936) {
    toLatin(53, &str, true);
    EXPECT_EQ(getResult(), "AAA");
}

// Test number 27 lowercase -> 'aa'
TEST_F(ToLatinTest_1936, Number27Lowercase_1936) {
    toLatin(27, &str, false);
    EXPECT_EQ(getResult(), "aa");
}

// Test number 52 lowercase -> 'zz'
TEST_F(ToLatinTest_1936, Number52Lowercase_1936) {
    toLatin(52, &str, false);
    EXPECT_EQ(getResult(), "zz");
}

// Test number 13 uppercase -> 'M'
TEST_F(ToLatinTest_1936, Number13Uppercase_1936) {
    toLatin(13, &str, true);
    EXPECT_EQ(getResult(), "M");
}

// Test number 13 lowercase -> 'm'
TEST_F(ToLatinTest_1936, Number13Lowercase_1936) {
    toLatin(13, &str, false);
    EXPECT_EQ(getResult(), "m");
}

// Test number 25 uppercase -> 'Y'
TEST_F(ToLatinTest_1936, Number25Uppercase_1936) {
    toLatin(25, &str, true);
    EXPECT_EQ(getResult(), "Y");
}

// Test number 3 lowercase -> 'c'
TEST_F(ToLatinTest_1936, Number3Lowercase_1936) {
    toLatin(3, &str, false);
    EXPECT_EQ(getResult(), "c");
}

// Test large number: 78 -> count=3, letter='C' -> 'CCC'
TEST_F(ToLatinTest_1936, Number78Uppercase_1936) {
    toLatin(78, &str, true);
    // (78-1)/26 + 1 = 77/26 + 1 = 2 + 1 = 3
    // 'A' + (78-1)%26 = 'A' + 77%26 = 'A' + 25 = 'Z'
    EXPECT_EQ(getResult(), "ZZZ");
}

// Test number 79 -> count=4, letter='A' -> 'AAAA'
TEST_F(ToLatinTest_1936, Number79Uppercase_1936) {
    toLatin(79, &str, true);
    // (79-1)/26 + 1 = 78/26 + 1 = 3 + 1 = 4
    // 'A' + (79-1)%26 = 'A' + 0 = 'A'
    EXPECT_EQ(getResult(), "AAAA");
}

// Test that the string is appended to (not cleared first)
TEST_F(ToLatinTest_1936, AppendsToExistingString_1936) {
    toLatin(1, &str, true);
    toLatin(2, &str, true);
    EXPECT_EQ(getResult(), "AB");
}

// Test all single letters uppercase (1-26)
TEST_F(ToLatinTest_1936, AllSingleLettersUppercase_1936) {
    for (int i = 1; i <= 26; i++) {
        GooString s;
        toLatin(i, &s, true);
        std::string expected(1, 'A' + (i - 1));
        EXPECT_EQ(s.toStr(), expected) << "Failed for number " << i;
    }
}

// Test all single letters lowercase (1-26)
TEST_F(ToLatinTest_1936, AllSingleLettersLowercase_1936) {
    for (int i = 1; i <= 26; i++) {
        GooString s;
        toLatin(i, &s, false);
        std::string expected(1, 'a' + (i - 1));
        EXPECT_EQ(s.toStr(), expected) << "Failed for number " << i;
    }
}

// Test double letters range (27-52 all produce double letters)
TEST_F(ToLatinTest_1936, DoubleLettersRange_1936) {
    for (int i = 27; i <= 52; i++) {
        GooString s;
        toLatin(i, &s, true);
        char letter = 'A' + (i - 1) % 26;
        std::string expected(2, letter);
        EXPECT_EQ(s.toStr(), expected) << "Failed for number " << i;
    }
}
