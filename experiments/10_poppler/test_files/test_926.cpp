#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/Form.h"



using namespace testing;



class FormFieldSignatureTest : public Test {

protected:

    PDFDoc* mockPDFDoc;

    Object mockDict;

    Ref mockRef;

    FormField* mockParent;

    std::set<int>* mockUsedParents;

    FormFieldSignature* formFieldSignature;



    void SetUp() override {

        mockPDFDoc = new PDFDoc();

        mockParent = new FormField(nullptr);

        mockUsedParents = new std::set<int>();

        formFieldSignature = new FormFieldSignature(mockPDFDoc, std::move(mockDict), mockRef, mockParent, mockUsedParents);

    }



    void TearDown() override {

        delete formFieldSignature;

        delete mockParent;

        delete mockUsedParents;

        delete mockPDFDoc;

    }

};



TEST_F(FormFieldSignatureTest_926, GetSignatureType_Default_ReturnsUnsigned_926) {

    EXPECT_EQ(formFieldSignature->getSignatureType(), CryptoSign::SignatureType::unsigned_signature_field);

}



TEST_F(FormFieldSignatureTest_926, SetAndGetSignatureType_NormalOperation_Success_926) {

    formFieldSignature->setSignatureType(CryptoSign::SignatureType::pkcs7_detached);

    EXPECT_EQ(formFieldSignature->getSignatureType(), CryptoSign::SignatureType::pkcs7_detached);

}



TEST_F(FormFieldSignatureTest_926, SetAndGetCustomAppearanceContent_NormalOperation_Success_926) {

    GooString content("custom appearance");

    formFieldSignature->setCustomAppearanceContent(content);

    EXPECT_EQ(formFieldSignature->getCustomAppearanceContent(), content);

}



TEST_F(FormFieldSignatureTest_926, SetAndGetCustomAppearanceLeftContent_NormalOperation_Success_926) {

    GooString leftContent("left custom appearance");

    formFieldSignature->setCustomAppearanceLeftContent(leftContent);

    EXPECT_EQ(formFieldSignature->getCustomAppearanceLeftContent(), leftContent);

}



TEST_F(FormFieldSignatureTest_926, SetAndGetCustomAppearanceLeftFontSize_NormalOperation_Success_926) {

    double fontSize = 14.0;

    formFieldSignature->setCustomAppearanceLeftFontSize(fontSize);

    EXPECT_EQ(formFieldSignature->getCustomAppearanceLeftFontSize(), fontSize);

}



TEST_F(FormFieldSignatureTest_926, GetImageResource_Default_ReturnsInvalidRef_926) {

    EXPECT_EQ(formFieldSignature->getImageResource(), Ref::INVALID());

}



TEST_F(FormFieldSignatureTest_926, SetAndGetImageResource_NormalOperation_Success_926) {

    Ref imageResource(10, 0);

    formFieldSignature->setImageResource(imageResource);

    EXPECT_EQ(formFieldSignature->getImageResource(), imageResource);

}



TEST_F(FormFieldSignatureTest_926, GetByteRange_Default_ReturnsValidObjectPointer_926) {

    EXPECT_NE(formFieldSignature->getByteRange(), nullptr);

}



TEST_F(FormFieldSignatureTest_926, GetSignature_Default_ReturnsEmptyVector_926) {

    std::vector<unsigned char> emptySignature;

    EXPECT_EQ(formFieldSignature->getSignature(), emptySignature);

}
