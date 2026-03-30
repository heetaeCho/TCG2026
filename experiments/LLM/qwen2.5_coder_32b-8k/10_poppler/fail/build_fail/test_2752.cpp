#include <gtest/gtest.h>

#include "Object.h"

#include "Dict.h"



class ObjectTest : public ::testing::Test {

protected:

    void SetUp() override {

        dict = std::make_unique<Dict>(nullptr);

        obj = std::make_unique<Object>(dict.get());

    }



    void TearDown() override {

        obj.reset();

        dict.reset();

    }



    std::unique_ptr<Dict> dict;

    std::unique_ptr<Object> obj;

};



TEST_F(ObjectTest_2752, TypeIsDict_2752) {

    EXPECT_EQ(obj->getType(), objDict);

}



TEST_F(ObjectTest_2752, IsDict_ReturnsTrueForDictType_2752) {

    EXPECT_TRUE(obj->isDict());

}



TEST_F(ObjectTest_2752, GetDict_ReturnsValidDictPointer_2752) {

    EXPECT_EQ(obj->getDict(), dict.get());

}



TEST_F(ObjectTest_2752, IsArray_ReturnsFalseForDictType_2752) {

    EXPECT_FALSE(obj->isArray());

}



TEST_F(ObjectTest_2752, DictGetLength_ReturnsZeroForEmptyDict_2752) {

    EXPECT_EQ(dict->getLength(), 0);

}



TEST_F(ObjectTest_2752, DictAddAndLookup_ReturnsCorrectObject_2752) {

    Object value(true);

    dict->add("key", std::move(value));

    const Object& result = dict->lookupNF("key");

    EXPECT_TRUE(result.getBool());

}



TEST_F(ObjectTest_2752, DictRemove_DecreasesLength_2752) {

    Object value(true);

    dict->add("key", std::move(value));

    EXPECT_EQ(dict->getLength(), 1);

    dict->remove("key");

    EXPECT_EQ(dict->getLength(), 0);

}



TEST_F(ObjectTest_2752, DictHasKey_ReturnsTrueForExistingKey_2752) {

    Object value(true);

    dict->add("key", std::move(value));

    EXPECT_TRUE(dict->hasKey("key"));

}



TEST_F(ObjectTest_2752, DictHasKey_ReturnsFalseForNonExistentKey_2752) {

    EXPECT_FALSE(dict->hasKey("nonexistent"));

}



TEST_F(ObjectTest_2752, StaticObjectNull_IsNone_2752) {

    Object nullObj = Object::null();

    EXPECT_TRUE(nullObj.isNone());

}



TEST_F(ObjectTest_2752, StaticObjectEof_IsEOF_2752) {

    Object eofObj = Object::eof();

    EXPECT_TRUE(eofObj.isEOF());

}



TEST_F(ObjectTest_2752, StaticObjectError_IsError_2752) {

    Object errorObj = Object::error();

    EXPECT_TRUE(errorObj.isError());

}
