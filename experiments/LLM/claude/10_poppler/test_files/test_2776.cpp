#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include the necessary headers for Poppler's PageTransition
#include "poppler-qt5.h"
#include "poppler-page-transition.h"

// We need access to Object for creating test transitions
#include "Object.h"
#include "PageTransition.h"

namespace {

class PageTransitionTest_2776 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test default construction via a null/empty Object
TEST_F(PageTransitionTest_2776, ConstructFromNullObject_2776) {
    Object obj;
    obj.initNull();
    Poppler::PageTransition pt(&obj);
    // Default transition type should be Replace
    EXPECT_EQ(pt.type(), Poppler::PageTransition::Replace);
    // Default duration
    EXPECT_EQ(pt.durationReal(), 1.0);
}

// Test copy constructor preserves transition type
TEST_F(PageTransitionTest_2776, CopyConstructorPreservesType_2776) {
    Object obj;
    obj.initNull();
    Poppler::PageTransition pt1(&obj);
    Poppler::PageTransition pt2(pt1);
    EXPECT_EQ(pt1.type(), pt2.type());
}

// Test copy constructor preserves duration
TEST_F(PageTransitionTest_2776, CopyConstructorPreservesDuration_2776) {
    Object obj;
    obj.initNull();
    Poppler::PageTransition pt1(&obj);
    Poppler::PageTransition pt2(pt1);
    EXPECT_DOUBLE_EQ(pt1.durationReal(), pt2.durationReal());
}

// Test copy constructor preserves alignment
TEST_F(PageTransitionTest_2776, CopyConstructorPreservesAlignment_2776) {
    Object obj;
    obj.initNull();
    Poppler::PageTransition pt1(&obj);
    Poppler::PageTransition pt2(pt1);
    EXPECT_EQ(pt1.alignment(), pt2.alignment());
}

// Test copy constructor preserves direction
TEST_F(PageTransitionTest_2776, CopyConstructorPreservesDirection_2776) {
    Object obj;
    obj.initNull();
    Poppler::PageTransition pt1(&obj);
    Poppler::PageTransition pt2(pt1);
    EXPECT_EQ(pt1.direction(), pt2.direction());
}

// Test copy constructor preserves angle
TEST_F(PageTransitionTest_2776, CopyConstructorPreservesAngle_2776) {
    Object obj;
    obj.initNull();
    Poppler::PageTransition pt1(&obj);
    Poppler::PageTransition pt2(pt1);
    EXPECT_EQ(pt1.angle(), pt2.angle());
}

// Test copy constructor preserves scale
TEST_F(PageTransitionTest_2776, CopyConstructorPreservesScale_2776) {
    Object obj;
    obj.initNull();
    Poppler::PageTransition pt1(&obj);
    Poppler::PageTransition pt2(pt1);
    EXPECT_DOUBLE_EQ(pt1.scale(), pt2.scale());
}

// Test copy constructor preserves rectangular flag
TEST_F(PageTransitionTest_2776, CopyConstructorPreservesRectangular_2776) {
    Object obj;
    obj.initNull();
    Poppler::PageTransition pt1(&obj);
    Poppler::PageTransition pt2(pt1);
    EXPECT_EQ(pt1.isRectangular(), pt2.isRectangular());
}

// Test that default alignment is horizontal
TEST_F(PageTransitionTest_2776, DefaultAlignmentIsHorizontal_2776) {
    Object obj;
    obj.initNull();
    Poppler::PageTransition pt(&obj);
    EXPECT_EQ(pt.alignment(), Poppler::PageTransition::Horizontal);
}

// Test that default direction is inward
TEST_F(PageTransitionTest_2776, DefaultDirectionIsInward_2776) {
    Object obj;
    obj.initNull();
    Poppler::PageTransition pt(&obj);
    EXPECT_EQ(pt.direction(), Poppler::PageTransition::Inward);
}

// Test that default angle is 0
TEST_F(PageTransitionTest_2776, DefaultAngle_2776) {
    Object obj;
    obj.initNull();
    Poppler::PageTransition pt(&obj);
    EXPECT_EQ(pt.angle(), 0);
}

// Test that default scale is 1.0
TEST_F(PageTransitionTest_2776, DefaultScale_2776) {
    Object obj;
    obj.initNull();
    Poppler::PageTransition pt(&obj);
    EXPECT_DOUBLE_EQ(pt.scale(), 1.0);
}

// Test that default rectangular is false
TEST_F(PageTransitionTest_2776, DefaultRectangular_2776) {
    Object obj;
    obj.initNull();
    Poppler::PageTransition pt(&obj);
    EXPECT_FALSE(pt.isRectangular());
}

// Test construction from a dictionary with type "Wipe"
TEST_F(PageTransitionTest_2776, ConstructWithWipeType_2776) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    Object typeObj;
    typeObj.initName("Wipe");
    obj.dictAdd(copyString("S"), &typeObj);
    
