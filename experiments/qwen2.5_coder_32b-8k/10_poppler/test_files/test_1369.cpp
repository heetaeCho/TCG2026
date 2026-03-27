#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/qt5/src/poppler-form.cc"

#include "./TestProjects/poppler/poppler/SignatureInfo.h"

#include "./TestProjects/poppler/poppler/Form.h"



using namespace Poppler;

using ::testing::NiceMock;

using ::testing::_;



class MockSignatureInfo : public SignatureInfo {

public:

    MOCK_METHOD(SignatureValidationStatus, getSignatureValStatus, (), (const));

    MOCK_METHOD(const std::string, getSignerName, (), (const));

    MOCK_METHOD(const std::string, getSubjectDN, (), (const));

    MOCK_METHOD(const GooString &, getLocation, (), (const));

    MOCK_METHOD(const GooString &, getReason, (), (const));

    MOCK_METHOD(HashAlgorithm, getHashAlgorithm, (), (const));

    MOCK_METHOD(time_t, getSigningTime, (), (const));

    MOCK_METHOD(const X509CertificateInfo *, getCertificateInfo, (), (const));

};



class MockFormWidgetSignature : public FormWidgetSignature {

public:

    MockFormWidgetSignature(PDFDoc *docA, Object *dictObj, unsigned int num, Ref ref, FormField *p)

        : FormWidgetSignature(docA, dictObj, num, ref, p) {}



    MOCK_METHOD(const std::vector<Goffset>, getSignedRangeBounds, (), (const));

    MOCK_METHOD(std::pair<std::optional<std::vector<unsigned char>>, int64_t>, getCheckedSignature, (), (const));

};



class SignatureValidationInfoTest_1369 : public ::testing::Test {

protected:

    NiceMock<MockSignatureInfo> mock_signature_info;

    NiceMock<MockFormWidgetSignature> mock_form_widget_signature{nullptr, nullptr, 0, Ref(), nullptr};

};



TEST_F(SignatureValidationInfoTest_1369, ValidSignatureStatus_1369) {

    EXPECT_CALL(mock_signature_info, getSignatureValStatus()).WillOnce(::testing::Return(SIGNATURE_VALID));

    

    SignatureValidationInfo result = fromInternal(&mock_signature_info, &mock_form_widget_signature);

    EXPECT_EQ(result.signature_status(), SignatureValidationInfo::SignatureValid);

}



TEST_F(SignatureValidationInfoTest_1369, InvalidSignatureStatus_1369) {

    EXPECT_CALL(mock_signature_info, getSignatureValStatus()).WillOnce(::testing::Return(SIGNATURE_INVALID));

    

    SignatureValidationInfo result = fromInternal(&mock_signature_info, &mock_form_widget_signature);

    EXPECT_EQ(result.signature_status(), SignatureValidationInfo::SignatureInvalid);

}



TEST_F(SignatureValidationInfoTest_1369, DigestMismatchSignatureStatus_1369) {

    EXPECT_CALL(mock_signature_info, getSignatureValStatus()).WillOnce(::testing::Return(SIGNATURE_DIGEST_MISMATCH));

    

    SignatureValidationInfo result = fromInternal(&mock_signature_info, &mock_form_widget_signature);

    EXPECT_EQ(result.signature_status(), SignatureValidationInfo::SignatureDigestMismatch);

}



TEST_F(SignatureValidationInfoTest_1369, DecodingErrorSignatureStatus_1369) {

    EXPECT_CALL(mock_signature_info, getSignatureValStatus()).WillOnce(::testing::Return(SIGNATURE_DECODING_ERROR));

    

    SignatureValidationInfo result = fromInternal(&mock_signature_info, &mock_form_widget_signature);

    EXPECT_EQ(result.signature_status(), SignatureValidationInfo::SignatureDecodingError);

}



TEST_F(SignatureValidationInfoTest_1369, GenericErrorSignatureStatus_1369) {

    EXPECT_CALL(mock_signature_info, getSignatureValStatus()).WillOnce(::testing::Return(SIGNATURE_GENERIC_ERROR));

    

    SignatureValidationInfo result = fromInternal(&mock_signature_info, &mock_form_widget_signature);

    EXPECT_EQ(result.signature_status(), SignatureValidationInfo::SignatureGenericError);

}



TEST_F(SignatureValidationInfoTest_1369, NotFoundSignatureStatus_1369) {

    EXPECT_CALL(mock_signature_info, getSignatureValStatus()).WillOnce(::testing::Return(SIGNATURE_NOT_FOUND));

    

    SignatureValidationInfo result = fromInternal(&mock_signature_info, &mock_form_widget_signature);

    EXPECT_EQ(result.signature_status(), SignatureValidationInfo::SignatureNotFound);

}



TEST_F(SignatureValidationInfoTest_1369, NotVerifiedSignatureStatus_1369) {

    EXPECT_CALL(mock_signature_info, getSignatureValStatus()).WillOnce(::testing::Return(SIGNATURE_NOT_VERIFIED));

    

    SignatureValidationInfo result = fromInternal(&mock_signature_info, &mock_form_widget_signature);

    EXPECT_EQ(result.signature_status(), SignatureValidationInfo::SignatureNotVerified);

}



