#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"

#include "./TestProjects/exiv2/src/sonymn_int.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class SonyMakerNoteTest_1613 : public ::testing::Test {

protected:

    SonyMakerNote sonyMakerNote;

    Value value;

    ExifData metadata;

};



TEST_F(SonyMakerNoteTest_1613, PrintSony2FpAmbientTemperature_NormalOperation_1613) {

    std::ostringstream os;

    value = Value(TypeId::int32);

    value.setDataArea(reinterpret_cast<const byte*>(&static_cast<int32_t>(30)), sizeof(int32_t));

    metadata.add(ExifKey("Exif.Sony2Fp.0x0002"), &value);



    sonyMakerNote.printSony2FpAmbientTemperature(os, value, &metadata);

    EXPECT_EQ(os.str(), "30 °C");

}



TEST_F(SonyMakerNoteTest_1613, PrintSony2FpAmbientTemperature_MetadataNull_1613) {

    std::ostringstream os;

    sonyMakerNote.printSony2FpAmbientTemperature(os, value, nullptr);

    EXPECT_EQ(os.str(), "(Value())");

}



TEST_F(SonyMakerNoteTest_1613, PrintSony2FpAmbientTemperature_ValueCountNotOne_1613) {

    std::ostringstream os;

    value = Value(TypeId::int32);

    value.setDataArea(reinterpret_cast<const byte*>(&static_cast<int32_t>(30)), sizeof(int32_t));

    metadata.add(ExifKey("Exif.Sony2Fp.0x0002"), &value);



    value = Value(TypeId::int32); // Changing value to have count not one

    sonyMakerNote.printSony2FpAmbientTemperature(os, value, &metadata);

    EXPECT_EQ(os.str(), "(Value())");

}



TEST_F(SonyMakerNoteTest_1613, PrintSony2FpAmbientTemperature_MetadataKeyNotFound_1613) {

    std::ostringstream os;

    value = Value(TypeId::int32);

    value.setDataArea(reinterpret_cast<const byte*>(&static_cast<int32_t>(30)), sizeof(int32_t));



    sonyMakerNote.printSony2FpAmbientTemperature(os, value, &metadata);

    EXPECT_EQ(os.str(), "n/a");

}



TEST_F(SonyMakerNoteTest_1613, PrintSony2FpAmbientTemperature_MetadataKeyValueNotOne_1613) {

    std::ostringstream os;

    value = Value(TypeId::int32);

    value.setDataArea(reinterpret_cast<const byte*>(&static_cast<int32_t>(30)), sizeof(int32_t));

    metadata.add(ExifKey("Exif.Sony2Fp.0x0002"), &value);



    Exifdatum& exifDatum = metadata["Exif.Sony2Fp.0x0002"];

    exifDatum.setValue(&static_cast<int32_t>(500), sizeof(int32_t));



    sonyMakerNote.printSony2FpAmbientTemperature(os, value, &metadata);

    EXPECT_EQ(os.str(), "n/a");

}



TEST_F(SonyMakerNoteTest_1613, PrintSony2FpAmbientTemperature_MetadataKeyValueNot255_1613) {

    std::ostringstream os;

    value = Value(TypeId::int32);

    value.setDataArea(reinterpret_cast<const byte*>(&static_cast<int32_t>(30)), sizeof(int32_t));

    metadata.add(ExifKey("Exif.Sony2Fp.0x0002"), &value);



    Exifdatum& exifDatum = metadata["Exif.Sony2Fp.0x0002"];

    exifDatum.setValue(&static_cast<int32_t>(1), sizeof(int32_t));



    sonyMakerNote.printSony2FpAmbientTemperature(os, value, &metadata);

    EXPECT_EQ(os.str(), "n/a");

}
