#include <gtest/gtest.h>

#include "string_piece.h"



class StringPieceTest_1 : public ::testing::Test {

protected:

    const std::string kSampleString = "Hello, World!";

    const char* kSampleCString = "Hello, C-Style String!";

};



TEST_F(StringPieceTest_1, DefaultConstructorCreatesEmptyString_1) {

    StringPiece sp;

    EXPECT_EQ(sp.size(), 0);

    EXPECT_TRUE(sp.empty());

}



TEST_F(StringPieceTest_1, ConstructorFromStdString_SetsCorrectValues_1) {

    StringPiece sp(kSampleString);

    EXPECT_EQ(sp.size(), kSampleString.size());

    EXPECT_FALSE(sp.empty());

    EXPECT_STREQ(sp.begin(), kSampleString.data());

}



TEST_F(StringPieceTest_1, ConstructorFromCString_SetsCorrectValues_1) {

    StringPiece sp(kSampleCString);

    EXPECT_EQ(sp.size(), strlen(kSampleCString));

    EXPECT_FALSE(sp.empty());

    EXPECT_STREQ(sp.begin(), kSampleCString);

}



TEST_F(StringPieceTest_1, ConstructorFromCStringAndLength_SetsCorrectValues_1) {

    const char* partialString = "Hello";

    size_t length = 5;

    StringPiece sp(partialString, length);

    EXPECT_EQ(sp.size(), length);

    EXPECT_FALSE(sp.empty());

    EXPECT_STREQ(sp.begin(), partialString);

}



TEST_F(StringPieceTest_1, OperatorEquals_ReturnsTrueForEqualStrings_1) {

    StringPiece sp1(kSampleString);

    StringPiece sp2(kSampleString);

    EXPECT_TRUE(sp1 == sp2);

}



TEST_F(StringPieceTest_1, OperatorEquals_ReturnsFalseForDifferentStrings_1) {

    StringPiece sp1(kSampleString);

    StringPiece sp2("Different String");

    EXPECT_FALSE(sp1 == sp2);

}



TEST_F(StringPieceTest_1, OperatorNotEquals_ReturnsTrueForDifferentStrings_1) {

    StringPiece sp1(kSampleString);

    StringPiece sp2("Different String");

    EXPECT_TRUE(sp1 != sp2);

}



TEST_F(StringPieceTest_1, OperatorNotEquals_ReturnsFalseForEqualStrings_1) {

    StringPiece sp1(kSampleString);

    StringPiece sp2(kSampleString);

    EXPECT_FALSE(sp1 != sp2);

}



TEST_F(StringPieceTest_1, AsString_ReturnsCorrectStdString_1) {

    StringPiece sp(kSampleCString);

    std::string result = sp.AsString();

    EXPECT_EQ(result, kSampleCString);

}



TEST_F(StringPieceTest_1, BeginAndEnd_IteratorsPointToCorrectPositions_1) {

    StringPiece sp(kSampleCString);

    EXPECT_EQ(sp.begin(), kSampleCString);

    EXPECT_EQ(sp.end(), kSampleCString + strlen(kSampleCString));

}



TEST_F(StringPieceTest_1, OperatorSubscript_ReturnsCorrectCharacter_1) {

    StringPiece sp(kSampleString);

    for (size_t i = 0; i < kSampleString.size(); ++i) {

        EXPECT_EQ(sp[i], kSampleString[i]);

    }

}



TEST_F(StringPieceTest_1, EmptyMethod_ReturnsTrueForEmptyString_1) {

    StringPiece sp;

    EXPECT_TRUE(sp.empty());

}



TEST_F(StringPieceTest_1, EmptyMethod_ReturnsFalseForNonEmptyString_1) {

    StringPiece sp(kSampleString);

    EXPECT_FALSE(sp.empty());

}
