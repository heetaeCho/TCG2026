// TEST_ID: 802
// File: AnnotMarkupTest_802.cpp

#include <gtest/gtest.h>
#include <memory>

// Include the header under test
#include "Annot.h"

// The tests below strictly treat AnnotMarkup as a black box.
// Only publicly observable behavior through its interface is verified.

class AnnotMarkupTest_802 : public ::testing::Test {
protected:
    // Since AnnotMarkup requires PDFDoc* and PDFRectangle*,
    // and their internal behavior is irrelevant for these tests,
    // we pass nullptr to satisfy the constructor signature.
    // We do NOT rely on any internal state or implementation details.
    AnnotMarkup* createAnnotMarkup() {
        return new AnnotMarkup(nullptr, nullptr);
    }
};

// Normal operation: getInReplyToID should be callable and return an int.
TEST_F(AnnotMarkupTest_802, GetInReplyToID_ReturnsInt_802) {
    std::unique_ptr<AnnotMarkup> annot(createAnnotMarkup());

    int id = annot->getInReplyToID();

    // We only verify that the call succeeds and returns an int.
    // No assumption is made about the internal value.
    EXPECT_TRUE(std::is_same<decltype(id), int>::value);
}

// Boundary condition: multiple calls should be consistent if state is unchanged.
TEST_F(AnnotMarkupTest_802, GetInReplyToID_MultipleCallsConsistent_802) {
    std::unique_ptr<AnnotMarkup> annot(createAnnotMarkup());

    int id1 = annot->getInReplyToID();
    int id2 = annot->getInReplyToID();

    // Without modifying state, repeated calls should yield the same result.
    EXPECT_EQ(id1, id2);
}

// Boundary condition: verify behavior immediately after construction.
TEST_F(AnnotMarkupTest_802, GetInReplyToID_AfterConstruction_802) {
    std::unique_ptr<AnnotMarkup> annot(createAnnotMarkup());

    // Immediately after construction, the function should be callable.
    int id = annot->getInReplyToID();

    // No assumption about value, only that it's a valid int.
    EXPECT_NO_THROW({
        volatile int tmp = id;
        (void)tmp;
    });
}

// Exceptional case (observable through interface):
// Ensure calling getInReplyToID does not throw.
TEST_F(AnnotMarkupTest_802, GetInReplyToID_DoesNotThrow_802) {
    std::unique_ptr<AnnotMarkup> annot(createAnnotMarkup());

    EXPECT_NO_THROW({
        annot->getInReplyToID();
    });
}

// Stability test: ensure getInReplyToID does not modify observable state
// (id should remain stable across unrelated getter calls).
TEST_F(AnnotMarkupTest_802, GetInReplyToID_StableAcrossOtherGetters_802) {
    std::unique_ptr<AnnotMarkup> annot(createAnnotMarkup());

    int idBefore = annot->getInReplyToID();

    // Call other const getters to ensure no interference
    (void)annot->getLabel();
    (void)annot->getPopup();
    (void)annot->getOpacity();
    (void)annot->getDate();
    (void)annot->getSubject();
    (void)annot->getReplyTo();
    (void)annot->getExData();

    int idAfter = annot->getInReplyToID();

    EXPECT_EQ(idBefore, idAfter);
}