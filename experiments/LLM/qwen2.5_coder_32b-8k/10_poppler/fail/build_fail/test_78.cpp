#include <gtest/gtest.h>

#include "poppler/Object.h"



class ObjectTest_78 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(ObjectTest_78, IsNull_ReturnsTrueForNullObject_78) {

    Object obj = Object::null();

    EXPECT_TRUE(obj.isNull());

}



TEST_F(ObjectTest_78, IsNull_ReturnsFalseForNonNullObject_78) {

    Object obj = Object(true);

    EXPECT_FALSE(obj.isNull());

}



TEST_F(ObjectTest_78, GetType_ReturnsCorrectTypeForBool_78) {

    Object obj = Object(true);

    EXPECT_EQ(obj.getType(), objBool);

}



TEST_F(ObjectTest_78, GetType_ReturnsCorrectTypeForInt_78) {

    Object obj = Object(42);

    EXPECT_EQ(obj.getType(), objInt);

}



TEST_F(ObjectTest_78, GetType_ReturnsCorrectTypeForReal_78) {

    Object obj = Object(3.14);

    EXPECT_EQ(obj.getType(), objReal);

}



TEST_F(ObjectTest_78, GetType_ReturnsCorrectTypeForString_78) {

    Object obj = Object(std::string("test"));

    EXPECT_EQ(obj.getType(), objString);

}



TEST_F(ObjectTest_78, GetType_ReturnsCorrectTypeForName_78) {

    Object obj(ObjType::objName, "name");

    EXPECT_EQ(obj.getType(), objName);

}



TEST_F(ObjectTest_78, GetType_ReturnsCorrectTypeForNull_78) {

    Object obj = Object::null();

    EXPECT_EQ(obj.getType(), objNull);

}



TEST_F(ObjectTest_78, GetType_ReturnsCorrectTypeForArray_78) {

    Object obj = Object(static_cast<Array*>(nullptr));

    EXPECT_EQ(obj.getType(), objArray);

}



TEST_F(ObjectTest_78, GetType_ReturnsCorrectTypeForDict_78) {

    Object obj = Object(static_cast<Dict*>(nullptr));

    EXPECT_EQ(obj.getType(), objDict);

}



TEST_F(ObjectTest_78, GetType_ReturnsCorrectTypeForStream_78) {

    Object obj = Object(static_cast<Stream*>(nullptr));

    EXPECT_EQ(obj.getType(), objStream);

}



TEST_F(ObjectTest_78, GetType_ReturnsCorrectTypeForRef_78) {

    Ref ref;

    Object obj(ref);

    EXPECT_EQ(obj.getType(), objRef);

}



TEST_F(ObjectTest_78, GetType_ReturnsCorrectTypeForCmd_78) {

    Object obj(ObjType::objCmd, "command");

    EXPECT_EQ(obj.getType(), objCmd);

}



TEST_F(ObjectTest_78, GetType_ReturnsCorrectTypeForError_78) {

    Object obj = Object::error();

    EXPECT_EQ(obj.getType(), objError);

}



TEST_F(ObjectTest_78, GetType_ReturnsCorrectTypeForEOF_78) {

    Object obj = Object::eof();

    EXPECT_EQ(obj.getType(), objEOF);

}



TEST_F(ObjectTest_78, GetType_ReturnsCorrectTypeForNone_78) {

    Object obj;

    EXPECT_EQ(obj.getType(), objNone);

}



TEST_F(ObjectTest_78, GetType_ReturnsCorrectTypeForInt64_78) {

    Object obj = Object(9223372036854775807LL);

    EXPECT_EQ(obj.getType(), objInt64);

}



TEST_F(ObjectTest_78, GetType_ReturnsCorrectTypeForHexString_78) {

    Object obj(std::unique_ptr<GooString>(new GooString("hex")));

    EXPECT_EQ(obj.getType(), objHexString);

}
