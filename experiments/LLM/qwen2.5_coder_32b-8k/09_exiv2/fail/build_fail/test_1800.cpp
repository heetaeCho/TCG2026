#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/futils.hpp"



using namespace Exiv2;



TEST_F(getEnvTest_1800, NormalOperation_HTTPPOST_1800) {

    EXPECT_EQ(getEnv(envHTTPPOST), "/exiv2.php");

}



TEST_F(getEnvTest_1800, NormalOperation_TIMEOUT_1800) {

    EXPECT_EQ(getEnv(envTIMEOUT), "40");

}



TEST_F(getEnvTest_1800, BoundaryCondition_LowerBound_1800) {

    EXPECT_EQ(getEnv(envHTTPPOST), "/exiv2.php");

}



TEST_F(getEnvTest_1800, BoundaryCondition_UpperBound_1800) {

    EXPECT_EQ(getEnv(envTIMEOUT), "40");

}



TEST_F(getEnvTest_1800, ExceptionalCase_OutOfRange_Lower_1800) {

    EXPECT_THROW(getEnv(static_cast<EnVar>(envHTTPPOST - 1)), std::out_of_range);

}



TEST_F(getEnvTest_1800, ExceptionalCase_OutOfRange_Upper_1800) {

    EXPECT_THROW(getEnv(static_cast<EnVar>(envTIMEOUT + 1)), std::out_of_range);

}
