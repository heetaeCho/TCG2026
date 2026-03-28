#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Annot.h"
#include "Dict.h"
#include "Object.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

#include <memory>

class AnnotIconFitTest_759 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Helper to create a Dict with icon fit properties
static Object makeIconFitDict(const char *scaleWhen, const char *scale,
                               double left, double bottom, bool fullyBounds) {
    Object dictObj = Object(new Dict(nullptr));
    Dict *dict = dictObj.getDict();

    if (scaleWhen) {
        dict->add("SW", Object(objName, scaleWhen));
    }
    if (scale) {
        dict->add("S", Object(objName, scale));
    }

    Object arrObj = Object(new Array(nullptr));
    arrObj.arrayAdd(Object(left));
    arrObj.arrayAdd(Object(bottom));
    dict->add("A", std::move(arrObj));

    dict->add("FB", Object(fullyBounds));

    return dictObj;
}

TEST_F(AnnotIconFitTest_759, ConstructWithValidDict_759) {
    Object dictObj = makeIconFitDict("A", "A", 0.5, 0.5, true);
    AnnotIconFit iconFit(dictObj.getDict());

    // Should construct without crashing
    SUCCEED();
}

TEST_F(AnnotIconFitTest_759, GetScaleWhenAlways_759) {
    Object dictObj = makeIconFitDict("A", "A", 0.5, 0.5, false);
    AnnotIconFit iconFit(dictObj.getDict());

    AnnotIconFit::AnnotIconFitScaleWhen sw = iconFit.getScaleWhen();
    EXPECT_EQ(sw, AnnotIconFit::scaleAlways);
}

TEST_F(AnnotIconFitTest_759, GetScaleWhenBigger_759) {
    Object dictObj = makeIconFitDict("B", "A", 0.5, 0.5, false);
    AnnotIconFit iconFit(dictObj.getDict());

    EXPECT_EQ(iconFit.getScaleWhen(), AnnotIconFit::scaleBigger);
}

TEST_F(AnnotIconFitTest_759, GetScaleWhenSmaller_759) {
    Object dictObj = makeIconFitDict("S", "A", 0.5, 0.5, false);
    AnnotIconFit iconFit(dictObj.getDict());

    EXPECT_EQ(iconFit.getScaleWhen(), AnnotIconFit::scaleSmaller);
}

TEST_F(AnnotIconFitTest_759, GetScaleWhenNever_759) {
    Object dictObj = makeIconFitDict("N", "A", 0.5, 0.5, false);
    AnnotIconFit iconFit(dictObj.getDict());

    EXPECT_EQ(iconFit.getScaleWhen(), AnnotIconFit::scaleNever);
}

TEST_F(AnnotIconFitTest_759, GetScaleAnamorphic_759) {
    Object dictObj = makeIconFitDict("A", "A", 0.5, 0.5, false);
    AnnotIconFit iconFit(dictObj.getDict());

    EXPECT_EQ(iconFit.getScale(), AnnotIconFit::scaleAnamorphic);
}

TEST_F(AnnotIconFitTest_759, GetScaleProportional_759) {
    Object dictObj = makeIconFitDict("A", "P", 0.5, 0.5, false);
    AnnotIconFit iconFit(dictObj.getDict());

    EXPECT_EQ(iconFit.getScale(), AnnotIconFit::scaleProportional);
}

TEST_F(AnnotIconFitTest_759, GetLeftValue_759) {
    Object dictObj = makeIconFitDict("A", "A", 0.3, 0.7, false);
    AnnotIconFit iconFit(dictObj.getDict());

    EXPECT_DOUBLE_EQ(iconFit.getLeft(), 0.3);
}

TEST_F(AnnotIconFitTest_759, GetBottomValue_759) {
    Object dictObj = makeIconFitDict("A", "A", 0.3, 0.7, false);
    AnnotIconFit iconFit(dictObj.getDict());

    EXPECT_DOUBLE_EQ(iconFit.getBottom(), 0.7);
}

