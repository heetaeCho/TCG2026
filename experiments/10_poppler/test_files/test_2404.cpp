#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-form-field.cc"

#include "CertificateInfo.h"



// Mock class for X509CertificateInfo

class MockX509CertificateInfo : public X509CertificateInfo {

public:

    MOCK_CONST_METHOD0(getNickName, const GooString&());

    MOCK_CONST_METHOD0(getSubjectInfo, const EntityInfo&());

    MOCK_CONST_METHOD0(getIssuerInfo, const EntityInfo&());

    MOCK_CONST_METHOD0(getValidity, const Validity&());

};



class PopplerCertificateInfoTest : public ::testing::Test {

protected:

    MockX509CertificateInfo mockCertInfo;

    GooString nickName = "testNick";

    X509CertificateInfo::EntityInfo subjectInfo = {"subjectCN", "subjectOrg", "subjectEmail"};

    X509CertificateInfo::EntityInfo issuerInfo = {"issuerCN", "issuerOrg", "issuerEmail"};

    X509CertificateInfo::Validity validity = {1672531200, 1704067200}; // Example timestamps



    void SetUp() override {

        EXPECT_CALL(mockCertInfo, getNickName()).WillRepeatedly(::testing::ReturnRef(nickName));

        EXPECT_CALL(mockCertInfo, getSubjectInfo()).WillRepeatedly(::testing::ReturnRef(subjectInfo));

        EXPECT_CALL(mockCertInfo, getIssuerInfo()).WillRepeatedly(::testing::ReturnRef(issuerInfo));

        EXPECT_CALL(mockCertInfo, getValidity()).WillRepeatedly(::testing::ReturnRef(validity));

    }

};



TEST_F(PopplerCertificateInfoTest_2404, CreateCertificateInfo_NormalOperation_2404) {

    PopplerCertificateInfo* certInfo = create_certificate_info(&mockCertInfo);

    EXPECT_STREQ(certInfo->id, "testNick");

    EXPECT_STREQ(certInfo->subject_common_name, "subjectCN");

    EXPECT_STREQ(certInfo->subject_organization, "subjectOrg");

    EXPECT_STREQ(certInfo->subject_email, "subjectEmail");

    EXPECT_STREQ(certInfo->issuer_common_name, "issuerCN");

    EXPECT_STREQ(certInfo->issuer_organization, "issuerOrg");

    EXPECT_STREQ(certInfo->issuer_email, "issuerEmail");

    g_date_time_unref(reinterpret_cast<GDateTime*>(certInfo->issued));

    g_date_time_unref(reinterpret_cast<GDateTime*>(certInfo->expires));

    g_free(certInfo->id);

    g_free(certInfo->subject_common_name);

    g_free(certInfo->subject_organization);

    g_free(certInfo->subject_email);

    g_free(certInfo->issuer_common_name);

    g_free(certInfo->issuer_organization);

    g_free(certInfo->issuer_email);

    g_free(certInfo);

}



TEST_F(PopplerCertificateInfoTest_2404, CreateCertificateInfo_NullInput_2404) {

    PopplerCertificateInfo* certInfo = create_certificate_info(nullptr);

    EXPECT_EQ(certInfo, nullptr);

}
