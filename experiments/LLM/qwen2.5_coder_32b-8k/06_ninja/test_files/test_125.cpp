#include <gtest/gtest.h>

#include "string_piece_util.cc"

#include "string_piece.h"



class StringPieceUtilTest_125 : public ::testing::Test {

protected:

    // You can set up any common state here if needed.

};



TEST_F(StringPieceUtilTest_125, JoinStringPiece_EmptyList_ReturnsEmptyString_125) {

    std::vector<StringPiece> list;

    EXPECT_EQ("", JoinStringPiece(list, ','));

}



TEST_F(StringPieceUtilTest_125, JoinStringPiece_SingleElement_ReturnsElementString_125) {

    std::vector<StringPiece> list = {StringPiece("hello")};

    EXPECT_EQ("hello", JoinStringPiece(list, ','));

}



TEST_F(StringPieceUtilTest_125, JoinStringPiece_MultipleElements_JoinsWithSeparator_125) {

    std::vector<StringPiece> list = {StringPiece("hello"), StringPiece("world")};

    EXPECT_EQ("hello,world", JoinStringPiece(list, ','));

}



TEST_F(StringPieceUtilTest_125, JoinStringPiece_DifferentSeparators_JoinsCorrectly_125) {

    std::vector<StringPiece> list = {StringPiece("apple"), StringPiece("banana"), StringPiece("cherry")};

    EXPECT_EQ("apple-banana-cherry", JoinStringPiece(list, '-'));

}



TEST_F(StringPieceUtilTest_125, JoinStringPiece_EmptyStringsInList_JoinsCorrectly_125) {

    std::vector<StringPiece> list = {StringPiece(""), StringPiece("foo"), StringPiece("")};

    EXPECT_EQ(",foo,", JoinStringPiece(list, ','));

}



TEST_F(StringPieceUtilTest_125, JoinStringPiece_AllEmptyStrings_ReturnsEmptyString_125) {

    std::vector<StringPiece> list = {StringPiece(""), StringPiece(""), StringPiece("")};

    EXPECT_EQ("", JoinStringPiece(list, ','));

}
