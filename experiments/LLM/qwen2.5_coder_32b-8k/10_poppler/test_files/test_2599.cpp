#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler/Error.h"

#include "poppler/poppler.cc"  // Assuming the function is not static or inlined



using ::testing::HasSubstr;



// Mocking g_log to verify its calls

class MockGLog {

public:

    MOCK_METHOD3(g_log, void(const char* log_domain, GLogLevelFlags log_level, const char* format, ...));

};



MockGLog* mock_g_log = nullptr;



void mock_g_log_wrapper(const gchar *log_domain, GLogLevelFlags log_level, const gchar *format, ...) {

    va_list args;

    va_start(args, format);

    mock_g_log->g_log(log_domain, log_level, format, args);

    va_end(args);

}



class PopplerErrorCallbackTest_2599 : public ::testing::Test {

protected:

    void SetUp() override {

        // Redirect g_log to our mock function

        mock_g_log = new MockGLog();

        g_log_set_default_handler((GLogFunc)mock_g_log_wrapper, nullptr);

    }



    void TearDown() override {

        delete mock_g_log;

    }

};



TEST_F(PopplerErrorCallbackTest_2599, SyntaxWarningLogsCorrectly_2599) {

    EXPECT_CALL(*mock_g_log, g_log(G_LOG_DOMAIN, G_LOG_LEVEL_INFO, HasSubstr("Syntax warning at position 10: Test message"))).Times(1);

    _poppler_error_cb(errSyntaxWarning, 10, "Test message");

}



TEST_F(PopplerErrorCallbackTest_2599, SyntaxErrorLogsCorrectly_2599) {

    EXPECT_CALL(*mock_g_log, g_log(G_LOG_DOMAIN, G_LOG_LEVEL_INFO, HasSubstr("Syntax error at position 20: Another test"))).Times(1);

    _poppler_error_cb(errSyntaxError, 20, "Another test");

}



TEST_F(PopplerErrorCallbackTest_2599, IOErrorLogsCorrectly_2599) {

    EXPECT_CALL(*mock_g_log, g_log(G_LOG_DOMAIN, G_LOG_LEVEL_INFO, HasSubstr("IO error at position 30: IO issue"))).Times(1);

    _poppler_error_cb(errIO, 30, "IO issue");

}



TEST_F(PopplerErrorCallbackTest_2599, UnimplementedFeatureLogsCorrectly_2599) {

    EXPECT_CALL(*mock_g_log, g_log(G_LOG_DOMAIN, G_LOG_LEVEL_INFO, HasSubstr("Unimplemented feature at position 40: Not implemented"))).Times(1);

    _poppler_error_cb(errUnimplemented, 40, "Not implemented");

}



TEST_F(PopplerErrorCallbackTest_2599, InternalErrorLogsCorrectly_2599) {

    EXPECT_CALL(*mock_g_log, g_log(G_LOG_DOMAIN, G_LOG_LEVEL_INFO, HasSubstr("Internal error at position 50: Something went wrong"))).Times(1);

    _poppler_error_cb(errInternal, 50, "Something went wrong");

}



TEST_F(PopplerErrorCallbackTest_2599, IgnoresConfigErrors_2599) {

    EXPECT_CALL(*mock_g_log, g_log(_, _, _)).Times(0); // Expect no call to g_log

    _poppler_error_cb(errConfig, 60, "Should not log");

}



TEST_F(PopplerErrorCallbackTest_2599, IgnoresCommandLineErrors_2599) {

    EXPECT_CALL(*mock_g_log, g_log(_, _, _)).Times(0); // Expect no call to g_log

    _poppler_error_cb(errCommandLine, 70, "Should not log");

}



TEST_F(PopplerErrorCallbackTest_2599, IgnoresNotAllowedErrors_2599) {

    EXPECT_CALL(*mock_g_log, g_log(_, _, _)).Times(0); // Expect no call to g_log

    _poppler_error_cb(errNotAllowed, 80, "Should not log");

}
