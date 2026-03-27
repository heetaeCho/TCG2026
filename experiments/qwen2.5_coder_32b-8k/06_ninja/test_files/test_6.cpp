#include <gtest/gtest.h>

#include "string_piece.h"



class StringPieceTest_6 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup can be used to initialize objects if needed.

    }



    void TearDown() override {

        // Cleanup can be done here if needed.

    }

};



TEST_F(StringPieceTest_6, DefaultConstructorInitializesEmptyString_6) {

    StringPiece sp;

    EXPECT_EQ(sp.size(), 0);

    EXPECT_TRUE(sp.empty());

}



TEST_F(StringPieceTest_6, ConstructorWithStdString_6) {

    std::string test_str = "hello";

    StringPiece sp(test_str);

    EXPECT_EQ(sp.size(), test_str.size());

    EXPECT_EQ(sp.AsString(), test_str);

    EXPECT_FALSE(sp.empty());

}



TEST_F(StringPieceTest_6, ConstructorWithCharPointer_6) {

    const char* test_cstr = "world";

    StringPiece sp(test_cstr);

    EXPECT_EQ(sp.size(), strlen(test_cstr));

    EXPECT_STREQ(sp.begin(), test_cstr);

    EXPECT_FALSE(sp.empty());

}



TEST_F(StringPieceTest_6, ConstructorWithCharPointerAndLength_6) {

    const char* test_cstr = "world";

    size_t len = 3;

    StringPiece sp(test_cstr, len);

    EXPECT_EQ(sp.size(), len);

    EXPECT_STREQ(std::string(sp.begin(), sp.end()).c_str(), std::string(test_cstr, len).c_str());

    EXPECT_FALSE(sp.empty());

}



TEST_F(StringPieceTest_6, OperatorEqualSameString_6) {

    StringPiece sp1("test");

    StringPiece sp2("test");

    EXPECT_TRUE(sp1 == sp2);

}



TEST_F(StringPieceTest_6, OperatorNotEqualDifferentStrings_6) {

    StringPiece sp1("test");

    StringPiece sp2("diff");

    EXPECT_TRUE(sp1 != sp2);

}



TEST_F(StringPieceTest_6, AsStringConversion_6) {

    std::string test_str = "example";

    StringPiece sp(test_str);

    EXPECT_EQ(sp.AsString(), test_str);

}



TEST_F(StringPieceTest_6, BeginEndIterators_6) {

    const char* test_cstr = "hello";

    StringPiece sp(test_cstr);

    EXPECT_STREQ(std::string(sp.begin(), sp.end()).c_str(), test_cstr);

}



TEST_F(StringPieceTest_6, OperatorSquareBracketValidIndex_6) {

    StringPiece sp("index");

    EXPECT_EQ(sp[0], 'i');

    EXPECT_EQ(sp[1], 'n');

    EXPECT_EQ(sp[4], 'x');

}



TEST_F(StringPieceTest_6, OperatorSquareBracketBoundaryCondition_6) {

    StringPiece sp("boundary");

    EXPECT_EQ(sp[sp.size() - 1], 'y');

}



TEST_F(StringPieceTest_6, OperatorSquareBracketOutofBounds_6) {

    StringPiece sp("outofbounds");

    EXPECT_THROW(sp[sp.size()], std::out_of_range); // Assuming out of range access throws an exception

}
