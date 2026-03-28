#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/value.hpp"



using namespace Exiv2;

using namespace testing;



class DateValueTest_873 : public ::testing::Test {

protected:

    DateValue dateValue;

};



TEST_F(DateValueTest_873, ToRational_NormalOperation_873) {

    EXPECT_CALL(dateValue, toInt64(0)).WillOnce(Return(static_cast<int64_t>(12345)));

    Rational result = dateValue.toRational(0);

    EXPECT_EQ(result.first, 12345);

    EXPECT_EQ(result.second, 1);

}



TEST_F(DateValueTest_873, ToRational_BoundaryCondition_MinInt32_873) {

    EXPECT_CALL(dateValue, toInt64(0)).WillOnce(Return(static_cast<int64_t>(std::numeric_limits<int32_t>::min())));

    Rational result = dateValue.toRational(0);

    EXPECT_EQ(result.first, std::numeric_limits<int32_t>::min());

    EXPECT_EQ(result.second, 1);

}



TEST_F(DateValueTest_873, ToRational_BoundaryCondition_MaxInt32_873) {

    EXPECT_CALL(dateValue, toInt64(0)).WillOnce(Return(static_cast<int64_t>(std::numeric_limits<int32_t>::max())));

    Rational result = dateValue.toRational(0);

    EXPECT_EQ(result.first, std::numeric_limits<int32_t>::max());

    EXPECT_EQ(result.second, 1);

}



TEST_F(DateValueTest_873, ToRational_ExceptionalCase_LessThanMinInt32_873) {

    EXPECT_CALL(dateValue, toInt64(0)).WillOnce(Return(static_cast<int64_t>(std::numeric_limits<int32_t>::min()) - 1));

    Rational result = dateValue.toRational(0);

    EXPECT_EQ(result.first, 0);

    EXPECT_EQ(result.second, 1);

}



TEST_F(DateValueTest_873, ToRational_ExceptionalCase_GreaterThanMaxInt32_873) {

    EXPECT_CALL(dateValue, toInt64(0)).WillOnce(Return(static_cast<int64_t>(std::numeric_limits<int32_t>::max()) + 1));

    Rational result = dateValue.toRational(0);

    EXPECT_EQ(result.first, 0);

    EXPECT_EQ(result.second, 1);

}
