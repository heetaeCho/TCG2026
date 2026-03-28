#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"

#include "./TestProjects/exiv2/src/nikonmn_int.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class Nikon3MakerNoteTest_494 : public ::testing::Test {

protected:

    Value value;

    ExifData metadata;

};



TEST_F(Nikon3MakerNoteTest_494, InvalidValueCount_494) {

    std::ostringstream os;

    value.setValue("dummy");

    EXPECT_EQ(&os, &Nikon3MakerNote::printFlashGroupADataFl7(os, value, &metadata));

    EXPECT_EQ("(dummy)", os.str());

}



TEST_F(Nikon3MakerNoteTest_494, InvalidValueType_494) {

    std::ostringstream os;

    Value intValue(TypeId::unsignedShort);

    intValue.setValue("123");

    EXPECT_EQ(&os, &Nikon3MakerNote::printFlashGroupADataFl7(os, intValue, &metadata));

    EXPECT_EQ("(123)", os.str());

}



TEST_F(Nikon3MakerNoteTest_494, NullMetadata_494) {

    std::ostringstream os;

    value.setValue("dummy");

    EXPECT_EQ(&os, &Nikon3MakerNote::printFlashGroupADataFl7(os, value, nullptr));

    EXPECT_EQ("(dummy)", os.str());

}



TEST_F(Nikon3MakerNoteTest_494, MetadataKeyNotFound_494) {

    std::ostringstream os;

    value.setValue("dummy");

    EXPECT_EQ(&os, &Nikon3MakerNote::printFlashGroupADataFl7(os, value, &metadata));

    EXPECT_EQ("(dummy)", os.str());

}



TEST_F(Nikon3MakerNoteTest_494, InvalidMetadataValueType_494) {

    std::ostringstream os;

    metadata.add(ExifKey("Exif.NikonFl7.FlashGroupAControlData"), Value::create(TypeId::unsignedShort));

    value.setValue("dummy");

    EXPECT_EQ(&os, &Nikon3MakerNote::printFlashGroupADataFl7(os, value, &metadata));

    EXPECT_EQ("(dummy)", os.str());

}



TEST_F(Nikon3MakerNoteTest_494, FlashModeZero_494) {

    std::ostringstream os;

    metadata.add(ExifKey("Exif.NikonFl7.FlashGroupAControlData"), Value::create(TypeId::unsignedByte));

    metadata["Exif.NikonFl7.FlashGroupAControlData"] = 0x10; // mode is 0

    value.setValue("\x00"); // FlashGroupAData

    EXPECT_EQ(&os, &Nikon3MakerNote::printFlashGroupADataFl7(os, value, &metadata));

    EXPECT_EQ("n/a", os.str());

}



TEST_F(Nikon3MakerNoteTest_494, NormalOperation_494) {

    std::ostringstream os;

    metadata.add(ExifKey("Exif.NikonFl7.FlashGroupAControlData"), Value::create(TypeId::unsignedByte));

    metadata["Exif.NikonFl7.FlashGroupAControlData"] = 0x11; // mode is 1

    value.setValue("\x02"); // FlashGroupAData, assuming printFlashCompensationValue returns "2"

    EXPECT_EQ(&os, &Nikon3MakerNote::printFlashGroupADataFl7(os, value, &metadata));

    EXPECT_EQ("2", os.str()); // Assuming printFlashCompensationValue converts 2 to "2" for mode 1

}
