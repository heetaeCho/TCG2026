#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"

#include "./TestProjects/exiv2/src/sonymn_int.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class SonyMakerNoteTest_1595 : public ::testing::Test {

protected:

    SonyMakerNote sonyMakerNote_;

    Value value_;

    std::ostringstream oss_;

};



TEST_F(SonyMakerNoteTest_1595, NormalOperationWithKnownModel_1595) {

    ExifData metadata;

    metadata.add(ExifKey("Exif.Image.Model"), Value::create(unsignedShort));

    metadata["Exif.Image.Model"] = "ILCE-7M4";



    value_.setValueType(unsignedShort);

    value_.setDataArea(reinterpret_cast<const byte*>(&std::array<uint16_t, 2>{100, 200}), sizeof(std::array<uint16_t, 2>));



    sonyMakerNote_.printFlexibleSpotPosition(oss_, value_, &metadata);



    EXPECT_EQ(oss_.str(), "100, 200");

}



TEST_F(SonyMakerNoteTest_1595, NormalOperationWithUnknownModel_1595) {

    ExifData metadata;

    metadata.add(ExifKey("Exif.Image.Model"), Value::create(unsignedShort));

    metadata["Exif.Image.Model"] = "UNKNOWN_MODEL";



    value_.setValueType(unsignedShort);

    value_.setDataArea(reinterpret_cast<const byte*>(&std::array<uint16_t, 2>{100, 200}), sizeof(std::array<uint16_t, 2>));



    sonyMakerNote_.printFlexibleSpotPosition(oss_, value_, &metadata);



    EXPECT_EQ(oss_.str(), "n/a");

}



TEST_F(SonyMakerNoteTest_1595, BoundaryConditionWithZeroCount_1595) {

    ExifData metadata;

    metadata.add(ExifKey("Exif.Image.Model"), Value::create(unsignedShort));

    metadata["Exif.Image.Model"] = "ILCE-7M4";



    value_.setValueType(unsignedShort);

    value_.setDataArea(reinterpret_cast<const byte*>(&std::array<uint16_t, 0>{}), sizeof(std::array<uint16_t, 0>));



    sonyMakerNote_.printFlexibleSpotPosition(oss_, value_, &metadata);



    EXPECT_EQ(oss_.str(), "(Value())");

}



TEST_F(SonyMakerNoteTest_1595, BoundaryConditionWithMoreThanTwoCount_1595) {

    ExifData metadata;

    metadata.add(ExifKey("Exif.Image.Model"), Value::create(unsignedShort));

    metadata["Exif.Image.Model"] = "ILCE-7M4";



    value_.setValueType(unsignedShort);

    std::array<uint16_t, 3> data = {100, 200, 300};

    value_.setDataArea(reinterpret_cast<const byte*>(data.data()), sizeof(data));



    sonyMakerNote_.printFlexibleSpotPosition(oss_, value_, &metadata);



    EXPECT_EQ(oss_.str(), "(Value())");

}



TEST_F(SonyMakerNoteTest_1595, BoundaryConditionWithIncorrectType_1595) {

    ExifData metadata;

    metadata.add(ExifKey("Exif.Image.Model"), Value::create(unsignedShort));

    metadata["Exif.Image.Model"] = "ILCE-7M4";



    value_.setValueType(signedByte);

    std::array<int8_t, 2> data = {100, 200};

    value_.setDataArea(reinterpret_cast<const byte*>(data.data()), sizeof(data));



    sonyMakerNote_.printFlexibleSpotPosition(oss_, value_, &metadata);



    EXPECT_EQ(oss_.str(), "(Value())");

}



TEST_F(SonyMakerNoteTest_1595, ExceptionalCaseWithNullMetadata_1595) {

    ExifData* metadata = nullptr;



    value_.setValueType(unsignedShort);

    std::array<uint16_t, 2> data = {100, 200};

    value_.setDataArea(reinterpret_cast<const byte*>(data.data()), sizeof(data));



    sonyMakerNote_.printFlexibleSpotPosition(oss_, value_, metadata);



    EXPECT_EQ(oss_.str(), "(Value())");

}
