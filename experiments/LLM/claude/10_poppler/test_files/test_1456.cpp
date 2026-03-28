#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "poppler-qt5.h"
#include "poppler-page-transition.h"

#include <Object.h>
#include <PageTransition.h>

namespace {

class PageTransitionTest_1456 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test creating a PageTransition with a null/empty Object
TEST_F(PageTransitionTest_1456, DefaultConstruction_1456)
{
    Object obj;
    Poppler::PageTransition pt(&obj);
    
    // Default transition type should be Replace
    EXPECT_EQ(pt.type(), Poppler::PageTransition::Replace);
}

// Test that duration has a default value
TEST_F(PageTransitionTest_1456, DefaultDuration_1456)
{
    Object obj;
    Poppler::PageTransition pt(&obj);
    
    // Default duration is typically 1 second
    EXPECT_GE(pt.durationReal(), 0.0);
}

// Test alignment default
TEST_F(PageTransitionTest_1456, DefaultAlignment_1456)
{
    Object obj;
    Poppler::PageTransition pt(&obj);
    
    EXPECT_EQ(pt.alignment(), Poppler::PageTransition::Horizontal);
}

// Test direction default
TEST_F(PageTransitionTest_1456, DefaultDirection_1456)
{
    Object obj;
    Poppler::PageTransition pt(&obj);
    
    EXPECT_EQ(pt.direction(), Poppler::PageTransition::Inward);
}

// Test angle default
TEST_F(PageTransitionTest_1456, DefaultAngle_1456)
{
    Object obj;
    Poppler::PageTransition pt(&obj);
    
    EXPECT_GE(pt.angle(), 0);
}

// Test scale default
TEST_F(PageTransitionTest_1456, DefaultScale_1456)
{
    Object obj;
    Poppler::PageTransition pt(&obj);
    
    EXPECT_GE(pt.scale(), 0.0);
}

// Test rectangular default
TEST_F(PageTransitionTest_1456, DefaultRectangular_1456)
{
    Object obj;
    Poppler::PageTransition pt(&obj);
    
    // rectangular is a bool, just check it doesn't crash
    bool rect = pt.isRectangular();
    (void)rect;
    SUCCEED();
}

// Test copy constructor
TEST_F(PageTransitionTest_1456, CopyConstructor_1456)
{
    Object obj;
    Poppler::PageTransition pt1(&obj);
    Poppler::PageTransition pt2(pt1);
    
    EXPECT_EQ(pt1.type(), pt2.type());
    EXPECT_EQ(pt1.alignment(), pt2.alignment());
    EXPECT_EQ(pt1.direction(), pt2.direction());
    EXPECT_EQ(pt1.angle(), pt2.angle());
    EXPECT_DOUBLE_EQ(pt1.scale(), pt2.scale());
    EXPECT_DOUBLE_EQ(pt1.durationReal(), pt2.durationReal());
    EXPECT_EQ(pt1.isRectangular(), pt2.isRectangular());
}

// Test assignment operator
TEST_F(PageTransitionTest_1456, AssignmentOperator_1456)
{
    Object obj;
    Poppler::PageTransition pt1(&obj);
    Poppler::PageTransition pt2(&obj);
    
    pt2 = pt1;
    
    EXPECT_EQ(pt1.type(), pt2.type());
    EXPECT_EQ(pt1.alignment(), pt2.alignment());
    EXPECT_EQ(pt1.direction(), pt2.direction());
    EXPECT_EQ(pt1.angle(), pt2.angle());
    EXPECT_DOUBLE_EQ(pt1.scale(), pt2.scale());
    EXPECT_DOUBLE_EQ(pt1.durationReal(), pt2.durationReal());
    EXPECT_EQ(pt1.isRectangular(), pt2.isRectangular());
}

// Test with a dictionary Object specifying a transition type
TEST_F(PageTransitionTest_1456, DictWithSplitType_1456)
{
    Object obj;
    obj = Object(new Dict(nullptr));
    obj.dictAdd("Type", Object(objName, "Trans"));
    obj.dictAdd("S", Object(objName, "Split"));
    
    Poppler::PageTransition pt(&obj);
    EXPECT_EQ(pt.type(), Poppler::PageTransition::Split);
}

// Test with Blinds type
TEST_F(PageTransitionTest_1456, DictWithBlindsType_1456)
{
    Object obj;
    obj = Object(new Dict(nullptr));
    obj.dictAdd("Type", Object(objName, "Trans"));
    obj.dictAdd("S", Object(objName, "Blinds"));
    
    Poppler::PageTransition pt(&obj);
    EXPECT_EQ(pt.type(), Poppler::PageTransition::Blinds);
}

// Test duration from dict
TEST_F(PageTransitionTest_1456, DictWithDuration_1456)
{
    Object obj;
    obj = Object(new Dict(nullptr));
    obj.dictAdd("Type", Object(objName, "Trans"));
    obj.dictAdd("D", Object(2.5));
    
    Poppler::PageTransition pt(&obj);
    EXPECT_DOUBLE_EQ(pt.durationReal(), 2.5);
}

} // namespace
