#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/emitfromevents.h"

#include "yaml-cpp/emitter.h"



using namespace YAML;



class MockEmitter : public Emitter {

public:

    MOCK_METHOD1(operator<<, Emitter&(EMITTER_MANIP manip));

};



class EmitFromEventsTest_61 : public ::testing::Test {

protected:

    void SetUp() override {

        mock_emitter = std::make_unique<MockEmitter>();

        emit_from_events = std::make_unique<EmitFromEvents>(*mock_emitter);

    }



    std::unique_ptr<MockEmitter> mock_emitter;

    std::unique_ptr<EmitFromEvents> emit_from_events;

};



TEST_F(EmitFromEventsTest_61, OnSequenceEnd_CallsEmitterWithEndSeq_61) {

    EXPECT_CALL(*mock_emitter, operator<<(EndSeq));

    emit_from_events->OnSequenceEnd();

}



// Boundary conditions

TEST_F(EmitFromEventsTest_61, OnSequenceEnd_StateStackNotEmpty_61) {

    // Assuming the stack is not empty before calling OnSequenceEnd

    mock_emitter->m_stateStack.push(State::WaitingForSequenceEntry);

    EXPECT_CALL(*mock_emitter, operator<<(EndSeq));

    emit_from_events->OnSequenceEnd();

}



// Exceptional or error cases (if observable through the interface)

TEST_F(EmitFromEventsTest_61, OnSequenceEnd_StateStackEmpty_ThrowsAssertionFailure_61) {

    // Assuming the stack is empty before calling OnSequenceEnd

    EXPECT_DEATH(emit_from_events->OnSequenceEnd(), ".*assertion failed.*");

}



// Verification of external interactions (e.g., mock handler calls and their parameters)

TEST_F(EmitFromEventsTest_61, OnSequenceEnd_VerifyStateStackPoppedOnce_61) {

    mock_emitter->m_stateStack.push(State::WaitingForSequenceEntry);

    EXPECT_CALL(*mock_emitter, operator<<(EndSeq));

    emit_from_events->OnSequenceEnd();

    EXPECT_TRUE(mock_emitter->m_stateStack.empty());

}
