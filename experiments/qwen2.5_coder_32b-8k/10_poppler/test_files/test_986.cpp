#include <gtest/gtest.h>

#include "PDFDoc.h"



class PDFDocTest_986 : public ::testing::Test {

protected:

    std::unique_ptr<PDFDoc> pdf_doc;



    void SetUp() override {

        // Create a mock PDFDoc instance for testing.

        // Since we cannot instantiate the actual class due to dependencies, this is assumed.

        pdf_doc = std::make_unique<PDFDoc>(

            std::make_unique<GooString>("dummy.pdf"),

            std::nullopt,

            std::nullopt,

            []() {}

        );

    }

};



TEST_F(PDFDocTest_986, GetDocInfoKeywords_ReturnsNullptrWhenNoKeywords_986) {

    auto result = pdf_doc->getDocInfoKeywords();

    EXPECT_EQ(result.get(), nullptr);

}



TEST_F(PDFDocTest_986, GetDocInfoKeywords_ReturnsValidStringWhenKeywordsSet_986) {

    auto keywords = std::make_unique<GooString>("test, example");

    pdf_doc->setDocInfoKeywords(std::move(keywords));



    auto result = pdf_doc->getDocInfoKeywords();

    EXPECT_NE(result.get(), nullptr);

    EXPECT_STREQ(result->getCString(), "test, example");

}



TEST_F(PDFDocTest_986, GetDocInfoKeywords_ReturnsSameInstanceOnSubsequentCallsWithNoChanges_986) {

    auto keywords = std::make_unique<GooString>("initial");

    pdf_doc->setDocInfoKeywords(std::move(keywords));



    auto result1 = pdf_doc->getDocInfoKeywords();

    auto result2 = pdf_doc->getDocInfoKeywords();



    EXPECT_EQ(result1.get(), result2.get());

}



TEST_F(PDFDocTest_986, GetDocInfoKeywords_ReturnsUpdatedStringWhenKeywordsChanged_986) {

    auto keywords = std::make_unique<GooString>("initial");

    pdf_doc->setDocInfoKeywords(std::move(keywords));



    auto result1 = pdf_doc->getDocInfoKeywords();

    EXPECT_STREQ(result1->getCString(), "initial");



    auto new_keywords = std::make_unique<GooString>("updated");

    pdf_doc->setDocInfoKeywords(std::move(new_keywords));



    auto result2 = pdf_doc->getDocInfoKeywords();

    EXPECT_STREQ(result2->getCString(), "updated");

}
