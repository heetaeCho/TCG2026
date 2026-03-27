#include <gtest/gtest.h>

#include "Object.h"



TEST_F(FileSpecTest_1986, GetStringFromSimpleStringFileSpec_1986) {

    Object fileSpec(Object::objString, "example.txt");

    Object result = getFileSpecName(&fileSpec);

    EXPECT_TRUE(result.isString());

    EXPECT_EQ(result.getNameString(), "example.txt");

}



TEST_F(FileSpecTest_1986, GetStringFromDictWithUFKey_1986) {

    Dict dict;

    dict.dictAdd("UF", Object(Object::objString, "unicode_filename.txt"));

    Object fileSpec(std::move(dict));

    Object result = getFileSpecName(&fileSpec);

    EXPECT_TRUE(result.isString());

    EXPECT_EQ(result.getNameString(), "unicode_filename.txt");

}



TEST_F(FileSpecTest_1986, GetStringFromDictWithFKey_1986) {

    Dict dict;

    dict.dictAdd("F", Object(Object::objString, "filename.txt"));

    Object fileSpec(std::move(dict));

    Object result = getFileSpecName(&fileSpec);

    EXPECT_TRUE(result.isString());

    EXPECT_EQ(result.getNameString(), "filename.txt");

}



TEST_F(FileSpecTest_1986, GetStringFromDictWithDOSKey_1986) {

    Dict dict;

    dict.dictAdd("DOS", Object(Object::objString, "dos_filename.txt"));

    Object fileSpec(std::move(dict));

    Object result = getFileSpecName(&fileSpec);

    EXPECT_TRUE(result.isString());

    EXPECT_EQ(result.getNameString(), "dos_filename.txt");

}



TEST_F(FileSpecTest_1986, GetStringFromDictWithMacKey_1986) {

    Dict dict;

    dict.dictAdd("Mac", Object(Object::objString, "mac_filename.txt"));

    Object fileSpec(std::move(dict));

    Object result = getFileSpecName(&fileSpec);

    EXPECT_TRUE(result.isString());

    EXPECT_EQ(result.getNameString(), "mac_filename.txt");

}



TEST_F(FileSpecTest_1986, GetStringFromDictWithUnixKey_1986) {

    Dict dict;

    dict.dictAdd("Unix", Object(Object::objString, "unix_filename.txt"));

    Object fileSpec(std::move(dict));

    Object result = getFileSpecName(&fileSpec);

    EXPECT_TRUE(result.isString());

    EXPECT_EQ(result.getNameString(), "unix_filename.txt");

}



TEST_F(FileSpecTest_1986, GetEmptyObjectFromDictWithoutFileNameKeys_1986) {

    Dict dict;

    Object fileSpec(std::move(dict));

    Object result = getFileSpecName(&fileSpec);

    EXPECT_FALSE(result.isString());

}



TEST_F(FileSpecTest_1986, GetEmptyObjectFromNonDictOrNonStringFileSpec_1986) {

    Object fileSpec(Object::objInt, 42);

    Object result = getFileSpecName(&fileSpec);

    EXPECT_FALSE(result.isString());

}
