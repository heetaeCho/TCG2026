#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"

#include "./TestProjects/exiv2/src/nikonmn_int.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;

using testing::_;



class Nikon3MakerNoteTest_487 : public ::testing::Test {

protected:

    Nikon3MakerNote maker_note_;

    std::ostringstream os_;

    Value value_{unsignedByte};

    const ExifData* metadata_{nullptr};



    void SetUp() override {

        // Setup for each test

    }



    void TearDown() override {

        // Cleanup after each test

    }

};



TEST_F(Nikon3MakerNoteTest_487, NormalOperationExternalFlashOnZoomOverride_487) {

    value_.setDataArea(reinterpret_cast<const byte*>(&0x81), 1); // External flash on and zoom override

    maker_note_.printExternalFlashData1Fl7(os_, value_, metadata_);

    EXPECT_EQ(os_.str(), "External flash on, External flash zoom override");

}



TEST_F(Nikon3MakerNoteTest_487, NormalOperationExternalFlashOnNoZoomOverride_487) {

    value_.setDataArea(reinterpret_cast<const byte*>(&0x01), 1); // External flash on and no zoom override

    maker_note_.printExternalFlashData1Fl7(os_, value_, metadata_);

    EXPECT_EQ(os_.str(), "External flash on, No external flash zoom override");

}



TEST_F(Nikon3MakerNoteTest_487, NormalOperationExternalFlashOff_487) {

    value_.setDataArea(reinterpret_cast<const byte*>(&0x00), 1); // External flash off

    maker_note_.printExternalFlashData1Fl7(os_, value_, metadata_);

    EXPECT_EQ(os_.str(), "External flash off");

}



TEST_F(Nikon3MakerNoteTest_487, BoundaryConditionCountNotOne_487) {

    value_.setDataArea(reinterpret_cast<const byte*>(&0x81), 2); // count is not 1

    maker_note_.printExternalFlashData1Fl7(os_, value_, metadata_);

    EXPECT_EQ(os_.str(), "(0x81)");

}



TEST_F(Nikon3MakerNoteTest_487, BoundaryConditionTypeIdNotUnsignedByte_487) {

    Value invalidValue(unsignedShort);

    invalidValue.setDataArea(reinterpret_cast<const byte*>(&0x81), 1); // typeId is not unsignedByte

    maker_note_.printExternalFlashData1Fl7(os_, invalidValue, metadata_);

    EXPECT_EQ(os_.str(), "(0x81)");

}



TEST_F(Nikon3MakerNoteTest_487, FlashAdaptorsBounceFlash_487) {

    value_.setDataArea(reinterpret_cast<const byte*>(&0x05), 1); // Bounce Flash adaptor

    maker_note_.printExternalFlashData1Fl7(os_, value_, metadata_);

    EXPECT_EQ(os_.str(), "External flash on, No external flash zoom override, Bounce Flash adaptor");

}



TEST_F(Nikon3MakerNoteTest_487, FlashAdaptorsWideFlash_487) {

    value_.setDataArea(reinterpret_cast<const byte*>(&0x11), 1); // Wide Flash adaptor

    maker_note_.printExternalFlashData1Fl7(os_, value_, metadata_);

    EXPECT_EQ(os_.str(), "External flash on, No external flash zoom override, Wide Flash adaptor");

}



TEST_F(Nikon3MakerNoteTest_487, FlashAdaptorsDiffusionDome_487) {

    value_.setDataArea(reinterpret_cast<const byte*>(&0x21), 1); // Nikon Diffusion Dome

    maker_note_.printExternalFlashData1Fl7(os_, value_, metadata_);

    EXPECT_EQ(os_.str(), "External flash on, No external flash zoom override, Nikon Diffusion Dome");

}



TEST_F(Nikon3MakerNoteTest_487, FlashAdaptorsMultiple_487) {

    value_.setDataArea(reinterpret_cast<const byte*>(&0x35), 1); // Multiple adaptors

    maker_note_.printExternalFlashData1Fl7(os_, value_, metadata_);

    EXPECT_EQ(os_.str(), "External flash on, No external flash zoom override, Bounce Flash adaptor, Wide Flash adaptor, Nikon Diffusion Dome");

}
