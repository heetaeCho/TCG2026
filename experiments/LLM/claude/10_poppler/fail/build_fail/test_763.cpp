#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Annot.h"
#include "Dict.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "Object.h"

#include <memory>

class AnnotIconFitTest_763 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Helper to create an AnnotIconFit from a Dict with specific entries
static std::unique_ptr<AnnotIconFit> createAnnotIconFitFromDict(
    const char *scaleWhenName,
    const char *scaleName,
    double left, double bottom,
    bool fullyBounds)
{
    // We need to build a Dict object with the IF dictionary entries
    // SW: scale when (A, B, S, N)
    // S: scale (A, P)
    // A: array [left, bottom]
    // FB: fully bounds (boolean)

    auto xref = (XRef *)nullptr; // For simplicity, many Dict operations accept nullptr
    Dict *dict = new Dict(xref);

    if (scaleWhenName) {
        Object swObj = Object(new GooString(scaleWhenName));
        // SW is a name
        swObj = Object(objName, scaleWhenName);
        dict->add("SW", std::move(swObj));
    }

    if (scaleName) {
        Object sObj = Object(objName, scaleName);
        dict->add("S", std::move(sObj));
    }

    // A array: [left, bottom]
    Array *arr = new Array(xref);
    arr->add(Object(left));
    arr->add(Object(bottom));
    dict->add("A", Object(arr));

    // FB: fully bounds
    dict->add("FB", Object(fullyBounds));

    auto iconFit = std::make_unique<AnnotIconFit>(dict);
    // Dict is ref-counted, the AnnotIconFit constructor should manage it
    return iconFit;
}

TEST_F(AnnotIconFitTest_763, GetFullyBoundsTrue_763) {
    // Test that getFullyBounds returns true when FB is set to true
    auto iconFit = createAnnotIconFitFromDict("A", "A", 0.5, 0.5, true);
    ASSERT_NE(iconFit, nullptr);
    EXPECT_TRUE(iconFit->getFullyBounds());
}

TEST_F(AnnotIconFitTest_763, GetFullyBoundsFalse_763) {
    // Test that getFullyBounds returns false when FB is set to false
    auto iconFit = createAnnotIconFitFromDict("A", "A", 0.5, 0.5, false);
    ASSERT_NE(iconFit, nullptr);
    EXPECT_FALSE(iconFit->getFullyBounds());
}

TEST_F(AnnotIconFitTest_763, GetLeftReturnsCorrectValue_763) {
    auto iconFit = createAnnotIconFitFromDict("A", "A", 0.3, 0.7, false);
    ASSERT_NE(iconFit, nullptr);
    EXPECT_NEAR(iconFit->getLeft(), 0.3, 1e-6);
}

TEST_F(AnnotIconFitTest_763, GetBottomReturnsCorrectValue_763) {
    auto iconFit = createAnnotIconFitFromDict("A", "A", 0.3, 0.7, false);
    ASSERT_NE(iconFit, nullptr);
    EXPECT_NEAR(iconFit->getBottom(), 0.7, 1e-6);
}

TEST_F(AnnotIconFitTest_763, GetLeftZero_763) {
    auto iconFit = createAnnotIconFitFromDict("A", "A", 0.0, 0.0, false);
    ASSERT_NE(iconFit, nullptr);
    EXPECT_NEAR(iconFit->getLeft(), 0.0, 1e-6);
}

TEST_F(AnnotIconFitTest_763, GetBottomZero_763) {
    auto iconFit = createAnnotIconFitFromDict("A", "A", 0.0, 0.0, false);
    ASSERT_NE(iconFit, nullptr);
    EXPECT_NEAR(iconFit->getBottom(), 0.0, 1e-6);
}

TEST_F(AnnotIconFitTest_763, GetLeftOne_763) {
    auto iconFit = createAnnotIconFitFromDict("A", "A", 1.0, 1.0, true);
    ASSERT_NE(iconFit, nullptr);
    EXPECT_NEAR(iconFit->getLeft(), 1.0, 1e-6);
}

TEST_F(AnnotIconFitTest_763, GetBottomOne_763) {
    auto iconFit = createAnnotIconFitFromDict("A", "A", 1.0, 1.0, true);
    ASSERT_NE(iconFit, nullptr);
    EXPECT_NEAR(iconFit->getBottom(), 1.0, 1e-6);
}

TEST_F(AnnotIconFitTest_763, DefaultDictMinimalEntries_763) {
    // Create a dict with minimal/no optional entries to test defaults
    auto xref = (XRef *)nullptr;
    Dict *dict = new Dict(xref);
    
    auto iconFit = std::make_unique<AnnotIconFit>(dict);
    ASSERT_NE(iconFit, nullptr);
    
    // Default for fullyBounds should be false per PDF spec
    EXPECT_FALSE(iconFit->getFullyBounds());
}

TEST_F(AnnotIconFitTest_763, GetLeftAndBottomDefaults_763) {
    // When A array is not present, defaults should be [0.5, 0.5] per PDF spec
    auto xref = (XRef *)nullptr;
    Dict *dict = new Dict(xref);
    
    auto iconFit = std::make_unique<AnnotIconFit>(dict);
    ASSERT_NE(iconFit, nullptr);
    
    EXPECT_NEAR(iconFit->getLeft(), 0.5, 1e-6);
    EXPECT_NEAR(iconFit->getBottom(), 0.5, 1e-6);
}

TEST_F(AnnotIconFitTest_763, ConstGetFullyBounds_763) {
    // Test that getFullyBounds() works on const reference
    auto iconFit = createAnnotIconFitFromDict("A", "A", 0.5, 0.5, true);
    ASSERT_NE(iconFit, nullptr);
    
    const AnnotIconFit &constRef = *iconFit;
    EXPECT_TRUE(constRef.getFullyBounds());
}

TEST_F(AnnotIconFitTest_763, ConstGetLeft_763) {
    auto iconFit = createAnnotIconFitFromDict("A", "A", 0.25, 0.75, false);
    ASSERT_NE(iconFit, nullptr);
    
    const AnnotIconFit &constRef = *iconFit;
    EXPECT_NEAR(constRef.getLeft(), 0.25, 1e-6);
}

TEST_F(AnnotIconFitTest_763, ConstGetBottom_763) {
    auto iconFit = createAnnotIconFitFromDict("A", "A", 0.25, 0.75, false);
    ASSERT_NE(iconFit, nullptr);
    
    const AnnotIconFit &constRef = *iconFit;
    EXPECT_NEAR(constRef.getBottom(), 0.75, 1e-6);
}
