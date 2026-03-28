#include <gtest/gtest.h>
#include "PageTransition.h"
#include "Object.h"

class PageTransitionTest_1233 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default construction with a null/empty dictionary
TEST_F(PageTransitionTest_1233, DefaultTransitionFromNullObject_1233) {
    Object obj;
    PageTransition pt(&obj);
    // Default transition should still be "ok" or have sensible defaults
    // Type should default to Replace
    EXPECT_EQ(pt.getType(), pageTransitionReplace);
    EXPECT_EQ(pt.getDuration(), 1.0);
    EXPECT_EQ(pt.getAlignment(), transitionHorizontal);
    EXPECT_EQ(pt.getDirection(), transitionInward);
    EXPECT_EQ(pt.getAngle(), 0);
    EXPECT_EQ(pt.getScale(), 1.0);
    EXPECT_FALSE(pt.isRectangular());
}

// Test with a valid dictionary containing a Split transition
TEST_F(PageTransitionTest_1233, SplitTransition_1233) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeVal(objName, "Split");
    dict.dictAdd("S", std::move(typeVal));
    
    Object durVal(2.5);
    dict.dictAdd("D", std::move(durVal));
    
    Object dmVal(objName, "V");
    dict.dictAdd("Dm", std::move(dmVal));
    
    Object mVal(objName, "O");
    dict.dictAdd("M", std::move(mVal));
    
    PageTransition pt(&dict);
    EXPECT_EQ(pt.getType(), pageTransitionSplit);
    EXPECT_EQ(pt.getDuration(), 2.5);
    EXPECT_EQ(pt.getAlignment(), transitionVertical);
    EXPECT_EQ(pt.getDirection(), transitionOutward);
}

// Test with a Blinds transition
TEST_F(PageTransitionTest_1233, BlindsTransition_1233) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeVal(objName, "Blinds");
    dict.dictAdd("S", std::move(typeVal));
    
    Object dmVal(objName, "H");
    dict.dictAdd("Dm", std::move(dmVal));
    
    PageTransition pt(&dict);
    EXPECT_EQ(pt.getType(), pageTransitionBlinds);
    EXPECT_EQ(pt.getAlignment(), transitionHorizontal);
}

// Test with a Wipe transition and angle
TEST_F(PageTransitionTest_1233, WipeTransitionWithAngle_1233) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeVal(objName, "Wipe");
    dict.dictAdd("S", std::move(typeVal));
    
    Object angleVal(90);
    dict.dictAdd("Di", std::move(angleVal));
    
    PageTransition pt(&dict);
    EXPECT_EQ(pt.getType(), pageTransitionWipe);
    EXPECT_EQ(pt.getAngle(), 90);
}

// Test with a Dissolve transition
TEST_F(PageTransitionTest_1233, DissolveTransition_1233) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeVal(objName, "Dissolve");
    dict.dictAdd("S", std::move(typeVal));
    
    PageTransition pt(&dict);
    EXPECT_EQ(pt.getType(), pageTransitionDissolve);
}

// Test with a Glitter transition
TEST_F(PageTransitionTest_1233, GlitterTransition_1233) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeVal(objName, "Glitter");
    dict.dictAdd("S", std::move(typeVal));
    
    Object angleVal(315);
    dict.dictAdd("Di", std::move(angleVal));
    
    PageTransition pt(&dict);
    EXPECT_EQ(pt.getType(), pageTransitionGlitter);
    EXPECT_EQ(pt.getAngle(), 315);
}

// Test with a Box transition with rectangular
TEST_F(PageTransitionTest_1233, BoxTransitionRectangular_1233) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeVal(objName, "Box");
    dict.dictAdd("S", std::move(typeVal));
    
    Object mVal(objName, "I");
    dict.dictAdd("M", std::move(mVal));
    
    PageTransition pt(&dict);
    EXPECT_EQ(pt.getType(), pageTransitionBox);
    EXPECT_EQ(pt.getDirection(), transitionInward);
}

