#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/Gfx.h"

class GfxTest_1258 : public ::testing::Test {
protected:
    // Set up resources for the tests
    void SetUp() override {
        catalog = new Catalog();
        outputDev = new OutputDev();
        dict = new Dict();
        gfx = new Gfx(nullptr, outputDev, 1, dict, 72.0, 72.0, nullptr, nullptr, 0, nullptr, nullptr, nullptr);
    }

    // Tear down after tests
    void TearDown() override {
        delete gfx;
        delete dict;
        delete outputDev;
        delete catalog;
    }

    // Mocked objects and Gfx object
    Catalog* catalog;
    OutputDev* outputDev;
    Dict* dict;
    Gfx* gfx;
};

// Test for the getState method
TEST_F(GfxTest_1258, GetStateReturnsNonNull_1258) {
    GfxState* state = gfx->getState();
    ASSERT_NE(state, nullptr) << "Expected state to be non-null.";
}

// Test for the saveState method
TEST_F(GfxTest_1258, SaveState_SuccessfulSave_1258) {
    // Given: current state of the gfx
    GfxState* currentState = gfx->getState();

    // When: saving state
    gfx->saveState();

    // Then: the saved state should not be the same as the current state
    GfxState* newState = gfx->getState();
    ASSERT_NE(currentState, newState) << "State should change after save.";
}

// Test for the restoreState method
TEST_F(GfxTest_1258, RestoreState_RestoreState_1258) {
    // Given: a saved state
    gfx->saveState();
    GfxState* savedState = gfx->getState();

    // When: restoring state
    gfx->restoreState();

    // Then: the state should match the saved state
    GfxState* restoredState = gfx->getState();
    ASSERT_EQ(savedState, restoredState) << "State should be restored to the previous state.";
}

// Test for exceptional case when calling getState without proper initialization
TEST_F(GfxTest_1258, GetState_FailsIfUninitialized_1258) {
    // Given: Gfx object without proper initialization
    delete gfx;
    gfx = new Gfx(nullptr, nullptr, 0, nullptr, 0, 0, nullptr, nullptr, 0, nullptr, nullptr, nullptr);

    // When: getting state
    GfxState* state = gfx->getState();

    // Then: Ensure it's a failure (null state expected)
    ASSERT_EQ(state, nullptr) << "State should be null when Gfx is improperly initialized.";
}

// Test for boundary condition with getState when Gfx is newly created
TEST_F(GfxTest_1258, GetState_NewGfxInstance_1258) {
    // Given: a newly created Gfx instance

    // When: getting state
    GfxState* state = gfx->getState();

    // Then: ensure the state is initialized and non-null
    ASSERT_NE(state, nullptr) << "State should be initialized and non-null for a new Gfx instance.";
}