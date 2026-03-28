#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <glib.h>

// Include necessary headers
#include "poppler-form-field.h"
#include "poppler-private.h"
#include "poppler-form-field.cc" // For access to static function and internal structs
#include "Form.h"
#include "SignatureInfo.h"
#include "CertificateInfo.h"

using ::testing::Return;
using ::testing::ReturnRef;
using ::testing::_;
using ::testing::NiceMock;

// Mock FormWidget to control getField() and type
class MockFormWidget : public FormWidget {
public:
    MockFormWidget() : FormWidget(nullptr, nullptr, 0, Ref::INVALID(), nullptr) {}
    MOCK_METHOD(FormField*, getField, ());
    MOCK_METHOD(FormFieldType, getType, ());
};

// Mock FormFieldSignature
class MockFormFieldSignature : public FormFieldSignature {
public:
    MockFormFieldSignature() : FormFieldSignature(nullptr, Object(), Ref::INVALID(), nullptr, (std::set<int>*)nullptr) {}
    MOCK_METHOD(SignatureInfo*, validateSignatureAsync, (bool, bool, time_t, bool, bool, const std::function<void(void)>&));
    MOCK_METHOD(CertificateValidationStatus, validateSignatureResult, ());
};

// Helper to create a PopplerFormField with specific type behavior
class PopplerFormFieldSignatureValidateTest_2321 : public ::testing::Test {
protected:
    void SetUp() override {
        error = nullptr;
    }

    void TearDown() override {
        if (error) {
            g_error_free(error);
            error = nullptr;
        }
    }

    GError *error;
};

// Test: Wrong field type returns nullptr and sets error
TEST_F(PopplerFormFieldSignatureValidateTest_2321, WrongFieldTypeReturnsNull_2321) {
    // Create a PopplerFormField that is NOT a signature field
    // We need poppler_form_field_get_field_type to return something != POPPLER_FORM_FIELD_SIGNATURE
    PopplerFormField *field = g_new0(PopplerFormField, 1);
    
    // Set up widget with a non-signature type
    // Since poppler_form_field_get_field_type checks field->widget->getType(),
    // we need a widget that returns a non-signature type
    MockFormWidget *mockWidget = new MockFormWidget();
    ON_CALL(*mockWidget, getType()).WillByDefault(Return(formText));
    field->widget = mockWidget;

    PopplerSignatureInfo *result = _poppler_form_field_signature_validate(
        field,
        POPPLER_SIGNATURE_VALIDATION_FLAG_VALIDATE_CERTIFICATE,
        FALSE,
        &error);

    EXPECT_EQ(result, nullptr);
    EXPECT_NE(error, nullptr);
    if (error) {
        EXPECT_EQ(error->domain, POPPLER_ERROR);
        EXPECT_EQ(error->code, POPPLER_ERROR_INVALID);
        EXPECT_STREQ(error->message, "Wrong FormField type");
    }

    delete mockWidget;
    g_free(field);
}

// Test: Valid signature field with SIGNATURE_VALID and CERTIFICATE_TRUSTED
TEST_F(PopplerFormFieldSignatureValidateTest_2321, ValidSignatureReturnsSigInfo_2321) {
    PopplerFormField *field = g_new0(PopplerFormField, 1);
    
    MockFormFieldSignature *mockSigField = new MockFormFieldSignature();
    MockFormWidget *mockWidget = new MockFormWidget();
    
    ON_CALL(*mockWidget, getType()).WillByDefault(Return(formSignature));
    ON_CALL(*mockWidget, getField()).WillByDefault(Return(mockSigField));
    field->widget = mockWidget;

    SignatureInfo sigInfo;
    sigInfo.setSignatureValStatus(SIGNATURE_VALID);
    sigInfo.setSignerName("Test Signer");
    sigInfo.setSigningTime(1609459200); // 2021-01-01 00:00:00 UTC

    ON_CALL(*mockSigField, validateSignatureAsync(_, _, _, _, _, _))
        .WillByDefault(Return(&sigInfo));
    ON_CALL(*mockSigField, validateSignatureResult())
        .WillByDefault(Return(CERTIFICATE_TRUSTED));

    PopplerSignatureInfo *result = _poppler_form_field_signature_validate(
        field,
        POPPLER_SIGNATURE_VALIDATION_FLAG_VALIDATE_CERTIFICATE,
        FALSE,
        &error);

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(error, nullptr);
    EXPECT_EQ(result->sig_status, POPPLER_SIGNATURE_VALID);
    EXPECT_EQ(result->cert_status, POPPLER_CERTIFICATE_TRUSTED);
    EXPECT_STREQ(result->signer_name, "Test Signer");
    EXPECT_NE(result->local_signing_time, nullptr);

    poppler_signature_info_free(result);
    delete mockSigField;
    delete mockWidget;
    g_free(field);
}

