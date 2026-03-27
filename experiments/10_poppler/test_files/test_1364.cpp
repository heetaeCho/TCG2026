#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/NSSCryptoSignBackend.h"



using namespace CryptoSign;

using ::testing::Return;



class NSSSignatureCreationTest : public ::testing::Test {

protected:

    NSSSignatureCreation* nssSigCreation;



    void SetUp() override {

        nssSigCreation = new NSSSignatureCreation("certNickname", HashAlgorithm::SHA1);

    }



    void TearDown() override {

        delete nssSigCreation;

    }

};



TEST_F(NSSSignatureCreationTest_1364, SignatureType_ReturnsCorrectValue_1364) {

    EXPECT_EQ(nssSigCreation->signatureType(), SignatureType::adbe_pkcs7_detached);

}



// Boundary condition test for getCertificateInfo

TEST_F(NSSSignatureCreationTest_1364, GetCertificateInfo_ReturnsNonNegative_1364) {

    int certInfo = nssSigCreation->getCertificateInfo();

    EXPECT_GE(certInfo, 0);

}



// Normal operation test for addData

TEST_F(NSSSignatureCreationTest_1364, AddData_DoesNotThrow_1364) {

    unsigned char data[] = {0x01, 0x02, 0x03};

    EXPECT_NO_THROW(nssSigCreation->addData(data, sizeof(data)));

}



// Exceptional or error case for signDetached

TEST_F(NSSSignatureCreationTest_1364, SignDetached_WithEmptyPassword_ReturnsNegative_1364) {

    int result = nssSigCreation->signDetached("");

    EXPECT_LT(result, 0);

}



// Boundary condition test for addData with zero length

TEST_F(NSSSignatureCreationTest_1364, AddData_ZeroLength_DoesNotThrow_1364) {

    unsigned char data[] = {};

    EXPECT_NO_THROW(nssSigCreation->addData(data, sizeof(data)));

}
