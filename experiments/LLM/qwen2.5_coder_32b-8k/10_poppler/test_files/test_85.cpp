#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Object.h"



class ObjectTest_85 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if necessary

    }



    void TearDown() override {

        // Cleanup if necessary

    }

};



TEST_F(ObjectTest_85, IsEOF_ReturnsTrueForEofObject_85) {

    Object eofObj = Object::eof();

    EXPECT_TRUE(eofObj.isEOF());

}



TEST_F(ObjectTest_85, IsEOF_ReturnsFalseForNonEofObject_85) {

    Object intObj(42);

    EXPECT_FALSE(intObj.isEOF());

}



TEST_F(ObjectTest_85, GetType_ReturnsCorrectTypeForBool_85) {

    Object boolObj(true);

    EXPECT_EQ(boolObj.getType(), objBool);

}



TEST_F(ObjectTest_85, GetType_ReturnsCorrectTypeForInt_85) {

    Object intObj(42);

    EXPECT_EQ(intObj.getType(), objInt);

}



TEST_F(ObjectTest_85, GetType_ReturnsCorrectTypeForReal_85) {

    Object realObj(3.14);

    EXPECT_EQ(realObj.getType(), objReal);

}



TEST_F(ObjectTest_85, GetType_ReturnsCorrectTypeForString_85) {

    Object stringObj("test");

    EXPECT_EQ(stringObj.getType(), objString);

}



TEST_F(ObjectTest_85, GetType_ReturnsCorrectTypeForHexString_85) {

    // Assuming there's a way to create a hex string object

    std::unique_ptr<GooString> hexString(new GooString("<1234>"));

    Object hexStringObj(std::move(hexString));

    EXPECT_EQ(hexStringObj.getType(), objHexString);

}



TEST_F(ObjectTest_85, GetType_ReturnsCorrectTypeForName_85) {

    Object nameObj("name");

    EXPECT_EQ(nameObj.getType(), objName);

}



TEST_F(ObjectTest_85, GetType_ReturnsCorrectTypeForNull_85) {

    Object nullObj = Object::null();

    EXPECT_EQ(nullObj.getType(), objNull);

}



TEST_F(ObjectTest_85, GetType_ReturnsCorrectTypeForArray_85) {

    // Assuming Array is a valid type that can be constructed

    Array* array = new Array();

    Object arrayObj(array);

    EXPECT_EQ(arrayObj.getType(), objArray);

    delete array;

}



TEST_F(ObjectTest_85, GetType_ReturnsCorrectTypeForDict_85) {

    // Assuming Dict is a valid type that can be constructed

    Dict* dict = new Dict();

    Object dictObj(dict);

    EXPECT_EQ(dictObj.getType(), objDict);

    delete dict;

}



TEST_F(ObjectTest_85, GetType_ReturnsCorrectTypeForStream_85) {

    // Assuming Stream is a valid type that can be constructed

    Stream* stream = nullptr; // Placeholder for actual stream object

    Object streamObj(stream);

    EXPECT_EQ(streamObj.getType(), objStream);

}



TEST_F(ObjectTest_85, GetType_ReturnsCorrectTypeForRef_85) {

    // Assuming Ref can be constructed directly or through a valid path

    Ref ref(1, 0);

    Object refObj(ref);

    EXPECT_EQ(refObj.getType(), objRef);

}



TEST_F(ObjectTest_85, GetType_ReturnsCorrectTypeForCmd_85) {

    Object cmdObj("command");

    EXPECT_EQ(cmdObj.getType(), objCmd);

}



TEST_F(ObjectTest_85, GetType_ReturnsCorrectTypeForError_85) {

    Object errorObj = Object::error();

    EXPECT_EQ(errorObj.getType(), objError);

}



TEST_F(ObjectTest_85, GetType_ReturnsCorrectTypeForNone_85) {

    Object noneObj;

    EXPECT_EQ(noneObj.getType(), objNone);

}



TEST_F(ObjectTest_85, GetType_ReturnsCorrectTypeForInt64_85) {

    Object int64Obj(1234567890LL);

    EXPECT_EQ(int64Obj.getType(), objInt64);

}