// Test: Signature status SIGNATURE_INVALID maps correctly
TEST_F(PopplerFormFieldSignatureValidateTest_2321, SignatureInvalidStatusMapping_2321) {
    PopplerFormField *field = g_new0(PopplerFormField, 1);
    MockFormFieldSignature *mockSigField = new MockFormFieldSignature();
    MockFormWidget *mockWidget = new MockFormWidget();

    ON_CALL(*mockWidget, getType()).WillByDefault(Return(formSignature));
    ON_CALL(*mockWidget, getField()).WillByDefault(Return(mockSigField));
    field->widget = mockWidget;

    SignatureInfo sigInfo;
    sigInfo.setSignatureValStatus(SIGNATURE_INVALID);
    sigInfo.setSignerName("");
    sigInfo.setSigningTime(0);

    ON_CALL(*mockSigField, validateSignatureAsync(_, _, _, _, _, _))
        .WillByDefault(Return(&sigInfo));
    ON_CALL(*mockSigField, validateSignatureResult())
        .WillByDefault(Return(CERTIFICATE_UNTRUSTED_ISSUER));

    PopplerSignatureInfo *result = _poppler_form_field_signature_validate(
        field,
        static_cast<PopplerSignatureValidationFlags>(0),
        FALSE,
        &error);

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->sig_status, POPPLER_SIGNATURE_INVALID);
    EXPECT_EQ(result->cert_status, POPPLER_CERTIFICATE_UNTRUSTED_ISSUER);

    poppler_signature_info_free(result);
    delete mockSigField;
    delete mockWidget;
    g_free(field);
}

// Test: SIGNATURE_DIGEST_MISMATCH maps correctly
TEST_F(PopplerFormFieldSignatureValidateTest_2321, DigestMismatchStatusMapping_2321) {
    PopplerFormField *field = g_new0(PopplerFormField, 1);
    MockFormFieldSignature *mockSigField = new MockFormFieldSignature();
    MockFormWidget *mockWidget = new MockFormWidget();

    ON_CALL(*mockWidget, getType()).WillByDefault(Return(formSignature));
    ON_CALL(*mockWidget, getField()).WillByDefault(Return(mockSigField));
    field->widget = mockWidget;

    SignatureInfo sigInfo;
    sigInfo.setSignatureValStatus(SIGNATURE_DIGEST_MISMATCH);
    sigInfo.setSignerName("Digest User");
    sigInfo.setSigningTime(0);

    ON_CALL(*mockSigField, validateSignatureAsync(_, _, _, _, _, _))
        .WillByDefault(Return(&sigInfo));
    ON_CALL(*mockSigField, validateSignatureResult())
        .WillByDefault(Return(CERTIFICATE_UNKNOWN_ISSUER));

    PopplerSignatureInfo *result = _poppler_form_field_signature_validate(
        field,
        static_cast<PopplerSignatureValidationFlags>(0),
        FALSE,
        &error);

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->sig_status, POPPLER_SIGNATURE_DIGEST_MISMATCH);
    EXPECT_EQ(result->cert_status, POPPLER_CERTIFICATE_UNKNOWN_ISSUER);

    poppler_signature_info_free(result);
    delete mockSigField;
    delete mockWidget;
    g_free(field);
}

