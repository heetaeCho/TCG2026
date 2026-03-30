#include <gtest/gtest.h>

#include "exiv2/value.hpp"

#include <sstream>



namespace Exiv2 {

    class TimeValue;

}



TEST_F(TimeValueTest_881, WriteValidTime_881) {

    Exiv2::TimeValue timeValue(14, 30, 45, -7, 30);

    std::ostringstream os;

    timeValue.write(os);

    EXPECT_EQ(os.str(), "14:30:45-07:30");

}



TEST_F(TimeValueTest_881, WriteUtcTime_881) {

    Exiv2::TimeValue timeValue(9, 45, 0, 0, 0);

    std::ostringstream os;

    timeValue.write(os);

    EXPECT_EQ(os.str(), "09:45:00+00:00");

}



TEST_F(TimeValueTest_881, WriteNegativeTimezone_881) {

    Exiv2::TimeValue timeValue(23, 59, 59, -12, -45);

    std::ostringstream os;

    timeValue.write(os);

    EXPECT_EQ(os.str(), "23:59:59-12:45");

}



TEST_F(TimeValueTest_881, WritePositiveTimezone_881) {

    Exiv2::TimeValue timeValue(0, 1, 2, 11, 15);

    std::ostringstream os;

    timeValue.write(os);

    EXPECT_EQ(os.str(), "00:01:02+11:15");

}



TEST_F(TimeValueTest_881, WriteBoundaryTime_881) {

    Exiv2::TimeValue timeValue(0, 0, 0, 0, 0);

    std::ostringstream os;

    timeValue.write(os);

    EXPECT_EQ(os.str(), "00:00:00+00:00");

}



TEST_F(TimeValueTest_881, WriteMaxTime_881) {

    Exiv2::TimeValue timeValue(23, 59, 59, 14, 59);

    std::ostringstream os;

    timeValue.write(os);

    EXPECT_EQ(os.str(), "23:59:59+14:59");

}



TEST_F(TimeValueTest_881, WriteMinTime_881) {

    Exiv2::TimeValue timeValue(0, 0, 0, -12, -59);

    std::ostringstream os;

    timeValue.write(os);

    EXPECT_EQ(os.str(), "00:00:00-12:59");

}
