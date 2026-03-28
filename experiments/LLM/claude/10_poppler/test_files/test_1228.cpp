#include <gtest/gtest.h>
#include "PageTransition.h"
#include "Object.h"

class PageTransitionTest_1228 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test with a null/invalid object - should result in default values
TEST_F(PageTransitionTest_1228, DefaultConstructionWithNullObject_1228) {
    Object obj;
    obj.initNull();
    PageTransition pt(&obj);
    // With a null object, the transition should still be ok (defaults applied)
    // or not ok depending on implementation. We test observable behavior.
    // Typically a null dict means defaults are used and isOk() returns true.
    EXPECT_TRUE(pt.isOk());
}

// Test with a valid empty dictionary - should use default values
TEST_F(PageTransitionTest_1228, EmptyDictDefaultValues_1228) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    PageTransition pt(&obj);
    
    EXPECT_TRUE(pt.isOk());
    // Default type should be Replace (R)
    EXPECT_EQ(pt.getType(), pageTransitionReplace);
    // Default duration is typically 1.0
    EXPECT_DOUBLE_EQ(pt.getDuration(), 1.0);
    // Default alignment is horizontal
    EXPECT_EQ(pt.getAlignment(), pageTransitionHorizontal);
    // Default direction is inward
    EXPECT_EQ(pt.getDirection(), pageTransitionInward);
    // Default angle is 0
    EXPECT_EQ(pt.getAngle(), 0);
    // Default scale is 1.0
    EXPECT_DOUBLE_EQ(pt.getScale(), 1.0);
    // Default rectangular is false
    EXPECT_FALSE(pt.isRectangular());
}

// Test with a dictionary specifying Split transition type
TEST_F(PageTransitionTest_1228, SplitTransitionType_1228) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    
    Object typeVal;
    typeVal.initName("Split");
    obj.dictAdd("S", std::move(typeVal));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getType(), pageTransitionSplit);
}

// Test with a dictionary specifying Blinds transition type
TEST_F(PageTransitionTest_1228, BlindsTransitionType_1228) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    
    Object typeVal;
    typeVal.initName("Blinds");
    obj.dictAdd("S", std::move(typeVal));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getType(), pageTransitionBlinds);
}

// Test with a dictionary specifying Box transition type
TEST_F(PageTransitionTest_1228, BoxTransitionType_1228) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    
    Object typeVal;
    typeVal.initName("Box");
    obj.dictAdd("S", std::move(typeVal));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getType(), pageTransitionBox);
}

// Test with a dictionary specifying Wipe transition type
TEST_F(PageTransitionTest_1228, WipeTransitionType_1228) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    
    Object typeVal;
    typeVal.initName("Wipe");
    obj.dictAdd("S", std::move(typeVal));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getType(), pageTransitionWipe);
}

// Test with a dictionary specifying Dissolve transition type
TEST_F(PageTransitionTest_1228, DissolveTransitionType_1228) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    
    Object typeVal;
    typeVal.initName("Dissolve");
    obj.dictAdd("S", std::move(typeVal));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getType(), pageTransitionDissolve);
}

// Test with a dictionary specifying Glitter transition type
TEST_F(PageTransitionTest_1228, GlitterTransitionType_1228) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    
    Object typeVal;
    typeVal.initName("Glitter");
    obj.dictAdd("S", std::move(typeVal));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getType(), pageTransitionGlitter);
}

// Test with a dictionary specifying R (Replace) transition type
TEST_F(PageTransitionTest_1228, ReplaceTransitionType_1228) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    
    Object typeVal;
    typeVal.initName("R");
    obj.dictAdd("S", std::move(typeVal));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getType(), pageTransitionReplace);
}

// Test with a dictionary specifying Fly transition type
TEST_F(PageTransitionTest_1228, FlyTransitionType_1228) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    
    Object typeVal;
    typeVal.initName("Fly");
    obj.dictAdd("S", std::move(typeVal));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getType(), pageTransitionFly);
}

// Test with a dictionary specifying Push transition type
TEST_F(PageTransitionTest_1228, PushTransitionType_1228) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    
    Object typeVal;
    typeVal.initName("Push");
    obj.dictAdd("S", std::move(typeVal));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getType(), pageTransitionPush);
}

// Test with a dictionary specifying Cover transition type
TEST_F(PageTransitionTest_1228, CoverTransitionType_1228) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    
    Object typeVal;
    typeVal.initName("Cover");
    obj.dictAdd("S", std::move(typeVal));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getType(), pageTransitionCover);
}

// Test with a dictionary specifying Uncover transition type
TEST_F(PageTransitionTest_1228, UncoverTransitionType_1228) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    
    Object typeVal;
    typeVal.initName("Uncover");
    obj.dictAdd("S", std::move(typeVal));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getType(), pageTransitionUncover);
}

// Test with a dictionary specifying Fade transition type
TEST_F(PageTransitionTest_1228, FadeTransitionType_1228) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    
    Object typeVal;
    typeVal.initName("Fade");
    obj.dictAdd("S", std::move(typeVal));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getType(), pageTransitionFade);
}

// Test duration setting
TEST_F(PageTransitionTest_1228, CustomDuration_1228) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    
    Object durVal;
    durVal.initReal(2.5);
    obj.dictAdd("D", std::move(durVal));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_DOUBLE_EQ(pt.getDuration(), 2.5);
}

// Test vertical alignment
TEST_F(PageTransitionTest_1228, VerticalAlignment_1228) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    
    Object typeVal;
    typeVal.initName("Split");
    obj.dictAdd("S", std::move(typeVal));
    
    Object dmVal;
    dmVal.initName("V");
    obj.dictAdd("Dm", std::move(dmVal));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getAlignment(), pageTransitionVertical);
}

