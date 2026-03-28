// =================================================================================================
// TEST_ID: 720
// File: test_logmsg_720.cpp
// Unit tests for Exiv2::LogMsg (error.hpp / error.cpp)
// =================================================================================================

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <climits>
#include <string>

#include "exiv2/error.hpp"

namespace {

using ::testing::_;
using ::testing::HasSubstr;
using ::testing::NotNull;

class LogMsgTest_720 : public ::testing::Test {
protected:
  void SetUp() override {
    // Preserve global/static settings to avoid leaking state across tests.
    savedLevel_ = Exiv2::LogMsg::level();
    savedHandler_ = Exiv2::LogMsg::handler();
  }

  void TearDown() override {
    // Restore global/static settings.
    Exiv2::LogMsg::setHandler(savedHandler_);
    Exiv2::LogMsg::setLevel(savedLevel_);
  }

  Exiv2::LogMsg::Level savedLevel_{};
  Exiv2::LogMsg::Handler savedHandler_{};
};

// ----------------------------
// Handler mocking via trampoline
// ----------------------------
struct MockHandler_720 {
  MOCK_METHOD(void, Call, (int level, const char* s));
};

MockHandler_720* g_mockHandler_720 = nullptr;

void HandlerTrampoline_720(int level, const char* s) {
  // Defensive: allow trampoline calls even if the test didn't set the mock.
  if (g_mockHandler_720) {
    g_mockHandler_720->Call(level, s);
  }
}

// -------------------------------------------------------------------------------------------------
// Tests
// -------------------------------------------------------------------------------------------------

TEST_F(LogMsgTest_720, SetLevelRoundTripsThroughStaticLevel_720) {
  // Use distinct values without assuming enum names.
  const auto level0 = static_cast<Exiv2::LogMsg::Level>(0);
  const auto level1 = static_cast<Exiv2::LogMsg::Level>(1);

  Exiv2::LogMsg::setLevel(level0);
  EXPECT_EQ(Exiv2::LogMsg::level(), level0);

  Exiv2::LogMsg::setLevel(level1);
  EXPECT_EQ(Exiv2::LogMsg::level(), level1);
}

TEST_F(LogMsgTest_720, SetHandlerRoundTripsThroughStaticHandler_720) {
  // Set to a known function and verify it is observable through handler().
  Exiv2::LogMsg::setHandler(&Exiv2::LogMsg::defaultHandler);
  EXPECT_EQ(Exiv2::LogMsg::handler(), &Exiv2::LogMsg::defaultHandler);

  // Set to our trampoline and verify it is observable.
  Exiv2::LogMsg::setHandler(&HandlerTrampoline_720);
  EXPECT_EQ(Exiv2::LogMsg::handler(), &HandlerTrampoline_720);
}

TEST_F(LogMsgTest_720, OsReturnsStableReference_720) {
  const auto level0 = static_cast<Exiv2::LogMsg::Level>(0);

  Exiv2::LogMsg msg(level0);

  auto& os1 = msg.os();
  auto& os2 = msg.os();

  EXPECT_EQ(&os1, &os2);
}

TEST_F(LogMsgTest_720, DefaultHandlerAcceptsTypicalInputs_720) {
  // Observable requirement here: it should be callable and not throw.
  EXPECT_NO_THROW(Exiv2::LogMsg::defaultHandler(0, ""));
  EXPECT_NO_THROW(Exiv2::LogMsg::defaultHandler(INT_MAX, "x"));
}

TEST_F(LogMsgTest_720, DestructorCanInvokeCustomHandlerAfterWritingToStream_720) {
  // This test verifies external interaction (handler invocation) without relying on internals:
  // If LogMsg is an RAII-style logger (as suggested by os() + destructor + handler API),
  // destroying a message after writing should result in a handler call.
  MockHandler_720 mock;
  g_mockHandler_720 = &mock;

  // Ensure handler is our trampoline during the scoped message lifetime.
  Exiv2::LogMsg::setHandler(&HandlerTrampoline_720);

  // Use a level value without assuming enum names; also set global level to something deterministic.
  const auto level0 = static_cast<Exiv2::LogMsg::Level>(0);
  Exiv2::LogMsg::setLevel(level0);

  EXPECT_CALL(mock, Call(_, NotNull()))
      .Times(::testing::AtLeast(1))
      .WillRepeatedly([&](int, const char* s) {
        // Keep assertion lightweight and observable: message content should include our token.
        // (If formatting adds prefixes/newlines, substring match still holds.)
        EXPECT_THAT(std::string(s), HasSubstr("hello-720"));
      });

  {
    Exiv2::LogMsg msg(level0);
    msg.os() << "hello-720";
  }

  g_mockHandler_720 = nullptr;
}

}  // namespace