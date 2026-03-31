#include <gtest/gtest.h>
#include "PageTransition.h"
#include "Object.h"

class PageTransitionTest_1231 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default construction with a null/empty dictionary
TEST_F(PageTransitionTest_1231, DefaultTransitionFromNullObject_1231) {
    Object obj;
    obj.initNull();
    PageTransition pt(&obj);
    // Default type should be Replace
    EXPECT_EQ(pt.getType(), pageTransitionReplace);
    EXPECT_EQ(pt.getAlignment(), transitionHorizontal);
    EXPECT_EQ(pt.getDirection(), transitionInward);
    EXPECT_EQ(pt.getAngle(), 0);
    EXPECT_DOUBLE_EQ(pt.getScale(), 1.0);
    EXPECT_FALSE(pt.isRectangular());
    EXPECT_TRUE(pt.isOk());
}

// Test with a valid dictionary that specifies a Split transition
TEST_F(PageTransitionTest_1231, SplitTransition_1231) {
    Object dict;
    dict.initDict((XRef *)nullptr);

    Object typeVal;
    typeVal.initName("Split");
    dict.dictAdd("S", std::move(typeVal));

    Object dmVal;
    dmVal.initName("V");
    dict.dictAdd("Dm", std::move(dmVal));

    Object mVal;
    mVal.initName("O");
    dict.dictAdd("M", std::move(mVal));

    PageTransition pt(&dict);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getType(), pageTransitionSplit);
    EXPECT_EQ(pt.getAlignment(), transitionVertical);
    EXPECT_EQ(pt.getDirection(), transitionOutward);
}

// Test with a valid dictionary that specifies a Blinds transition
TEST_F(PageTransitionTest_1231, BlindsTransition_1231) {
    Object dict;
    dict.initDict((XRef *)nullptr);

    Object typeVal;
    typeVal.initName("Blinds");
    dict.dictAdd("S", std::move(typeVal));

    Object dmVal;
    dmVal.initName("H");
    dict.dictAdd("Dm", std::move(dmVal));

    PageTransition pt(&dict);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getType(), pageTransitionBlinds);
    EXPECT_EQ(pt.getAlignment(), transitionHorizontal);
}

// Test with a valid dictionary specifying Wipe transition with angle
TEST_F(PageTransitionTest_1231, WipeTransitionWithAngle_1231) {
    Object dict;
    dict.initDict((XRef *)nullptr);

    Object typeVal;
    typeVal.initName("Wipe");
    dict.dictAdd("S", std::move(typeVal));

    Object angleVal;
    angleVal.initInt(90);
    dict.dictAdd("Di", std::move(angleVal));

    PageTransition pt(&dict);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getType(), pageTransitionWipe);
    EXPECT_EQ(pt.getAngle(), 90);
}

// Test with a valid dictionary specifying Dissolve transition
TEST_F(PageTransitionTest_1231, DissolveTransition_1231) {
    Object dict;
    dict.initDict((XRef *)nullptr);

    Object typeVal;
    typeVal.initName("Dissolve");
    dict.dictAdd("S", std::move(typeVal));

    PageTransition pt(&dict);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getType(), pageTransitionDissolve);
}

// Test with a valid dictionary specifying Box transition
TEST_F(PageTransitionTest_1231, BoxTransitionInward_1231) {
    Object dict;
    dict.initDict((XRef *)nullptr);

    Object typeVal;
    typeVal.initName("Box");
    dict.dictAdd("S", std::move(typeVal));

    Object mVal;
    mVal.initName("I");
    dict.dictAdd("M", std::move(mVal));

    PageTransition pt(&dict);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getType(), pageTransitionBox);
    EXPECT_EQ(pt.getDirection(), transitionInward);
}

// Test Box transition with outward direction
TEST_F(PageTransitionTest_1231, BoxTransitionOutward_1231) {
    Object dict;
    dict.initDict((XRef *)nullptr);

    Object typeVal;
    typeVal.initName("Box");
    dict.dictAdd("S", std::move(typeVal));

    Object mVal;
    mVal.initName("O");
    dict.dictAdd("M", std::move(mVal));

    PageTransition pt(&dict);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getType(), pageTransitionBox);
    EXPECT_EQ(pt.getDirection(), transitionOutward);
}

// Test Glitter transition
TEST_F(PageTransitionTest_1231, GlitterTransition_1231) {
    Object dict;
    dict.initDict((XRef *)nullptr);

    Object typeVal;
    typeVal.initName("Glitter");
    dict.dictAdd("S", std::move(typeVal));

    Object angleVal;
    angleVal.initInt(315);
    dict.dictAdd("Di", std::move(angleVal));

    PageTransition pt(&dict);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getType(), pageTransitionGlitter);
    EXPECT_EQ(pt.getAngle(), 315);
}

// Test Replace transition
TEST_F(PageTransitionTest_1231, ReplaceTransition_1231) {
    Object dict;
    dict.initDict((XRef *)nullptr);

    Object typeVal;
    typeVal.initName("R");
    dict.dictAdd("S", std::move(typeVal));

    PageTransition pt(&dict);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getType(), pageTransitionReplace);
}

