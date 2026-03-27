#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/qt5/src/poppler-annotation.h"  // Include necessary headers
#include "./TestProjects/poppler/qt5/src/poppler-annotation-private.h"
#include "./TestProjects/poppler/poppler/Page.h"
#include "./TestProjects/poppler/qt6/src/poppler-private.h"

namespace Poppler {

// Mocking dependencies
class MockPage : public Page {
public:
    MockPage(PDFDoc *doc, int numA, Object &&pageDict, Ref pageRefA)
        : Page(doc, numA, std::move(pageDict), pageRefA) {}
    MOCK_METHOD(Dict*, getResourceDict, (), (override));
    MOCK_METHOD(Object*, getResourceDictObject, (), (override));
    MOCK_METHOD(bool, addAnnot, (const std::shared_ptr<Annot> & annot), (override));
    MOCK_METHOD(void, removeAnnot, (const std::shared_ptr<Annot> & annot), (override));
};

// Test Fixture Class for StampAnnotationPrivate
class StampAnnotationPrivateTest_1404 : public ::testing::Test {
protected:
    // Test setup and teardown
    void SetUp() override {
        // Setup mock page and document data
        page = std::make_shared<MockPage>(nullptr, 1, Object{}, Ref{});
        documentData = std::make_shared<DocumentData>("dummy_path", {}, {});
    }

    // Mocked objects
    std::shared_ptr<MockPage> page;
    std::shared_ptr<DocumentData> documentData;
};

TEST_F(StampAnnotationPrivateTest_1404, CreateNativeAnnot_ValidArguments_1404) {
    // Arrange: Set up the expected behavior for the createNativeAnnot function
    StampAnnotationPrivate stampAnnotPrivate;

    // Mock expected behavior for the Page
    EXPECT_CALL(*page, addAnnot(testing::_)).Times(1).WillOnce(testing::Return(true));

    // Act: Create the native annotation
    auto annot = stampAnnotPrivate.createNativeAnnot(page.get(), documentData.get());

    // Assert: Verify the expected behavior (check return type, interactions, etc.)
    EXPECT_NE(annot, nullptr);  // Ensure that the annotation was created
}

TEST_F(StampAnnotationPrivateTest_1404, CreateNativeAnnot_PageNull_1404) {
    // Arrange: Create a StampAnnotationPrivate instance
    StampAnnotationPrivate stampAnnotPrivate;

    // Act: Call with a null page
    auto annot = stampAnnotPrivate.createNativeAnnot(nullptr, documentData.get());

    // Assert: Ensure the result is null as the page is null
    EXPECT_EQ(annot, nullptr);
}

TEST_F(StampAnnotationPrivateTest_1404, CreateNativeAnnot_DocumentDataNull_1404) {
    // Arrange: Create a StampAnnotationPrivate instance
    StampAnnotationPrivate stampAnnotPrivate;

    // Act: Call with null DocumentData
    auto annot = stampAnnotPrivate.createNativeAnnot(page.get(), nullptr);

    // Assert: Ensure that the annotation creation fails with null DocumentData
    EXPECT_EQ(annot, nullptr);
}

TEST_F(StampAnnotationPrivateTest_1404, CreateNativeAnnot_InvalidInteraction_1404) {
    // Arrange: Create a StampAnnotationPrivate instance
    StampAnnotationPrivate stampAnnotPrivate;

    // Mock expected behavior for invalid interaction
    EXPECT_CALL(*page, addAnnot(testing::_)).Times(1).WillOnce(testing::Return(false));

    // Act: Attempt to create a native annotation
    auto annot = stampAnnotPrivate.createNativeAnnot(page.get(), documentData.get());

    // Assert: Ensure that the creation fails if addAnnot fails
    EXPECT_EQ(annot, nullptr);
}

}  // namespace Poppler