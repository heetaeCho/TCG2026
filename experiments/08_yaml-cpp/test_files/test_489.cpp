#include <gtest/gtest.h>

#include "yaml-cpp/src/emitterstate.h"



using namespace YAML;



class EmitterStateTest : public ::testing::Test {

protected:

    EmitterState emitter_state;

};



TEST_F(EmitterStateTest_489, SetOutputCharset_ValidValues_LocalScope_ReturnsTrue_489) {

    EXPECT_TRUE(emitter_state.SetOutputCharset(EmitNonAscii, FmtScope::Local));

    EXPECT_TRUE(emitter_state.SetOutputCharset(EscapeNonAscii, FmtScope::Local));

    EXPECT_TRUE(emitter_state.SetOutputCharset(EscapeAsJson, FmtScope::Local));

}



TEST_F(EmitterStateTest_489, SetOutputCharset_ValidValues_GlobalScope_ReturnsTrue_489) {

    EXPECT_TRUE(emitter_state.SetOutputCharset(EmitNonAscii, FmtScope::Global));

    EXPECT_TRUE(emitter_state.SetOutputCharset(EscapeNonAscii, FmtScope::Global));

    EXPECT_TRUE(emitter_state.SetOutputCharset(EscapeAsJson, FmtScope::Global));

}



TEST_F(EmitterStateTest_489, SetOutputCharset_InvalidValue_ReturnsFalse_489) {

    EXPECT_FALSE(emitter_state.SetOutputCharset(static_cast<EMITTER_MANIP>(255), FmtScope::Local));

    EXPECT_FALSE(emitter_state.SetOutputCharset(static_cast<EMITTER_MANIP>(255), FmtScope::Global));

}



TEST_F(EmitterStateTest_489, SetOutputCharset_Auto_ReturnsFalse_489) {

    EXPECT_FALSE(emitter_state.SetOutputCharset(Auto, FmtScope::Local));

    EXPECT_FALSE(emitter_state.SetOutputCharset(Auto, FmtScope::Global));

}



TEST_F(EmitterStateTest_489, SetOutputCharset_TagByKind_ReturnsFalse_489) {

    EXPECT_FALSE(emitter_state.SetOutputCharset(TagByKind, FmtScope::Local));

    EXPECT_FALSE(emitter_state.SetOutputCharset(TagByKind, FmtScope::Global));

}



TEST_F(EmitterStateTest_489, SetOutputCharset_Newline_ReturnsFalse_489) {

    EXPECT_FALSE(emitter_state.SetOutputCharset(Newline, FmtScope::Local));

    EXPECT_FALSE(emitter_state.SetOutputCharset(Newline, FmtScope::Global));

}
