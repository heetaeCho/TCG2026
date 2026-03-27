#include <gtest/gtest.h>

#include "poppler-annot.h"

#include "Annot.h"



// Mock class to simulate PopplerAnnotText

class MockPopplerAnnotText : public _PopplerAnnotText {

public:

    MOCK_METHOD(AnnotTextState, getState, (), (const));

};



TEST_F(PopplerAnnotTextTest_2093, GetStateReturnsMarked_2093) {

    MockPopplerAnnotText mockAnnot;

    EXPECT_CALL(mockAnnot, getState()).WillOnce(::testing::Return(AnnotText::stateMarked));

    EXPECT_EQ(poppler_annot_text_get_state(reinterpret_cast<PopplerAnnotText*>(&mockAnnot)), POPPLER_ANNOT_TEXT_STATE_MARKED);

}



TEST_F(PopplerAnnotTextTest_2093, GetStateReturnsUnmarked_2093) {

    MockPopplerAnnotText mockAnnot;

    EXPECT_CALL(mockAnnot, getState()).WillOnce(::testing::Return(AnnotText::stateUnmarked));

    EXPECT_EQ(poppler_annot_text_get_state(reinterpret_cast<PopplerAnnotText*>(&mockAnnot)), POPPLER_ANNOT_TEXT_STATE_UNMARKED);

}



TEST_F(PopplerAnnotTextTest_2093, GetStateReturnsAccepted_2093) {

    MockPopplerAnnotText mockAnnot;

    EXPECT_CALL(mockAnnot, getState()).WillOnce(::testing::Return(AnnotText::stateAccepted));

    EXPECT_EQ(poppler_annot_text_get_state(reinterpret_cast<PopplerAnnotText*>(&mockAnnot)), POPPLER_ANNOT_TEXT_STATE_ACCEPTED);

}



TEST_F(PopplerAnnotTextTest_2093, GetStateReturnsRejected_2093) {

    MockPopplerAnnotText mockAnnot;

    EXPECT_CALL(mockAnnot, getState()).WillOnce(::testing::Return(AnnotText::stateRejected));

    EXPECT_EQ(poppler_annot_text_get_state(reinterpret_cast<PopplerAnnotText*>(&mockAnnot)), POPPLER_ANNOT_TEXT_STATE_REJECTED);

}



TEST_F(PopplerAnnotTextTest_2093, GetStateReturnsCancelled_2093) {

    MockPopplerAnnotText mockAnnot;

    EXPECT_CALL(mockAnnot, getState()).WillOnce(::testing::Return(AnnotText::stateCancelled));

    EXPECT_EQ(poppler_annot_text_get_state(reinterpret_cast<PopplerAnnotText*>(&mockAnnot)), POPPLER_ANNOT_TEXT_STATE_CANCELLED);

}



TEST_F(PopplerAnnotTextTest_2093, GetStateReturnsCompleted_2093) {

    MockPopplerAnnotText mockAnnot;

    EXPECT_CALL(mockAnnot, getState()).WillOnce(::testing::Return(AnnotText::stateCompleted));

    EXPECT_EQ(poppler_annot_text_get_state(reinterpret_cast<PopplerAnnotText*>(&mockAnnot)), POPPLER_ANNOT_TEXT_STATE_COMPLETED);

}



TEST_F(PopplerAnnotTextTest_2093, GetStateReturnsNone_2093) {

    MockPopplerAnnotText mockAnnot;

    EXPECT_CALL(mockAnnot, getState()).WillOnce(::testing::Return(AnnotText::stateNone));

    EXPECT_EQ(poppler_annot_text_get_state(reinterpret_cast<PopplerAnnotText*>(&mockAnnot)), POPPLER_ANNOT_TEXT_STATE_NONE);

}



TEST_F(PopplerAnnotTextTest_2093, GetStateReturnsUnknown_2093) {

    MockPopplerAnnotText mockAnnot;

    EXPECT_CALL(mockAnnot, getState()).WillOnce(::testing::Return(AnnotText::stateUnknown));

    EXPECT_EQ(poppler_annot_text_get_state(reinterpret_cast<PopplerAnnotText*>(&mockAnnot)), POPPLER_ANNOT_TEXT_STATE_UNKNOWN);

}



TEST_F(PopplerAnnotTextTest_2093, GetStateReturnsDefaultOnUnsupportedValue_2093) {

    MockPopplerAnnotText mockAnnot;

    EXPECT_CALL(mockAnnot, getState()).WillOnce(::testing::Return(static_cast<AnnotTextState>(10))); // Unsupported value

    EXPECT_EQ(poppler_annot_text_get_state(reinterpret_cast<PopplerAnnotText*>(&mockAnnot)), POPPLER_ANNOT_TEXT_STATE_UNKNOWN);

}



TEST_F(PopplerAnnotTextTest_2093, GetStateHandlesNullPointer_2093) {

    PopplerAnnotText* nullPtr = nullptr;

    EXPECT_EQ(poppler_annot_text_get_state(nullPtr), POPPLER_ANNOT_TEXT_STATE_UNKNOWN);

}
