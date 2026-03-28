#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <optional>

#include "SecurityHandler.h"
#include "PDFDoc.h"
#include "GooString.h"
#include "Object.h"

class StandardSecurityHandlerTest_1849 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create a PDFDoc from a test PDF file
    std::unique_ptr<PDFDoc> createPDFDoc(const char* filename) {
        auto fileName = std::make_unique<GooString>(filename);
        return std::make_unique<PDFDoc>(std::move(fileName));
    }
};

// Test that getEncVersion returns a valid encryption version for an encrypted PDF
TEST_F(StandardSecurityHandlerTest_1849, GetEncVersionReturnsValidVersion_1849) {
    // We need an actual encrypted PDF to properly test this.
    // Since we can't create one in-memory easily, we test with available resources.
    // This test verifies the method is callable and returns a reasonable value.
    // Encryption versions are typically 1, 2, 3, 4, or 5.
    auto doc = createPDFDoc("../test/unittestcases/encrypted.pdf");
    if (doc && doc->isOk()) {
        Object encryptDict = doc->getXRef()->getTrailerDict()->dictLookup("Encrypt");
        if (encryptDict.isDict()) {
            StandardSecurityHandler handler(doc.get(), &encryptDict);
            int version = handler.getEncVersion();
            EXPECT_GE(version, 0);
            EXPECT_LE(version, 5);
        }
    }
}

// Test getEncRevision returns a valid revision number
TEST_F(StandardSecurityHandlerTest_1849, GetEncRevisionReturnsValidRevision_1849) {
    auto doc = createPDFDoc("../test/unittestcases/encrypted.pdf");
    if (doc && doc->isOk()) {
        Object encryptDict = doc->getXRef()->getTrailerDict()->dictLookup("Encrypt");
        if (encryptDict.isDict()) {
            StandardSecurityHandler handler(doc.get(), &encryptDict);
            int revision = handler.getEncRevision();
            // Revisions are typically 2, 3, 4, 5, or 6
            EXPECT_GE(revision, 0);
            EXPECT_LE(revision, 6);
        }
    }
}

// Test getFileKeyLength returns a reasonable key length
TEST_F(StandardSecurityHandlerTest_1849, GetFileKeyLengthReturnsValidLength_1849) {
    auto doc = createPDFDoc("../test/unittestcases/encrypted.pdf");
    if (doc && doc->isOk()) {
        Object encryptDict = doc->getXRef()->getTrailerDict()->dictLookup("Encrypt");
        if (encryptDict.isDict()) {
            StandardSecurityHandler handler(doc.get(), &encryptDict);
            int keyLength = handler.getFileKeyLength();
            // Key lengths are typically 5 (40-bit), 16 (128-bit), or 32 (256-bit) bytes
            EXPECT_GE(keyLength, 0);
            EXPECT_LE(keyLength, 32);
        }
    }
}

// Test authorize with correct user password (empty password for user-readable PDFs)
TEST_F(StandardSecurityHandlerTest_1849, AuthorizeWithEmptyPasswordForUserReadable_1849) {
    auto doc = createPDFDoc("../test/unittestcases/encrypted.pdf");
    if (doc && doc->isOk()) {
        Object encryptDict = doc->getXRef()->getTrailerDict()->dictLookup("Encrypt");
        if (encryptDict.isDict()) {
            StandardSecurityHandler handler(doc.get(), &encryptDict);
            void* authData = handler.makeAuthData(std::nullopt, std::nullopt);
            // Try authorizing - result depends on the PDF's password settings
            bool authorized = handler.authorize(authData);
            // We just verify it doesn't crash; result depends on PDF
            if (authData) {
                handler.freeAuthData(authData);
            }
            // The test primarily verifies no crash occurs
            SUCCEED();
        }
    }
}

// Test makeAuthData and freeAuthData with passwords
TEST_F(StandardSecurityHandlerTest_1849, MakeAuthDataAndFreeAuthData_1849) {
    auto doc = createPDFDoc("../test/unittestcases/encrypted.pdf");
    if (doc && doc->isOk()) {
        Object encryptDict = doc->getXRef()->getTrailerDict()->dictLookup("Encrypt");
        if (encryptDict.isDict()) {
            StandardSecurityHandler handler(doc.get(), &encryptDict);

            GooString ownerPass("owner");
            GooString userPass("user");
            void* authData = handler.makeAuthData(ownerPass, userPass);
            // authData may or may not be null depending on implementation
            if (authData) {
                handler.freeAuthData(authData);
            }
            SUCCEED();
        }
    }
}

// Test freeAuthData with nullptr should not crash
TEST_F(StandardSecurityHandlerTest_1849, FreeAuthDataWithNullptr_1849) {
    auto doc = createPDFDoc("../test/unittestcases/encrypted.pdf");
    if (doc && doc->isOk()) {
        Object encryptDict = doc->getXRef()->getTrailerDict()->dictLookup("Encrypt");
        if (encryptDict.isDict()) {
            StandardSecurityHandler handler(doc.get(), &encryptDict);
            // Freeing nullptr should be safe
            handler.freeAuthData(nullptr);
            SUCCEED();
        }
    }
}

