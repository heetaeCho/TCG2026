#include <gtest/gtest.h>

#include "PDFDoc.h"

#include "GooString.h"



class PDFDocTest_988 : public ::testing::Test {

protected:

    std::unique_ptr<PDFDoc> pdfDoc;



    void SetUp() override {

        // Assuming a default constructor or mock setup is available for testing purposes

        // Since we cannot re-implement or infer internal logic, this remains abstract

        pdfDoc = std::make_unique<PDFDoc>();

    }

};



TEST_F(PDFDocTest_988, GetDocInfoProducer_ReturnsValidString_988) {

    auto producer = pdfDoc->getDocInfoProducer();

    EXPECT_TRUE(producer != nullptr);

}



TEST_F(PDFDocTest_988, GetDocInfoProducer_ReturnsNullptrWhenNotSet_988) {

    // Assuming no other setup has been done to set the producer

    auto producer = pdfDoc->getDocInfoProducer();

    EXPECT_EQ(producer.get(), nullptr);

}
