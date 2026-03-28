#include <gtest/gtest.h>

#include "Object.h"

#include <string>



using namespace std::literals;



class ObjectTest_2758 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if needed

    }



    void TearDown() override {

        // Cleanup if needed

    }

};



TEST_F(ObjectTest_2758, ConstructorWithStringView_2758) {

    Object obj(objName, "test"sv);

    EXPECT_STREQ(obj.getName(), "test");

}



TEST_F(ObjectTest_2758, ConstructorWithCString_2758) {

    Object obj(objCmd, "command");

    EXPECT_STREQ(obj.getCmd(), "command");

}



TEST_F(ObjectTest_2758, IsBool_2758) {

    Object boolObj(true);

    EXPECT_TRUE(boolObj.isBool());

    EXPECT_FALSE(boolObj.isInt());



    Object intObj(42);

    EXPECT_FALSE(intObj.isBool());

    EXPECT_TRUE(intObj.isInt());

}



TEST_F(ObjectTest_2758, IsString_2758) {

    Object stringObj(std::string("test_string"));

    EXPECT_TRUE(stringObj.isString());

}



TEST_F(ObjectTest_2758, IsName_2758) {

    Object nameObj(objName, "name_test"sv);

    EXPECT_TRUE(nameObj.isName("name_test"sv));

}



TEST_F(ObjectTest_2758, IsCmd_2758) {

    Object cmdObj(objCmd, "cmd_test");

    EXPECT_TRUE(cmdObj.isCmd("cmd_test"sv));

}



TEST_F(ObjectTest_2758, GetInt_2758) {

    Object intObj(42);

    EXPECT_EQ(intObj.getInt(), 42);

}



TEST_F(ObjectTest_2758, GetReal_2758) {

    Object realObj(3.14);

    EXPECT_DOUBLE_EQ(realObj.getReal(), 3.14);

}



TEST_F(ObjectTest_2758, GetInt64_2758) {

    Object int64Obj(9223372036854775807LL);

    EXPECT_EQ(int64Obj.getInt64(), 9223372036854775807LL);

}



TEST_F(ObjectTest_2758, GetNameString_2758) {

    Object nameObj(objName, "name_test"sv);

    EXPECT_EQ(nameObj.getNameString(), "name_test");

}



TEST_F(ObjectTest_2758, GetType_2758) {

    Object intObj(42);

    EXPECT_EQ(intObj.getType(), objInt);



    Object stringObj(std::string("test_string"));

    EXPECT_EQ(stringObj.getType(), objString);

}



TEST_F(ObjectTest_2758, StaticNullObject_2758) {

    Object nullObj = Object::null();

    EXPECT_TRUE(nullObj.isNull());

}



TEST_F(ObjectTest_2758, StaticEofObject_2758) {

    Object eofObj = Object::eof();

    EXPECT_TRUE(eofObj.isEOF());

}



TEST_F(ObjectTest_2758, StaticErrorObject_2758) {

    Object errorObj = Object::error();

    EXPECT_TRUE(errorObj.isError());

}



TEST_F(ObjectTest_2758, CopyConstructor_2758) {

    Object original(objName, "original"sv);

    Object copy = original.copy();

    EXPECT_STREQ(copy.getName(), "original");

}



TEST_F(ObjectTest_2758, MoveConstructor_2758) {

    Object original(objCmd, "command"sv);

    Object moved = std::move(original);

    EXPECT_STREQ(moved.getCmd(), "command");

}



TEST_F(ObjectTest_2758, DefaultConstructor_2758) {

    Object defaultObj;

    EXPECT_TRUE(defaultObj.isNone());

}