// Test: SIGNATURE_DECODING_ERROR and CERTIFICATE_REVOKED
TEST_F(PopplerFormFieldSignatureValidateTest_2321, DecodingErrorAndRevokedCert_2321) {
    PopplerFormField *field = g_new0(PopplerFormField, 1);
    MockFormFieldSignature *mockSigField = new MockFormFieldSignature();
    MockFormWidget *mockWidget = new MockFormWidget();

    ON_CALL(*mockWidget, getType()).WillByDefault(Return(formSignature));
    ON_CALL(*mockWidget, getField()).WillByDefault(Return(mockSigField));
    field->widget = mockWidget;

    SignatureInfo sigInfo;
    sigInfo.setSignatureValStatus(SIGNATURE_DECODING_ERROR);
    sigInfo.setSignerName("");
    sigInfo.setSigningTime(0);

    ON_CALL(*mockSigField, validateSignatureAsync(_, _, _, _, _, _))
        .WillByDefault(Return(&sigInfo));
    ON_CALL(*mockSigField, validateSignatureResult())
        .WillByDefault(Return(CERTIFICATE_REVOKED));

    PopplerSignatureInfo *result = _poppler_form_field_signature_validate(
        field,
        static_cast<PopplerSignatureValidationFlags>(0),
        FALSE,
        &error);

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->sig_status, POPPLER_SIGNATURE_DECODING_ERROR);
    EXPECT_EQ(result->cert_status, POPPLER_CERTIFICATE_REVOKED);

    poppler_signature_info_free(result);
    delete mockSigField;
    delete mockWidget;
    g_free(field);
}

// Test: SIGNATURE_GENERIC_ERROR and CERTIFICATE_EXPIRED
TEST_F(PopplerFormFieldSignatureValidateTest_2321, GenericErrorAndExpiredCert_2321) {
    PopplerFormField *field = g_new0(PopplerFormField, 1);
    MockFormFieldSignature *mockSigField = new MockFormFieldSignature();
    MockFormWidget *mockWidget = new MockFormWidget();

    ON_CALL(*mockWidget, getType()).WillByDefault(Return(formSignature));
    ON_CALL(*mockWidget, getField()).WillByDefault(Return(mockSigField));
    field->widget = mockWidget;

    SignatureInfo sigInfo;
    sigInfo.setSignatureValStatus(SIGNATURE_GENERIC_ERROR);
    sigInfo.setSignerName("");
    sigInfo.setSigningTime(0);

    ON_CALL(*mockSigField, validateSignatureAsync(_, _, _, _, _, _))
        .WillByDefault(Return(&sigInfo));
    ON_CALL(*mockSigField, validateSignatureResult())
        .WillByDefault(Return(CERTIFICATE_EXPIRED));

    PopplerSignatureInfo *result = _poppler_form_field_signature_validate(
        field,
        static_cast<PopplerSignatureValidationFlags>(0),
        FALSE,
        &error);

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->sig_status, POPPLER_SIGNATURE_GENERIC_ERROR);
    EXPECT_EQ(result->cert_status, POPPLER_CERTIFICATE_EXPIRED);

    poppler_signature_info_free(result);
    delete mockSigField;
    delete mockWidget;
    g_free(field);
}

