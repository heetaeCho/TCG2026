#include <gtest/gtest.h>

#include "string_piece.h"

#include <string>



class StringPieceTest_4 : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}



    std::string sample_string = "Hello, World!";

};



// Test normal operation of the default constructor

TEST_F(StringPieceTest_4, DefaultConstructorInitializesEmptyString_4) {

    StringPiece sp;

    EXPECT_EQ(sp.size(), 0);

    EXPECT_TRUE(sp.empty());

}



// Test normal operation of the string constructor

TEST_F(StringPieceTest_4, StringConstructorSetsCorrectly_4) {

    StringPiece sp(sample_string);

    EXPECT_EQ(sp.size(), sample_string.size());

    EXPECT_FALSE(sp.empty());

    EXPECT_EQ(std::string(sp.begin(), sp.end()), sample_string);

}



// Test normal operation of the char* constructor

TEST_F(StringPieceTest_4, CharPtrConstructorSetsCorrectly_4) {

    StringPiece sp(sample_string.c_str());

    EXPECT_EQ(sp.size(), sample_string.size());

    EXPECT_FALSE(sp.empty());

    EXPECT_EQ(std::string(sp.begin(), sp.end()), sample_string);

}



// Test normal operation of the char* and length constructor

TEST_F(StringPieceTest_4, CharPtrAndLengthConstructorSetsCorrectly_4) {

    size_t len = 5;

    StringPiece sp(sample_string.c_str(), len);

    EXPECT_EQ(sp.size(), len);

    EXPECT_FALSE(sp.empty());

    EXPECT_EQ(std::string(sp.begin(), sp.end()), sample_string.substr(0, len));

}



// Test boundary condition of an empty char* string

TEST_F(StringPieceTest_4, EmptyCharPtrConstructorSetsCorrectly_4) {

    StringPiece sp("");

    EXPECT_EQ(sp.size(), 0);

    EXPECT_TRUE(sp.empty());

}



// Test boundary condition of a zero-length substring

TEST_F(StringPieceTest_4, ZeroLengthSubstringConstructorSetsCorrectly_4) {

    StringPiece sp(sample_string.c_str(), 0);

    EXPECT_EQ(sp.size(), 0);

    EXPECT_TRUE(sp.empty());

}



// Test operator== for equal strings

TEST_F(StringPieceTest_4, EqualityOperatorReturnsTrueForEqualStrings_4) {

    StringPiece sp1(sample_string);

    StringPiece sp2(sample_string);

    EXPECT_TRUE(sp1 == sp2);

}



// Test operator== for different strings

TEST_F(StringPieceTest_4, EqualityOperatorReturnsFalseForDifferentStrings_4) {

    StringPiece sp1(sample_string);

    StringPiece sp2("Another string");

    EXPECT_FALSE(sp1 == sp2);

}



// Test operator!= for equal strings

TEST_F(StringPieceTest_4, InequalityOperatorReturnsFalseForEqualStrings_4) {

    StringPiece sp1(sample_string);

    StringPiece sp2(sample_string);

    EXPECT_FALSE(sp1 != sp2);

}



// Test operator!= for different strings

TEST_F(StringPieceTest_4, InequalityOperatorReturnsTrueForDifferentStrings_4) {

    StringPiece sp1(sample_string);

    StringPiece sp2("Another string");

    EXPECT_TRUE(sp1 != sp2);

}



// Test AsString method returns correct string

TEST_F(StringPieceTest_4, AsStringMethodReturnsCorrectString_4) {

    StringPiece sp(sample_string);

    EXPECT_EQ(sp.AsString(), sample_string);

}



// Test begin() and end() iterators cover the entire string

TEST_F(StringPieceTest_4, BeginAndEndIteratorsCoverEntireString_4) {

    StringPiece sp(sample_string);

    std::string result(sp.begin(), sp.end());

    EXPECT_EQ(result, sample_string);

}



// Test operator[] for a valid position

TEST_F(StringPieceTest_4, OperatorBracketReturnsCorrectChar_4) {

    StringPiece sp(sample_string);

    size_t pos = 7;

    EXPECT_EQ(sp[pos], sample_string[pos]);

}



// Test operator[] for an invalid position (out of bounds)

TEST_F(StringPieceTest_4, OperatorBracketThrowsExceptionForOutOfBoundsPosition_4) {

    StringPiece sp(sample_string);

    size_t pos = sample_string.size();

    EXPECT_THROW({ char c = sp[pos]; }, std::out_of_range);

}



// Test size() returns correct length

TEST_F(StringPieceTest_4, SizeMethodReturnsCorrectLength_4) {

    StringPiece sp(sample_string);

    EXPECT_EQ(sp.size(), sample_string.size());

}



// Test empty() returns true for an empty string

TEST_F(StringPieceTest_4, EmptyMethodReturnsTrueForEmptyString_4) {

    StringPiece sp("");

    EXPECT_TRUE(sp.empty());

}



// Test empty() returns false for a non-empty string

TEST_F(StringPieceTest_4, EmptyMethodReturnsFalseForNonEmptyString_4) {

    StringPiece sp(sample_string);

    EXPECT_FALSE(sp.empty());

}
