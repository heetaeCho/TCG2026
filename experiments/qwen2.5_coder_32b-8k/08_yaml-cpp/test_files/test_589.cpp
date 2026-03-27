#include <gtest/gtest.h>

#include <yaml-cpp/src/null.cpp>  // Assuming this is how to include the file



namespace YAML {



class IsNullStringTest_589 : public ::testing::Test {};



TEST_F(IsNullStringTest_589, EmptyStringReturnsTrue_589) {

    EXPECT_TRUE(IsNullString("", 0));

}



TEST_F(IsNullStringTest_589, TildeReturnsTrue_589) {

    EXPECT_TRUE(IsNullString("~", 1));

}



TEST_F(IsNullStringTest_589, NullLowercaseReturnsTrue_589) {

    EXPECT_TRUE(IsNullString("null", 4));

}



TEST_F(IsNullStringTest_589, NullCapitalizedFirstLetterReturnsTrue_589) {

    EXPECT_TRUE(IsNullString("Null", 4));

}



TEST_F(IsNullStringTest_589, NullUppercaseReturnsTrue_589) {

    EXPECT_TRUE(IsNullString("NULL", 4));

}



TEST_F(IsNullStringTest_589, NonEmptyNonMatchingStringReturnsFalse_589) {

    EXPECT_FALSE(IsNullString("notnull", 7));

}



TEST_F(IsNullStringTest_589, PartialMatchTildeReturnsFalse_589) {

    EXPECT_FALSE(IsNullString("~abc", 4));

}



TEST_F(IsNullStringTest_589, PartialMatchNullLowercaseReturnsFalse_589) {

    EXPECT_FALSE(IsNullString("nul", 3));

}



TEST_F(IsNullStringTest_589, PartialMatchNullCapitalizedFirstLetterReturnsFalse_589) {

    EXPECT_FALSE(IsNullString("Nul", 3));

}



TEST_F(IsNullStringTest_589, PartialMatchNullUppercaseReturnsFalse_589) {

    EXPECT_FALSE(IsNullString("NUL", 3));

}



} // namespace YAML
