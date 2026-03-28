// TEST_ID: 774

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>

// Catch2 headers (interfaces + reporter)
#include <catch2/reporters/catch_reporter_console.hpp>
#include <catch2/interfaces/catch_interfaces_config.hpp>
#include <catch2/internal/catch_test_run_info.hpp>

// If your repo exposes the test spec parser publicly, include it to build a spec with filters.
// If not available in your layout, you can drop the second test or use whatever builder your tree provides.
#include <catch2/internal/catch_test_spec_parser.hpp>   // adjust include path if needed

using ::testing::Return;
using ::testing::ReturnRef;
using ::testing::NiceMock;

namespace {

// Minimal mock for IConfig, mocking only what we observe through the public interface here.
class MockConfig : public Catch::IConfig {
public:
    // The interface declarations in the provided snippet are odd (e.g., "const" on return types),
    // but in practice these work fine as non-const by-value returns in mocks.

    MOCK_METHOD(uint32_t, rngSeed, (), (override));
    MOCK_METHOD((const Catch::TestSpec&), testSpec, (), (override));

    // All other virtuals keep their default (do-nothing) base implementations.
};

// Helper to construct a ConsoleReporter writing to an arbitrary std::ostream.
// In upstream Catch2 this ctor signature is available via ReporterConfig &&.
// If your local header differs slightly, adjust the ReporterConfig construction accordingly.
static std::unique_ptr<Catch::ConsoleReporter>
makeConsoleReporter(Catch::IConfig* cfg, std::ostream& os) {
    // ReporterConfig lives alongside reporter base helpers in Catch2 v3.
    // There is a ReporterConfig that can be constructed from (IConfig*, std::ostream&, ColourMode, customOptions).
    Catch::ReporterConfig rc{
        cfg,
        os,
        Catch::ColourMode::None, // keep output free from ANSI codes to simplify assertions
        {}
    };
    return std::make_unique<Catch::ConsoleReporter>(CATCH_MOVE(rc));
}

// Build a TestSpec with at least one filter using the public parser,
// so that hasFilters() returns true without peeking into internals.
static Catch::TestSpec makeSpecWithAnyFilter(Catch::IConfig* cfg) {
    Catch::TestSpecParser parser{cfg};
    // Any token that creates a filter is fine. "[foo]" is a tag expression in Catch2.
    parser.parse("[foo]");
    return parser.testSpec();
}

} // namespace

// =============== Tests ===============

TEST(ConsoleReporter_TestRunStarting_NoFilters_PrintsSeed_774, NoFilters_PrintsOnlySeedLine) {
    NiceMock<MockConfig> cfg;
    std::ostringstream oss;

    // Default-constructed TestSpec should have no filters.
    const Catch::TestSpec emptySpec;
    ON_CALL(cfg, testSpec()).WillByDefault(ReturnRef(emptySpec));

    // Choose a distinctive seed to make matching robust.
    ON_CALL(cfg, rngSeed()).WillByDefault(Return(424242u));

    auto reporter = makeConsoleReporter(&cfg, oss);

    const Catch::TestRunInfo tri{"run"_sr};
    reporter->testRunStarting(tri);

    const std::string out = oss.str();

    // Should NOT print the Filters line if there are no filters
    EXPECT_THAT(out, ::testing::Not(::testing::HasSubstr("Filters:")));

    // Should always print the seed line
    EXPECT_THAT(out, ::testing::HasSubstr("Randomness seeded to: 424242"));

    // And should end that line with a newline
    // (we don't assert it's the very last character, just that a newline follows that segment somewhere)
    EXPECT_THAT(out, ::testing::HasSubstr("Randomness seeded to: 424242\n"));
}

TEST(ConsoleReporter_TestRunStarting_WithFilters_PrintsFiltersAndSeed_774, WithFilters_PrintsFiltersThenSeedLine) {
    NiceMock<MockConfig> cfg;
    std::ostringstream oss;

    // Build a spec that definitely reports hasFilters() == true via the public parser API
    // (no internal state assumptions).
    // Keep it alive for the full duration of the call since testSpec() returns by reference.
    static Catch::TestSpec specWithFilter = makeSpecWithAnyFilter(&cfg);
    ON_CALL(cfg, testSpec()).WillByDefault(ReturnRef(specWithFilter));

    ON_CALL(cfg, rngSeed()).WillByDefault(Return(17u));

    auto reporter = makeConsoleReporter(&cfg, oss);

    const Catch::TestRunInfo tri{"run"_sr};
    reporter->testRunStarting(tri);

    const std::string out = oss.str();

    // With filters, the reporter prints a Filters line.
    // We do not assert exact formatting/colour codes; just presence of the user-visible token.
    EXPECT_THAT(out, ::testing::HasSubstr("Filters:"));

    // The seed line must still be printed afterwards.
    EXPECT_THAT(out, ::testing::HasSubstr("Randomness seeded to: 17"));

    // Both lines end with '\n'. We only check the seed line explicitly; the Filters line
    // may include colour manipulator output before the word "Filters:".
    EXPECT_THAT(out, ::testing::HasSubstr("Randomness seeded to: 17\n"));
}
