#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <exiv2/exif.hpp>

#include <exiv2/value.hpp>

#include "nikonmn_int.hpp"

#include <sstream>



using namespace Exiv2;

using namespace Exiv2::Internal;



class Nikon3MakerNoteTest_486 : public ::testing::Test {

protected:

    Nikon3MakerNote nikonMakerNote_;

    Value mockValue_;

    ExifData mockMetadata_;



    Nikon3MakerNoteTest_486() : mockValue_(unsignedByte) {}

};



TEST_F(Nikon3MakerNoteTest_486, PrintExternalFlashData2Fl6_NormalOperation_486) {

    std::ostringstream os;

    mockValue_.setDataArea(reinterpret_cast<const byte*>(&0xFF), 1); // Set to a value where bit 7 is set

    nikonMakerNote_.printExternalFlashData2Fl6(os, mockValue_, &mockMetadata_);

    EXPECT_EQ(os.str(), "External flash on, Off");

}



TEST_F(Nikon3MakerNoteTest_486, PrintExternalFlashData2Fl6_FlashOff_486) {

    std::ostringstream os;

    mockValue_.setDataArea(reinterpret_cast<const byte*>(&0x00), 1); // Set to a value where bit 7 is not set

    nikonMakerNote_.printExternalFlashData2Fl6(os, mockValue_, &mockMetadata_);

    EXPECT_EQ(os.str(), "External flash off");

}



TEST_F(Nikon3MakerNoteTest_486, PrintExternalFlashData2Fl6_CountNotOne_486) {

    std::ostringstream os;

    ON_CALL(mockValue_, count()).WillByDefault(::testing::Return(2));

    nikonMakerNote_.printExternalFlashData2Fl6(os, mockValue_, &mockMetadata_);

    EXPECT_EQ(os.str(), "(0 0)");

}



TEST_F(Nikon3MakerNoteTest_486, PrintExternalFlashData2Fl6_TypeNotUnsignedByte_486) {

    std::ostringstream os;

    Value mockValue(unsignedShort); // Different type

    nikonMakerNote_.printExternalFlashData2Fl6(os, mockValue, &mockMetadata_);

    EXPECT_EQ(os.str(), "(0)");

}



TEST_F(Nikon3MakerNoteTest_486, PrintExternalFlashData2Fl6_TTLControlMode_486) {

    std::ostringstream os;

    byte data = 0x81; // Bit 7 set for flash on and lower bits set to TTL (1)

    mockValue_.setDataArea(&data, 1);

    nikonMakerNote_.printExternalFlashData2Fl6(os, mockValue_, &mockMetadata_);

    EXPECT_EQ(os.str(), "External flash on, TTL");

}



TEST_F(Nikon3MakerNoteTest_486, PrintExternalFlashData2Fl6_iTTLControlMode_486) {

    std::ostringstream os;

    byte data = 0x82; // Bit 7 set for flash on and lower bits set to iTTL (2)

    mockValue_.setDataArea(&data, 1);

    nikonMakerNote_.printExternalFlashData2Fl6(os, mockValue_, &mockMetadata_);

    EXPECT_EQ(os.str(), "External flash on, iTTL");

}



TEST_F(Nikon3MakerNoteTest_486, PrintExternalFlashData2Fl6_AutoApertureControlMode_486) {

    std::ostringstream os;

    byte data = 0x83; // Bit 7 set for flash on and lower bits set to Auto Aperture (3)

    mockValue_.setDataArea(&data, 1);

    nikonMakerNote_.printExternalFlashData2Fl6(os, mockValue_, &mockMetadata_);

    EXPECT_EQ(os.str(), "External flash on, Auto Aperture");

}



TEST_F(Nikon3MakerNoteTest_486, PrintExternalFlashData2Fl6_AutomaticControlMode_486) {

    std::ostringstream os;

    byte data = 0x84; // Bit 7 set for flash on and lower bits set to Automatic (4)

    mockValue_.setDataArea(&data, 1);

    nikonMakerNote_.printExternalFlashData2Fl6(os, mockValue_, &mockMetadata_);

    EXPECT_EQ(os.str(), "External flash on, Automatic");

}



TEST_F(Nikon3MakerNoteTest_486, PrintExternalFlashData2Fl6_GNControlMode_486) {

    std::ostringstream os;

    byte data = 0x85; // Bit 7 set for flash on and lower bits set to GN (distance priority) (5)

    mockValue_.setDataArea(&data, 1);

    nikonMakerNote_.printExternalFlashData2Fl6(os, mockValue_, &mockMetadata_);

    EXPECT_EQ(os.str(), "External flash on, GN (distance priority)");

}



TEST_F(Nikon3MakerNoteTest_486, PrintExternalFlashData2Fl6_ManualControlMode_486) {

    std::ostringstream os;

    byte data = 0x86; // Bit 7 set for flash on and lower bits set to Manual (6)

    mockValue_.setDataArea(&data, 1);

    nikonMakerNote_.printExternalFlashData2Fl6(os, mockValue_, &mockMetadata_);

    EXPECT_EQ(os.str(), "External flash on, Manual");

}



TEST_F(Nikon3MakerNoteTest_486, PrintExternalFlashData2Fl6_RepeatingFlashControlMode_486) {

    std::ostringstream os;

    byte data = 0x87; // Bit 7 set for flash on and lower bits set to Repeating Flash (7)

    mockValue_.setDataArea(&data, 1);

    nikonMakerNote_.printExternalFlashData2Fl6(os, mockValue_, &mockMetadata_);

    EXPECT_EQ(os.str(), "External flash on, Repeating Flash");

}
