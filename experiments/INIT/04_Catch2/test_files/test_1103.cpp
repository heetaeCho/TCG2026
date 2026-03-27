// File: tests/XmlReporter_1103.tests.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <memory>

// Include the Catch2 headers as provided by your codebase
// (paths follow your partials)
#include "catch2/reporters/catch_reporter_xml.hpp"
#include "catch2/reporters/catch_reporter_streaming_base.hpp"
#include "catch2/reporters/catch_reporter_common_base.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"

using ::testing::NiceMock;

namespace Catch {

// Minimal mock/fake collaborators kept strictly to public interfaces.

// Catch2 usually defines an IStream with a virtual std::ostream& stream()
struct FakeStream final : IStream {
    std::stringstream ss;
    std::ostream& stream() override { return ss; }
    ~FakeStream() override = default;
};

// IConfig is only stored/forwarded; we don't need any behavior.
class DummyConfig : public IConfig {
public:
    ~DummyConfig() override = default;
    // No methods are used by XmlReporter constructor path we test.
};

// Small helper to make a ReporterConfig with our fake stream.
// We avoid accessing any internal state; we only use public constructor.
static ReporterConfig MakeConfig(const IConfig* cfg = nullptr,
                                 ColourMode colour = ColourMode::PlatformDefault,
                                 std::map<std::string, std::string> custom = {}) {
    Detail::unique_ptr<IStream> sPtr(new FakeStream());
    return ReporterConfig(cfg, CATCH_MOVE(sPtr), colour, CATCH_MOVE(custom));
}

} // namespace Catch

// ---- Tests ----

class XmlReporterTest_1103 : public ::testing::Test {};

// Verifies the observable constructor side-effect on preferences:
// shouldRedirectStdOut and shouldReportAllAssertions must be true.
TEST_F(XmlReporterTest_1103, Constructor_SetsPreferencesTrue_1103) {
    using namespace Catch;

    auto cfg = MakeConfig(); // nullptr IConfig is acceptable for this path
    XmlReporter reporter(std::move(cfg));

    const auto& prefs = reporter.getPreferences();
    EXPECT_TRUE(prefs.shouldRedirectStdOut);
    EXPECT_TRUE(prefs.shouldReportAllAssertions);
}

// Sanity: constructing with a non-null IConfig should also succeed and
// still set the same public preferences (observable behavior).
TEST_F(XmlReporterTest_1103, Constructor_WithConfigPointer_StillSetsPrefs_1103) {
    using namespace Catch;

    DummyConfig dummyCfg; // external collaborator instance
    auto cfg = MakeConfig(&dummyCfg);
    XmlReporter reporter(std::move(cfg));

    const auto& prefs = reporter.getPreferences();
    EXPECT_TRUE(prefs.shouldRedirectStdOut);
    EXPECT_TRUE(prefs.shouldReportAllAssertions);
}

// Smoke: constructing with different ColourMode/custom options should not
// change the publicly observable constructor side-effects on preferences.
TEST_F(XmlReporterTest_1103, Constructor_WithVariousOptions_DoesNotChangePrefs_1103) {
    using namespace Catch;

    std::map<std::string, std::string> custom{{"x", "1"}, {"style", "compact"}};
    auto cfg = MakeConfig(nullptr, ColourMode::Light, custom);
    XmlReporter reporter(std::move(cfg));

    const auto& prefs = reporter.getPreferences();
    EXPECT_TRUE(prefs.shouldRedirectStdOut);
    EXPECT_TRUE(prefs.shouldReportAllAssertions);
}
