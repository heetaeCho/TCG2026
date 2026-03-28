#include <gtest/gtest.h>

// Include the header that declares the enum and the function we're testing
#include "poppler-form.h"

// We need access to the function under test. Since hasNSSBackendFeature is declared
// as static in the .cc file, we need to include the .cc to access it in tests.
// This is a common pattern for testing static (file-scope) functions.
#include "poppler-form.cc"

namespace Poppler {

class HasNSSBackendFeatureTest_1376 : public ::testing::Test {
protected:
};

// Test that BackendAsksPassphrase returns false
TEST_F(HasNSSBackendFeatureTest_1376, BackendAsksPassphraseReturnsFalse_1376)
{
    bool result = hasNSSBackendFeature(CryptoSignBackendFeature::BackendAsksPassphrase);
    EXPECT_FALSE(result);
}

// Test that the enum value 0 (which corresponds to BackendAsksPassphrase) returns false
TEST_F(HasNSSBackendFeatureTest_1376, EnumValueZeroReturnsFalse_1376)
{
    bool result = hasNSSBackendFeature(static_cast<CryptoSignBackendFeature>(0));
    EXPECT_FALSE(result);
}

// Test that an unknown/invalid enum value returns false (default case in switch)
TEST_F(HasNSSBackendFeatureTest_1376, UnknownFeatureReturnsFalse_1376)
{
    bool result = hasNSSBackendFeature(static_cast<CryptoSignBackendFeature>(1));
    EXPECT_FALSE(result);
}

// Test with another out-of-range enum value
TEST_F(HasNSSBackendFeatureTest_1376, OutOfRangePositiveValueReturnsFalse_1376)
{
    bool result = hasNSSBackendFeature(static_cast<CryptoSignBackendFeature>(999));
    EXPECT_FALSE(result);
}

// Test with a negative out-of-range enum value
TEST_F(HasNSSBackendFeatureTest_1376, NegativeEnumValueReturnsFalse_1376)
{
    bool result = hasNSSBackendFeature(static_cast<CryptoSignBackendFeature>(-1));
    EXPECT_FALSE(result);
}

// Test that calling the function multiple times yields consistent results
TEST_F(HasNSSBackendFeatureTest_1376, ConsistentResultsOnMultipleCalls_1376)
{
    bool result1 = hasNSSBackendFeature(CryptoSignBackendFeature::BackendAsksPassphrase);
    bool result2 = hasNSSBackendFeature(CryptoSignBackendFeature::BackendAsksPassphrase);
    EXPECT_EQ(result1, result2);
    EXPECT_FALSE(result1);
}

} // namespace Poppler
