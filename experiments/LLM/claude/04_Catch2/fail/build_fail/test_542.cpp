#include <catch2/internal/catch_output_redirect.hpp>
#include <catch2/internal/catch_unique_ptr.hpp>

#include <gtest/gtest.h>

namespace {

class MakeOutputRedirectTest_542 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that makeOutputRedirect with false returns a non-null pointer
TEST_F(MakeOutputRedirectTest_542, ReturnNonNullWhenActualIsFalse_542) {
    auto redirect = Catch::makeOutputRedirect(false);
    ASSERT_NE(redirect.get(), nullptr);
}

// Test that makeOutputRedirect with true returns a non-null pointer
TEST_F(MakeOutputRedirectTest_542, ReturnNonNullWhenActualIsTrue_542) {
    auto redirect = Catch::makeOutputRedirect(true);
    ASSERT_NE(redirect.get(), nullptr);
}

// Test that calling makeOutputRedirect(false) produces a valid OutputRedirect
// that can be used (NoopRedirect should not throw on redirect/restore operations)
TEST_F(MakeOutputRedirectTest_542, NoopRedirectIsUsable_542) {
    auto redirect = Catch::makeOutputRedirect(false);
    ASSERT_NE(redirect.get(), nullptr);
    // The NoopRedirect should handle redirect and restore without issues
    EXPECT_NO_THROW(redirect->activateStdout());
    EXPECT_NO_THROW(redirect->activateStderr());
    // Getting redirected output should return empty strings for noop
    auto stdoutOutput = redirect->getStdout();
    auto stderrOutput = redirect->getStderr();
    EXPECT_TRUE(stdoutOutput.empty());
    EXPECT_TRUE(stderrOutput.empty());
}

// Test that calling makeOutputRedirect(true) produces a valid OutputRedirect
// that can be used for actual redirection
TEST_F(MakeOutputRedirectTest_542, ActualRedirectIsUsable_542) {
    auto redirect = Catch::makeOutputRedirect(true);
    ASSERT_NE(redirect.get(), nullptr);
    // Should be able to activate without throwing
    EXPECT_NO_THROW(redirect->activateStdout());
    EXPECT_NO_THROW(redirect->activateStderr());
}

// Test that multiple calls to makeOutputRedirect return independent objects
TEST_F(MakeOutputRedirectTest_542, MultipleCallsReturnIndependentObjects_542) {
    auto redirect1 = Catch::makeOutputRedirect(false);
    auto redirect2 = Catch::makeOutputRedirect(false);
    ASSERT_NE(redirect1.get(), nullptr);
    ASSERT_NE(redirect2.get(), nullptr);
    EXPECT_NE(redirect1.get(), redirect2.get());
}

// Test that makeOutputRedirect(true) and makeOutputRedirect(false) return different types
// (observable through different behavior)
TEST_F(MakeOutputRedirectTest_542, TrueAndFalseReturnDifferentObjects_542) {
    auto noopRedirect = Catch::makeOutputRedirect(false);
    auto actualRedirect = Catch::makeOutputRedirect(true);
    ASSERT_NE(noopRedirect.get(), nullptr);
    ASSERT_NE(actualRedirect.get(), nullptr);
    // They should be different objects
    EXPECT_NE(noopRedirect.get(), actualRedirect.get());
}

// Test that NoopRedirect getStdout returns empty after activation
TEST_F(MakeOutputRedirectTest_542, NoopRedirectStdoutEmpty_542) {
    auto redirect = Catch::makeOutputRedirect(false);
    redirect->activateStdout();
    std::string captured = redirect->getStdout();
    EXPECT_EQ(captured, "");
}

// Test that NoopRedirect getStderr returns empty after activation
TEST_F(MakeOutputRedirectTest_542, NoopRedirectStderrEmpty_542) {
    auto redirect = Catch::makeOutputRedirect(false);
    redirect->activateStderr();
    std::string captured = redirect->getStderr();
    EXPECT_EQ(captured, "");
}

} // anonymous namespace
