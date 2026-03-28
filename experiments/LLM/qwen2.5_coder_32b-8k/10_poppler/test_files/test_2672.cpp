#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler/PDFDoc.h"

#include "poppler/Links.h"

#include "poppler/Page.h"

#include "poppler/AnnotLink.h"

#include "poppler/LinkAction.h"

#include "poppler/LinkURI.h"



using namespace testing;



// Mock PDFDoc class

class MockPDFDoc : public PDFDoc {

public:

    MOCK_METHOD(int, getNumPages, (), (override));

    MOCK_METHOD(Page*, getPage, (int page), (override));

};



// Mock Page class

class MockPage : public Page {

public:

    MOCK_METHOD(std::unique_ptr<Links>, getLinks, (), (override));

};



// Mock Links class

class MockLinks : public Links {

public:

    MOCK_METHOD(const std::vector<std::shared_ptr<AnnotLink>>&, getLinks, (), (const override));

};



// Mock AnnotLink class

class MockAnnotLink : public AnnotLink {

public:

    MOCK_METHOD(LinkAction*, getAction, (), (override));

};



// Mock LinkAction class

class MockLinkAction : public LinkAction {

public:

    MOCK_METHOD(ActionKind, getKind, (), (const override));

};



// Mock LinkURI class

class MockLinkURI : public LinkURI {

public:

    MOCK_METHOD(std::string, getURI, (), (const override));

};



class PrintUrlListTest_2672 : public Test {

protected:

    void SetUp() override {

        doc = std::make_unique<MockPDFDoc>();

        ON_CALL(*doc, getNumPages()).WillByDefault(Return(3)); // Assuming 3 pages for testing

        firstPage = 1;

        lastPage = 3;

    }



    static int firstPage;

    static int lastPage;



    std::unique_ptr<MockPDFDoc> doc;

};



int PrintUrlListTest_2672::firstPage = 1;

int PrintUrlListTest_2672::lastPage = 0;



TEST_F(PrintUrlListTest_2672, NoLinksOnPages_2672) {

    ON_CALL(*doc, getNumPages()).WillByDefault(Return(3));

    for (int pg = firstPage; pg <= lastPage; ++pg) {

        EXPECT_CALL(*doc, getPage(pg)).WillOnce(Return(nullptr));

    }



    testing::internal::CaptureStdout();

    printUrlList(doc.get());

    std::string output = testing::internal::GetCapturedStdout();



    EXPECT_EQ(output, "Page Type URL\n");

}



TEST_F(PrintUrlListTest_2672, OneLinkPerPage_2672) {

    ON_CALL(*doc, getNumPages()).WillByDefault(Return(3));

    for (int pg = firstPage; pg <= lastPage; ++pg) {

        auto mockPage = std::make_unique<MockPage>();

        auto mockLinks = std::make_unique<MockLinks>();

        auto mockAnnotLink = std::make_shared<MockAnnotLink>();

        auto mockAction = std::make_unique<MockLinkAction>();

        auto mockUri = std::make_unique<MockLinkURI>();



        EXPECT_CALL(*doc, getPage(pg)).WillOnce(Return(mockPage.get()));

        EXPECT_CALL(*mockPage, getLinks()).WillOnce(Return(ByMove(std::move(mockLinks))));

        EXPECT_CALL(*mockLinks, getLinks()).WillOnce(Return(std::vector<std::shared_ptr<AnnotLink>>{mockAnnotLink}));

        EXPECT_CALL(*mockAnnotLink, getAction()).WillOnce(Return(mockAction.get()));

        EXPECT_CALL(*mockAction, getKind()).WillOnce(Return(actionURI));

        EXPECT_CALL(*mockUri, getURI()).WillOnce(Return("http://example.com"));



        mockLinks->getLinks()[0]->setAction(std::move(mockAction));

        mockAnnotLink->setAction(std::move(mockUri));



        mockPage.release();

    }



    testing::internal::CaptureStdout();

    printUrlList(doc.get());

    std::string output = testing::internal::GetCapturedStdout();



    EXPECT_EQ(output, "Page Type URL\n   1 Annotation http://example.com\n   2 Annotation http://example.com\n   3 Annotation http://example.com\n");

}



