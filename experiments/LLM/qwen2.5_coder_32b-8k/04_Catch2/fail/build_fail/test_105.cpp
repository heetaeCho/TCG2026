#include <gtest/gtest.h>

#include <chrono>

#include <ctime>

#include "./TestProjects/Catch2/src/catch2/catch_tostring.hpp"



using namespace Catch;

using namespace std::chrono;



class TimePointToStringTest_105 : public ::testing::Test {

protected:

    system_clock::time_point tp;

};



TEST_F(TimePointToStringTest_105, ConvertValidTimePoint_105) {

    tp = system_clock::from_time_t(1633072800); // 2021-10-01T00:00:00Z

    EXPECT_EQ(convert(tp), "2021-10-01T00:00:00Z");

}



TEST_F(TimePointToStringTest_105, ConvertEpochStart_105) {

    tp = system_clock::from_time_t(0); // 1970-01-01T00:00:00Z

    EXPECT_EQ(convert(tp), "1970-01-01T00:00:00Z");

}



TEST_F(TimePointToStringTest_105, ConvertFutureTimePoint_105) {

    tp = system_clock::from_time_t(4622486400); // 2100-10-01T00:00:00Z

    EXPECT_EQ(convert(tp), "2100-10-01T00:00:00Z");

}



TEST_F(TimePointToStringTest_105, ConvertBoundaryConditionPre1970_105) {

#ifdef _MSC_VER

    tp = system_clock::from_time_t(-1); // Pre-1970 date

    EXPECT_EQ(convert(tp), "gmtime from provided timepoint has failed. This happens e.g. with pre-1970 dates using Microsoft libc");

#else

    tp = system_clock::from_time_t(-1); // Pre-1970 date

    EXPECT_NE(convert(tp), ""); // Expect non-empty string, but specific content depends on implementation

#endif

}
