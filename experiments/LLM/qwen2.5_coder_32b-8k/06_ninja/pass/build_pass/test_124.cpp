#include <gtest/gtest.h>

#include "string_piece_util.h"

#include "string_piece.h"



using namespace std;



class StringPieceUtilTest_124 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(StringPieceUtilTest_124, SplitStringPiece_EmptyString_124) {

    vector<StringPiece> result = SplitStringPiece("", ',');

    EXPECT_EQ(result.size(), 1);

    EXPECT_TRUE(result[0] == StringPiece(""));

}



TEST_F(StringPieceUtilTest_124, SplitStringPiece_NoSeparator_124) {

    vector<StringPiece> result = SplitStringPiece("hello", ',');

    EXPECT_EQ(result.size(), 1);

    EXPECT_TRUE(result[0] == StringPiece("hello"));

}



TEST_F(StringPieceUtilTest_124, SplitStringPiece_SingleSeparator_124) {

    vector<StringPiece> result = SplitStringPiece("hello,world", ',');

    EXPECT_EQ(result.size(), 2);

    EXPECT_TRUE(result[0] == StringPiece("hello"));

    EXPECT_TRUE(result[1] == StringPiece("world"));

}



TEST_F(StringPieceUtilTest_124, SplitStringPiece_MultipleSeparators_124) {

    vector<StringPiece> result = SplitStringPiece("a,b,c,d", ',');

    EXPECT_EQ(result.size(), 4);

    EXPECT_TRUE(result[0] == StringPiece("a"));

    EXPECT_TRUE(result[1] == StringPiece("b"));

    EXPECT_TRUE(result[2] == StringPiece("c"));

    EXPECT_TRUE(result[3] == StringPiece("d"));

}



TEST_F(StringPieceUtilTest_124, SplitStringPiece_TrailingSeparator_124) {

    vector<StringPiece> result = SplitStringPiece("hello,", ',');

    EXPECT_EQ(result.size(), 2);

    EXPECT_TRUE(result[0] == StringPiece("hello"));

    EXPECT_TRUE(result[1] == StringPiece(""));

}



TEST_F(StringPieceUtilTest_124, SplitStringPiece_LeadingSeparator_124) {

    vector<StringPiece> result = SplitStringPiece(",world", ',');

    EXPECT_EQ(result.size(), 2);

    EXPECT_TRUE(result[0] == StringPiece(""));

    EXPECT_TRUE(result[1] == StringPiece("world"));

}



TEST_F(StringPieceUtilTest_124, SplitStringPiece_MultipleConsecutiveSeparators_124) {

    vector<StringPiece> result = SplitStringPiece("hello,,world", ',');

    EXPECT_EQ(result.size(), 3);

    EXPECT_TRUE(result[0] == StringPiece("hello"));

    EXPECT_TRUE(result[1] == StringPiece(""));

    EXPECT_TRUE(result[2] == StringPiece("world"));

}
