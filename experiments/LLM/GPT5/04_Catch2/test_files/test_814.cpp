// File: tests/compact_reporter_assertionEnded_814_tests.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <memory>

// --- Catch2 public headers (paths follow the repository layout you provided) ---
#include "Catch2/src/catch2/reporters/catch_reporter_compact.hpp"
#include "Catch2/src/catch2/reporters/catch_reporter_common_base.hpp"
#include "Catch2/src/catch2/interfaces/catch_interfaces_config.hpp"
#include "Catch2/src/catch2/interfaces/catch_interfaces_reporter.hpp"
#include "Catch2/src/catch2/catch_assertion_result.hpp"
#include "Catch2/src/catch2/internal/catch_result_type.hpp"
// If your tree splits stream/colour helpers, you might need:
// #include "Catch2/src/catch2/internal/catch_stream.hpp"
// #include "Catch2/src/catch2/internal/catch_colour.hpp"
// #include "Catch2/src/catch2/reporters/catch_reporter_helpers.hpp"

using ::testing::Return;
using ::testing::NiceMock;

namespace {

//
// Minimal adapter that lets ReporterBase write into an ostringstream
//
class OStringStreamAdapter : public Catch::IStream {
public:
    explicit OStringStreamAdapter(std::ostringstream& oss)
        : m_oss(oss) {}
    std::ostream& stream() override { return m_oss; }
private:
    std::ostringstream& m_oss;
};

//
// Mock for IConfig, we only need includeSuccessfulResults() for these tests
//
class MockConfig_814 : public Catch::IConfig {
public:
    MOCK_METHOD(bool, includeSuccessfulResults, (), (const, override));
    // The rest of IConfig virtuals are not used by the code paths under test.
    // They can remain with base defaults.
};

//
// Small helpers to build AssertionResult/AssertionStats with public types only
//
static Catch::AssertionInfo makeInfo_814(
    const char* macro = "REQUIRE",
    const char* file  = "file.cpp",
    std::size_t line  = 1,
    Catch::ResultDisposition::Flags disp = Catch::ResultDisposition::Normal) {

    return Catch::AssertionInfo{
        Catch::StringRef{macro},
        Catch::SourceLineInfo{file, static_cast<std::uint32_t>(line)},
        Catch::StringRef{}, // captured expression (unused by these tests)
        disp
    };
}

// If your version provides AssertionResultBuilder, prefer it. Otherwise,
// construct AssertionResultData minimally (constructor signatures vary a bit
// across versions; adjust here if your tree differs).
static Catch::AssertionResult makeResult_814(Catch::ResultWas::OfType type) {
    using namespace Catch;

    const auto info = makeInfo_814();

    // ---- Adjust this block if your local AssertionResultData ctor differs ----
    AssertionResultData data;
    // Public, writable field in Catch2 v3:
    data.resultType = type;
    // -------------------------------------------------------------------------

    return AssertionResult(info, std::move(data));
}

static Catch::AssertionStats makeStats_814(Catch::ResultWas::OfType type) {
    using namespace Catch;
    AssertionResult res = makeResult_814(type);
    std::vector<MessageInfo> messages;
    Totals totals; // default totals are fine; not observed here
    return AssertionStats(res, messages, totals);
}

//
// Fixture that wires CompactReporter to a capture stream.
//
class CompactReporterAssertionEndedTest_814 : public ::testing::Test {
protected:
    std::ostringstream oss;                             // where reporter writes
    NiceMock<MockConfig_814> mockCfg;                   // controls includeSuccessfulResults

    // Helper to build a ready-to-use CompactReporter with our stream/config
    std::unique_ptr<Catch::CompactReporter> makeReporter() {
        using namespace Catch;

        // Wrap our ostringstream so ReporterBase can use it via IStream
        Detail::unique_ptr<IStream> wrapped(new OStringStreamAdapter(oss));

        // ReporterConfig interface: fullConfig(), takeStream(), colourMode(), customOptions()
        // If your tree needs a different header for ReporterConfig, include it above.
        ReporterConfig rc(
            &mockCfg,                 // full config
            std::move(wrapped),       // stream
            ColourMode::None,         // no colouring for stable tests
            {}                        // no custom options
        );

        return std::unique_ptr<CompactReporter>(new CompactReporter(std::move(rc)));
    }
};

//
// TESTS
//

// When successes are hidden and the result is a clean success (not Warning/ExplicitSkip),
// CompactReporter::assertionEnded returns early and writes nothing (no newline).
TEST_F(CompactReporterAssertionEndedTest_814, SuccessHidden_Ok_EarlyReturn_NoOutput_814) {
    using namespace Catch;

    EXPECT_CALL(mockCfg, includeSuccessfulResults()).WillRepeatedly(Return(false));

    auto uut = makeReporter();
    auto stats = makeStats_814(ResultWas::Ok);

    uut->assertionEnded(stats);

    EXPECT_TRUE(oss.str().empty()) << "Expected no output when successes are hidden and result is Ok.";
}

// When successes are hidden but the result is Warning, it should still print (with info messages suppressed),
// and at least a newline is pushed after printing.
TEST_F(CompactReporterAssertionEndedTest_814, SuccessHidden_Warning_Prints_Newline_814) {
    using namespace Catch;

    EXPECT_CALL(mockCfg, includeSuccessfulResults()).WillRepeatedly(Return(false));

    auto uut = makeReporter();
    auto stats = makeStats_814(ResultWas::Warning);

    uut->assertionEnded(stats);

    const std::string out = oss.str();
    ASSERT_FALSE(out.empty()) << "Expected output for Warning even when successes are hidden.";
    EXPECT_EQ(out.back(), '\n') << "CompactReporter should append a trailing newline.";
}

// When successes are hidden but the result is ExplicitSkip, it should still print,
// and at least a newline is pushed after printing.
TEST_F(CompactReporterAssertionEndedTest_814, SuccessHidden_ExplicitSkip_Prints_Newline_814) {
    using namespace Catch;

    EXPECT_CALL(mockCfg, includeSuccessfulResults()).WillRepeatedly(Return(false));

    auto uut = makeReporter();
    auto stats = makeStats_814(ResultWas::ExplicitSkip);

    uut->assertionEnded(stats);

    const std::string out = oss.str();
    ASSERT_FALSE(out.empty()) << "Expected output for ExplicitSkip even when successes are hidden.";
    EXPECT_EQ(out.back(), '\n');
}

// When successes are shown, a clean Ok result should be printed (and newline appended).
TEST_F(CompactReporterAssertionEndedTest_814, SuccessShown_Ok_Prints_Newline_814) {
    using namespace Catch;

    EXPECT_CALL(mockCfg, includeSuccessfulResults()).WillRepeatedly(Return(true));

    auto uut = makeReporter();
    auto stats = makeStats_814(ResultWas::Ok);

    uut->assertionEnded(stats);

    const std::string out = oss.str();
    ASSERT_FALSE(out.empty()) << "Expected output when successes are shown.";
    EXPECT_EQ(out.back(), '\n');
}

} // namespace
