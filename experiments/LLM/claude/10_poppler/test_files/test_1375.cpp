#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include the Poppler form header for the function under test
#include "poppler-form.h"
#include "poppler-qt5.h"

namespace {

class SetActiveCryptoSignBackendTest_1375 : public ::testing::Test {
protected:
    void SetUp() override {
        // Store available backends for use in tests
        availableBackends_ = Poppler::availableCryptoSignBackends();
    }

    QVector<Poppler::CryptoSignBackend> availableBackends_;
};

// Test that setting an available backend returns true
TEST_F(SetActiveCryptoSignBackendTest_1375, SetAvailableBackendReturnsTrue_1375) {
    if (availableBackends_.isEmpty()) {
        GTEST_SKIP() << "No crypto sign backends available, skipping test";
    }

    for (const auto &backend : availableBackends_) {
        bool result = Poppler::setActiveCryptoSignBackend(backend);
        EXPECT_TRUE(result) << "Setting an available backend should succeed";
    }
}

// Test that after setting an available backend, the active backend matches
TEST_F(SetActiveCryptoSignBackendTest_1375, ActiveBackendMatchesAfterSet_1375) {
    if (availableBackends_.isEmpty()) {
        GTEST_SKIP() << "No crypto sign backends available, skipping test";
    }

    for (const auto &backend : availableBackends_) {
        bool result = Poppler::setActiveCryptoSignBackend(backend);
        if (result) {
            auto active = Poppler::activeCryptoSignBackend();
            EXPECT_TRUE(active.has_value());
            if (active.has_value()) {
                EXPECT_EQ(active.value(), backend)
                    << "Active backend should match the one that was set";
            }
        }
    }
}

// Test that setting an unavailable/invalid backend returns false
TEST_F(SetActiveCryptoSignBackendTest_1375, SetUnavailableBackendReturnsFalse_1375) {
    // Use a backend value that is unlikely to be available
    // Cast a high integer to CryptoSignBackend to create an invalid one
    auto invalidBackend = static_cast<Poppler::CryptoSignBackend>(9999);
    
    // Only test if this value is truly not in available list
    if (!availableBackends_.contains(invalidBackend)) {
        bool result = Poppler::setActiveCryptoSignBackend(invalidBackend);
        EXPECT_FALSE(result) << "Setting an unavailable backend should fail";
    }
}

// Test that setting the same backend twice works consistently
TEST_F(SetActiveCryptoSignBackendTest_1375, SetSameBackendTwiceSucceeds_1375) {
    if (availableBackends_.isEmpty()) {
        GTEST_SKIP() << "No crypto sign backends available, skipping test";
    }

    auto backend = availableBackends_.first();
    bool result1 = Poppler::setActiveCryptoSignBackend(backend);
    bool result2 = Poppler::setActiveCryptoSignBackend(backend);
    
    EXPECT_EQ(result1, result2) << "Setting the same backend twice should give consistent results";
}

// Test that available backends list is consistent
TEST_F(SetActiveCryptoSignBackendTest_1375, AvailableBackendsConsistent_1375) {
    auto backends1 = Poppler::availableCryptoSignBackends();
    auto backends2 = Poppler::availableCryptoSignBackends();
    
    EXPECT_EQ(backends1.size(), backends2.size())
        << "Available backends should be consistent across calls";
    
    for (int i = 0; i < backends1.size(); ++i) {
        EXPECT_EQ(backends1[i], backends2[i]);
    }
}

// Test switching between different available backends
TEST_F(SetActiveCryptoSignBackendTest_1375, SwitchBetweenBackends_1375) {
    if (availableBackends_.size() < 2) {
        GTEST_SKIP() << "Need at least 2 backends to test switching";
    }

    auto backend1 = availableBackends_[0];
    auto backend2 = availableBackends_[1];

    EXPECT_TRUE(Poppler::setActiveCryptoSignBackend(backend1));
    auto active1 = Poppler::activeCryptoSignBackend();
    ASSERT_TRUE(active1.has_value());
    EXPECT_EQ(active1.value(), backend1);

    EXPECT_TRUE(Poppler::setActiveCryptoSignBackend(backend2));
    auto active2 = Poppler::activeCryptoSignBackend();
    ASSERT_TRUE(active2.has_value());
    EXPECT_EQ(active2.value(), backend2);
}

} // namespace
