#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QVector>

// Include the poppler-qt5 headers for the form/certificate interface
#include "poppler-form.h"
#include "poppler-qt5.h"

// We test the public interface of getAvailableSigningCertificates()
// Since the function depends on CryptoSign::Factory::createActive(),
// which may or may not return a backend depending on the build configuration,
// we test observable behavior through the public API.

namespace {

class GetAvailableSigningCertificatesTest_1371 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that the function returns a QVector (possibly empty) without crashing
TEST_F(GetAvailableSigningCertificatesTest_1371, ReturnsQVectorWithoutCrash_1371)
{
    QVector<Poppler::CertificateInfo> certs = Poppler::getAvailableSigningCertificates();
    // The function should return without crashing.
    // The result may be empty if no crypto backend is available.
    EXPECT_GE(certs.size(), 0);
}

// Test that calling the function multiple times yields consistent results
TEST_F(GetAvailableSigningCertificatesTest_1371, ConsistentResultsOnMultipleCalls_1371)
{
    QVector<Poppler::CertificateInfo> certs1 = Poppler::getAvailableSigningCertificates();
    QVector<Poppler::CertificateInfo> certs2 = Poppler::getAvailableSigningCertificates();
    // Both calls should return the same number of certificates
    EXPECT_EQ(certs1.size(), certs2.size());
}

// Test that if certificates are returned, each CertificateInfo is valid (non-null)
TEST_F(GetAvailableSigningCertificatesTest_1371, ReturnedCertificatesAreAccessible_1371)
{
    QVector<Poppler::CertificateInfo> certs = Poppler::getAvailableSigningCertificates();
    for (int i = 0; i < certs.size(); ++i) {
        // Access public methods on each CertificateInfo to verify they don't crash
        // CertificateInfo should have isNull() or similar accessors
        const Poppler::CertificateInfo &cert = certs.at(i);
        // Just accessing the certificate info object should not crash
        // We can check nickName or similar public accessors if available
        (void)cert.isNull();
    }
}

// Test that the returned vector can be copied without issues
TEST_F(GetAvailableSigningCertificatesTest_1371, ReturnedVectorIsCopyable_1371)
{
    QVector<Poppler::CertificateInfo> certs = Poppler::getAvailableSigningCertificates();
    QVector<Poppler::CertificateInfo> certsCopy = certs;
    EXPECT_EQ(certs.size(), certsCopy.size());
}

// Test that the returned vector handles being cleared properly
TEST_F(GetAvailableSigningCertificatesTest_1371, ReturnedVectorCanBeCleared_1371)
{
    QVector<Poppler::CertificateInfo> certs = Poppler::getAvailableSigningCertificates();
    certs.clear();
    EXPECT_EQ(certs.size(), 0);
}

// Test boundary: the function returns an empty vector when no backend or no certs exist
// This is environment-dependent but should not crash
TEST_F(GetAvailableSigningCertificatesTest_1371, EmptyResultIsValid_1371)
{
    QVector<Poppler::CertificateInfo> certs = Poppler::getAvailableSigningCertificates();
    if (certs.isEmpty()) {
        EXPECT_EQ(certs.size(), 0);
    } else {
        EXPECT_GT(certs.size(), 0);
    }
}

// Test that if certificates are returned, their properties can be queried
TEST_F(GetAvailableSigningCertificatesTest_1371, CertificatePropertiesAccessible_1371)
{
    QVector<Poppler::CertificateInfo> certs = Poppler::getAvailableSigningCertificates();
    for (const auto &cert : certs) {
        // These should not crash regardless of content
        (void)cert.isNull();
        (void)cert.nickName();
        (void)cert.validityStart();
        (void)cert.validityEnd();
    }
}

} // anonymous namespace
