#include <gtest/gtest.h>

#include "exiv2/exif.hpp"



using namespace Exiv2;



class ExifDataTest_775 : public ::testing::Test {

protected:

    ExifData exifData;

};



TEST_F(ExifDataTest_775, OperatorBracket_AddsNewKey_775) {

    std::string key = "Exif.Image.Artist";

    Exifdatum& exifDatum = exifData[key];

    EXPECT_EQ(exifDatum.key(), key);

}



TEST_F(ExifDataTest_775, OperatorBracket_ReturnsExistingKey_775) {

    std::string key = "Exif.Image.Artist";

    Exifdatum& exifDatum1 = exifData[key];

    Exifdatum& exifDatum2 = exifData[key];

    EXPECT_EQ(&exifDatum1, &exifDatum2);

}



TEST_F(ExifDataTest_775, AddByKeyAndValue_IncreasesCount_775) {

    size_t initialCount = exifData.count();

    ExifKey key("Exif.Image.Artist");

    Value* pValue = new StringValue("ArtistName");

    exifData.add(key, pValue);

    EXPECT_EQ(exifData.count(), initialCount + 1);

}



TEST_F(ExifDataTest_775, AddByExifdatum_IncreasesCount_775) {

    size_t initialCount = exifData.count();

    ExifKey key("Exif.Image.Artist");

    Value* pValue = new StringValue("ArtistName");

    Exifdatum exifDatum(key, pValue);

    exifData.add(exifDatum);

    EXPECT_EQ(exifData.count(), initialCount + 1);

}



TEST_F(ExifDataTest_775, Clear_ResetsCountToZero_775) {

    ExifKey key("Exif.Image.Artist");

    Value* pValue = new StringValue("ArtistName");

    exifData.add(key, pValue);

    exifData.clear();

    EXPECT_EQ(exifData.count(), 0);

}



TEST_F(ExifDataTest_775, SortByKey_DoesNotChangeCount_775) {

    ExifKey key1("Exif.Image.Artist");

    Value* pValue1 = new StringValue("ArtistName");

    exifData.add(key1, pValue1);



    ExifKey key2("Exif.Image.Make");

    Value* pValue2 = new StringValue("MakeName");

    exifData.add(key2, pValue2);



    size_t initialCount = exifData.count();

    exifData.sortByKey();

    EXPECT_EQ(exifData.count(), initialCount);

}



TEST_F(ExifDataTest_775, SortByTag_DoesNotChangeCount_775) {

    ExifKey key1("Exif.Image.Artist");

    Value* pValue1 = new StringValue("ArtistName");

    exifData.add(key1, pValue1);



    ExifKey key2("Exif.Image.Make");

    Value* pValue2 = new StringValue("MakeName");

    exifData.add(key2, pValue2);



    size_t initialCount = exifData.count();

    exifData.sortByTag();

    EXPECT_EQ(exifData.count(), initialCount);

}



TEST_F(ExifDataTest_775, EraseSingleElement_DecreasesCount_775) {

    ExifKey key("Exif.Image.Artist");

    Value* pValue = new StringValue("ArtistName");

    exifData.add(key, pValue);



    size_t initialCount = exifData.count();

    auto pos = exifData.findKey(key);

    if (pos != exifData.end()) {

        exifData.erase(pos);

    }

    EXPECT_EQ(exifData.count(), initialCount - 1);

}



TEST_F(ExifDataTest_775, EraseRange_DecreasesCount_775) {

    ExifKey key1("Exif.Image.Artist");

    Value* pValue1 = new StringValue("ArtistName");

    exifData.add(key1, pValue1);



    ExifKey key2("Exif.Image.Make");

    Value* pValue2 = new StringValue("MakeName");

    exifData.add(key2, pValue2);



    size_t initialCount = exifData.count();

    exifData.erase(exifData.begin(), exifData.end());

    EXPECT_EQ(exifData.count(), 0);

}



TEST_F(ExifDataTest_775, FindKey_ReturnsIteratorToElement_775) {

    ExifKey key("Exif.Image.Artist");

    Value* pValue = new StringValue("ArtistName");

    exifData.add(key, pValue);



    auto pos = exifData.findKey(key);

    EXPECT_NE(pos, exifData.end());

    EXPECT_EQ(pos->key(), key.key());

}



TEST_F(ExifDataTest_775, FindKey_ReturnsEndIfNotFound_775) {

    ExifKey key("Non.Existing.Key");

    auto pos = exifData.findKey(key);

    EXPECT_EQ(pos, exifData.end());

}
