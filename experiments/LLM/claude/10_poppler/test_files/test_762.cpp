#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Annot.h"
#include "Dict.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "Object.h"

#include <memory>

class AnnotIconFitTest_762 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Helper to create an AnnotIconFit from a Dict with specific values
static std::unique_ptr<AnnotIconFit> createAnnotIconFit(Object &dictObj) {
    Dict *dict = dictObj.getDict();
    return std::make_unique<AnnotIconFit>(dict);
}

TEST_F(AnnotIconFitTest_762, DefaultValuesFromEmptyDict_762) {
    // Test that an empty dictionary results in default values
    Object dictObj = Object(new Dict(nullptr));
    auto iconFit = createAnnotIconFit(dictObj);

    // Default values should be returned for an empty dict
    // Typically defaults: scaleWhen=Always, scale=Proportional, left=0.5, bottom=0.5, fullyBounds=false
    EXPECT_DOUBLE_EQ(iconFit->getBottom(), 0.5);
    EXPECT_DOUBLE_EQ(iconFit->getLeft(), 0.5);
    EXPECT_EQ(iconFit->getFullyBounds(), false);
}

TEST_F(AnnotIconFitTest_762, GetBottomReturnsSetValue_762) {
    Object dictObj = Object(new Dict(nullptr));
    Dict *dict = dictObj.getDict();

    // Create an A array with [left, bottom]
    Object arrObj = Object(new Array(nullptr));
    arrObj.arrayAdd(Object(0.3));
    arrObj.arrayAdd(Object(0.7));
    dict->add("A", std::move(arrObj));

    auto iconFit = createAnnotIconFit(dictObj);
    EXPECT_DOUBLE_EQ(iconFit->getBottom(), 0.7);
}

TEST_F(AnnotIconFitTest_762, GetLeftReturnsSetValue_762) {
    Object dictObj = Object(new Dict(nullptr));
    Dict *dict = dictObj.getDict();

    Object arrObj = Object(new Array(nullptr));
    arrObj.arrayAdd(Object(0.2));
    arrObj.arrayAdd(Object(0.8));
    dict->add("A", std::move(arrObj));

    auto iconFit = createAnnotIconFit(dictObj);
    EXPECT_DOUBLE_EQ(iconFit->getLeft(), 0.2);
}

TEST_F(AnnotIconFitTest_762, GetFullyBoundsTrue_762) {
    Object dictObj = Object(new Dict(nullptr));
    Dict *dict = dictObj.getDict();

    dict->add("FB", Object(true));

    auto iconFit = createAnnotIconFit(dictObj);
    EXPECT_TRUE(iconFit->getFullyBounds());
}

TEST_F(AnnotIconFitTest_762, GetFullyBoundsFalse_762) {
    Object dictObj = Object(new Dict(nullptr));
    Dict *dict = dictObj.getDict();

    dict->add("FB", Object(false));

    auto iconFit = createAnnotIconFit(dictObj);
    EXPECT_FALSE(iconFit->getFullyBounds());
}

TEST_F(AnnotIconFitTest_762, ScaleWhenAlways_762) {
    Object dictObj = Object(new Dict(nullptr));
    Dict *dict = dictObj.getDict();

    dict->add("SW", Object(objName, "A"));

    auto iconFit = createAnnotIconFit(dictObj);
    EXPECT_EQ(iconFit->getScaleWhen(), AnnotIconFit::scaleAlways);
}

TEST_F(AnnotIconFitTest_762, ScaleWhenNever_762) {
    Object dictObj = Object(new Dict(nullptr));
    Dict *dict = dictObj.getDict();

    dict->add("SW", Object(objName, "N"));

    auto iconFit = createAnnotIconFit(dictObj);
    EXPECT_EQ(iconFit->getScaleWhen(), AnnotIconFit::scaleNever);
}

TEST_F(AnnotIconFitTest_762, ScaleWhenBigger_762) {
    Object dictObj = Object(new Dict(nullptr));
    Dict *dict = dictObj.getDict();

    dict->add("SW", Object(objName, "B"));

    auto iconFit = createAnnotIconFit(dictObj);
    EXPECT_EQ(iconFit->getScaleWhen(), AnnotIconFit::scaleBigger);
}

TEST_F(AnnotIconFitTest_762, ScaleWhenSmaller_762) {
    Object dictObj = Object(new Dict(nullptr));
    Dict *dict = dictObj.getDict();

    dict->add("SW", Object(objName, "S"));

    auto iconFit = createAnnotIconFit(dictObj);
    EXPECT_EQ(iconFit->getScaleWhen(), AnnotIconFit::scaleSmaller);
}

TEST_F(AnnotIconFitTest_762, ScaleProportional_762) {
    Object dictObj = Object(new Dict(nullptr));
    Dict *dict = dictObj.getDict();

    dict->add("S", Object(objName, "P"));

    auto iconFit = createAnnotIconFit(dictObj);
    EXPECT_EQ(iconFit->getScale(), AnnotIconFit::scaleProportional);
}

TEST_F(AnnotIconFitTest_762, ScaleAnamorphic_762) {
    Object dictObj = Object(new Dict(nullptr));
    Dict *dict = dictObj.getDict();

    dict->add("S", Object(objName, "A"));

    auto iconFit = createAnnotIconFit(dictObj);
    EXPECT_EQ(iconFit->getScale(), AnnotIconFit::scaleAnamorphic);
}

TEST_F(AnnotIconFitTest_762, BoundaryBottomZero_762) {
    Object dictObj = Object(new Dict(nullptr));
    Dict *dict = dictObj.getDict();

    Object arrObj = Object(new Array(nullptr));
    arrObj.arrayAdd(Object(0.0));
    arrObj.arrayAdd(Object(0.0));
    dict->add("A", std::move(arrObj));

    auto iconFit = createAnnotIconFit(dictObj);
    EXPECT_DOUBLE_EQ(iconFit->getBottom(), 0.0);
    EXPECT_DOUBLE_EQ(iconFit->getLeft(), 0.0);
}

TEST_F(AnnotIconFitTest_762, BoundaryBottomOne_762) {
    Object dictObj = Object(new Dict(nullptr));
    Dict *dict = dictObj.getDict();

    Object arrObj = Object(new Array(nullptr));
    arrObj.arrayAdd(Object(1.0));
    arrObj.arrayAdd(Object(1.0));
    dict->add("A", std::move(arrObj));

    auto iconFit = createAnnotIconFit(dictObj);
    EXPECT_DOUBLE_EQ(iconFit->getBottom(), 1.0);
    EXPECT_DOUBLE_EQ(iconFit->getLeft(), 1.0);
}

TEST_F(AnnotIconFitTest_762, AllFieldsSetTogether_762) {
    Object dictObj = Object(new Dict(nullptr));
    Dict *dict = dictObj.getDict();

    dict->add("SW", Object(objName, "B"));
    dict->add("S", Object(objName, "A"));
    dict->add("FB", Object(true));

    Object arrObj = Object(new Array(nullptr));
    arrObj.arrayAdd(Object(0.25));
    arrObj.arrayAdd(Object(0.75));
    dict->add("A", std::move(arrObj));

    auto iconFit = createAnnotIconFit(dictObj);

    EXPECT_EQ(iconFit->getScaleWhen(), AnnotIconFit::scaleBigger);
    EXPECT_EQ(iconFit->getScale(), AnnotIconFit::scaleAnamorphic);
    EXPECT_DOUBLE_EQ(iconFit->getLeft(), 0.25);
    EXPECT_DOUBLE_EQ(iconFit->getBottom(), 0.75);
    EXPECT_TRUE(iconFit->getFullyBounds());
}
