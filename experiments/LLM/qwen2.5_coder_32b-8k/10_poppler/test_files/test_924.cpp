#include <gtest/gtest.h>

#include "Form.h"

#include <gmock/gmock.h>



using namespace testing;



class FormFieldSignatureTest_924 : public ::testing::Test {

protected:

    PDFDoc* doc;

    Object dict;

    Ref ref;

    FormField parent;

    std::set<int> usedParents;



    void SetUp() override {

        doc = new PDFDoc();

        dict.initNull();

        ref.num = 1;

        ref.gen = 0;

    }



    void TearDown() override {

        delete doc;

    }

};



TEST_F(FormFieldSignatureTest_924, GetByteRange_ReturnsNonNullPointer_924) {

    FormFieldSignature formFieldSignature(doc, std::move(dict), ref, &parent, &usedParents);

    EXPECT_NE(formFieldSignature.getByteRange(), nullptr);

}



TEST_F(FormFieldSignatureTest_924, GetSignature_ReturnsEmptyVectorByDefault_924) {

    FormFieldSignature formFieldSignature(doc, std::move(dict), ref, &parent, &usedParents);

    EXPECT_TRUE(formFieldSignature.getSignature().empty());

}



TEST_F(FormFieldSignatureTest_924, SetAndGetSignature_ModifiesSignatureCorrectly_924) {

    FormFieldSignature formFieldSignature(doc, std::move(dict), ref, &parent, &usedParents);

    std::vector<unsigned char> testSignature = {0x12, 0x34, 0x56};

    formFieldSignature.setSignature(std::move(testSignature));

    EXPECT_EQ(formFieldSignature.getSignature(), std::vector<unsigned char>({0x12, 0x34, 0x56}));

}



TEST_F(FormFieldSignatureTest_924, GetSignatureType_ReturnsDefaultType_924) {

    FormFieldSignature formFieldSignature(doc, std::move(dict), ref, &parent, &usedParents);

    EXPECT_EQ(formFieldSignature.getSignatureType(), CryptoSign::SignatureType::unsigned_signature_field);

}



TEST_F(FormFieldSignatureTest_924, SetAndGetSignatureType_ModifiesSignatureTypeCorrectly_924) {

    FormFieldSignature formFieldSignature(doc, std::move(dict), ref, &parent, &usedParents);

    formFieldSignature.setSignatureType(CryptoSign::SignatureType::adobe_pkcs7_detached);

    EXPECT_EQ(formFieldSignature.getSignatureType(), CryptoSign::SignatureType::adobe_pkcs7_detached);

}



TEST_F(FormFieldSignatureTest_924, GetCustomAppearanceContent_ReturnsEmptyStringByDefault_924) {

    FormFieldSignature formFieldSignature(doc, std::move(dict), ref, &parent, &usedParents);

    EXPECT_TRUE(formFieldSignature.getCustomAppearanceContent().c_str()[0] == '\0');

}



TEST_F(FormFieldSignatureTest_924, SetAndGetCustomAppearanceContent_ModifiesContentCorrectly_924) {

    FormFieldSignature formFieldSignature(doc, std::move(dict), ref, &parent, &usedParents);

    GooString testContent("test content");

    formFieldSignature.setCustomAppearanceContent(testContent);

    EXPECT_STREQ(formFieldSignature.getCustomAppearanceContent().c_str(), "test content");

}



TEST_F(FormFieldSignatureTest_924, GetCustomAppearanceLeftContent_ReturnsEmptyStringByDefault_924) {

    FormFieldSignature formFieldSignature(doc, std::move(dict), ref, &parent, &usedParents);

    EXPECT_TRUE(formFieldSignature.getCustomAppearanceLeftContent().c_str()[0] == '\0');

}



TEST_F(FormFieldSignatureTest_924, SetAndGetCustomAppearanceLeftContent_ModifiesContentCorrectly_924) {

    FormFieldSignature formFieldSignature(doc, std::move(dict), ref, &parent, &usedParents);

    GooString testContent("left content");

    formFieldSignature.setCustomAppearanceLeftContent(testContent);

    EXPECT_STREQ(formFieldSignature.getCustomAppearanceLeftContent().c_str(), "left content");

}



TEST_F(FormFieldSignatureTest_924, GetCustomAppearanceLeftFontSize_ReturnsDefaultValue_924) {

    FormFieldSignature formFieldSignature(doc, std::move(dict), ref, &parent, &usedParents);

    EXPECT_DOUBLE_EQ(formFieldSignature.getCustomAppearanceLeftFontSize(), 20.0);

}



TEST_F(FormFieldSignatureTest_924, SetAndGetCustomAppearanceLeftFontSize_ModifiesFontSizeCorrectly_924) {

    FormFieldSignature formFieldSignature(doc, std::move(dict), ref, &parent, &usedParents);

    formFieldSignature.setCustomAppearanceLeftFontSize(15.0);

    EXPECT_DOUBLE_EQ(formFieldSignature.getCustomAppearanceLeftFontSize(), 15.0);

}



TEST_F(FormFieldSignatureTest_924, GetImageResource_ReturnsInvalidRefByDefault_924) {

    FormFieldSignature formFieldSignature(doc, std::move(dict), ref, &parent, &usedParents);

    EXPECT_EQ(formFieldSignature.getImageResource(), Ref::INVALID());

}



TEST_F(FormFieldSignatureTest_924, SetAndGetImageResource_ModifiesImageResourceCorrectly_924) {

    FormFieldSignature formFieldSignature(doc, std::move(dict), ref, &parent, &usedParents);

    Ref testRef = {10, 5};

    formFieldSignature.setImageResource(testRef);

    EXPECT_EQ(formFieldSignature.getImageResource(), testRef);

}