TEST_F(AnnotIconFitTest_759, GetFullyBoundsTrue_759) {
    Object dictObj = makeIconFitDict("A", "A", 0.5, 0.5, true);
    AnnotIconFit iconFit(dictObj.getDict());

    EXPECT_TRUE(iconFit.getFullyBounds());
}

TEST_F(AnnotIconFitTest_759, GetFullyBoundsFalse_759) {
    Object dictObj = makeIconFitDict("A", "A", 0.5, 0.5, false);
    AnnotIconFit iconFit(dictObj.getDict());

    EXPECT_FALSE(iconFit.getFullyBounds());
}

TEST_F(AnnotIconFitTest_759, GetLeftZero_759) {
    Object dictObj = makeIconFitDict("A", "A", 0.0, 0.0, false);
    AnnotIconFit iconFit(dictObj.getDict());

    EXPECT_DOUBLE_EQ(iconFit.getLeft(), 0.0);
}

TEST_F(AnnotIconFitTest_759, GetBottomZero_759) {
    Object dictObj = makeIconFitDict("A", "A", 0.0, 0.0, false);
    AnnotIconFit iconFit(dictObj.getDict());

    EXPECT_DOUBLE_EQ(iconFit.getBottom(), 0.0);
}

TEST_F(AnnotIconFitTest_759, GetLeftOne_759) {
    Object dictObj = makeIconFitDict("A", "A", 1.0, 1.0, false);
    AnnotIconFit iconFit(dictObj.getDict());

    EXPECT_DOUBLE_EQ(iconFit.getLeft(), 1.0);
}

TEST_F(AnnotIconFitTest_759, GetBottomOne_759) {
    Object dictObj = makeIconFitDict("A", "A", 1.0, 1.0, false);
    AnnotIconFit iconFit(dictObj.getDict());

    EXPECT_DOUBLE_EQ(iconFit.getBottom(), 1.0);
}

TEST_F(AnnotIconFitTest_759, DefaultScaleWhenNoSWKey_759) {
    Object dictObj = Object(new Dict(nullptr));
    Dict *dict = dictObj.getDict();
    // No SW key - should use default
    dict->add("S", Object(objName, "A"));
    Object arrObj = Object(new Array(nullptr));
    arrObj.arrayAdd(Object(0.5));
    arrObj.arrayAdd(Object(0.5));
    dict->add("A", std::move(arrObj));
    dict->add("FB", Object(false));

    AnnotIconFit iconFit(dict);

    // Default scaleWhen should be scaleAlways ("A")
    EXPECT_EQ(iconFit.getScaleWhen(), AnnotIconFit::scaleAlways);
}

TEST_F(AnnotIconFitTest_759, DefaultScaleNoSKey_759) {
    Object dictObj = Object(new Dict(nullptr));
    Dict *dict = dictObj.getDict();
    dict->add("SW", Object(objName, "A"));
    // No S key - should use default
    Object arrObj = Object(new Array(nullptr));
    arrObj.arrayAdd(Object(0.5));
    arrObj.arrayAdd(Object(0.5));
    dict->add("A", std::move(arrObj));
    dict->add("FB", Object(false));

    AnnotIconFit iconFit(dict);

    // Default scale should be scaleProportional ("P")
    EXPECT_EQ(iconFit.getScale(), AnnotIconFit::scaleProportional);
}

TEST_F(AnnotIconFitTest_759, EmptyDict_759) {
    Object dictObj = Object(new Dict(nullptr));
    Dict *dict = dictObj.getDict();

    AnnotIconFit iconFit(dict);

    // Should use defaults and not crash
    EXPECT_EQ(iconFit.getScaleWhen(), AnnotIconFit::scaleAlways);
    EXPECT_EQ(iconFit.getScale(), AnnotIconFit::scaleProportional);
    EXPECT_FALSE(iconFit.getFullyBounds());
}
