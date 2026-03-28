#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

// Include necessary headers
#include "poppler-annotation-private.h"
#include "poppler-private.h"
#include "Page.h"
#include "Annot.h"
#include "Error.h"

// We need to test AnnotationPrivate::tieToNativeAnnot
// Since we can't easily construct real Page, DocumentData, and Annot objects
// in isolation, we'll test what we can observe through the public interface.

// For testing purposes, we may need minimal stubs or use the actual classes
// if the build system provides them.

namespace {

class AnnotationPrivateTest_1382 : public ::testing::Test {
protected:
    void SetUp() override {
        annotPrivate = std::make_unique<Poppler::AnnotationPrivate>();
    }

    void TearDown() override {
        annotPrivate.reset();
    }

    std::unique_ptr<Poppler::AnnotationPrivate> annotPrivate;
};

// Test that initially pdfAnnot is null, pdfPage is nullptr, and parentDoc is nullptr
TEST_F(AnnotationPrivateTest_1382, InitialState_1382) {
    EXPECT_EQ(annotPrivate->pdfAnnot, nullptr);
    EXPECT_EQ(annotPrivate->pdfPage, nullptr);
    EXPECT_EQ(annotPrivate->parentDoc, nullptr);
}

// Test that tieToNativeAnnot sets all three members when called on a fresh object
TEST_F(AnnotationPrivateTest_1382, TieToNativeAnnotSetsMembers_1382) {
    // Create a shared_ptr<Annot> - we use a nullptr-initialized shared_ptr with a non-null value
    // Since we can't easily construct a real Annot, we'll use a mock or a minimal approach.
    // For the purpose of this test, we'll create a shared_ptr that wraps a non-null pointer
    // using a custom deleter that does nothing (to avoid real deallocation issues).
    
    // We need some non-null pointers for testing
    // Using reinterpret_cast to create fake pointers for testing - these won't be dereferenced
    ::Page *fakePage = reinterpret_cast<::Page *>(0x1234);
    Poppler::DocumentData *fakeDoc = reinterpret_cast<Poppler::DocumentData *>(0x5678);
    
    // Create a shared_ptr<Annot> with a no-op deleter to avoid actual deallocation
    Annot *fakeAnnotRaw = reinterpret_cast<Annot *>(0x9ABC);
    std::shared_ptr<Annot> fakeAnnot(fakeAnnotRaw, [](Annot *) { /* no-op deleter */ });

    annotPrivate->tieToNativeAnnot(fakeAnnot, fakePage, fakeDoc);

    EXPECT_NE(annotPrivate->pdfAnnot, nullptr);
    EXPECT_EQ(annotPrivate->pdfAnnot.get(), fakeAnnotRaw);
    EXPECT_EQ(annotPrivate->pdfPage, fakePage);
    EXPECT_EQ(annotPrivate->parentDoc, fakeDoc);
}

// Test that calling tieToNativeAnnot twice does not overwrite the first binding
// (the second call should be a no-op with an error message)
TEST_F(AnnotationPrivateTest_1382, TieToNativeAnnotCalledTwiceDoesNotOverwrite_1382) {
    ::Page *fakePage1 = reinterpret_cast<::Page *>(0x1111);
    Poppler::DocumentData *fakeDoc1 = reinterpret_cast<Poppler::DocumentData *>(0x2222);
    Annot *fakeAnnotRaw1 = reinterpret_cast<Annot *>(0x3333);
    std::shared_ptr<Annot> fakeAnnot1(fakeAnnotRaw1, [](Annot *) {});

    ::Page *fakePage2 = reinterpret_cast<::Page *>(0x4444);
    Poppler::DocumentData *fakeDoc2 = reinterpret_cast<Poppler::DocumentData *>(0x5555);
    Annot *fakeAnnotRaw2 = reinterpret_cast<Annot *>(0x6666);
    std::shared_ptr<Annot> fakeAnnot2(fakeAnnotRaw2, [](Annot *) {});

    // First call should succeed
    annotPrivate->tieToNativeAnnot(fakeAnnot1, fakePage1, fakeDoc1);
    EXPECT_EQ(annotPrivate->pdfAnnot.get(), fakeAnnotRaw1);
    EXPECT_EQ(annotPrivate->pdfPage, fakePage1);
    EXPECT_EQ(annotPrivate->parentDoc, fakeDoc1);

    // Second call should not overwrite - annotation is already tied
    annotPrivate->tieToNativeAnnot(fakeAnnot2, fakePage2, fakeDoc2);
    
    // Original values should remain unchanged
    EXPECT_EQ(annotPrivate->pdfAnnot.get(), fakeAnnotRaw1);
    EXPECT_EQ(annotPrivate->pdfPage, fakePage1);
    EXPECT_EQ(annotPrivate->parentDoc, fakeDoc1);
}

// Test tieToNativeAnnot with null Annot shared_ptr
// When pdfAnnot is null (default), tieToNativeAnnot should proceed.
// But if we pass an empty shared_ptr, the guard condition checks pdfAnnot (which is null),
// so it should proceed and set the members (even though ann itself might be null).
TEST_F(AnnotationPrivateTest_1382, TieToNativeAnnotWithNullAnnotPtr_1382) {
    ::Page *fakePage = reinterpret_cast<::Page *>(0xAAAA);
    Poppler::DocumentData *fakeDoc = reinterpret_cast<Poppler::DocumentData *>(0xBBBB);
    std::shared_ptr<Annot> nullAnnot; // empty/null shared_ptr

    annotPrivate->tieToNativeAnnot(nullAnnot, fakePage, fakeDoc);

    // pdfAnnot should be set (even if null), pdfPage and parentDoc should be updated
    EXPECT_EQ(annotPrivate->pdfAnnot, nullptr);
    EXPECT_EQ(annotPrivate->pdfPage, fakePage);
    EXPECT_EQ(annotPrivate->parentDoc, fakeDoc);
}

// Test tieToNativeAnnot with null page and null doc
TEST_F(AnnotationPrivateTest_1382, TieToNativeAnnotWithNullPageAndDoc_1382) {
    Annot *fakeAnnotRaw = reinterpret_cast<Annot *>(0xCCCC);
    std::shared_ptr<Annot> fakeAnnot(fakeAnnotRaw, [](Annot *) {});

    annotPrivate->tieToNativeAnnot(fakeAnnot, nullptr, nullptr);

    EXPECT_EQ(annotPrivate->pdfAnnot.get(), fakeAnnotRaw);
    EXPECT_EQ(annotPrivate->pdfPage, nullptr);
    EXPECT_EQ(annotPrivate->parentDoc, nullptr);
}

// Test that after tying with a null shared_ptr, a second call with a non-null shared_ptr
// still does NOT overwrite because the condition checks if pdfAnnot is non-null.
// However, since the first call passed a null shared_ptr, pdfAnnot remains null (evaluates to false),
// so the second call should succeed.
TEST_F(AnnotationPrivateTest_1382, TieAfterNullAnnotAllowsRetie_1382) {
    ::Page *fakePage1 = reinterpret_cast<::Page *>(0x1000);
    Poppler::DocumentData *fakeDoc1 = reinterpret_cast<Poppler::DocumentData *>(0x2000);
    std::shared_ptr<Annot> nullAnnot; // null

    annotPrivate->tieToNativeAnnot(nullAnnot, fakePage1, fakeDoc1);
    EXPECT_EQ(annotPrivate->pdfAnnot, nullptr);

    // Now tie with a real (non-null) annot - this should work since pdfAnnot is still null
    ::Page *fakePage2 = reinterpret_cast<::Page *>(0x3000);
    Poppler::DocumentData *fakeDoc2 = reinterpret_cast<Poppler::DocumentData *>(0x4000);
    Annot *fakeAnnotRaw2 = reinterpret_cast<Annot *>(0x5000);
    std::shared_ptr<Annot> fakeAnnot2(fakeAnnotRaw2, [](Annot *) {});

    annotPrivate->tieToNativeAnnot(fakeAnnot2, fakePage2, fakeDoc2);
    EXPECT_EQ(annotPrivate->pdfAnnot.get(), fakeAnnotRaw2);
    EXPECT_EQ(annotPrivate->pdfPage, fakePage2);
    EXPECT_EQ(annotPrivate->parentDoc, fakeDoc2);
}

// Test that shared_ptr ownership is properly moved
TEST_F(AnnotationPrivateTest_1382, TieToNativeAnnotMovesSharedPtr_1382) {
    Annot *fakeAnnotRaw = reinterpret_cast<Annot *>(0xDDDD);
    std::shared_ptr<Annot> fakeAnnot(fakeAnnotRaw, [](Annot *) {});
    
    // Store the use count before tying
    long useCountBefore = fakeAnnot.use_count();
    EXPECT_EQ(useCountBefore, 1);

    ::Page *fakePage = reinterpret_cast<::Page *>(0xEEEE);
    Poppler::DocumentData *fakeDoc = reinterpret_cast<Poppler::DocumentData *>(0xFFFF);

    // tieToNativeAnnot uses std::move, so fakeAnnot should become empty after the call
    annotPrivate->tieToNativeAnnot(std::move(fakeAnnot), fakePage, fakeDoc);

    // After move, the original shared_ptr should be null
    EXPECT_EQ(fakeAnnot, nullptr); // NOLINT - intentionally checking moved-from object
    EXPECT_EQ(annotPrivate->pdfAnnot.get(), fakeAnnotRaw);
    EXPECT_EQ(annotPrivate->pdfAnnot.use_count(), 1);
}

} // namespace
