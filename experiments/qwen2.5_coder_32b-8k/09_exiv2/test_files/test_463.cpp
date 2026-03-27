#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include <Exiv2/exiv2.hpp>



using namespace Exiv2;

using namespace Exiv2::Internal;



class Nikon3MakerNoteTest_463 : public ::testing::Test {

protected:

    Nikon3MakerNote nikon3MakerNote;

    Value value;

    ExifData exifData;

};



TEST_F(Nikon3MakerNoteTest_463, Print0x0083_MFOnly_463) {

    std::ostringstream os;

    value = 1u; // Binary: 0001

    nikon3MakerNote.print0x0083(os, value, &exifData);

    EXPECT_EQ(os.str(), "MF ");

}



TEST_F(Nikon3MakerNoteTest_463, Print0x0083_DOnly_463) {

    std::ostringstream os;

    value = 2u; // Binary: 0010

    nikon3MakerNote.print0x0083(os, value, &exifData);

    EXPECT_EQ(os.str(), "D ");

}



TEST_F(Nikon3MakerNoteTest_463, Print0x0083_GOnly_463) {

    std::ostringstream os;

    value = 4u; // Binary: 0100

    nikon3MakerNote.print0x0083(os, value, &exifData);

    EXPECT_EQ(os.str(), "G ");

}



TEST_F(Nikon3MakerNoteTest_463, Print0x0083_VROnly_463) {

    std::ostringstream os;

    value = 8u; // Binary: 1000

    nikon3MakerNote.print0x0083(os, value, &exifData);

    EXPECT_EQ(os.str(), "VR");

}



TEST_F(Nikon3MakerNoteTest_463, Print0x0083_MFAndD_463) {

    std::ostringstream os;

    value = 3u; // Binary: 0011

    nikon3MakerNote.print0x0083(os, value, &exifData);

    EXPECT_EQ(os.str(), "MF D ");

}



TEST_F(Nikon3MakerNoteTest_463, Print0x0083_MFAndG_463) {

    std::ostringstream os;

    value = 5u; // Binary: 0101

    nikon3MakerNote.print0x0083(os, value, &exifData);

    EXPECT_EQ(os.str(), "MF G ");

}



TEST_F(Nikon3MakerNoteTest_463, Print0x0083_MFAndVR_463) {

    std::ostringstream os;

    value = 9u; // Binary: 1001

    nikon3MakerNote.print0x0083(os, value, &exifData);

    EXPECT_EQ(os.str(), "MF VR");

}



TEST_F(Nikon3MakerNoteTest_463, Print0x0083_DAndG_463) {

    std::ostringstream os;

    value = 6u; // Binary: 0110

    nikon3MakerNote.print0x0083(os, value, &exifData);

    EXPECT_EQ(os.str(), "D G ");

}



TEST_F(Nikon3MakerNoteTest_463, Print0x0083_DAndVR_463) {

    std::ostringstream os;

    value = 10u; // Binary: 1010

    nikon3MakerNote.print0x0083(os, value, &exifData);

    EXPECT_EQ(os.str(), "D VR");

}



TEST_F(Nikon3MakerNoteTest_463, Print0x0083_GAndVR_463) {

    std::ostringstream os;

    value = 12u; // Binary: 1100

    nikon3MakerNote.print0x0083(os, value, &exifData);

    EXPECT_EQ(os.str(), "G VR");

}



TEST_F(Nikon3MakerNoteTest_463, Print0x0083_AllFlags_463) {

    std::ostringstream os;

    value = 15u; // Binary: 1111

    nikon3MakerNote.print0x0083(os, value, &exifData);

    EXPECT_EQ(os.str(), "MF D G VR");

}



TEST_F(Nikon3MakerNoteTest_463, Print0x0083_NoFlags_463) {

    std::ostringstream os;

    value = 0u; // Binary: 0000

    nikon3MakerNote.print0x0083(os, value, &exifData);

    EXPECT_EQ(os.str(), "(0)");

}



TEST_F(Nikon3MakerNoteTest_463, Print0x0083_LargeValue_463) {

    std::ostringstream os;

    value = 255u; // Binary: 11111111

    nikon3MakerNote.print0x0083(os, value, &exifData);

    EXPECT_EQ(os.str(), "MF D G VR");

}



TEST_F(Nikon3MakerNoteTest_463, Print0x0083_UnrecognizedBits_463) {

    std::ostringstream os;

    value = 17u; // Binary: 10001

    nikon3MakerNote.print0x0083(os, value, &exifData);

    EXPECT_EQ(os.str(), "MF VR");

}
