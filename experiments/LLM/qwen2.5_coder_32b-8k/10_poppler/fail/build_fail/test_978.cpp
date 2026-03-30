#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler/PDFDoc.h"

#include "goo/GooString.h"



using namespace testing;



class PDFDocTest_978 : public Test {

protected:

    std::unique_ptr<PDFDoc> pdfDoc;

    

    void SetUp() override {

        // Create a valid PDFDoc object using one of the constructors

        auto fileName = std::make_unique<GooString>("dummy.pdf");

        pdfDoc = std::make_unique<PDFDoc>(std::move(fileName), std::nullopt, std::nullopt, [](){});

    }

};



TEST_F(PDFDocTest_978, SetDocInfoKeywords_NormalOperation_978) {

    auto keywords = std::make_unique<GooString>("test_keywords");

    pdfDoc->setDocInfoKeywords(std::move(keywords));

    // No observable behavior to verify directly, but we can check if the operation is successful by attempting retrieval

}



TEST_F(PDFDocTest_978, SetDocInfoKeywords_BoundaryConditions_EmptyString_978) {

    auto keywords = std::make_unique<GooString>("");

    pdfDoc->setDocInfoKeywords(std::move(keywords));

    // No observable behavior to verify directly, but we can check if the operation is successful by attempting retrieval

}



TEST_F(PDFDocTest_978, SetDocInfoKeywords_ExceptionalCase_NullPointer_978) {

    // Test with a null pointer. Since unique_ptr cannot be null, this test case is not applicable.

    // If the function were to accept raw pointers, we could test it, but as it stands, this is redundant.

}



TEST_F(PDFDocTest_978, SetDocInfoKeywords_VerifyExternalInteractions_NoCollaborators_978) {

    auto keywords = std::make_unique<GooString>("test_keywords");

    pdfDoc->setDocInfoKeywords(std::move(keywords));

    // No external collaborators to verify interactions with

}



TEST_F(PDFDocTest_978, GetDocInfoKeywords_NormalOperation_AfterSet_978) {

    auto keywordsToSet = std::make_unique<GooString>("test_keywords");

    pdfDoc->setDocInfoKeywords(std::move(keywordsToSet));



    auto retrievedKeywords = pdfDoc->getDocInfoStringEntry("Keywords");

    ASSERT_NE(retrievedKeywords, nullptr);

    EXPECT_STREQ(retrievedKeywords->getCString(), "test_keywords");

}



TEST_F(PDFDocTest_978, GetDocInfoKeywords_BoundaryConditions_EmptyStringAfterSet_978) {

    auto keywordsToSet = std::make_unique<GooString>("");

    pdfDoc->setDocInfoKeywords(std::move(keywordsToSet));



    auto retrievedKeywords = pdfDoc->getDocInfoStringEntry("Keywords");

    ASSERT_NE(retrievedKeywords, nullptr);

    EXPECT_STREQ(retrievedKeywords->getCString(), "");

}



TEST_F(PDFDocTest_978, GetDocInfoKeywords_ExceptionalCase_Unset_978) {

    auto retrievedKeywords = pdfDoc->getDocInfoStringEntry("Keywords");

    // If the keywords are not set, we expect a nullptr or an empty GooString

    EXPECT_TRUE(retrievedKeywords == nullptr || retrievedKeywords->getCString()[0] == '\0');

}
