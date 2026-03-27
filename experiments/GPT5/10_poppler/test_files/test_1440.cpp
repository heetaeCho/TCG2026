#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler-page.h"
#include "poppler-link.h"
#include "poppler-private.h"

// Mock DocumentData class to simulate the parentDoc behavior
class MockDocumentData : public Poppler::DocumentData {
public:
    MOCK_METHOD(void, init, (), (override));
    MOCK_METHOD(int, checkDocument, (DocumentData* doc), (override));
};

// Mock LinkAction class to simulate actions
class MockLinkAction : public LinkAction {
public:
    MOCK_METHOD(LinkActionKind, getKind, (), (const, override));
    MOCK_METHOD(const std::vector<std::unique_ptr<LinkAction>>& , nextActions, (), (const, override));
};

class PageDataTest_1440 : public ::testing::Test {
protected:
    // Create a mock of DocumentData and a PageData instance
    MockDocumentData* mockDocData;
    Poppler::PageData* pageData;
    QRectF linkArea;

    void SetUp() override {
        mockDocData = new MockDocumentData();
        pageData = new Poppler::PageData();
        linkArea = QRectF(0, 0, 100, 100);  // Arbitrary link area
    }

    void TearDown() override {
        delete mockDocData;
        delete pageData;
    }
};

// Test normal operation for actionGoTo
TEST_F(PageDataTest_1440, ConvertLinkActionToLink_GoToAction_1440) {
    MockLinkAction* mockAction = new MockLinkAction();
    EXPECT_CALL(*mockAction, getKind()).WillOnce(testing::Return(actionGoTo));

    Link* link = pageData->convertLinkActionToLink(mockAction, mockDocData, linkArea);

    ASSERT_NE(link, nullptr);
    EXPECT_EQ(link->getKind(), actionGoTo);  // Verifying that the link type matches the expected one
}

// Test boundary condition for null action
TEST_F(PageDataTest_1440, ConvertLinkActionToLink_NullAction_1440) {
    Link* link = pageData->convertLinkActionToLink(nullptr, mockDocData, linkArea);

    EXPECT_EQ(link, nullptr);  // Null action should return a null link
}

// Test actionGoToR handling
TEST_F(PageDataTest_1440, ConvertLinkActionToLink_GoToR_1440) {
    MockLinkAction* mockAction = new MockLinkAction();
    EXPECT_CALL(*mockAction, getKind()).WillOnce(testing::Return(actionGoToR));

    Link* link = pageData->convertLinkActionToLink(mockAction, mockDocData, linkArea);

    ASSERT_NE(link, nullptr);
    EXPECT_EQ(link->getKind(), actionGoToR);
}

// Test exceptional case for an unhandled action type
TEST_F(PageDataTest_1440, ConvertLinkActionToLink_UnhandledAction_1440) {
    MockLinkAction* mockAction = new MockLinkAction();
    EXPECT_CALL(*mockAction, getKind()).WillOnce(testing::Return(actionUnknown));

    Link* link = pageData->convertLinkActionToLink(mockAction, mockDocData, linkArea);

    EXPECT_EQ(link, nullptr);  // Unhandled action type should return null
}

// Test that the next links are correctly converted when there are multiple actions
TEST_F(PageDataTest_1440, ConvertLinkActionToLink_MultipleNextActions_1440) {
    MockLinkAction* mockAction = new MockLinkAction();
    std::vector<std::unique_ptr<LinkAction>> actions;
    actions.push_back(std::make_unique<MockLinkAction>());

    EXPECT_CALL(*mockAction, getKind()).WillOnce(testing::Return(actionGoTo));
    EXPECT_CALL(*mockAction, nextActions()).WillOnce(testing::ReturnRef(actions));

    Link* link = pageData->convertLinkActionToLink(mockAction, mockDocData, linkArea);

    ASSERT_NE(link, nullptr);
    EXPECT_EQ(link->nextLinks.size(), 1);  // Should have one next link based on the mock
}