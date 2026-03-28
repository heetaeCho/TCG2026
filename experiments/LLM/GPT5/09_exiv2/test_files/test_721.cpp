// TEST_ID: 721
// File: test_logmsg_721.cpp

#include <gtest/gtest.h>

#include <exiv2/error.hpp>

#include <atomic>
#include <cstring>
#include <mutex>
#include <string>

namespace {

// A simple thread-safe sink for captured handler invocations.
struct CapturedLog {
  std::atomic<int> calls{0};
  std::mutex mu;
  int last_level = 0;
  std::string last_msg;

  void reset() {
    calls.store(0);
    std::lock_guard<std::mutex> lk(mu);
    last_level = 0;
    last_msg.clear();
  }

  void record(int level, const char* s) {
    calls.fetch_add(1);
    std::lock_guard<std::mutex> lk(mu);
    last_level = level;
    last_msg = (s != nullptr) ? std::string(s) : std::string();
  }
};

CapturedLog& captured1() {
  static CapturedLog c;
  return c;
}
CapturedLog& captured2() {
  static CapturedLog c;
  return c;
}

// Use plain function pointers so this works whether Handler is a function pointer
// typedef or a std::function taking (int, const char*).
static void TestHandler1(int level, const char* s) { captured1().record(level, s); }
static void TestHandler2(int level, const char* s) { captured2().record(level, s); }

class LogMsgTest_721 : public ::testing::Test {
 protected:
  using LogMsg = Exiv2::LogMsg;

  void SetUp() override {
    captured1().reset();
    captured2().reset();
    // Ensure a known handler is installed at test start.
    LogMsg::setHandler(&TestHandler1);
  }

  void TearDown() override {
    // Restore a valid handler to avoid impacting other tests in the suite.
    LogMsg::setHandler(&TestHandler1);
  }
};

}  // namespace

TEST_F(LogMsgTest_721, SetHandler_EmitsThroughInstalledHandlerOnDestruction_721) {
  using LogMsg = Exiv2::LogMsg;

  captured1().reset();
  LogMsg::setHandler(&TestHandler1);

  // Pick a valid Level value without assuming specific enumerators exist.
  const auto lvl = static_cast<LogMsg::Level>(0);

  {
    LogMsg msg(lvl);
    msg.os() << "hello logmsg";
  }  // destructor should flush to handler if implemented that way

  // Observable behavior: handler should be invoked (common contract for LogMsg).
  EXPECT_GE(captured1().calls.load(), 1);

  // If invoked, the rendered message should include streamed content.
  // (We only require substring to avoid assuming exact formatting.)
  {
    std::lock_guard<std::mutex> lk(captured1().mu);
    if (!captured1().last_msg.empty()) {
      EXPECT_NE(captured1().last_msg.find("hello logmsg"), std::string::npos);
    }
  }
}

TEST_F(LogMsgTest_721, MultipleSetHandler_LastHandlerWinsForSubsequentMessages_721) {
  using LogMsg = Exiv2::LogMsg;

  captured1().reset();
  captured2().reset();

  LogMsg::setHandler(&TestHandler1);
  LogMsg::setHandler(&TestHandler2);

  const auto lvl = static_cast<LogMsg::Level>(0);
  {
    LogMsg msg(lvl);
    msg.os() << "second handler should receive this";
  }

  EXPECT_EQ(captured1().calls.load(), 0);
  EXPECT_GE(captured2().calls.load(), 1);

  {
    std::lock_guard<std::mutex> lk(captured2().mu);
    if (!captured2().last_msg.empty()) {
      EXPECT_NE(captured2().last_msg.find("second handler should receive this"), std::string::npos);
    }
  }
}

TEST_F(LogMsgTest_721, SetHandler_CanBeChangedRepeatedlyWithoutCrashing_721) {
  using LogMsg = Exiv2::LogMsg;

  EXPECT_NO_THROW(LogMsg::setHandler(&TestHandler1));
  EXPECT_NO_THROW(LogMsg::setHandler(&TestHandler2));
  EXPECT_NO_THROW(LogMsg::setHandler(&TestHandler1));

  const auto lvl = static_cast<LogMsg::Level>(0);
  captured1().reset();
  {
    LogMsg msg(lvl);
    msg.os() << "stability check";
  }
  EXPECT_GE(captured1().calls.load(), 1);
}

TEST_F(LogMsgTest_721, DefaultHandler_DoesNotThrowForNullAndNonNullMessages_721) {
  using LogMsg = Exiv2::LogMsg;

  EXPECT_NO_THROW(LogMsg::defaultHandler(0, "default handler message"));
  EXPECT_NO_THROW(LogMsg::defaultHandler(0, nullptr));
}