#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Object.h"

#include <memory>

#include <string>



using namespace testing;



class ObjectTest_67 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(ObjectTest_67, ConstructWithBool_67) {

    Object obj(true);

    EXPECT_TRUE(obj.isBool());

    EXPECT_EQ(obj.getBool(), true);

}



TEST_F(ObjectTest_67, ConstructWithInt_67) {

    Object obj(42);

    EXPECT_TRUE(obj.isInt());

    EXPECT_EQ(obj.getInt(), 42);

}



TEST_F(ObjectTest_67, ConstructWithDouble_67) {

    Object obj(3.14);

    EXPECT_TRUE(obj.isReal());

    EXPECT_DOUBLE_EQ(obj.getReal(), 3.14);

}



TEST_F(ObjectTest_67, ConstructWithStringUniquePtr_67) {

    auto str = std::make_unique<GooString>("test");

    Object obj(std::move(str));

    EXPECT_TRUE(obj.isString());

    EXPECT_STREQ(obj.getString()->c_str(), "test");

}



TEST_F(ObjectTest_67, ConstructWithStringRvalue_67) {

    Object obj(std::string("test"));

    EXPECT_TRUE(obj.isString());

    EXPECT_EQ(obj.getNameString(), "test");

}



TEST_F(ObjectTest_67, ConstructWithLongLongInt_67) {

    Object obj(1234567890123LL);

    EXPECT_TRUE(obj.isInt64());

    EXPECT_EQ(obj.getInt64(), 1234567890123LL);

}



TEST_F(ObjectTest_67, IsNullAfterDefaultConstructor_67) {

    Object obj;

    EXPECT_TRUE(obj.isNull());

}



TEST_F(ObjectTest_67, SetToNull_67) {

    Object obj(42);

    obj.setToNull();

    EXPECT_TRUE(obj.isNull());

}



TEST_F(ObjectTest_67, IsDictWithValidType_67) {

    Dict dict;

    Object obj(&dict);

    EXPECT_TRUE(obj.isDict());

}



TEST_F(ObjectTest_67, ArrayAddAndGet_67) {

    Object arrayObj(Array::initArray());

    arrayObj.arrayAdd(Object(42));

    EXPECT_EQ(arrayObj.arrayGetLength(), 1);

    EXPECT_EQ(arrayObj.arrayGetNF(0).getInt(), 42);

}



TEST_F(ObjectTest_67, ArrayRemoveAndGet_67) {

    Object arrayObj(Array::initArray());

    arrayObj.arrayAdd(Object(42));

    arrayObj.arrayAdd(Object(3.14));

    EXPECT_EQ(arrayObj.arrayGetLength(), 2);



    arrayObj.arrayRemove(0);

    EXPECT_EQ(arrayObj.arrayGetLength(), 1);

    EXPECT_DOUBLE_EQ(arrayObj.arrayGetNF(0).getReal(), 3.14);

}



TEST_F(ObjectTest_67, DictAddAndGet_67) {

    Object dictObj(Dict::initDict());

    dictObj.dictAdd("key1", Object(42));

    dictObj.dictAdd("key2", Object(3.14));



    EXPECT_TRUE(dictObj.isDict());

    EXPECT_EQ(dictObj.dictGetLength(), 2);

    EXPECT_EQ(dictObj.dictLookupNF("key1").getInt(), 42);

    EXPECT_DOUBLE_EQ(dictObj.dictLookupNF("key2").getReal(), 3.14);

}



TEST_F(ObjectTest_67, DictSetAndGet_67) {

    Object dictObj(Dict::initDict());

    dictObj.dictAdd("key", Object(42));

    EXPECT_EQ(dictObj.dictLookupNF("key").getInt(), 42);



    dictObj.dictSet("key", Object(3.14));

    EXPECT_DOUBLE_EQ(dictObj.dictLookupNF("key").getReal(), 3.14);

}



TEST_F(ObjectTest_67, DictRemoveAndGet_67) {

    Object dictObj(Dict::initDict());

    dictObj.dictAdd("key1", Object(42));

    dictObj.dictAdd("key2", Object(3.14));

    EXPECT_EQ(dictObj.dictGetLength(), 2);



    dictObj.dictRemove("key1");

    EXPECT_EQ(dictObj.dictGetLength(), 1);

    EXPECT_TRUE(dictObj.dictLookupNF("key2").isReal());

}



TEST_F(ObjectTest_67, StreamOperations_67) {

    // Assuming we have a mock or fake stream implementation for testing

    Object obj(Stream::initStream(/*mock stream*/));

    EXPECT_TRUE(obj.isStream());



    obj.streamRewind();

    int ch = obj.streamGetChar();

    unsigned char buffer[10];

    int numCharsRead = obj.streamGetChars(10, buffer);

    Goffset pos = 10;

    obj.streamSetPos(pos, /*dir*/);

    const Dict* dict = obj.streamGetDict();



    EXPECT_TRUE(dict != nullptr); // Just a placeholder check

}



TEST_F(ObjectTest_67, StaticNullObject_67) {

    Object nullObj = Object::null();

    EXPECT_TRUE(nullObj.isNull());

}



TEST_F(ObjectTest_67, StaticEofObject_67) {

    Object eofObj = Object::eof();

    EXPECT_TRUE(eofObj.isEOF());

}



TEST_F(ObjectTest_67, StaticErrorObject_67) {

    Object errorObj = Object::error();

    EXPECT_TRUE(errorObj.isError());

}
