#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler/PDFDoc.h"

#include "poppler/XRef.h"



using ::testing::_;

using ::testing::Return;

using ::testing::NiceMock;



class MockXRef : public XRef {

public:

    MOCK_METHOD(Object, getDocInfoNF, (), (override));

};



class PDFDocTest_973 : public ::testing::Test {

protected:

    NiceMock<MockXRef> mock_xref;

    PDFDoc pdf_doc;



    void SetUp() override {

        // Inject the mocked XRef into the PDFDoc

        pdf_doc.xref = &mock_xref;

    }



    void TearDown() override {

        // Reset the injected XRef

        pdf_doc.xref = nullptr;

    }

};



TEST_F(PDFDocTest_973, GetDocInfoNF_NormalOperation_973) {

    Object expected_obj;

    EXPECT_CALL(mock_xref, getDocInfoNF()).WillOnce(Return(expected_obj));



    Object result = pdf_doc.getDocInfoNF();



    EXPECT_EQ(&result, &expected_obj);

}



TEST_F(PDFDocTest_973, GetDocInfoNF_ExceptionalCase_973) {

    // Assuming exceptional case means getDocInfoNF returns an invalid object

    Object expected_invalid_obj;

    expected_invalid_obj.initNull();

    EXPECT_CALL(mock_xref, getDocInfoNF()).WillOnce(Return(expected_invalid_obj));



    Object result = pdf_doc.getDocInfoNF();



    EXPECT_TRUE(result.isNull());

}



TEST_F(PDFDocTest_973, GetDocInfoNF_VerifyExternalInteraction_973) {

    // Verify that getDocInfoNF interacts with the mocked XRef's method

    EXPECT_CALL(mock_xref, getDocInfoNF()).Times(1);



    pdf_doc.getDocInfoNF();

}
