#include <gtest/gtest.h>

#include "yaml-cpp/src/emitterstate.h"

#include "yaml-cpp/emittermanip.h"



using namespace YAML;



class EmitterStateTest_500 : public ::testing::Test {

protected:

    EmitterState emitterState;

};



TEST_F(EmitterStateTest_500, GetFlowType_CurGroupFlowIsFlow_ReturnsFlow_500) {

    // Arrange

    emitterState.ForceFlow();



    // Act & Assert

    EXPECT_EQ(emitterState.GetFlowType(GroupType::Seq), Flow);

}



TEST_F(EmitterStateTest_500, GetFlowType_GroupTypeSeqAndCurGroupNotFlow_ReturnsSeqFormat_500) {

    // Arrange

    emitterState.m_seqFmt.set(EMITTER_MANIP::SingleQuoted);



    // Act & Assert

    EXPECT_EQ(emitterState.GetFlowType(GroupType::Seq), EMITTER_MANIP::SingleQuoted);

}



TEST_F(EmitterStateTest_500, GetFlowType_GroupTypeMapAndCurGroupNotFlow_ReturnsMapFormat_500) {

    // Arrange

    emitterState.m_mapFmt.set(EMITTER_MANIP::DoubleQuoted);



    // Act & Assert

    EXPECT_EQ(emitterState.GetFlowType(GroupType::Map), EMITTER_MANIP::DoubleQuoted);

}



TEST_F(EmitterStateTest_500, GetFlowType_GroupTypeInvalid_ReturnsDefault_500) {

    // Arrange

    emitterState.m_seqFmt.set(EMITTER_MANIP::SingleQuoted);

    emitterState.m_mapFmt.set(EMITTER_MANIP::DoubleQuoted);



    // Act & Assert

    EXPECT_EQ(emitterState.GetFlowType(static_cast<GroupType::value>(-1)), EMITTER_MANIP::Block); // Assuming invalid GroupType returns Block as default

}
