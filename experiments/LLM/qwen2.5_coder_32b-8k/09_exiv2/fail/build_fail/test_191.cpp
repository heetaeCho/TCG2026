#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "TestProjects/exiv2/src/pentaxmn_int.cpp"



using namespace Exiv2::Internal;



// Test fixture for PentaxMakerNote class

class PentaxMakerNoteTest_191 : public ::testing::Test {

protected:

    PentaxMakerNote makerNote;

};



TEST_F(PentaxMakerNoteTest_191, PrintDate_ValidInput_ReturnsFormattedString_191) {

    std::ostringstream os;

    Exiv2::Value value;

    value.setValue(Exiv2::DataBuf<uint32_t>({0x12, 0x34, 56, 78}));

    makerNote.printDate(os, value, nullptr);

    EXPECT_EQ(os.str(), "4660:34:56");

}



TEST_F(PentaxMakerNoteTest_191, PrintDate_ZeroValues_ReturnsZeroString_191) {

    std::ostringstream os;

    Exiv2::Value value;

    value.setValue(Exiv2::DataBuf<uint32_t>({0x00, 0x00, 0x00, 0x00}));

    makerNote.printDate(os, value, nullptr);

    EXPECT_EQ(os.str(), "0:00:00");

}



TEST_F(PentaxMakerNoteTest_191, PrintDate_MaxValues_ReturnsMaxString_191) {

    std::ostringstream os;

    Exiv2::Value value;

    value.setValue(Exiv2::DataBuf<uint32_t>({0xFF, 0xFF, 59, 59}));

    makerNote.printDate(os, value, nullptr);

    EXPECT_EQ(os.str(), "65535:59:59");

}



TEST_F(PentaxMakerNoteTest_191, PrintDate_BoundaryValues_ReturnsBoundaryString_191) {

    std::ostringstream os;

    Exiv2::Value value;

    value.setValue(Exiv2::DataBuf<uint32_t>({0x00, 0xFF, 59, 59}));

    makerNote.printDate(os, value, nullptr);

    EXPECT_EQ(os.str(), "255:59:59");

}



TEST_F(PentaxMakerNoteTest_191, PrintDate_ExifDataNull_NoCrash_191) {

    std::ostringstream os;

    Exiv2::Value value;

    value.setValue(Exiv2::DataBuf<uint32_t>({0x00, 0x00, 0x00, 0x00}));

    makerNote.printDate(os, value, nullptr);

    EXPECT_EQ(os.str(), "0:00:00");

}
