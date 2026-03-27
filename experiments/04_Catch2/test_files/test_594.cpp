#include <gtest/gtest.h>

#include "catch2/internal/catch_string_manip.hpp"



namespace Catch {



class ReplaceInPlaceTest_594 : public ::testing::Test {

protected:

    std::string str;

};



TEST_F(ReplaceInPlaceTest_594, NoReplacementNeeded_594) {

    str = "hello";

    EXPECT_FALSE(replaceInPlace(str, "world", "there"));

    EXPECT_EQ(str, "hello");

}



TEST_F(ReplaceInPlaceTest_594, SingleReplacementAtStart_594) {

    str = "hello world";

    EXPECT_TRUE(replaceInPlace(str, "hello", "hi"));

    EXPECT_EQ(str, "hi world");

}



TEST_F(ReplaceInPlaceTest_594, SingleReplacementAtEnd_594) {

    str = "hello world";

    EXPECT_TRUE(replaceInPlace(str, "world", "there"));

    EXPECT_EQ(str, "hello there");

}



TEST_F(ReplaceInPlaceTest_594, MultipleReplacements_594) {

    str = "banana";

    EXPECT_TRUE(replaceInPlace(str, "na", "ma"));

    EXPECT_EQ(str, "bamama");

}



TEST_F(ReplaceInPlaceTest_594, ReplaceWithEmptyString_594) {

    str = "banana";

    EXPECT_TRUE(replaceInPlace(str, "an", ""));

    EXPECT_EQ(str, "ba");

}



TEST_F(ReplaceInPlaceTest_594, EmptyOriginalString_594) {

    str = "";

    EXPECT_FALSE(replaceInPlace(str, "test", "replace"));

    EXPECT_EQ(str, "");

}



TEST_F(ReplaceInPlaceTest_594, EmptySearchString_594) {

    str = "hello";

    EXPECT_THROW(replaceInPlace(str, "", "there"), std::invalid_argument);

}



TEST_F(ReplaceInPlaceTest_594, ReplaceWithSelf_594) {

    str = "test test test";

    EXPECT_FALSE(replaceInPlace(str, "test", "test"));

    EXPECT_EQ(str, "test test test");

}



TEST_F(ReplaceInPlaceTest_594, OverlappingReplacement_594) {

    str = "abababa";

    EXPECT_TRUE(replaceInPlace(str, "aba", "xxx"));

    EXPECT_EQ(str, "xxxbaxx");

}



}  // namespace Catch
