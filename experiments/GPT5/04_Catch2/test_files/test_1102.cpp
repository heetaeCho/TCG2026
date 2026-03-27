// File: tests/reporters/JunitReporter_Construct_1102.tests.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_junit.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"

// Minimal test double for Catch::IStream so ReporterConfig can own a stream.
namespace {
class FakeStream : public Catch::IStream {
public:
    std::ostream& stream() override { return oss_; }
private:
    std::ostringstream oss_;
};
} // namespace

// Common helper to build a ReporterConfig without relying on private state.
// We only use the public constructor and observable parameters.
static Catch::ReporterConfig makeConfig(
    const Catch::IConfig* cfg = nullptr,
    Catch::ColourMode colour = Catch::ColourMode::None,
    std::map<std::string, std::string> custom = {}
) {
    // Use the public ctor: ReporterConfig(IConfig*, unique_ptr<IStream>, ColourMode, map)
    return Catch::ReporterConfig(
        cfg,
        Catch::Detail::unique_ptr<Catch::IStream>(new FakeStream()),
        colour,
        std::move(custom)
    );
}

// =============== Tests ===============

TEST(JunitReporterTest_1102, Preferences_AreInitialized_AsSpecifiedByCtor_1102) {
    // Arrange
    auto cfg = makeConfig();

    // Act
    Catch::JunitReporter uut(std::move(cfg));

    // Assert (observable via IEventListener API)
    const Catch::ReporterPreferences& prefs = uut.getPreferences();
    EXPECT_TRUE(prefs.shouldRedirectStdOut);      // set true by JunitReporter ctor
    EXPECT_FALSE(prefs.shouldReportAllAssertions); // set false by JunitReporter ctor
}

TEST(JunitReporterTest_1102, Construction_Succeeds_WithNullConfig_AndVariousOptions_1102) {
    // Arrange: Use non-default colour & a custom option to ensure ctor robustness.
    std::map<std::string, std::string> custom { {"foo","bar"} };
    auto cfg = makeConfig(/*cfg*/nullptr, Catch::ColourMode::PlatformDefault, custom);

    // Act
    // The test’s goal is purely that construction works and observable prefs match
    // what JunitReporter guarantees in its own ctor.
    Catch::JunitReporter uut(std::move(cfg));

    // Assert (only observable behavior we can check from the public interface)
    const Catch::ReporterPreferences& prefs = uut.getPreferences();
    EXPECT_TRUE(prefs.shouldRedirectStdOut);
    EXPECT_FALSE(prefs.shouldReportAllAssertions);
}

// Notes:
// - We intentionally do NOT probe internal flags like m_shouldStoreSuccesfulAssertions,
//   because they are not exposed via the public interface. We only verify what is
//   observable: the ReporterPreferences returned by getPreferences().
// - We also avoid making assumptions about output, as the constructor should not
//   produce visible output and xml/stream internals are not exposed by the interface.
