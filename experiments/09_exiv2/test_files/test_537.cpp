#include <gtest/gtest.h>

#include "exiv2/exif.hpp"

#include "TestProjects/exiv2/src/easyaccess.cpp"



namespace Exiv2 {

    class SerialNumberTest_537 : public ::testing::Test {

    protected:

        void SetUp() override {

            exifData.clear();

        }



        ExifData exifData;

    };



    TEST_F(SerialNumberTest_537, NormalOperationWithCanonSerialNumber_537) {

        const char* key = "Exif.Canon.SerialNumber";

        const std::string value = "1234567890";

        exifData.add(ExifKey(key), new AsciiValue(value));

        ExifData::const_iterator it = serialNumber(exifData);

        ASSERT_NE(it, exifData.end());

        EXPECT_EQ(it->key(), key);

        EXPECT_EQ(it->value()->toString(), value);

    }



    TEST_F(SerialNumberTest_537, NormalOperationWithNikonSerialNumber_537) {

        const char* key = "Exif.Nikon3.SerialNumber";

        const std::string value = "0987654321";

        exifData.add(ExifKey(key), new AsciiValue(value));

        ExifData::const_iterator it = serialNumber(exifData);

        ASSERT_NE(it, exifData.end());

        EXPECT_EQ(it->key(), key);

        EXPECT_EQ(it->value()->toString(), value);

    }



    TEST_F(SerialNumberTest_537, BoundaryConditionWithEmptyExifData_537) {

        ExifData::const_iterator it = serialNumber(exifData);

        EXPECT_EQ(it, exifData.end());

    }



    TEST_F(SerialNumberTest_537, ExceptionalCaseWithInvalidKey_537) {

        const char* key = "Exif.Invalid.SerialNumber";

        const std::string value = "1234567890";

        exifData.add(ExifKey(key), new AsciiValue(value));

        ExifData::const_iterator it = serialNumber(exifData);

        EXPECT_EQ(it, exifData.end());

    }



    TEST_F(SerialNumberTest_537, MultiplePossibleKeysWithFirstMatched_537) {

        const char* key1 = "Exif.Canon.SerialNumber";

        const std::string value1 = "1234567890";

        exifData.add(ExifKey(key1), new AsciiValue(value1));



        const char* key2 = "Exif.Nikon3.SerialNumber";

        const std::string value2 = "0987654321";

        exifData.add(ExifKey(key2), new AsciiValue(value2));



        ExifData::const_iterator it = serialNumber(exifData);

        ASSERT_NE(it, exifData.end());

        EXPECT_EQ(it->key(), key1);

        EXPECT_EQ(it->value()->toString(), value1);

    }

}
