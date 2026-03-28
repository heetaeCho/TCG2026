#include <glib.h>
#include <gtest/gtest.h>
#include <string>
#include <vector>

// Include the error category enum
#include "poppler/Error.h"

// Declaration of the function under test
extern "C" {
void _poppler_error_cb(ErrorCategory category, Goffset pos, const char *message);
}

// Structure to capture log messages
struct LogMessage {
    std::string log_domain;
    GLogLevelFlags log_level;
    std::string message;
};

static std::vector<LogMessage> captured_logs;

// Custom log handler to capture g_log output
static void test_log_handler(const gchar *log_domain, GLogLevelFlags log_level, const gchar *message, gpointer user_data)
{
    LogMessage msg;
    msg.log_domain = log_domain ? log_domain : "";
    msg.log_level = log_level;
    msg.message = message ? message : "";
    captured_logs.push_back(msg);
}

class PopplerErrorCbTest_2599 : public ::testing::Test {
protected:
    guint handler_id;

    void SetUp() override
    {
        captured_logs.clear();
        // Install our custom log handler for the "Poppler" domain (G_LOG_DOMAIN in poppler-glib)
        handler_id = g_log_set_handler("Poppler", static_cast<GLogLevelFlags>(G_LOG_LEVEL_MASK | G_LOG_FLAG_FATAL | G_LOG_FLAG_RECURSION), test_log_handler, nullptr);
    }

    void TearDown() override
    {
        g_log_remove_handler("Poppler", handler_id);
        captured_logs.clear();
    }
};

// Test that errSyntaxWarning produces a log message with "Syntax warning"
TEST_F(PopplerErrorCbTest_2599, SyntaxWarningProducesLogMessage_2599)
{
    _poppler_error_cb(errSyntaxWarning, 100, "test warning");

    ASSERT_EQ(captured_logs.size(), 1u);
    EXPECT_EQ(captured_logs[0].log_level, G_LOG_LEVEL_INFO);
    EXPECT_NE(captured_logs[0].message.find("Syntax warning"), std::string::npos);
    EXPECT_NE(captured_logs[0].message.find("100"), std::string::npos);
    EXPECT_NE(captured_logs[0].message.find("test warning"), std::string::npos);
}

// Test that errSyntaxError produces a log message with "Syntax error"
TEST_F(PopplerErrorCbTest_2599, SyntaxErrorProducesLogMessage_2599)
{
    _poppler_error_cb(errSyntaxError, 200, "test error");

    ASSERT_EQ(captured_logs.size(), 1u);
    EXPECT_EQ(captured_logs[0].log_level, G_LOG_LEVEL_INFO);
    EXPECT_NE(captured_logs[0].message.find("Syntax error"), std::string::npos);
    EXPECT_NE(captured_logs[0].message.find("200"), std::string::npos);
    EXPECT_NE(captured_logs[0].message.find("test error"), std::string::npos);
}

// Test that errIO produces a log message with "IO error"
TEST_F(PopplerErrorCbTest_2599, IOErrorProducesLogMessage_2599)
{
    _poppler_error_cb(errIO, 300, "io problem");

    ASSERT_EQ(captured_logs.size(), 1u);
    EXPECT_EQ(captured_logs[0].log_level, G_LOG_LEVEL_INFO);
    EXPECT_NE(captured_logs[0].message.find("IO error"), std::string::npos);
    EXPECT_NE(captured_logs[0].message.find("300"), std::string::npos);
    EXPECT_NE(captured_logs[0].message.find("io problem"), std::string::npos);
}

// Test that errUnimplemented produces a log message with "Unimplemented feature"
TEST_F(PopplerErrorCbTest_2599, UnimplementedProducesLogMessage_2599)
{
    _poppler_error_cb(errUnimplemented, 400, "not implemented");

    ASSERT_EQ(captured_logs.size(), 1u);
    EXPECT_EQ(captured_logs[0].log_level, G_LOG_LEVEL_INFO);
    EXPECT_NE(captured_logs[0].message.find("Unimplemented feature"), std::string::npos);
    EXPECT_NE(captured_logs[0].message.find("400"), std::string::npos);
    EXPECT_NE(captured_logs[0].message.find("not implemented"), std::string::npos);
}

// Test that errInternal produces a log message with "Internal error"
TEST_F(PopplerErrorCbTest_2599, InternalErrorProducesLogMessage_2599)
{
    _poppler_error_cb(errInternal, 500, "internal issue");

    ASSERT_EQ(captured_logs.size(), 1u);
    EXPECT_EQ(captured_logs[0].log_level, G_LOG_LEVEL_INFO);
    EXPECT_NE(captured_logs[0].message.find("Internal error"), std::string::npos);
    EXPECT_NE(captured_logs[0].message.find("500"), std::string::npos);
    EXPECT_NE(captured_logs[0].message.find("internal issue"), std::string::npos);
}

// Test that errConfig is silently ignored (no log message produced)
TEST_F(PopplerErrorCbTest_2599, ConfigErrorIsIgnored_2599)
{
    _poppler_error_cb(errConfig, 0, "config error");

    EXPECT_EQ(captured_logs.size(), 0u);
}

