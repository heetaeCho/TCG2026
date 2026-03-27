#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-form-field.cc"

#include "Form.h"

#include "SignatureInfo.h"



using namespace testing;



// Mocking external collaborators (if needed)

class MockFormField : public FormField {

public:

    MOCK_METHOD(FormFieldType, getFieldType, (), (const));

    MOCK_METHOD(FormWidget*, getField, (), (const));

};



class MockFormFieldSignature : public FormFieldSignature {

public:

    MOCK_METHOD(SignatureInfo*, validateSignatureAsync, 

                (bool doVerifyCert, bool forceRevalidation, time_t validationTime, 

                 bool ocspRevocationCheck, bool enableAIA, const std::function<void(void)>& doneCallback), (override));

    MOCK_METHOD(CertificateValidationStatus, validateSignatureResult, (), (override));

};



class MockX509CertificateInfo : public X509CertificateInfo {

public:

    MOCK_CONST_METHOD0(getSubjectInfo, const EntityInfo&());

    MOCK_CONST_METHOD0(getIssuerInfo, const EntityInfo&());

    MOCK_CONST_METHOD0(getValidity, const Validity&());

};



// Test Fixture

class PopplerFormFieldSignatureValidateTest_2321 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize necessary objects and mocks here

        mock_field = std::make_unique<MockFormField>();

        mock_sig_field = std::make_unique<MockFormFieldSignature>();

        mock_cert_info = std::make_unique<MockX509CertificateInfo>();



        field.widget = mock_field.get();

        sig_info->setSignatureValStatus(SIGNATURE_VALID);

        sig_info->setSignerName("Test Signer");

        sig_info->setSigningTime(1672534800); // Example signing time

        sig_info->setCertificateInfo(std::move(mock_cert_info));



        EXPECT_CALL(*mock_field, getFieldType())

            .WillRepeatedly(Return(POPPLER_FORM_FIELD_SIGNATURE));

        EXPECT_CALL(*mock_field, getField())

            .WillRepeatedly(Return(mock_sig_field.get()));



        EXPECT_CALL(*mock_sig_field, validateSignatureAsync(_, _, _, _, _, _))

            .WillRepeatedly(Return(sig_info));



        EXPECT_CALL(*mock_sig_field, validateSignatureResult())

            .WillRepeatedly(Return(CERTIFICATE_TRUSTED));

    }



    PopplerFormField field;

    std::unique_ptr<MockFormField> mock_field;

    std::unique_ptr<MockFormFieldSignature> mock_sig_field;

    SignatureInfo* sig_info = new SignatureInfo();

    std::unique_ptr<MockX509CertificateInfo> mock_cert_info;

};



// Normal Operation Tests

TEST_F(PopplerFormFieldSignatureValidateTest_2321, ValidateSignature_ReturnsValidInfo_2321) {

    GError *error = nullptr;

    PopplerSignatureInfo* result = _poppler_form_field_signature_validate(&field, POPPLER_SIGNATURE_VALIDATION_FLAG_VALIDATE_CERTIFICATE, FALSE, &error);

    ASSERT_NE(result, nullptr);

    EXPECT_EQ(result->sig_status, POPPLER_SIGNATURE_VALID);

    EXPECT_STREQ(result->signer_name, "Test Signer");

    g_clear_error(&error);

}



// Boundary Condition Tests

TEST_F(PopplerFormFieldSignatureValidateTest_2321, ValidateSignature_NoFlags_ReturnsValidInfo_2321) {

    GError *error = nullptr;

    PopplerSignatureInfo* result = _poppler_form_field_signature_validate(&field, 0, FALSE, &error);

    ASSERT_NE(result, nullptr);

    EXPECT_EQ(result->sig_status, POPPLER_SIGNATURE_VALID);

    g_clear_error(&error);

}



// Exceptional/Error Case Tests

TEST_F(PopplerFormFieldSignatureValidateTest_2321, ValidateSignature_WrongFieldType_ReturnsNullAndError_2321) {

    EXPECT_CALL(*mock_field, getFieldType())

        .WillOnce(Return(POPPLER_FORM_FIELD_BUTTON));



    GError *error = nullptr;

    PopplerSignatureInfo* result = _poppler_form_field_signature_validate(&field, POPPLER_SIGNATURE_VALIDATION_FLAG_VALIDATE_CERTIFICATE, FALSE, &error);

    EXPECT_EQ(result, nullptr);

    ASSERT_NE(error, nullptr);

    EXPECT_STREQ(error->message, "Wrong FormField type");

    g_clear_error(&error);

}
