#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Page.h"



class PageTest : public ::testing::Test {

protected:

    class MockDict : public Dict {

    public:

        MOCK_METHOD(Dict*, copy, (), (const, override));

    };



    std::unique_ptr<MockDict> mockDict;

    std::unique_ptr<PageAttrs> pageAttrs;

    PDFDoc* mockPDFDoc = nullptr; // Assuming PDFDoc is not required to be mocked for this test

    Object pageDict;

    Ref pageRef;



    void SetUp() override {

        mockDict = std::make_unique<MockDict>();

        pageAttrs = std::make_unique<PageAttrs>(nullptr, mockDict.get());

    }

};



TEST_F(PageTest_718, GetPieceInfo_ReturnsCorrectDict_718) {

    Page page(mockPDFDoc, 0, std::move(pageDict), pageRef, std::move(pageAttrs));



    EXPECT_EQ(page.getPieceInfo(), mockDict.get());

}



TEST_F(PageTest_718, GetPieceInfo_ReturnsNullPtrWhenNoPieceInfo_718) {

    auto attrs = std::make_unique<PageAttrs>(nullptr, nullptr);

    Page page(mockPDFDoc, 0, std::move(pageDict), pageRef, std::move(attrs));



    EXPECT_EQ(page.getPieceInfo(), nullptr);

}
