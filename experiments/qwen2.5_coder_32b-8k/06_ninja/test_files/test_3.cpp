#include <gtest/gtest.h>

#include "string_piece.h"



class StringPieceTest_3 : public ::testing::Test {

protected:

    StringPiece emptyPiece;

    StringPiece singleCharPiece;

    StringPiece multiCharPiece;



    void SetUp() override {

        emptyPiece = StringPiece();

        singleCharPiece = StringPiece("a");

        multiCharPiece = StringPiece("hello");

    }

};



TEST_F(StringPieceTest_3, AsString_ReturnsEmptyStringForEmptyPiece_3) {

    EXPECT_EQ(emptyPiece.AsString(), "");

}



TEST_F(StringPieceTest_3, AsString_ReturnsCorrectStringForSingleCharPiece_3) {

    EXPECT_EQ(singleCharPiece.AsString(), "a");

}



TEST_F(StringPieceTest_3, AsString_ReturnsCorrectStringForMultiCharPiece_3) {

    EXPECT_EQ(multiCharPiece.AsString(), "hello");

}



TEST_F(StringPieceTest_3, OperatorEqual_ReturnsTrueForEqualPieces_3) {

    StringPiece anotherSingleCharPiece("a");

    EXPECT_TRUE(singleCharPiece == anotherSingleCharPiece);

}



TEST_F(StringPieceTest_3, OperatorEqual_ReturnsFalseForDifferentPieces_3) {

    StringPiece differentPiece("b");

    EXPECT_FALSE(singleCharPiece == differentPiece);

}



TEST_F(StringPieceTest_3, OperatorNotEqual_ReturnsTrueForDifferentPieces_3) {

    StringPiece differentPiece("b");

    EXPECT_TRUE(singleCharPiece != differentPiece);

}



TEST_F(StringPieceTest_3, OperatorNotEqual_ReturnsFalseForEqualPieces_3) {

    StringPiece anotherSingleCharPiece("a");

    EXPECT_FALSE(singleCharPiece != anotherSingleCharPiece);

}



TEST_F(StringPieceTest_3, Begin_ReturnsStartOfData_3) {

    EXPECT_EQ(*multiCharPiece.begin(), 'h');

}



TEST_F(StringPieceTest_3, End_ReturnsPastEndOfData_3) {

    EXPECT_TRUE(multiCharPiece.end() == multiCharPiece.str_ + multiCharPiece.len_);

}



TEST_F(StringPieceTest_3, OperatorIndex_ReturnsCorrectCharacter_3) {

    EXPECT_EQ(multiCharPiece[1], 'e');

}



TEST_F(StringPieceTest_3, Size_ReturnsCorrectSize_3) {

    EXPECT_EQ(singleCharPiece.size(), 1);

    EXPECT_EQ(multiCharPiece.size(), 5);

}



TEST_F(StringPieceTest_3, Empty_ReturnsTrueForEmptyPiece_3) {

    EXPECT_TRUE(emptyPiece.empty());

}



TEST_F(StringPieceTest_3, Empty_ReturnsFalseForNonEmptyPiece_3) {

    EXPECT_FALSE(singleCharPiece.empty());

}
