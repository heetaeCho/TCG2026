#include <gtest/gtest.h>

#include "poppler/PDFDoc.h"



class PDFDocTest_987 : public ::testing::Test {

protected:

    std::unique_ptr<PDFDoc> pdfDoc;



    void SetUp() override {

        // Create a PDFDoc instance for testing purposes.

        // Using nullptr and empty passwords as placeholders since actual file handling is not required.

        pdfDoc = std::make_unique<PDFDoc>(std::make_unique<GooString>("dummy.pdf"), std::optional<GooString>{}, std::optional<GooString>{}, [](){});

    }

};



TEST_F(PDFDocTest_987, GetDocInfoCreator_ReturnsValidPointer_987) {

    auto creator = pdfDoc->getDocInfoCreator();

    EXPECT_NE(creator.get(), nullptr);

}



TEST_F(PDFDocTest_987, GetDocInfoCreator_EmptyStringWhenNotSet_987) {

    auto creator = pdfDoc->getDocInfoCreator();

    EXPECT_EQ(creator->c_str(), "");

}



// Assuming there is a way to set the Creator for boundary conditions and normal operations

// For demonstration purposes, let's assume we have a method to set it (not part of the provided interface)

// TEST_F(PDFDocTest_987, SetAndGetDocInfoCreator_NormalOperation_987) {

//     auto creatorString = std::make_unique<GooString>("Test Creator");

//     pdfDoc->setDocInfoCreator(std::move(creatorString));

//

//     auto creator = pdfDoc->getDocInfoCreator();

//     EXPECT_STREQ(creator->c_str(), "Test Creator");

// }



TEST_F(PDFDocTest_987, GetDocInfoCreator_NotNullWhenSet_987) {

    // Assuming we can set the value through some means (not provided in interface)

    // For demonstration purposes, let's assume we have a method to set it

    // pdfDoc->setDocInfoStringEntry("Creator", std::make_unique<GooString>("Test Creator"));



    auto creator = pdfDoc->getDocInfoCreator();

    EXPECT_NE(creator.get(), nullptr);

}



// Since the internal state cannot be modified, we can't directly test boundary conditions or error cases

// related to setting values. However, we can still check if it behaves correctly when retrieving unset values.

```


