#include <gtest/gtest.h>

// Include the necessary headers
#include "poppler-form.h"

// We need access to the function under test. Since hasGPGBackendFeature is static
// (file-local linkage) in the .cc file, we need to include the .cc file directly
// to test it, or it must be exposed somehow. Given the constraints, we include
// the implementation file to get access to the static function.
#include "poppler-form.cc"

namespace Poppler {

class HasGPGBackendFeatureTest_1377 : public ::testing::Test {
protected:
    // No setup needed
};

// Test that BackendAsksPassphrase feature returns true
TEST_F(HasGPGBackendFeatureTest_1377, BackendAsksPassphraseReturnsTrue_1377)
{
    bool result = hasGPGBackendFeature(CryptoSignBackendFeature::BackendAsksPassphrase);
    EXPECT_TRUE(result);
}

// Test that the explicit enum value 0 (which corresponds to BackendAsksPassphrase) returns true
TEST_F(HasGPGBackendFeatureTest_1377, ExplicitEnumValueZeroReturnsTrue_1377)
{
    bool result = hasGPGBackendFeature(static_cast<CryptoSignBackendFeature>(0));
    EXPECT_TRUE(result);
}

// Test that an unknown/invalid feature value returns false (boundary: value 1)
TEST_F(HasGPGBackendFeatureTest_1377, UnknownFeatureValue1ReturnsFalse_1377)
{
    bool result = hasGPGBackendFeature(static_cast<CryptoSignBackendFeature>(1));
    EXPECT_FALSE(result);
}

// Test that an unknown/invalid feature value returns false (boundary: value -1)
TEST_F(HasGPGBackendFeatureTest_1377, UnknownFeatureValueNegativeReturnsFalse_1377)
{
    bool result = hasGPGBackendFeature(static_cast<CryptoSignBackendFeature>(-1));
    EXPECT_FALSE(result);
}

// Test that a large unknown feature value returns false
TEST_F(HasGPGBackendFeatureTest_1377, UnknownFeatureLargeValueReturnsFalse_1377)
{
    bool result = hasGPGBackendFeature(static_cast<CryptoSignBackendFeature>(999));
    EXPECT_FALSE(result);
}

// Test that another arbitrary unknown feature value returns false
TEST_F(HasGPGBackendFeatureTest_1377, UnknownFeatureValue42ReturnsFalse_1377)
{
    bool result = hasGPGBackendFeature(static_cast<CryptoSignBackendFeature>(42));
    EXPECT_FALSE(result);
}

// Test consistency - calling multiple times with same argument yields same result
TEST_F(HasGPGBackendFeatureTest_1377, ConsistentResultsOnRepeatedCalls_1377)
{
    bool result1 = hasGPGBackendFeature(CryptoSignBackendFeature::BackendAsksPassphrase);
    bool result2 = hasGPGBackendFeature(CryptoSignBackendFeature::BackendAsksPassphrase);
    EXPECT_EQ(result1, result2);
    EXPECT_TRUE(result1);
}

} // namespace Poppler
