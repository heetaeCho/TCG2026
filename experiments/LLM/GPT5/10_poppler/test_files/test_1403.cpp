#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler-annotation-private.h"  // Ensure this path matches the header for HighlightAnnotationPrivate
#include "poppler/Page.h"
#include "poppler/DocumentData.h"

namespace Poppler {

class MockPage : public ::Page {
public:
    MOCK_METHOD(Dict*, getResourceDict, (), (override));
    MOCK_METHOD(bool, addAnnot, (const std::shared_ptr<Annot>& annot), (override));
    MOCK_METHOD(bool, removeAnnot, (const std::shared_ptr<Annot>& annot), (override));
    MOCK_METHOD(bool, isOk, (), (const, override));
};

class MockDocumentData : public DocumentData {
public:
    MOCK_METHOD(void, init, (), (override));
    MOCK_METHOD(void, notifyXRefReconstructed, (), (override));
};

class HighlightAnnotationPrivateTest_1403 : public testing::Test {
protected:
    HighlightAnnotationPrivate highlightAnnotPrivate;
    std::shared_ptr<MockPage> mockPage;
    std::shared_ptr<MockDocumentData> mockDocData;

    void SetUp() override {
        mockPage = std::make_shared<MockPage>();
        mockDocData = std::make_shared<MockDocumentData>();
    }
};

// Normal Operation Test
TEST_F(HighlightAnnotationPrivateTest_1403, CreateNativeAnnot_1403) {
    // Setup the expectations
    PDFRectangle rect;
    EXPECT_CALL(*mockPage, getDoc()).WillOnce(testing::Return(nullptr));
    EXPECT_CALL(*mockPage, addAnnot(testing::_)).WillOnce(testing::Return(true));
    
    auto result = highlightAnnotPrivate.createNativeAnnot(mockPage.get(), mockDocData.get());
    
    // Assert the expected behavior
    ASSERT_TRUE(result != nullptr);
    ASSERT_EQ(result->getType(), Annot::eTextMarkup);  // Assuming Annot::eTextMarkup is the type for Highlight
}

// Boundary Condition Test - Ensure that empty or invalid inputs are handled
TEST_F(HighlightAnnotationPrivateTest_1403, CreateNativeAnnot_InvalidInputs_1403) {
    // Simulate an invalid Page
    EXPECT_CALL(*mockPage, getDoc()).WillOnce(testing::Return(nullptr));
    
    auto result = highlightAnnotPrivate.createNativeAnnot(nullptr, nullptr);
    
    // Assert that the result is nullptr or handles invalid inputs correctly
    ASSERT_EQ(result, nullptr);
}

// Exceptional Case Test - If the document or page is invalid, the function should fail
TEST_F(HighlightAnnotationPrivateTest_1403, CreateNativeAnnot_InvalidPage_1403) {
    EXPECT_CALL(*mockPage, getDoc()).WillOnce(testing::Return(nullptr));  // Simulate invalid doc
    
    auto result = highlightAnnotPrivate.createNativeAnnot(mockPage.get(), nullptr);  // No valid DocumentData
    
    ASSERT_EQ(result, nullptr);  // Expect failure when there is no valid DocumentData
}

// Verification of External Interactions
TEST_F(HighlightAnnotationPrivateTest_1403, CreateNativeAnnot_ExternalInteraction_1403) {
    // Mock some necessary behavior
    PDFRectangle rect;
    EXPECT_CALL(*mockPage, getDoc()).WillOnce(testing::Return(nullptr));  // Mock document
    EXPECT_CALL(*mockPage, addAnnot(testing::_)).WillOnce(testing::Return(true));  // Expect addAnnot to be called
    
    auto result = highlightAnnotPrivate.createNativeAnnot(mockPage.get(), mockDocData.get());
    
    // Verify external interaction (e.g., mock page annotation addition)
    ASSERT_TRUE(result != nullptr); 
}

}  // namespace Poppler