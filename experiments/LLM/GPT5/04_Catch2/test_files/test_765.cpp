// File: tests/ConsoleReporter_assertionEnded_765.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>
#include <streambuf>
#include <memory>
#include <vector>

#include "catch2/reporters/catch_reporter_console.hpp"
#include "catch2/reporters/catch_reporter_common_base.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/catch_assertion_result.hpp"
#include "catch2/internal/catch_result_type.hpp"

// -----------------------------
// Test utilities & collaborators
// -----------------------------

using ::testing::Return;

namespace Catch {

// Minimal stream wrapper so ReporterConfig can own it.
struct OStreamWrapper : IStream {
    explicit OStreamWrapper(std::ostream& os) : m_os(&os) {}
    std::ostream& stream() override { return *m_os; }
    std::ostream* m_os;
};

// Simple MockConfig – we only need includeSuccessfulResults()
class MockConfig : public IConfig {
public:
    MOCK_METHOD(bool, includeSuccessfulResults, (), (const, override));
    // Other virtuals are non-pure in Catch2, so we don't need to override them here.
};

} // namespace Catch

// A stringbuf that counts flushes via sync()
struct SyncCountingStringBuf : public std::stringbuf {
    int sync_calls = 0;
    int sync() override {
        ++sync_calls;
        return std::stringbuf::sync();
    }
};

// Helper to build AssertionStats (uses Catch2’s public constructors)
static Catch::AssertionStats MakeStats(Catch::ResultWas::OfType type) {
    using namespace Catch;

    // Minimal assertion info/data sufficient to create a result.
    // Adjust names/fields if your local Catch2 variant differs.
    AssertionInfo info{
        StringRef("expr"),
        SourceLineInfo{"file.cpp", 123},
        StringRef("REQUIRE"),
        ResultDisposition::Normal
    };

    AssertionResultData data{ type };
    // For "ok" results, Catch2 usually treats Info/Warning/ExplicitSkip/Ok as "ok".
    // For failures, types like ExpressionFailed, ExplicitFailure, etc., are not ok.

    AssertionResult result{ info, CATCH_MOVE(data) };
    std::vector<MessageInfo> messages;
    Totals totals;

    return AssertionStats{ result, messages, totals };
}

// Fixture wires up a ConsoleReporter with a custom ostream and mock config
class ConsoleReporterAssertionEndedTest_765 : public ::testing::Test {
protected:
    void SetUp() override {
        // Route reporter output into our counting buffer
        os = std::make_unique<std::ostream>(&buf);

        // Build ReporterConfig with our stream + mock config
        // ReporterConfig in Catch2 v3 typically:
        // ReporterConfig(IConfig const* fullConfig,
        //                Detail::unique_ptr<IStream> stream,
        //                ColourMode colourMode,
        //                std::map<std::string, std::string> customOptions = {})
        auto streamPtr = Catch::Detail::unique_ptr<Catch::IStream>(
            new Catch::OStreamWrapper(*os));

        Catch::ReporterConfig cfg(
            &config,
            CATCH_MOVE(streamPtr),
            Catch::ColourMode::None,
            {} /* custom options */
        );

        reporter = std::make_unique<Catch::ConsoleReporter>(CATCH_MOVE(cfg));
    }

    // Convenience to get current buffer content
    std::string out() const { return buf.str(); }

    // Members
    SyncCountingStringBuf buf;
    std::unique_ptr<std::ostream> os;
    Catch::MockConfig config;
    std::unique_ptr<Catch::ConsoleReporter> reporter;
};

// ----------------------------------------------------
// Tests
// ----------------------------------------------------

// 1) Successful, non-special result (Info) suppressed if includeSuccessfulResults == false
TEST_F(ConsoleReporterAssertionEndedTest_765, Suppresses_Info_When_Success_Hidden_765) {
    EXPECT_CALL(config, includeSuccessfulResults()).WillOnce(Return(false));

    auto stats = MakeStats(Catch::ResultWas::Info);
    reporter->assertionEnded(stats);

    EXPECT_TRUE(out().empty()) << "Expected no output for Info when successful results are hidden";
    EXPECT_EQ(buf.sync_calls, 0) << "Expected no flush when early-return is taken";
}

// 2) Warning should always print (even if successful results are hidden)
TEST_F(ConsoleReporterAssertionEndedTest_765, Prints_For_Warning_Even_If_Success_Hidden_765) {
    EXPECT_CALL(config, includeSuccessfulResults()).WillOnce(Return(false));

    auto stats = MakeStats(Catch::ResultWas::Warning);
    reporter->assertionEnded(stats);

    ASSERT_FALSE(out().empty());
    EXPECT_EQ(out().back(), '\n') << "ConsoleReporter appends a newline after printer.print()";
    EXPECT_GE(buf.sync_calls, 1) << "Expected a flush due to std::flush";
}

// 3) ExplicitSkip should always print (even if successful results are hidden)
TEST_F(ConsoleReporterAssertionEndedTest_765, Prints_For_ExplicitSkip_Even_If_Success_Hidden_765) {
    EXPECT_CALL(config, includeSuccessfulResults()).WillOnce(Return(false));

    auto stats = MakeStats(Catch::ResultWas::ExplicitSkip);
    reporter->assertionEnded(stats);

    ASSERT_FALSE(out().empty());
    EXPECT_EQ(out().back(), '\n');
    EXPECT_GE(buf.sync_calls, 1);
}

// 4) Failure should print regardless of includeSuccessfulResults (isOk == false)
TEST_F(ConsoleReporterAssertionEndedTest_765, Prints_For_Failure_Regardless_Of_SuccessFlag_765) {
    EXPECT_CALL(config, includeSuccessfulResults()).WillOnce(Return(false));

    auto stats = MakeStats(Catch::ResultWas::ExpressionFailed);
    reporter->assertionEnded(stats);

    ASSERT_FALSE(out().empty());
    EXPECT_EQ(out().back(), '\n');
    EXPECT_GE(buf.sync_calls, 1);
}

// 5) Plain successful (Ok) prints only when includeSuccessfulResults == true
TEST_F(ConsoleReporterAssertionEndedTest_765, Ok_Prints_Only_When_Success_Enabled_765) {
    // First, hidden => suppressed
    {
        buf.str(""); buf.sync_calls = 0;
        EXPECT_CALL(config, includeSuccessfulResults()).WillOnce(Return(false));

        auto okStats = MakeStats(Catch::ResultWas::Ok);
        reporter->assertionEnded(okStats);

        EXPECT_TRUE(out().empty());
        EXPECT_EQ(buf.sync_calls, 0);
    }

    // Then, enabled => prints (note: set expectation again)
    {
        buf.str(""); buf.sync_calls = 0;
        EXPECT_CALL(config, includeSuccessfulResults()).WillOnce(Return(true));

        auto okStats = MakeStats(Catch::ResultWas::Ok);
        reporter->assertionEnded(okStats);

        ASSERT_FALSE(out().empty());
        EXPECT_EQ(out().back(), '\n');
        EXPECT_GE(buf.sync_calls, 1);
    }
}
