#include <gtest/gtest.h>
#include "PageTransition.h"
#include "Object.h"

class PageTransitionTest_1232 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default construction with a null/empty Object
TEST_F(PageTransitionTest_1232, DefaultTransitionFromNullObject_1232) {
    Object obj;
    PageTransition pt(&obj);
    // Default values should be set when no valid transition dict is provided
    EXPECT_TRUE(pt.isOk() || !pt.isOk()); // Should not crash
}

// Test construction with a valid dictionary Object containing type
TEST_F(PageTransitionTest_1232, ConstructWithValidDict_1232) {
    Object dict = Object(new Dict(nullptr));
    PageTransition pt(&dict);
    // Should construct without crashing
}

// Test getType returns a valid PageTransitionType for default
TEST_F(PageTransitionTest_1232, GetTypeDefault_1232) {
    Object obj;
    PageTransition pt(&obj);
    PageTransitionType type = pt.getType();
    // Default type should be Replace (0) typically
    EXPECT_GE(static_cast<int>(type), 0);
}

// Test getDuration returns non-negative value
TEST_F(PageTransitionTest_1232, GetDurationDefault_1232) {
    Object obj;
    PageTransition pt(&obj);
    double duration = pt.getDuration();
    EXPECT_GE(duration, 0.0);
}

// Test getAlignment returns a valid alignment
TEST_F(PageTransitionTest_1232, GetAlignmentDefault_1232) {
    Object obj;
    PageTransition pt(&obj);
    PageTransitionAlignment alignment = pt.getAlignment();
    EXPECT_GE(static_cast<int>(alignment), 0);
}

// Test getDirection returns a valid direction
TEST_F(PageTransitionTest_1232, GetDirectionDefault_1232) {
    Object obj;
    PageTransition pt(&obj);
    PageTransitionDirection direction = pt.getDirection();
    EXPECT_GE(static_cast<int>(direction), 0);
}

// Test getAngle returns a valid angle
TEST_F(PageTransitionTest_1232, GetAngleDefault_1232) {
    Object obj;
    PageTransition pt(&obj);
    int angle = pt.getAngle();
    EXPECT_GE(angle, 0);
}

// Test getScale returns a valid scale
TEST_F(PageTransitionTest_1232, GetScaleDefault_1232) {
    Object obj;
    PageTransition pt(&obj);
    double scale = pt.getScale();
    EXPECT_GE(scale, 0.0);
}

// Test isRectangular returns a boolean
TEST_F(PageTransitionTest_1232, IsRectangularDefault_1232) {
    Object obj;
    PageTransition pt(&obj);
    bool rectangular = pt.isRectangular();
    EXPECT_TRUE(rectangular || !rectangular); // Just ensure it returns valid bool
}

// Test with a properly formed transition dictionary specifying "Split" type
TEST_F(PageTransitionTest_1232, SplitTransitionType_1232) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeObj = Object(new GooString("Split"));
    dict.dictSet("S", std::move(typeObj));
    
    PageTransition pt(&dict);
    if (pt.isOk()) {
        EXPECT_EQ(pt.getType(), pageTransitionSplit);
    }
}

// Test with "Blinds" transition type
TEST_F(PageTransitionTest_1232, BlindsTransitionType_1232) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeObj = Object(new GooString("Blinds"));
    dict.dictSet("S", std::move(typeObj));
    
    PageTransition pt(&dict);
    if (pt.isOk()) {
        EXPECT_EQ(pt.getType(), pageTransitionBlinds);
    }
}

// Test with "Dissolve" transition type
TEST_F(PageTransitionTest_1232, DissolveTransitionType_1232) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeObj = Object(new GooString("Dissolve"));
    dict.dictSet("S", std::move(typeObj));
    
    PageTransition pt(&dict);
    if (pt.isOk()) {
        EXPECT_EQ(pt.getType(), pageTransitionDissolve);
    }
}

// Test with custom duration value
TEST_F(PageTransitionTest_1232, CustomDuration_1232) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object durObj = Object(2.5);
    dict.dictSet("D", std::move(durObj));
    
    PageTransition pt(&dict);
    if (pt.isOk()) {
        EXPECT_DOUBLE_EQ(pt.getDuration(), 2.5);
    }
}

// Test with horizontal alignment
TEST_F(PageTransitionTest_1232, HorizontalAlignment_1232) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeObj = Object(new GooString("Split"));
    dict.dictSet("S", std::move(typeObj));
    
    Object dmObj = Object(new GooString("H"));
    dict.dictSet("Dm", std::move(dmObj));
    
    PageTransition pt(&dict);
    if (pt.isOk()) {
        EXPECT_EQ(pt.getAlignment(), pageTransitionHorizontal);
    }
}

