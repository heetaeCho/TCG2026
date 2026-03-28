#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <exiv2/exif.hpp>

#include <exiv2/value.hpp>

#include "./TestProjects/exiv2/src/sonymn_int.cpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class SonyMakerNoteTest_1621 : public ::testing::Test {

protected:

    Value value;

    ExifData metadata;

    std::ostringstream os;



    void SetUp() override {

        value = Value(unsignedByte);

    }



    bool getModel(const ExifData* metadata, std::string& model) {

        auto it = metadata->findKey(ExifKey("Exif.Image.Model"));

        if (it != metadata.end()) {

            model = it->value().toString();

            return true;

        }

        return false;

    }



    void setModel(const std::string& model) {

        Exiv2::Value::AutoPtr modelValue = Value::create(unsignedByte);

        modelValue->read(model.data(), model.size());

        metadata["Exif.Image.Model"] = *modelValue;

    }

};



TEST_F(SonyMakerNoteTest_1621, NormalOperation_ILCE_1_1621) {

    setModel("ILCE-1");

    value.setDataArea(reinterpret_cast<const byte*>(&uint8_t(1)), 1);

    SonyMakerNote::printSonyMisc3cQuality2(os, value, &metadata);

    EXPECT_EQ(os.str(), "JPEG");

}



TEST_F(SonyMakerNoteTest_1621, NormalOperation_ILCE_7M4_2_1621) {

    setModel("ILCE-7M4");

    value.setDataArea(reinterpret_cast<const byte*>(&uint8_t(2)), 1);

    SonyMakerNote::printSonyMisc3cQuality2(os, value, &metadata);

    EXPECT_EQ(os.str(), "Raw");

}



TEST_F(SonyMakerNoteTest_1621, NormalOperation_ILCE_7RM5_3_1621) {

    setModel("ILCE-7RM5");

    value.setDataArea(reinterpret_cast<const byte*>(&uint8_t(3)), 1);

    SonyMakerNote::printSonyMisc3cQuality2(os, value, &metadata);

    EXPECT_EQ(os.str(), "Raw + JPEG");

}



TEST_F(SonyMakerNoteTest_1621, NormalOperation_ILCE_7SM3_4_1621) {

    setModel("ILCE-7SM3");

    value.setDataArea(reinterpret_cast<const byte*>(&uint8_t(4)), 1);

    SonyMakerNote::printSonyMisc3cQuality2(os, value, &metadata);

    EXPECT_EQ(os.str(), "HEIF");

}



TEST_F(SonyMakerNoteTest_1621, NormalOperation_ILME_FX3_6_1621) {

    setModel("ILME-FX3");

    value.setDataArea(reinterpret_cast<const byte*>(&uint8_t(6)), 1);

    SonyMakerNote::printSonyMisc3cQuality2(os, value, &metadata);

    EXPECT_EQ(os.str(), "Raw + HEIF");

}



TEST_F(SonyMakerNoteTest_1621, UnknownModel_0_1621) {

    setModel("UnknownModel");

    value.setDataArea(reinterpret_cast<const byte*>(&uint8_t(0)), 1);

    SonyMakerNote::printSonyMisc3cQuality2(os, value, &metadata);

    EXPECT_EQ(os.str(), "JPEG");

}



TEST_F(SonyMakerNoteTest_1621, UnknownModel_1_1621) {

    setModel("UnknownModel");

    value.setDataArea(reinterpret_cast<const byte*>(&uint8_t(1)), 1);

    SonyMakerNote::printSonyMisc3cQuality2(os, value, &metadata);

    EXPECT_EQ(os.str(), "Raw");

}



TEST_F(SonyMakerNoteTest_1621, UnknownModel_2_1621) {

    setModel("UnknownModel");

    value.setDataArea(reinterpret_cast<const byte*>(&uint8_t(2)), 1);

    SonyMakerNote::printSonyMisc3cQuality2(os, value, &metadata);

    EXPECT_EQ(os.str(), "Raw + JPEG");

}



TEST_F(SonyMakerNoteTest_1621, UnknownModel_3_1621) {

    setModel("UnknownModel");

    value.setDataArea(reinterpret_cast<const byte*>(&uint8_t(3)), 1);

    SonyMakerNote::printSonyMisc3cQuality2(os, value, &metadata);

    EXPECT_EQ(os.str(), "Raw + MPO");

}



TEST_F(SonyMakerNoteTest_1621, InvalidValueCount_1621) {

    value.setDataArea(reinterpret_cast<const byte*>(&uint8_t(0)), 2); // count != 1

    SonyMakerNote::printSonyMisc3cQuality2(os, value, &metadata);

    EXPECT_EQ(os.str(), "()()");

}



TEST_F(SonyMakerNoteTest_1621, InvalidValueType_1621) {

    Value invalidValue(asciiString);

    invalidValue.setDataArea(reinterpret_cast<const byte*>("0"), 1); // type != unsignedByte

    SonyMakerNote::printSonyMisc3cQuality2(os, invalidValue, &metadata);

    EXPECT_EQ(os.str(), "()()");

}



TEST_F(SonyMakerNoteTest_1621, NullMetadata_1621) {

    value.setDataArea(reinterpret_cast<const byte*>(&uint8_t(0)), 1);

    SonyMakerNote::printSonyMisc3cQuality2(os, value, nullptr); // metadata == nullptr

    EXPECT_EQ(os.str(), "()()");

}



TEST_F(SonyMakerNoteTest_1621, NoModelInMetadata_1621) {

    value.setDataArea(reinterpret_cast<const byte*>(&uint8_t(0)), 1);

    SonyMakerNote::printSonyMisc3cQuality2(os, value, &metadata); // no model in metadata

    EXPECT_EQ(os.str(), "()()");

}
