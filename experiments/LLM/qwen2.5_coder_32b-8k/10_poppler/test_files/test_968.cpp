#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "PDFDoc.h"

#include "XRef.h"



using namespace testing;



class MockXRef : public XRef {

public:

    MOCK_METHOD(bool, okToAddNotes, (bool ignoreOwnerPW), (const));

};



class PDFDocTest_968 : public ::testing::Test {

protected:

    MockXRef mock_xref;

    std::unique_ptr<PDFDoc> pdf_doc;



    void SetUp() override {

        // We assume that the constructor of PDFDoc can take a pointer to XRef.

        // This might require modifying the actual code or using a test-specific constructor.

        // For this example, we will use a pointer to simulate it.

        pdf_doc = std::make_unique<PDFDoc>();

        pdf_doc->xref = &mock_xref;

    }

};



TEST_F(PDFDocTest_968, OkToAddNotes_DefaultCase_968) {

    EXPECT_CALL(mock_xref, okToAddNotes(false)).WillOnce(Return(true));

    bool result = pdf_doc->okToAddNotes();

    EXPECT_TRUE(result);

}



TEST_F(PDFDocTest_968, OkToAddNotes_IgnoreOwnerPWTrue_968) {

    EXPECT_CALL(mock_xref, okToAddNotes(true)).WillOnce(Return(false));

    bool result = pdf_doc->okToAddNotes(true);

    EXPECT_FALSE(result);

}



TEST_F(PDFDocTest_968, OkToAddNotes_IgnoreOwnerPWFalse_968) {

    EXPECT_CALL(mock_xref, okToAddNotes(false)).WillOnce(Return(false));

    bool result = pdf_doc->okToAddNotes(false);

    EXPECT_FALSE(result);

}
