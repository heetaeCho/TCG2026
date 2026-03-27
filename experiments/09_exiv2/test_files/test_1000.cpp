#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include <sstream>

#include "TestProjects/exiv2/src/minoltamn_int.cpp"



using namespace Exiv2::Internal;

using namespace testing;



class MinoltaMakerNoteTest_1000 : public ::testing::Test {

protected:

    MinoltaMakerNote minoltaMakerNote_;

};



TEST_F(MinoltaMakerNoteTest_1000, PrintMinoltaExposureSpeedStd_NormalOperation_1000) {

    std::ostringstream os;

    Value value;

    value._typeId = 5; // Assuming long type for toInt64()

    value._size = 1;

    value._data.lValue[0] = 24; // Example value that should result in 2



    minoltaMakerNote_.printMinoltaExposureSpeedStd(os, value, nullptr);



    EXPECT_EQ(os.str(), "2");

}



TEST_F(MinoltaMakerNoteTest_1000, PrintMinoltaExposureSpeedStd_BoundaryConditionZero_1000) {

    std::ostringstream os;

    Value value;

    value._typeId = 5; // Assuming long type for toInt64()

    value._size = 1;

    value._data.lValue[0] = 8; // Example value that should result in 0



    minoltaMakerNote_.printMinoltaExposureSpeedStd(os, value, nullptr);



    EXPECT_EQ(os.str(), "0");

}



TEST_F(MinoltaMakerNoteTest_1000, PrintMinoltaExposureSpeedStd_BoundaryConditionNegative_1000) {

    std::ostringstream os;

    Value value;

    value._typeId = 5; // Assuming long type for toInt64()

    value._size = 1;

    value._data.lValue[0] = 0; // Example value that should result in -1



    minoltaMakerNote_.printMinoltaExposureSpeedStd(os, value, nullptr);



    EXPECT_EQ(os.str(), "-1");

}



TEST_F(MinoltaMakerNoteTest_1000, PrintMinoltaExposureSpeedStd_LargeValue_1000) {

    std::ostringstream os;

    Value value;

    value._typeId = 5; // Assuming long type for toInt64()

    value._size = 1;

    value._data.lValue[0] = 2048; // Example value that should result in 255



    minoltaMakerNote_.printMinoltaExposureSpeedStd(os, value, nullptr);



    EXPECT_EQ(os.str(), "255");

}
