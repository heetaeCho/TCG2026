#include <gtest/gtest.h>

#include "yaml-cpp/emitter.h"



using namespace YAML;



class EmitterTest_48 : public ::testing::Test {

protected:

    Emitter emitter;

};



TEST_F(EmitterTest_48, WriteIntegralType_NormalOperation_48) {

    int value = 123;

    emitter << value;

    EXPECT_EQ(emitter.c_str(), "123");

}



TEST_F(EmitterTest_48, WriteIntegralType_BoundaryCondition_Zero_48) {

    int value = 0;

    emitter << value;

    EXPECT_EQ(emitter.c_str(), "0");

}



TEST_F(EmitterTest_48, WriteIntegralType_BoundaryCondition_Negative_48) {

    int value = -123;

    emitter << value;

    EXPECT_EQ(emitter.c_str(), "-123");

}



TEST_F(EmitterTest_48, Write_String_NormalOperation_48) {

    std::string str = "test string";

    emitter.Write(str);

    EXPECT_EQ(emitter.c_str(), "test string");

}



TEST_F(EmitterTest_48, Write_Char_NormalOperation_48) {

    char ch = 'a';

    emitter.Write(ch);

    EXPECT_EQ(emitter.c_str(), "a");

}



TEST_F(EmitterTest_48, Write_Bool_NormalOperation_True_48) {

    bool value = true;

    emitter.Write(value);

    EXPECT_EQ(emitter.c_str(), "true");

}



TEST_F(EmitterTest_48, Write_Bool_NormalOperation_False_48) {

    bool value = false;

    emitter.Write(value);

    EXPECT_EQ(emitter.c_str(), "false");

}



TEST_F(EmitterTest_48, SetOutputCharset_Success_48) {

    EXPECT_TRUE(emitter.SetOutputCharset(EMITTER_MANIP::UTF8));

}



TEST_F(EmitterTest_48, SetStringFormat_Success_48) {

    EXPECT_TRUE(emitter.SetStringFormat(EMITTER_MANIP::AUTO));

}



TEST_F(EmitterTest_48, SetBoolFormat_Success_48) {

    EXPECT_TRUE(emitter.SetBoolFormat(EMITTER_MANIP::TRUEFALSE));

}



TEST_F(EmitterTest_48, SetNullFormat_Success_48) {

    EXPECT_TRUE(emitter.SetNullFormat(EMITTER_MANIP::NULLSTR));

}



TEST_F(EmitterTest_48, SetIntBase_Success_48) {

    EXPECT_TRUE(emitter.SetIntBase(EMITTER_MANIP::DEC));

}



TEST_F(EmitterTest_48, SetSeqFormat_Success_48) {

    EXPECT_TRUE(emitter.SetSeqFormat(EMITTER_MANIP::BLOCK));

}



TEST_F(EmitterTest_48, SetMapFormat_Success_48) {

    EXPECT_TRUE(emitter.SetMapFormat(EMITTER_MANIP::FLOW));

}



TEST_F(EmitterTest_48, SetIndent_Success_48) {

    EXPECT_TRUE(emitter.SetIndent(2));

}



TEST_F(EmitterTest_48, SetPreCommentIndent_Success_48) {

    EXPECT_TRUE(emitter.SetPreCommentIndent(1));

}



TEST_F(EmitterTest_48, SetPostCommentIndent_Success_48) {

    EXPECT_TRUE(emitter.SetPostCommentIndent(1));

}



TEST_F(EmitterTest_48, SetFloatPrecision_Success_48) {

    EXPECT_TRUE(emitter.SetFloatPrecision(5));

}



TEST_F(EmitterTest_48, SetDoublePrecision_Success_48) {

    EXPECT_TRUE(emitter.SetDoublePrecision(6));

}



TEST_F(EmitterTest_48, Good_ReturnsTrue_48) {

    emitter << 123;

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_48, GetLastError_EmptyStringInitially_48) {

    EXPECT_EQ(emitter.GetLastError(), "");

}
