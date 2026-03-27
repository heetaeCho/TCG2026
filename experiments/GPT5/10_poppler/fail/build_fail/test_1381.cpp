#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace Poppler {
    bool arePgpSignaturesAllowed();
}

class PopplerTest_1381 : public ::testing::Test {
protected:
    // Any necessary setup can go here.
};

// Mock class for the external collaborator (if required)
class MockGpgSignatureConfiguration {
public:
    MOCK_METHOD(bool, arePgpSignaturesAllowed, (), (const));
};

TEST_F(PopplerTest_1381, ArePgpSignaturesAllowed_NormalOperation_1381) {
#if ENABLE_GPGME
    // Simulating the normal case where GpgSignatureConfiguration is available
    EXPECT_TRUE(Poppler::arePgpSignaturesAllowed());
#else
    // Simulating the scenario when GPGME is disabled, expecting false
    EXPECT_FALSE(Poppler::arePgpSignaturesAllowed());
#endif
}

TEST_F(PopplerTest_1381, ArePgpSignaturesAllowed_ErrorCase_1381) {
    // Since the function is a simple boolean return based on a macro, no real error condition exists.
    // The behavior can be checked based on the macro ENABLE_GPGME.
    #if !defined(ENABLE_GPGME)
    EXPECT_FALSE(Poppler::arePgpSignaturesAllowed());
    #else
    // Additional checks can be added if there is a way to trigger errors.
    // Example: If GpgSignatureConfiguration fails, this can be tested.
    #endif
}