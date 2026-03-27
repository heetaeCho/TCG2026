#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "exiv2/value.hpp"

#include "exiv2/exif.hpp"

#include "./TestProjects/exiv2/src/nikonmn_int.hpp"



namespace Exiv2 {

    namespace Internal {



class Nikon3MakerNoteTest_485 : public ::testing::Test {

protected:

    Value value;

    ExifData metadata;



    Nikon3MakerNoteTest_485() : value(unsignedByte) {}

};



TEST_F(Nikon3MakerNoteTest_485, InvalidCount_ReturnsParenthesesValue_485) {

    std::ostringstream os;

    value = Value(unsignedByte);

    value.setDataArea(reinterpret_cast<const byte*>(&dummyData), 2); // Simulate invalid count

    auto result = Nikon3MakerNote::printExternalFlashData1Fl6(os, value, &metadata);

    EXPECT_EQ(result.str(), "(0)");

}



TEST_F(Nikon3MakerNoteTest_485, InvalidTypeId_ReturnsParenthesesValue_485) {

    std::ostringstream os;

    value = Value(asciiString); // Simulate invalid type id

    auto result = Nikon3MakerNote::printExternalFlashData1Fl6(os, value, &metadata);

    EXPECT_EQ(result.str(), "(0)");

}



TEST_F(Nikon3MakerNoteTest_485, FlashDidNotFire_ReturnsDidNotFire_485) {

    std::ostringstream os;

    value = Value(unsignedByte);

    uint32_t v0 = 0; // Simulate flash did not fire

    value.setDataArea(reinterpret_cast<const byte*>(&v0), 1);

    auto result = Nikon3MakerNote::printExternalFlashData1Fl6(os, value, &metadata);

    EXPECT_EQ(result.str(), "Did not fire");

}



TEST_F(Nikon3MakerNoteTest_485, FlashFiredNoAdaptors_ReturnsFired_485) {

    std::ostringstream os;

    value = Value(unsignedByte);

    uint32_t v0 = 1; // Simulate flash fired with no adaptors

    value.setDataArea(reinterpret_cast<const byte*>(&v0), 1);

    auto result = Nikon3MakerNote::printExternalFlashData1Fl6(os, value, &metadata);

    EXPECT_EQ(result.str(), "Fired");

}



TEST_F(Nikon3MakerNoteTest_485, FlashFiredWithBounceAdaptor_ReturnsFiredWithBounceAdaptor_485) {

    std::ostringstream os;

    value = Value(unsignedByte);

    uint32_t v0 = 1 | 4; // Simulate flash fired with bounce adaptor

    value.setDataArea(reinterpret_cast<const byte*>(&v0), 1);

    auto result = Nikon3MakerNote::printExternalFlashData1Fl6(os, value, &metadata);

    EXPECT_EQ(result.str(), "Fired, Bounce Flash adaptor");

}



TEST_F(Nikon3MakerNoteTest_485, FlashFiredWithWideAdaptor_ReturnsFiredWithWideAdaptor_485) {

    std::ostringstream os;

    value = Value(unsignedByte);

    uint32_t v0 = 1 | 16; // Simulate flash fired with wide adaptor

    value.setDataArea(reinterpret_cast<const byte*>(&v0), 1);

    auto result = Nikon3MakerNote::printExternalFlashData1Fl6(os, value, &metadata);

    EXPECT_EQ(result.str(), "Fired, Wide Flash adaptor");

}



TEST_F(Nikon3MakerNoteTest_485, FlashFiredWithNikonDiffusionDome_ReturnsFiredWithNikonDiffusionDome_485) {

    std::ostringstream os;

    value = Value(unsignedByte);

    uint32_t v0 = 1 | 32; // Simulate flash fired with Nikon diffusion dome

    value.setDataArea(reinterpret_cast<const byte*>(&v0), 1);

    auto result = Nikon3MakerNote::printExternalFlashData1Fl6(os, value, &metadata);

    EXPECT_EQ(result.str(), "Fired, Nikon Diffusion Dome");

}



TEST_F(Nikon3MakerNoteTest_485, FlashFiredWithMultipleAdaptors_ReturnsFiredWithAllAdaptors_485) {

    std::ostringstream os;

    value = Value(unsignedByte);

    uint32_t v0 = 1 | 4 | 16 | 32; // Simulate flash fired with all adaptors

    value.setDataArea(reinterpret_cast<const byte*>(&v0), 1);

    auto result = Nikon3MakerNote::printExternalFlashData1Fl6(os, value, &metadata);

    EXPECT_EQ(result.str(), "Fired, Bounce Flash adaptor, Wide Flash adaptor, Nikon Diffusion Dome");

}



} // namespace Internal

} // namespace Exiv2
