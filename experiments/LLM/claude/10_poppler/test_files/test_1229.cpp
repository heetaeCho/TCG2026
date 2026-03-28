#include <gtest/gtest.h>
#include "PageTransition.h"
#include "Object.h"

class PageTransitionTest_1229 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default construction with a null/invalid object
TEST_F(PageTransitionTest_1229, DefaultTransitionFromNullObject_1229) {
    Object obj;
    PageTransition pt(&obj);
    // Default type should be Replace when no valid transition dict is provided
    EXPECT_EQ(pt.getType(), pageTransitionReplace);
}

// Test that isOk returns a valid boolean for default construction
TEST_F(PageTransitionTest_1229, IsOkWithNullObject_1229) {
    Object obj;
    PageTransition pt(&obj);
    // isOk should return true or false without crashing
    bool ok = pt.isOk();
    (void)ok; // Just ensure it doesn't crash
}

// Test getDuration with default/invalid object
TEST_F(PageTransitionTest_1229, GetDurationDefault_1229) {
    Object obj;
    PageTransition pt(&obj);
    double duration = pt.getDuration();
    // Default duration is typically 1.0
    EXPECT_GE(duration, 0.0);
}

// Test getAlignment with default/invalid object
TEST_F(PageTransitionTest_1229, GetAlignmentDefault_1229) {
    Object obj;
    PageTransition pt(&obj);
    PageTransitionAlignment align = pt.getAlignment();
    EXPECT_EQ(align, pageTransitionHorizontal);
}

// Test getDirection with default/invalid object
TEST_F(PageTransitionTest_1229, GetDirectionDefault_1229) {
    Object obj;
    PageTransition pt(&obj);
    PageTransitionDirection dir = pt.getDirection();
    EXPECT_EQ(dir, pageTransitionInward);
}

// Test getAngle with default/invalid object
TEST_F(PageTransitionTest_1229, GetAngleDefault_1229) {
    Object obj;
    PageTransition pt(&obj);
    int angle = pt.getAngle();
    // Default angle is 0
    EXPECT_EQ(angle, 0);
}

// Test getScale with default/invalid object
TEST_F(PageTransitionTest_1229, GetScaleDefault_1229) {
    Object obj;
    PageTransition pt(&obj);
    double scale = pt.getScale();
    // Default scale is typically 1.0
    EXPECT_DOUBLE_EQ(scale, 1.0);
}

// Test isRectangular with default/invalid object
TEST_F(PageTransitionTest_1229, IsRectangularDefault_1229) {
    Object obj;
    PageTransition pt(&obj);
    bool rect = pt.isRectangular();
    EXPECT_FALSE(rect);
}

// Test with a valid transition dictionary specifying "Split" type
TEST_F(PageTransitionTest_1229, SplitTransitionType_1229) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeObj;
    typeObj = Object(objName, "Split");
    dict.dictSet("S", std::move(typeObj));
    
    PageTransition pt(&dict);
    EXPECT_EQ(pt.getType(), pageTransitionSplit);
}

// Test with a valid transition dictionary specifying "Blinds" type
TEST_F(PageTransitionTest_1229, BlindsTransitionType_1229) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeObj;
    typeObj = Object(objName, "Blinds");
    dict.dictSet("S", std::move(typeObj));
    
    PageTransition pt(&dict);
    EXPECT_EQ(pt.getType(), pageTransitionBlinds);
}

// Test with a valid transition dictionary specifying "Box" type
TEST_F(PageTransitionTest_1229, BoxTransitionType_1229) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeObj;
    typeObj = Object(objName, "Box");
    dict.dictSet("S", std::move(typeObj));
    
    PageTransition pt(&dict);
    EXPECT_EQ(pt.getType(), pageTransitionBox);
}

// Test with a valid transition dictionary specifying "Wipe" type
TEST_F(PageTransitionTest_1229, WipeTransitionType_1229) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeObj;
    typeObj = Object(objName, "Wipe");
    dict.dictSet("S", std::move(typeObj));
    
    PageTransition pt(&dict);
    EXPECT_EQ(pt.getType(), pageTransitionWipe);
}

// Test with a valid transition dictionary specifying "Dissolve" type
TEST_F(PageTransitionTest_1229, DissolveTransitionType_1229) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeObj;
    typeObj = Object(objName, "Dissolve");
    dict.dictSet("S", std::move(typeObj));
    
    PageTransition pt(&dict);
    EXPECT_EQ(pt.getType(), pageTransitionDissolve);
}

// Test with a valid transition dictionary specifying "Glitter" type
TEST_F(PageTransitionTest_1229, GlitterTransitionType_1229) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeObj;
    typeObj = Object(objName, "Glitter");
    dict.dictSet("S", std::move(typeObj));
    
    PageTransition pt(&dict);
    EXPECT_EQ(pt.getType(), pageTransitionGlitter);
}

