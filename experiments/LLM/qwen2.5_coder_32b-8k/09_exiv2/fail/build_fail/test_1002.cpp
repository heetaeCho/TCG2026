#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "minoltamn_int.cpp"  // Assuming the class is defined in this file



using namespace Exiv2::Internal;

using ::testing::_;



class MinoltaMakerNoteTest : public ::testing::Test {

protected:

    MinoltaMakerNote minoltaMakerNote;

};



TEST_F(MinoltaMakerNoteTest, PrintMinoltaFNumberStd_NormalOperation_1002) {

    std::ostringstream os;

    Exiv2::Value value;

    value.setValue(48);  // (48 / 8) - 1 = 5



    minoltaMakerNote.printMinoltaFNumberStd(os, value, nullptr);



    EXPECT_EQ(os.str(), "5");

}



TEST_F(MinoltaMakerNoteTest, PrintMinoltaFNumberStd_BoundaryConditionZero_1002) {

    std::ostringstream os;

    Exiv2::Value value;

    value.setValue(0);  // (0 / 8) - 1 = -1



    minoltaMakerNote.printMinoltaFNumberStd(os, value, nullptr);



    EXPECT_EQ(os.str(), "-1");

}



TEST_F(MinoltaMakerNoteTest, PrintMinoltaFNumberStd_BoundaryConditionNegative_1002) {

    std::ostringstream os;

    Exiv2::Value value;

    value.setValue(-8);  // (-8 / 8) - 1 = -2



    minoltaMakerNote.printMinoltaFNumberStd(os, value, nullptr);



    EXPECT_EQ(os.str(), "-2");

}



TEST_F(MinoltaMakerNoteTest, PrintMinoltaFNumberStd_LargeValue_1002) {

    std::ostringstream os;

    Exiv2::Value value;

    value.setValue(1024);  // (1024 / 8) - 1 = 127



    minoltaMakerNote.printMinoltaFNumberStd(os, value, nullptr);



    EXPECT_EQ(os.str(), "127");

}



TEST_F(MinoltaMakerNoteTest, PrintMinoltaFNumberStd_ExifDataIgnored_1002) {

    std::ostringstream os;

    Exiv2::Value value;

    value.setValue(48);  // (48 / 8) - 1 = 5

    Exiv2::ExifData exifData;  // Mock ExifData object



    minoltaMakerNote.printMinoltaFNumberStd(os, value, &exifData);



    EXPECT_EQ(os.str(), "5");

}
