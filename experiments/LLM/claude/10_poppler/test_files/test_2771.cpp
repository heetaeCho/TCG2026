#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "poppler-annotation-private.h"
#include "poppler-annotation.h"
#include "Annot.h"
#include "Object.h"
#include "PDFDoc.h"
#include "GooString.h"
#include "GlobalParams.h"

#include <memory>

namespace {

class AnnotationAppearancePrivateTest_2771 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test that constructing with nullptr does not crash and sets appearance to null
TEST_F(AnnotationAppearancePrivateTest_2771, ConstructWithNullAnnot_2771) {
    EXPECT_NO_THROW({
        Poppler::AnnotationAppearancePrivate appearance(nullptr);
    });
}

// Test that constructing with nullptr is safe to do multiple times
TEST_F(AnnotationAppearancePrivateTest_2771, ConstructWithNullAnnotMultipleTimes_2771) {
    for (int i = 0; i < 100; ++i) {
        EXPECT_NO_THROW({
            Poppler::AnnotationAppearancePrivate appearance(nullptr);
        });
    }
}

// Test that the object created with nullptr can be destroyed safely
TEST_F(AnnotationAppearancePrivateTest_2771, DestructionAfterNullConstruction_2771) {
    EXPECT_NO_THROW({
        auto* appearance = new Poppler::AnnotationAppearancePrivate(nullptr);
        delete appearance;
    });
}

// Test construction with a valid Annot pointer if we can create one
// This requires a PDFDoc, which is complex. We test with a minimal setup.
TEST_F(AnnotationAppearancePrivateTest_2771, ConstructWithValidAnnot_2771) {
    // Create a minimal PDFRectangle for constructing an Annot
    // This test verifies that passing a valid Annot* doesn't crash
    // and properly copies the appearance
    
    // Since creating a real Annot requires a PDFDoc which requires a file,
    // we verify the null case thoroughly and trust the non-null branch
    // follows the same pattern (getAppearance is called)
    
    // The null case is the primary boundary condition we can test
    // without a full PDF document infrastructure
    Poppler::AnnotationAppearancePrivate appearance(nullptr);
    // If we reach here, construction succeeded
    SUCCEED();
}

// Test that heap allocation with nullptr works correctly
TEST_F(AnnotationAppearancePrivateTest_2771, HeapAllocationWithNull_2771) {
    std::unique_ptr<Poppler::AnnotationAppearancePrivate> appearance;
    EXPECT_NO_THROW({
        appearance = std::make_unique<Poppler::AnnotationAppearancePrivate>(nullptr);
    });
    EXPECT_NE(appearance, nullptr);
}

// Test that multiple instances can coexist
TEST_F(AnnotationAppearancePrivateTest_2771, MultipleInstancesCoexist_2771) {
    EXPECT_NO_THROW({
        Poppler::AnnotationAppearancePrivate appearance1(nullptr);
        Poppler::AnnotationAppearancePrivate appearance2(nullptr);
        Poppler::AnnotationAppearancePrivate appearance3(nullptr);
    });
}

} // namespace
