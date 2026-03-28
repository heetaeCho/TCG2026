#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Form.h"

#include <CryptoSign/CryptoSign.h>



using namespace CryptoSign;



class FormFieldSignatureTest_927 : public ::testing::Test {

protected:

    PDFDoc* doc;

    Object dict;

    Ref ref;

    FormField parent;

    std::set<int> usedParents;



    void SetUp() override {

        // Initialize necessary objects for the test

        doc = new PDFDoc();

        dict.initNull();

        ref.num = 0;

        ref.gen = 0;

        signature_field = std::make_unique<FormFieldSignature>(doc, std::move(dict), ref, &parent, &usedParents);

    }



    void TearDown() override {

        // Clean up after each test

        delete doc;

    }



    std::unique_ptr<FormFieldSignature> signature_field;

};



TEST_F(FormFieldSignatureTest_927, SetAndGetSignatureType_NormalOperation_927) {

    SignatureType type = SignatureType::digital_signature_field;

    signature_field->setSignatureType(type);

    EXPECT_EQ(signature_field->getSignatureType(), type);

}



TEST_F(FormFieldSignatureTest_927, GetInitialSignatureType_BoundaryCondition_927) {

    EXPECT_EQ(signature_field->getSignatureType(), SignatureType::unsigned_signature_field);

}



TEST_F(FormFieldSignatureTest_927, SetAndGetCustomAppearanceContent_NormalOperation_927) {

    GooString content("Custom Appearance Content");

    signature_field->setCustomAppearanceContent(content);

    EXPECT_STREQ(signature_field->getCustomAppearanceContent().getCString(), content.getCString());

}



TEST_F(FormFieldSignatureTest_927, SetAndGetCustomAppearanceLeftContent_NormalOperation_927) {

    GooString left_content("Custom Appearance Left Content");

    signature_field->setCustomAppearanceLeftContent(left_content);

    EXPECT_STREQ(signature_field->getCustomAppearanceLeftContent().getCString(), left_content.getCString());

}



TEST_F(FormFieldSignatureTest_927, SetAndGetCustomAppearanceLeftFontSize_NormalOperation_927) {

    double font_size = 14.5;

    signature_field->setCustomAppearanceLeftFontSize(font_size);

    EXPECT_EQ(signature_field->getCustomAppearanceLeftFontSize(), font_size);

}



TEST_F(FormFieldSignatureTest_927, GetInitialCustomAppearanceLeftFontSize_BoundaryCondition_927) {

    EXPECT_EQ(signature_field->getCustomAppearanceLeftFontSize(), 20.0);

}
