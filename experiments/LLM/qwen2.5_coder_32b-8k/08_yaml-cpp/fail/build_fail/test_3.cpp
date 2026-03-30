#include <gtest/gtest.h>

#include "yaml-cpp/mark.h"



using namespace YAML;



class MarkTest_3 : public ::testing::Test {

protected:

    Mark mark;

};



TEST_F(MarkTest_3, DefaultConstructorInitializesToZero_3) {

    EXPECT_EQ(mark.pos, 0);

    EXPECT_EQ(mark.line, 0);

    EXPECT_EQ(mark.column, 0);

}



TEST_F(MarkTest_3, NullMarkIsCorrectlyIdentified_3) {

    Mark null_mark = Mark::null_mark();

    EXPECT_TRUE(null_mark.is_null());

}



TEST_F(MarkTest_3, NonNullMarkIsNotIdentifiedAsNull_3) {

    Mark non_null_mark(1, 2, 3);

    EXPECT_FALSE(non_null_mark.is_null());

}



TEST_F(MarkTest_3, BoundaryConditionsWithNegativeValues_3) {

    Mark boundary_mark(-1, -1, -1);

    EXPECT_TRUE(boundary_mark.is_null());



    Mark boundary_mark_pos(-1, 0, 0);

    EXPECT_FALSE(boundary_mark_pos.is_null());



    Mark boundary_mark_line(0, -1, 0);

    EXPECT_FALSE(boundary_mark_line.is_null());



    Mark boundary_mark_column(0, 0, -1);

    EXPECT_FALSE(boundary_mark_column.is_null());

}



TEST_F(MarkTest_3, BoundaryConditionsWithPositiveValues_3) {

    Mark positive_mark(1, 1, 1);

    EXPECT_FALSE(positive_mark.is_null());

}
