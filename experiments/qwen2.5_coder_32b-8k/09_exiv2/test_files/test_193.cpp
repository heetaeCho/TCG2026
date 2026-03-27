#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "TestProjects/exiv2/src/pentaxmn_int.cpp"



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::StrEq;



class PentaxMakerNoteTest_193 : public ::testing::Test {

protected:

    PentaxMakerNote pentaxMakerNote;

    std::ostringstream os;

};



TEST_F(PentaxMakerNoteTest_193, PrintExposure_NormalOperation_193) {

    Exiv2::Value value;

    value.setValue(150); // 1.5 ms

    const ExifData* exifData = nullptr;



    std::ostream& resultOs = pentaxMakerNote.printExposure(os, value, exifData);



    EXPECT_EQ(resultOs.str(), "1.5 ms");

}



TEST_F(PentaxMakerNoteTest_193, PrintExposure_ZeroValue_193) {

    Exiv2::Value value;

    value.setValue(0); // 0 ms

    const ExifData* exifData = nullptr;



    std::ostream& resultOs = pentaxMakerNote.printExposure(os, value, exifData);



    EXPECT_EQ(resultOs.str(), "0 ms");

}



TEST_F(PentaxMakerNoteTest_193, PrintExposure_MaxValue_193) {

    Exiv2::Value value;

    value.setValue(std::numeric_limits<int64_t>::max());

    const ExifData* exifData = nullptr;



    std::ostream& resultOs = pentaxMakerNote.printExposure(os, value, exifData);



    EXPECT_EQ(resultOs.str(), "9.22337e+18 ms");

}



TEST_F(PentaxMakerNoteTest_193, PrintExposure_NegativeValue_193) {

    Exiv2::Value value;

    value.setValue(-100); // -1 ms

    const ExifData* exifData = nullptr;



    std::ostream& resultOs = pentaxMakerNote.printExposure(os, value, exifData);



    EXPECT_EQ(resultOs.str(), "-1 ms");

}
