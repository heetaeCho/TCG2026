#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/Object.h"

class ObjectTest_1238 : public ::testing::Test {
protected:
    // Any necessary setup or teardown can go here.
    ObjectTest_1238() = default;
    ~ObjectTest_1238() override = default;
};

TEST_F(ObjectTest_1238, IsCmd_ReturnsTrue_WhenCmdMatches_1238) {
    Object obj(objCmd, "testCmd");

    EXPECT_TRUE(obj.isCmd("testCmd"));
}

TEST_F(ObjectTest_1238, IsCmd_ReturnsFalse_WhenCmdDoesNotMatch_1238) {
    Object obj(objCmd, "testCmd");

    EXPECT_FALSE(obj.isCmd("anotherCmd"));
}

TEST_F(ObjectTest_1238, IsCmd_ReturnsFalse_WhenObjectIsNotCmd_1238) {
    Object obj(objInt, 10);

    EXPECT_FALSE(obj.isCmd("testCmd"));
}

TEST_F(ObjectTest_1238, IsNone_ReturnsTrue_WhenObjectIsNone_1238) {
    Object obj(objNone);

    EXPECT_TRUE(obj.isNone());
}

TEST_F(ObjectTest_1238, IsNone_ReturnsFalse_WhenObjectIsNotNone_1238) {
    Object obj(objInt, 10);

    EXPECT_FALSE(obj.isNone());
}

TEST_F(ObjectTest_1238, GetInt_ReturnsCorrectIntValue_WhenObjectIsInt_1238) {
    Object obj(10);

    EXPECT_EQ(obj.getInt(), 10);
}

TEST_F(ObjectTest_1238, GetInt_ReturnsZero_WhenObjectIsNotInt_1238) {
    Object obj(objReal, 10.5);

    EXPECT_EQ(obj.getInt(), 0);
}

TEST_F(ObjectTest_1238, IsReal_ReturnsTrue_WhenObjectIsReal_1238) {
    Object obj(10.5);

    EXPECT_TRUE(obj.isReal());
}

TEST_F(ObjectTest_1238, IsReal_ReturnsFalse_WhenObjectIsNotReal_1238) {
    Object obj(objInt, 10);

    EXPECT_FALSE(obj.isReal());
}

TEST_F(ObjectTest_1238, IsString_ReturnsTrue_WhenObjectIsString_1238) {
    Object obj(std::make_unique<GooString>("testString"));

    EXPECT_TRUE(obj.isString());
}

TEST_F(ObjectTest_1238, IsString_ReturnsFalse_WhenObjectIsNotString_1238) {
    Object obj(objInt, 10);

    EXPECT_FALSE(obj.isString());
}

TEST_F(ObjectTest_1238, GetString_ReturnsCorrectString_WhenObjectIsString_1238) {
    Object obj(std::make_unique<GooString>("testString"));

    EXPECT_EQ(obj.getString()->getCString(), "testString");
}

TEST_F(ObjectTest_1238, IsArray_ReturnsTrue_WhenObjectIsArray_1238) {
    Array* arr = new Array();
    Object obj(arr);

    EXPECT_TRUE(obj.isArray());
}

TEST_F(ObjectTest_1238, IsArray_ReturnsFalse_WhenObjectIsNotArray_1238) {
    Object obj(objInt, 10);

    EXPECT_FALSE(obj.isArray());
}

TEST_F(ObjectTest_1238, DictAdd_AddsKeyValuePair_WhenObjectIsDict_1238) {
    Dict* dict = new Dict();
    Object obj(dict);

    obj.dictAdd("key", Object(20));

    EXPECT_EQ(dict->getLength(), 1);
    EXPECT_EQ(dict->dictLookup("key").getInt(), 20);
}

TEST_F(ObjectTest_1238, DictRemove_RemovesKeyValuePair_WhenKeyExists_1238) {
    Dict* dict = new Dict();
    Object obj(dict);
    
    obj.dictAdd("key", Object(20));
    obj.dictRemove("key");

    EXPECT_EQ(dict->getLength(), 0);
}

TEST_F(ObjectTest_1238, DictRemove_DoesNothing_WhenKeyDoesNotExist_1238) {
    Dict* dict = new Dict();
    Object obj(dict);

    obj.dictRemove("nonExistentKey");

    EXPECT_EQ(dict->getLength(), 0);
}

TEST_F(ObjectTest_1238, StreamRewind_RewindsStream_1238) {
    Stream* stream = new Stream();
    Object obj(stream);

    EXPECT_TRUE(obj.streamRewind());
}

TEST_F(ObjectTest_1238, StreamClose_ClosesStream_1238) {
    Stream* stream = new Stream();
    Object obj(stream);

    obj.streamClose();
    
    EXPECT_TRUE(stream->isClosed());
}

TEST_F(ObjectTest_1238, IsError_ReturnsTrue_WhenObjectIsError_1238) {
    Object obj(objError);

    EXPECT_TRUE(obj.isError());
}

TEST_F(ObjectTest_1238, IsError_ReturnsFalse_WhenObjectIsNotError_1238) {
    Object obj(objInt, 10);

    EXPECT_FALSE(obj.isError());
}

TEST_F(ObjectTest_1238, IsEOF_ReturnsTrue_WhenObjectIsEOF_1238) {
    Object obj(objEOF);

    EXPECT_TRUE(obj.isEOF());
}

TEST_F(ObjectTest_1238, IsEOF_ReturnsFalse_WhenObjectIsNotEOF_1238) {
    Object obj(objInt, 10);

    EXPECT_FALSE(obj.isEOF());
}

TEST_F(ObjectTest_1238, IsNull_ReturnsTrue_WhenObjectIsNull_1238) {
    Object obj(objNull);

    EXPECT_TRUE(obj.isNull());
}

TEST_F(ObjectTest_1238, IsNull_ReturnsFalse_WhenObjectIsNotNull_1238) {
    Object obj(objInt, 10);

    EXPECT_FALSE(obj.isNull());
}