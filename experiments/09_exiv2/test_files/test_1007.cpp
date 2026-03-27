#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include <Exiv2/exiv2.hpp>



using namespace Exiv2;

using namespace Exiv2::Internal;



class MinoltaMakerNoteTest_1007 : public ::testing::Test {

protected:

    MinoltaMakerNote minoltaMakerNote;

    Value mockValue;

};



TEST_F(MinoltaMakerNoteTest_1007, PrintMinoltaFlashExposureCompStd_NormalOperation_1007) {

    std::ostringstream os;

    int64_t testValue = 21; // (21 - 6) / 3 = 5

    mockValue.setValue(testValue);



    minoltaMakerNote.printMinoltaFlashExposureCompStd(os, mockValue, nullptr);



    EXPECT_EQ("5", os.str());

}



TEST_F(MinoltaMakerNoteTest_1007, PrintMinoltaFlashExposureCompStd_BoundaryCondition_Zero_1007) {

    std::ostringstream os;

    int64_t testValue = 6; // (6 - 6) / 3 = 0

    mockValue.setValue(testValue);



    minoltaMakerNote.printMinoltaFlashExposureCompStd(os, mockValue, nullptr);



    EXPECT_EQ("0", os.str());

}



TEST_F(MinoltaMakerNoteTest_1007, PrintMinoltaFlashExposureCompStd_BoundaryCondition_Negative_1007) {

    std::ostringstream os;

    int64_t testValue = -3; // (-3 - 6) / 3 = -3

    mockValue.setValue(testValue);



    minoltaMakerNote.printMinoltaFlashExposureCompStd(os, mockValue, nullptr);



    EXPECT_EQ("-3", os.str());

}



TEST_F(MinoltaMakerNoteTest_1007, PrintMinoltaFlashExposureCompStd_BoundaryCondition_MaxInt64_1007) {

    std::ostringstream os;

    int64_t testValue = std::numeric_limits<int64_t>::max(); // Large value

    mockValue.setValue(testValue);



    minoltaMakerNote.printMinoltaFlashExposureCompStd(os, mockValue, nullptr);



    EXPECT_EQ(std::to_string((testValue - 6) / 3), os.str());

}



TEST_F(MinoltaMakerNoteTest_1007, PrintMinoltaFlashExposureCompStd_BoundaryCondition_MinInt64_1007) {

    std::ostringstream os;

    int64_t testValue = std::numeric_limits<int64_t>::min(); // Large negative value

    mockValue.setValue(testValue);



    minoltaMakerNote.printMinoltaFlashExposureCompStd(os, mockValue, nullptr);



    EXPECT_EQ(std::to_string((testValue - 6) / 3), os.str());

}
