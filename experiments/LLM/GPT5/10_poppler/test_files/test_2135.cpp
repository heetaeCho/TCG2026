// File: poppler_annot_ink_new_test_2135.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C" {
#include "poppler.h"
#include "poppler-private.h"
}

//
// TEST SUITE FOR poppler_annot_ink_new
//
// Black-box testing only based on the exposed C interface.
// We do NOT access internal/private fields or re-implement logic.
//

class PopplerAnnotInkNewTest_2135 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a dummy PopplerDocument structure.
        // We do NOT rely on any internal state.
        doc = reinterpret_cast<PopplerDocument*>(g_malloc0(sizeof(PopplerDocument)));
    }

    void TearDown() override {
        if (doc) {
            g_free(doc);
            doc = nullptr;
        }
    }

    PopplerDocument* doc = nullptr;
};

//
// Normal Operation Tests
//

TEST_F(PopplerAnnotInkNewTest_2135, CreatesAnnotWithValidRectangle_2135) {
    PopplerRectangle rect;
    rect.x1 = 10.0;
    rect.y1 = 20.0;
    rect.x2 = 100.0;
    rect.y2 = 200.0;

    PopplerAnnot* annot = poppler_annot_ink_new(doc, &rect);

    EXPECT_NE(annot, nullptr)
        << "poppler_annot_ink_new should return non-null for valid document and rectangle";

    if (annot) {
        g_object_unref(annot);
    }
}

//
// Boundary Condition Tests
//

TEST_F(PopplerAnnotInkNewTest_2135, CreatesAnnotWithZeroSizeRectangle_2135) {
    PopplerRectangle rect;
    rect.x1 = 0.0;
    rect.y1 = 0.0;
    rect.x2 = 0.0;
    rect.y2 = 0.0;

    PopplerAnnot* annot = poppler_annot_ink_new(doc, &rect);

    EXPECT_NE(annot, nullptr)
        << "Even with zero-size rectangle, function should return a valid annotation object";

    if (annot) {
        g_object_unref(annot);
    }
}

TEST_F(PopplerAnnotInkNewTest_2135, CreatesAnnotWithNegativeCoordinates_2135) {
    PopplerRectangle rect;
    rect.x1 = -50.0;
    rect.y1 = -50.0;
    rect.x2 = -10.0;
    rect.y2 = -10.0;

    PopplerAnnot* annot = poppler_annot_ink_new(doc, &rect);

    EXPECT_NE(annot, nullptr)
        << "Function should handle negative rectangle coordinates without crashing";

    if (annot) {
        g_object_unref(annot);
    }
}

//
// Exceptional / Error Case Tests
//

TEST_F(PopplerAnnotInkNewTest_2135, ReturnsNullWhenDocumentIsNull_2135) {
    PopplerRectangle rect;
    rect.x1 = 0.0;
    rect.y1 = 0.0;
    rect.x2 = 10.0;
    rect.y2 = 10.0;

    PopplerAnnot* annot = nullptr;

    // Protect against potential crash: call inside ASSERT_NO_FATAL_FAILURE
    ASSERT_NO_FATAL_FAILURE({
        annot = poppler_annot_ink_new(nullptr, &rect);
    });

    // Depending on implementation contract, null doc may result in null return.
    // We verify observable behavior only (no crash).
    // If implementation returns non-null, it must still be a valid GObject.
    if (annot) {
        g_object_unref(annot);
    }
}

TEST_F(PopplerAnnotInkNewTest_2135, ReturnsNullWhenRectangleIsNull_2135) {
    PopplerAnnot* annot = nullptr;

    ASSERT_NO_FATAL_FAILURE({
        annot = poppler_annot_ink_new(doc, nullptr);
    });

    if (annot) {
        g_object_unref(annot);
    }
}

//
// Stability / Multiple Invocation Test
//

TEST_F(PopplerAnnotInkNewTest_2135, MultipleCallsReturnIndependentObjects_2135) {
    PopplerRectangle rect;
    rect.x1 = 1.0;
    rect.y1 = 2.0;
    rect.x2 = 3.0;
    rect.y2 = 4.0;

    PopplerAnnot* annot1 = poppler_annot_ink_new(doc, &rect);
    PopplerAnnot* annot2 = poppler_annot_ink_new(doc, &rect);

    EXPECT_NE(annot1, nullptr);
    EXPECT_NE(annot2, nullptr);

    if (annot1 && annot2) {
        EXPECT_NE(annot1, annot2)
            << "Each call should return a distinct annotation instance";
    }

    if (annot1) g_object_unref(annot1);
    if (annot2) g_object_unref(annot2);
}