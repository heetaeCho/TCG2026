#include <gtest/gtest.h>

#include "poppler-annot.h"

#include <gmock/gmock.h>



// Mocking external collaborators if necessary

class MockPopplerAnnotScreen {

public:

    MockPopplerAnnotScreen() : action(nullptr) {}

    PopplerAction* action;

};



TEST(PopplerAnnotScreenTest_2111, GetAction_ReturnsStoredAction_2111) {

    MockPopplerAnnotScreen mockAnnot;

    PopplerAction expectedAction;

    mockAnnot.action = &expectedAction;



    PopplerAnnotScreen* annot = reinterpret_cast<PopplerAnnotScreen*>(&mockAnnot);

    EXPECT_EQ(poppler_annot_screen_get_action(annot), &expectedAction);

}



TEST(PopplerAnnotScreenTest_2111, GetAction_ReturnsNullWhenNoActionSet_2111) {

    MockPopplerAnnotScreen mockAnnot;

    mockAnnot.action = nullptr;



    PopplerAnnotScreen* annot = reinterpret_cast<PopplerAnnotScreen*>(&mockAnnot);

    EXPECT_EQ(poppler_annot_screen_get_action(annot), nullptr);

}
