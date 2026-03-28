#include <gtest/gtest.h>

#include "TestProjects/re2/re2/prog.h"



namespace re2 {

    class ProgTest_113 : public ::testing::Test {

    protected:

        Prog prog;

    };



    TEST_F(ProgTest_113, SetStartAndGetStart_NormalOperation_113) {

        int start = 5;

        prog.set_start(start);

        EXPECT_EQ(prog.start(), start);

    }



    TEST_F(ProgTest_113, SetStartBoundaryCondition_Zero_113) {

        prog.set_start(0);

        EXPECT_EQ(prog.start(), 0);

    }



    TEST_F(ProgTest_113, SetStartBoundaryCondition_MaxInt_113) {

        prog.set_start(INT_MAX);

        EXPECT_EQ(prog.start(), INT_MAX);

    }



    TEST_F(ProgTest_113, StartDefaultValue_113) {

        Prog new_prog;

        EXPECT_EQ(new_prog.start(), 0);

    }



} // namespace re2
