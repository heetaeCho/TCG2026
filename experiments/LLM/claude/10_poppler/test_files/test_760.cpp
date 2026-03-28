#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Annot.h"
#include "Dict.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "Object.h"

#include <memory>

class AnnotIconFitTest_760 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Helper to create a Dict with specific AnnotIconFit properties
static Dict *createIconFitDict(XRef *xref, const char *sw, const char *s, double left, double bottom, bool fb) {
    Dict *dict = new Dict(xref);
    
    if (sw) {
        dict->add("SW", Object(new GooString(sw)));
    }
    if (s) {
        dict->add("S", Object(new GooString(s)));
    }
    
    // A array [left bottom]
    Array *aArray = new Array(xref);
    aArray->add(Object(left));
    aArray->add(Object(bottom));
    dict->add("A", Object(aArray));
    
    dict->add("FB", Object(fb));
    
    return dict;
}

TEST_F(AnnotIconFitTest_760, ConstructWithNullDict_760) {
    // Test that constructing with a dict that has no entries uses defaults
    Dict dict(nullptr);
    AnnotIconFit iconFit(&dict);
    
    // Default scale should be some defined value
    AnnotIconFit::AnnotIconFitScale scale = iconFit.getScale();
    // Just verify it returns without crashing
    (void)scale;
}

TEST_F(AnnotIconFitTest_760, GetScaleReturnsValue_760) {
    Dict dict(nullptr);
    AnnotIconFit iconFit(&dict);
    
    AnnotIconFit::AnnotIconFitScale scale = iconFit.getScale();
    // Default behavior - just check it's a valid enum value
    // The enum values are typically: scaleAnamorphic, scaleProportional
    EXPECT_TRUE(scale == AnnotIconFit::scaleAnamorphic || scale == AnnotIconFit::scaleProportional);
}

TEST_F(AnnotIconFitTest_760, GetScaleWhenReturnsValue_760) {
    Dict dict(nullptr);
    AnnotIconFit iconFit(&dict);
    
    AnnotIconFit::AnnotIconFitScaleWhen scaleWhen = iconFit.getScaleWhen();
    // Default should be scaleAlways typically
    EXPECT_TRUE(scaleWhen == AnnotIconFit::scaleAlways || 
                scaleWhen == AnnotIconFit::scaleBigger ||
                scaleWhen == AnnotIconFit::scaleSmaller ||
                scaleWhen == AnnotIconFit::scaleNever);
}

TEST_F(AnnotIconFitTest_760, GetLeftDefaultValue_760) {
    Dict dict(nullptr);
    AnnotIconFit iconFit(&dict);
    
    double left = iconFit.getLeft();
    // Default is typically 0.5 (centered)
    EXPECT_GE(left, 0.0);
    EXPECT_LE(left, 1.0);
}

TEST_F(AnnotIconFitTest_760, GetBottomDefaultValue_760) {
    Dict dict(nullptr);
    AnnotIconFit iconFit(&dict);
    
    double bottom = iconFit.getBottom();
    // Default is typically 0.5 (centered)
    EXPECT_GE(bottom, 0.0);
    EXPECT_LE(bottom, 1.0);
}

TEST_F(AnnotIconFitTest_760, GetFullyBoundsDefaultValue_760) {
    Dict dict(nullptr);
    AnnotIconFit iconFit(&dict);
    
    bool fb = iconFit.getFullyBounds();
    // Default is typically false
    EXPECT_FALSE(fb);
}

TEST_F(AnnotIconFitTest_760, ScaleProportionalFromDict_760) {
    Dict dict(nullptr);
    dict.add("S", Object(new GooString("P")));
    
    AnnotIconFit iconFit(&dict);
    EXPECT_EQ(iconFit.getScale(), AnnotIconFit::scaleProportional);
}

TEST_F(AnnotIconFitTest_760, ScaleAnamorphicFromDict_760) {
    Dict dict(nullptr);
    dict.add("S", Object(new GooString("A")));
    
    AnnotIconFit iconFit(&dict);
    EXPECT_EQ(iconFit.getScale(), AnnotIconFit::scaleAnamorphic);
}

TEST_F(AnnotIconFitTest_760, ScaleWhenAlwaysFromDict_760) {
    Dict dict(nullptr);
    dict.add("SW", Object(new GooString("A")));
    
    AnnotIconFit iconFit(&dict);
    EXPECT_EQ(iconFit.getScaleWhen(), AnnotIconFit::scaleAlways);
}

