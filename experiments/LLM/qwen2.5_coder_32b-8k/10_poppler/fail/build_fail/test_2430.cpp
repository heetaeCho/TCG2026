#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-page.h"

#include "poppler-private.h"

#include "PageTransition.h"



class PopplerPageMock : public Page {

public:

    MOCK_METHOD(Object, getTrans, (), (const, override));

};



TEST(PopplerPageGetTransitionTest_2430, NormalOperationReplaceType_2430) {

    auto page = std::make_unique<PopplerPageMock>();

    Object transObj;

    EXPECT_CALL(*page, getTrans()).WillOnce(::testing::Return(transObj));



    PageTransition* mockPageTransition = new PageTransition(&transObj);

    ON_CALL(mockPageTransition, isOk()).WillByDefault(::testing::Return(true));

    ON_CALL(mockPageTransition, getType()).WillByDefault(::testing::Return(transitionReplace));

    ON_CALL(mockPageTransition, getAlignment()).WillByDefault(::testing::Return(transitionHorizontal));

    ON_CALL(mockPageTransition, getDirection()).WillByDefault(::testing::Return(transitionInward));

    ON_CALL(mockPageTransition, getDuration()).WillByDefault(::testing::Return(2.0));

    ON_CALL(mockPageTransition, getAngle()).WillByDefault(::testing::Return(45));

    ON_CALL(mockPageTransition, getScale()).WillByDefault(::testing::Return(1.5));

    ON_CALL(mockPageTransition, isRectangular()).WillByDefault(::testing::Return(true));



    PopplerPage* poppler_page = reinterpret_cast<PopplerPage*>(page.get());

    PopplerPageTransition* transition = poppler_page_get_transition(poppler_page);



    ASSERT_NE(transition, nullptr);

    EXPECT_EQ(transition->type, POPPLER_PAGE_TRANSITION_REPLACE);

    EXPECT_EQ(transition->alignment, POPPLER_PAGE_TRANSITION_HORIZONTAL);

    EXPECT_EQ(transition->direction, POPPLER_PAGE_TRANSITION_INWARD);

    EXPECT_FLOAT_EQ(transition->duration, 2.0f);

    EXPECT_FLOAT_EQ(transition->duration_real, 2.0f);

    EXPECT_EQ(transition->angle, 45);

    EXPECT_FLOAT_EQ(transition->scale, 1.5f);

    EXPECT_NE(transition->rectangular, 0);



    delete transition;

}



TEST(PopplerPageGetTransitionTest_2430, NormalOperationSplitType_2430) {

    auto page = std::make_unique<PopplerPageMock>();

    Object transObj;

    EXPECT_CALL(*page, getTrans()).WillOnce(::testing::Return(transObj));



    PageTransition* mockPageTransition = new PageTransition(&transObj);

    ON_CALL(mockPageTransition, isOk()).WillByDefault(::testing::Return(true));

    ON_CALL(mockPageTransition, getType()).WillByDefault(::testing::Return(transitionSplit));

    ON_CALL(mockPageTransition, getAlignment()).WillByDefault(::testing::Return(transitionVertical));

    ON_CALL(mockPageTransition, getDirection()).WillByDefault(::testing::Return(transitionOutward));

    ON_CALL(mockPageTransition, getDuration()).WillByDefault(::testing::Return(3.0));

    ON_CALL(mockPageTransition, getAngle()).WillByDefault(::testing::Return(90));

    ON_CALL(mockPageTransition, getScale()).WillByDefault(::testing::Return(2.0));

    ON_CALL(mockPageTransition, isRectangular()).WillByDefault(::testing::Return(false));



    PopplerPage* poppler_page = reinterpret_cast<PopplerPage*>(page.get());

    PopplerPageTransition* transition = poppler_page_get_transition(poppler_page);



    ASSERT_NE(transition, nullptr);

    EXPECT_EQ(transition->type, POPPLER_PAGE_TRANSITION_SPLIT);

    EXPECT_EQ(transition->alignment, POPPLER_PAGE_TRANSITION_VERTICAL);

    EXPECT_EQ(transition->direction, POPPLER_PAGE_TRANSITION_OUTWARD);

    EXPECT_FLOAT_EQ(transition->duration, 3.0f);

    EXPECT_FLOAT_EQ(transition->duration_real, 3.0f);

    EXPECT_EQ(transition->angle, 90);

    EXPECT_FLOAT_EQ(transition->scale, 2.0f);

    EXPECT_EQ(transition->rectangular, 0);



    delete transition;

}



TEST(PopplerPageGetTransitionTest_2430, BoundaryConditionNoTransition_2430) {

    auto page = std::make_unique<PopplerPageMock>();

    Object transObj;

    EXPECT_CALL(*page, getTrans()).WillOnce(::testing::Return(transObj));



    PageTransition* mockPageTransition = new PageTransition(&transObj);

    ON_CALL(mockPageTransition, isOk()).WillByDefault(::testing::Return(false));



    PopplerPage* poppler_page = reinterpret_cast<PopplerPage*>(page.get());

    PopplerPageTransition* transition = poppler_page_get_transition(poppler_page);



    EXPECT_EQ(transition, nullptr);

}



TEST(PopplerPageGetTransitionTest_2430, ExceptionalInvalidType_2430) {

    auto page = std::make_unique<PopplerPageMock>();

    Object transObj;

    EXPECT_CALL(*page, getTrans()).WillOnce(::testing::Return(transObj));



    PageTransition* mockPageTransition = new PageTransition(&transObj);

    ON_CALL(mockPageTransition, isOk()).WillByDefault(::testing::Return(true));

    ON_CALL(mockPageTransition, getType()).WillByDefault(::testing::Return(static_cast<PageTransitionType>(20)));



    PopplerPage* poppler_page = reinterpret_cast<PopplerPage*>(page.get());

    EXPECT_DEATH(poppler_page_get_transition(poppler_page), "g_assert_not_reached");

}



TEST(PopplerPageGetTransitionTest_2430, NullPagePointer_2430) {

    EXPECT_EQ(poppler_page_get_transition(nullptr), nullptr);

}
