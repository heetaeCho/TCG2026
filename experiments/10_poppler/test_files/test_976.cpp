#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "PDFDoc.h"

#include "GooString.h"



using namespace testing;



class PDFDocTest_976 : public Test {

protected:

    std::unique_ptr<PDFDoc> pdfDoc;

    std::unique_ptr<GooString> authorName;



    void SetUp() override {

        // Assuming a default constructor or mock constructor setup is available for testing

        pdfDoc = std::make_unique<PDFDoc>();

        authorName = std::make_unique<GooString>("Test Author");

    }

};



TEST_F(PDFDocTest_976, SetDocInfoAuthor_NormalOperation_976) {

    // Test setting the author with a normal string

    EXPECT_NO_THROW(pdfDoc->setDocInfoAuthor(std::move(authorName)));

}



TEST_F(PDFDocTest_976, SetDocInfoAuthor_EmptyString_976) {

    // Test setting the author with an empty string

    auto emptyAuthor = std::make_unique<GooString>("");

    EXPECT_NO_THROW(pdfDoc->setDocInfoAuthor(std::move(emptyAuthor)));

}



TEST_F(PDFDocTest_976, SetDocInfoAuthor_NullString_976) {

    // Test setting the author with a null string (moved from unique_ptr)

    auto nullAuthor = std::unique_ptr<GooString>(nullptr);

    EXPECT_NO_THROW(pdfDoc->setDocInfoAuthor(std::move(nullAuthor)));

}



TEST_F(PDFDocTest_976, SetDocInfoAuthor_LongString_976) {

    // Test setting the author with a very long string

    auto longAuthor = std::make_unique<GooString>(std::string(1024 * 1024, 'A')); // 1MB long string

    EXPECT_NO_THROW(pdfDoc->setDocInfoAuthor(std::move(longAuthor)));

}



TEST_F(PDFDocTest_976, GetDocInfoAuthor_AfterSet_976) {

    // Test retrieving the author after setting it

    pdfDoc->setDocInfoAuthor(std::move(authorName));

    auto retrievedAuthor = pdfDoc->getDocInfoStringEntry("Author");

    ASSERT_NE(retrievedAuthor, nullptr);

    EXPECT_EQ(strcmp(retrievedAuthor->getCString(), "Test Author"), 0);

}



TEST_F(PDFDocTest_976, SetAndGetDocInfoAuthor_MultipleTimes_976) {

    // Test setting and getting the author multiple times

    auto firstAuthor = std::make_unique<GooString>("First Author");

    pdfDoc->setDocInfoAuthor(std::move(firstAuthor));

    auto retrievedFirstAuthor = pdfDoc->getDocInfoStringEntry("Author");

    ASSERT_NE(retrievedFirstAuthor, nullptr);

    EXPECT_EQ(strcmp(retrievedFirstAuthor->getCString(), "First Author"), 0);



    auto secondAuthor = std::make_unique<GooString>("Second Author");

    pdfDoc->setDocInfoAuthor(std::move(secondAuthor));

    auto retrievedSecondAuthor = pdfDoc->getDocInfoStringEntry("Author");

    ASSERT_NE(retrievedSecondAuthor, nullptr);

    EXPECT_EQ(strcmp(retrievedSecondAuthor->getCString(), "Second Author"), 0);

}
