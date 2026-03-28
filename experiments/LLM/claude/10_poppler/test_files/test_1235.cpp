#include <gtest/gtest.h>
#include "PageTransition.h"
#include "Object.h"

class PageTransitionTest_1235 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default construction with a null/empty dictionary
TEST_F(PageTransitionTest_1235, DefaultTransitionFromNullObject_1235) {
    Object obj;
    PageTransition pt(&obj);
    // Default transition should be ok or have sensible defaults
    // We test observable behavior through the public interface
    EXPECT_GE(pt.getDuration(), 0.0);
    EXPECT_GE(pt.getAngle(), 0);
    EXPECT_GE(pt.getScale(), 0.0);
}

// Test construction with a valid dictionary containing type "Blinds"
TEST_F(PageTransitionTest_1235, BlindsTransition_1235) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeObj(objName, "Blinds");
    dict.dictAdd("S", std::move(typeObj));
    
    PageTransition pt(&dict);
    EXPECT_EQ(pt.getType(), pageTransitionBlinds);
}

// Test construction with a valid dictionary containing type "Wipe"
TEST_F(PageTransitionTest_1235, WipeTransition_1235) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeObj(objName, "Wipe");
    dict.dictAdd("S", std::move(typeObj));
    
    PageTransition pt(&dict);
    EXPECT_EQ(pt.getType(), pageTransitionWipe);
}

// Test isRectangular defaults to false
TEST_F(PageTransitionTest_1235, DefaultIsRectangularFalse_1235) {
    Object obj;
    PageTransition pt(&obj);
    EXPECT_FALSE(pt.isRectangular());
}

// Test default type is Replace (R)
TEST_F(PageTransitionTest_1235, DefaultTypeIsReplace_1235) {
    Object obj;
    PageTransition pt(&obj);
    EXPECT_EQ(pt.getType(), pageTransitionReplace);
}

// Test default alignment is horizontal
TEST_F(PageTransitionTest_1235, DefaultAlignmentIsHorizontal_1235) {
    Object obj;
    PageTransition pt(&obj);
    EXPECT_EQ(pt.getAlignment(), pageTransitionHorizontal);
}

// Test default direction is inward
TEST_F(PageTransitionTest_1235, DefaultDirectionIsInward_1235) {
    Object obj;
    PageTransition pt(&obj);
    EXPECT_EQ(pt.getDirection(), pageTransitionInward);
}

// Test default angle is 0
TEST_F(PageTransitionTest_1235, DefaultAngleIsZero_1235) {
    Object obj;
    PageTransition pt(&obj);
    EXPECT_EQ(pt.getAngle(), 0);
}

// Test default scale is 1.0
TEST_F(PageTransitionTest_1235, DefaultScaleIsOne_1235) {
    Object obj;
    PageTransition pt(&obj);
    EXPECT_DOUBLE_EQ(pt.getScale(), 1.0);
}

// Test default duration
TEST_F(PageTransitionTest_1235, DefaultDuration_1235) {
    Object obj;
    PageTransition pt(&obj);
    EXPECT_DOUBLE_EQ(pt.getDuration(), 1.0);
}

// Test with a dictionary specifying rectangular = true
TEST_F(PageTransitionTest_1235, RectangularTrue_1235) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object boolObj(true);
    dict.dictAdd("B", std::move(boolObj));
    
    PageTransition pt(&dict);
    EXPECT_TRUE(pt.isRectangular());
}

// Test with a dictionary specifying alignment = Vertical
TEST_F(PageTransitionTest_1235, VerticalAlignment_1235) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object dmObj(objName, "V");
    dict.dictAdd("Dm", std::move(dmObj));
    
    PageTransition pt(&dict);
    EXPECT_EQ(pt.getAlignment(), pageTransitionVertical);
}

// Test with a dictionary specifying direction = Outward
TEST_F(PageTransitionTest_1235, OutwardDirection_1235) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object mObj(objName, "O");
    dict.dictAdd("M", std::move(mObj));
    
    PageTransition pt(&dict);
    EXPECT_EQ(pt.getDirection(), pageTransitionOutward);
}

// Test with a dictionary specifying a custom angle
TEST_F(PageTransitionTest_1235, CustomAngle_1235) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object angleObj(270);
    dict.dictAdd("Di", std::move(angleObj));
    
    PageTransition pt(&dict);
    EXPECT_EQ(pt.getAngle(), 270);
}

// Test with a dictionary specifying a custom duration
TEST_F(PageTransitionTest_1235, CustomDuration_1235) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object durObj(2.5);
    dict.dictAdd("D", std::move(durObj));
    
    PageTransition pt(&dict);
    EXPECT_DOUBLE_EQ(pt.getDuration(), 2.5);
}

