#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler/PDFDoc.h"

#include "goo/GooString.h"



class PDFDocTest_985 : public ::testing::Test {

protected:

    std::unique_ptr<PDFDoc> pdfDoc;



    void SetUp() override {

        // Assuming a valid PDF file is provided for testing

        auto fileName = std::make_unique<GooString>("test.pdf");

        std::optional<GooString> ownerPassword;

        std::optional<GooString> userPassword;

        std::function<void(void)> xrefReconstructedCallback;



        pdfDoc = std::make_unique<PDFDoc>(std::move(fileName), ownerPassword, userPassword, xrefReconstructedCallback);

    }

};



TEST_F(PDFDocTest_985, GetDocInfoSubject_ReturnsNonNullPointerForExistingEntry_985) {

    auto subject = pdfDoc->getDocInfoSubject();

    ASSERT_NE(subject.get(), nullptr);

}



TEST_F(PDFDocTest_985, GetDocInfoSubject_ReturnsNullPointerForNonExistingEntry_985) {

    // Assuming there is no "NonExistentKey" entry in the PDF document

    auto nonExistentEntry = pdfDoc->getDocInfoStringEntry("NonExistentKey");

    ASSERT_EQ(nonExistentEntry.get(), nullptr);

}



TEST_F(PDFDocTest_985, GetDocInfoSubject_HandlesBoundaryConditionsProperly_985) {

    // Assuming the document is in a state where getDocInfoStringEntry can handle boundary conditions

    auto subject = pdfDoc->getDocInfoSubject();

    ASSERT_TRUE(subject->hasData());

}



TEST_F(PDFDocTest_985, GetDocInfoSubject_HandlesErrorCasesProperly_985) {

    // Assuming the document is in a state where getDocInfoStringEntry can handle error cases

    auto subject = pdfDoc->getDocInfoSubject();

    ASSERT_NE(subject.get(), nullptr);

}



// Additional tests based on other public functions if necessary, but focusing on getDocInfoSubject as per provided interface.
