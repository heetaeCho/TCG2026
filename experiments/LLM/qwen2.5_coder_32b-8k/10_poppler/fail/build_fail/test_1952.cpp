#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GPGMECryptoSignBackend.cc"

#include "CertificateInfo.h"



namespace {



using namespace GpgME;



class SubkeyMock : public Subkey {

public:

    MOCK_CONST_METHOD0(creationTime, time_t());

    MOCK_CONST_METHOD0(expirationTime, time_t());

    MOCK_CONST_METHOD0(neverExpires, bool());

};



class X509CertificateInfoTest_1952 : public ::testing::Test {

protected:

    SubkeyMock mockSubkey;

};



TEST_F(X509CertificateInfoTest_1952, ValidityNotBeforeSetCorrectly_1952) {

    const time_t expectedCreationTime = 1672531200; // Example timestamp

    EXPECT_CALL(mockSubkey, creationTime()).WillOnce(::testing::Return(expectedCreationTime));

    X509CertificateInfo::Validity validity = getValidityFromSubkey(mockSubkey);

    EXPECT_EQ(validity.notBefore, expectedCreationTime);

}



TEST_F(X509CertificateInfoTest_1952, ValidityNotAfterSetToMaxWhenNeverExpires_1952) {

    EXPECT_CALL(mockSubkey, neverExpires()).WillOnce(::testing::Return(true));

    X509CertificateInfo::Validity validity = getValidityFromSubkey(mockSubkey);

    EXPECT_EQ(validity.notAfter, std::numeric_limits<time_t>::max());

}



TEST_F(X509CertificateInfoTest_1952, ValidityNotAfterSetCorrectlyWhenExpires_1952) {

    const time_t expectedExpirationTime = 1704067200; // Example timestamp

    EXPECT_CALL(mockSubkey, neverExpires()).WillOnce(::testing::Return(false));

    EXPECT_CALL(mockSubkey, expirationTime()).WillOnce(::testing::Return(expectedExpirationTime));

    X509CertificateInfo::Validity validity = getValidityFromSubkey(mockSubkey);

    EXPECT_EQ(validity.notAfter, expectedExpirationTime);

}



TEST_F(X509CertificateInfoTest_1952, BoundaryConditionNeverExpiresFalseAndZeroExpiration_1952) {

    EXPECT_CALL(mockSubkey, neverExpires()).WillOnce(::testing::Return(false));

    EXPECT_CALL(mockSubkey, expirationTime()).WillOnce(::testing::Return(0));

    X509CertificateInfo::Validity validity = getValidityFromSubkey(mockSubkey);

    EXPECT_EQ(validity.notAfter, 0);

}



} // namespace
