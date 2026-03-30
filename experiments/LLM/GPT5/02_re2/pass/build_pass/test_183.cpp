// File: pcre_matchobject_parse_test_183.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "TestProjects/re2/util/pcre.h"

using ::testing::_;
using ::testing::Eq;
using ::testing::Return;

namespace {

// Collaborator type T with the required interface (mocked).
class MockParseTarget {
public:
  MOCK_METHOD(bool, ParseFrom, (const char* str, size_t n), ());
};

}  // namespace

// ---- Tests ----

// Verifies: When dest == nullptr, Parse returns true and does not access T.
TEST(PCRE_MatchObjectParse_183, NullDestReturnsTrue_183) {
  const char* input = "ignored";
  size_t n = 7;

  // No object provided; should simply return true.
  bool ok = re2::_PCRE_MatchObject<MockParseTarget>::Parse(input, n, /*dest=*/nullptr);
  EXPECT_TRUE(ok);
}

// Verifies: With a valid dest, Parse forwards (str, n) to T::ParseFrom and returns true.
TEST(PCRE_MatchObjectParse_183, ForwardsArgsAndReturnsTrue_183) {
  MockParseTarget obj;
  const char* input = "hello";
  size_t n = 5;

  EXPECT_CALL(obj, ParseFrom(Eq(input), Eq(n)))
      .Times(1)
      .WillOnce(Return(true));

  bool ok = re2::_PCRE_MatchObject<MockParseTarget>::Parse(input, n, &obj);
  EXPECT_TRUE(ok);
}

// Verifies: With a valid dest, Parse forwards (str, n) and propagates a false return.
TEST(PCRE_MatchObjectParse_183, ForwardsArgsAndReturnsFalse_183) {
  MockParseTarget obj;
  const char* input = "data";
  size_t n = 4;

  EXPECT_CALL(obj, ParseFrom(Eq(input), Eq(n)))
      .Times(1)
      .WillOnce(Return(false));

  bool ok = re2::_PCRE_MatchObject<MockParseTarget>::Parse(input, n, &obj);
  EXPECT_FALSE(ok);
}

// Verifies: Boundary condition n == 0 is forwarded correctly.
TEST(PCRE_MatchObjectParse_183, ZeroLengthInputIsForwarded_183) {
  MockParseTarget obj;
  const char* input = "";   // Pointer should still be forwarded, length is 0.
  size_t n = 0;

  EXPECT_CALL(obj, ParseFrom(Eq(input), Eq(n)))
      .Times(1)
      .WillOnce(Return(true));

  bool ok = re2::_PCRE_MatchObject<MockParseTarget>::Parse(input, n, &obj);
  EXPECT_TRUE(ok);
}