// Test with a valid transition dictionary specifying "R" (Replace) type
TEST_F(PageTransitionTest_1229, ReplaceTransitionType_1229) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeObj;
    typeObj = Object(objName, "R");
    dict.dictSet("S", std::move(typeObj));
    
    PageTransition pt(&dict);
    EXPECT_EQ(pt.getType(), pageTransitionReplace);
}

// Test with a valid transition dictionary specifying "Fly" type
TEST_F(PageTransitionTest_1229, FlyTransitionType_1229) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeObj;
    typeObj = Object(objName, "Fly");
    dict.dictSet("S", std::move(typeObj));
    
    PageTransition pt(&dict);
    EXPECT_EQ(pt.getType(), pageTransitionFly);
}

// Test with a valid transition dictionary specifying "Push" type
TEST_F(PageTransitionTest_1229, PushTransitionType_1229) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeObj;
    typeObj = Object(objName, "Push");
    dict.dictSet("S", std::move(typeObj));
    
    PageTransition pt(&dict);
    EXPECT_EQ(pt.getType(), pageTransitionPush);
}

// Test with a valid transition dictionary specifying "Cover" type
TEST_F(PageTransitionTest_1229, CoverTransitionType_1229) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeObj;
    typeObj = Object(objName, "Cover");
    dict.dictSet("S", std::move(typeObj));
    
    PageTransition pt(&dict);
    EXPECT_EQ(pt.getType(), pageTransitionCover);
}

// Test with a valid transition dictionary specifying "Uncover" type
TEST_F(PageTransitionTest_1229, UncoverTransitionType_1229) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeObj;
    typeObj = Object(objName, "Uncover");
    dict.dictSet("S", std::move(typeObj));
    
    PageTransition pt(&dict);
    EXPECT_EQ(pt.getType(), pageTransitionUncover);
}

// Test with a valid transition dictionary specifying "Fade" type
TEST_F(PageTransitionTest_1229, FadeTransitionType_1229) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeObj;
    typeObj = Object(objName, "Fade");
    dict.dictSet("S", std::move(typeObj));
    
    PageTransition pt(&dict);
    EXPECT_EQ(pt.getType(), pageTransitionFade);
}

// Test with an unknown/invalid type name
TEST_F(PageTransitionTest_1229, UnknownTransitionType_1229) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeObj;
    typeObj = Object(objName, "InvalidType");
    dict.dictSet("S", std::move(typeObj));
    
    PageTransition pt(&dict);
    // Should default to Replace for unknown types
    EXPECT_EQ(pt.getType(), pageTransitionReplace);
}

// Test setting duration in dictionary
TEST_F(PageTransitionTest_1229, CustomDuration_1229) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object durObj(2.5);
    dict.dictSet("D", std::move(durObj));
    
    PageTransition pt(&dict);
    EXPECT_DOUBLE_EQ(pt.getDuration(), 2.5);
}

// Test setting alignment to vertical
TEST_F(PageTransitionTest_1229, VerticalAlignment_1229) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeObj(objName, "Split");
    dict.dictSet("S", std::move(typeObj));
    
    Object dmObj(objName, "V");
    dict.dictSet("Dm", std::move(dmObj));
    
    PageTransition pt(&dict);
    EXPECT_EQ(pt.getAlignment(), pageTransitionVertical);
}

// Test setting direction to outward
TEST_F(PageTransitionTest_1229, OutwardDirection_1229) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeObj(objName, "Split");
    dict.dictSet("S", std::move(typeObj));
    
    Object mObj(objName, "O");
    dict.dictSet("M", std::move(mObj));
    
    PageTransition pt(&dict);
    EXPECT_EQ(pt.getDirection(), pageTransitionOutward);
}

// Test setting angle
TEST_F(PageTransitionTest_1229, CustomAngle_1229) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeObj(objName, "Wipe");
    dict.dictSet("S", std::move(typeObj));
    
    Object angleObj(90);
    dict.dictSet("Di", std::move(angleObj));
    
    PageTransition pt(&dict);
    EXPECT_EQ(pt.getAngle(), 90);
}

// Test setting rectangular
TEST_F(PageTransitionTest_1229, RectangularTrue_1229) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeObj(objName, "Fly");
    dict.dictSet("S", std::move(typeObj));
    
    Object bObj(true);
    dict.dictSet("B", std::move(bObj));
    
    PageTransition pt(&dict);
    EXPECT_TRUE(pt.isRectangular());
}

// Test that empty dict gives default values for all properties
TEST_F(PageTransitionTest_1229, EmptyDictDefaults_1229) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    PageTransition pt(&dict);
    EXPECT_EQ(pt.getType(), pageTransitionReplace);
    EXPECT_DOUBLE_EQ(pt.getDuration(), 1.0);
    EXPECT_EQ(pt.getAlignment(), pageTransitionHorizontal);
    EXPECT_EQ(pt.getDirection(), pageTransitionInward);
    EXPECT_EQ(pt.getAngle(), 0);
    EXPECT_DOUBLE_EQ(pt.getScale(), 1.0);
    EXPECT_FALSE(pt.isRectangular());
}
