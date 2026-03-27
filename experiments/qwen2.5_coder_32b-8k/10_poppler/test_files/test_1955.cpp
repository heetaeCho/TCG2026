#include <gtest/gtest.h>

#include <gpgme++/context.h>

#include "GPGMECryptoSignBackendConfiguration.h"



// Mock class for GpgSignatureConfiguration if needed

class MockGpgSignatureConfiguration : public GpgSignatureConfiguration {

public:

    MOCK_STATIC_METHOD0(arePgpSignaturesAllowed, bool());

};



TEST(AllowedTypesTest_1955, OnlyCMSWhenPgpDisallowed_1955) {

    // Arrange

    EXPECT_CALL(MockGpgSignatureConfiguration::arePgpSignaturesAllowed(), Times(1)).WillOnce(testing::Return(false));



    // Act

    std::vector<GpgME::Protocol> result = allowedTypes();



    // Assert

    ASSERT_EQ(result.size(), 1);

    EXPECT_EQ(result[0], GpgME::CMS);

}



TEST(AllowedTypesTest_1955, BothCMSAndOpenPGPWhenPgpAllowed_1955) {

    // Arrange

    EXPECT_CALL(MockGpgSignatureConfiguration::arePgpSignaturesAllowed(), Times(1)).WillOnce(testing::Return(true));



    // Act

    std::vector<GpgME::Protocol> result = allowedTypes();



    // Assert

    ASSERT_EQ(result.size(), 2);

    EXPECT_EQ(result[0], GpgME::CMS);

    EXPECT_EQ(result[1], GpgME::OpenPGP);

}
