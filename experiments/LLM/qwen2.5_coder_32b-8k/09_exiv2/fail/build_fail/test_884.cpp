#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/value.hpp"



using namespace Exiv2;



class TimeValueTest : public ::testing::Test {

protected:

    TimeValue timeValue;

};



TEST_F(TimeValueTest_884, ToFloatReturnsCorrectValue_884) {

    // Assuming the internal state of TimeValue is set in a way that toInt64 returns 12345 for n=0

    EXPECT_FLOAT_EQ(timeValue.toFloat(0), static_cast<float>(12345));

}



TEST_F(TimeValueTest_884, ToFloatBoundaryCondition_884) {

    // Assuming the internal state of TimeValue is set in a way that toInt64 returns 0 for n=0

    EXPECT_FLOAT_EQ(timeValue.toFloat(0), static_cast<float>(0));



    // Assuming the internal state of TimeValue is set in a way that toInt64 returns INT64_MAX for n=0

    EXPECT_FLOAT_EQ(timeValue.toFloat(0), static_cast<float>(INT64_MAX));



    // Assuming the internal state of TimeValue is set in a way that toInt64 returns INT64_MIN for n=0

    EXPECT_FLOAT_EQ(timeValue.toFloat(0), static_cast<float>(INT64_MIN));

}



TEST_F(TimeValueTest_884, ToFloatInvalidIndex_884) {

    // Assuming the internal state of TimeValue is set in a way that accessing an invalid index throws or returns 0

    EXPECT_FLOAT_EQ(timeValue.toFloat(1), static_cast<float>(0)); // Invalid index access should return 0 or handle gracefully

}



TEST_F(TimeValueTest_884, ToFloatConsistencyCheck_884) {

    // Assuming the internal state of TimeValue is set in a way that toInt64 returns consistent values for n=0 and n=1

    EXPECT_FLOAT_EQ(timeValue.toFloat(0), timeValue.toFloat(1));

}



TEST_F(TimeValueTest_884, ToFloatConversionCheck_884) {

    // Assuming the internal state of TimeValue is set in a way that toInt64 returns 12345 for n=0

    EXPECT_FLOAT_EQ(timeValue.toFloat(0), static_cast<float>(static_cast<int64_t>(12345)));

}
