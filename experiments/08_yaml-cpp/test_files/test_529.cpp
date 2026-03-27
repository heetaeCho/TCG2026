#include <gtest/gtest.h>

#include "yaml-cpp/emitter.h"



using namespace YAML;



class EmitterTest_529 : public ::testing::Test {

protected:

    Emitter emitter;

};



TEST_F(EmitterTest_529, RestoreGlobalModifiedSettings_NormalOperation_529) {

    // Since we don't have any observable behavior from this function,

    // we can only call it and check for no exceptions or issues.

    emitter.RestoreGlobalModifiedSettings();

}



TEST_F(EmitterTest_529, SetIndent_ValidValues_529) {

    EXPECT_TRUE(emitter.SetIndent(2));

    EXPECT_TRUE(emitter.SetIndent(4));

    EXPECT_TRUE(emitter.SetIndent(6));

}



TEST_F(EmitterTest_529, SetIndent_BoundaryConditions_529) {

    EXPECT_FALSE(emitter.SetIndent(0)); // Assuming 0 is not a valid indent

    EXPECT_TRUE(emitter.SetIndent(1));

    EXPECT_TRUE(emitter.SetIndent(std::numeric_limits<std::size_t>::max()));

}



TEST_F(EmitterTest_529, SetFloatPrecision_ValidValues_529) {

    EXPECT_TRUE(emitter.SetFloatPrecision(3));

    EXPECT_TRUE(emitter.SetFloatPrecision(6));

    EXPECT_TRUE(emitter.SetFloatPrecision(10));

}



TEST_F(EmitterTest_529, SetFloatPrecision_BoundaryConditions_529) {

    EXPECT_FALSE(emitter.SetFloatPrecision(0)); // Assuming 0 is not a valid precision

    EXPECT_TRUE(emitter.SetFloatPrecision(1));

    EXPECT_TRUE(emitter.SetFloatPrecision(std::numeric_limits<std::size_t>::max()));

}



TEST_F(EmitterTest_529, SetDoublePrecision_ValidValues_529) {

    EXPECT_TRUE(emitter.SetDoublePrecision(3));

    EXPECT_TRUE(emitter.SetDoublePrecision(6));

    EXPECT_TRUE(emitter.SetDoublePrecision(10));

}



TEST_F(EmitterTest_529, SetDoublePrecision_BoundaryConditions_529) {

    EXPECT_FALSE(emitter.SetDoublePrecision(0)); // Assuming 0 is not a valid precision

    EXPECT_TRUE(emitter.SetDoublePrecision(1));

    EXPECT_TRUE(emitter.SetDoublePrecision(std::numeric_limits<std::size_t>::max()));

}



TEST_F(EmitterTest_529, SetOutputCharset_ValidValues_529) {

    EXPECT_TRUE(emitter.SetOutputCharset(EMITTER_MANIP::UTF8));

    // Add more valid values if necessary

}



TEST_F(EmitterTest_529, SetStringFormat_ValidValues_529) {

    EXPECT_TRUE(emitter.SetStringFormat(EMITTER_MANIP::AUTO));

    // Add more valid values if necessary

}



TEST_F(EmitterTest_529, SetBoolFormat_ValidValues_529) {

    EXPECT_TRUE(emitter.SetBoolFormat(EMITTER_MANIP::TRUEFALSE));

    // Add more valid values if necessary

}



TEST_F(EmitterTest_529, SetNullFormat_ValidValues_529) {

    EXPECT_TRUE(emitter.SetNullFormat(EMITTER_MANIP::NULLSTR));

    // Add more valid values if necessary

}



TEST_F(EmitterTest_529, SetIntBase_ValidValues_529) {

    EXPECT_TRUE(emitter.SetIntBase(EMITTER_MANIP::DEC));

    // Add more valid values if necessary

}



TEST_F(EmitterTest_529, SetSeqFormat_ValidValues_529) {

    EXPECT_TRUE(emitter.SetSeqFormat(EMITTER_MANIP::BLOCK));

    // Add more valid values if necessary

}



TEST_F(EmitterTest_529, SetMapFormat_ValidValues_529) {

    EXPECT_TRUE(emitter.SetMapFormat(EMITTER_MANIP::BLOCK));

    // Add more valid values if necessary

}



TEST_F(EmitterTest_529, Write_String_529) {

    emitter.Write("test");

    // Assuming the internal state change is observable through c_str() or size()

    EXPECT_EQ(emitter.c_str(), "test");

}



TEST_F(EmitterTest_529, Write_Bool_529) {

    emitter.Write(true);

    emitter.Write(false);

    // Assuming the internal state change is observable through c_str() or size()

    EXPECT_TRUE(std::string(emitter.c_str()).find("true") != std::string::npos);

    EXPECT_TRUE(std::string(emitter.c_str()).find("false") != std::string::npos);

}



TEST_F(EmitterTest_529, Write_Char_529) {

    emitter.Write('a');

    // Assuming the internal state change is observable through c_str() or size()

    EXPECT_EQ(emitter.c_str(), "a");

}



TEST_F(EmitterTest_529, good_DefaultState_529) {

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_529, GetLastError_NoError_529) {

    EXPECT_EQ(emitter.GetLastError(), "");

}