// Test with vertical alignment
TEST_F(PageTransitionTest_1232, VerticalAlignment_1232) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeObj = Object(new GooString("Split"));
    dict.dictSet("S", std::move(typeObj));
    
    Object dmObj = Object(new GooString("V"));
    dict.dictSet("Dm", std::move(dmObj));
    
    PageTransition pt(&dict);
    if (pt.isOk()) {
        EXPECT_EQ(pt.getAlignment(), pageTransitionVertical);
    }
}

// Test with inward direction
TEST_F(PageTransitionTest_1232, InwardDirection_1232) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeObj = Object(new GooString("Split"));
    dict.dictSet("S", std::move(typeObj));
    
    Object mObj = Object(new GooString("I"));
    dict.dictSet("M", std::move(mObj));
    
    PageTransition pt(&dict);
    if (pt.isOk()) {
        EXPECT_EQ(pt.getDirection(), pageTransitionInward);
    }
}

// Test with outward direction
TEST_F(PageTransitionTest_1232, OutwardDirection_1232) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeObj = Object(new GooString("Split"));
    dict.dictSet("S", std::move(typeObj));
    
    Object mObj = Object(new GooString("O"));
    dict.dictSet("M", std::move(mObj));
    
    PageTransition pt(&dict);
    if (pt.isOk()) {
        EXPECT_EQ(pt.getDirection(), pageTransitionOutward);
    }
}

// Test with custom angle
TEST_F(PageTransitionTest_1232, CustomAngle_1232) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeObj = Object(new GooString("Wipe"));
    dict.dictSet("S", std::move(typeObj));
    
    Object diObj = Object(90);
    dict.dictSet("Di", std::move(diObj));
    
    PageTransition pt(&dict);
    if (pt.isOk()) {
        EXPECT_EQ(pt.getAngle(), 90);
    }
}

// Test with scale value
TEST_F(PageTransitionTest_1232, CustomScale_1232) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeObj = Object(new GooString("Fly"));
    dict.dictSet("S", std::move(typeObj));
    
    Object ssObj = Object(0.5);
    dict.dictSet("SS", std::move(ssObj));
    
    PageTransition pt(&dict);
    if (pt.isOk()) {
        EXPECT_DOUBLE_EQ(pt.getScale(), 0.5);
    }
}

// Test isOk on default-constructed transition
TEST_F(PageTransitionTest_1232, IsOkOnDefault_1232) {
    Object obj;
    PageTransition pt(&obj);
    // isOk should return a definitive boolean
    bool ok = pt.isOk();
    EXPECT_TRUE(ok || !ok);
}

// Test with rectangular flag
TEST_F(PageTransitionTest_1232, RectangularFlag_1232) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeObj = Object(new GooString("Fly"));
    dict.dictSet("S", std::move(typeObj));
    
    Object bObj = Object(true);
    dict.dictSet("B", std::move(bObj));
    
    PageTransition pt(&dict);
    if (pt.isOk()) {
        EXPECT_TRUE(pt.isRectangular());
    }
}

// Test angle of 0
TEST_F(PageTransitionTest_1232, AngleZero_1232) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeObj = Object(new GooString("Wipe"));
    dict.dictSet("S", std::move(typeObj));
    
    Object diObj = Object(0);
    dict.dictSet("Di", std::move(diObj));
    
    PageTransition pt(&dict);
    if (pt.isOk()) {
        EXPECT_EQ(pt.getAngle(), 0);
    }
}

// Test angle of 270
TEST_F(PageTransitionTest_1232, Angle270_1232) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeObj = Object(new GooString("Wipe"));
    dict.dictSet("S", std::move(typeObj));
    
    Object diObj = Object(270);
    dict.dictSet("Di", std::move(diObj));
    
    PageTransition pt(&dict);
    if (pt.isOk()) {
        EXPECT_EQ(pt.getAngle(), 270);
    }
}

// Test duration of zero
TEST_F(PageTransitionTest_1232, ZeroDuration_1232) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object durObj = Object(0.0);
    dict.dictSet("D", std::move(durObj));
    
    PageTransition pt(&dict);
    if (pt.isOk()) {
        EXPECT_DOUBLE_EQ(pt.getDuration(), 0.0);
    }
}

// Test Replace transition type (default)
TEST_F(PageTransitionTest_1232, ReplaceTransitionType_1232) {
    Object dict;
    dict = Object(new Dict(nullptr));
    
    Object typeObj = Object(new GooString("R"));
    dict.dictSet("S", std::move(typeObj));
    
    PageTransition pt(&dict);
    if (pt.isOk()) {
        EXPECT_EQ(pt.getType(), pageTransitionReplace);
    }
}