// Test Fly transition with scale
TEST_F(PageTransitionTest_1231, FlyTransitionWithScale_1231) {
    Object dict;
    dict.initDict((XRef *)nullptr);

    Object typeVal;
    typeVal.initName("Fly");
    dict.dictAdd("S", std::move(typeVal));

    Object scaleVal;
    scaleVal.initReal(0.5);
    dict.dictAdd("SS", std::move(scaleVal));

    Object rectVal;
    rectVal.initBool(true);
    dict.dictAdd("B", std::move(rectVal));

    PageTransition pt(&dict);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getType(), pageTransitionFly);
    EXPECT_DOUBLE_EQ(pt.getScale(), 0.5);
    EXPECT_TRUE(pt.isRectangular());
}

// Test Push transition
TEST_F(PageTransitionTest_1231, PushTransition_1231) {
    Object dict;
    dict.initDict((XRef *)nullptr);

    Object typeVal;
    typeVal.initName("Push");
    dict.dictAdd("S", std::move(typeVal));

    PageTransition pt(&dict);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getType(), pageTransitionPush);
}

// Test Cover transition
TEST_F(PageTransitionTest_1231, CoverTransition_1231) {
    Object dict;
    dict.initDict((XRef *)nullptr);

    Object typeVal;
    typeVal.initName("Cover");
    dict.dictAdd("S", std::move(typeVal));

    PageTransition pt(&dict);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getType(), pageTransitionCover);
}

// Test Uncover transition
TEST_F(PageTransitionTest_1231, UncoverTransition_1231) {
    Object dict;
    dict.initDict((XRef *)nullptr);

    Object typeVal;
    typeVal.initName("Uncover");
    dict.dictAdd("S", std::move(typeVal));

    PageTransition pt(&dict);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getType(), pageTransitionUncover);
}

// Test Fade transition
TEST_F(PageTransitionTest_1231, FadeTransition_1231) {
    Object dict;
    dict.initDict((XRef *)nullptr);

    Object typeVal;
    typeVal.initName("Fade");
    dict.dictAdd("S", std::move(typeVal));

    PageTransition pt(&dict);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getType(), pageTransitionFade);
}

// Test default values when dictionary is empty
TEST_F(PageTransitionTest_1231, EmptyDictionaryDefaults_1231) {
    Object dict;
    dict.initDict((XRef *)nullptr);

    PageTransition pt(&dict);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getType(), pageTransitionReplace);
    EXPECT_EQ(pt.getAlignment(), transitionHorizontal);
    EXPECT_EQ(pt.getDirection(), transitionInward);
    EXPECT_EQ(pt.getAngle(), 0);
    EXPECT_DOUBLE_EQ(pt.getScale(), 1.0);
    EXPECT_FALSE(pt.isRectangular());
}

// Test with angle of 0
TEST_F(PageTransitionTest_1231, WipeTransitionAngleZero_1231) {
    Object dict;
    dict.initDict((XRef *)nullptr);

    Object typeVal;
    typeVal.initName("Wipe");
    dict.dictAdd("S", std::move(typeVal));

    Object angleVal;
    angleVal.initInt(0);
    dict.dictAdd("Di", std::move(angleVal));

    PageTransition pt(&dict);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getAngle(), 0);
}

// Test with angle of 180
TEST_F(PageTransitionTest_1231, WipeTransitionAngle180_1231) {
    Object dict;
    dict.initDict((XRef *)nullptr);

    Object typeVal;
    typeVal.initName("Wipe");
    dict.dictAdd("S", std::move(typeVal));

    Object angleVal;
    angleVal.initInt(180);
    dict.dictAdd("Di", std::move(angleVal));

    PageTransition pt(&dict);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getAngle(), 180);
}

// Test with angle of 270
TEST_F(PageTransitionTest_1231, WipeTransitionAngle270_1231) {
    Object dict;
    dict.initDict((XRef *)nullptr);

    Object typeVal;
    typeVal.initName("Wipe");
    dict.dictAdd("S", std::move(typeVal));

    Object angleVal;
    angleVal.initInt(270);
    dict.dictAdd("Di", std::move(angleVal));

    PageTransition pt(&dict);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getAngle(), 270);
}

// Test rectangular false by default
TEST_F(PageTransitionTest_1231, RectangularDefaultFalse_1231) {
    Object dict;
    dict.initDict((XRef *)nullptr);

    Object typeVal;
    typeVal.initName("Fly");
    dict.dictAdd("S", std::move(typeVal));

    PageTransition pt(&dict);
    EXPECT_FALSE(pt.isRectangular());
}

// Test scale default is 1.0
TEST_F(PageTransitionTest_1231, ScaleDefaultIsOne_1231) {
    Object dict;
    dict.initDict((XRef *)nullptr);

    Object typeVal;
    typeVal.initName("Fly");
    dict.dictAdd("S", std::move(typeVal));

    PageTransition pt(&dict);
    EXPECT_DOUBLE_EQ(pt.getScale(), 1.0);
}

// Test getDuration with default
TEST_F(PageTransitionTest_1231, DurationDefault_1231) {
    Object dict;
    dict.initDict((XRef *)nullptr);

    PageTransition pt(&dict);
    EXPECT_GE(pt.getDuration(), 0.0);
}

// Test an unknown transition type name
TEST_F(PageTransitionTest_1231, UnknownTransitionType_1231) {
    Object dict;
    dict.initDict((XRef *)nullptr);

    Object typeVal;
    typeVal.initName("UnknownType");
    dict.dictAdd("S", std::move(typeVal));

    PageTransition pt(&dict);
    // Should still be ok, possibly defaults
    // We just verify it doesn't crash
    pt.getType();
    pt.getAlignment();
    pt.getDirection();
    pt.getAngle();
    pt.getScale();
    pt.isRectangular();
}
