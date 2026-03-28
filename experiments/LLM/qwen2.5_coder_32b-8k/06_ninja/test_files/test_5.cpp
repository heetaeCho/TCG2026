#include <gtest/gtest.h>

#include "string_piece.h"



class StringPieceTest_5 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(StringPieceTest_5, DefaultConstructorCreatesEmptyString_5) {

    StringPiece sp;

    EXPECT_EQ(sp.size(), 0u);

    EXPECT_TRUE(sp.empty());

}



TEST_F(StringPieceTest_5, StringConstructorSetsCorrectly_5) {

    std::string test_str = "Hello";

    StringPiece sp(test_str);

    EXPECT_EQ(sp.size(), test_str.size());

    EXPECT_STREQ(sp.begin(), test_str.c_str());

    EXPECT_FALSE(sp.empty());

}



TEST_F(StringPieceTest_5, CharPtrConstructorSetsCorrectly_5) {

    const char* test_cstr = "Hello";

    StringPiece sp(test_cstr);

    EXPECT_EQ(sp.size(), strlen(test_cstr));

    EXPECT_STREQ(sp.begin(), test_cstr);

    EXPECT_FALSE(sp.empty());

}



TEST_F(StringPieceTest_5, CharPtrLenConstructorSetsCorrectly_5) {

    const char* test_cstr = "Hello";

    size_t len = 3;

    StringPiece sp(test_cstr, len);

    EXPECT_EQ(sp.size(), len);

    EXPECT_STREQ(std::string(sp.begin(), sp.end()).c_str(), std::string(test_cstr, len).c_str());

    EXPECT_FALSE(sp.empty());

}



TEST_F(StringPieceTest_5, EqualityOperatorReturnsTrueForEqualStrings_5) {

    StringPiece sp1("Hello");

    StringPiece sp2("Hello");

    EXPECT_TRUE(sp1 == sp2);

}



TEST_F(StringPieceTest_5, EqualityOperatorReturnsFalseForDifferentStrings_5) {

    StringPiece sp1("Hello");

    StringPiece sp2("World");

    EXPECT_FALSE(sp1 == sp2);

}



TEST_F(StringPieceTest_5, InequalityOperatorReturnsTrueForDifferentStrings_5) {

    StringPiece sp1("Hello");

    StringPiece sp2("World");

    EXPECT_TRUE(sp1 != sp2);

}



TEST_F(StringPieceTest_5, InequalityOperatorReturnsFalseForEqualStrings_5) {

    StringPiece sp1("Hello");

    StringPiece sp2("Hello");

    EXPECT_FALSE(sp1 != sp2);

}



TEST_F(StringPieceTest_5, AsStringConvertsToStringCorrectly_5) {

    std::string test_str = "Hello";

    StringPiece sp(test_str);

    EXPECT_EQ(sp.AsString(), test_str);

}



TEST_F(StringPieceTest_5, BeginReturnsStartPointer_5) {

    const char* test_cstr = "Hello";

    StringPiece sp(test_cstr);

    EXPECT_STREQ(sp.begin(), test_cstr);

}



TEST_F(StringPieceTest_5, EndReturnsEndPointer_5) {

    const char* test_cstr = "Hello";

    StringPiece sp(test_cstr);

    EXPECT_EQ(sp.end(), test_cstr + strlen(test_cstr));

}



TEST_F(StringPieceTest_5, SubscriptOperatorAccessesCorrectCharacter_5) {

    StringPiece sp("Hello");

    EXPECT_EQ(sp[0], 'H');

    EXPECT_EQ(sp[1], 'e');

    EXPECT_EQ(sp[2], 'l');

    EXPECT_EQ(sp[3], 'l');

    EXPECT_EQ(sp[4], 'o');

}



TEST_F(StringPieceTest_5, SizeReturnsCorrectLength_5) {

    StringPiece sp("Hello");

    EXPECT_EQ(sp.size(), 5u);

}



TEST_F(StringPieceTest_5, EmptyReturnsTrueForEmptyString_5) {

    StringPiece sp;

    EXPECT_TRUE(sp.empty());

}



TEST_F(StringPieceTest_5, EmptyReturnsFalseForNonEmptyString_5) {

    StringPiece sp("Hello");

    EXPECT_FALSE(sp.empty());

}
