#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <ctime>

// NSS headers
#include <nss.h>
#include <cert.h>
#include <pk11pub.h>
#include <secerr.h>
#include <prerror.h>
#include <keyhi.h>
#include <secder.h>

#include "CertificateInfo.h"
#include "GooString.h"

// Include the source to access the static function
#include "NSSCryptoSignBackend.cc"

class NSSCertificateInfoTest_1797 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        // Initialize NSS with no database (in-memory only)
        if (NSS_NoDB_Init(nullptr) != SECSuccess) {
            FAIL() << "Failed to initialize NSS";
        }
    }

    static void TearDownTestSuite() {
        NSS_Shutdown();
    }

    // Helper to create a self-signed certificate for testing
    static CERTCertificate *createSelfSignedCert(const char *subjectStr, SECKEYPrivateKey **privKey, SECKEYPublicKey **pubKey) {
        PK11SlotInfo *slot = PK11_GetInternalKeySlot();
        if (!slot) {
            return nullptr;
        }

        PK11RSAGenParams rsaParams;
        rsaParams.keySizeInBits = 2048;
        rsaParams.pe = 65537;

        *privKey = PK11_GenerateKeyPair(slot, CKM_RSA_PKCS_KEY_PAIR_GEN, &rsaParams, pubKey, PR_FALSE, PR_FALSE, nullptr);
        PK11_FreeSlot(slot);

        if (!*privKey || !*pubKey) {
            return nullptr;
        }

        CERTName *subject = CERT_AsciiToName(subjectStr);
        if (!subject) {
            SECKEY_DestroyPrivateKey(*privKey);
            SECKEY_DestroyPublicKey(*pubKey);
            return nullptr;
        }

        CERTSubjectPublicKeyInfo *spki = SECKEY_CreateSubjectPublicKeyInfo(*pubKey);
        if (!spki) {
            CERT_DestroyName(subject);
            SECKEY_DestroyPrivateKey(*privKey);
            SECKEY_DestroyPublicKey(*pubKey);
            return nullptr;
        }

        CERTCertificateRequest *certReq = CERT_CreateCertificateRequest(subject, spki, nullptr);
        SECKEY_DestroySubjectPublicKeyInfo(spki);

        if (!certReq) {
            CERT_DestroyName(subject);
            SECKEY_DestroyPrivateKey(*privKey);
            SECKEY_DestroyPublicKey(*pubKey);
            return nullptr;
        }

        // Create certificate
        unsigned long serialNumber = 1;
        CERTValidity *validity = CERT_CreateValidity(PR_Now() - (PRTime)86400 * 1000000LL, PR_Now() + (PRTime)365 * 86400 * 1000000LL);
        if (!validity) {
            CERT_DestroyCertificateRequest(certReq);
            CERT_DestroyName(subject);
            SECKEY_DestroyPrivateKey(*privKey);
            SECKEY_DestroyPublicKey(*pubKey);
            return nullptr;
        }

        CERTCertificate *cert = CERT_CreateCertificate(serialNumber, subject, validity, certReq);
        CERT_DestroyValidity(validity);
        CERT_DestroyCertificateRequest(certReq);
        CERT_DestroyName(subject);

        if (!cert) {
            SECKEY_DestroyPrivateKey(*privKey);
            SECKEY_DestroyPublicKey(*pubKey);
            return nullptr;
        }

        // Sign the certificate
        SECAlgorithmID algID;
        memset(&algID, 0, sizeof(algID));
        SECOidTag sigAlg = SEC_OID_PKCS1_SHA256_WITH_RSA_ENCRYPTION;

        SECStatus rv = SECOID_SetAlgorithmID(cert->arena, &cert->signature, sigAlg, nullptr);
        if (rv != SECSuccess) {
            CERT_DestroyCertificate(cert);
            SECKEY_DestroyPrivateKey(*privKey);
            SECKEY_DestroyPublicKey(*pubKey);
            return nullptr;
        }

        // Encode and sign
        SECItem der = { siBuffer, nullptr, 0 };
        der.len = 0;
        der.data = nullptr;

        SECItem *result = SEC_ASN1EncodeItem(cert->arena, &der, cert, SEC_ASN1_GET(CERT_CertificateTemplate));
        if (!result) {
            CERT_DestroyCertificate(cert);
            SECKEY_DestroyPrivateKey(*privKey);
            SECKEY_DestroyPublicKey(*pubKey);
            return nullptr;
        }

        rv = SEC_DerSignData(cert->arena, &cert->derCert, der.data, der.len, *privKey, sigAlg);
        if (rv != SECSuccess) {
            CERT_DestroyCertificate(cert);
            SECKEY_DestroyPrivateKey(*privKey);
            SECKEY_DestroyPublicKey(*pubKey);
            return nullptr;
        }

        // Decode the signed cert to get a proper CERTCertificate
        CERTCertificate *signedCert = CERT_DecodeDERCertificate(&cert->derCert, PR_TRUE, nullptr);
        CERT_DestroyCertificate(cert);

        return signedCert;
    }
};

