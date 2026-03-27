#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/PDFDoc.h"

#include "TestProjects/poppler/poppler/GooString.h"



using namespace testing;



class PDFDocTest : public ::testing::Test {

protected:

    std::unique_ptr<PDFDoc> pdfDoc;

    std::unique_ptr<GooString> creator;



    void SetUp() override {

        // Create a valid PDFDoc instance

        pdfDoc = std::make_unique<PDFDoc>(std::make_unique<GooString>("dummy.pdf"), std::nullopt, std::nullopt, [](){});

        creator = std::make_unique<GooString>("Test Creator");

    }

};



TEST_F(PDFDocTest_979, SetCreator_NormalOperation_979) {

    pdfDoc->setDocInfoCreator(std::move(creator));

    // Assuming getDocInfoStringEntry is available to verify the change

    auto retrievedCreator = pdfDoc->getDocInfoStringEntry("Creator");

    ASSERT_NE(retrievedCreator, nullptr);

    EXPECT_STREQ(retrievedCreator->getCString(), "Test Creator");

}



TEST_F(PDFDocTest_979, SetCreator_EmptyString_979) {

    creator = std::make_unique<GooString>("");

    pdfDoc->setDocInfoCreator(std::move(creator));

    auto retrievedCreator = pdfDoc->getDocInfoStringEntry("Creator");

    ASSERT_NE(retrievedCreator, nullptr);

    EXPECT_STREQ(retrievedCreator->getCString(), "");

}



TEST_F(PDFDocTest_979, SetCreator_LongString_979) {

    creator = std::make_unique<GooString>("A very long string that represents a creator name which is unusually lengthy for demonstration purposes");

    pdfDoc->setDocInfoCreator(std::move(creator));

    auto retrievedCreator = pdfDoc->getDocInfoStringEntry("Creator");

    ASSERT_NE(retrievedCreator, nullptr);

    EXPECT_STREQ(retrievedCreator->getCString(), "A very long string that represents a creator name which is unusually lengthy for demonstration purposes");

}



TEST_F(PDFDocTest_979, SetCreator_NullptrHandling_979) {

    creator.reset();

    pdfDoc->setDocInfoCreator(std::move(creator));

    auto retrievedCreator = pdfDoc->getDocInfoStringEntry("Creator");

    EXPECT_EQ(retrievedCreator, nullptr);

}
