// File: ./TestProjects/re2/util/pcre_arg_parse_test_184.cc

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "TestProjects/re2/util/pcre.h"

using ::testing::_;
using ::testing::Return;
using ::testing::StrictMock;

namespace re2 {
namespace {

//
// We verify that Arg::Parse delegates to the parser supplied via the
// (T* value, Parser parser) constructor, forwards parameters correctly,
// returns the parser's boolean result, and allows writes through dest.
//

// A mock that will receive the forwarded call via a static thunk compatible
// with the expected Parser function pointer type: bool(const char*, size_t, void*).
class MockParser_184 {
public:
  MOCK_METHOD(bool, Call, (const char* str, size_t n, void* dest));

  // Static thunk that matches Parser's function signature and routes to the mock.
  static bool Thunk(const char* str, size_t n, void* dest) {
    // Guard in case tests forget to set instance.
    if (instance_ == nullptr) return false;
    return instance_->Call(str, n, dest);
  }

  static void SetInstance(MockParser_184* inst) { instance_ = inst; }
  static void ClearInstance() { instance_ = nullptr; }

private:
  static MockParser_184* instance_;
};

MockParser_184* MockParser_184::instance_ = nullptr;

// Fixture provides RAII for setting/clearing the static mock instance.
class ArgParseTest_184 : public ::testing::Test {
protected:
  void SetUp() override { MockParser_184::SetInstance(&mock_); }
  void TearDown() override { MockParser_184::ClearInstance(); }

  StrictMock<MockParser_184> mock_;
};

// --- Tests ---

// Normal operation: Parse forwards (str, n, dest) to the supplied parser and
// returns the parser's boolean result.
TEST_F(ArgParseTest_184, ForwardsToCustomParserAndReturnsTrue_184) {
  int sink = 0;
  // Construct Arg with our destination and the mock thunk as parser.
  PCRE::Arg arg(&sink, &MockParser_184::Thunk);

  const char* kStr = "abc123";
  const size_t kLen = 6;

  EXPECT_CALL(mock_, Call(kStr, kLen, &sink))
      .WillOnce(Return(true));

  const bool ok = arg.Parse(kStr, kLen);
  EXPECT_TRUE(ok);
}

// Error/exceptional observable behavior: if the parser returns false,
// Arg::Parse must return false.
TEST_F(ArgParseTest_184, ReturnsFalseWhenParserFails_184) {
  int sink = 42;
  PCRE::Arg arg(&sink, &MockParser_184::Thunk);

  const char* kStr = "bad-input";
  const size_t kLen = 9;

  EXPECT_CALL(mock_, Call(kStr, kLen, &sink))
      .WillOnce(Return(false));

  const bool ok = arg.Parse(kStr, kLen);
  EXPECT_FALSE(ok);
}

// Verification of external interaction AND visible side-effect:
// the parser can write through the provided destination pointer.
TEST_F(ArgParseTest_184, AllowsParserToWriteThroughDest_184) {
  int sink = 0;
  PCRE::Arg arg(&sink, &MockParser_184::Thunk);

  const char* kStr = "99";
  const size_t kLen = 2;

  EXPECT_CALL(mock_, Call(kStr, kLen, &sink))
      .WillOnce([](const char* str, size_t n, void* dest) {
        // Simulate a successful parse that writes to the destination.
        // We only rely on the pointer we were given (publicly observable effect).
        *static_cast<int*>(dest) = 99;
        return true;
      });

  const bool ok = arg.Parse(kStr, kLen);
  EXPECT_TRUE(ok);
  EXPECT_EQ(99, sink);
}

// Boundary condition: empty input should still be forwarded exactly as given.
TEST_F(ArgParseTest_184, ForwardsEmptyInputAndZeroLength_184) {
  int sink = -1;
  PCRE::Arg arg(&sink, &MockParser_184::Thunk);

  const char* kStr = "";     // empty C-string
  const size_t kLen = 0;     // explicit length 0

  EXPECT_CALL(mock_, Call(kStr, kLen, &sink))
      .WillOnce(Return(true));

  EXPECT_TRUE(arg.Parse(kStr, kLen));
}

// Reentrancy/Idempotence w.r.t. method constness: can call Parse multiple times,
// and each call should forward its own parameters.
TEST_F(ArgParseTest_184, CanBeCalledMultipleTimesAndForwardsEachCall_184) {
  int sink = 0;
  PCRE::Arg arg(&sink, &MockParser_184::Thunk);

  const char* s1 = "first";
  const size_t n1 = 5;
  const char* s2 = "second";
  const size_t n2 = 6;

  {
    ::testing::InSequence seq;
    EXPECT_CALL(mock_, Call(s1, n1, &sink)).WillOnce([](const char*, size_t, void* d){
      *static_cast<int*>(d) = 1;
      return true;
    });
    EXPECT_CALL(mock_, Call(s2, n2, &sink)).WillOnce([](const char*, size_t, void* d){
      *static_cast<int*>(d) = 2;
      return true;
    });
  }

  EXPECT_TRUE(arg.Parse(s1, n1));
  EXPECT_EQ(1, sink);

  EXPECT_TRUE(arg.Parse(s2, n2));
  EXPECT_EQ(2, sink);
}

}  // namespace
}  // namespace re2
