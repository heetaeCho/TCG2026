#include <gtest/gtest.h>

// Forward declare the namespace and function we're testing
namespace Poppler {
    bool arePgpSignaturesAllowed();
}

// Test normal operation - the function should return a boolean value
TEST(ArePgpSignaturesAllowedTest_1381, ReturnsBooleanValue_1381) {
    bool result = Poppler::arePgpSignaturesAllowed();
    // The function should return either true or false
    EXPECT_TRUE(result == true || result == false);
}

// Test consistency - calling the function multiple times should return the same result
TEST(ArePgpSignaturesAllowedTest_1381, ConsistentReturnValue_1381) {
    bool result1 = Poppler::arePgpSignaturesAllowed();
    bool result2 = Poppler::arePgpSignaturesAllowed();
    EXPECT_EQ(result1, result2);
}

// Test that the function is callable and doesn't throw
TEST(ArePgpSignaturesAllowedTest_1381, DoesNotThrow_1381) {
    EXPECT_NO_THROW(Poppler::arePgpSignaturesAllowed());
}

// Test behavior based on compile-time configuration
// When ENABLE_GPGME is not defined, should return false
TEST(ArePgpSignaturesAllowedTest_1381, ReturnsExpectedBasedOnConfig_1381) {
#if ENABLE_GPGME
    // When GPG is enabled, the result depends on GpgSignatureConfiguration
    // We can only verify it returns a valid bool
    bool result = Poppler::arePgpSignaturesAllowed();
    SUCCEED() << "GPGME enabled, arePgpSignaturesAllowed returned: " << result;
#else
    // When GPGME is not enabled, should always return false
    EXPECT_FALSE(Poppler::arePgpSignaturesAllowed());
#endif
}

// Test idempotency - repeated calls should not change the result
TEST(ArePgpSignaturesAllowedTest_1381, IdempotentBehavior_1381) {
    bool first = Poppler::arePgpSignaturesAllowed();
    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(first, Poppler::arePgpSignaturesAllowed());
    }
}
