#include <gtest/gtest.h>

#include "PDFDoc.h"

#include <memory>



class PDFDocTest : public ::testing::Test {

protected:

    std::unique_ptr<PDFDoc> pdf_doc;



    void SetUp() override {

        // Create a PDFDoc instance with dummy parameters.

        pdf_doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("dummy.pdf"), std::nullopt, std::nullopt, [](){});

    }

};



TEST_F(PDFDocTest_975, SetAndGetDocInfoTitle_NormalOperation_975) {

    auto title = std::make_unique<GooString>("Sample Title");

    pdf_doc->setDocInfoTitle(std::move(title));

    auto retrieved_title = pdf_doc->getDocInfoTitle();

    ASSERT_EQ(retrieved_title->cmp("Sample Title"), 0);

}



TEST_F(PDFDocTest_975, SetAndGetDocInfoTitle_EmptyString_975) {

    auto title = std::make_unique<GooString>("");

    pdf_doc->setDocInfoTitle(std::move(title));

    auto retrieved_title = pdf_doc->getDocInfoTitle();

    ASSERT_EQ(retrieved_title->cmp(""), 0);

}



TEST_F(PDFDocTest_975, SetAndGetDocInfoTitle_SpecialCharacters_975) {

    auto title = std::make_unique<GooString>("!@#$%^&*()_+");

    pdf_doc->setDocInfoTitle(std::move(title));

    auto retrieved_title = pdf_doc->getDocInfoTitle();

    ASSERT_EQ(retrieved_title->cmp("!@#$%^&*()_+"), 0);

}



TEST_F(PDFDocTest_975, SetAndGetDocInfoTitle_LargeString_975) {

    std::string large_string(1024, 'A');

    auto title = std::make_unique<GooString>(large_string.c_str());

    pdf_doc->setDocInfoTitle(std::move(title));

    auto retrieved_title = pdf_doc->getDocInfoTitle();

    ASSERT_EQ(retrieved_title->cmp(large_string.c_str()), 0);

}
