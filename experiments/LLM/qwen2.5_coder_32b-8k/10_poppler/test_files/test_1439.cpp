#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-page-private.h"

#include "Link.h"



using namespace Poppler;

using ::testing::_;

using ::testing::MockFunction;



class MockDocumentData : public DocumentData {

public:

    MOCK_METHOD0(getSomeProperty, int());

};



class PageDataTest_1439 : public ::testing::Test {

protected:

    void SetUp() override {

        documentData = std::make_unique<MockDocumentData>();

        pageData = new PageData();

        pageData->parentDoc = documentData.get();



        mockLinkAction = new LinkAction();

        mockLinkAction->nextActionList = {}; // Ensure it's empty for simplicity

    }



    void TearDown() override {

        delete pageData;

        delete mockLinkAction;

    }



    std::unique_ptr<MockDocumentData> documentData;

    PageData* pageData;

    LinkAction* mockLinkAction;

};



TEST_F(PageDataTest_1439, ConvertLinkActionToLink_NormalOperation_1439) {

    QRectF linkArea(0, 0, 100, 100);

    const Link* result = pageData->convertLinkActionToLink(mockLinkAction, linkArea);



    // Assuming that a valid LinkAction results in a non-null Link

    ASSERT_NE(result, nullptr);

}



TEST_F(PageDataTest_1439, ConvertLinkActionToLink_BoundaryConditions_EmptyNextActions_1439) {

    QRectF linkArea(0, 0, 100, 100);

    const Link* result = pageData->convertLinkActionToLink(mockLinkAction, linkArea);



    // Assuming that even with no next actions, a valid LinkAction still results in a non-null Link

    ASSERT_NE(result, nullptr);

}



TEST_F(PageDataTest_1439, ConvertLinkActionToLink_Exceptional_IsOkFalse_1439) {

    EXPECT_CALL(*mockLinkAction, isOk()).WillOnce(::testing::Return(false));

    QRectF linkArea(0, 0, 100, 100);

    const Link* result = pageData->convertLinkActionToLink(mockLinkAction, linkArea);



    // Assuming that if isOk() returns false, the resulting Link should be null

    ASSERT_EQ(result, nullptr);

}



TEST_F(PageDataTest_1439, ConvertLinkActionToLink_Exceptional_NullLinkAction_1439) {

    QRectF linkArea(0, 0, 100, 100);

    const Link* result = pageData->convertLinkActionToLink(nullptr, linkArea);



    // If the LinkAction is null, the resulting Link should be null

    ASSERT_EQ(result, nullptr);

}
