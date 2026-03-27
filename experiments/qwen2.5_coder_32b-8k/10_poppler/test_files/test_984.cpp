#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/PDFDoc.h"

#include "GooString.h"



using ::testing::Return;

using ::testing::_;



class PDFDocTest_984 : public ::testing::Test {

protected:

    PDFDoc* pdfDoc;



    void SetUp() override {

        // Since we cannot create a valid PDFDoc instance without actual file handling,

        // we will mock the necessary behavior for testing purposes.

        pdfDoc = new PDFDoc(nullptr, std::nullopt, std::nullopt, [](){});

    }



    void TearDown() override {

        delete pdfDoc;

    }

};



TEST_F(PDFDocTest_984, GetDocInfoAuthor_ReturnsNullptrWhenNoAuthorSet_984) {

    auto author = pdfDoc->getDocInfoAuthor();

    EXPECT_EQ(author.get(), nullptr);

}



TEST_F(PDFDocTest_984, GetDocInfoAuthor_ReturnsCorrectAuthorString_984) {

    auto authorName = std::make_unique<GooString>("John Doe");

    pdfDoc->setDocInfoAuthor(std::move(authorName));



    auto author = pdfDoc->getDocInfoAuthor();

    EXPECT_NE(author.get(), nullptr);

    EXPECT_STREQ(author->getCString(), "John Doe");

}



TEST_F(PDFDocTest_984, GetDocInfoAuthor_ReturnsSameInstanceOnSubsequentCalls_984) {

    auto authorName = std::make_unique<GooString>("Jane Smith");

    pdfDoc->setDocInfoAuthor(std::move(authorName));



    auto firstCall = pdfDoc->getDocInfoAuthor();

    auto secondCall = pdfDoc->getDocInfoAuthor();



    EXPECT_EQ(firstCall.get(), secondCall.get());

}



TEST_F(PDFDocTest_984, GetDocInfoAuthor_HandlesMultipleAuthorsCorrectly_984) {

    auto authorName1 = std::make_unique<GooString>("Alice");

    pdfDoc->setDocInfoAuthor(std::move(authorName1));

    auto firstCall = pdfDoc->getDocInfoAuthor();

    EXPECT_STREQ(firstCall->getCString(), "Alice");



    auto authorName2 = std::make_unique<GooString>("Bob");

    pdfDoc->setDocInfoAuthor(std::move(authorName2));

    auto secondCall = pdfDoc->getDocInfoAuthor();

    EXPECT_STREQ(secondCall->getCString(), "Bob");

}



TEST_F(PDFDocTest_984, GetDocInfoAuthor_ReturnsNullptrAfterRemovingDocInfo_984) {

    auto authorName = std::make_unique<GooString>("Charlie");

    pdfDoc->setDocInfoAuthor(std::move(authorName));



    pdfDoc->removeDocInfo();

    auto author = pdfDoc->getDocInfoAuthor();

    EXPECT_EQ(author.get(), nullptr);

}
