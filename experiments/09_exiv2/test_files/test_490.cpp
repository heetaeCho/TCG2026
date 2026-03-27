#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "nikonmn_int.hpp"

#include "exif.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class Nikon3MakerNoteTest_490 : public ::testing::Test {

protected:

    Value value;

    ExifData metadata;

    std::ostringstream os;



    Nikon3MakerNoteTest_490() : value(unsignedByte) {}



    void addMetadataEntry(const std::string& key, const Value& value) {

        Exiv2::Exifdatum exifdatum(Exiv2::ExifKey(key), &value);

        metadata.add(exifdatum);

    }

};



TEST_F(Nikon3MakerNoteTest_490, InvalidValueCount_490) {

    addMetadataEntry("Exif.NikonFl7.ExternalFlashData2", Value(unsignedByte));

    os.str("");

    value.setValue(nullptr);

    Nikon3MakerNote::printFlashMasterDataFl7(os, value, &metadata);

    EXPECT_EQ(os.str(), "(X)");

}



TEST_F(Nikon3MakerNoteTest_490, InvalidValueType_490) {

    addMetadataEntry("Exif.NikonFl7.ExternalFlashData2", Value(unsignedByte));

    os.str("");

    value.setValue(nullptr);

    value = Value(asciiString);

    Nikon3MakerNote::printFlashMasterDataFl7(os, value, &metadata);

    EXPECT_EQ(os.str(), "(X)");

}



TEST_F(Nikon3MakerNoteTest_490, NullMetadata_490) {

    os.str("");

    value.setValue(nullptr);

    Nikon3MakerNote::printFlashMasterDataFl7(os, value, nullptr);

    EXPECT_EQ(os.str(), "(X)");

}



TEST_F(Nikon3MakerNoteTest_490, MissingExternalFlashData2_490) {

    os.str("");

    value = Value(unsignedByte);

    Nikon3MakerNote::printFlashMasterDataFl7(os, value, &metadata);

    EXPECT_EQ(os.str(), "(X)");

}



TEST_F(Nikon3MakerNoteTest_490, InvalidExternalFlashData2Count_490) {

    addMetadataEntry("Exif.NikonFl7.ExternalFlashData2", Value(unsignedByte));

    metadata.findKey(Exiv2::ExifKey("Exif.NikonFl7.ExternalFlashData2"))->setValue(nullptr);

    os.str("");

    Nikon3MakerNote::printFlashMasterDataFl7(os, value, &metadata);

    EXPECT_EQ(os.str(), "(X)");

}



TEST_F(Nikon3MakerNoteTest_490, InvalidExternalFlashData2Type_490) {

    addMetadataEntry("Exif.NikonFl7.ExternalFlashData2", Value(asciiString));

    os.str("");

    Nikon3MakerNote::printFlashMasterDataFl7(os, value, &metadata);

    EXPECT_EQ(os.str(), "(X)");

}



TEST_F(Nikon3MakerNoteTest_490, FlashModeZero_490) {

    addMetadataEntry("Exif.NikonFl7.ExternalFlashData2", Value(unsignedByte));

    metadata.findKey(Exiv2::ExifKey("Exif.NikonFl7.ExternalFlashData2"))->setValue(&value);

    value = Value(unsignedByte);

    os.str("");

    Nikon3MakerNote::printFlashMasterDataFl7(os, value, &metadata);

    EXPECT_EQ(os.str(), "n/a");

}



TEST_F(Nikon3MakerNoteTest_490, FlashModeNonZero_490) {

    addMetadataEntry("Exif.NikonFl7.ExternalFlashData2", Value(unsignedByte));

    metadata.findKey(Exiv2::ExifKey("Exif.NikonFl7.ExternalFlashData2"))->setValue(&value);

    value.setValue(static_cast<uint8_t>(15)); // Flash mode 0xF

    os.str("");

    Nikon3MakerNote::printFlashMasterDataFl7(os, value, &metadata);

    EXPECT_EQ(os.str(), "X"); // Assuming printFlashCompensationValue returns "X" for test purpose

}
