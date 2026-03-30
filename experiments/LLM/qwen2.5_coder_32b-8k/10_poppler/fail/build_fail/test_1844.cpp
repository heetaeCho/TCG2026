#include <gtest/gtest.h>

#include "poppler/SecurityHandler.h"



class SecurityHandlerTest : public ::testing::Test {

protected:

    class MockPDFDoc {};

    class MockObject {};



    MockPDFDoc mockDoc;

    MockObject mockEncryptDict;



    std::unique_ptr<SecurityHandler> securityHandler;



    void SetUp() override {

        securityHandler.reset(SecurityHandler::make(&mockDoc, &mockEncryptDict));

    }

};



TEST_F(SecurityHandlerTest_1844, IsUnencrypted_Default_ReturnsFalse_1844) {

    EXPECT_FALSE(securityHandler->isUnencrypted());

}



TEST_F(SecurityHandlerTest_1844, CheckEncryption_NoPasswords_ReturnsFalse_1844) {

    EXPECT_FALSE(securityHandler->checkEncryption(std::nullopt, std::nullopt));

}



TEST_F(SecurityHandlerTest_1844, CheckEncryption_WithUserPassword_ReturnsBoolean_1844) {

    GooString userPassword("userPass");

    EXPECT_EQ(securityHandler->checkEncryption(std::nullopt, userPassword), ::testing::_);

}



TEST_F(SecurityHandlerTest_1844, CheckEncryption_WithOwnerPassword_ReturnsBoolean_1844) {

    GooString ownerPassword("ownerPass");

    EXPECT_EQ(securityHandler->checkEncryption(ownerPassword, std::nullopt), ::testing::_);

}



TEST_F(SecurityHandlerTest_1844, MakeAuthData_NoPasswords_ReturnsNonNullPtr_1844) {

    void* authData = securityHandler->makeAuthData(std::nullopt, std::nullopt);

    EXPECT_NE(authData, nullptr);

    securityHandler->freeAuthData(authData);

}



TEST_F(SecurityHandlerTest_1844, MakeAuthData_WithUserPassword_ReturnsNonNullPtr_1844) {

    GooString userPassword("userPass");

    void* authData = securityHandler->makeAuthData(std::nullopt, userPassword);

    EXPECT_NE(authData, nullptr);

    securityHandler->freeAuthData(authData);

}



TEST_F(SecurityHandlerTest_1844, MakeAuthData_WithOwnerPassword_ReturnsNonNullPtr_1844) {

    GooString ownerPassword("ownerPass");

    void* authData = securityHandler->makeAuthData(ownerPassword, std::nullopt);

    EXPECT_NE(authData, nullptr);

    securityHandler->freeAuthData(authData);

}



TEST_F(SecurityHandlerTest_1844, FreeAuthData_ValidPointer_NoCrash_1844) {

    void* authData = securityHandler->makeAuthData(std::nullopt, std::nullopt);

    EXPECT_NO_THROW(securityHandler->freeAuthData(authData));

}



TEST_F(SecurityHandlerTest_1844, Authorize_ValidAuthData_ReturnsFalse_1844) {

    void* authData = securityHandler->makeAuthData(std::nullopt, std::nullopt);

    EXPECT_FALSE(securityHandler->authorize(authData));

    securityHandler->freeAuthData(authData);

}



TEST_F(SecurityHandlerTest_1844, GetPermissionFlags_ReturnsInt_1844) {

    int permissionFlags = securityHandler->getPermissionFlags();

    EXPECT_EQ(permissionFlags, ::testing::_);

}



TEST_F(SecurityHandlerTest_1844, GetOwnerPasswordOk_Default_ReturnsFalse_1844) {

    EXPECT_FALSE(securityHandler->getOwnerPasswordOk());

}



TEST_F(SecurityHandlerTest_1844, GetFileKey_ReturnsPointer_1844) {

    const unsigned char* fileKey = securityHandler->getFileKey();

    EXPECT_EQ(fileKey, ::testing::_);

}



TEST_F(SecurityHandlerTest_1844, GetFileKeyLength_Default_ReturnsInt_1844) {

    int fileKeyLength = securityHandler->getFileKeyLength();

    EXPECT_EQ(fileKeyLength, ::testing::_);

}



TEST_F(SecurityHandlerTest_1844, GetEncVersion_Default_ReturnsInt_1844) {

    int encVersion = securityHandler->getEncVersion();

    EXPECT_EQ(encVersion, ::testing::_);

}



TEST_F(SecurityHandlerTest_1844, GetEncRevision_Default_ReturnsInt_1844) {

    int encRevision = securityHandler->getEncRevision();

    EXPECT_EQ(encRevision, ::testing::_);

}



TEST_F(SecurityHandlerTest_1844, GetEncAlgorithm_Default_ReturnsCryptAlgorithm_1844) {

    CryptAlgorithm encAlgorithm = securityHandler->getEncAlgorithm();

    EXPECT_EQ(encAlgorithm, ::testing::_);

}