    Poppler::PageTransition pt(&obj);
    EXPECT_EQ(pt.type(), Poppler::PageTransition::Wipe);
}

// Test construction from a dictionary with type "Dissolve"
TEST_F(PageTransitionTest_2776, ConstructWithDissolveType_2776) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    Object typeObj;
    typeObj.initName("Dissolve");
    obj.dictAdd(copyString("S"), &typeObj);
    
    Poppler::PageTransition pt(&obj);
    EXPECT_EQ(pt.type(), Poppler::PageTransition::Dissolve);
}

// Test construction from a dictionary with custom duration
TEST_F(PageTransitionTest_2776, ConstructWithCustomDuration_2776) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    Object durObj;
    durObj.initReal(2.5);
    obj.dictAdd(copyString("D"), &durObj);
    
    Poppler::PageTransition pt(&obj);
    EXPECT_DOUBLE_EQ(pt.durationReal(), 2.5);
}

// Test copy is independent (modifying copy doesn't affect original)
TEST_F(PageTransitionTest_2776, CopyIsIndependent_2776) {
    Object obj;
    obj.initNull();
    Poppler::PageTransition pt1(&obj);
    Poppler::PageTransition pt2(pt1);
    
    // Both should have the same values but be independent objects
    EXPECT_EQ(pt1.type(), pt2.type());
    EXPECT_DOUBLE_EQ(pt1.durationReal(), pt2.durationReal());
}

// Test construction with Split type
TEST_F(PageTransitionTest_2776, ConstructWithSplitType_2776) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    Object typeObj;
    typeObj.initName("Split");
    obj.dictAdd(copyString("S"), &typeObj);
    
    Poppler::PageTransition pt(&obj);
    EXPECT_EQ(pt.type(), Poppler::PageTransition::Split);
}

// Test construction with Blinds type
TEST_F(PageTransitionTest_2776, ConstructWithBlindsType_2776) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    Object typeObj;
    typeObj.initName("Blinds");
    obj.dictAdd(copyString("S"), &typeObj);
    
    Poppler::PageTransition pt(&obj);
    EXPECT_EQ(pt.type(), Poppler::PageTransition::Blinds);
}

// Test construction with Box type
TEST_F(PageTransitionTest_2776, ConstructWithBoxType_2776) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    Object typeObj;
    typeObj.initName("Box");
    obj.dictAdd(copyString("S"), &typeObj);
    
    Poppler::PageTransition pt(&obj);
    EXPECT_EQ(pt.type(), Poppler::PageTransition::Box);
}

// Test construction with Fly type
TEST_F(PageTransitionTest_2776, ConstructWithFlyType_2776) {
    Object obj;
    obj.initDict((XRef*)nullptr);
    Object typeObj;
    typeObj.initName("Fly");
    obj.dictAdd(copyString("S"), &typeObj);
    
    Poppler::PageTransition pt(&obj);
    EXPECT_EQ(pt.type(), Poppler::PageTransition::Fly);
}

} // namespace
