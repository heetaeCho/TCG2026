#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <optional>
#include "poppler-annotation-private.h"
#include "poppler-annotation.h"
#include "poppler-documentdata.h"
#include "poppler-page.h"
#include "poppler-error.h"

namespace Poppler {

class AnnotationPrivateTest_1382 : public ::testing::Test {
protected:
    AnnotationPrivate annotationPrivate;
    std::shared_ptr<Annot> annot;
    std::shared_ptr<Page> page;
    std::shared_ptr<DocumentData> documentData;

    void SetUp() override {
        // Initialize the shared pointers
        annot = std::make_shared<Annot>();
        page = std::make_shared<Page>(nullptr, 1, {}, {}, {});
        documentData = std::make_shared<DocumentData>("test.pdf", {}, {});
    }
};

// Test normal operation: successfully tying an annotation to a page and document
TEST_F(AnnotationPrivateTest_1382, TieToNativeAnnot_Success_1382) {
    // Call tieToNativeAnnot
    annotationPrivate.tieToNativeAnnot(annot, page.get(), documentData.get());

    // Verify that the annotation was tied correctly
    ASSERT_EQ(annotationPrivate.pdfAnnot, annot);
    ASSERT_EQ(annotationPrivate.pdfPage, page.get());
    ASSERT_EQ(annotationPrivate.parentDoc, documentData.get());
}

// Test exceptional case: trying to tie an annotation when it's already tied
TEST_F(AnnotationPrivateTest_1382, TieToNativeAnnot_AlreadyTied_1382) {
    annotationPrivate.tieToNativeAnnot(annot, page.get(), documentData.get());

    // Trying to tie again should produce an error
    // We mock the error function to capture the error
    ::testing::MockFunction<void(ErrorCategory, int, const std::string&)> mockError;
    EXPECT_CALL(mockError, Call(errIO, -1, "Annotation is already tied"));

    // Reattempt tying
    annotationPrivate.tieToNativeAnnot(annot, page.get(), documentData.get());
}

// Test boundary condition: passing null page and document data
TEST_F(AnnotationPrivateTest_1382, TieToNativeAnnot_NullPageAndDoc_1382) {
    // Try tying annotation to a null page and document data
    annotationPrivate.tieToNativeAnnot(annot, nullptr, nullptr);

    // Assert that the annotation is tied but with null values for page and document data
    ASSERT_EQ(annotationPrivate.pdfAnnot, annot);
    ASSERT_EQ(annotationPrivate.pdfPage, nullptr);
    ASSERT_EQ(annotationPrivate.parentDoc, nullptr);
}

// Test the behavior of the constructor
TEST_F(AnnotationPrivateTest_1382, Constructor_1382) {
    AnnotationPrivate newAnnotationPrivate;
    ASSERT_EQ(newAnnotationPrivate.pdfAnnot, nullptr);
    ASSERT_EQ(newAnnotationPrivate.pdfPage, nullptr);
    ASSERT_EQ(newAnnotationPrivate.parentDoc, nullptr);
}

// Test the behavior of addRevision (this requires a mock annotation for testing)
TEST_F(AnnotationPrivateTest_1382, AddRevision_1382) {
    // Create a mock annotation
    MockAnnotation mockAnnotation;

    // Call addRevision on the AnnotationPrivate instance
    annotationPrivate.addRevision(&mockAnnotation, Annotation::RevScope::Scope1, Annotation::RevType::Type1);

    // Verify that the addRevision function works as expected (mock verification would go here)
}

// Test boundary case for empty annotation and document data
TEST_F(AnnotationPrivateTest_1382, TieToNativeAnnot_EmptyData_1382) {
    std::shared_ptr<Annot> emptyAnnot = nullptr;
    annotationPrivate.tieToNativeAnnot(emptyAnnot, nullptr, nullptr);

    // Validate that the tie operation does not set any internal values
    ASSERT_EQ(annotationPrivate.pdfAnnot, nullptr);
    ASSERT_EQ(annotationPrivate.pdfPage, nullptr);
    ASSERT_EQ(annotationPrivate.parentDoc, nullptr);
}

}  // namespace Poppler