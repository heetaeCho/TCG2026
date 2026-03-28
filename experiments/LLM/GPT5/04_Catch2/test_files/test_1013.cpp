// File: tests/isThrowSafe_1013_tests.cpp

#include <gtest/gtest.h>

// Catch2 public headers used by the function under test
#include "catch2/catch_test_case_info.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"

// The function under test (declared in amalgamated, defined in namespace Catch)
namespace Catch {
    bool isThrowSafe(TestCaseHandle const& testCase, IConfig const& config);
}

// Minimal concrete config to control allowThrows(), other virtuals return dummies.
class StubConfig final : public Catch::IConfig {
public:
    explicit StubConfig(bool allow) : allow_(allow) {}

    // Only behavior we care about in these tests
    bool allowThrows() const override { return allow_; }

    // The remainder are stubbed to satisfy the interface; they are not used
    Catch::StringRef name() const override { static Catch::StringRef n(""); return n; }
    bool includeSuccessfulResults() const override { return false; }
    bool shouldDebugBreak() const override { return false; }
    bool warnAboutMissingAssertions() const override { return false; }
    bool warnAboutUnmatchedTestSpecs() const override { return false; }
    bool zeroTestsCountAsSuccess() const override { return false; }
    int abortAfter() const override { return 0; }
    bool showInvisibles() const override { return false; }
    Catch::ShowDurations showDurations() const override { return Catch::ShowDurations::DefaultForReporter; }
    double minDuration() const override { return 0.0; }
    Catch::TestSpec const& testSpec() const override {
        static Catch::TestSpec spec;
        return spec;
    }
    bool hasTestFilters() const override { return false; }
    std::vector<std::string> const& getTestsOrTags() const override {
        static std::vector<std::string> v;
        return v;
    }
    Catch::TestRunOrder runOrder() const override { return Catch::TestRunOrder::Declared; }
    std::uint32_t rngSeed() const override { return 0u; }
    unsigned int shardCount() const override { return 1u; }
    unsigned int shardIndex() const override { return 0u; }
    Catch::ColourMode defaultColourMode() const override { return Catch::ColourMode::PlatformDefault; }
    std::vector<std::string> const& getSectionsToRun() const override {
        static std::vector<std::string> v;
        return v;
    }
    Catch::Verbosity verbosity() const override { return Catch::Verbosity::Normal; }
    bool skipBenchmarks() const override { return false; }
    bool benchmarkNoAnalysis() const override { return false; }
    unsigned int benchmarkSamples() const override { return 0u; }
    double benchmarkConfidenceInterval() const override { return 0.0; }
    unsigned int benchmarkResamples() const override { return 0u; }
    std::chrono::milliseconds benchmarkWarmupTime() const override { return std::chrono::milliseconds{0}; }

private:
    bool allow_;
};

// Test fixture that owns the TestCaseInfo backing storage used by TestCaseHandle
class IsThrowSafeTest_1013 : public ::testing::Test {
protected:
    // Helper to construct a TestCaseHandle whose TestCaseInfo indicates throws/non-throws
    Catch::TestCaseHandle makeHandle(bool shouldThrow) {
        // Build minimal NameAndTags and SourceLineInfo for TestCaseInfo ctor
        Catch::NameAndTags nt;
        nt.name = "dummy_test";
        nt.tags = "";

        Catch::SourceLineInfo sli{__FILE__, static_cast<std::size_t>(__LINE__)};

        // Allocate the TestCaseInfo we will keep alive for the duration of the handle
        info_ = std::make_unique<Catch::TestCaseInfo>(Catch::StringRef("DummyClass"), nt, sli);

        // Set the public 'properties' to control throws() observable behavior
        using Props = Catch::TestCaseProperties;
        info_->properties = shouldThrow ? (Props)(Props::Throws) : Props::None;

        // ITestInvoker is irrelevant to isThrowSafe; nullptr is fine as we never invoke.
        return Catch::TestCaseHandle(info_.get(), /*invoker*/ nullptr);
    }

    std::unique_ptr<Catch::TestCaseInfo> info_;
};

// ========== Tests ==========

TEST_F(IsThrowSafeTest_1013, NonThrowing_ConfigDisallows_ReturnsTrue_1013) {
    auto handle = makeHandle(/*shouldThrow=*/false);
    StubConfig cfg(/*allow=*/false);

    // For non-throwing tests, isThrowSafe should be true regardless of config
    EXPECT_TRUE(Catch::isThrowSafe(handle, cfg));
}

TEST_F(IsThrowSafeTest_1013, NonThrowing_ConfigAllows_ReturnsTrue_1013) {
    auto handle = makeHandle(/*shouldThrow=*/false);
    StubConfig cfg(/*allow=*/true);

    EXPECT_TRUE(Catch::isThrowSafe(handle, cfg));
}

TEST_F(IsThrowSafeTest_1013, Throwing_ConfigAllows_ReturnsTrue_1013) {
    auto handle = makeHandle(/*shouldThrow=*/true);
    StubConfig cfg(/*allow=*/true);

    // throws() == true, but config allows throws -> safe
    EXPECT_TRUE(Catch::isThrowSafe(handle, cfg));
}

TEST_F(IsThrowSafeTest_1013, Throwing_ConfigDisallows_ReturnsFalse_1013) {
    auto handle = makeHandle(/*shouldThrow=*/true);
    StubConfig cfg(/*allow=*/false);

    // throws() == true and config disallows throws -> unsafe
    EXPECT_FALSE(Catch::isThrowSafe(handle, cfg));
}
