#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mocking Catalog class to simulate its behavior

class MockCatalog : public Catalog {

public:

    MOCK_METHOD(int, getNumPages, (), (const));

    MOCK_METHOD(Ref*, getPageRef, (int), (const));

    MOCK_METHOD(std::unique_ptr<LinkDest>, getDestNameTreeDest, (int), (const));

    MOCK_METHOD(int, numDestNameTree, (), (const));

    MOCK_METHOD(const GooString*, getDestNameTreeName, (int), (const));

    MOCK_METHOD(int, numDests, (), (const));

    MOCK_METHOD(const char*, getDestsName, (int), (const));

    MOCK_METHOD(std::unique_ptr<LinkDest>, getDestsDest, (int), (const));

};



// Mocking LinkDest class to simulate its behavior

class MockLinkDest : public LinkDest {

public:

    MOCK_METHOD(bool, isPageRef, (), (const));

    MOCK_METHOD(Ref, getPageRef, (), (const));

};



// Mocking PDFDoc class to return the mocked Catalog object

class MockPDFDoc : public PDFDoc {

public:

    MockCatalog* catalogMock = new MockCatalog;



    MockPDFDoc() {}

    ~MockPDFDoc() { delete catalogMock; }



    MOCK_METHOD(Catalog*, getCatalog, (), (const));

};



// Test fixture for printDestinations function

class PrintDestinationsTest_2671 : public ::testing::Test {

protected:

    void SetUp() override {

        pdfDocMock = new MockPDFDoc();

        EXPECT_CALL(*pdfDocMock, getCatalog()).WillRepeatedly(::testing::Return(pdfDocMock->catalogMock));

    }



    void TearDown() override {

        delete pdfDocMock;

    }



    MockPDFDoc* pdfDocMock;

};



TEST_F(PrintDestinationsTest_2671, NoDests_2671) {

    EXPECT_CALL(*pdfDocMock->catalogMock, getNumPages()).WillOnce(::testing::Return(0));

    EXPECT_CALL(*pdfDocMock->catalogMock, numDestNameTree()).WillOnce(::testing::Return(0));

    EXPECT_CALL(*pdfDocMock->catalogMock, numDests()).WillOnce(::testing::Return(0));



    testing::internal::CaptureStdout();

    printDestinations(pdfDocMock, nullptr);

    std::string output = testing::internal::GetCapturedStdout();



    EXPECT_EQ(output, "Page Destination Name\n");

}



TEST_F(PrintDestinationsTest_2671, SingleDestOnFirstPage_2671) {

    Ref pageRef{1, 0};

    auto linkDestMock = std::make_unique<MockLinkDest>();

    EXPECT_CALL(*linkDestMock, isPageRef()).WillOnce(::testing::Return(true));

    EXPECT_CALL(*linkDestMock, getPageRef()).WillOnce(::testing::Return(pageRef));



    EXPECT_CALL(*pdfDocMock->catalogMock, getNumPages()).WillOnce(::testing::Return(1));

    EXPECT_CALL(*pdfDocMock->catalogMock, numDestNameTree()).WillOnce(::testing::Return(0));

    EXPECT_CALL(*pdfDocMock->catalogMock, numDests()).WillOnce(::testing::Return(1));



    EXPECT_CALL(*pdfDocMock->catalogMock, getPageRef(1)).WillOnce(::testing::Return(&pageRef));

    EXPECT_CALL(*pdfDocMock->catalogMock, getDestsName(0)).WillOnce(::testing::Return("Destination1"));

    EXPECT_CALL(*pdfDocMock->catalogMock, getDestsDest(0)).WillOnce(::testing::Return(ByMove(std::move(linkDestMock))));



    testing::internal::CaptureStdout();

    printDestinations(pdfDocMock, nullptr);

    std::string output = testing::internal::GetCapturedStdout();



    EXPECT_EQ(output, "Page Destination Name\n   1 <LinkDest> \"Destination1\"\n");

}



TEST_F(PrintDestinationsTest_2671, MultipleDestsOnDifferentPages_2671) {

    Ref pageRef1{1, 0};

    Ref pageRef2{2, 0};



    auto linkDestMock1 = std::make_unique<MockLinkDest>();

    EXPECT_CALL(*linkDestMock1, isPageRef()).WillOnce(::testing::Return(true));

    EXPECT_CALL(*linkDestMock1, getPageRef()).WillOnce(::testing::Return(pageRef1));



    auto linkDestMock2 = std::make_unique<MockLinkDest>();

    EXPECT_CALL(*linkDestMock2, isPageRef()).WillOnce(::testing::Return(true));

    EXPECT_CALL(*linkDestMock2, getPageRef()).WillOnce(::testing::Return(pageRef2));



    EXPECT_CALL(*pdfDocMock->catalogMock, getNumPages()).WillOnce(::testing::Return(3));

    EXPECT_CALL(*pdfDocMock->catalogMock, numDestNameTree()).WillOnce(::testing::Return(0));

    EXPECT_CALL(*pdfDocMock->catalogMock, numDests()).WillOnce(::testing::Return(2));



    EXPECT_CALL(*pdfDocMock->catalogMock, getPageRef(1)).WillOnce(::testing::Return(&pageRef1));

    EXPECT_CALL(*pdfDocMock->catalogMock, getDestsName(0)).WillOnce(::testing::Return("Destination1"));

    EXPECT_CALL(*pdfDocMock->catalogMock, getDestsDest(0)).WillOnce(::testing::Return(ByMove(std::move(linkDestMock1))));



    EXPECT_CALL(*pdfDocMock->catalogMock, getPageRef(2)).WillOnce(::testing::Return(&pageRef2));

    EXPECT_CALL(*pdfDocMock->catalogMock, getDestsName(1)).WillOnce(::testing::Return("Destination2"));

    EXPECT_CALL(*pdfDocMock->catalogMock, getDestsDest(1)).WillOnce(::testing::Return(ByMove(std::move(linkDestMock2))));



    testing::internal::CaptureStdout();

    printDestinations(pdfDocMock, nullptr);

    std::string output = testing::internal::GetCapturedStdout();



    EXPECT_EQ(output, "Page Destination Name\n   1 <LinkDest> \"Destination1\"\n   2 <LinkDest> \"Destination2\"\n");

}