// Test: SIGNATURE_NOT_FOUND and CERTIFICATE_GENERIC_ERROR
TEST_F(PopplerFormFieldSignatureValidateTest_2321, NotFoundAndCertGenericError_2321) {
    PopplerFormField *field = g_new0(PopplerFormField, 1);
    MockFormFieldSignature *mockSigField = new MockFormFieldSignature();
    MockFormWidget *mockWidget = new MockFormWidget();

    ON_CALL(*mockWidget, getType()).WillByDefault(Return(formSignature));
    ON_CALL(*mockWidget, getField()).WillByDefault(Return(mockSigField));
    field->widget = mockWidget;

    SignatureInfo sigInfo;
    sigInfo.setSignatureValStatus(SIGNATURE_NOT_FOUND);
    sigInfo.setSignerName("");
    sigInfo.setSigningTime(0);

    ON_CALL(*mockSigField, validateSignatureAsync(_, _, _, _, _, _))
        .WillByDefault(Return(&sigInfo));
    ON_CALL(*mockSigField, validateSignatureResult())
        .WillByDefault(Return(CERTIFICATE_GENERIC_ERROR));

    PopplerSignatureInfo *result = _poppler_form_field_signature_validate(
        field,
        static_cast<PopplerSignatureValidationFlags>(0),
        FALSE,
        &error);

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->sig_status, POPPLER_SIGNATURE_NOT_FOUND);
    EXPECT_EQ(result->cert_status, POPPLER_CERTIFICATE_GENERIC_ERROR);

    poppler_signature_info_free(result);
    delete mockSigField;
    delete mockWidget;
    g_free(field);
}

// Test: SIGNATURE_NOT_VERIFIED and CERTIFICATE_NOT_VERIFIED
TEST_F(PopplerFormFieldSignatureValidateTest_2321, NotVerifiedBoth_2321) {
    PopplerFormField *field = g_new0(PopplerFormField, 1);
    MockFormFieldSignature *mockSigField = new MockFormFieldSignature();
    MockFormWidget *mockWidget = new MockFormWidget();

    ON_CALL(*mockWidget, getType()).WillByDefault(Return(formSignature));
    ON_CALL(*mockWidget, getField()).WillByDefault(Return(mockSigField));
    field->widget = mockWidget;

    SignatureInfo sigInfo;
    sigInfo.setSignatureValStatus(SIGNATURE_NOT_VERIFIED);
    sigInfo.setSignerName("");
    sigInfo.setSigningTime(0);

    ON_CALL(*mockSigField, validateSignatureAsync(_, _, _, _, _, _))
        .WillByDefault(Return(&sigInfo));
    ON_CALL(*mockSigField, validateSignatureResult())
        .WillByDefault(Return(CERTIFICATE_NOT_VERIFIED));

    PopplerSignatureInfo *result = _poppler_form_field_signature_validate(
        field,
        static_cast<PopplerSignatureValidationFlags>(0),
        FALSE,
        &error);

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->sig_status, POPPLER_SIGNATURE_NOT_VERIFIED);
    EXPECT_EQ(result->cert_status, POPPLER_CERTIFICATE_NOT_VERIFIED);

    poppler_signature_info_free(result);
    delete mockSigField;
    delete mockWidget;
    g_free(field);
}

