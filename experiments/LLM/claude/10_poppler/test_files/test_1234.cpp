#include <gtest/gtest.h>
#include "PageTransition.h"
#include "Object.h"

class PageTransitionTest_1234 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test construction with a null/empty dictionary - should use defaults
TEST_F(PageTransitionTest_1234, DefaultConstructionFromNullObject_1234) {
    Object obj;
    obj.initNull();
    PageTransition pt(&obj);
    
    // Default transition should be valid
    EXPECT_TRUE(pt.isOk());
}

// Test default type is Replace (R) when no /S entry
TEST_F(PageTransitionTest_1234, DefaultTypeIsReplace_1234) {
    Object obj;
    obj.initNull();
    PageTransition pt(&obj);
    
    EXPECT_EQ(pt.getType(), transitionReplace);
}

// Test default duration
TEST_F(PageTransitionTest_1234, DefaultDuration_1234) {
    Object obj;
    obj.initNull();
    PageTransition pt(&obj);
    
    EXPECT_DOUBLE_EQ(pt.getDuration(), 1.0);
}

// Test default alignment is horizontal
TEST_F(PageTransitionTest_1234, DefaultAlignment_1234) {
    Object obj;
    obj.initNull();
    PageTransition pt(&obj);
    
    EXPECT_EQ(pt.getAlignment(), transitionHorizontal);
}

// Test default direction is inward
TEST_F(PageTransitionTest_1234, DefaultDirection_1234) {
    Object obj;
    obj.initNull();
    PageTransition pt(&obj);
    
    EXPECT_EQ(pt.getDirection(), transitionInward);
}

// Test default angle is 0
TEST_F(PageTransitionTest_1234, DefaultAngle_1234) {
    Object obj;
    obj.initNull();
    PageTransition pt(&obj);
    
    EXPECT_EQ(pt.getAngle(), 0);
}

// Test default scale is 1.0
TEST_F(PageTransitionTest_1234, DefaultScale_1234) {
    Object obj;
    obj.initNull();
    PageTransition pt(&obj);
    
    EXPECT_DOUBLE_EQ(pt.getScale(), 1.0);
}

// Test default rectangular is false
TEST_F(PageTransitionTest_1234, DefaultRectangular_1234) {
    Object obj;
    obj.initNull();
    PageTransition pt(&obj);
    
    EXPECT_FALSE(pt.isRectangular());
}

// Test construction with a proper dictionary specifying Split type
TEST_F(PageTransitionTest_1234, SplitTransitionType_1234) {
    Object obj;
    obj.initDict((XRef *)nullptr);
    
    Object typeObj;
    typeObj.initName("Split");
    obj.dictAdd("S", std::move(typeObj));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getType(), transitionSplit);
}

// Test construction with Blinds type
TEST_F(PageTransitionTest_1234, BlindsTransitionType_1234) {
    Object obj;
    obj.initDict((XRef *)nullptr);
    
    Object typeObj;
    typeObj.initName("Blinds");
    obj.dictAdd("S", std::move(typeObj));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getType(), transitionBlinds);
}

// Test construction with Box type
TEST_F(PageTransitionTest_1234, BoxTransitionType_1234) {
    Object obj;
    obj.initDict((XRef *)nullptr);
    
    Object typeObj;
    typeObj.initName("Box");
    obj.dictAdd("S", std::move(typeObj));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getType(), transitionBox);
}

// Test construction with Wipe type
TEST_F(PageTransitionTest_1234, WipeTransitionType_1234) {
    Object obj;
    obj.initDict((XRef *)nullptr);
    
    Object typeObj;
    typeObj.initName("Wipe");
    obj.dictAdd("S", std::move(typeObj));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getType(), transitionWipe);
}

// Test construction with Dissolve type
TEST_F(PageTransitionTest_1234, DissolveTransitionType_1234) {
    Object obj;
    obj.initDict((XRef *)nullptr);
    
    Object typeObj;
    typeObj.initName("Dissolve");
    obj.dictAdd("S", std::move(typeObj));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getType(), transitionDissolve);
}

// Test construction with Glitter type
TEST_F(PageTransitionTest_1234, GlitterTransitionType_1234) {
    Object obj;
    obj.initDict((XRef *)nullptr);
    
    Object typeObj;
    typeObj.initName("Glitter");
    obj.dictAdd("S", std::move(typeObj));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getType(), transitionGlitter);
}

// Test construction with Fly type
TEST_F(PageTransitionTest_1234, FlyTransitionType_1234) {
    Object obj;
    obj.initDict((XRef *)nullptr);
    
    Object typeObj;
    typeObj.initName("Fly");
    obj.dictAdd("S", std::move(typeObj));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getType(), transitionFly);
}

// Test custom duration value
TEST_F(PageTransitionTest_1234, CustomDuration_1234) {
    Object obj;
    obj.initDict((XRef *)nullptr);
    
    Object durObj;
    durObj.initReal(2.5);
    obj.dictAdd("D", std::move(durObj));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_DOUBLE_EQ(pt.getDuration(), 2.5);
}

// Test vertical alignment
TEST_F(PageTransitionTest_1234, VerticalAlignment_1234) {
    Object obj;
    obj.initDict((XRef *)nullptr);
    
    Object typeObj;
    typeObj.initName("Split");
    obj.dictAdd("S", std::move(typeObj));
    
    Object dmObj;
    dmObj.initName("V");
    obj.dictAdd("Dm", std::move(dmObj));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getAlignment(), transitionVertical);
}

