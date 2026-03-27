// File: re2_arg_parse_test.cc
#include <gtest/gtest.h>
#include "re2/re2.h"

using re2::RE2;

namespace {

// A simple payload the parser can write into (observable effect).
struct RecordingDest {
  std::string last_str;
  size_t last_n = 0;
  int calls = 0;
};

// Parser that records inputs into RecordingDest and returns a configurable bool.
bool RecordingParserTrue(const char* str, size_t n, void* dest_void) {
  auto* dest = static_cast<RecordingDest*>(dest_void);
  if (dest) {
    dest->last_str.assign(str, n);  // copy n bytes (may include '\0')
    dest->last_n = n;
    dest->calls += 1;
  }
  return true;
}

bool RecordingParserFalse(const char* str, size_t n, void* dest_void) {
  (void)str; (void)n;
  auto* dest = static_cast<RecordingDest*>(dest_void);
  if (dest) dest->calls += 1;
  return false;
}

// Parser that only records whether dest was nullptr.
struct NullDestProbe {
  bool saw_null = false;
  int calls = 0;
};

bool NullCheckingParser(const char* /*str*/, size_t /*n*/, void* dest_void) {
  auto* probe = static_cast<NullDestProbe*>(dest_void);
  if (probe) {
    probe->saw_null = (dest_void == nullptr);  // always false here; we also test with nullptr Arg storage
    probe->calls += 1;
  }
  // Return value isn't under test here; choose true.
  return true;
}

// Parser that records raw bytes including embedded NULs into dest->last_str.
bool BinaryCopyParser(const char* str, size_t n, void* dest_void) {
  auto* dest = static_cast<RecordingDest*>(dest_void);
  if (dest) {
    dest->last_str.assign(str, n);
    dest->last_n = n;
    dest->calls += 1;
  }
  return true;
}

}  // namespace

// Normal operation: Parse delegates to the provided parser and returns its value.
TEST(RE2ArgParseTest_42, ParseDelegatesAndReturnsParserValue_42) {
  RecordingDest dest;
  RE2::Arg arg(&dest, &RecordingParserTrue);
  const char* input = "hello";
  const size_t n = 5;

  // Should return whatever the parser returns (true here).
  EXPECT_TRUE(arg.Parse(input, n));
  EXPECT_EQ(dest.calls, 1);
  EXPECT_EQ(dest.last_str, "hello");
  EXPECT_EQ(dest.last_n, n);

  // Now use a parser that returns false, to ensure pass-through.
  RecordingDest dest2;
  RE2::Arg arg2(&dest2, &RecordingParserFalse);
  EXPECT_FALSE(arg2.Parse(input, n));
  EXPECT_EQ(dest2.calls, 1);
}

// Boundary: zero-length input should still be forwarded with n == 0.
TEST(RE2ArgParseTest_42, ParseForwardsZeroLengthInput_42) {
  RecordingDest dest;
  RE2::Arg arg(&dest, &RecordingParserTrue);

  const char* input = "";  // pointer may be non-null; n==0 is what matters
  const size_t n = 0;

  EXPECT_TRUE(arg.Parse(input, n));
  EXPECT_EQ(dest.calls, 1);
  EXPECT_EQ(dest.last_n, 0u);
  EXPECT_EQ(dest.last_str, std::string());  // empty copy
}

// Boundary: input containing embedded NUL bytes is respected via length 'n'.
TEST(RE2ArgParseTest_42, ParsePreservesEmbeddedNullBytesByLength_42) {
  RecordingDest dest;
  RE2::Arg arg(&dest, &BinaryCopyParser);

  const char buf[5] = {'a', '\0', 'b', 'c', '\0'};
  const size_t n = sizeof(buf);

  EXPECT_TRUE(arg.Parse(buf, n));
  ASSERT_EQ(dest.calls, 1);
  ASSERT_EQ(dest.last_n, n);
  // Verify content including embedded NULs.
  ASSERT_EQ(dest.last_str.size(), n);
  EXPECT_EQ(dest.last_str[0], 'a');
  EXPECT_EQ(dest.last_str[1], '\0');
  EXPECT_EQ(dest.last_str[2], 'b');
  EXPECT_EQ(dest.last_str[3], 'c');
  EXPECT_EQ(dest.last_str[4], '\0');
}

// Exceptional/edge: destination pointer provided to Arg can be nullptr;
// Parse still delegates, and the parser receives a nullptr dest.
TEST(RE2ArgParseTest_42, ParseAllowsNullDestinationPointer_42) {
  // Construct Arg with a nullptr destination and a parser we control.
  // We cannot inspect Arg internals; we only verify that calling Parse does not crash
  // and that return value passes through from the parser.
  RE2::Arg arg(static_cast<RecordingDest*>(nullptr), &RecordingParserTrue);
  const char* input = "x";
  EXPECT_TRUE(arg.Parse(input, 1));  // parser returns true
  // No observable dest writes possible, but call should be successful.
}

// Interaction verification: multiple calls forward differing inputs to the parser.
TEST(RE2ArgParseTest_42, ParseCanBeCalledMultipleTimesWithDifferentInputs_42) {
  RecordingDest dest;
  RE2::Arg arg(&dest, &RecordingParserTrue);

  EXPECT_TRUE(arg.Parse("one", 3));
  EXPECT_EQ(dest.calls, 1);
  EXPECT_EQ(dest.last_str, "one");
  EXPECT_EQ(dest.last_n, 3u);

  EXPECT_TRUE(arg.Parse("two", 3));
  EXPECT_EQ(dest.calls, 2);
  EXPECT_EQ(dest.last_str, "two");
  EXPECT_EQ(dest.last_n, 3u);

  EXPECT_TRUE(arg.Parse("three", 5));
  EXPECT_EQ(dest.calls, 3);
  EXPECT_EQ(dest.last_str, "three");
  EXPECT_EQ(dest.last_n, 5u);
}

// Smoke: constructing with std::nullptr_t should be callable without crash.
// We do not assert on return value since the private default parser behavior
// is not part of the public contract here; we only assert that it returns a bool
// and is invocable.
TEST(RE2ArgParseTest_42, NullptrConstructedArgIsInvocable_42) {
  RE2::Arg arg(nullptr);  // uses the nullptr_t overload
  // We only assert that calling does not crash; capture the boolean result as an observable.
  bool result = arg.Parse("", 0);
  (void)result;  // No assumption about true/false — just ensure invocability.
  SUCCEED();
}
