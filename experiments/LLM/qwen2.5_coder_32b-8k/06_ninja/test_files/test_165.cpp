#include <gtest/gtest.h>

#include "edit_distance.cc"



TEST(EditDistanceTest_165, IdenticalStringsNoReplacements_165) {

    StringPiece s1("test");

    StringPiece s2("test");

    EXPECT_EQ(EditDistance(s1, s2, false, 0), 0);

}



TEST(EditDistanceTest_165, IdenticalStringsAllowReplacements_165) {

    StringPiece s1("test");

    StringPiece s2("test");

    EXPECT_EQ(EditDistance(s1, s2, true, 0), 0);

}



TEST(EditDistanceTest_165, OneCharacterDifferenceNoReplacements_165) {

    StringPiece s1("test");

    StringPiece s2("tast");

    EXPECT_EQ(EditDistance(s1, s2, false, 0), 1);

}



TEST(EditDistanceTest_165, OneCharacterDifferenceAllowReplacements_165) {

    StringPiece s1("test");

    StringPiece s2("tast");

    EXPECT_EQ(EditDistance(s1, s2, true, 0), 1);

}



TEST(EditDistanceTest_165, InsertionAtEndNoReplacements_165) {

    StringPiece s1("test");

    StringPiece s2("tests");

    EXPECT_EQ(EditDistance(s1, s2, false, 0), 1);

}



TEST(EditDistanceTest_165, InsertionAtEndAllowReplacements_165) {

    StringPiece s1("test");

    StringPiece s2("tests");

    EXPECT_EQ(EditDistance(s1, s2, true, 0), 1);

}



TEST(EditDistanceTest_165, DeletionAtEndNoReplacements_165) {

    StringPiece s1("tests");

    StringPiece s2("test");

    EXPECT_EQ(EditDistance(s1, s2, false, 0), 1);

}



TEST(EditDistanceTest_165, DeletionAtEndAllowReplacements_165) {

    StringPiece s1("tests");

    StringPiece s2("test");

    EXPECT_EQ(EditDistance(s1, s2, true, 0), 1);

}



TEST(EditDistanceTest_165, CompleteMismatchNoReplacements_165) {

    StringPiece s1("test");

    StringPiece s2("abcd");

    EXPECT_EQ(EditDistance(s1, s2, false, 0), 4);

}



TEST(EditDistanceTest_165, CompleteMismatchAllowReplacements_165) {

    StringPiece s1("test");

    StringPiece s2("abcd");

    EXPECT_EQ(EditDistance(s1, s2, true, 0), 4);

}



TEST(EditDistanceTest_165, MaxEditDistanceReachedNoReplacements_165) {

    StringPiece s1("kitten");

    StringPiece s2("sitting");

    EXPECT_EQ(EditDistance(s1, s2, false, 3), 4);

}



TEST(EditDistanceTest_165, MaxEditDistanceReachedAllowReplacements_165) {

    StringPiece s1("kitten");

    StringPiece s2("sitting");

    EXPECT_EQ(EditDistance(s1, s2, true, 3), 4);

}



TEST(EditDistanceTest_165, EmptyStringsNoReplacements_165) {

    StringPiece s1("");

    StringPiece s2("");

    EXPECT_EQ(EditDistance(s1, s2, false, 0), 0);

}



TEST(EditDistanceTest_165, EmptyStringsAllowReplacements_165) {

    StringPiece s1("");

    StringPiece s2("");

    EXPECT_EQ(EditDistance(s1, s2, true, 0), 0);

}



TEST(EditDistanceTest_165, OneEmptyStringNoReplacements_165) {

    StringPiece s1("test");

    StringPiece s2("");

    EXPECT_EQ(EditDistance(s1, s2, false, 0), 4);

}



TEST(EditDistanceTest_165, OneEmptyStringAllowReplacements_165) {

    StringPiece s1("test");

    StringPiece s2("");

    EXPECT_EQ(EditDistance(s1, s2, true, 0), 4);

}
