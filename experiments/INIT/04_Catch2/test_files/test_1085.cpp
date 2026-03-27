// File: tests/sonarqube_reporter_constructor_1085.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>
#include <map>

// Catch2 headers (paths may need to match your project layout)
#include "catch2/reporters/catch_reporter_sonarqube.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"

namespace {

using namespace Catch;

// Minimal external collaborator for the ReporterConfig stream.
// We keep this as a simple concrete IStream that wraps an ostringstream.
class OStringStreamWrapper : public IStream {
public:
    std::ostream& stream() override { return oss_; }
private:
    std::ostringstream oss_;
};

// Helper to make a valid ReporterConfig without relying on IConfig
// (the reporter only stores the pointer; it does not use it in the ctor path we test).
static ReporterConfig makeConfig() {
    Detail::unique_ptr<IStream> ptr(new OStringStreamWrapper());
    // ColourMode value is not relevant for these tests; use 0 safely.
    return ReporterConfig(
        /*_fullConfig=*/nullptr,
        std::move(ptr),
        static_cast<ColourMode>(0),
        std::map<std::string, std::string>{}
    );
}

} // namespace

// ============================= TESTS =============================

class SonarQubeReporterTest_1085 : public ::testing::Test {};

// Verifies constructor side-effects that are observable via the public interface:
// - shouldRedirectStdOut is true
// - shouldReportAllAssertions is false
TEST_F(SonarQubeReporterTest_1085, Constructor_SetsPreferences_1085) {
    // Arrange
    ReporterConfig cfg = makeConfig();

    // Act
    SonarQubeReporter uut(std::move(cfg));

    // Assert (observable via IEventListener::getPreferences)
    const ReporterPreferences& prefs = uut.getPreferences();
    EXPECT_TRUE(prefs.shouldRedirectStdOut) << "SonarQubeReporter should redirect stdout";
    EXPECT_FALSE(prefs.shouldReportAllAssertions) << "SonarQubeReporter should not report all assertions";
}

// Sanity check: constructing with a valid ReporterConfig should not throw.
TEST_F(SonarQubeReporterTest_1085, Constructor_DoesNotThrow_1085) {
    ReporterConfig cfg = makeConfig();
    EXPECT_NO_THROW({
        SonarQubeReporter uut(std::move(cfg));
        (void)uut; // suppress unused warning
    });
}
