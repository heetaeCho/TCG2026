#include <gtest/gtest.h>
#include <QVector>

// Include the necessary Poppler headers
#include "poppler-form.h"
#include "poppler-qt5.h"

namespace {

// Test that availableCryptoSignBackends returns a QVector (normal operation)
TEST(AvailableCryptoSignBackendsTest_1374, ReturnsQVector_1374)
{
    QVector<Poppler::CryptoSignBackend> backends = Poppler::availableCryptoSignBackends();
    // The function should return without crashing; the result is a valid QVector
    // We can't assert exact contents since it depends on system configuration,
    // but it should be a non-negative size
    EXPECT_GE(backends.size(), 0);
}

// Test that calling the function multiple times returns consistent results
TEST(AvailableCryptoSignBackendsTest_1374, ConsistentResults_1374)
{
    QVector<Poppler::CryptoSignBackend> backends1 = Poppler::availableCryptoSignBackends();
    QVector<Poppler::CryptoSignBackend> backends2 = Poppler::availableCryptoSignBackends();
    
    EXPECT_EQ(backends1.size(), backends2.size());
    for (int i = 0; i < backends1.size(); ++i) {
        EXPECT_EQ(backends1[i], backends2[i]);
    }
}

// Test that all returned backends are valid enum values
TEST(AvailableCryptoSignBackendsTest_1374, AllReturnedBackendsAreValid_1374)
{
    QVector<Poppler::CryptoSignBackend> backends = Poppler::availableCryptoSignBackends();
    
    for (const auto &backend : backends) {
        // Each backend should be one of the known CryptoSignBackend enum values
        // At minimum, the value should be representable as the enum type
        // We verify it's a known value by checking it can be cast to int without issue
        int val = static_cast<int>(backend);
        EXPECT_GE(val, 0);
    }
}

// Test that there are no duplicates in the returned backends
TEST(AvailableCryptoSignBackendsTest_1374, NoDuplicateBackends_1374)
{
    QVector<Poppler::CryptoSignBackend> backends = Poppler::availableCryptoSignBackends();
    
    for (int i = 0; i < backends.size(); ++i) {
        for (int j = i + 1; j < backends.size(); ++j) {
            EXPECT_NE(backends[i], backends[j])
                << "Duplicate backend found at indices " << i << " and " << j;
        }
    }
}

// Test boundary: the returned vector size does not exceed a reasonable limit
// (there are only a few known crypto backends)
TEST(AvailableCryptoSignBackendsTest_1374, ReasonableNumberOfBackends_1374)
{
    QVector<Poppler::CryptoSignBackend> backends = Poppler::availableCryptoSignBackends();
    
    // There shouldn't be more backends than what's defined in the enum
    // Typically NSS and GPG are the known backends, so a reasonable upper bound
    EXPECT_LE(backends.size(), 10);
}

} // namespace