// Test: Certificate info is populated when available
TEST_F(PopplerFormFieldSignatureValidateTest_2321, CertificateInfoPopulated_2321) {
    PopplerFormField *field = g_new0(PopplerFormField, 1);
    MockFormFieldSignature *mockSigField = new MockFormFieldSignature();
    MockFormWidget *mockWidget = new MockFormWidget();

    ON_CALL(*mockWidget, getType()).WillByDefault(Return(formSignature));
    ON_CALL(*mockWidget, getField()).WillByDefault(Return(mockSigField));
    field->widget = mockWidget;

    auto certInfo = std::make_unique<X509CertificateInfo>();
    X509CertificateInfo::EntityInfo subjectInfo;
    subjectInfo.commonName = "Test Subject CN";
    subjectInfo.organization = "Test Subject Org";
    subjectInfo.email = "subject@test.com";
    certInfo->setSubjectInfo(std::move(subjectInfo));

    X509CertificateInfo::EntityInfo issuerInfo;
    issuerInfo.commonName = "Test Issuer CN";
    issuerInfo.organization = "Test Issuer Org";
    issuerInfo.email = "issuer@test.com";
    certInfo->setIssuerInfo(std::move(issuerInfo));

    X509CertificateInfo::Validity validity;
    validity.notBefore = 1609459200; // 2021-01-01
    validity.notAfter = 1640995200;  // 2022-01-01
    certInfo->setValidity(validity);

    SignatureInfo sigInfo;
    sigInfo.setSignatureValStatus(SIGNATURE_VALID);
    sigInfo.setSignerName("Cert Signer");
    sigInfo.setSigningTime(1609459200);
    sigInfo.setCertificateInfo(std::move(certInfo));

    ON_CALL(*mockSigField, validateSignatureAsync(_, _, _, _, _, _))
        .WillByDefault(Return(&sigInfo));
    ON_CALL(*mockSigField, validateSignatureResult())
        .WillByDefault(Return(CERTIFICATE_TRUSTED));

    PopplerSignatureInfo *result = _poppler_form_field_signature_validate(
        field,
        POPPLER_SIGNATURE_VALIDATION_FLAG_VALIDATE_CERTIFICATE,
        FALSE,
        &error);

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(error, nullptr);
    ASSERT_NE(result->certificate_info, nullptr);
    EXPECT_STREQ(result->certificate_info->subject_common_name, "Test Subject CN");
    EXPECT_STREQ(result->certificate_info->subject_organization, "Test Subject Org");
    EXPECT_STREQ(result->certificate_info->subject_email, "subject@test.com");
    EXPECT_STREQ(result->certificate_info->issuer_common_name, "Test Issuer CN");
    EXPECT_STREQ(result->certificate_info->issuer_organization, "Test Issuer Org");
    EXPECT_STREQ(result->certificate_info->issuer_email, "issuer@test.com");
    EXPECT_NE(result->certificate_info->issued, nullptr);
    EXPECT_NE(result->certificate_info->expires, nullptr);

    poppler_signature_info_free(result);
    delete mockSigField;
    delete mockWidget;
    g_free(field);
}

// Test: No certificate info when getCertificateInfo returns nullptr
TEST_F(PopplerFormFieldSignatureValidateTest_2321, NoCertificateInfo_2321) {
    PopplerFormField *field = g_new0(PopplerFormField, 1);
    MockFormFieldSignature *mockSigField = new MockFormFieldSignature();
    MockFormWidget *mockWidget = new MockFormWidget();

    ON_CALL(*mockWidget, getType()).WillByDefault(Return(formSignature));
    ON_CALL(*mockWidget, getField()).WillByDefault(Return(mockSigField));
    field->widget = mockWidget;

    SignatureInfo sigInfo;
    sigInfo.setSignatureValStatus(SIGNATURE_VALID);
    sigInfo.setSignerName("No Cert Signer");
    sigInfo.setSigningTime(1609459200);
    // No certificate info set - getCertificateInfo() returns nullptr

    ON_CALL(*mockSigField, validateSignatureAsync(_, _, _, _, _, _))
        .WillByDefault(Return(&sigInfo));
    ON_CALL(*mockSigField, validateSignatureResult())
        .WillByDefault(Return(CERTIFICATE_TRUSTED));

    PopplerSignatureInfo *result = _poppler_form_field_signature_validate(
        field,
        static_cast<PopplerSignatureValidationFlags>(0),
        FALSE,
        &error);

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->certificate_info, nullptr);

    poppler_signature_info_free(result);
    delete mockSigField;
    delete mockWidget;
    g_free(field);
}

