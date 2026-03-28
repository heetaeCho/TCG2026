#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"

#include "./TestProjects/exiv2/src/nikonmn_int.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class Nikon3MakerNoteTest_495 : public ::testing::Test {

protected:

    std::ostringstream os;

    Value value;

    ExifData metadata;

};



TEST_F(Nikon3MakerNoteTest_495, InvalidValueCount_495) {

    Value invalidValue(unsignedByte);

    invalidValue.read(reinterpret_cast<const byte*>("\x01\x02"), 2, littleEndian);



    Nikon3MakerNote::printFlashGroupBDataFl6(os, invalidValue, &metadata);

    EXPECT_EQ(os.str(), "(1 2)");

}



TEST_F(Nikon3MakerNoteTest_495, InvalidValueType_495) {

    Value invalidValue(asciiString); // Wrong type

    invalidValue.read(reinterpret_cast<const byte*>("AB"), 2);



    Nikon3MakerNote::printFlashGroupBDataFl6(os, invalidValue, &metadata);

    EXPECT_EQ(os.str(), "(AB)");

}



TEST_F(Nikon3MakerNoteTest_495, NullMetadata_495) {

    Value validValue(unsignedByte);

    validValue.read(reinterpret_cast<const byte*>("\x01"), 1, littleEndian);



    Nikon3MakerNote::printFlashGroupBDataFl6(os, validValue, nullptr);

    EXPECT_EQ(os.str(), "(1)");

}



TEST_F(Nikon3MakerNoteTest_495, MissingFlashGroupBCControlData_495) {

    Value validValue(unsignedByte);

    validValue.read(reinterpret_cast<const byte*>("\x01"), 1, littleEndian);



    Nikon3MakerNote::printFlashGroupBDataFl6(os, validValue, &metadata);

    EXPECT_EQ(os.str(), "(1)");

}



TEST_F(Nikon3MakerNoteTest_495, InvalidFlashGroupBCControlDataCount_495) {

    Value validValue(unsignedByte);

    validValue.read(reinterpret_cast<const byte*>("\x01"), 1, littleEndian);



    Exifdatum exifDatum(ExifKey("Exif.NikonFl6.FlashGroupBCControlData"), new UShortValue);

    metadata.add(exifDatum);



    Nikon3MakerNote::printFlashGroupBDataFl6(os, validValue, &metadata);

    EXPECT_EQ(os.str(), "(1)");

}



TEST_F(Nikon3MakerNoteTest_495, InvalidFlashGroupBCControlDataType_495) {

    Value validValue(unsignedByte);

    validValue.read(reinterpret_cast<const byte*>("\x01"), 1, littleEndian);



    Exifdatum exifDatum(ExifKey("Exif.NikonFl6.FlashGroupBCControlData"), new AsciiString); // Wrong type

    metadata.add(exifDatum);



    Nikon3MakerNote::printFlashGroupBDataFl6(os, validValue, &metadata);

    EXPECT_EQ(os.str(), "(1)");

}



TEST_F(Nikon3MakerNoteTest_495, FlashModeUsesManualScaleFalse_495) {

    Value validValue(unsignedByte);

    validValue.read(reinterpret_cast<const byte*>("\x01"), 1, littleEndian);



    UShortValue* bcControlData = new UShortValue;

    bcControlData->read(reinterpret_cast<const byte*>("\x0F\x00"), 2, littleEndian); // mode is 0

    Exifdatum exifDatum(ExifKey("Exif.NikonFl6.FlashGroupBCControlData"), bcControlData);

    metadata.add(exifDatum);



    Nikon3MakerNote::printFlashGroupBDataFl6(os, validValue, &metadata);

    EXPECT_EQ(os.str(), "n/a");

}



TEST_F(Nikon3MakerNoteTest_495, FlashModeUsesManualScaleTrue_495) {

    Value validValue(unsignedByte);

    validValue.read(reinterpret_cast<const byte*>("\x01"), 1, littleEndian);



    UShortValue* bcControlData = new UShortValue;

    bcControlData->read(reinterpret_cast<const byte*>("\xF0\x00"), 2, littleEndian); // mode is 15

    Exifdatum exifDatum(ExifKey("Exif.NikonFl6.FlashGroupBCControlData"), bcControlData);

    metadata.add(exifDatum);



    Nikon3MakerNote::printFlashGroupBDataFl6(os, validValue, &metadata);

    EXPECT_EQ(os.str(), "n/a"); // Assuming printFlashCompensationValue returns n/a for this test

}
