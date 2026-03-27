#include <gtest/gtest.h>

#include "yaml-cpp/emitter.h"

#include "yaml-cpp/emittermanip.h"



using namespace YAML;



class EmitterTest_44 : public ::testing::Test {

protected:

    Emitter emitter;

};



TEST_F(EmitterTest_44, WriteComment_NormalOperation_44) {

    _Comment comment("This is a comment");

    emitter << comment;

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_44, WriteComment_EmptyString_44) {

    _Comment comment("");

    emitter << comment;

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_44, WriteComment_SpecialCharacters_44) {

    _Comment comment("!@#$%^&*()_+");

    emitter << comment;

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_44, WriteString_NormalOperation_44) {

    emitter << "This is a string";

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_44, WriteString_EmptyString_44) {

    emitter << "";

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_44, WriteString_SpecialCharacters_44) {

    emitter << "!@#$%^&*()_+";

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_44, WriteBool_True_44) {

    emitter << true;

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_44, WriteBool_False_44) {

    emitter << false;

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_44, WriteChar_NormalOperation_44) {

    emitter << 'A';

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_44, WriteInt_DefaultBase_44) {

    emitter << 123;

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_44, WriteFloat_NormalOperation_44) {

    emitter << 123.456f;

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_44, WriteDouble_NormalOperation_44) {

    emitter << 123.456;

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_44, SetIndent_ValidValue_44) {

    EXPECT_TRUE(emitter.SetIndent(4));

}



TEST_F(EmitterTest_44, SetIndent_Zero_44) {

    EXPECT_FALSE(emitter.SetIndent(0));

}



TEST_F(EmitterTest_44, SetFloatPrecision_ValidValue_44) {

    EXPECT_TRUE(emitter.SetFloatPrecision(5));

}



TEST_F(EmitterTest_44, SetDoublePrecision_ValidValue_44) {

    EXPECT_TRUE(emitter.SetDoublePrecision(10));

}



TEST_F(EmitterTest_44, GetLastErrorCode_NoError_44) {

    emitter << "This is a string";

    EXPECT_EQ("", emitter.GetLastError());

}
