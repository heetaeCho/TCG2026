#include <gtest/gtest.h>

#include "GfxState.h"

#include <vector>



class GfxStateTest : public ::testing::Test {

protected:

    GfxState *state;



    void SetUp() override {

        state = new GfxState(300, 300, nullptr, 0, false);

    }



    void TearDown() override {

        delete state;

    }

};



TEST_F(GfxStateTest_595, GetTransferInitiallyEmpty_595) {

    EXPECT_TRUE(state->getTransfer().empty());

}



TEST_F(GfxStateTest_595, SetAndGetTransfer_595) {

    std::vector<std::unique_ptr<Function>> functions;

    // Assuming Function is a class that can be instantiated

    functions.emplace_back(new Function());  // Placeholder for actual instantiation



    state->setTransfer(std::move(functions));



    EXPECT_EQ(state->getTransfer().size(), 1);

}



TEST_F(GfxStateTest_595, SetAndGetTransferMultipleFunctions_595) {

    std::vector<std::unique_ptr<Function>> functions;

    for (int i = 0; i < 3; ++i) {

        functions.emplace_back(new Function());  // Placeholder for actual instantiation

    }



    state->setTransfer(std::move(functions));



    EXPECT_EQ(state->getTransfer().size(), 3);

}



TEST_F(GfxStateTest_595, SetAndGetTransferEmptyVector_595) {

    std::vector<std::unique_ptr<Function>> emptyFunctions;



    state->setTransfer(std::move(emptyFunctions));



    EXPECT_TRUE(state->getTransfer().empty());

}
