#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/qt5/src/poppler-annotation-private.h"
#include "./TestProjects/poppler/poppler/Page.h"
#include "./TestProjects/poppler/poppler/Error.h"

namespace Poppler {

// Mock class for the Page dependency
class MockPage : public Page {
public:
    MOCK_METHOD(void, removeAnnot, (const std::shared_ptr<Annot>& annot), ());
};

// Test fixture for AnnotationPrivate
class AnnotationPrivateTest : public ::testing::Test {
protected:
    AnnotationPrivate annotationPrivate;
    MockPage mockPage;
    std::shared_ptr<Annot> annot;

    void SetUp() override {
        annot = std::make_shared<Annot>();
    }
};

// Test normal operation for removeAnnotationFromPage
TEST_F(AnnotationPrivateTest, RemoveAnnotationFromPage_Success_1393) {
    // Arrange
    annotationPrivate.pdfAnnot = annot;
    annotationPrivate.pdfPage = &mockPage;

    // Expectation: removeAnnot will be called on the mock Page
    EXPECT_CALL(mockPage, removeAnnot(annot)).Times(1);

    // Act
    annotationPrivate.removeAnnotationFromPage(&mockPage, annot.get());

    // Verify no additional expectations
}

// Test error case when annotation is not tied
TEST_F(AnnotationPrivateTest, RemoveAnnotationFromPage_AnnotationNotTied_1394) {
    // Arrange
    annotationPrivate.pdfAnnot = nullptr;
    annotationPrivate.pdfPage = &mockPage;

    // Act & Assert
    // This should trigger an error with errIO category
    EXPECT_CALL(*this, error(errIO, -1, "Annotation is not tied")).Times(1);
    annotationPrivate.removeAnnotationFromPage(&mockPage, annot.get());
}

// Test error case when annotation does not belong to the specified page
TEST_F(AnnotationPrivateTest, RemoveAnnotationFromPage_AnnotationDoesNotBelongToPage_1395) {
    // Arrange
    annotationPrivate.pdfAnnot = annot;
    annotationPrivate.pdfPage = nullptr; // Different page

    // Act & Assert
    // This should trigger an error with errIO category
    EXPECT_CALL(*this, error(errIO, -1, "Annotation doesn't belong to the specified page")).Times(1);
    annotationPrivate.removeAnnotationFromPage(&mockPage, annot.get());
}

// Test removeAnnotationFromPage with valid annotation but fails to delete
TEST_F(AnnotationPrivateTest, RemoveAnnotationFromPage_FailureToDeleteAnnotation_1396) {
    // Arrange
    annotationPrivate.pdfAnnot = annot;
    annotationPrivate.pdfPage = &mockPage;

    // Expectation: mock removeAnnot will be called
    EXPECT_CALL(mockPage, removeAnnot(annot)).Times(1);
    // Fail deletion after calling removeAnnot
    EXPECT_CALL(*this, delete(annot)).Times(0);

    // Act
    annotationPrivate.removeAnnotationFromPage(&mockPage, annot.get());
}

}  // namespace Poppler