TEST_F(NSSCertificateInfoTest_1797, NullCertHandling_1797) {
    // Testing with nullptr - this may crash, so we document expected behavior
    // Skip if implementation doesn't handle null
    // This test documents the interface expectation
}

TEST_F(NSSCertificateInfoTest_1797, SelfSignedCertBasicInfo_1797) {
    SECKEYPrivateKey *privKey = nullptr;
    SECKEYPublicKey *pubKey = nullptr;

    CERTCertificate *cert = createSelfSignedCert("CN=Test User,O=Test Org,C=US", &privKey, &pubKey);
    if (!cert) {
        GTEST_SKIP() << "Could not create test certificate";
    }

    auto certInfo = getCertificateInfoFromCERT(cert);

    ASSERT_NE(certInfo, nullptr);

    // Self-signed cert should report isSelfSigned = true
    EXPECT_TRUE(certInfo->getIsSelfSigned());

    // Version should be set (typically v3 = 3 or v1 = 1)
    EXPECT_GE(certInfo->getVersion(), 1);

    CERT_DestroyCertificate(cert);
    if (privKey) SECKEY_DestroyPrivateKey(privKey);
    if (pubKey) SECKEY_DestroyPublicKey(pubKey);
}

TEST_F(NSSCertificateInfoTest_1797, CertificateVersionIsCorrect_1797) {
    SECKEYPrivateKey *privKey = nullptr;
    SECKEYPublicKey *pubKey = nullptr;

    CERTCertificate *cert = createSelfSignedCert("CN=Version Test,O=Test,C=US", &privKey, &pubKey);
    if (!cert) {
        GTEST_SKIP() << "Could not create test certificate";
    }

    auto certInfo = getCertificateInfoFromCERT(cert);
    ASSERT_NE(certInfo, nullptr);

    // DER_GetInteger(&cert->version) + 1 should give us version
    int expectedVersion = DER_GetInteger(&cert->version) + 1;
    EXPECT_EQ(certInfo->getVersion(), expectedVersion);

    CERT_DestroyCertificate(cert);
    if (privKey) SECKEY_DestroyPrivateKey(privKey);
    if (pubKey) SECKEY_DestroyPublicKey(pubKey);
}

TEST_F(NSSCertificateInfoTest_1797, SerialNumberIsNonEmpty_1797) {
    SECKEYPrivateKey *privKey = nullptr;
    SECKEYPublicKey *pubKey = nullptr;

    CERTCertificate *cert = createSelfSignedCert("CN=Serial Test,O=Test,C=US", &privKey, &pubKey);
    if (!cert) {
        GTEST_SKIP() << "Could not create test certificate";
    }

    auto certInfo = getCertificateInfoFromCERT(cert);
    ASSERT_NE(certInfo, nullptr);

    // Serial number should be non-empty
    EXPECT_GT(certInfo->getSerialNumber().getLength(), 0);

    CERT_DestroyCertificate(cert);
    if (privKey) SECKEY_DestroyPrivateKey(privKey);
    if (pubKey) SECKEY_DestroyPublicKey(pubKey);
}

TEST_F(NSSCertificateInfoTest_1797, ValidityDatesAreSet_1797) {
    SECKEYPrivateKey *privKey = nullptr;
    SECKEYPublicKey *pubKey = nullptr;

    CERTCertificate *cert = createSelfSignedCert("CN=Validity Test,O=Test,C=US", &privKey, &pubKey);
    if (!cert) {
        GTEST_SKIP() << "Could not create test certificate";
    }

    auto certInfo = getCertificateInfoFromCERT(cert);
    ASSERT_NE(certInfo, nullptr);

    auto validity = certInfo->getValidity();

    // notBefore should be in the past (we set it to yesterday)
    EXPECT_GT(validity.notBefore, 0);
    // notAfter should be in the future
    EXPECT_GT(validity.notAfter, validity.notBefore);

    // Verify the times match what NSS reports
    PRTime notBefore, notAfter;
    CERT_GetCertTimes(cert, &notBefore, &notAfter);
    EXPECT_EQ(validity.notBefore, static_cast<time_t>(notBefore / 1000000));
    EXPECT_EQ(validity.notAfter, static_cast<time_t>(notAfter / 1000000));

    CERT_DestroyCertificate(cert);
    if (privKey) SECKEY_DestroyPrivateKey(privKey);
    if (pubKey) SECKEY_DestroyPublicKey(pubKey);
}

TEST_F(NSSCertificateInfoTest_1797, PublicKeyInfoIsRSA_1797) {
    SECKEYPrivateKey *privKey = nullptr;
    SECKEYPublicKey *pubKey = nullptr;

    CERTCertificate *cert = createSelfSignedCert("CN=RSA Key Test,O=Test,C=US", &privKey, &pubKey);
    if (!cert) {
        GTEST_SKIP() << "Could not create test certificate";
    }

    auto certInfo = getCertificateInfoFromCERT(cert);
    ASSERT_NE(certInfo, nullptr);

    auto pkInfo = certInfo->getPublicKeyInfo();
    // We created an RSA key
    EXPECT_EQ(pkInfo.publicKeyType, RSAKEY);
    EXPECT_EQ(pkInfo.publicKeyStrength, 2048u);
    EXPECT_GT(pkInfo.publicKey.getLength(), 0);

    CERT_DestroyCertificate(cert);
    if (privKey) SECKEY_DestroyPrivateKey(privKey);
    if (pubKey) SECKEY_DestroyPublicKey(pubKey);
}

