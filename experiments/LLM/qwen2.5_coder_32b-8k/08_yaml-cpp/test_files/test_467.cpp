#include <gtest/gtest.h>

#include "emitterstate.h"



using namespace YAML;



class EmitterStateTest_467 : public ::testing::Test {

protected:

    EmitterState emitter_state;

};



TEST_F(EmitterStateTest_467, SetLocalValue_NormalOperation_467) {

    EMITTER_MANIP value = EMITTER_MANIP::Block;  // Example value

    emitter_state.SetLocalValue(value);

    // Since we cannot access internal state directly, we assume that if no exception is thrown and the object remains in a good state, it works.

    EXPECT_TRUE(emitter_state.good());

}



TEST_F(EmitterStateTest_467, SetLocalValue_BoundaryConditions_467) {

    EMITTER_MANIP min_value = static_cast<EMITTER_MANIP>(0);  // Assuming enum starts from 0

    EMITTER_MANIP max_value = EMITTER_MANIP::LastManip;       // Example boundary value



    emitter_state.SetLocalValue(min_value);

    EXPECT_TRUE(emitter_state.good());



    emitter_state.SetLocalValue(max_value);

    EXPECT_TRUE(emitter_state.good());

}



TEST_F(EmitterStateTest_467, SetLocalValue_ExceptionalCases_467) {

    // Assuming invalid enum value is out of range

    EMITTER_MANIP invalid_value = static_cast<EMITTER_MANIP>(-1);  // Invalid value



    emitter_state.SetLocalValue(invalid_value);

    EXPECT_FALSE(emitter_state.good());

}



TEST_F(EmitterStateTest_467, SetLocalValue_VerifyExternalInteractions_467) {

    // Since the class does not have external collaborators in the provided interface,

    // we cannot verify external interactions. This test is a placeholder.

    EMITTER_MANIP value = EMITTER_MANIP::Block;  // Example value

    emitter_state.SetLocalValue(value);

    EXPECT_TRUE(emitter_state.good());

}