TEST_F(SignatureValidationInfoTest_1369, SignerNameRetrieval_1369) {

    std::string expectedSignerName = "John Doe";

    EXPECT_CALL(mock_signature_info, getSignerName()).WillOnce(::testing::Return(expectedSignerName));

    

    SignatureValidationInfo result = fromInternal(&mock_signature_info, &mock_form_widget_signature);

    EXPECT_EQ(result.signer_name(), QString::fromStdString(expectedSignerName));

}



TEST_F(SignatureValidationInfoTest_1369, SubjectDNRetrieval_1369) {

    std::string expectedSubjectDN = "CN=example.com";

    EXPECT_CALL(mock_signature_info, getSubjectDN()).WillOnce(::testing::Return(expectedSubjectDN));

    

    SignatureValidationInfo result = fromInternal(&mock_signature_info, &mock_form_widget_signature);

    EXPECT_EQ(result.signer_subject_dn(), QString::fromStdString(expectedSubjectDN));

}



TEST_F(SignatureValidationInfoTest_1369, LocationRetrieval_1369) {

    GooString expectedLocation("New York");

    EXPECT_CALL(mock_signature_info, getLocation()).WillOnce(::testing::ReturnRef(expectedLocation));

    

    SignatureValidationInfo result = fromInternal(&mock_signature_info, &mock_form_widget_signature);

    EXPECT_EQ(result.location().toStr(), "New York");

}



TEST_F(SignatureValidationInfoTest_1369, ReasonRetrieval_1369) {

    GooString expectedReason("Contract Signing");

    EXPECT_CALL(mock_signature_info, getReason()).WillOnce(::testing::ReturnRef(expectedReason));

    

    SignatureValidationInfo result = fromInternal(&mock_signature_info, &mock_form_widget_signature);

    EXPECT_EQ(result.reason().toStr(), "Contract Signing");

}



TEST_F(SignatureValidationInfoTest_1369, HashAlgorithmRetrieval_1369) {

    HashAlgorithm expectedHashAlgorithm = HashAlgorithm::SHA256;

    EXPECT_CALL(mock_signature_info, getHashAlgorithm()).WillOnce(::testing::Return(expectedHashAlgorithm));

    

    SignatureValidationInfo result = fromInternal(&mock_signature_info, &mock_form_widget_signature);

    EXPECT_EQ(result.hash_algorithm(), expectedHashAlgorithm);

}



TEST_F(SignatureValidationInfoTest_1369, SigningTimeRetrieval_1369) {

    time_t expectedSigningTime = 1633072800;

    EXPECT_CALL(mock_signature_info, getSigningTime()).WillOnce(::testing::Return(expectedSigningTime));

    

    SignatureValidationInfo result = fromInternal(&mock_signature_info, &mock_form_widget_signature);

    EXPECT_EQ(result.signing_time(), expectedSigningTime);

}



TEST_F(SignatureValidationInfoTest_1369, RangeBoundsRetrieval_1369) {

    std::vector<Goffset> expectedRanges = {0, 1024, 2048, 3072};

    EXPECT_CALL(mock_form_widget_signature, getSignedRangeBounds()).WillOnce(::testing::Return(expectedRanges));

    

    SignatureValidationInfo result = fromInternal(&mock_signature_info, &mock_form_widget_signature);

    EXPECT_EQ(result.range_bounds(), expectedRanges);

}



TEST_F(SignatureValidationInfoTest_1369, CheckedSignatureRetrieval_1369) {

    std::vector<unsigned char> signatureData = {0x30, 0x82, 0x04, 0x7f};

    EXPECT_CALL(mock_form_widget_signature, getCheckedSignature()).WillOnce(::testing::Return(std::make_pair(std::optional<std::vector<unsigned char>>(signatureData), 4096)));

    

    SignatureValidationInfo result = fromInternal(&mock_signature_info, &mock_form_widget_signature);

    EXPECT_EQ(result.signature().toVector(), signatureData);

}



TEST_F(SignatureValidationInfoTest_1369, EmptyRangeBounds_1369) {

    std::vector<Goffset> emptyRanges;

    EXPECT_CALL(mock_form_widget_signature, getSignedRangeBounds()).WillOnce(::testing::Return(emptyRanges));

    

    SignatureValidationInfo result = fromInternal(&mock_signature_info, &mock_form_widget_signature);

    EXPECT_TRUE(result.range_bounds().empty());

}



TEST_F(SignatureValidationInfoTest_1369, NoCheckedSignature_1369) {

    EXPECT_CALL(mock_form_widget_signature, getCheckedSignature()).WillOnce(::testing::Return(std::make_pair(std::optional<std::vector<unsigned char>>(), 4096)));

    

    SignatureValidationInfo result = fromInternal(&mock_signature_info, &mock_form_widget_signature);

    EXPECT_TRUE(result.signature().isEmpty());

}