// Test that errCommandLine is silently ignored (no log message produced)
TEST_F(PopplerErrorCbTest_2599, CommandLineErrorIsIgnored_2599)
{
    _poppler_error_cb(errCommandLine, 0, "command line error");

    EXPECT_EQ(captured_logs.size(), 0u);
}

// Test that errNotAllowed is silently ignored (no log message produced)
TEST_F(PopplerErrorCbTest_2599, NotAllowedErrorIsIgnored_2599)
{
    _poppler_error_cb(errNotAllowed, 0, "not allowed error");

    EXPECT_EQ(captured_logs.size(), 0u);
}

// Test with position 0 (boundary)
TEST_F(PopplerErrorCbTest_2599, ZeroPositionBoundary_2599)
{
    _poppler_error_cb(errSyntaxWarning, 0, "at start");

    ASSERT_EQ(captured_logs.size(), 1u);
    EXPECT_NE(captured_logs[0].message.find("0"), std::string::npos);
    EXPECT_NE(captured_logs[0].message.find("at start"), std::string::npos);
}

// Test with a large position value
TEST_F(PopplerErrorCbTest_2599, LargePositionValue_2599)
{
    Goffset large_pos = G_MAXINT64;
    _poppler_error_cb(errSyntaxError, large_pos, "large position");

    ASSERT_EQ(captured_logs.size(), 1u);
    EXPECT_NE(captured_logs[0].message.find("large position"), std::string::npos);
}

// Test with negative position value
TEST_F(PopplerErrorCbTest_2599, NegativePositionValue_2599)
{
    _poppler_error_cb(errSyntaxWarning, -1, "negative pos");

    ASSERT_EQ(captured_logs.size(), 1u);
    EXPECT_NE(captured_logs[0].message.find("negative pos"), std::string::npos);
    EXPECT_NE(captured_logs[0].message.find("-1"), std::string::npos);
}

// Test with an empty message string
TEST_F(PopplerErrorCbTest_2599, EmptyMessageString_2599)
{
    _poppler_error_cb(errIO, 42, "");

    ASSERT_EQ(captured_logs.size(), 1u);
    EXPECT_NE(captured_logs[0].message.find("IO error"), std::string::npos);
    EXPECT_NE(captured_logs[0].message.find("42"), std::string::npos);
}

// Test that log domain is "Poppler"
TEST_F(PopplerErrorCbTest_2599, LogDomainIsPoppler_2599)
{
    _poppler_error_cb(errInternal, 10, "domain check");

    ASSERT_EQ(captured_logs.size(), 1u);
    EXPECT_EQ(captured_logs[0].log_domain, "Poppler");
}

// Test that log level is G_LOG_LEVEL_INFO for all logging categories
TEST_F(PopplerErrorCbTest_2599, LogLevelIsInfo_2599)
{
    _poppler_error_cb(errSyntaxWarning, 1, "msg1");
    _poppler_error_cb(errSyntaxError, 2, "msg2");
    _poppler_error_cb(errIO, 3, "msg3");
    _poppler_error_cb(errUnimplemented, 4, "msg4");
    _poppler_error_cb(errInternal, 5, "msg5");

    ASSERT_EQ(captured_logs.size(), 5u);
    for (const auto &log : captured_logs) {
        EXPECT_EQ(log.log_level, G_LOG_LEVEL_INFO);
    }
}

// Test message format includes "at position"
TEST_F(PopplerErrorCbTest_2599, MessageFormatContainsAtPosition_2599)
{
    _poppler_error_cb(errSyntaxWarning, 999, "format check");

    ASSERT_EQ(captured_logs.size(), 1u);
    EXPECT_NE(captured_logs[0].message.find("at position"), std::string::npos);
    EXPECT_NE(captured_logs[0].message.find("999"), std::string::npos);
    EXPECT_NE(captured_logs[0].message.find("format check"), std::string::npos);
}

// Test multiple calls accumulate log messages correctly
TEST_F(PopplerErrorCbTest_2599, MultipleCallsAccumulate_2599)
{
    _poppler_error_cb(errSyntaxWarning, 1, "first");
    _poppler_error_cb(errSyntaxError, 2, "second");

    ASSERT_EQ(captured_logs.size(), 2u);
    EXPECT_NE(captured_logs[0].message.find("first"), std::string::npos);
    EXPECT_NE(captured_logs[1].message.find("second"), std::string::npos);
}

// Test that ignored categories mixed with valid ones only produce expected logs
TEST_F(PopplerErrorCbTest_2599, MixedCategoriesOnlyValidOnesLogged_2599)
{
    _poppler_error_cb(errConfig, 0, "ignored1");
    _poppler_error_cb(errSyntaxWarning, 10, "logged1");
    _poppler_error_cb(errCommandLine, 0, "ignored2");
    _poppler_error_cb(errIO, 20, "logged2");
    _poppler_error_cb(errNotAllowed, 0, "ignored3");

    ASSERT_EQ(captured_logs.size(), 2u);
    EXPECT_NE(captured_logs[0].message.find("logged1"), std::string::npos);
    EXPECT_NE(captured_logs[1].message.find("logged2"), std::string::npos);
}