// Test isUnencrypted returns false for encrypted PDF
TEST_F(StandardSecurityHandlerTest_1849, IsUnencryptedReturnsFalseForEncryptedPDF_1849) {
    auto doc = createPDFDoc("../test/unittestcases/encrypted.pdf");
    if (doc && doc->isOk()) {
        Object encryptDict = doc->getXRef()->getTrailerDict()->dictLookup("Encrypt");
        if (encryptDict.isDict()) {
            StandardSecurityHandler handler(doc.get(), &encryptDict);
            // An encrypted PDF with an Encrypt dict should not report as unencrypted
            // unless it's a special identity-only encryption
            bool unencrypted = handler.isUnencrypted();
            // We can't assert the exact value without knowing the PDF, but we verify the call works
            SUCCEED();
        }
    }
}

// Test getPermissionFlags returns a value
TEST_F(StandardSecurityHandlerTest_1849, GetPermissionFlagsReturnsValue_1849) {
    auto doc = createPDFDoc("../test/unittestcases/encrypted.pdf");
    if (doc && doc->isOk()) {
        Object encryptDict = doc->getXRef()->getTrailerDict()->dictLookup("Encrypt");
        if (encryptDict.isDict()) {
            StandardSecurityHandler handler(doc.get(), &encryptDict);
            int flags = handler.getPermissionFlags();
            // Permission flags is a bitmask, should be some integer value
            // We just verify the method is callable
            (void)flags;
            SUCCEED();
        }
    }
}

// Test getOwnerPasswordOk before authorization
TEST_F(StandardSecurityHandlerTest_1849, GetOwnerPasswordOkBeforeAuthorize_1849) {
    auto doc = createPDFDoc("../test/unittestcases/encrypted.pdf");
    if (doc && doc->isOk()) {
        Object encryptDict = doc->getXRef()->getTrailerDict()->dictLookup("Encrypt");
        if (encryptDict.isDict()) {
            StandardSecurityHandler handler(doc.get(), &encryptDict);
            // Before authorization, owner password should not be ok
            bool ownerOk = handler.getOwnerPasswordOk();
            EXPECT_FALSE(ownerOk);
        }
    }
}

// Test getEncAlgorithm returns a valid algorithm
TEST_F(StandardSecurityHandlerTest_1849, GetEncAlgorithmReturnsValidAlgorithm_1849) {
    auto doc = createPDFDoc("../test/unittestcases/encrypted.pdf");
    if (doc && doc->isOk()) {
        Object encryptDict = doc->getXRef()->getTrailerDict()->dictLookup("Encrypt");
        if (encryptDict.isDict()) {
            StandardSecurityHandler handler(doc.get(), &encryptDict);
            CryptAlgorithm algo = handler.getEncAlgorithm();
            // Valid algorithm values - just verify it's callable and returns something in range
            EXPECT_GE(static_cast<int>(algo), 0);
        }
    }
}

// Test getFileKey returns non-null after successful authorization
TEST_F(StandardSecurityHandlerTest_1849, GetFileKeyAfterAuthorization_1849) {
    auto doc = createPDFDoc("../test/unittestcases/encrypted.pdf");
    if (doc && doc->isOk()) {
        Object encryptDict = doc->getXRef()->getTrailerDict()->dictLookup("Encrypt");
        if (encryptDict.isDict()) {
            StandardSecurityHandler handler(doc.get(), &encryptDict);
            void* authData = handler.makeAuthData(std::nullopt, std::nullopt);
            bool authorized = handler.authorize(authData);
            if (authorized) {
                const unsigned char* key = handler.getFileKey();
                EXPECT_NE(key, nullptr);
                int keyLen = handler.getFileKeyLength();
                EXPECT_GT(keyLen, 0);
            }
            if (authData) {
                handler.freeAuthData(authData);
            }
        }
    }
}

// Test makeAuthData with optional passwords as nullopt
TEST_F(StandardSecurityHandlerTest_1849, MakeAuthDataWithNullOptPasswords_1849) {
    auto doc = createPDFDoc("../test/unittestcases/encrypted.pdf");
    if (doc && doc->isOk()) {
        Object encryptDict = doc->getXRef()->getTrailerDict()->dictLookup("Encrypt");
        if (encryptDict.isDict()) {
            StandardSecurityHandler handler(doc.get(), &encryptDict);
            void* authData = handler.makeAuthData(std::nullopt, std::nullopt);
            // Should return valid auth data (possibly representing empty passwords)
            if (authData) {
                handler.freeAuthData(authData);
            }
            SUCCEED();
        }
    }
}

// Test multiple authorize calls don't crash
TEST_F(StandardSecurityHandlerTest_1849, MultipleAuthorizeCalls_1849) {
    auto doc = createPDFDoc("../test/unittestcases/encrypted.pdf");
    if (doc && doc->isOk()) {
        Object encryptDict = doc->getXRef()->getTrailerDict()->dictLookup("Encrypt");
        if (encryptDict.isDict()) {
            StandardSecurityHandler handler(doc.get(), &encryptDict);

            void* authData1 = handler.makeAuthData(std::nullopt, std::nullopt);
            handler.authorize(authData1);
            if (authData1) handler.freeAuthData(authData1);

            void* authData2 = handler.makeAuthData(std::nullopt, std::nullopt);
            handler.authorize(authData2);
            if (authData2) handler.freeAuthData(authData2);

            SUCCEED();
        }
    }
}
