// File: ./TestProjects/re2/tests/parse_string_tests.cc

#include <gtest/gtest.h>
#include <string>
#include <vector>

// Forward declaration of the function under test, matching its namespace and signature.
// We do NOT re-implement any logic; we only declare it so tests can call it.
namespace re2 {
namespace re2_internal {
bool Parse(const char* str, size_t n, std::string* dest);
}  // namespace re2_internal
}  // namespace re2

// Normal operation: copies exactly n bytes into dest and returns true.
TEST(ParseStringTest_267, CopiesExactLength_267) {
  const char* src = "hello world";
  std::string out = "preset";
  bool ok = re2::re2_internal::Parse(src, 5u, &out);
  EXPECT_TRUE(ok);
  EXPECT_EQ(out, std::string("hello"));
}

// Boundary: n == 0 produces an empty string in dest and returns true.
TEST(ParseStringTest_267, ZeroLengthProducesEmpty_267) {
  const char* src = "ignored";
  std::string out = "will be cleared";
  bool ok = re2::re2_internal::Parse(src, 0u, &out);
  EXPECT_TRUE(ok);
  EXPECT_TRUE(out.empty());
}

// Normal/edge: supports embedded NUL bytes; result length equals n (not strlen).
TEST(ParseStringTest_267, SupportsEmbeddedNulls_267) {
  const char data[] = {'a', '\0', 'b', 'c'};
  std::string out;
  bool ok = re2::re2_internal::Parse(data, 3u, &out);  // "a\0b"
  EXPECT_TRUE(ok);
  EXPECT_EQ(out.size(), 3u);
  EXPECT_EQ(out, std::string("a\0b", 3));
}

// Boundary: large input (no trailing NUL required); ensures exact size copy and true return.
TEST(ParseStringTest_267, LargeInputNoTerminatorRequired_267) {
  const size_t N = 100000;  // reasonably large to test bulk copy without being excessive
  std::vector<char> buf(N, 'x');
  // Intentionally do not add a '\0' terminator to validate length-based copy.
  std::string out;
  bool ok = re2::re2_internal::Parse(buf.data(), buf.size(), &out);
  EXPECT_TRUE(ok);
  EXPECT_EQ(out.size(), N);
  EXPECT_TRUE(std::all_of(out.begin(), out.end(), [](char c){ return c == 'x'; }));
}

// Exceptional/edge (observable via return + no crash): null dest pointer is allowed and returns true.
TEST(ParseStringTest_267, NullDestPointerReturnsTrue_267) {
  const char* src = "anything";
  // We cannot (and should not) observe any internal side effects; just verify the API contract.
  bool ok = re2::re2_internal::Parse(src, 4u, /*dest=*/nullptr);
  EXPECT_TRUE(ok);
  // No further expectations; the key observable behavior is successful return and no crash.
}
