#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annotation-private.h"

#include "Page.h"

#include "DocumentData.h"



using namespace Poppler;

using ::testing::NiceMock;

using ::testing::Return;

using ::testing::_;



class MockPage : public Page {

public:

    MOCK_METHOD(std::shared_ptr<Annot>, getDoc, (), (const));

};



class MockDocumentData : public DocumentData {

public:

    MockDocumentData() : DocumentData("dummy", std::nullopt, std::nullopt) {}

};



class HighlightAnnotationPrivateTest : public ::testing::Test {

protected:

    NiceMock<MockPage> mockPage;

    MockDocumentData mockDocData;

    HighlightAnnotationPrivate highlightAnnotPriv;



    void SetUp() override {

        // Set up necessary preconditions for tests

    }

};



TEST_F(HighlightAnnotationPrivateTest_NormalOperation_1403, CreateNativeAnnot_ReturnsNonNullPointer_1403) {

    auto result = highlightAnnotPriv.createNativeAnnot(&mockPage, &mockDocData);

    EXPECT_NE(result, nullptr);

}



TEST_F(HighlightAnnotationPrivateTest_BoundaryConditions_1403, CreateNativeAnnot_WithNullPage_ReturnsNullPointer_1403) {

    auto result = highlightAnnotPriv.createNativeAnnot(nullptr, &mockDocData);

    EXPECT_EQ(result, nullptr);

}



TEST_F(HighlightAnnotationPrivateTest_BoundaryConditions_1403, CreateNativeAnnot_WithNullDocument_ReturnsNullPointer_1403) {

    auto result = highlightAnnotPriv.createNativeAnnot(&mockPage, nullptr);

    EXPECT_EQ(result, nullptr);

}



TEST_F(HighlightAnnotationPrivateTest_ExceptionalCases_1403, CreateNativeAnnot_WithInvalidPage_ReturnsNullPointer_1403) {

    Page* invalidPage = new Page(nullptr, 0, Object(), Ref(), std::make_unique<PageAttrs>());

    auto result = highlightAnnotPriv.createNativeAnnot(invalidPage, &mockDocData);

    delete invalidPage;

    EXPECT_EQ(result, nullptr);

}



TEST_F(HighlightAnnotationPrivateTest_ExceptionalCases_1403, CreateNativeAnnot_WithInvalidDocument_ReturnsNullPointer_1403) {

    DocumentData* invalidDoc = new DocumentData("dummy", std::nullopt, std::nullopt);

    auto result = highlightAnnotPriv.createNativeAnnot(&mockPage, invalidDoc);

    delete invalidDoc;

    EXPECT_EQ(result, nullptr);

}



TEST_F(HighlightAnnotationPrivateTest_VerifyExternalInteractions_1403, CreateNativeAnnot_CallsGetDocOnPage_1403) {

    EXPECT_CALL(mockPage, getDoc()).WillOnce(Return(std::make_shared<Annot>()));

    auto result = highlightAnnotPriv.createNativeAnnot(&mockPage, &mockDocData);

}