TEST_F(PrintDestinationsTest_2671, DestsWithSameNameOnDifferentPages_2671) {

    Ref pageRef1{1, 0};

    Ref pageRef2{2, 0};



    auto linkDestMock1 = std::make_unique<MockLinkDest>();

    EXPECT_CALL(*linkDestMock1, isPageRef()).WillOnce(::testing::Return(true));

    EXPECT_CALL(*linkDestMock1, getPageRef()).WillOnce(::testing::Return(pageRef1));



    auto linkDestMock2 = std::make_unique<MockLinkDest>();

    EXPECT_CALL(*linkDestMock2, isPageRef()).WillOnce(::testing::Return(true));

    EXPECT_CALL(*linkDestMock2, getPageRef()).WillOnce(::testing::Return(pageRef2));



    EXPECT_CALL(*pdfDocMock->catalogMock, getNumPages()).WillOnce(::testing::Return(3));

    EXPECT_CALL(*pdfDocMock->catalogMock, numDestNameTree()).WillOnce(::testing::Return(0));

    EXPECT_CALL(*pdfDocMock->catalogMock, numDests()).WillOnce(::testing::Return(2));



    EXPECT_CALL(*pdfDocMock->catalogMock, getPageRef(1)).WillOnce(::testing::Return(&pageRef1));

    EXPECT_CALL(*pdfDocMock->catalogMock, getDestsName(0)).WillOnce(::testing::Return("Destination1"));

    EXPECT_CALL(*pdfDocMock->catalogMock, getDestsDest(0)).WillOnce(::testing::Return(ByMove(std::move(linkDestMock1))));



    EXPECT_CALL(*pdfDocMock->catalogMock, getPageRef(2)).WillOnce(::testing::Return(&pageRef2));

    EXPECT_CALL(*pdfDocMock->catalogMock, getDestsName(1)).WillOnce(::testing::Return("Destination1"));

    EXPECT_CALL(*pdfDocMock->catalogMock, getDestsDest(1)).WillOnce(::testing::Return(ByMove(std::move(linkDestMock2))));



    testing::internal::CaptureStdout();

    printDestinations(pdfDocMock, nullptr);

    std::string output = testing::internal::GetCapturedStdout();



    EXPECT_EQ(output, "Page Destination Name\n   1 <LinkDest> \"Destination1\"\n   2 <LinkDest> \"Destination1\"\n");

}



TEST_F(PrintDestinationsTest_2671, NoPageRefsInDests_2671) {

    Ref pageRef{1, 0};



    auto linkDestMock = std::make_unique<MockLinkDest>();

    EXPECT_CALL(*linkDestMock, isPageRef()).WillOnce(::testing::Return(false));



    EXPECT_CALL(*pdfDocMock->catalogMock, getNumPages()).WillOnce(::testing::Return(1));

    EXPECT_CALL(*pdfDocMock->catalogMock, numDestNameTree()).WillOnce(::testing::Return(0));

    EXPECT_CALL(*pdfDocMock->catalogMock, numDests()).WillOnce(::testing::Return(1));



    EXPECT_CALL(*pdfDocMock->catalogMock, getPageRef(1)).WillOnce(::testing::Return(&pageRef));

    EXPECT_CALL(*pdfDocMock->catalogMock, getDestsName(0)).WillOnce(::testing::Return("Destination1"));

    EXPECT_CALL(*pdfDocMock->catalogMock, getDestsDest(0)).WillOnce(::testing::Return(ByMove(std::move(linkDestMock))));



    testing::internal::CaptureStdout();

    printDestinations(pdfDocMock, nullptr);

    std::string output = testing::internal::GetCapturedStdout();



    EXPECT_EQ(output, "Page Destination Name\n");

}



TEST_F(PrintDestinationsTest_2671, DestsOnNonExistentPages_2671) {

    Ref pageRef{3, 0};



    auto linkDestMock = std::make_unique<MockLinkDest>();

    EXPECT_CALL(*linkDestMock, isPageRef()).WillOnce(::testing::Return(true));

    EXPECT_CALL(*linkDestMock, getPageRef()).WillOnce(::testing::Return(pageRef));



    EXPECT_CALL(*pdfDocMock->catalogMock, getNumPages()).WillOnce(::testing::Return(2));

    EXPECT_CALL(*pdfDocMock->catalogMock, numDestNameTree()).WillOnce(::testing::Return(0));

    EXPECT_CALL(*pdfDocMock->catalogMock, numDests()).WillOnce(::testing::Return(1));



    EXPECT_CALL(*pdfDocMock->catalogMock, getPageRef(3)).WillOnce(::testing::Return(nullptr));

    EXPECT_CALL(*pdfDocMock->catalogMock, getDestsName(0)).WillOnce(::testing::Return("Destination1"));

    EXPECT_CALL(*pdfDocMock->catalogMock, getDestsDest(0)).WillOnce(::testing::Return(ByMove(std::move(linkDestMock))));



    testing::internal::CaptureStdout();

    printDestinations(pdfDocMock, nullptr);

    std::string output = testing::internal::GetCapturedStdout();



    EXPECT_EQ(output, "Page Destination Name\n");

}
