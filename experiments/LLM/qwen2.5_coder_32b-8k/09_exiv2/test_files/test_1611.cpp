#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include <exiv2/value.hpp>

#include <exiv2/exif.hpp>

#include "sonymn_int.hpp"



namespace Exiv2 {

    namespace Internal {

        class SonyMakerNoteTest : public ::testing::Test {

        protected:

            std::ostringstream os;

            Value value;

            const ExifData* metadata = nullptr;

            TagDetails sonyFocusMode3[5] = {{0, "Manual"}, {2, "AF-S"}, {3, "AF-C"}, {5, "Semi-manual"}, {6, "DMF"}};



            SonyMakerNoteTest() : value(unsignedShort) {}

        };



        TEST_F(SonyMakerNoteTest_1611, ValueCountNotOne_ReturnsEncodedValue_1611) {

            Value valueWithMultipleCount(unsignedShort);

            valueWithMultipleCount.setDataArea(reinterpret_cast<const byte*>(&sonyFocusMode3), sizeof(sonyFocusMode3));

            os.str("");

            SonyMakerNote::printFocusMode3(os, valueWithMultipleCount, metadata);

            EXPECT_EQ(os.str(), "(0)");

        }



        TEST_F(SonyMakerNoteTest_1611, ValueTypeNotUnsignedShort_ReturnsEncodedValue_1611) {

            Value wrongTypeValue(unsignedByte);

            os.str("");

            SonyMakerNote::printFocusMode3(os, wrongTypeValue, metadata);

            EXPECT_EQ(os.str(), "(0)");

        }



        TEST_F(SonyMakerNoteTest_1611, MetadataIsNull_ReturnsEncodedValue_1611) {

            value.setDataArea(reinterpret_cast<const byte*>(&sonyFocusMode3[0]), sizeof(sonyFocusMode3[0]));

            os.str("");

            SonyMakerNote::printFocusMode3(os, value, nullptr);

            EXPECT_EQ(os.str(), "(0)");

        }



        TEST_F(SonyMakerNoteTest_1611, MetadataVersionNotExpected_ReturnsNAN_1611) {

            ExifData exifData;

            std::string metaVersion = "WrongVersion";

            exifData.add(ExifKey("Exif.Image.ProcessingSoftware"), Value::create(string));

            exifData["Exif.Image.ProcessingSoftware"].setDataArea(reinterpret_cast<const byte*>(metaVersion.c_str()), metaVersion.size());



            value.setDataArea(reinterpret_cast<const byte*>(&sonyFocusMode3[0]), sizeof(sonyFocusMode3[0]));

            os.str("");

            SonyMakerNote::printFocusMode3(os, value, &exifData);

            EXPECT_EQ(os.str(), "n/a");

        }



        TEST_F(SonyMakerNoteTest_1611, MetadataVersionExpected_ReturnsCorrectFocusMode_1611) {

            ExifData exifData;

            std::string metaVersion = "DC7303320222000";

            exifData.add(ExifKey("Exif.Image.ProcessingSoftware"), Value::create(string));

            exifData["Exif.Image.ProcessingSoftware"].setDataArea(reinterpret_cast<const byte*>(metaVersion.c_str()), metaVersion.size());



            uint16_t focusModeValue = 3;

            value.setDataArea(reinterpret_cast<const byte*>(&focusModeValue), sizeof(focusModeValue));

            os.str("");

            SonyMakerNote::printFocusMode3(os, value, &exifData);

            EXPECT_EQ(os.str(), "AF-C");

        }



        TEST_F(SonyMakerNoteTest_1611, FocusModeValueNotInTagList_ReturnsEncodedValue_1611) {

            ExifData exifData;

            std::string metaVersion = "DC7303320222000";

            exifData.add(ExifKey("Exif.Image.ProcessingSoftware"), Value::create(string));

            exifData["Exif.Image.ProcessingSoftware"].setDataArea(reinterpret_cast<const byte*>(metaVersion.c_str()), metaVersion.size());



            uint16_t focusModeValue = 99;

            value.setDataArea(reinterpret_cast<const byte*>(&focusModeValue), sizeof(focusModeValue));

            os.str("");

            SonyMakerNote::printFocusMode3(os, value, &exifData);

            EXPECT_EQ(os.str(), "(99)");

        }



    } // namespace Internal

} // namespace Exiv2
