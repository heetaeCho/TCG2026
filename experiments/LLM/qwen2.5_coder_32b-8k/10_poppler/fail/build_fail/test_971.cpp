#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "PDFDoc.h"

#include "XRef.h"



class MockXRef : public XRef {

public:

    MOCK_CONST_METHOD1(okToAssemble, bool(bool ignoreOwnerPW));

};



class PDFDocTest_971 : public ::testing::Test {

protected:

    MockXRef mock_xref;

    std::unique_ptr<PDFDoc> pdf_doc;



    void SetUp() override {

        pdf_doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("dummy.pdf"), std::nullopt, std::nullopt, nullptr);

        // Set the mock XRef to the PDFDoc

        pdf_doc->xref = &mock_xref;

    }

};



TEST_F(PDFDocTest_971, OkToAssemble_NormalOperation_True_971) {

    EXPECT_CALL(mock_xref, okToAssemble(false)).WillOnce(::testing::Return(true));

    ASSERT_TRUE(pdf_doc->okToAssemble());

}



TEST_F(PDFDocTest_971, OkToAssemble_NormalOperation_False_971) {

    EXPECT_CALL(mock_xref, okToAssemble(false)).WillOnce(::testing::Return(false));

    ASSERT_FALSE(pdf_doc->okToAssemble());

}



TEST_F(PDFDocTest_971, OkToAssemble_IgnoreOwnerPW_True_971) {

    EXPECT_CALL(mock_xref, okToAssemble(true)).WillOnce(::testing::Return(true));

    ASSERT_TRUE(pdf_doc->okToAssemble(true));

}



TEST_F(PDFDocTest_971, OkToAssemble_IgnoreOwnerPW_False_971) {

    EXPECT_CALL(mock_xref, okToAssemble(true)).WillOnce(::testing::Return(false));

    ASSERT_FALSE(pdf_doc->okToAssemble(true));

}
