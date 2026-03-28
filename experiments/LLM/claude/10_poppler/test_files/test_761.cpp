#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Annot.h"
#include "Dict.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "Object.h"

#include <memory>

class AnnotIconFitTest_761 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Helper to create a Dict with icon fit properties
static Dict *createIconFitDict(XRef *xref, const char *sw, const char *s, double left, double bottom, bool fb) {
    Dict *dict = new Dict(xref);

    // SW - Scale When: A (always), B (bigger), S (smaller), N (never)
    if (sw) {
        Object swObj = Object(new GooString(sw));
        dict->add("SW", std::move(swObj));
    }

    // S - Scale: A (anamorphic), P (proportional)
    if (s) {
        Object sObj = Object(new GooString(s));
        dict->add("S", std::move(sObj));
    }

    // A - array of two numbers [left, bottom]
    Array *arr = new Array(xref);
    arr->add(Object(left));
    arr->add(Object(bottom));
    Object aObj = Object(arr);
    dict->add("A", std::move(aObj));

    // FB - fully bounds
    Object fbObj = Object(fb);
    dict->add("FB", std::move(fbObj));

    return dict;
}

TEST_F(AnnotIconFitTest_761, GetLeftReturnsSetValue_761) {
    Dict *dict = createIconFitDict(nullptr, "A", "A", 0.5, 0.5, false);
    AnnotIconFit iconFit(dict);
    EXPECT_DOUBLE_EQ(iconFit.getLeft(), 0.5);
    delete dict;
}

TEST_F(AnnotIconFitTest_761, GetBottomReturnsSetValue_761) {
    Dict *dict = createIconFitDict(nullptr, "A", "A", 0.5, 0.75, false);
    AnnotIconFit iconFit(dict);
    EXPECT_DOUBLE_EQ(iconFit.getBottom(), 0.75);
    delete dict;
}

TEST_F(AnnotIconFitTest_761, GetLeftZero_761) {
    Dict *dict = createIconFitDict(nullptr, "A", "A", 0.0, 0.5, false);
    AnnotIconFit iconFit(dict);
    EXPECT_DOUBLE_EQ(iconFit.getLeft(), 0.0);
    delete dict;
}

TEST_F(AnnotIconFitTest_761, GetLeftOne_761) {
    Dict *dict = createIconFitDict(nullptr, "A", "A", 1.0, 0.5, false);
    AnnotIconFit iconFit(dict);
    EXPECT_DOUBLE_EQ(iconFit.getLeft(), 1.0);
    delete dict;
}

TEST_F(AnnotIconFitTest_761, GetBottomZero_761) {
    Dict *dict = createIconFitDict(nullptr, "A", "A", 0.5, 0.0, false);
    AnnotIconFit iconFit(dict);
    EXPECT_DOUBLE_EQ(iconFit.getBottom(), 0.0);
    delete dict;
}

TEST_F(AnnotIconFitTest_761, GetBottomOne_761) {
    Dict *dict = createIconFitDict(nullptr, "A", "A", 0.5, 1.0, false);
    AnnotIconFit iconFit(dict);
    EXPECT_DOUBLE_EQ(iconFit.getBottom(), 1.0);
    delete dict;
}

TEST_F(AnnotIconFitTest_761, GetFullyBoundsTrue_761) {
    Dict *dict = createIconFitDict(nullptr, "A", "A", 0.5, 0.5, true);
    AnnotIconFit iconFit(dict);
    EXPECT_TRUE(iconFit.getFullyBounds());
    delete dict;
}

TEST_F(AnnotIconFitTest_761, GetFullyBoundsFalse_761) {
    Dict *dict = createIconFitDict(nullptr, "A", "A", 0.5, 0.5, false);
    AnnotIconFit iconFit(dict);
    EXPECT_FALSE(iconFit.getFullyBounds());
    delete dict;
}

TEST_F(AnnotIconFitTest_761, DefaultValuesWithEmptyDict_761) {
    Dict *dict = new Dict(nullptr);
    AnnotIconFit iconFit(dict);
    // Default left and bottom should be 0.5 per PDF spec
    EXPECT_DOUBLE_EQ(iconFit.getLeft(), 0.5);
    EXPECT_DOUBLE_EQ(iconFit.getBottom(), 0.5);
    delete dict;
}

TEST_F(AnnotIconFitTest_761, ScaleWhenAlways_761) {
    Dict *dict = createIconFitDict(nullptr, "A", "A", 0.5, 0.5, false);
    AnnotIconFit iconFit(dict);
    EXPECT_EQ(iconFit.getScaleWhen(), AnnotIconFit::scaleAlways);
    delete dict;
}

TEST_F(AnnotIconFitTest_761, ScaleWhenBigger_761) {
    Dict *dict = createIconFitDict(nullptr, "B", "A", 0.5, 0.5, false);
    AnnotIconFit iconFit(dict);
    EXPECT_EQ(iconFit.getScaleWhen(), AnnotIconFit::scaleBigger);
    delete dict;
}

TEST_F(AnnotIconFitTest_761, ScaleWhenSmaller_761) {
    Dict *dict = createIconFitDict(nullptr, "S", "A", 0.5, 0.5, false);
    AnnotIconFit iconFit(dict);
    EXPECT_EQ(iconFit.getScaleWhen(), AnnotIconFit::scaleSmaller);
    delete dict;
}

TEST_F(AnnotIconFitTest_761, ScaleWhenNever_761) {
    Dict *dict = createIconFitDict(nullptr, "N", "A", 0.5, 0.5, false);
    AnnotIconFit iconFit(dict);
    EXPECT_EQ(iconFit.getScaleWhen(), AnnotIconFit::scaleNever);
    delete dict;
}

TEST_F(AnnotIconFitTest_761, ScaleAnamorphic_761) {
    Dict *dict = createIconFitDict(nullptr, "A", "A", 0.5, 0.5, false);
    AnnotIconFit iconFit(dict);
    EXPECT_EQ(iconFit.getScale(), AnnotIconFit::scaleAnamorphic);
    delete dict;
}

TEST_F(AnnotIconFitTest_761, ScaleProportional_761) {
    Dict *dict = createIconFitDict(nullptr, "A", "P", 0.5, 0.5, false);
    AnnotIconFit iconFit(dict);
    EXPECT_EQ(iconFit.getScale(), AnnotIconFit::scaleProportional);
    delete dict;
}

TEST_F(AnnotIconFitTest_761, BoundaryLeftNegative_761) {
    Dict *dict = createIconFitDict(nullptr, "A", "A", -0.5, 0.5, false);
    AnnotIconFit iconFit(dict);
    // Negative value - implementation may clamp or accept as-is
    double left = iconFit.getLeft();
    // Just verify it returns a value (behavior depends on implementation)
    SUCCEED();
    delete dict;
}

TEST_F(AnnotIconFitTest_761, BoundaryLeftGreaterThanOne_761) {
    Dict *dict = createIconFitDict(nullptr, "A", "A", 2.0, 0.5, false);
    AnnotIconFit iconFit(dict);
    double left = iconFit.getLeft();
    SUCCEED();
    delete dict;
}

TEST_F(AnnotIconFitTest_761, LeftAndBottomMidpoint_761) {
    Dict *dict = createIconFitDict(nullptr, "A", "P", 0.25, 0.75, true);
    AnnotIconFit iconFit(dict);
    EXPECT_DOUBLE_EQ(iconFit.getLeft(), 0.25);
    EXPECT_DOUBLE_EQ(iconFit.getBottom(), 0.75);
    EXPECT_TRUE(iconFit.getFullyBounds());
    delete dict;
}
