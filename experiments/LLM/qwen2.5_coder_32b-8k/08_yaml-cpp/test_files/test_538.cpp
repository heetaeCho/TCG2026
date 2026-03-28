#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/emitter.h"

#include "yaml-cpp/emittermanip.h"



namespace YAML {

    class MockEmitterState : public EmitterState {

    public:

        MOCK_METHOD(bool, HasAnchor, (), (const));

        MOCK_METHOD(bool, HasTag, (), (const));

        MOCK_METHOD(void, SetError, (const std::string&), ());

        MOCK_METHOD(void, SetAlias, (), ());

    };

}



class MockEmitter : public YAML::Emitter {

public:

    MockEmitter(std::ostream &stream) : YAML::Emitter(stream) {}



    MOCK_METHOD0(good, bool());

};



using namespace YAML;



class EmitterTest_538 : public ::testing::Test {

protected:

    void SetUp() override {

        // Redirect the private m_pState to our mock object

        emitter.m_pState.reset(new MockEmitterState());



        // Capture the output stream for verification if needed

        std::ostringstream oss;

        emitter = MockEmitter(oss);

    }



    MockEmitter emitter;

};



TEST_F(EmitterTest_538, WriteAlias_NormalOperation_538) {

    _Alias alias("alias_name");

    EXPECT_CALL(*static_cast<MockEmitterState*>(emitter.m_pState.get()), HasAnchor()).WillOnce(::testing::Return(false));

    EXPECT_CALL(*static_cast<MockEmitterState*>(emitter.m_pState.get()), HasTag()).WillOnce(::testing::Return(false));



    emitter.Write(alias);



    // Assuming Write should return a good emitter if no errors occur

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_538, WriteAlias_BoundaryCondition_EmptyString_538) {

    _Alias alias("");

    EXPECT_CALL(*static_cast<MockEmitterState*>(emitter.m_pState.get()), HasAnchor()).WillOnce(::testing::Return(false));

    EXPECT_CALL(*static_cast<MockEmitterState*>(emitter.m_pState.get()), HasTag()).WillOnce(::testing::Return(false));



    emitter.Write(alias);



    // Assuming Write should return a good emitter even with an empty string

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_538, WriteAlias_ErrorCase_HasAnchor_538) {

    _Alias alias("alias_name");

    EXPECT_CALL(*static_cast<MockEmitterState*>(emitter.m_pState.get()), HasAnchor()).WillOnce(::testing::Return(true));

    EXPECT_CALL(*static_cast<MockEmitterState*>(emitter.m_pState.get()), SetError(ErrorMsg::INVALID_ALIAS)).Times(1);



    emitter.Write(alias);



    // Expecting the emitter to be in a bad state due to the error

    EXPECT_FALSE(emitter.good());

}



TEST_F(EmitterTest_538, WriteAlias_ErrorCase_HasTag_538) {

    _Alias alias("alias_name");

    EXPECT_CALL(*static_cast<MockEmitterState*>(emitter.m_pState.get()), HasAnchor()).WillOnce(::testing::Return(false));

    EXPECT_CALL(*static_cast<MockEmitterState*>(emitter.m_pState.get()), HasTag()).WillOnce(::testing::Return(true));

    EXPECT_CALL(*static_cast<MockEmitterState*>(emitter.m_pState.get()), SetError(ErrorMsg::INVALID_ALIAS)).Times(1);



    emitter.Write(alias);



    // Expecting the emitter to be in a bad state due to the error

    EXPECT_FALSE(emitter.good());

}



TEST_F(EmitterTest_538, WriteAlias_ErrorCase_WriteFailure_538) {

    _Alias alias("alias_name");

    EXPECT_CALL(*static_cast<MockEmitterState*>(emitter.m_pState.get()), HasAnchor()).WillOnce(::testing::Return(false));

    EXPECT_CALL(*static_cast<MockEmitterState*>(emitter.m_pState.get()), HasTag()).WillOnce(::testing::Return(false));



    // Mock the Utils::WriteAlias function to fail

    bool (*original_WriteAlias)(std::ostream&, const char*, std::size_t) = Utils::WriteAlias;

    Utils::WriteAlias = [](std::ostream&, const char*, std::size_t) -> bool { return false; };



    emitter.Write(alias);



    // Restore the original function pointer

    Utils::WriteAlias = original_WriteAlias;



    EXPECT_CALL(*static_cast<MockEmitterState*>(emitter.m_pState.get()), SetError(ErrorMsg::INVALID_ALIAS)).Times(1);

    EXPECT_FALSE(emitter.good());

}



TEST_F(EmitterTest_538, WriteAlias_VerifyExternalInteractions_538) {

    _Alias alias("alias_name");

    EXPECT_CALL(*static_cast<MockEmitterState*>(emitter.m_pState.get()), HasAnchor()).WillOnce(::testing::Return(false));

    EXPECT_CALL(*static_cast<MockEmitterState*>(emitter.m_pState.get()), HasTag()).WillOnce(::testing::Return(false));

    EXPECT_CALL(*static_cast<MockEmitterState*>(emitter.m_pState.get()), SetAlias()).Times(1);



    emitter.Write(alias);



    // Assuming the SetAlias should be called if no errors occur

    EXPECT_TRUE(emitter.good());

}
