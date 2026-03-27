#include <gtest/gtest.h>

#include "elide_middle.cc"



TEST_F(ElideMiddleInPlaceTest_107, NoChangeWhenShorterThanMaxWidth_107) {

    std::string str = "hello";

    size_t max_width = 10;

    ElideMiddleInPlace(str, max_width);

    EXPECT_EQ(str, "hello");

}



TEST_F(ElideMiddleInPlaceTest_107, NoChangeWhenEqualToMaxWidth_107) {

    std::string str = "hello";

    size_t max_width = 5;

    ElideMiddleInPlace(str, max_width);

    EXPECT_EQ(str, "hello");

}



TEST_F(ElideMiddleInPlaceTest_107, ReplaceWithEllipsisWhenLongerThanMaxWidthNoAnsi_107) {

    std::string str = "this is a test string";

    size_t max_width = 15;

    ElideMiddleInPlace(str, max_width);

    EXPECT_EQ(str, "this ... string");

}



TEST_F(ElideMiddleInPlaceTest_107, ReplaceWithEllipsisWhenLongerThanMaxWidthMinWidth_107) {

    std::string str = "abc";

    size_t max_width = 2;

    ElideMiddleInPlace(str, max_width);

    EXPECT_EQ(str, "..");

}



TEST_F(ElideMiddleInPlaceTest_107, ReplaceWithEllipsisWhenLongerThanMaxWidthExactFit_107) {

    std::string str = "this is a test";

    size_t max_width = 8;

    ElideMiddleInPlace(str, max_width);

    EXPECT_EQ(str, "thi...st");

}



TEST_F(ElideMiddleInPlaceTest_107, HandleAnsiSequencesCorrectlyNoChange_107) {

    std::string str = "\x1b[31mhello\x1b[0m";

    size_t max_width = 20;

    ElideMiddleInPlace(str, max_width);

    EXPECT_EQ(str, "\x1b[31mhello\x1b[0m");

}



TEST_F(ElideMiddleInPlaceTest_107, HandleAnsiSequencesCorrectlyWithEllipsis_107) {

    std::string str = "\x1b[31mthis is a test string\x1b[0m";

    size_t max_width = 20;

    ElideMiddleInPlace(str, max_width);

    EXPECT_EQ(str, "\x1b[31mthi...str\x1b[0m");

}



TEST_F(ElideMiddleInPlaceTest_107, HandleAnsiSequencesExactFitWithEllipsis_107) {

    std::string str = "\x1b[31mthis is a test string\x1b[0m";

    size_t max_width = 15;

    ElideMiddleInPlace(str, max_width);

    EXPECT_EQ(str, "\x1b[31mth...ng\x1b[0m");

}



TEST_F(ElideMiddleInPlaceTest_107, HandleAnsiSequencesWithMinWidth_107) {

    std::string str = "\x1b[31mabc\x1b[0m";

    size_t max_width = 2;

    ElideMiddleInPlace(str, max_width);

    EXPECT_EQ(str, "..");

}



TEST_F(ElideMiddleInPlaceTest_107, HandleAnsiSequencesWithVisibleWidthLessThanMaxWidth_107) {

    std::string str = "\x1b[31mabc\x1b[0m";

    size_t max_width = 10;

    ElideMiddleInPlace(str, max_width);

    EXPECT_EQ(str, "\x1b[31mabc\x1b[0m");

}
