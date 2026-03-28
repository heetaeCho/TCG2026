#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "string_piece.h"

#include <string>



using namespace testing;



class StringPieceTest_2 : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}

};



TEST_F(StringPieceTest_2, DefaultConstructorInitializesEmptyString_2) {

    StringPiece sp;

    EXPECT_EQ(sp.size(), 0);

    EXPECT_TRUE(sp.empty());

}



TEST_F(StringPieceTest_2, ConstructorWithStdString_2) {

    std::string str = "hello";

    StringPiece sp(str);

    EXPECT_EQ(sp.AsString(), str);

    EXPECT_EQ(sp.size(), str.size());

    EXPECT_FALSE(sp.empty());

}



TEST_F(StringPieceTest_2, ConstructorWithCString_2) {

    const char* cstr = "world";

    StringPiece sp(cstr);

    EXPECT_STREQ(sp.str_, cstr);

    EXPECT_EQ(sp.size(), strlen(cstr));

    EXPECT_FALSE(sp.empty());

}



TEST_F(StringPieceTest_2, ConstructorWithCStringAndLength_2) {

    const char* cstr = "example";

    size_t len = 3;

    StringPiece sp(cstr, len);

    EXPECT_STREQ(sp.str_, cstr);

    EXPECT_EQ(sp.size(), len);

    EXPECT_FALSE(sp.empty());

}



TEST_F(StringPieceTest_2, EqualityOperatorWithEqualStrings_2) {

    std::string str1 = "test";

    std::string str2 = "test";

    StringPiece sp1(str1);

    StringPiece sp2(str2);

    EXPECT_TRUE(sp1 == sp2);

}



TEST_F(StringPieceTest_2, EqualityOperatorWithDifferentStrings_2) {

    std::string str1 = "test1";

    std::string str2 = "test2";

    StringPiece sp1(str1);

    StringPiece sp2(str2);

    EXPECT_FALSE(sp1 == sp2);

}



TEST_F(StringPieceTest_2, InequalityOperatorWithEqualStrings_2) {

    std::string str1 = "equal";

    std::string str2 = "equal";

    StringPiece sp1(str1);

    StringPiece sp2(str2);

    EXPECT_FALSE(sp1 != sp2);

}



TEST_F(StringPieceTest_2, InequalityOperatorWithDifferentStrings_2) {

    std::string str1 = "not_equal";

    std::string str2 = "different";

    StringPiece sp1(str1);

    StringPiece sp2(str2);

    EXPECT_TRUE(sp1 != sp2);

}



TEST_F(StringPieceTest_2, AsStringConversion_2) {

    const char* cstr = "convert";

    StringPiece sp(cstr);

    EXPECT_EQ(sp.AsString(), cstr);

}



TEST_F(StringPieceTest_2, BeginEndIterators_2) {

    std::string str = "iterate";

    StringPiece sp(str);

    EXPECT_EQ(sp.begin(), sp.str_);

    EXPECT_EQ(sp.end(), sp.str_ + sp.size());

}



TEST_F(StringPieceTest_2, ElementAccessOperator_2) {

    std::string str = "access";

    StringPiece sp(str);

    for (size_t i = 0; i < sp.size(); ++i) {

        EXPECT_EQ(sp[i], str[i]);

    }

}



TEST_F(StringPieceTest_2, SizeAndEmptyForNonEmptyString_2) {

    std::string str = "non_empty";

    StringPiece sp(str);

    EXPECT_EQ(sp.size(), str.size());

    EXPECT_FALSE(sp.empty());

}



TEST_F(StringPieceTest_2, SizeAndEmptyForEmptyString_2) {

    StringPiece sp;

    EXPECT_EQ(sp.size(), 0);

    EXPECT_TRUE(sp.empty());

}
