#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include "CryptoSignBackend.h"

// We need access to the createAvailableBackends function.
// Since it's declared static in the .cc file, we need to test through
// whatever public interface exposes it. However, based on the partial code,
// we test the Backend::Type enum and available backends through the public API.
// If createAvailableBackends is not directly accessible, we test what we can
// from the public header.

// Since createAvailableBackends is a static function in the .cc file,
// it may be used internally. We'll test the public-facing API that
// the CryptoSignBackend header exposes.

namespace {

// Test that Backend::Type enum values are as expected
TEST(CryptoSignBackendTest_1962, EnumNSS3HasValue0_1962)
{
    EXPECT_EQ(static_cast<int>(CryptoSign::Backend::Type::NSS3), 0);
}

TEST(CryptoSignBackendTest_1962, EnumGPGMEHasValue1_1962)
{
    EXPECT_EQ(static_cast<int>(CryptoSign::Backend::Type::GPGME), 1);
}

TEST(CryptoSignBackendTest_1962, EnumTypesAreDifferent_1962)
{
    EXPECT_NE(CryptoSign::Backend::Type::NSS3, CryptoSign::Backend::Type::GPGME);
}

// Test that we can create vectors of Backend::Type (simulating what createAvailableBackends does)
TEST(CryptoSignBackendTest_1962, BackendTypeCanBeStoredInVector_1962)
{
    std::vector<CryptoSign::Backend::Type> backends;
    backends.push_back(CryptoSign::Backend::Type::NSS3);
    backends.push_back(CryptoSign::Backend::Type::GPGME);
    EXPECT_EQ(backends.size(), 2u);
    EXPECT_EQ(backends[0], CryptoSign::Backend::Type::NSS3);
    EXPECT_EQ(backends[1], CryptoSign::Backend::Type::GPGME);
}

TEST(CryptoSignBackendTest_1962, EmptyBackendVector_1962)
{
    std::vector<CryptoSign::Backend::Type> backends;
    EXPECT_TRUE(backends.empty());
}

TEST(CryptoSignBackendTest_1962, BackendTypeComparison_1962)
{
    CryptoSign::Backend::Type t1 = CryptoSign::Backend::Type::NSS3;
    CryptoSign::Backend::Type t2 = CryptoSign::Backend::Type::NSS3;
    EXPECT_EQ(t1, t2);
}

TEST(CryptoSignBackendTest_1962, BackendTypeCopyAssignment_1962)
{
    CryptoSign::Backend::Type t1 = CryptoSign::Backend::Type::GPGME;
    CryptoSign::Backend::Type t2 = t1;
    EXPECT_EQ(t2, CryptoSign::Backend::Type::GPGME);
}

TEST(CryptoSignBackendTest_1962, BackendTypeSwitchCoverage_1962)
{
    CryptoSign::Backend::Type t = CryptoSign::Backend::Type::NSS3;
    bool matched = false;
    switch (t) {
    case CryptoSign::Backend::Type::NSS3:
        matched = true;
        break;
    case CryptoSign::Backend::Type::GPGME:
        matched = false;
        break;
    }
    EXPECT_TRUE(matched);
}

TEST(CryptoSignBackendTest_1962, BackendTypeSwitchGPGME_1962)
{
    CryptoSign::Backend::Type t = CryptoSign::Backend::Type::GPGME;
    bool matched = false;
    switch (t) {
    case CryptoSign::Backend::Type::NSS3:
        matched = false;
        break;
    case CryptoSign::Backend::Type::GPGME:
        matched = true;
        break;
    }
    EXPECT_TRUE(matched);
}

TEST(CryptoSignBackendTest_1962, FindBackendInVector_1962)
{
    std::vector<CryptoSign::Backend::Type> backends;
    backends.push_back(CryptoSign::Backend::Type::NSS3);
    
    auto it = std::find(backends.begin(), backends.end(), CryptoSign::Backend::Type::NSS3);
    EXPECT_NE(it, backends.end());
    
    auto it2 = std::find(backends.begin(), backends.end(), CryptoSign::Backend::Type::GPGME);
    EXPECT_EQ(it2, backends.end());
}

} // namespace