// Test Dissolve transition type
TEST_F(PageTransitionTest_1235, DissolveTransition_1235) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeObj(objName, "Dissolve");
    dict.dictAdd("S", std::move(typeObj));
    
    PageTransition pt(&dict);
    EXPECT_EQ(pt.getType(), pageTransitionDissolve);
}

// Test Box transition type
TEST_F(PageTransitionTest_1235, BoxTransition_1235) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeObj(objName, "Box");
    dict.dictAdd("S", std::move(typeObj));
    
    PageTransition pt(&dict);
    EXPECT_EQ(pt.getType(), pageTransitionBox);
}

// Test Split transition type
TEST_F(PageTransitionTest_1235, SplitTransition_1235) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeObj(objName, "Split");
    dict.dictAdd("S", std::move(typeObj));
    
    PageTransition pt(&dict);
    EXPECT_EQ(pt.getType(), pageTransitionSplit);
}

// Test Glitter transition type
TEST_F(PageTransitionTest_1235, GlitterTransition_1235) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeObj(objName, "Glitter");
    dict.dictAdd("S", std::move(typeObj));
    
    PageTransition pt(&dict);
    EXPECT_EQ(pt.getType(), pageTransitionGlitter);
}

// Test Fly transition type
TEST_F(PageTransitionTest_1235, FlyTransition_1235) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeObj(objName, "Fly");
    dict.dictAdd("S", std::move(typeObj));
    
    PageTransition pt(&dict);
    EXPECT_EQ(pt.getType(), pageTransitionFly);
}

// Test Push transition type
TEST_F(PageTransitionTest_1235, PushTransition_1235) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeObj(objName, "Push");
    dict.dictAdd("S", std::move(typeObj));
    
    PageTransition pt(&dict);
    EXPECT_EQ(pt.getType(), pageTransitionPush);
}

// Test Cover transition type
TEST_F(PageTransitionTest_1235, CoverTransition_1235) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeObj(objName, "Cover");
    dict.dictAdd("S", std::move(typeObj));
    
    PageTransition pt(&dict);
    EXPECT_EQ(pt.getType(), pageTransitionCover);
}

// Test Uncover transition type
TEST_F(PageTransitionTest_1235, UncoverTransition_1235) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeObj(objName, "Uncover");
    dict.dictAdd("S", std::move(typeObj));
    
    PageTransition pt(&dict);
    EXPECT_EQ(pt.getType(), pageTransitionUncover);
}

// Test Fade transition type
TEST_F(PageTransitionTest_1235, FadeTransition_1235) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeObj(objName, "Fade");
    dict.dictAdd("S", std::move(typeObj));
    
    PageTransition pt(&dict);
    EXPECT_EQ(pt.getType(), pageTransitionFade);
}

// Test isOk on a valid transition
TEST_F(PageTransitionTest_1235, IsOkOnValidTransition_1235) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeObj(objName, "Wipe");
    dict.dictAdd("S", std::move(typeObj));
    
    PageTransition pt(&dict);
    EXPECT_TRUE(pt.isOk());
}

// Test with custom scale for Fly transition
TEST_F(PageTransitionTest_1235, CustomScaleFlyTransition_1235) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeObj(objName, "Fly");
    dict.dictAdd("S", std::move(typeObj));
    
    Object scaleObj(0.5);
    dict.dictAdd("SS", std::move(scaleObj));
    
    PageTransition pt(&dict);
    EXPECT_DOUBLE_EQ(pt.getScale(), 0.5);
}

// Test zero duration
TEST_F(PageTransitionTest_1235, ZeroDuration_1235) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object durObj(0.0);
    dict.dictAdd("D", std::move(durObj));
    
    PageTransition pt(&dict);
    EXPECT_DOUBLE_EQ(pt.getDuration(), 0.0);
}

// Test combination of multiple properties
TEST_F(PageTransitionTest_1235, CombinedProperties_1235) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeObj(objName, "Split");
    dict.dictAdd("S", std::move(typeObj));
    
    Object dmObj(objName, "V");
    dict.dictAdd("Dm", std::move(dmObj));
    
    Object mObj(objName, "O");
    dict.dictAdd("M", std::move(mObj));
    
    Object durObj(3.0);
    dict.dictAdd("D", std::move(durObj));
    
    PageTransition pt(&dict);
    EXPECT_EQ(pt.getType(), pageTransitionSplit);
    EXPECT_EQ(pt.getAlignment(), pageTransitionVertical);
    EXPECT_EQ(pt.getDirection(), pageTransitionOutward);
    EXPECT_DOUBLE_EQ(pt.getDuration(), 3.0);
}
