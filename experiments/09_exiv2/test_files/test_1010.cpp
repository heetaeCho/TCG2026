#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "minoltamn_int.cpp"  // Include the partial implementation



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::Return;

using ::testing::StrEq;



class MinoltaMakerNoteTest_1010 : public ::testing::Test {

protected:

    MinoltaMakerNote minoltaMakerNote;

};



TEST_F(MinoltaMakerNoteTest_1010, PrintMinoltaExposureManualBias5D_NormalOperation_1010) {

    std::ostringstream os;

    Exiv2::Value value;

    value.setValue(384);  // This should result in (384 - 128) / 24 = 10.67



    minoltaMakerNote.printMinoltaExposureManualBias5D(os, value, nullptr);



    EXPECT_EQ(os.str(), "10.67");

}



TEST_F(MinoltaMakerNoteTest_1010, PrintMinoltaExposureManualBias5D_BoundaryConditionZero_1010) {

    std::ostringstream os;

    Exiv2::Value value;

    value.setValue(128);  // This should result in (128 - 128) / 24 = 0.00



    minoltaMakerNote.printMinoltaExposureManualBias5D(os, value, nullptr);



    EXPECT_EQ(os.str(), "0.00");

}



TEST_F(MinoltaMakerNoteTest_1010, PrintMinoltaExposureManualBias5D_BoundaryConditionNegative_1010) {

    std::ostringstream os;

    Exiv2::Value value;

    value.setValue(64);  // This should result in (64 - 128) / 24 = -2.67



    minoltaMakerNote.printMinoltaExposureManualBias5D(os, value, nullptr);



    EXPECT_EQ(os.str(), "-2.67");

}



TEST_F(MinoltaMakerNoteTest_1010, PrintMinoltaExposureManualBias5D_BoundaryConditionMax_1010) {

    std::ostringstream os;

    Exiv2::Value value;

    value.setValue(448);  // This should result in (448 - 128) / 24 = 13.33



    minoltaMakerNote.printMinoltaExposureManualBias5D(os, value, nullptr);



    EXPECT_EQ(os.str(), "13.33");

}



TEST_F(MinoltaMakerNoteTest_1010, PrintMinoltaExposureManualBias5D_ExifDataNullptr_1010) {

    std::ostringstream os;

    Exiv2::Value value;

    value.setValue(384);  // This should result in (384 - 128) / 24 = 10.67



    minoltaMakerNote.printMinoltaExposureManualBias5D(os, value, nullptr);



    EXPECT_EQ(os.str(), "10.67");

}
