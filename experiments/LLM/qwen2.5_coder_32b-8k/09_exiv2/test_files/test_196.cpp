#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/exiv2/src/pentaxmn_int.cpp"

#include <sstream>



using namespace Exiv2::Internal;



class PentaxMakerNoteTest_196 : public ::testing::Test {

protected:

    PentaxMakerNote maker_note;

};



TEST_F(PentaxMakerNoteTest_196, PrintCompensation_NormalOperation_196) {

    std::ostringstream os;

    Exiv2::Value value;

    value.setValue(150); // This corresponds to 1.0 EV

    const ExifData* exif_data = nullptr; // Assuming no dependency on exif_data for this test



    maker_note.printCompensation(os, value, exif_data);



    EXPECT_EQ(os.str(), "1 EV");

}



TEST_F(PentaxMakerNoteTest_196, PrintCompensation_BoundaryConditionMin_196) {

    std::ostringstream os;

    Exiv2::Value value;

    value.setValue(50); // This corresponds to 0.0 EV

    const ExifData* exif_data = nullptr;



    maker_note.printCompensation(os, value, exif_data);



    EXPECT_EQ(os.str(), "0 EV");

}



TEST_F(PentaxMakerNoteTest_196, PrintCompensation_BoundaryConditionMax_196) {

    std::ostringstream os;

    Exiv2::Value value;

    value.setValue(150); // This corresponds to 1.0 EV

    const ExifData* exif_data = nullptr;



    maker_note.printCompensation(os, value, exif_data);



    EXPECT_EQ(os.str(), "1 EV");

}



TEST_F(PentaxMakerNoteTest_196, PrintCompensation_ExceptionalCaseNegativeValue_196) {

    std::ostringstream os;

    Exiv2::Value value;

    value.setValue(30); // This corresponds to -2.0 EV

    const ExifData* exif_data = nullptr;



    maker_note.printCompensation(os, value, exif_data);



    EXPECT_EQ(os.str(), "-2 EV");

}
