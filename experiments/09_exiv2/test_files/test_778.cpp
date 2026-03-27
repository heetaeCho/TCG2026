#include <gtest/gtest.h>

#include "exiv2/exif.hpp"

#include "exiv2/tags.hpp"



using namespace Exiv2;



class ExifDataTest_778 : public ::testing::Test {

protected:

    ExifData exifData;

};



TEST_F(ExifDataTest_778, FindKey_ReturnsEndWhenNotFound_778) {

    ExifKey key("NonexistentTag");

    EXPECT_EQ(exifData.findKey(key), exifData.end());

}



TEST_F(ExifDataTest_778, FindKey_ReturnsIteratorWhenFound_778) {

    ExifKey key("ExistingTag");

    Exifdatum exifDatum;

    exifData.add(key, &exifDatum);

    EXPECT_NE(exifData.findKey(key), exifData.end());

}



TEST_F(ExifDataTest_778, FindKey_DoesNotModifyData_778) {

    size_t initialCount = exifData.count();

    ExifKey key("SomeTag");

    exifData.findKey(key);

    EXPECT_EQ(exifData.count(), initialCount);

}



TEST_F(ExifDataTest_778, Add_IncreasesCount_778) {

    size_t initialCount = exifData.count();

    ExifKey key("NewTag");

    Exifdatum exifDatum;

    exifData.add(key, &exifDatum);

    EXPECT_EQ(exifData.count(), initialCount + 1);

}



TEST_F(ExifDataTest_778, Add_DoesNotIncreaseCountWhenDuplicate_778) {

    size_t initialCount = exifData.count();

    ExifKey key("DuplicateTag");

    Exifdatum exifDatum;

    exifData.add(key, &exifDatum);

    exifData.add(key, &exifDatum);

    EXPECT_EQ(exifData.count(), initialCount + 1);

}



TEST_F(ExifDataTest_778, Clear_ResetsCount_778) {

    ExifKey key("TagToAdd");

    Exifdatum exifDatum;

    exifData.add(key, &exifDatum);

    exifData.clear();

    EXPECT_EQ(exifData.count(), 0);

}



TEST_F(ExifDataTest_778, Erase_SingleElement_DecreasesCount_778) {

    ExifKey key("TagToRemove");

    Exifdatum exifDatum;

    exifData.add(key, &exifDatum);

    size_t initialCount = exifData.count();

    exifData.erase(exifData.findKey(key));

    EXPECT_EQ(exifData.count(), initialCount - 1);

}



TEST_F(ExifDataTest_778, Erase_Range_DecreasesCount_778) {

    ExifKey key1("TagToRemove1");

    ExifKey key2("TagToRemove2");

    Exifdatum exifDatum1;

    Exifdatum exifDatum2;

    exifData.add(key1, &exifDatum1);

    exifData.add(key2, &exifDatum2);

    size_t initialCount = exifData.count();

    exifData.erase(exifData.begin(), exifData.end());

    EXPECT_EQ(exifData.count(), initialCount - 2);

}



TEST_F(ExifDataTest_778, Empty_ReturnsTrueWhenNoElements_778) {

    EXPECT_TRUE(exifData.empty());

}



TEST_F(ExifDataTest_778, Empty_ReturnsFalseWhenElementsPresent_778) {

    ExifKey key("Tag");

    Exifdatum exifDatum;

    exifData.add(key, &exifDatum);

    EXPECT_FALSE(exifData.empty());

}
