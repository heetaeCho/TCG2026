#include <gtest/gtest.h>

#include <yaml-cpp/emitter.h>



using namespace YAML;



class EmitterTest_537 : public ::testing::Test {

protected:

    std::ostringstream oss;

    Emitter emitter;

    Emitter streamEmitter{oss};



    EmitterTest_537() : emitter(), streamEmitter(oss) {}

};



TEST_F(EmitterTest_537, WriteChar_NormalOperation_537) {

    char ch = 'A';

    streamEmitter.Write(ch);

    EXPECT_EQ(oss.str(), "A");

}



TEST_F(EmitterTest_537, WriteChar_BoundaryCondition_EmptyStream_537) {

    emitter.Write('B');

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_537, WriteChar_ErrorCase_NotGoodEmitter_537) {

    emitter.m_pState->SetError("Forced error");

    Emitter& result = emitter.Write('C');

    EXPECT_EQ(&result, &emitter);

    EXPECT_FALSE(emitter.good());

}



TEST_F(EmitterTest_537, WriteChar_VerifyExternalInteractions_NotGoodEmitter_537) {

    emitter.m_pState->SetError("Forced error");

    Emitter& result = emitter.Write('D');

    EXPECT_EQ(&result, &emitter);

    EXPECT_FALSE(emitter.good());

}



TEST_F(EmitterTest_537, WriteChar_VerifyExternalInteractions_StreamEmitter_537) {

    streamEmitter.Write('E');

    EXPECT_TRUE(streamEmitter.good());

    EXPECT_EQ(oss.str(), "E");

}
