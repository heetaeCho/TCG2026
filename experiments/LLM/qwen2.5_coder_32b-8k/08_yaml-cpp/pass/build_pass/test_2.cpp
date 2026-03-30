#include <gtest/gtest.h>

#include "yaml-cpp/mark.h"



using namespace YAML;



class MarkTest_2 : public ::testing::Test {

protected:

    Mark mark;

};



TEST_F(MarkTest_2, DefaultConstructorInitializesToZero_2) {

    EXPECT_EQ(mark.pos, 0);

    EXPECT_EQ(mark.line, 0);

    EXPECT_EQ(mark.column, 0);

}



TEST_F(MarkTest_2, NullMarkReturnsCorrectValues_2) {

    Mark nullMark = Mark::null_mark();

    EXPECT_EQ(nullMark.pos, -1);

    EXPECT_EQ(nullMark.line, -1);

    EXPECT_EQ(nullMark.column, -1);

}



TEST_F(MarkTest_2, IsNullReturnsTrueForNullMark_2) {

    Mark nullMark = Mark::null_mark();

    EXPECT_TRUE(nullMark.is_null());

}



TEST_F(MarkTest_2, IsNullReturnsFalseForNonNullMark_2) {

    EXPECT_FALSE(mark.is_null());

}
