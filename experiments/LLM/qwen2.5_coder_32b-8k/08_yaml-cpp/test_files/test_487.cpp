#include <gtest/gtest.h>

#include "emitterstate.h"



using namespace YAML;



class EmitterStateTest_487 : public ::testing::Test {

protected:

    EmitterState state;

};



TEST_F(EmitterStateTest_487, ClearModifiedSettings_NoModification_487) {

    // No modification is done before calling ClearModifiedSettings

    state.ClearModifiedSettings();

    // Since no changes were made, this should be a no-op and no observable effect can be verified directly.

}



TEST_F(EmitterStateTest_487, ClearModifiedSettings_AfterModification_487) {

    // Assuming some modification is done before calling ClearModifiedSettings

    state.SetAnchor();

    state.ClearModifiedSettings();

    // Since no changes were made, this should reset any internal state related to modifications.

}



TEST_F(EmitterStateTest_487, SetAndGetIndent_Normal_487) {

    std::size_t new_indent = 4;

    state.SetIndent(new_indent, FmtScope::BLOCK);

    EXPECT_EQ(state.GetIndent(), new_indent);

}



TEST_F(EmitterStateTest_487, SetIndent_BoundaryCondition_487) {

    // Test with the minimum possible value

    std::size_t min_indent = 0;

    state.SetIndent(min_indent, FmtScope::BLOCK);

    EXPECT_EQ(state.GetIndent(), min_indent);



    // Test with a larger but still valid value

    std::size_t max_indent = 16; // Arbitrary large number

    state.SetIndent(max_indent, FmtScope::BLOCK);

    EXPECT_EQ(state.GetIndent(), max_indent);

}



TEST_F(EmitterStateTest_487, SetAndGetPreCommentIndent_Normal_487) {

    std::size_t new_pre_comment_indent = 2;

    state.SetPreCommentIndent(new_pre_comment_indent, FmtScope::BLOCK);

    EXPECT_EQ(state.GetPreCommentIndent(), new_pre_comment_indent);

}



TEST_F(EmitterStateTest_487, SetAndGetPostCommentIndent_Normal_487) {

    std::size_t new_post_comment_indent = 2;

    state.SetPostCommentIndent(new_post_comment_indent, FmtScope::BLOCK);

    EXPECT_EQ(state.GetPostCommentIndent(), new_post_comment_indent);

}



TEST_F(EmitterStateTest_487, SetAndGetFloatPrecision_Normal_487) {

    std::size_t new_float_precision = 6;

    state.SetFloatPrecision(new_float_precision, FmtScope::BLOCK);

    EXPECT_EQ(state.GetFloatPrecision(), new_float_precision);

}



TEST_F(EmitterStateTest_487, SetAndGetDoublePrecision_Normal_487) {

    std::size_t new_double_precision = 15;

    state.SetDoublePrecision(new_double_precision, FmtScope::BLOCK);

    EXPECT_EQ(state.GetDoublePrecision(), new_double_precision);

}



TEST_F(EmitterStateTest_487, SetAnchor_CheckState_487) {

    state.SetAnchor();

    // Since there's no direct way to check if an anchor is set without affecting other states,

    // we rely on the internal state consistency.

}



TEST_F(EmitterStateTest_487, SetAlias_CheckState_487) {

    state.SetAlias();

    // Similar to SetAnchor, there's no direct observable effect without affecting other states.

}



TEST_F(EmitterStateTest_487, SetTag_CheckState_487) {

    state.SetTag();

    // Similar to SetAnchor and SetAlias, there's no direct observable effect without affecting other states.

}



TEST_F(EmitterStateTest_487, SetNonContent_CheckState_487) {

    state.SetNonContent();

    // Similar to other setters, this doesn't have a direct observable effect through public interface.

}



TEST_F(EmitterStateTest_487, StartedDoc_EndedDoc_Normal_487) {

    state.StartedDoc();

    // This should setup internal states for the document start

    // No direct way to verify this without checking internal state.



    state.EndedDoc();

    // This should teardown internal states for the document end

    // No direct way to verify this without checking internal state.

}



TEST_F(EmitterStateTest_487, StartedScalar_Normal_487) {

    state.StartedScalar();

    // This should setup internal states for scalar start

    // No direct way to verify this without checking internal state.

}
