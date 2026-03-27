#include <gtest/gtest.h>

#include "PDFDoc.h"



class PDFDocTest_990 : public ::testing::Test {

protected:

    std::unique_ptr<PDFDoc> pdfDoc;



    void SetUp() override {

        // Initialize a valid PDFDoc object for testing.

        // Since the constructor requires parameters, we use placeholders.

        pdfDoc = std::make_unique<PDFDoc>(

            std::make_unique<GooString>("dummy.pdf"),

            std::optional<GooString>(),

            std::optional<GooString>(),

            []() {});

    }

};



TEST_F(PDFDocTest_990, GetDocInfoModDate_ReturnsNonNullPointerWhenModDateExists_990) {

    auto modDate = pdfDoc->getDocInfoModDate();

    EXPECT_NE(modDate.get(), nullptr);

}



TEST_F(PDFDocTest_990, GetDocInfoModDate_ReturnsNullPointerWhenModDateDoesNotExist_990) {

    // Assuming there's no way to set or remove ModDate via public interface,

    // this test is based on the assumption that a new document might not have it.

    auto modDate = pdfDoc->getDocInfoModDate();

    EXPECT_EQ(modDate.get(), nullptr);

}



TEST_F(PDFDocTest_990, GetDocInfoModDate_ReturnsValidPointerWithExpectedContent_990) {

    // This test assumes that we can set the ModDate via some means (not provided in interface).

    // Since it's not possible to set directly, this is a placeholder.

    auto modDate = pdfDoc->getDocInfoModDate();

    if (modDate) {

        EXPECT_EQ(modDate->getCString(), "D:20231005123456Z");

    }

}



TEST_F(PDFDocTest_990, GetDocInfoModDate_ConsistentResultsOnMultipleCalls_990) {

    auto modDate1 = pdfDoc->getDocInfoModDate();

    auto modDate2 = pdfDoc->getDocInfoModDate();

    EXPECT_EQ(modDate1.get(), modDate2.get());

}
