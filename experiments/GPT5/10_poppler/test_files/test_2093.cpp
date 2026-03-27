#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler-annot.h"
#include "Annot.h"

using ::testing::Return;

// Mock class for PopplerAnnotText to simulate the behavior of AnnotText class.
class MockPopplerAnnotText : public PopplerAnnotText {
public:
    MOCK_METHOD(AnnotTextState, getState, (), (const));
};

class PopplerAnnotTextTest_2093 : public ::testing::Test {
protected:
    MockPopplerAnnotText* poppler_annot;

    void SetUp() override {
        poppler_annot = new MockPopplerAnnotText();
    }

    void TearDown() override {
        delete poppler_annot;
    }
};

// Test for normal operation: AnnotText state is 'stateMarked'.
TEST_F(PopplerAnnotTextTest_2093, GetStateMarked_2093) {
    EXPECT_CALL(*poppler_annot, getState())
        .WillOnce(Return(AnnotText::stateMarked));

    PopplerAnnotTextState state = poppler_annot_text_get_state(poppler_annot);

    EXPECT_EQ(state, POPPLER_ANNOT_TEXT_STATE_MARKED);
}

// Test for normal operation: AnnotText state is 'stateUnmarked'.
TEST_F(PopplerAnnotTextTest_2093, GetStateUnmarked_2093) {
    EXPECT_CALL(*poppler_annot, getState())
        .WillOnce(Return(AnnotText::stateUnmarked));

    PopplerAnnotTextState state = poppler_annot_text_get_state(poppler_annot);

    EXPECT_EQ(state, POPPLER_ANNOT_TEXT_STATE_UNMARKED);
}

// Test for normal operation: AnnotText state is 'stateAccepted'.
TEST_F(PopplerAnnotTextTest_2093, GetStateAccepted_2093) {
    EXPECT_CALL(*poppler_annot, getState())
        .WillOnce(Return(AnnotText::stateAccepted));

    PopplerAnnotTextState state = poppler_annot_text_get_state(poppler_annot);

    EXPECT_EQ(state, POPPLER_ANNOT_TEXT_STATE_ACCEPTED);
}

// Test for normal operation: AnnotText state is 'stateRejected'.
TEST_F(PopplerAnnotTextTest_2093, GetStateRejected_2093) {
    EXPECT_CALL(*poppler_annot, getState())
        .WillOnce(Return(AnnotText::stateRejected));

    PopplerAnnotTextState state = poppler_annot_text_get_state(poppler_annot);

    EXPECT_EQ(state, POPPLER_ANNOT_TEXT_STATE_REJECTED);
}

// Test for boundary condition: AnnotText state is 'stateUnknown'.
TEST_F(PopplerAnnotTextTest_2093, GetStateUnknown_2093) {
    EXPECT_CALL(*poppler_annot, getState())
        .WillOnce(Return(AnnotText::stateUnknown));

    PopplerAnnotTextState state = poppler_annot_text_get_state(poppler_annot);

    EXPECT_EQ(state, POPPLER_ANNOT_TEXT_STATE_UNKNOWN);
}

// Test for exceptional case: Unsupported AnnotText state.
TEST_F(PopplerAnnotTextTest_2093, GetStateUnsupported_2093) {
    EXPECT_CALL(*poppler_annot, getState())
        .WillOnce(Return(static_cast<AnnotTextState>(-1)));

    PopplerAnnotTextState state = poppler_annot_text_get_state(poppler_annot);

    EXPECT_EQ(state, POPPLER_ANNOT_TEXT_STATE_UNKNOWN);
}

// Test for normal operation: AnnotText state is 'stateCompleted'.
TEST_F(PopplerAnnotTextTest_2093, GetStateCompleted_2093) {
    EXPECT_CALL(*poppler_annot, getState())
        .WillOnce(Return(AnnotText::stateCompleted));

    PopplerAnnotTextState state = poppler_annot_text_get_state(poppler_annot);

    EXPECT_EQ(state, POPPLER_ANNOT_TEXT_STATE_COMPLETED);
}

// Test for normal operation: AnnotText state is 'stateCancelled'.
TEST_F(PopplerAnnotTextTest_2093, GetStateCancelled_2093) {
    EXPECT_CALL(*poppler_annot, getState())
        .WillOnce(Return(AnnotText::stateCancelled));

    PopplerAnnotTextState state = poppler_annot_text_get_state(poppler_annot);

    EXPECT_EQ(state, POPPLER_ANNOT_TEXT_STATE_CANCELLED);
}

// Test for normal operation: AnnotText state is 'stateNone'.
TEST_F(PopplerAnnotTextTest_2093, GetStateNone_2093) {
    EXPECT_CALL(*poppler_annot, getState())
        .WillOnce(Return(AnnotText::stateNone));

    PopplerAnnotTextState state = poppler_annot_text_get_state(poppler_annot);

    EXPECT_EQ(state, POPPLER_ANNOT_TEXT_STATE_NONE);
}