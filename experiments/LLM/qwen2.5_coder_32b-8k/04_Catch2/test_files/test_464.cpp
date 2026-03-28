#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_case_insensitive_comparisons.hpp"

#include "./TestProjects/Catch2/src/catch2/internal/catch_stringref.hpp"



using namespace Catch;

using namespace Catch::Detail;



class CaseInsensitiveLessTest : public ::testing::Test {

protected:

    CaseInsensitiveLess comparator;

};



TEST_F(CaseInsensitiveLessTest_464, NormalOperationLowerCaseFirst_464) {

    StringRef lhs("apple");

    StringRef rhs("banana");

    EXPECT_FALSE(comparator(lhs, rhs));

}



TEST_F(CaseInsensitiveLessTest_464, NormalOperationUpperCaseSecond_464) {

    StringRef lhs("APPLE");

    StringRef rhs("Banana");

    EXPECT_TRUE(comparator(lhs, rhs));

}



TEST_F(CaseInsensitiveLessTest_464, NormalOperationMixedCase_464) {

    StringRef lhs("ApPlE");

    StringRef rhs("bAnAnA");

    EXPECT_TRUE(comparator(lhs, rhs));

}



TEST_F(CaseInsensitiveLessTest_464, EqualStrings_464) {

    StringRef lhs("apple");

    StringRef rhs("APPLE");

    EXPECT_FALSE(comparator(lhs, rhs));

}



TEST_F(CaseInsensitiveLessTest_464, EmptyStringFirst_464) {

    StringRef lhs("");

    StringRef rhs("banana");

    EXPECT_TRUE(comparator(lhs, rhs));

}



TEST_F(CaseInsensitiveLessTest_464, EmptyStringSecond_464) {

    StringRef lhs("apple");

    StringRef rhs("");

    EXPECT_FALSE(comparator(lhs, rhs));

}



TEST_F(CaseInsensitiveLessTest_464, BothEmptyStrings_464) {

    StringRef lhs("");

    StringRef rhs("");

    EXPECT_FALSE(comparator(lhs, rhs));

}
