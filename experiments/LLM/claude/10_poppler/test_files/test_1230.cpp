#include <gtest/gtest.h>
#include "PageTransition.h"
#include "Object.h"

class PageTransitionTest_1230 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default construction with a null/empty dictionary
TEST_F(PageTransitionTest_1230, DefaultConstructionWithNullObject_1230) {
    Object obj;
    obj.initNull();
    PageTransition pt(&obj);
    // Default values should be set when given a null object
    EXPECT_TRUE(pt.isOk());
}

// Test construction with an empty dictionary
TEST_F(PageTransitionTest_1230, ConstructionWithEmptyDict_1230) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    // Default type should be Replace
    EXPECT_EQ(pt.getType(), pageTransitionReplace);
    // Default duration
    EXPECT_DOUBLE_EQ(pt.getDuration(), 1.0);
    // Default alignment
    EXPECT_EQ(pt.getAlignment(), pageTransitionHorizontal);
    // Default direction
    EXPECT_EQ(pt.getDirection(), pageTransitionInward);
    // Default angle
    EXPECT_EQ(pt.getAngle(), 0);
    // Default scale
    EXPECT_DOUBLE_EQ(pt.getScale(), 1.0);
    // Default rectangular
    EXPECT_FALSE(pt.isRectangular());
}

// Test getDuration returns expected default
TEST_F(PageTransitionTest_1230, GetDurationDefault_1230) {
    Object obj;
    obj.initNull();
    PageTransition pt(&obj);
    // Default duration should be 1.0 according to PDF spec
    EXPECT_DOUBLE_EQ(pt.getDuration(), 1.0);
}

// Test getType returns expected default
TEST_F(PageTransitionTest_1230, GetTypeDefault_1230) {
    Object obj;
    obj.initNull();
    PageTransition pt(&obj);
    EXPECT_EQ(pt.getType(), pageTransitionReplace);
}

// Test getAlignment returns expected default
TEST_F(PageTransitionTest_1230, GetAlignmentDefault_1230) {
    Object obj;
    obj.initNull();
    PageTransition pt(&obj);
    EXPECT_EQ(pt.getAlignment(), pageTransitionHorizontal);
}

// Test getDirection returns expected default
TEST_F(PageTransitionTest_1230, GetDirectionDefault_1230) {
    Object obj;
    obj.initNull();
    PageTransition pt(&obj);
    EXPECT_EQ(pt.getDirection(), pageTransitionInward);
}

// Test getAngle returns expected default
TEST_F(PageTransitionTest_1230, GetAngleDefault_1230) {
    Object obj;
    obj.initNull();
    PageTransition pt(&obj);
    EXPECT_EQ(pt.getAngle(), 0);
}

// Test getScale returns expected default
TEST_F(PageTransitionTest_1230, GetScaleDefault_1230) {
    Object obj;
    obj.initNull();
    PageTransition pt(&obj);
    EXPECT_DOUBLE_EQ(pt.getScale(), 1.0);
}

// Test isRectangular returns expected default
TEST_F(PageTransitionTest_1230, IsRectangularDefault_1230) {
    Object obj;
    obj.initNull();
    PageTransition pt(&obj);
    EXPECT_FALSE(pt.isRectangular());
}

// Test isOk returns true for valid construction
TEST_F(PageTransitionTest_1230, IsOkForValidConstruction_1230) {
    Object obj;
    obj.initNull();
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
}

// Test with a dictionary containing transition type "Split"
TEST_F(PageTransitionTest_1230, ConstructionWithSplitType_1230) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    
    Object typeObj;
    typeObj.initName("Split");
    obj.dictAdd("S", std::move(typeObj));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getType(), pageTransitionSplit);
}

// Test with a dictionary containing transition type "Blinds"
TEST_F(PageTransitionTest_1230, ConstructionWithBlindsType_1230) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    
    Object typeObj;
    typeObj.initName("Blinds");
    obj.dictAdd("S", std::move(typeObj));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getType(), pageTransitionBlinds);
}

// Test with a dictionary containing transition type "Box"
TEST_F(PageTransitionTest_1230, ConstructionWithBoxType_1230) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    
    Object typeObj;
    typeObj.initName("Box");
    obj.dictAdd("S", std::move(typeObj));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getType(), pageTransitionBox);
}

// Test with a dictionary containing transition type "Wipe"
TEST_F(PageTransitionTest_1230, ConstructionWithWipeType_1230) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    
    Object typeObj;
    typeObj.initName("Wipe");
    obj.dictAdd("S", std::move(typeObj));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getType(), pageTransitionWipe);
}

// Test with a dictionary containing transition type "Dissolve"
TEST_F(PageTransitionTest_1230, ConstructionWithDissolveType_1230) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    
    Object typeObj;
    typeObj.initName("Dissolve");
    obj.dictAdd("S", std::move(typeObj));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getType(), pageTransitionDissolve);
}

// Test with a dictionary containing transition type "Glitter"
TEST_F(PageTransitionTest_1230, ConstructionWithGlitterType_1230) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    
    Object typeObj;
    typeObj.initName("Glitter");
    obj.dictAdd("S", std::move(typeObj));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getType(), pageTransitionGlitter);
}

// Test with a dictionary containing transition type "R" (Replace)
TEST_F(PageTransitionTest_1230, ConstructionWithRType_1230) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    
    Object typeObj;
    typeObj.initName("R");
    obj.dictAdd("S", std::move(typeObj));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getType(), pageTransitionReplace);
}