// Test outward direction
TEST_F(PageTransitionTest_1234, OutwardDirection_1234) {
    Object obj;
    obj.initDict((XRef *)nullptr);
    
    Object typeObj;
    typeObj.initName("Box");
    obj.dictAdd("S", std::move(typeObj));
    
    Object mObj;
    mObj.initName("O");
    obj.dictAdd("M", std::move(mObj));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getDirection(), transitionOutward);
}

// Test custom angle
TEST_F(PageTransitionTest_1234, CustomAngle_1234) {
    Object obj;
    obj.initDict((XRef *)nullptr);
    
    Object typeObj;
    typeObj.initName("Wipe");
    obj.dictAdd("S", std::move(typeObj));
    
    Object diObj;
    diObj.initInt(90);
    obj.dictAdd("Di", std::move(diObj));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getAngle(), 90);
}

// Test custom scale for Fly transition
TEST_F(PageTransitionTest_1234, CustomScaleForFly_1234) {
    Object obj;
    obj.initDict((XRef *)nullptr);
    
    Object typeObj;
    typeObj.initName("Fly");
    obj.dictAdd("S", std::move(typeObj));
    
    Object ssObj;
    ssObj.initReal(0.5);
    obj.dictAdd("SS", std::move(ssObj));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_DOUBLE_EQ(pt.getScale(), 0.5);
}

// Test rectangular flag
TEST_F(PageTransitionTest_1234, RectangularFlag_1234) {
    Object obj;
    obj.initDict((XRef *)nullptr);
    
    Object typeObj;
    typeObj.initName("Fly");
    obj.dictAdd("S", std::move(typeObj));
    
    Object bObj;
    bObj.initBool(true);
    obj.dictAdd("B", std::move(bObj));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_TRUE(pt.isRectangular());
}

// Test angle 270 for Wipe
TEST_F(PageTransitionTest_1234, WipeAngle270_1234) {
    Object obj;
    obj.initDict((XRef *)nullptr);
    
    Object typeObj;
    typeObj.initName("Wipe");
    obj.dictAdd("S", std::move(typeObj));
    
    Object diObj;
    diObj.initInt(270);
    obj.dictAdd("Di", std::move(diObj));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getAngle(), 270);
}

// Test zero duration
TEST_F(PageTransitionTest_1234, ZeroDuration_1234) {
    Object obj;
    obj.initDict((XRef *)nullptr);
    
    Object durObj;
    durObj.initReal(0.0);
    obj.dictAdd("D", std::move(durObj));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_DOUBLE_EQ(pt.getDuration(), 0.0);
}

// Test scale of 0.0
TEST_F(PageTransitionTest_1234, ZeroScale_1234) {
    Object obj;
    obj.initDict((XRef *)nullptr);
    
    Object typeObj;
    typeObj.initName("Fly");
    obj.dictAdd("S", std::move(typeObj));
    
    Object ssObj;
    ssObj.initReal(0.0);
    obj.dictAdd("SS", std::move(ssObj));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_DOUBLE_EQ(pt.getScale(), 0.0);
}

// Test Push transition type
TEST_F(PageTransitionTest_1234, PushTransitionType_1234) {
    Object obj;
    obj.initDict((XRef *)nullptr);
    
    Object typeObj;
    typeObj.initName("Push");
    obj.dictAdd("S", std::move(typeObj));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getType(), transitionPush);
}

// Test Cover transition type
TEST_F(PageTransitionTest_1234, CoverTransitionType_1234) {
    Object obj;
    obj.initDict((XRef *)nullptr);
    
    Object typeObj;
    typeObj.initName("Cover");
    obj.dictAdd("S", std::move(typeObj));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getType(), transitionCover);
}

// Test Uncover transition type
TEST_F(PageTransitionTest_1234, UncoverTransitionType_1234) {
    Object obj;
    obj.initDict((XRef *)nullptr);
    
    Object typeObj;
    typeObj.initName("Uncover");
    obj.dictAdd("S", std::move(typeObj));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getType(), transitionUncover);
}

// Test Fade transition type
TEST_F(PageTransitionTest_1234, FadeTransitionType_1234) {
    Object obj;
    obj.initDict((XRef *)nullptr);
    
    Object typeObj;
    typeObj.initName("Fade");
    obj.dictAdd("S", std::move(typeObj));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getType(), transitionFade);
}

// Test combination of multiple parameters
TEST_F(PageTransitionTest_1234, MultipleParameters_1234) {
    Object obj;
    obj.initDict((XRef *)nullptr);
    
    Object typeObj;
    typeObj.initName("Fly");
    obj.dictAdd("S", std::move(typeObj));
    
    Object durObj;
    durObj.initReal(3.0);
    obj.dictAdd("D", std::move(durObj));
    
    Object mObj;
    mObj.initName("O");
    obj.dictAdd("M", std::move(mObj));
    
    Object ssObj;
    ssObj.initReal(0.75);
    obj.dictAdd("SS", std::move(ssObj));
    
    Object bObj;
    bObj.initBool(true);
    obj.dictAdd("B", std::move(bObj));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getType(), transitionFly);
    EXPECT_DOUBLE_EQ(pt.getDuration(), 3.0);
    EXPECT_EQ(pt.getDirection(), transitionOutward);
    EXPECT_DOUBLE_EQ(pt.getScale(), 0.75);
    EXPECT_TRUE(pt.isRectangular());
}

// Test getScale returns expected value (the method shown in partial code)
TEST_F(PageTransitionTest_1234, GetScaleReturnsScale_1234) {
    Object obj;
    obj.initNull();
    PageTransition pt(&obj);
    
    // Default scale should be 1.0
    double scale = pt.getScale();
    EXPECT_DOUBLE_EQ(scale, 1.0);
}
