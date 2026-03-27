#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "exiv2/src/minoltamn_int.cpp" // Assuming the file contains the implementation



using namespace Exiv2::Internal;



class MinoltaMakerNoteTest : public ::testing::Test {

protected:

    MinoltaMakerNote minoltaMakerNote;

};



TEST_F(MinoltaMakerNoteTest_1003, PrintMinoltaExposureCompensationStd_NormalOperation_1003) {

    std::ostringstream os;

    Exiv2::Value value;

    value = 512; // Example value

    const ExifData* exifData = nullptr;



    minoltaMakerNote.printMinoltaExposureCompensationStd(os, value, exifData);



    EXPECT_EQ(os.str(), "2");

}



TEST_F(MinoltaMakerNoteTest_1003, PrintMinoltaExposureCompensationStd_ZeroValue_1003) {

    std::ostringstream os;

    Exiv2::Value value;

    value = 0; // Zero value

    const ExifData* exifData = nullptr;



    minoltaMakerNote.printMinoltaExposureCompensationStd(os, value, exifData);



    EXPECT_EQ(os.str(), "0");

}



TEST_F(MinoltaMakerNoteTest_1003, PrintMinoltaExposureCompensationStd_NegativeValue_1003) {

    std::ostringstream os;

    Exiv2::Value value;

    value = -256; // Negative value

    const ExifData* exifData = nullptr;



    minoltaMakerNote.printMinoltaExposureCompensationStd(os, value, exifData);



    EXPECT_EQ(os.str(), "-1");

}



TEST_F(MinoltaMakerNoteTest_1003, PrintMinoltaExposureCompensationStd_MaxValue_1003) {

    std::ostringstream os;

    Exiv2::Value value;

    value = 4294967295; // Max unsigned int value

    const ExifData* exifData = nullptr;



    minoltaMakerNote.printMinoltaExposureCompensationStd(os, value, exifData);



    EXPECT_EQ(os.str(), "16777215");

}



TEST_F(MinoltaMakerNoteTest_1003, PrintMinoltaExposureCompensationStd_MinValue_1003) {

    std::ostringstream os;

    Exiv2::Value value;

    value = -4294967296; // Min signed int value (assuming 32-bit)

    const ExifData* exifData = nullptr;



    minoltaMakerNote.printMinoltaExposureCompensationStd(os, value, exifData);



    EXPECT_EQ(os.str(), "-16777216");

}
