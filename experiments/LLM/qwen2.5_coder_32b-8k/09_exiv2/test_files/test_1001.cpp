#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <iostream>

#include <sstream>

#include "minoltamn_int.cpp" // Assuming this file is included for the class definition



using namespace Exiv2::Internal;



class MinoltaMakerNoteTest : public ::testing::Test {

protected:

    MinoltaMakerNote minoltaMakerNote;

};



TEST_F(MinoltaMakerNoteTest_1001, PrintMinoltaExposureTimeStd_NormalOperation_1001) {

    std::ostringstream os;

    ExifData exifData; // Assuming ExifData is default constructible

    Value value(48);   // Example value that should result in 0 after calculation ((48 / 8) - 6)



    minoltaMakerNote.printMinoltaExposureTimeStd(os, value, &exifData);



    EXPECT_EQ("0", os.str());

}



TEST_F(MinoltaMakerNoteTest_1001, PrintMinoltaExposureTimeStd_BoundaryCondition_LowerBound_1001) {

    std::ostringstream os;

    ExifData exifData; // Assuming ExifData is default constructible

    Value value(47);   // Example value that should result in -1 after calculation ((47 / 8) - 6)



    minoltaMakerNote.printMinoltaExposureTimeStd(os, value, &exifData);



    EXPECT_EQ("-1", os.str());

}



TEST_F(MinoltaMakerNoteTest_1001, PrintMinoltaExposureTimeStd_BoundaryCondition_UpperBound_1001) {

    std::ostringstream os;

    ExifData exifData; // Assuming ExifData is default constructible

    Value value(128);  // Example value that should result in 7 after calculation ((128 / 8) - 6)



    minoltaMakerNote.printMinoltaExposureTimeStd(os, value, &exifData);



    EXPECT_EQ("7", os.str());

}



TEST_F(MinoltaMakerNoteTest_1001, PrintMinoltaExposureTimeStd_ExceptionalCase_ZeroValue_1001) {

    std::ostringstream os;

    ExifData exifData; // Assuming ExifData is default constructible

    Value value(0);    // Example value that should result in -6 after calculation ((0 / 8) - 6)



    minoltaMakerNote.printMinoltaExposureTimeStd(os, value, &exifData);



    EXPECT_EQ("-6", os.str());

}



TEST_F(MinoltaMakerNoteTest_1001, PrintMinoltaExposureTimeStd_ExceptionalCase_NegativeValue_1001) {

    std::ostringstream os;

    ExifData exifData; // Assuming ExifData is default constructible

    Value value(-8);   // Example value that should result in -7 after calculation ((-8 / 8) - 6)



    minoltaMakerNote.printMinoltaExposureTimeStd(os, value, &exifData);



    EXPECT_EQ("-7", os.str());

}
