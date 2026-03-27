#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include "emitterstate.h"



using namespace YAML;



class EmitterStateTest_445 : public ::testing::Test {

protected:

    EmitterState emitterState;

};



TEST_F(EmitterStateTest_445, GetLastError_Default_ReturnsEmptyString_445) {

    EXPECT_EQ(emitterState.GetLastError(), "");

}



TEST_F(EmitterStateTest_445, SetError_ChangesLastError_445) {

    const std::string testError = "Test Error";

    emitterState.SetError(testError);

    EXPECT_EQ(emitterState.GetLastError(), testError);

}



TEST_F(EmitterStateTest_445, Good_Default_ReturnsTrue_445) {

    EXPECT_TRUE(emitterState.good());

}



TEST_F(EmitterStateTest_445, SetError_MakesGoodFalse_445) {

    emitterState.SetError("Test Error");

    EXPECT_FALSE(emitterState.good());

}



TEST_F(EmitterStateTest_445, SetLocalValue_DoesNotThrowException_445) {

    EXPECT_NO_THROW(emitterState.SetLocalValue(EMITTER_MANIP::BLOCK));

}



TEST_F(EmitterStateTest_445, SetOutputCharset_ValidValue_ReturnsTrue_445) {

    EXPECT_TRUE(emitterState.SetOutputCharset(EMITTER_MANIP::UTF8, FmtScope::GLOBAL));

}



TEST_F(EmitterStateTest_445, SetStringFormat_ValidValue_ReturnsTrue_445) {

    EXPECT_TRUE(emitterState.SetStringFormat(EMITTER_MANIP::HEX, FmtScope::LOCAL));

}



TEST_F(EmitterStateTest_445, SetBoolFormat_ValidValue_ReturnsTrue_445) {

    EXPECT_TRUE(emitterState.SetBoolFormat(EMITTER_MANIP::TRUEFALSE, FmtScope::BLOCK));

}



TEST_F(EmitterStateTest_445, SetBoolLengthFormat_ValidValue_ReturnsTrue_445) {

    EXPECT_TRUE(emitterState.SetBoolLengthFormat(EMITTER_MANIP::LONG, FmtScope::LOCAL));

}



TEST_F(EmitterStateTest_445, SetBoolCaseFormat_ValidValue_ReturnsTrue_445) {

    EXPECT_TRUE(emitterState.SetBoolCaseFormat(EMITTER_MANIP::UPPERCASE, FmtScope::GLOBAL));

}



TEST_F(EmitterStateTest_445, SetNullFormat_ValidValue_ReturnsTrue_445) {

    EXPECT_TRUE(emitterState.SetNullFormat(EMITTER_MANIP::TILDE, FmtScope::BLOCK));

}



TEST_F(EmitterStateTest_445, SetIntFormat_ValidValue_ReturnsTrue_445) {

    EXPECT_TRUE(emitterState.SetIntFormat(EMITTER_MANIP::DECIMAL, FmtScope::LOCAL));

}



TEST_F(EmitterStateTest_445, SetIndent_ValidValue_ReturnsTrue_445) {

    EXPECT_TRUE(emitterState.SetIndent(2, FmtScope::GLOBAL));

}



TEST_F(EmitterStateTest_445, SetPreCommentIndent_ValidValue_ReturnsTrue_445) {

    EXPECT_TRUE(emitterState.SetPreCommentIndent(1, FmtScope::BLOCK));

}



TEST_F(EmitterStateTest_445, SetPostCommentIndent_ValidValue_ReturnsTrue_445) {

    EXPECT_TRUE(emitterState.SetPostCommentIndent(3, FmtScope::LOCAL));

}



TEST_F(EmitterStateTest_445, SetFlowType_ValidValue_ReturnsTrue_445) {

    EXPECT_TRUE(emitterState.SetFlowType(GroupType::BLOCK, EMITTER_MANIP::FLOW, FmtScope::GLOBAL));

}



TEST_F(EmitterStateTest_445, SetMapKeyFormat_ValidValue_ReturnsTrue_445) {

    EXPECT_TRUE(emitterState.SetMapKeyFormat(EMITTER_MANIP::AUTO, FmtScope::LOCAL));

}



TEST_F(EmitterStateTest_445, SetFloatPrecision_ValidValue_ReturnsTrue_445) {

    EXPECT_TRUE(emitterState.SetFloatPrecision(6, FmtScope::BLOCK));

}



TEST_F(EmitterStateTest_445, SetDoublePrecision_ValidValue_ReturnsTrue_445) {

    EXPECT_TRUE(emitterState.SetDoublePrecision(10, FmtScope::GLOBAL));

}



TEST_F(EmitterStateTest_445, StartedDoc_DoesNotThrowException_445) {

    EXPECT_NO_THROW(emitterState.StartedDoc());

}



TEST_F(EmitterStateTest_445, EndedDoc_DoesNotThrowException_445) {

    EXPECT_NO_THROW(emitterState.EndedDoc());

}



TEST_F(EmitterStateTest_445, StartedScalar_DoesNotThrowException_445) {

    EXPECT_NO_THROW(emitterState.StartedScalar());

}



TEST_F(EmitterStateTest_445, StartedGroup_ValidType_DoesNotThrowException_445) {

    EXPECT_NO_THROW(emitterState.StartedGroup(GroupType::BLOCK));

}



TEST_F(EmitterStateTest_445, EndedGroup_ValidType_DoesNotThrowException_445) {

    EXPECT_NO_THROW(emitterState.EndedGroup(GroupType::BLOCK));

}



TEST_F(EmitterStateTest_445, CurIndent_Default_ReturnsZero_445) {

    EXPECT_EQ(emitterState.CurIndent(), 0);

}



TEST_F(EmitterStateTest_445, HasAnchor_Default_ReturnsFalse_445) {

    EXPECT_FALSE(emitterState.HasAnchor());

}



TEST_F(EmitterStateTest_445, HasAlias_Default_ReturnsFalse_445) {

    EXPECT_FALSE(emitterState.HasAlias());

}



TEST_F(EmitterStateTest_445, HasTag_Default_ReturnsFalse_445) {

    EXPECT_FALSE(emitterState.HasTag());

}



TEST_F(EmitterStateTest_445, HasBegunNode_Default_ReturnsFalse_445) {

    EXPECT_FALSE(emitterState.HasBegunNode());

}



TEST_F(EmitterStateTest_445, HasBegunContent_Default_ReturnsFalse_445) {

    EXPECT_FALSE(emitterState.HasBegunContent());

}
