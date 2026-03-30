#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "TestProjects/exiv2/src/easyaccess.cpp"



using namespace Exiv2;



class EasyAccessTest_533 : public ::testing::Test {

protected:

    ExifData ed;

};



TEST_F(EasyAccessTest_533, MaxApertureValue_ReturnsValidIteratorWhenKeyExists_533) {

    const char* key = "Exif.Photo.MaxApertureValue";

    Exifdatum exifDatum(key);

    ed.add(exifDatum);



    auto it = maxApertureValue(ed);

    EXPECT_NE(it, ed.end());

    EXPECT_EQ(it->key(), key);

}



TEST_F(EasyAccessTest_533, MaxApertureValue_ReturnsEndIteratorWhenNoKeysExist_533) {

    auto it = maxApertureValue(ed);

    EXPECT_EQ(it, ed.end());

}



TEST_F(EasyAccessTest_533, MaxApertureValue_ReturnsValidIteratorForFirstMatchingKey_533) {

    const char* key1 = "Exif.Image.MaxApertureValue";

    const char* key2 = "Exif.Photo.MaxApertureValue";

    Exifdatum exifDatum1(key1);

    Exifdatum exifDatum2(key2);

    ed.add(exifDatum1);

    ed.add(exifDatum2);



    auto it = maxApertureValue(ed);

    EXPECT_NE(it, ed.end());

    EXPECT_EQ(it->key(), key1);

}



TEST_F(EasyAccessTest_533, MaxApertureValue_ReturnsValidIteratorForLastMatchingKeyWhenOthersAreMissing_533) {

    const char* key = "Exif.NikonLd4.MaxAperture";

    Exifdatum exifDatum(key);

    ed.add(exifDatum);



    auto it = maxApertureValue(ed);

    EXPECT_NE(it, ed.end());

    EXPECT_EQ(it->key(), key);

}



TEST_F(EasyAccessTest_533, MaxApertureValue_IgnoresNonMatchingKeys_533) {

    const char* nonMatchingKey = "Exif.Photo.SomeOtherTag";

    Exifdatum exifDatum(nonMatchingKey);

    ed.add(exifDatum);



    auto it = maxApertureValue(ed);

    EXPECT_EQ(it, ed.end());

}
