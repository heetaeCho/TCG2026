// =====================================================================================
// UNIT TESTS for Exiv2::CommentValue (value.cpp)
// TEST_ID: 819
//
// These tests treat CommentValue as a black box and validate only observable behavior
// via the public interface (return codes, comment output when available, and optional
// log-handler interaction on invalid charset).
// =====================================================================================

#include <gtest/gtest.h>

#include <exiv2/value.hpp>
#include <exiv2/error.hpp>

#include <atomic>
#include <cstring>
#include <string>

namespace {

class CommentValueTest_819 : public ::testing::Test {
protected:
#ifndef SUPPRESS_WARNINGS
  // If warnings are enabled, we can capture log output via LogMsg handler.
  static inline std::atomic<int> warn_calls_{0};
  static inline std::atomic<int> last_level_{-1};

  // Signature is not shown in the prompt, but Exiv2::LogMsg::defaultHandler suggests:
  //   handler(int level, const char* s)
  static void CaptureHandler(int level, const char* /*s*/) {
    last_level_.store(level, std::memory_order_relaxed);
    warn_calls_.fetch_add(1, std::memory_order_relaxed);
  }

  void SetUp() override {
    warn_calls_.store(0, std::memory_order_relaxed);
    last_level_.store(-1, std::memory_order_relaxed);

    // Make sure warnings are not muted and handler is installed.
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::warn);
    Exiv2::LogMsg::setHandler(&CaptureHandler);
  }

  void TearDown() override {
    // Restore default handler to avoid impacting other tests.
    Exiv2::LogMsg::setHandler(&Exiv2::LogMsg::defaultHandler);
  }
#endif
};

TEST_F(CommentValueTest_819, Read_InvalidCharsetName_Returns1_819) {
  Exiv2::CommentValue v;
  const int rc = v.read(std::string("charset=NoSuchCharset hello"));
  EXPECT_EQ(1, rc);
}

TEST_F(CommentValueTest_819, Read_InvalidCharsetName_Quoted_Returns1_819) {
  Exiv2::CommentValue v;
  const int rc = v.read(std::string("charset=\"NoSuchCharset\" hello"));
  EXPECT_EQ(1, rc);
}

TEST_F(CommentValueTest_819, Read_InvalidCharsetName_NoTrailingText_Returns1_819) {
  Exiv2::CommentValue v;
  // Boundary: no space after charset spec.
  const int rc = v.read(std::string("charset=NoSuchCharset"));
  EXPECT_EQ(1, rc);
}

TEST_F(CommentValueTest_819, Read_CharsetPrefix_EmptyName_Returns1_819) {
  Exiv2::CommentValue v;
  // Boundary: empty charset name right after "charset="
  const int rc = v.read(std::string("charset= hello"));
  EXPECT_EQ(1, rc);
}

TEST_F(CommentValueTest_819, Read_CharsetPrefix_QuotedEmptyName_Returns1_819) {
  Exiv2::CommentValue v;
  // Boundary: quoted empty charset name
  const int rc = v.read(std::string("charset=\"\" hello"));
  EXPECT_EQ(1, rc);
}

TEST_F(CommentValueTest_819, Read_NoCharsetPrefix_DoesNotReturn1_819) {
  Exiv2::CommentValue v;

  const std::string input = "hello";
  const int rc = v.read(input);

  // Black-box: we only know invalid charset returns 1 from the provided implementation.
  // For a plain comment (no charset= prefix), it should not take that invalid-charset path.
  EXPECT_NE(1, rc);

  // If the read was successful (commonly 0), comment("UTF-8") should be at least consistent.
  // We avoid assuming exact behavior when rc != 0.
  if (rc == 0) {
    EXPECT_EQ(input, v.comment("UTF-8"));
  }
}

TEST_F(CommentValueTest_819, Read_EmptyString_DoesNotReturn1_819) {
  Exiv2::CommentValue v;

  const int rc = v.read(std::string());
  // Should not trigger invalid charset handling (which returns 1).
  EXPECT_NE(1, rc);

  if (rc == 0) {
    EXPECT_EQ(std::string(), v.comment("UTF-8"));
  }
}

#ifndef SUPPRESS_WARNINGS
TEST_F(CommentValueTest_819, Read_InvalidCharset_EmitsWarningViaHandler_819) {
  Exiv2::CommentValue v;

  const int rc = v.read(std::string("charset=NoSuchCharset hello"));
  ASSERT_EQ(1, rc);

  // Observable external interaction: a warning is expected when warnings are not suppressed.
  // We do not assert exact message text; only that the handler was invoked.
  EXPECT_GT(warn_calls_.load(std::memory_order_relaxed), 0);

  // Level should be warn or higher (implementation-dependent exact int values).
  // We rely only on the enum constants exposed in the header.
  const int lvl = last_level_.load(std::memory_order_relaxed);
  EXPECT_GE(lvl, static_cast<int>(Exiv2::LogMsg::warn));
}
#endif

}  // namespace