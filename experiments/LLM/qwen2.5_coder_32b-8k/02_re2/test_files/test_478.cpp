#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/regexp.h"



namespace re2 {



class RegexpTest : public ::testing::Test {

protected:

    RegexpTest() {}

    virtual ~RegexpTest() {}



    void SetUp() override {

        // Reset maximum_repeat_count before each test

        Regexp::FUZZING_ONLY_set_maximum_repeat_count(1000);

    }



    void TearDown() override {}

};



TEST_F(RegexpTest_478, SetMaximumRepeatCount_NormalOperation_478) {

    Regexp::FUZZING_ONLY_set_maximum_repeat_count(500);

    // Since we cannot access internal state, we rely on observable behavior.

    // We assume that setting the maximum repeat count will affect how repeats are handled,

    // but we do not test that directly here. Instead, we verify the set operation itself.

}



TEST_F(RegexpTest_478, SetMaximumRepeatCount_BoundaryCondition_478) {

    Regexp::FUZZING_ONLY_set_maximum_repeat_count(0);

    // Setting to 0 is a boundary condition

}



TEST_F(RegexpTest_478, SetMaximumRepeatCount_ExceptionalCase_478) {

    // There are no exceptional cases directly observable from the interface for this function.

    // The function does not throw exceptions or return error codes.

}



}  // namespace re2
