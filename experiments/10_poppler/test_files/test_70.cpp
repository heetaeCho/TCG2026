#include <gtest/gtest.h>

#include "Object.h"



class ObjectTest_70 : public ::testing::Test {

protected:

    // Setup and teardown can be added here if necessary

};



// Test normal operation of getType() with different types

TEST_F(ObjectTest_70, GetType_Bool_70) {

    Object obj(true);

    EXPECT_EQ(obj.getType(), objBool);

}



TEST_F(ObjectTest_70, GetType_Int_70) {

    Object obj(42);

    EXPECT_EQ(obj.getType(), objInt);

}



TEST_F(ObjectTest_70, GetType_Real_70) {

    Object obj(3.14);

    EXPECT_EQ(obj.getType(), objReal);

}



TEST_F(ObjectTest_70, GetType_String_70) {

    Object obj("test_string");

    EXPECT_EQ(obj.getType(), objString);

}



TEST_F(ObjectTest_70, GetType_Name_70) {

    Object obj(std::string_view("/name"), "value");

    EXPECT_EQ(obj.getType(), objName);

}



TEST_F(ObjectTest_70, GetType_Null_70) {

    Object obj = Object::null();

    EXPECT_EQ(obj.getType(), objNull);

}



TEST_F(ObjectTest_70, GetType_Array_70) {

    Array* array = new Array();

    Object obj(array);

    EXPECT_EQ(obj.getType(), objArray);

    delete array;

}



TEST_F(ObjectTest_70, GetType_Dict_70) {

    Dict* dict = new Dict();

    Object obj(dict);

    EXPECT_EQ(obj.getType(), objDict);

    delete dict;

}



TEST_F(ObjectTest_70, GetType_Stream_70) {

    // Assuming Stream is a mockable or testable class

    Stream* stream = nullptr; // Mock or create a valid Stream object

    Object obj(stream);

    EXPECT_EQ(obj.getType(), objStream);

}



TEST_F(ObjectTest_70, GetType_Ref_70) {

    Ref ref(1, 0);

    Object obj(ref.num, ref.gen);

    EXPECT_EQ(obj.getType(), objRef);

}



TEST_F(ObjectTest_70, GetType_Cmd_70) {

    Object obj(std::string_view("command"));

    EXPECT_EQ(obj.getType(), objCmd);

}



TEST_F(ObjectTest_70, GetType_Error_70) {

    Object obj = Object::error();

    EXPECT_EQ(obj.getType(), objError);

}



TEST_F(ObjectTest_70, GetType_EOF_70) {

    Object obj = Object::eof();

    EXPECT_EQ(obj.getType(), objEOF);

}



TEST_F(ObjectTest_70, GetType_None_70) {

    Object obj;

    EXPECT_EQ(obj.getType(), objNone);

}



TEST_F(ObjectTest_70, GetType_Int64_70) {

    Object obj(9223372036854775807LL);

    EXPECT_EQ(obj.getType(), objInt64);

}



TEST_F(ObjectTest_70, GetType_HexString_70) {

    std::unique_ptr<GooString> hexStr = std::make_unique<GooString>("<hex>");

    Object obj(std::move(hexStr));

    EXPECT_EQ(obj.getType(), objHexString);

}



// Test boundary conditions and exceptional cases

TEST_F(ObjectTest_70, IsDict_EmptyDict_70) {

    Dict* dict = new Dict();

    Object obj(dict);

    EXPECT_FALSE(obj.isDict("any_type"));

    delete dict;

}



TEST_F(ObjectTest_70, ArrayGetLength_EmptyArray_70) {

    Array* array = new Array();

    Object obj(array);

    EXPECT_EQ(obj.arrayGetLength(), 0);

    delete array;

}



TEST_F(ObjectTest_70, DictGetLength_EmptyDict_70) {

    Dict* dict = new Dict();

    Object obj(dict);

    EXPECT_EQ(obj.dictGetLength(), 0);

    delete dict;

}