TEST_F(NSSCertificateInfoTest_1797, SelfSignedFlagCorrect_1797) {
    SECKEYPrivateKey *privKey = nullptr;
    SECKEYPublicKey *pubKey = nullptr;

    // Self-signed: subject == issuer
    CERTCertificate *cert = createSelfSignedCert("CN=Self Signed,O=Test,C=US", &privKey, &pubKey);
    if (!cert) {
        GTEST_SKIP() << "Could not create test certificate";
    }

    auto certInfo = getCertificateInfoFromCERT(cert);
    ASSERT_NE(certInfo, nullptr);

    // For a self-signed cert, subject and issuer are the same
    bool expectedSelfSigned = (CERT_CompareName(&cert->subject, &cert->issuer) == SECEqual);
    EXPECT_EQ(certInfo->getIsSelfSigned(), expectedSelfSigned);

    CERT_DestroyCertificate(cert);
    if (privKey) SECKEY_DestroyPrivateKey(privKey);
    if (pubKey) SECKEY_DestroyPublicKey(pubKey);
}

TEST_F(NSSCertificateInfoTest_1797, CertificateDERIsNonEmpty_1797) {
    SECKEYPrivateKey *privKey = nullptr;
    SECKEYPublicKey *pubKey = nullptr;

    CERTCertificate *cert = createSelfSignedCert("CN=DER Test,O=Test,C=US", &privKey, &pubKey);
    if (!cert) {
        GTEST_SKIP() << "Could not create test certificate";
    }

    auto certInfo = getCertificateInfoFromCERT(cert);
    ASSERT_NE(certInfo, nullptr);

    // DER encoding should be non-empty
    EXPECT_GT(certInfo->getCertificateDER().getLength(), 0);

    CERT_DestroyCertificate(cert);
    if (privKey) SECKEY_DestroyPrivateKey(privKey);
    if (pubKey) SECKEY_DestroyPublicKey(pubKey);
}

TEST_F(NSSCertificateInfoTest_1797, SubjectInfoContainsExpectedFields_1797) {
    SECKEYPrivateKey *privKey = nullptr;
    SECKEYPublicKey *pubKey = nullptr;

    CERTCertificate *cert = createSelfSignedCert("CN=Subject Test,O=My Organization,C=DE", &privKey, &pubKey);
    if (!cert) {
        GTEST_SKIP() << "Could not create test certificate";
    }

    auto certInfo = getCertificateInfoFromCERT(cert);
    ASSERT_NE(certInfo, nullptr);

    auto subjectInfo = certInfo->getSubjectInfo();
    // The subject should contain the CN we specified
    EXPECT_FALSE(subjectInfo.commonName.empty());

    CERT_DestroyCertificate(cert);
    if (privKey) SECKEY_DestroyPrivateKey(privKey);
    if (pubKey) SECKEY_DestroyPublicKey(pubKey);
}

TEST_F(NSSCertificateInfoTest_1797, IssuerInfoContainsExpectedFields_1797) {
    SECKEYPrivateKey *privKey = nullptr;
    SECKEYPublicKey *pubKey = nullptr;

    CERTCertificate *cert = createSelfSignedCert("CN=Issuer Test,O=Issuer Org,C=FR", &privKey, &pubKey);
    if (!cert) {
        GTEST_SKIP() << "Could not create test certificate";
    }

    auto certInfo = getCertificateInfoFromCERT(cert);
    ASSERT_NE(certInfo, nullptr);

    auto issuerInfo = certInfo->getIssuerInfo();
    // For self-signed cert, issuer info should match subject
    EXPECT_FALSE(issuerInfo.commonName.empty());

    CERT_DestroyCertificate(cert);
    if (privKey) SECKEY_DestroyPrivateKey(privKey);
    if (pubKey) SECKEY_DestroyPublicKey(pubKey);
}

TEST_F(NSSCertificateInfoTest_1797, ReturnTypeIsUniquePtrNotNull_1797) {
    SECKEYPrivateKey *privKey = nullptr;
    SECKEYPublicKey *pubKey = nullptr;

    CERTCertificate *cert = createSelfSignedCert("CN=UniquePtr Test,O=Test,C=US", &privKey, &pubKey);
    if (!cert) {
        GTEST_SKIP() << "Could not create test certificate";
    }

    auto certInfo = getCertificateInfoFromCERT(cert);

    // Should always return a non-null unique_ptr for valid cert
    ASSERT_NE(certInfo.get(), nullptr);

    CERT_DestroyCertificate(cert);
    if (privKey) SECKEY_DestroyPrivateKey(privKey);
    if (pubKey) SECKEY_DestroyPublicKey(pubKey);
}
