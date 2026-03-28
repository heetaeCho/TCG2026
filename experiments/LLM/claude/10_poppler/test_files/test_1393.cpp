#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

// Include necessary headers
#include "poppler-annotation.h"
#include "poppler-annotation-private.h"
#include "poppler-private.h"
#include "Page.h"
#include "Annot.h"

using namespace Poppler;

class AnnotationPrivateTest_1393 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: removeAnnotationFromPage when annotation has null pdfAnnot (not tied)
// Expected: error is logged, annotation is NOT deleted (no crash), function returns early
TEST_F(AnnotationPrivateTest_1393, RemoveAnnotation_NullPdfAnnot_ReturnsEarly_1393)
{
    // Create an annotation that is not tied to any native annotation (pdfAnnot == nullptr)
    Annotation *ann = new TextAnnotation(TextAnnotation::Linked);
    // Ensure pdfAnnot is nullptr (default state for newly created annotation)
    ASSERT_EQ(ann->d_ptr->pdfAnnot, nullptr);

    // Calling removeAnnotationFromPage with a null pdfAnnot should log error and return
    // without crashing. The annotation should NOT be deleted in this path.
    // We pass nullptr for pdfPage since it shouldn't be accessed in this path
    // But the actual code accesses ann->d_ptr->pdfAnnot first, so this should be safe
    // Actually we need a valid pointer pattern. Let's just verify no crash.
    // The function checks pdfAnnot == nullptr first, so pdfPage is not accessed for removeAnnot.
    
    // Since the annotation is not deleted in the error path, we need to clean up
    AnnotationPrivate::removeAnnotationFromPage(nullptr, ann);
    
    // If we reach here, the function returned early without crashing
    // The annotation was not deleted (error path), so we must delete it ourselves
    delete ann;
}

// Test: removeAnnotationFromPage when annotation's pdfPage doesn't match specified page
// Expected: error is logged, function returns early, annotation is NOT deleted
TEST_F(AnnotationPrivateTest_1393, RemoveAnnotation_PageMismatch_ReturnsEarly_1393)
{
    // Create an annotation and give it a non-null pdfAnnot but mismatched page
    Annotation *ann = new TextAnnotation(TextAnnotation::Linked);
    
    // We need pdfAnnot to be non-null to pass the first check
    // and pdfPage to differ from the passed page to trigger the second error
    auto fakeAnnot = std::make_shared<Annot>(nullptr, 0, 0, nullptr);
    ann->d_ptr->pdfAnnot = fakeAnnot;
    ann->d_ptr->pdfPage = reinterpret_cast<::Page*>(0xDEAD); // Some non-null fake page pointer

    // Pass a different page pointer to trigger the mismatch
    ::Page *differentPage = reinterpret_cast<::Page*>(0xBEEF);

    // This should hit the "doesn't belong to the specified page" error and return early
    AnnotationPrivate::removeAnnotationFromPage(differentPage, ann);

    // Annotation should NOT have been deleted (error path), clean up manually
    ann->d_ptr->pdfAnnot = nullptr; // Prevent issues on cleanup
    ann->d_ptr->pdfPage = nullptr;
    delete ann;
}

// Test: Verify the static method exists and is callable
TEST_F(AnnotationPrivateTest_1393, RemoveAnnotationFromPage_StaticMethodExists_1393)
{
    // Verify that removeAnnotationFromPage is a valid static method
    // by taking its address
    auto funcPtr = &AnnotationPrivate::removeAnnotationFromPage;
    ASSERT_NE(funcPtr, nullptr);
}