// Test: Flags are passed correctly - VALIDATE_CERTIFICATE flag
TEST_F(PopplerFormFieldSignatureValidateTest_2321, ValidateCertificateFlagPassed_2321) {
    PopplerFormField *field = g_new0(PopplerFormField, 1);
    MockFormFieldSignature *mockSigField = new MockFormFieldSignature();
    MockFormWidget *mockWidget = new MockFormWidget();

    ON_CALL(*mockWidget, getType()).WillByDefault(Return(formSignature));
    ON_CALL(*mockWidget, getField()).WillByDefault(Return(mockSigField));
    field->widget = mockWidget;

    SignatureInfo sigInfo;
    sigInfo.setSignatureValStatus(SIGNATURE_VALID);
    sigInfo.setSignerName("Flag Tester");
    sigInfo.setSigningTime(0);

    // Expect validateSignatureAsync called with doVerifyCert=true (flag set),
    // ocspRevocationCheck=true (WITHOUT flag NOT set), enableAIA=false (flag not set)
    EXPECT_CALL(*mockSigField, validateSignatureAsync(
        true,   // VALIDATE_CERTIFICATE flag is set
        false,  // force_revalidation
        -1,     // validationTime
        true,   // ocsp check (WITHOUT flag not set, so !(0) = true)
        false,  // AIA not set
        _))
        .WillOnce(Return(&sigInfo));
    ON_CALL(*mockSigField, validateSignatureResult())
        .WillByDefault(Return(CERTIFICATE_TRUSTED));

    PopplerSignatureInfo *result = _poppler_form_field_signature_validate(
        field,
        POPPLER_SIGNATURE_VALIDATION_FLAG_VALIDATE_CERTIFICATE,
        FALSE,
        &error);

    ASSERT_NE(result, nullptr);

    poppler_signature_info_free(result);
    delete mockSigField;
    delete mockWidget;
    g_free(field);
}

// Test: Force revalidation flag
TEST_F(PopplerFormFieldSignatureValidateTest_2321, ForceRevalidation_2321) {
    PopplerFormField *field = g_new0(PopplerFormField, 1);
    MockFormFieldSignature *mockSigField = new MockFormFieldSignature();
    MockFormWidget *mockWidget = new MockFormWidget();

    ON_CALL(*mockWidget, getType()).WillByDefault(Return(formSignature));
    ON_CALL(*mockWidget, getField()).WillByDefault(Return(mockSigField));
    field->widget = mockWidget;

    SignatureInfo sigInfo;
    sigInfo.setSignatureValStatus(SIGNATURE_VALID);
    sigInfo.setSignerName("Revalidation Tester");
    sigInfo.setSigningTime(0);

    EXPECT_CALL(*mockSigField, validateSignatureAsync(
        false,  // no VALIDATE_CERTIFICATE flag
        true,   // force_revalidation = TRUE
        -1,
        true,   // ocsp check
        false,  // no AIA
        _))
        .WillOnce(Return(&sigInfo));
    ON_CALL(*mockSigField, validateSignatureResult())
        .WillByDefault(Return(CERTIFICATE_TRUSTED));

    PopplerSignatureInfo *result = _poppler_form_field_signature_validate(
        field,
        static_cast<PopplerSignatureValidationFlags>(0),
        TRUE,
        &error);

    ASSERT_NE(result, nullptr);

    poppler_signature_info_free(result);
    delete mockSigField;
    delete mockWidget;
    g_free(field);
}

