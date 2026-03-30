#include <gtest/gtest.h>

#include "exiv2/exif.hpp"



using namespace Exiv2;



class ExifDataTest_777 : public ::testing::Test {

protected:

    ExifData exifData;

};



TEST_F(ExifDataTest_777, AddExifdatum_NormalOperation_777) {

    Exifdatum exifDatum(/*key*/, /*pValue*/ nullptr);

    exifData.add(exifDatum);



    EXPECT_FALSE(exifData.empty());

    EXPECT_EQ(exifData.count(), 1);

}



TEST_F(ExifDataTest_777, AddMultipleExifdatums_NormalOperation_777) {

    Exifdatum exifDatum1(/*key*/, /*pValue*/ nullptr);

    Exifdatum exifDatum2(/*key*/, /*pValue*/ nullptr);



    exifData.add(exifDatum1);

    exifData.add(exifDatum2);



    EXPECT_EQ(exifData.count(), 2);

}



TEST_F(ExifDataTest_777, AddExifdatum_BoundaryCondition_EmptyKey_777) {

    Exifdatum exifDatum(/*empty key*/, /*pValue*/ nullptr);

    exifData.add(exifDatum);



    EXPECT_EQ(exifData.count(), 1);

}



TEST_F(ExifDataTest_777, Clear_Exifdatums_NormalOperation_777) {

    Exifdatum exifDatum(/*key*/, /*pValue*/ nullptr);

    exifData.add(exifDatum);



    exifData.clear();



    EXPECT_TRUE(exifData.empty());

    EXPECT_EQ(exifData.count(), 0);

}



TEST_F(ExifDataTest_777, EraseSingle_Exifdatum_NormalOperation_777) {

    Exifdatum exifDatum(/*key*/, /*pValue*/ nullptr);

    exifData.add(exifDatum);



    auto it = exifData.begin();

    exifData.erase(it);



    EXPECT_TRUE(exifData.empty());

    EXPECT_EQ(exifData.count(), 0);

}



TEST_F(ExifDataTest_777, EraseRange_Exifdatums_NormalOperation_777) {

    Exifdatum exifDatum1(/*key*/, /*pValue*/ nullptr);

    Exifdatum exifDatum2(/*key*/, /*pValue*/ nullptr);



    exifData.add(exifDatum1);

    exifData.add(exifDatum2);



    exifData.erase(exifData.begin(), exifData.end());



    EXPECT_TRUE(exifData.empty());

    EXPECT_EQ(exifData.count(), 0);

}



TEST_F(ExifDataTest_777, FindKey_Exifdatum_NormalOperation_777) {

    ExifKey key(/*keyString*/);

    Exifdatum exifDatum(key, /*pValue*/ nullptr);



    exifData.add(exifDatum);



    auto it = exifData.findKey(key);

    EXPECT_NE(it, exifData.end());

}



TEST_F(ExifDataTest_777, FindNonexistentKey_Exifdatum_NormalOperation_777) {

    ExifKey key(/*keyString*/);

    Exifdatum exifDatum(key, /*pValue*/ nullptr);



    exifData.add(exifDatum);



    ExifKey nonExistentKey(/*nonExistentKeyString*/);

    auto it = exifData.findKey(nonExistentKey);

    EXPECT_EQ(it, exifData.end());

}



TEST_F(ExifDataTest_777, SortByKey_NormalOperation_777) {

    Exifdatum exifDatum1(/*key1*/, /*pValue*/ nullptr);

    Exifdatum exifDatum2(/*key2*/, /*pValue*/ nullptr);



    exifData.add(exifDatum1);

    exifData.add(exifDatum2);



    exifData.sortByKey();

}



TEST_F(ExifDataTest_777, SortByTag_NormalOperation_777) {

    Exifdatum exifDatum1(/*key1*/, /*pValue*/ nullptr);

    Exifdatum exifDatum2(/*key2*/, /*pValue*/ nullptr);



    exifData.add(exifDatum1);

    exifData.add(exifDatum2);



    exifData.sortByTag();

}
