#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/Form.h"

#include <vector>



using namespace testing;



class FormFieldSignatureTest_925 : public ::testing::Test {

protected:

    PDFDoc* doc;

    Object dict;

    Ref ref;

    FormField* parent;

    std::set<int>* usedParents;

    FormFieldSignature* formFieldSignature;



    void SetUp() override {

        doc = new PDFDoc();

        parent = nullptr;

        usedParents = new std::set<int>();

        formFieldSignature = new FormFieldSignature(doc, std::move(dict), ref, parent, usedParents);

    }



    void TearDown() override {

        delete formFieldSignature;

        delete usedParents;

        delete doc;

    }

};



TEST_F(FormFieldSignatureTest_925, GetSignature_ReturnsEmptyVector_925) {

    const auto& signature = formFieldSignature->getSignature();

    EXPECT_TRUE(signature.empty());

}



TEST_F(FormFieldSignatureTest_925, SetSignatureAndGetSignature_NormalOperation_925) {

    std::vector<unsigned char> testSignature = {0x1A, 0x2B, 0x3C};

    formFieldSignature->setSignature(std::move(testSignature));

    const auto& retrievedSignature = formFieldSignature->getSignature();

    EXPECT_EQ(retrievedSignature, std::vector<unsigned char>({0x1A, 0x2B, 0x3C}));

}



TEST_F(FormFieldSignatureTest_925, SetSignatureAndGetSignature_BoundaryCondition_EmptyVector_925) {

    std::vector<unsigned char> testSignature = {};

    formFieldSignature->setSignature(std::move(testSignature));

    const auto& retrievedSignature = formFieldSignature->getSignature();

    EXPECT_TRUE(retrievedSignature.empty());

}



TEST_F(FormFieldSignatureTest_925, SetSignatureAndGetSignature_BoundaryCondition_SingleElement_925) {

    std::vector<unsigned char> testSignature = {0x1A};

    formFieldSignature->setSignature(std::move(testSignature));

    const auto& retrievedSignature = formFieldSignature->getSignature();

    EXPECT_EQ(retrievedSignature, std::vector<unsigned char>({0x1A}));

}



TEST_F(FormFieldSignatureTest_925, SetSignatureAndGetSignature_BoundaryCondition_LargeVector_925) {

    std::vector<unsigned char> testSignature(1024, 0xFF);

    formFieldSignature->setSignature(std::move(testSignature));

    const auto& retrievedSignature = formFieldSignature->getSignature();

    EXPECT_EQ(retrievedSignature.size(), 1024);

    for (const auto& byte : retrievedSignature) {

        EXPECT_EQ(byte, 0xFF);

    }

}



TEST_F(FormFieldSignatureTest_925, GetSignatureType_ReturnsDefaultSignatureType_925) {

    CryptoSign::SignatureType signatureType = formFieldSignature->getSignatureType();

    EXPECT_EQ(signatureType, CryptoSign::SignatureType::unsigned_signature_field);

}
