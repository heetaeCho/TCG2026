// File: poppler-error-cb-test-2599.cc
#include <gtest/gtest.h>

#include <glib.h>

#include "poppler/Error.h"

// Function under test (implemented in ./TestProjects/poppler/glib/poppler.cc)
extern void _poppler_error_cb(ErrorCategory category, Goffset pos, const char *message);

namespace {

struct LogCapture2599 {
  static void Handler(const gchar* /*log_domain*/,
                      GLogLevelFlags log_level,
                      const gchar* message,
                      gpointer user_data) {
    auto* self = static_cast<LogCapture2599*>(user_data);
    self->count++;
    self->last_level = log_level;
    self->last_message = (message ? message : "");
  }

  void Install() {
    // Capture all logs via the default handler.
    old_handler = g_log_set_default_handler(&LogCapture2599::Handler, this);
  }

  void Restore() {
    // Old user_data is not provided by GLib; in practice this is typically fine.
    // We restore the previous handler and pass nullptr as data.
    g_log_set_default_handler(old_handler, nullptr);
  }

  int count = 0;
  GLogLevelFlags last_level = static_cast<GLogLevelFlags>(0);
  std::string last_message;

  GLogFunc old_handler = nullptr;
};

class PopplerErrorCbTest_2599 : public ::testing::Test {
 protected:
  void SetUp() override { capture.Install(); }
  void TearDown() override { capture.Restore(); }

  LogCapture2599 capture;
};

TEST_F(PopplerErrorCbTest_2599, LogsSyntaxWarning_2599) {
  _poppler_error_cb(errSyntaxWarning, static_cast<Goffset>(123), "hello");
  ASSERT_EQ(capture.count, 1);
  EXPECT_TRUE((capture.last_level & G_LOG_LEVEL_INFO) != 0);
  EXPECT_NE(capture.last_message.find("Syntax warning"), std::string::npos);
  EXPECT_NE(capture.last_message.find("position 123"), std::string::npos);
  EXPECT_NE(capture.last_message.find("hello"), std::string::npos);
}

TEST_F(PopplerErrorCbTest_2599, LogsSyntaxError_2599) {
  _poppler_error_cb(errSyntaxError, static_cast<Goffset>(0), "bad token");
  ASSERT_EQ(capture.count, 1);
  EXPECT_TRUE((capture.last_level & G_LOG_LEVEL_INFO) != 0);
  EXPECT_NE(capture.last_message.find("Syntax error"), std::string::npos);
  EXPECT_NE(capture.last_message.find("position 0"), std::string::npos);
  EXPECT_NE(capture.last_message.find("bad token"), std::string::npos);
}

TEST_F(PopplerErrorCbTest_2599, LogsIOError_2599) {
  _poppler_error_cb(errIO, static_cast<Goffset>(42), "read failed");
  ASSERT_EQ(capture.count, 1);
  EXPECT_TRUE((capture.last_level & G_LOG_LEVEL_INFO) != 0);
  EXPECT_NE(capture.last_message.find("IO error"), std::string::npos);
  EXPECT_NE(capture.last_message.find("position 42"), std::string::npos);
  EXPECT_NE(capture.last_message.find("read failed"), std::string::npos);
}

TEST_F(PopplerErrorCbTest_2599, LogsUnimplementedFeature_2599) {
  _poppler_error_cb(errUnimplemented, static_cast<Goffset>(7), "feature X");
  ASSERT_EQ(capture.count, 1);
  EXPECT_TRUE((capture.last_level & G_LOG_LEVEL_INFO) != 0);
  EXPECT_NE(capture.last_message.find("Unimplemented feature"), std::string::npos);
  EXPECT_NE(capture.last_message.find("position 7"), std::string::npos);
  EXPECT_NE(capture.last_message.find("feature X"), std::string::npos);
}

TEST_F(PopplerErrorCbTest_2599, LogsInternalError_2599) {
  _poppler_error_cb(errInternal, static_cast<Goffset>(999), "oops");
  ASSERT_EQ(capture.count, 1);
  EXPECT_TRUE((capture.last_level & G_LOG_LEVEL_INFO) != 0);
  EXPECT_NE(capture.last_message.find("Internal error"), std::string::npos);
  EXPECT_NE(capture.last_message.find("position 999"), std::string::npos);
  EXPECT_NE(capture.last_message.find("oops"), std::string::npos);
}

TEST_F(PopplerErrorCbTest_2599, DoesNotLogForErrConfig_2599) {
  _poppler_error_cb(errConfig, static_cast<Goffset>(1), "ignored");
  EXPECT_EQ(capture.count, 0);
  EXPECT_TRUE(capture.last_message.empty());
}

TEST_F(PopplerErrorCbTest_2599, DoesNotLogForErrCommandLine_2599) {
  _poppler_error_cb(errCommandLine, static_cast<Goffset>(2), "ignored");
  EXPECT_EQ(capture.count, 0);
  EXPECT_TRUE(capture.last_message.empty());
}

TEST_F(PopplerErrorCbTest_2599, DoesNotLogForErrNotAllowed_2599) {
  _poppler_error_cb(errNotAllowed, static_cast<Goffset>(3), "ignored");
  EXPECT_EQ(capture.count, 0);
  EXPECT_TRUE(capture.last_message.empty());
}

TEST_F(PopplerErrorCbTest_2599, BoundaryLargeOffsetStillLogs_2599) {
  // Boundary-ish: very large offset value.
  const auto large_pos = static_cast<Goffset>(G_MAXINT64);
  _poppler_error_cb(errIO, large_pos, "big");
  ASSERT_EQ(capture.count, 1);
  EXPECT_TRUE((capture.last_level & G_LOG_LEVEL_INFO) != 0);
  EXPECT_NE(capture.last_message.find("IO error"), std::string::npos);
  EXPECT_NE(capture.last_message.find("big"), std::string::npos);
  // We don't assert the exact numeric formatting beyond being present in the message,
  // since formatting is implementation/ABI dependent (G_GOFFSET_FORMAT).
  EXPECT_NE(capture.last_message.find("position"), std::string::npos);
}

}  // namespace