TEST_F(AnnotIconFitTest_760, ScaleWhenBiggerFromDict_760) {
    Dict dict(nullptr);
    dict.add("SW", Object(new GooString("B")));
    
    AnnotIconFit iconFit(&dict);
    EXPECT_EQ(iconFit.getScaleWhen(), AnnotIconFit::scaleBigger);
}

TEST_F(AnnotIconFitTest_760, ScaleWhenSmallerFromDict_760) {
    Dict dict(nullptr);
    dict.add("SW", Object(new GooString("S")));
    
    AnnotIconFit iconFit(&dict);
    EXPECT_EQ(iconFit.getScaleWhen(), AnnotIconFit::scaleSmaller);
}

TEST_F(AnnotIconFitTest_760, ScaleWhenNeverFromDict_760) {
    Dict dict(nullptr);
    dict.add("SW", Object(new GooString("N")));
    
    AnnotIconFit iconFit(&dict);
    EXPECT_EQ(iconFit.getScaleWhen(), AnnotIconFit::scaleNever);
}

TEST_F(AnnotIconFitTest_760, FullyBoundsTrueFromDict_760) {
    Dict dict(nullptr);
    dict.add("FB", Object(true));
    
    AnnotIconFit iconFit(&dict);
    EXPECT_TRUE(iconFit.getFullyBounds());
}

TEST_F(AnnotIconFitTest_760, FullyBoundsFalseFromDict_760) {
    Dict dict(nullptr);
    dict.add("FB", Object(false));
    
    AnnotIconFit iconFit(&dict);
    EXPECT_FALSE(iconFit.getFullyBounds());
}

TEST_F(AnnotIconFitTest_760, CustomAlignmentFromDict_760) {
    Dict dict(nullptr);
    
    Array *aArray = new Array(nullptr);
    aArray->add(Object(0.3));
    aArray->add(Object(0.7));
    dict.add("A", Object(aArray));
    
    AnnotIconFit iconFit(&dict);
    EXPECT_DOUBLE_EQ(iconFit.getLeft(), 0.3);
    EXPECT_DOUBLE_EQ(iconFit.getBottom(), 0.7);
}

TEST_F(AnnotIconFitTest_760, ZeroAlignmentFromDict_760) {
    Dict dict(nullptr);
    
    Array *aArray = new Array(nullptr);
    aArray->add(Object(0.0));
    aArray->add(Object(0.0));
    dict.add("A", Object(aArray));
    
    AnnotIconFit iconFit(&dict);
    EXPECT_DOUBLE_EQ(iconFit.getLeft(), 0.0);
    EXPECT_DOUBLE_EQ(iconFit.getBottom(), 0.0);
}

TEST_F(AnnotIconFitTest_760, OneAlignmentFromDict_760) {
    Dict dict(nullptr);
    
    Array *aArray = new Array(nullptr);
    aArray->add(Object(1.0));
    aArray->add(Object(1.0));
    dict.add("A", Object(aArray));
    
    AnnotIconFit iconFit(&dict);
    EXPECT_DOUBLE_EQ(iconFit.getLeft(), 1.0);
    EXPECT_DOUBLE_EQ(iconFit.getBottom(), 1.0);
}

TEST_F(AnnotIconFitTest_760, AllPropertiesSetFromDict_760) {
    Dict dict(nullptr);
    
    dict.add("SW", Object(new GooString("B")));
    dict.add("S", Object(new GooString("P")));
    dict.add("FB", Object(true));
    
    Array *aArray = new Array(nullptr);
    aArray->add(Object(0.25));
    aArray->add(Object(0.75));
    dict.add("A", Object(aArray));
    
    AnnotIconFit iconFit(&dict);
    
    EXPECT_EQ(iconFit.getScaleWhen(), AnnotIconFit::scaleBigger);
    EXPECT_EQ(iconFit.getScale(), AnnotIconFit::scaleProportional);
    EXPECT_TRUE(iconFit.getFullyBounds());
    EXPECT_DOUBLE_EQ(iconFit.getLeft(), 0.25);
    EXPECT_DOUBLE_EQ(iconFit.getBottom(), 0.75);
}
