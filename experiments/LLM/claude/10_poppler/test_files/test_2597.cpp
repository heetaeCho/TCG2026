#include <gtest/gtest.h>

// Include the necessary headers
#include "poppler.h"

// Declaration of the function under test
extern "C" PopplerBackend poppler_get_backend(void);

class PopplerBackendTest_2597 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that poppler_get_backend returns POPPLER_BACKEND_CAIRO
TEST_F(PopplerBackendTest_2597, ReturnsBackendCairo_2597)
{
    PopplerBackend backend = poppler_get_backend();
    EXPECT_EQ(backend, POPPLER_BACKEND_CAIRO);
}

// Test that the returned value is not POPPLER_BACKEND_UNKNOWN
TEST_F(PopplerBackendTest_2597, DoesNotReturnUnknown_2597)
{
    PopplerBackend backend = poppler_get_backend();
    EXPECT_NE(backend, POPPLER_BACKEND_UNKNOWN);
}

// Test that the returned value is not POPPLER_BACKEND_SPLASH
TEST_F(PopplerBackendTest_2597, DoesNotReturnSplash_2597)
{
    PopplerBackend backend = poppler_get_backend();
    EXPECT_NE(backend, POPPLER_BACKEND_SPLASH);
}

// Test that the numeric value matches the expected enum value for CAIRO (2)
TEST_F(PopplerBackendTest_2597, ReturnValueMatchesCairoNumericValue_2597)
{
    PopplerBackend backend = poppler_get_backend();
    EXPECT_EQ(static_cast<int>(backend), 2);
}

// Test that calling the function multiple times yields consistent results
TEST_F(PopplerBackendTest_2597, ConsistentAcrossMultipleCalls_2597)
{
    PopplerBackend first = poppler_get_backend();
    PopplerBackend second = poppler_get_backend();
    PopplerBackend third = poppler_get_backend();
    EXPECT_EQ(first, second);
    EXPECT_EQ(second, third);
}

// Test that the returned value is a valid PopplerBackend enum value
TEST_F(PopplerBackendTest_2597, ReturnsValidEnumValue_2597)
{
    int backend = static_cast<int>(poppler_get_backend());
    EXPECT_GE(backend, POPPLER_BACKEND_UNKNOWN);
    EXPECT_LE(backend, POPPLER_BACKEND_CAIRO);
}