// Test with a Fly transition
TEST_F(PageTransitionTest_1233, FlyTransition_1233) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeVal(objName, "Fly");
    dict.dictAdd("S", std::move(typeVal));
    
    Object scaleVal(0.5);
    dict.dictAdd("SS", std::move(scaleVal));
    
    Object rectVal(true);
    dict.dictAdd("B", std::move(rectVal));
    
    PageTransition pt(&dict);
    EXPECT_EQ(pt.getType(), pageTransitionFly);
    EXPECT_EQ(pt.getScale(), 0.5);
    EXPECT_TRUE(pt.isRectangular());
}

// Test with a Push transition
TEST_F(PageTransitionTest_1233, PushTransition_1233) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeVal(objName, "Push");
    dict.dictAdd("S", std::move(typeVal));
    
    PageTransition pt(&dict);
    EXPECT_EQ(pt.getType(), pageTransitionPush);
}

// Test with a Cover transition
TEST_F(PageTransitionTest_1233, CoverTransition_1233) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeVal(objName, "Cover");
    dict.dictAdd("S", std::move(typeVal));
    
    PageTransition pt(&dict);
    EXPECT_EQ(pt.getType(), pageTransitionCover);
}

// Test with an Uncover transition
TEST_F(PageTransitionTest_1233, UncoverTransition_1233) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeVal(objName, "Uncover");
    dict.dictAdd("S", std::move(typeVal));
    
    PageTransition pt(&dict);
    EXPECT_EQ(pt.getType(), pageTransitionUncover);
}

// Test with a Fade transition
TEST_F(PageTransitionTest_1233, FadeTransition_1233) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeVal(objName, "Fade");
    dict.dictAdd("S", std::move(typeVal));
    
    PageTransition pt(&dict);
    EXPECT_EQ(pt.getType(), pageTransitionFade);
}

// Test getAngle returns the angle value
TEST_F(PageTransitionTest_1233, GetAngleReturnsCorrectValue_1233) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeVal(objName, "Wipe");
    dict.dictAdd("S", std::move(typeVal));
    
    Object angleVal(270);
    dict.dictAdd("Di", std::move(angleVal));
    
    PageTransition pt(&dict);
    EXPECT_EQ(pt.getAngle(), 270);
}

// Test zero duration
TEST_F(PageTransitionTest_1233, ZeroDuration_1233) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object durVal(0.0);
    dict.dictAdd("D", std::move(durVal));
    
    PageTransition pt(&dict);
    EXPECT_EQ(pt.getDuration(), 0.0);
}

// Test isRectangular defaults to false
TEST_F(PageTransitionTest_1233, IsRectangularDefaultFalse_1233) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    PageTransition pt(&dict);
    EXPECT_FALSE(pt.isRectangular());
}

// Test scale defaults to 1.0
TEST_F(PageTransitionTest_1233, ScaleDefaultValue_1233) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    PageTransition pt(&dict);
    EXPECT_EQ(pt.getScale(), 1.0);
}

// Test with an unknown/invalid transition type name defaults to Replace
TEST_F(PageTransitionTest_1233, UnknownTransitionTypeDefaultsToReplace_1233) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeVal(objName, "InvalidType");
    dict.dictAdd("S", std::move(typeVal));
    
    PageTransition pt(&dict);
    EXPECT_EQ(pt.getType(), pageTransitionReplace);
}

// Test angle of 0
TEST_F(PageTransitionTest_1233, AngleZero_1233) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeVal(objName, "Wipe");
    dict.dictAdd("S", std::move(typeVal));
    
    Object angleVal(0);
    dict.dictAdd("Di", std::move(angleVal));
    
    PageTransition pt(&dict);
    EXPECT_EQ(pt.getAngle(), 0);
}

// Test direction outward
TEST_F(PageTransitionTest_1233, DirectionOutward_1233) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeVal(objName, "Split");
    dict.dictAdd("S", std::move(typeVal));
    
    Object mVal(objName, "O");
    dict.dictAdd("M", std::move(mVal));
    
    PageTransition pt(&dict);
    EXPECT_EQ(pt.getDirection(), transitionOutward);
}

// Test direction inward (default)
TEST_F(PageTransitionTest_1233, DirectionInwardDefault_1233) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeVal(objName, "Split");
    dict.dictAdd("S", std::move(typeVal));
    
    PageTransition pt(&dict);
    EXPECT_EQ(pt.getDirection(), transitionInward);
}
