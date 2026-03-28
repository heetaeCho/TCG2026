#include <gtest/gtest.h>



// Mocking external collaborators if needed (None in this case)



TEST(radialExtendRangeTest_1888, ValidValueWithinRange_1888) {

    double range[2] = {0.5, 1.5};

    bool valid = true;

    bool result = radialExtendRange(range, 1.0, valid);

    EXPECT_TRUE(result);

    EXPECT_DOUBLE_EQ(range[0], 0.5);

    EXPECT_DOUBLE_EQ(range[1], 1.5);

}



TEST(radialExtendRangeTest_1888, ValidValueBelowRange_1888) {

    double range[2] = {1.0, 2.0};

    bool valid = true;

    bool result = radialExtendRange(range, 0.5, valid);

    EXPECT_TRUE(result);

    EXPECT_DOUBLE_EQ(range[0], 0.5);

    EXPECT_DOUBLE_EQ(range[1], 2.0);

}



TEST(radialExtendRangeTest_1888, ValidValueAboveRange_1888) {

    double range[2] = {0.5, 1.0};

    bool valid = true;

    bool result = radialExtendRange(range, 1.5, valid);

    EXPECT_TRUE(result);

    EXPECT_DOUBLE_EQ(range[0], 0.5);

    EXPECT_DOUBLE_EQ(range[1], 1.5);

}



TEST(radialExtendRangeTest_1888, InvalidValueInitializesRange_1888) {

    double range[2] = {0.0, 0.0};

    bool valid = false;

    bool result = radialExtendRange(range, 1.0, valid);

    EXPECT_TRUE(result);

    EXPECT_DOUBLE_EQ(range[0], 1.0);

    EXPECT_DOUBLE_EQ(range[1], 1.0);

}



TEST(radialExtendRangeTest_1888, BoundaryConditionValidValueAtLowerBound_1888) {

    double range[2] = {1.0, 2.0};

    bool valid = true;

    bool result = radialExtendRange(range, 1.0, valid);

    EXPECT_TRUE(result);

    EXPECT_DOUBLE_EQ(range[0], 1.0);

    EXPECT_DOUBLE_EQ(range[1], 2.0);

}



TEST(radialExtendRangeTest_1888, BoundaryConditionValidValueAtUpperBound_1888) {

    double range[2] = {0.5, 1.0};

    bool valid = true;

    bool result = radialExtendRange(range, 1.0, valid);

    EXPECT_TRUE(result);

    EXPECT_DOUBLE_EQ(range[0], 0.5);

    EXPECT_DOUBLE_EQ(range[1], 1.0);

}



TEST(radialExtendRangeTest_1888, BoundaryConditionInvalidValueAtZero_1888) {

    double range[2] = {0.0, 0.0};

    bool valid = false;

    bool result = radialExtendRange(range, 0.0, valid);

    EXPECT_TRUE(result);

    EXPECT_DOUBLE_EQ(range[0], 0.0);

    EXPECT_DOUBLE_EQ(range[1], 0.0);

}



TEST(radialExtendRangeTest_1888, BoundaryConditionInvalidValueAtNegative_1888) {

    double range[2] = {0.0, 0.0};

    bool valid = false;

    bool result = radialExtendRange(range, -1.5, valid);

    EXPECT_TRUE(result);

    EXPECT_DOUBLE_EQ(range[0], -1.5);

    EXPECT_DOUBLE_EQ(range[1], -1.5);

}