// Test with custom duration
TEST_F(PageTransitionTest_1230, ConstructionWithCustomDuration_1230) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    
    Object durObj;
    durObj.initReal(3.5);
    obj.dictAdd("D", std::move(durObj));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_DOUBLE_EQ(pt.getDuration(), 3.5);
}

// Test with zero duration
TEST_F(PageTransitionTest_1230, ConstructionWithZeroDuration_1230) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    
    Object durObj;
    durObj.initReal(0.0);
    obj.dictAdd("D", std::move(durObj));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_DOUBLE_EQ(pt.getDuration(), 0.0);
}

// Test with vertical alignment
TEST_F(PageTransitionTest_1230, ConstructionWithVerticalAlignment_1230) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    
    Object typeObj;
    typeObj.initName("Split");
    obj.dictAdd("S", std::move(typeObj));
    
    Object dmObj;
    dmObj.initName("V");
    obj.dictAdd("Dm", std::move(dmObj));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getAlignment(), pageTransitionVertical);
}

// Test with horizontal alignment
TEST_F(PageTransitionTest_1230, ConstructionWithHorizontalAlignment_1230) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    
    Object typeObj;
    typeObj.initName("Blinds");
    obj.dictAdd("S", std::move(typeObj));
    
    Object dmObj;
    dmObj.initName("H");
    obj.dictAdd("Dm", std::move(dmObj));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getAlignment(), pageTransitionHorizontal);
}

// Test with outward direction
TEST_F(PageTransitionTest_1230, ConstructionWithOutwardDirection_1230) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    
    Object typeObj;
    typeObj.initName("Split");
    obj.dictAdd("S", std::move(typeObj));
    
    Object mObj;
    mObj.initName("O");
    obj.dictAdd("M", std::move(mObj));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getDirection(), pageTransitionOutward);
}

// Test with inward direction
TEST_F(PageTransitionTest_1230, ConstructionWithInwardDirection_1230) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    
    Object typeObj;
    typeObj.initName("Box");
    obj.dictAdd("S", std::move(typeObj));
    
    Object mObj;
    mObj.initName("I");
    obj.dictAdd("M", std::move(mObj));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getDirection(), pageTransitionInward);
}

// Test with custom angle
TEST_F(PageTransitionTest_1230, ConstructionWithCustomAngle_1230) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    
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

// Test with angle 270
TEST_F(PageTransitionTest_1230, ConstructionWithAngle270_1230) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    
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

// Test with rectangular set to true
TEST_F(PageTransitionTest_1230, ConstructionWithRectangularTrue_1230) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    
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

// Test with rectangular set to false
TEST_F(PageTransitionTest_1230, ConstructionWithRectangularFalse_1230) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    
    Object typeObj;
    typeObj.initName("Fly");
    obj.dictAdd("S", std::move(typeObj));
    
    Object bObj;
    bObj.initBool(false);
    obj.dictAdd("B", std::move(bObj));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_FALSE(pt.isRectangular());
}

// Test with custom scale
TEST_F(PageTransitionTest_1230, ConstructionWithCustomScale_1230) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    
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

// Test with Fly transition type
TEST_F(PageTransitionTest_1230, ConstructionWithFlyType_1230) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    
    Object typeObj;
    typeObj.initName("Fly");
    obj.dictAdd("S", std::move(typeObj));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getType(), pageTransitionFly);
}

// Test with Push transition type
TEST_F(PageTransitionTest_1230, ConstructionWithPushType_1230) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    
    Object typeObj;
    typeObj.initName("Push");
    obj.dictAdd("S", std::move(typeObj));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getType(), pageTransitionPush);
}

// Test with Cover transition type
TEST_F(PageTransitionTest_1230, ConstructionWithCoverType_1230) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    
    Object typeObj;
    typeObj.initName("Cover");
    obj.dictAdd("S", std::move(typeObj));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getType(), pageTransitionCover);
}

// Test with Uncover transition type
TEST_F(PageTransitionTest_1230, ConstructionWithUncoverType_1230) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    
    Object typeObj;
    typeObj.initName("Uncover");
    obj.dictAdd("S", std::move(typeObj));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getType(), pageTransitionUncover);
}

// Test with Fade transition type
TEST_F(PageTransitionTest_1230, ConstructionWithFadeType_1230) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    
    Object typeObj;
    typeObj.initName("Fade");
    obj.dictAdd("S", std::move(typeObj));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getType(), pageTransitionFade);
}

// Test with multiple properties set at once
TEST_F(PageTransitionTest_1230, ConstructionWithMultipleProperties_1230) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    
    Object typeObj;
    typeObj.initName("Split");
    obj.dictAdd("S", std::move(typeObj));
    
    Object durObj;
    durObj.initReal(2.0);
    obj.dictAdd("D", std::move(durObj));
    
    Object dmObj;
    dmObj.initName("V");
    obj.dictAdd("Dm", std::move(dmObj));
    
    Object mObj;
    mObj.initName("O");
    obj.dictAdd("M", std::move(mObj));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_EQ(pt.getType(), pageTransitionSplit);
    EXPECT_DOUBLE_EQ(pt.getDuration(), 2.0);
    EXPECT_EQ(pt.getAlignment(), pageTransitionVertical);
    EXPECT_EQ(pt.getDirection(), pageTransitionOutward);
}

// Test with integer duration
TEST_F(PageTransitionTest_1230, ConstructionWithIntegerDuration_1230) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    
    Object durObj;
    durObj.initInt(5);
    obj.dictAdd("D", std::move(durObj));
    
    PageTransition pt(&obj);
    EXPECT_TRUE(pt.isOk());
    EXPECT_DOUBLE_EQ(pt.getDuration(), 5.0);
}
