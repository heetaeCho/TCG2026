#include <gtest/gtest.h>

#include <string>

#include "TestProjects/ninja/src/string_piece.h"



class StringPieceTest_8 : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}

};



TEST_F(StringPieceTest_8, Constructor_Default_8) {

    StringPiece sp;

    EXPECT_TRUE(sp.empty());

    EXPECT_EQ(0, sp.size());

}



TEST_F(StringPieceTest_8, Constructor_FromStdString_8) {

    std::string test_str = "hello";

    StringPiece sp(test_str);

    EXPECT_FALSE(sp.empty());

    EXPECT_EQ(test_str.size(), sp.size());

    EXPECT_STREQ(test_str.c_str(), sp.str_);

}



TEST_F(StringPieceTest_8, Constructor_FromCString_8) {

    const char* test_cstr = "world";

    StringPiece sp(test_cstr);

    EXPECT_FALSE(sp.empty());

    EXPECT_EQ(strlen(test_cstr), sp.size());

    EXPECT_STREQ(test_cstr, sp.str_);

}



TEST_F(StringPieceTest_8, Constructor_FromCStringAndLength_8) {

    const char* test_cstr = "example";

    size_t len = 3;

    StringPiece sp(test_cstr, len);

    EXPECT_FALSE(sp.empty());

    EXPECT_EQ(len, sp.size());

    EXPECT_STREQ("exa", sp.AsString().c_str());

}



TEST_F(StringPieceTest_8, OperatorEqual_SameContent_8) {

    std::string test_str1 = "test";

    std::string test_str2 = "test";

    StringPiece sp1(test_str1);

    StringPiece sp2(test_str2);

    EXPECT_TRUE(sp1 == sp2);

}



TEST_F(StringPieceTest_8, OperatorEqual_DifferentContent_8) {

    std::string test_str1 = "hello";

    std::string test_str2 = "world";

    StringPiece sp1(test_str1);

    StringPiece sp2(test_str2);

    EXPECT_FALSE(sp1 == sp2);

}



TEST_F(StringPieceTest_8, OperatorNotEqual_SameContent_8) {

    std::string test_str1 = "example";

    std::string test_str2 = "example";

    StringPiece sp1(test_str1);

    StringPiece sp2(test_str2);

    EXPECT_FALSE(sp1 != sp2);

}



TEST_F(StringPieceTest_8, OperatorNotEqual_DifferentContent_8) {

    std::string test_str1 = "foo";

    std::string test_str2 = "bar";

    StringPiece sp1(test_str1);

    StringPiece sp2(test_str2);

    EXPECT_TRUE(sp1 != sp2);

}



TEST_F(StringPieceTest_8, AsString_ReturnsCorrectValue_8) {

    const char* test_cstr = "test_string";

    StringPiece sp(test_cstr);

    EXPECT_EQ(std::string(test_cstr), sp.AsString());

}



TEST_F(StringPieceTest_8, Begin_End_Iterators_Correct_8) {

    std::string test_str = "hello";

    StringPiece sp(test_str);

    EXPECT_EQ(sp.begin(), &sp.str_[0]);

    EXPECT_EQ(sp.end(), &sp.str_[test_str.size()]);

}



TEST_F(StringPieceTest_8, SubscriptOperator_ValidIndex_8) {

    const char* test_cstr = "index";

    StringPiece sp(test_cstr);

    for (size_t i = 0; i < strlen(test_cstr); ++i) {

        EXPECT_EQ(sp[i], test_cstr[i]);

    }

}



TEST_F(StringPieceTest_8, SubscriptOperator_OutOfBounds_8) {

    const char* test_cstr = "out_of_bounds";

    StringPiece sp(test_cstr);

    EXPECT_THROW({sp[sp.size()];}, std::out_of_range);

}