// Test: All flags set
TEST_F(PopplerFormFieldSignatureValidateTest_2321, AllFlagsSet_2321) {
    PopplerFormField *field = g_new0(PopplerFormField, 1);
    MockFormFieldSignature *mockSigField = new MockFormFieldSignature();
    MockFormWidget *mockWidget = new MockFormWidget();

    ON_CALL(*mockWidget, getType()).WillByDefault(Return(formSignature));
    ON_CALL(*mockWidget, getField()).WillByDefault(Return(mockSigField));
    field->widget = mockWidget;

    SignatureInfo sigInfo;
    sigInfo.setSignatureValStatus(SIGNATURE_VALID);
    sigInfo.setSignerName("All Flags");
    sigInfo.setSigningTime(0);

    PopplerSignatureValidationFlags allFlags = static_cast<PopplerSignatureValidationFlags>(
        POPPLER_SIGNATURE_VALIDATION_FLAG_VALIDATE_CERTIFICATE |
        POPPLER_SIGNATURE_VALIDATION_FLAG_WITHOUT_OCSP_REVOCATION_CHECK |
        POPPLER_SIGNATURE_VALIDATION_FLAG_USE_AIA_CERTIFICATE_FETCH);

    EXPECT_CALL(*mockSigField, validateSignatureAsync(
        true,   // VALIDATE_CERTIFICATE set
        true,   // force_revalidation
        -1,
        false,  // WITHOUT_OCSP set, so !(flag) = false
        true,   // USE_AIA set
        _))
        .WillOnce(Return(&sigInfo));
    ON_CALL(*mockSigField, validateSignatureResult())
        .WillByDefault(Return(CERTIFICATE_TRUSTED));

    PopplerSignatureInfo *result = _poppler_form_field_signature_validate(
        field,
        allFlags,
        TRUE,
        &error);

    ASSERT_NE(result, nullptr);

    poppler_signature_info_free(result);
    delete mockSigField;
    delete mockWidget;
    g_free(field);
}

// Test: Empty signer name
TEST_F(PopplerFormFieldSignatureValidateTest_2321, EmptySignerName_2321) {
    PopplerFormField *field = g_new0(PopplerFormField, 1);
    MockFormFieldSignature *mockSigField = new MockFormFieldSignature();
    MockFormWidget *mockWidget = new MockFormWidget();

    ON_CALL(*mockWidget, getType()).WillByDefault(Return(formSignature));
    ON_CALL(*mockWidget, getField()).WillByDefault(Return(mockSigField));
    field->widget = mockWidget;

    SignatureInfo sigInfo;
    sigInfo.setSignatureValStatus(SIGNATURE_VALID);
    sigInfo.setSignerName("");
    sigInfo.setSigningTime(0);

    ON_CALL(*mockSigField, validateSignatureAsync(_, _, _, _, _, _))
        .WillByDefault(Return(&sigInfo));
    ON_CALL(*mockSigField, validateSignatureResult())
        .WillByDefault(Return(CERTIFICATE_TRUSTED));

    PopplerSignatureInfo *result = _poppler_form_field_signature_validate(
        field,
        static_cast<PopplerSignatureValidationFlags>(0),
        FALSE,
        &error);

    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->signer_name, "");

    poppler_signature_info_free(result);
    delete mockSigField;
    delete mockWidget;
    g_free(field);
}

// Test: Null error parameter for wrong field type
TEST_F(PopplerFormFieldSignatureValidateTest_2321, WrongFieldTypeNullError_2321) {
    PopplerFormField *field = g_new0(PopplerFormField, 1);
    MockFormWidget *mockWidget = new MockFormWidget();
    ON_CALL(*mockWidget, getType()).WillByDefault(Return(formText));
    field->widget = mockWidget;

    PopplerSignatureInfo *result = _poppler_form_field_signature_validate(
        field,
        POPPLER_SIGNATURE_VALIDATION_FLAG_VALIDATE_CERTIFICATE,
        FALSE,
        nullptr);

    EXPECT_EQ(result, nullptr);

    delete mockWidget;
    g_free(field);
}

// Test: Button field type returns null
TEST_F(PopplerFormFieldSignatureValidateTest_2321, ButtonFieldTypeReturnsNull_2321) {
    PopplerFormField *field = g_new0(PopplerFormField, 1);
    MockFormWidget *mockWidget = new MockFormWidget();
    ON_CALL(*mockWidget, getType()).WillByDefault(Return(formButton));
    field->widget = mockWidget;

    PopplerSignatureInfo *result = _poppler_form_field_signature_validate(
        field,
        static_cast<PopplerSignatureValidationFlags>(0),
        FALSE,
        &error);

    EXPECT_EQ(result, nullptr);
    EXPECT_NE(error, nullptr);

    delete mockWidget;
    g_free(field);
}