// Test horizontal alignment
TEST_F(PageTransitionTest_1228, HorizontalAlignment_1228) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    
    Object typeVal;
    typeVal.initName("Split");
    obj.dictAdd("S", std::move(typeVal));
    
    Object dmVal;
    dmVal.initName("H");
    obj.dictAdd("Dm", std::move(dmVal));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getAlignment(), pageTransitionHorizontal);
}

// Test outward direction
TEST_F(PageTransitionTest_1228, OutwardDirection_1228) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    
    Object typeVal;
    typeVal.initName("Split");
    obj.dictAdd("S", std::move(typeVal));
    
    Object mVal;
    mVal.initName("O");
    obj.dictAdd("M", std::move(mVal));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getDirection(), pageTransitionOutward);
}

// Test inward direction
TEST_F(PageTransitionTest_1228, InwardDirection_1228) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    
    Object typeVal;
    typeVal.initName("Split");
    obj.dictAdd("S", std::move(typeVal));
    
    Object mVal;
    mVal.initName("I");
    obj.dictAdd("M", std::move(mVal));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getDirection(), pageTransitionInward);
}

// Test angle setting
TEST_F(PageTransitionTest_1228, CustomAngle_1228) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    
    Object typeVal;
    typeVal.initName("Wipe");
    obj.dictAdd("S", std::move(typeVal));
    
    Object diVal;
    diVal.initInt(270);
    obj.dictAdd("Di", std::move(diVal));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getAngle(), 270);
}

// Test scale setting
TEST_F(PageTransitionTest_1228, CustomScale_1228) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    
    Object typeVal;
    typeVal.initName("Fly");
    obj.dictAdd("S", std::move(typeVal));
    
    Object ssVal;
    ssVal.initReal(0.5);
    obj.dictAdd("SS", std::move(ssVal));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_DOUBLE_EQ(pt.getScale(), 0.5);
}

// Test rectangular setting
TEST_F(PageTransitionTest_1228, RectangularTrue_1228) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    
    Object typeVal;
    typeVal.initName("Fly");
    obj.dictAdd("S", std::move(typeVal));
    
    Object bVal;
    bVal.initBool(true);
    obj.dictAdd("B", std::move(bVal));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_TRUE(pt.isRectangular());
}

// Test rectangular false setting
TEST_F(PageTransitionTest_1228, RectangularFalse_1228) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    
    Object typeVal;
    typeVal.initName("Fly");
    obj.dictAdd("S", std::move(typeVal));
    
    Object bVal;
    bVal.initBool(false);
    obj.dictAdd("B", std::move(bVal));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_FALSE(pt.isRectangular());
}

// Test zero duration
TEST_F(PageTransitionTest_1228, ZeroDuration_1228) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    
    Object durVal;
    durVal.initReal(0.0);
    obj.dictAdd("D", std::move(durVal));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_DOUBLE_EQ(pt.getDuration(), 0.0);
}

// Test angle of 0
TEST_F(PageTransitionTest_1228, ZeroAngle_1228) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    
    Object typeVal;
    typeVal.initName("Wipe");
    obj.dictAdd("S", std::move(typeVal));
    
    Object diVal;
    diVal.initInt(0);
    obj.dictAdd("Di", std::move(diVal));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getAngle(), 0);
}

// Test angle of 90
TEST_F(PageTransitionTest_1228, Angle90_1228) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    
    Object typeVal;
    typeVal.initName("Wipe");
    obj.dictAdd("S", std::move(typeVal));
    
    Object diVal;
    diVal.initInt(90);
    obj.dictAdd("Di", std::move(diVal));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getAngle(), 90);
}

// Test angle of 180
TEST_F(PageTransitionTest_1228, Angle180_1228) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    
    Object typeVal;
    typeVal.initName("Wipe");
    obj.dictAdd("S", std::move(typeVal));
    
    Object diVal;
    diVal.initInt(180);
    obj.dictAdd("Di", std::move(diVal));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getAngle(), 180);
}

// Test with integer duration
TEST_F(PageTransitionTest_1228, IntegerDuration_1228) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    
    Object durVal;
    durVal.initInt(3);
    obj.dictAdd("D", std::move(durVal));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_DOUBLE_EQ(pt.getDuration(), 3.0);
}

// Test with all properties set at once
TEST_F(PageTransitionTest_1228, AllPropertiesSet_1228) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    
    Object typeVal;
    typeVal.initName("Fly");
    obj.dictAdd("S", std::move(typeVal));
    
    Object durVal;
    durVal.initReal(5.0);
    obj.dictAdd("D", std::move(durVal));
    
    Object dmVal;
    dmVal.initName("V");
    obj.dictAdd("Dm", std::move(dmVal));
    
    Object mVal;
    mVal.initName("O");
    obj.dictAdd("M", std::move(mVal));
    
    Object diVal;
    diVal.initInt(315);
    obj.dictAdd("Di", std::move(diVal));
    
    Object ssVal;
    ssVal.initReal(0.75);
    obj.dictAdd("SS", std::move(ssVal));
    
    Object bVal;
    bVal.initBool(true);
    obj.dictAdd("B", std::move(bVal));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getType(), pageTransitionFly);
    EXPECT_DOUBLE_EQ(pt.getDuration(), 5.0);
    EXPECT_EQ(pt.getAlignment(), pageTransitionVertical);
    EXPECT_EQ(pt.getDirection(), pageTransitionOutward);
    EXPECT_EQ(pt.getAngle(), 315);
    EXPECT_DOUBLE_EQ(pt.getScale(), 0.75);
    EXPECT_TRUE(pt.isRectangular());
}
