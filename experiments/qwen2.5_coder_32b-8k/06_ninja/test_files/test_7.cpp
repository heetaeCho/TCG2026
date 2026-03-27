#include <gtest/gtest.h>

#include "string_piece.h"



class StringPieceTest_7 : public ::testing::Test {

protected:

    StringPiece emptyString;

    StringPiece literalString;

    StringPiece stdString;



    StringPieceTest_7()

        : emptyString(),

          literalString("Hello, World!"),

          stdString(std::string("Hello, World!")) {}

};



TEST_F(StringPieceTest_7, DefaultConstructorCreatesEmptyString_7) {

    EXPECT_EQ(emptyString.size(), 0);

}



TEST_F(StringPieceTest_7, CtorWithStdStringInitializesCorrectly_7) {

    EXPECT_EQ(stdString.AsString(), "Hello, World!");

    EXPECT_EQ(stdString.size(), 13);

}



TEST_F(StringPieceTest_7, CtorWithCharPtrInitializesCorrectly_7) {

    EXPECT_EQ(literalString.AsString(), "Hello, World!");

    EXPECT_EQ(literalString.size(), 13);

}



TEST_F(StringPieceTest_7, CtorWithCharPtrAndLengthInitializesCorrectly_7) {

    StringPiece partialString("Hello", 5);

    EXPECT_EQ(partialString.AsString(), "Hello");

    EXPECT_EQ(partialString.size(), 5);

}



TEST_F(StringPieceTest_7, OperatorEqualComparesIdenticalStrings_7) {

    StringPiece anotherLiteral("Hello, World!");

    EXPECT_TRUE(literalString == anotherLiteral);

}



TEST_F(StringPieceTest_7, OperatorNotEqualComparesDifferentStrings_7) {

    StringPiece differentString("Goodbye, World!");

    EXPECT_TRUE(literalString != differentString);

}



TEST_F(StringPieceTest_7, BeginAndEndIteratorsCoverWholeRange_7) {

    auto start = literalString.begin();

    auto end = literalString.end();

    for (size_t i = 0; start != end; ++start, ++i) {

        EXPECT_EQ(*start, literalString[i]);

    }

}



TEST_F(StringPieceTest_7, SubscriptOperatorAccessesCharactersCorrectly_7) {

    EXPECT_EQ(literalString[0], 'H');

    EXPECT_EQ(literalString[12], '!');

}



TEST_F(StringPieceTest_7, EmptyFunctionReturnsTrueForEmptyString_7) {

    EXPECT_TRUE(emptyString.empty());

    EXPECT_FALSE(literalString.empty());

}
