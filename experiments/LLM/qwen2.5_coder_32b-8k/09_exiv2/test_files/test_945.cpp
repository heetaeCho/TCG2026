#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "./TestProjects/exiv2/src/canonmn_int.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class CanonMakerNoteTest_945 : public ::testing::Test {

protected:

    Value mockValue;

    std::ostringstream os;

    ExifData exifData;

};



TEST_F(CanonMakerNoteTest_945, Print0x000c_NoExifData_945) {

    CanonMakerNote::print0x000c(os, mockValue, nullptr);

    EXPECT_EQ(os.str(), "");

}



TEST_F(CanonMakerNoteTest_945, Print0x000c_ModelIDNotFound_945) {

    ExifKey key("Exif.Canon.ModelID");

    exifData.add(key, &mockValue);

    mockValue = 0x12345678; // Different ModelID



    CanonMakerNote::print0x000c(os, mockValue, &exifData);

    EXPECT_EQ(os.str(), "0x12345678");

}



TEST_F(CanonMakerNoteTest_945, Print0x000c_ModelIDMatch_ValueConversion_945) {

    ExifKey key("Exif.Canon.ModelID");

    exifData.add(key, &mockValue);

    mockValue = 0x01140000; // Matching ModelID



    Value value;

    value = "123456"; // Example value that will be converted

    CanonMakerNote::print0x000c(os, value, &exifData);

    EXPECT_EQ(os.str(), "007b096");

}



TEST_F(CanonMakerNoteTest_945, Print0x000c_ModelIDMatch_ValueConversionBoundary_945) {

    ExifKey key("Exif.Canon.ModelID");

    exifData.add(key, &mockValue);

    mockValue = 0x01140000; // Matching ModelID



    Value value;

    value = "0"; // Boundary condition: smallest possible value

    CanonMakerNote::print0x000c(os, value, &exifData);

    EXPECT_EQ(os.str(), "0000000");



    os.str(""); // Clearing the output stream for next test



    value = "4294967295"; // Boundary condition: largest possible uint32_t value

    CanonMakerNote::print0x000c(os, value, &exifData);

    EXPECT_EQ(os.str(), "fffff");

}
