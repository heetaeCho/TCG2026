#include <gtest/gtest.h>

#include "emitterstate.h"



class EmitterStateTest : public ::testing::Test {

protected:

    YAML::EmitterState emitter_state;

};



TEST_F(EmitterStateTest_444, GoodInitiallyTrue_444) {

    EXPECT_TRUE(emitter_state.good());

}



TEST_F(EmitterStateTest_444, SetErrorChangesGoodToFalse_444) {

    emitter_state.SetError("Test error");

    EXPECT_FALSE(emitter_state.good());

}



TEST_F(EmitterStateTest_444, GetLastErrorReturnsSetError_444) {

    const std::string test_error = "Another test error";

    emitter_state.SetError(test_error);

    EXPECT_EQ(emitter_state.GetLastError(), test_error);

}



TEST_F(EmitterStateTest_444, SetLocalValueDoesNotAffectGood_444) {

    emitter_state.SetLocalValue(EMITTER_MANIP::BlockStyle);

    EXPECT_TRUE(emitter_state.good());

}



TEST_F(EmitterStateTest_444, SetOutputCharsetWithValidValueReturnsTrue_444) {

    EXPECT_TRUE(emitter_state.SetOutputCharset(EMITTER_MANIP::Utf8, FmtScope::Local));

}



TEST_F(EmitterStateTest_444, SetStringFormatWithValidValueReturnsTrue_444) {

    EXPECT_TRUE(emitter_state.SetStringFormat(EMITTER_MANIP::Literal, FmtScope::Global));

}



TEST_F(EmitterStateTest_444, SetBoolFormatWithValidValueReturnsTrue_444) {

    EXPECT_TRUE(emitter_state.SetBoolFormat(EMITTER_MANIP::TrueFalse, FmtScope::Local));

}



TEST_F(EmitterStateTest_444, SetBoolLengthFormatWithValidValueReturnsTrue_444) {

    EXPECT_TRUE(emitter_state.SetBoolLengthFormat(EMITTER_MANIP::Long, FmtScope::Global));

}



TEST_F(EmitterStateTest_444, SetBoolCaseFormatWithValidValueReturnsTrue_444) {

    EXPECT_TRUE(emitter_state.SetBoolCaseFormat(EMITTER_MANIP::Lowercase, FmtScope::Local));

}



TEST_F(EmitterStateTest_444, SetNullFormatWithValidValueReturnsTrue_444) {

    EXPECT_TRUE(emitter_state.SetNullFormat(EMITTER_MANIP::Tilde, FmtScope::Global));

}



TEST_F(EmitterStateTest_444, SetIntFormatWithValidValueReturnsTrue_444) {

    EXPECT_TRUE(emitter_state.SetIntFormat(EMITTER_MANIP::Dec, FmtScope::Local));

}



TEST_F(EmitterStateTest_444, SetIndentWithinRangeReturnsTrue_444) {

    EXPECT_TRUE(emitter_state.SetIndent(2, FmtScope::Global));

}



TEST_F(EmitterStateTest_444, SetPreCommentIndentWithValidValueReturnsTrue_444) {

    EXPECT_TRUE(emitter_state.SetPreCommentIndent(1, FmtScope::Local));

}



TEST_F(EmitterStateTest_444, SetPostCommentIndentWithValidValueReturnsTrue_444) {

    EXPECT_TRUE(emitter_state.SetPostCommentIndent(1, FmtScope::Global));

}



TEST_F(EmitterStateTest_444, SetFlowTypeWithValidGroupAndValueReturnsTrue_444) {

    EXPECT_TRUE(emitter_state.SetFlowType(GroupType::Sequence, EMITTER_MANIP::BlockStyle, FmtScope::Local));

}



TEST_F(EmitterStateTest_444, SetMapKeyFormatWithValidValueReturnsTrue_444) {

    EXPECT_TRUE(emitter_state.SetMapKeyFormat(EMITTER_MANIP::Plain, FmtScope::Global));

}



TEST_F(EmitterStateTest_444, SetFloatPrecisionWithValidValueReturnsTrue_444) {

    EXPECT_TRUE(emitter_state.SetFloatPrecision(6, FmtScope::Local));

}



TEST_F(EmitterStateTest_444, SetDoublePrecisionWithValidValueReturnsTrue_444) {

    EXPECT_TRUE(emitter_state.SetDoublePrecision(15, FmtScope::Global));

}
