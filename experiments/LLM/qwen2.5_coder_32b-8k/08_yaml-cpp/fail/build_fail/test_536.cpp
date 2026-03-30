#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/emitter.h"

#include "yaml-cpp/emitterstate.h"



using namespace YAML;



class EmitterTest_536 : public ::testing::Test {

protected:

    std::ostringstream stream;

    Emitter emitter;



    void SetUp() override {

        emitter = Emitter(stream);

    }

};



TEST_F(EmitterTest_536, WriteTrue_DefaultBoolFormat_ReturnsTrueString_536) {

    emitter.Write(true);

    EXPECT_EQ("true", stream.str());

}



TEST_F(EmitterTest_536, WriteFalse_DefaultBoolFormat_ReturnsFalseString_536) {

    emitter.Write(false);

    EXPECT_EQ("false", stream.str());

}



TEST_F(EmitterTest_536, WriteTrue_ShortBoolLength_ReturnsTString_536) {

    emitter.SetBoolFormat(ShortBool);

    emitter.Write(true);

    EXPECT_EQ("t", stream.str());

}



TEST_F(EmitterTest_536, WriteFalse_ShortBoolLength_ReturnsFString_536) {

    emitter.SetBoolFormat(ShortBool);

    emitter.Write(false);

    EXPECT_EQ("f", stream.str());

}



TEST_F(EmitterTest_536, WriteTrue_UpperCase_ReturnsTRUEString_536) {

    emitter.SetBoolCaseFormat(UpperCase);

    emitter.Write(true);

    EXPECT_EQ("TRUE", stream.str());

}



TEST_F(EmitterTest_536, WriteFalse_UpperCase_ReturnsFALSEString_536) {

    emitter.SetBoolCaseFormat(UpperCase);

    emitter.Write(false);

    EXPECT_EQ("FALSE", stream.str());

}



TEST_F(EmitterTest_536, WriteTrue_LowerCase_ReturnstrueString_536) {

    emitter.SetBoolCaseFormat(LowerCase);

    emitter.Write(true);

    EXPECT_EQ("true", stream.str());

}



TEST_F(EmitterTest_536, WriteFalse_LowerCase_ReturnsfalseString_536) {

    emitter.SetBoolCaseFormat(LowerCase);

    emitter.Write(false);

    EXPECT_EQ("false", stream.str());

}



TEST_F(EmitterTest_536, WriteTrue_CamelCase_ReturnstrUeString_536) {

    emitter.SetBoolCaseFormat(CamelCase);

    emitter.Write(true);

    EXPECT_EQ("trUe", stream.str());

}



TEST_F(EmitterTest_536, WriteFalse_CamelCase_ReturnsfAlSeString_536) {

    emitter.SetBoolCaseFormat(CamelCase);

    emitter.Write(false);

    EXPECT_EQ("fAlSe", stream.str());

}



TEST_F(EmitterTest_536, WriteTrue_WhenEmitterNotGood_NothingWritten_536) {

    emitter.m_pState->SetError("test error");

    emitter.Write(true);

    EXPECT_TRUE(stream.str().empty());

}



TEST_F(EmitterTest_536, WriteFalse_WhenEmitterNotGood_NothingWritten_536) {

    emitter.m_pState->SetError("test error");

    emitter.Write(false);

    EXPECT_TRUE(stream.str().empty());

}
