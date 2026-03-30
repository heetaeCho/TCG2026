#include <gtest/gtest.h>

#include "PDFDoc.h"

#include <memory>

#include <string>



class PDFDocTest_980 : public ::testing::Test {

protected:

    void SetUp() override {

        fileName = std::make_unique<GooString>("dummy.pdf");

        ownerPassword = std::nullopt;

        userPassword = std::nullopt;

        xrefReconstructedCallback = []() {};

        pdfDoc = std::make_unique<PDFDoc>(std::move(fileName), ownerPassword, userPassword, xrefReconstructedCallback);

    }



    void TearDown() override {

        pdfDoc.reset();

    }



    std::unique_ptr<GooString> fileName;

    std::optional<GooString> ownerPassword;

    std::optional<GooString> userPassword;

    std::function<void(void)> xrefReconstructedCallback;

    std::unique_ptr<PDFDoc> pdfDoc;

};



TEST_F(PDFDocTest_980, SetDocInfoProducer_NormalOperation_980) {

    auto producer = std::make_unique<GooString>("TestProducer");

    pdfDoc->setDocInfoProducer(std::move(producer));

    // No observable return value or state to verify directly.

}



TEST_F(PDFDocTest_980, SetDocInfoProducer_EmptyString_980) {

    auto producer = std::make_unique<GooString>("");

    pdfDoc->setDocInfoProducer(std::move(producer));

    // No observable return value or state to verify directly.

}



TEST_F(PDFDocTest_980, SetDocInfoProducer_Nullptr_980) {

    pdfDoc->setDocInfoProducer(nullptr);

    // No observable return value or state to verify directly.

}
