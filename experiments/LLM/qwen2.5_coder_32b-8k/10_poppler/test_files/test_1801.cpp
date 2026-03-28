#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming the interface we need to test is part of a class or namespace

// Since there's no class provided, I'll assume this function is part of some utility class or namespace

// For the sake of testing, let's assume it's in a namespace called `NSSCryptoSignBackend`



namespace NSSCryptoSignBackend {

    static NSSCMSSignerInfo *CMS_SignerInfoCreate(NSSCMSSignedData *cms_sig_data);

}



// Mocking external dependencies if any were present

// In this case, there are no direct collaborators to mock, but we can mock the behavior of NSS_CMSSignedData_GetSignerInfo



class MockNSSCrypto {

public:

    MOCK_STATIC_METHOD1(NSS_CMSSignedData_GetSignerInfo, NSSCMSSignerInfo*(NSSCMSSignedData*, int));

};



// Using a test fixture if needed

class CMS_SignerInfoCreateTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Redirect calls to the mock implementation

        ON_CALL(MockNSSCrypto, NSS_CMSSignedData_GetSignerInfo(testing::_, testing::_))

            .WillByDefault([](NSSCMSSignedData*, int) -> NSSCMSSignerInfo* { return nullptr; });

    }

};



TEST_F(CMS_SignerInfoCreateTest_1801, NormalOperation_ReturnsNonNullSignerInfo_1801) {

    // Arrange

    NSSCMSSignedData *mockCmsSigData = reinterpret_cast<NSSCMSSignedData*>(0x1);

    NSSCMSSignerInfo mockSignerInfo;

    EXPECT_CALL(MockNSSCrypto, NSS_CMSSignedData_GetSignerInfo(mockCmsSigData, 0))

        .WillOnce(testing::Return(&mockSignerInfo));



    // Act

    NSSCMSSignerInfo* result = NSSCryptoSignBackend::CMS_SignerInfoCreate(mockCmsSigData);



    // Assert

    EXPECT_NE(result, nullptr);

}



TEST_F(CMS_SignerInfoCreateTest_1801, BoundaryCondition_ZeroIndex_ReturnsNonNullSignerInfo_1801) {

    // Arrange

    NSSCMSSignedData *mockCmsSigData = reinterpret_cast<NSSCMSSignedData*>(0x1);

    NSSCMSSignerInfo mockSignerInfo;

    EXPECT_CALL(MockNSSCrypto, NSS_CMSSignedData_GetSignerInfo(mockCmsSigData, 0))

        .WillOnce(testing::Return(&mockSignerInfo));



    // Act

    NSSCMSSignerInfo* result = NSSCryptoSignBackend::CMS_SignerInfoCreate(mockCmsSigData);



    // Assert

    EXPECT_NE(result, nullptr);

}



TEST_F(CMS_SignerInfoCreateTest_1801, ErrorCase_NullSignerInfo_ReturnsNull_1801) {

    // Arrange

    NSSCMSSignedData *mockCmsSigData = reinterpret_cast<NSSCMSSignedData*>(0x1);

    EXPECT_CALL(MockNSSCrypto, NSS_CMSSignedData_GetSignerInfo(mockCmsSigData, 0))

        .WillOnce(testing::Return(nullptr));



    // Act

    NSSCMSSignerInfo* result = NSSCryptoSignBackend::CMS_SignerInfoCreate(mockCmsSigData);



    // Assert

    EXPECT_EQ(result, nullptr);

}



TEST_F(CMS_SignerInfoCreateTest_1801, ErrorCase_NullCmsSignedData_ReturnsNull_1801) {

    // Arrange

    NSSCMSSignedData *mockCmsSigData = nullptr;

    EXPECT_CALL(MockNSSCrypto, NSS_CMSSignedData_GetSignerInfo(mockCmsSigData, 0))

        .WillOnce(testing::Return(nullptr));



    // Act

    NSSCMSSignerInfo* result = NSSCryptoSignBackend::CMS_SignerInfoCreate(mockCmsSigData);



    // Assert

    EXPECT_EQ(result, nullptr);

}

```