TEST_F(PrintUrlListTest_2672, MultipleLinksOnSamePage_2672) {

    ON_CALL(*doc, getNumPages()).WillByDefault(Return(1));

    firstPage = 1;

    lastPage = 1;



    auto mockPage = std::make_unique<MockPage>();

    auto mockLinks = std::make_unique<MockLinks>();

    auto mockAnnotLink1 = std::make_shared<MockAnnotLink>();

    auto mockAction1 = std::make_unique<MockLinkAction>();

    auto mockUri1 = std::make_unique<MockLinkURI>();

    auto mockAnnotLink2 = std::make_shared<MockAnnotLink>();

    auto mockAction2 = std::make_unique<MockLinkAction>();

    auto mockUri2 = std::make_unique<MockLinkURI>();



    EXPECT_CALL(*doc, getPage(1)).WillOnce(Return(mockPage.get()));

    EXPECT_CALL(*mockPage, getLinks()).WillOnce(Return(ByMove(std::move(mockLinks))));

    EXPECT_CALL(*mockLinks, getLinks()).WillOnce(Return(std::vector<std::shared_ptr<AnnotLink>>{mockAnnotLink1, mockAnnotLink2}));

    

    EXPECT_CALL(*mockAnnotLink1, getAction()).WillOnce(Return(mockAction1.get()));

    EXPECT_CALL(*mockAction1, getKind()).WillOnce(Return(actionURI));

    EXPECT_CALL(*mockUri1, getURI()).WillOnce(Return("http://example.com/1"));



    mockLinks->getLinks()[0]->setAction(std::move(mockAction1));

    mockAnnotLink1->setAction(std::move(mockUri1));



    EXPECT_CALL(*mockAnnotLink2, getAction()).WillOnce(Return(mockAction2.get()));

    EXPECT_CALL(*mockAction2, getKind()).WillOnce(Return(actionURI));

    EXPECT_CALL(*mockUri2, getURI()).WillOnce(Return("http://example.com/2"));



    mockLinks->getLinks()[1]->setAction(std::move(mockAction2));

    mockAnnotLink2->setAction(std::move(mockUri2));



    mockPage.release();



    testing::internal::CaptureStdout();

    printUrlList(doc.get());

    std::string output = testing::internal::GetCapturedStdout();



    EXPECT_EQ(output, "Page Type URL\n   1 Annotation http://example.com/1\n   1 Annotation http://example.com/2\n");

}



TEST_F(PrintUrlListTest_2672, NoLinksAtAll_2672) {

    ON_CALL(*doc, getNumPages()).WillByDefault(Return(0));



    testing::internal::CaptureStdout();

    printUrlList(doc.get());

    std::string output = testing::internal::GetCapturedStdout();



    EXPECT_EQ(output, "Page Type URL\n");

}



TEST_F(PrintUrlListTest_2672, ActionNotURI_2672) {

    ON_CALL(*doc, getNumPages()).WillByDefault(Return(1));

    firstPage = 1;

    lastPage = 1;



    auto mockPage = std::make_unique<MockPage>();

    auto mockLinks = std::make_unique<MockLinks>();

    auto mockAnnotLink = std::make_shared<MockAnnotLink>();

    auto mockAction = std::make_unique<MockLinkAction>();



    EXPECT_CALL(*doc, getPage(1)).WillOnce(Return(mockPage.get()));

    EXPECT_CALL(*mockPage, getLinks()).WillOnce(Return(ByMove(std::move(mockLinks))));

    EXPECT_CALL(*mockLinks, getLinks()).WillOnce(Return(std::vector<std::shared_ptr<AnnotLink>>{mockAnnotLink}));

    EXPECT_CALL(*mockAnnotLink, getAction()).WillOnce(Return(mockAction.get()));

    EXPECT_CALL(*mockAction, getKind()).WillOnce(Return(actionGoTo));



    mockPage.release();



    testing::internal::CaptureStdout();

    printUrlList(doc.get());

    std::string output = testing::internal::GetCapturedStdout();



    EXPECT_EQ(output, "Page Type URL\n");

}
