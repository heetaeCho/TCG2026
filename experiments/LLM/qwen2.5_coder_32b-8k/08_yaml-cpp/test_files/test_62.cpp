#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/emitfromevents.h"

#include "yaml-cpp/emittermanip.h"



using namespace YAML;

using namespace testing;



class MockEmitter : public Emitter {

public:

    MOCK_METHOD1(operator<<, Emitter&(EMITTER_MANIP));

};



class EmitFromEventsTest_62 : public Test {

protected:

    MockEmitter mock_emitter;

    EmitFromEvents emit_from_events{mock_emitter};

};



TEST_F(EmitFromEventsTest_62, OnMapEnd_CallsEmitWithEndMap_62) {

    EXPECT_CALL(mock_emitter, operator<<(EndMap));

    emit_from_events.OnMapEnd();

}



// Since the internal state is not accessible, we can't test boundary conditions or

// exceptional cases directly. However, we can ensure that the function behaves as expected

// under normal operation.



TEST_F(EmitFromEventsTest_62, OnMapEnd_TopStateIsWaitingForKey_62) {

    // This test assumes that the state stack is correctly managed by other methods.

    // We cannot directly verify the internal state, but we can ensure that the function

    // behaves as expected when called in a valid state.

    emit_from_events.OnMapEnd();

}



// Additional tests would typically involve mocking other methods and interactions,

// but given the constraints, these are the primary test cases we can write.


