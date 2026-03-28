#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"

#include "TestProjects/exiv2/src/nikonmn_int.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class Nikon3MakerNoteTest_498 : public ::testing::Test {

protected:

    Nikon3MakerNote nikonMakerNote;

    std::ostringstream os;

    Value value;

    ExifData metadata;



    void SetUp() override {

        // Initialize a default Value with unsignedByte type

        value = Value(TypeId::unsignedByte);

        value.setValue(0x12);  // Arbitrary initial value



        // Initialize metadata with necessary entries

        Exifdatum exifDatum(ExifKey("Exif.NikonFl7.FlashGroupBCControlData"), &value);

        metadata.add(exifDatum.key(), &exifDatum.value());

    }

};



TEST_F(Nikon3MakerNoteTest_498, ValueCountNotOne_498) {

    value.setValue({0x12, 0x34});  // More than one byte

    nikonMakerNote.printFlashGroupCDataFl7(os, value, &metadata);

    EXPECT_EQ(os.str(), "(0x12, 0x34)");

}



TEST_F(Nikon3MakerNoteTest_498, ValueTypeNotUnsignedByte_498) {

    Value invalidValue(TypeId::asciiString);  // Invalid type

    nikonMakerNote.printFlashGroupCDataFl7(os, invalidValue, &metadata);

    EXPECT_EQ(os.str(), "(0x12)");

}



TEST_F(Nikon3MakerNoteTest_498, MetadataIsNullptr_498) {

    nikonMakerNote.printFlashGroupCDataFl7(os, value, nullptr);

    EXPECT_EQ(os.str(), "(0x12)");

}



TEST_F(Nikon3MakerNoteTest_498, FlashGroupBCControlDataNotFound_498) {

    metadata.clear();  // Remove the necessary key

    nikonMakerNote.printFlashGroupCDataFl7(os, value, &metadata);

    EXPECT_EQ(os.str(), "(0x12)");

}



TEST_F(Nikon3MakerNoteTest_498, FlashGroupBCControlDataCountNotOne_498) {

    Exifdatum exifDatum(ExifKey("Exif.NikonFl7.FlashGroupBCControlData"), &value);

    exifDatum.setValue({0x12, 0x34});  // More than one byte

    metadata.add(exifDatum.key(), &exifDatum.value());

    nikonMakerNote.printFlashGroupCDataFl7(os, value, &metadata);

    EXPECT_EQ(os.str(), "(0x12)");

}



TEST_F(Nikon3MakerNoteTest_498, FlashGroupBCControlDataTypeNotUnsignedByte_498) {

    Value invalidValue(TypeId::asciiString);  // Invalid type

    Exifdatum exifDatum(ExifKey("Exif.NikonFl7.FlashGroupBCControlData"), &invalidValue);

    metadata.add(exifDatum.key(), &exifDatum.value());

    nikonMakerNote.printFlashGroupCDataFl7(os, value, &metadata);

    EXPECT_EQ(os.str(), "(0x12)");

}



TEST_F(Nikon3MakerNoteTest_498, FlashModeZero_498) {

    value.setValue(0x10);  // Flash mode is zero

    nikonMakerNote.printFlashGroupCDataFl7(os, value, &metadata);

    EXPECT_EQ(os.str(), "n/a");

}



TEST_F(Nikon3MakerNoteTest_498, FlashModeNonZero_498) {

    value.setValue(0x1F);  // Flash mode is non-zero

    nikonMakerNote.printFlashGroupCDataFl7(os, value, &metadata);

    EXPECT_EQ(os.str(), "n/a");  // Assuming printFlashCompensationValue returns "n/a" for test purposes

}
