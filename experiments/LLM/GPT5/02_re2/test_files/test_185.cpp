// File: pcre_compile_tests_185.cc
#include <gtest/gtest.h>
#include <string>

// Forward declaration matching the provided implementation unit.
// We don't include the .cc to avoid multiple definitions at link time.
struct pcre;
extern pcre* pcre_compile(const char* pattern,
                          int options,
                          const char** errorptr,
                          int* erroffset,
                          const unsigned char* tableptr);

// Test fixture kept minimal since the interface is plain functions.
class PcreCompileTest_185 : public ::testing::Test {};

// Normal operation: callable with typical non-null output pointers.
TEST_F(PcreCompileTest_185, ReturnsNull_WithNonNullOutputs_185) {
  const char* error = reinterpret_cast<const char*>(0xDEADBEEF); // sentinel
  const char* error_out = error;
  int offset = -42;

  pcre* result = pcre_compile("abc", /*options=*/0, &error_out, &offset, /*tableptr=*/nullptr);

  EXPECT_EQ(result, nullptr);
  // We do not assert on error_out/offset contents per constraints (no inference about output semantics).
}

// Boundary: accepts null for error/output pointers without crashing and returns nullptr.
TEST_F(PcreCompileTest_185, ReturnsNull_WithNullOutputs_185) {
  pcre* result = pcre_compile("abc", /*options=*/0, /*errorptr=*/nullptr, /*erroffset=*/nullptr, /*tableptr=*/nullptr);
  EXPECT_EQ(result, nullptr);
}

// Boundary: empty pattern string.
TEST_F(PcreCompileTest_185, ReturnsNull_WithEmptyPattern_185) {
  const char* error_out = nullptr;
  int offset_out = 0;
  pcre* result = pcre_compile("", /*options=*/0, &error_out, &offset_out, /*tableptr=*/nullptr);
  EXPECT_EQ(result, nullptr);
}

// Boundary / robustness: various option values (including negative and large).
TEST_F(PcreCompileTest_185, ReturnsNull_WithVariousFlags_185) {
  const char* error_out = nullptr;
  int offset_out = 0;

  // 0 options
  EXPECT_EQ(pcre_compile("x", 0, &error_out, &offset_out, nullptr), nullptr);

  // Arbitrary positive option
  EXPECT_EQ(pcre_compile("x", 1, &error_out, &offset_out, nullptr), nullptr);

  // Negative option value
  EXPECT_EQ(pcre_compile("x", -1, &error_out, &offset_out, nullptr), nullptr);

  // Large option value
  EXPECT_EQ(pcre_compile("x", 0x7FFFFFFF, &error_out, &offset_out, nullptr), nullptr);
}

// Error-case input: null pattern pointer (if accepted by the interface) should still return nullptr.
TEST_F(PcreCompileTest_185, ReturnsNull_WithNullPattern_185) {
  const char* error_out = nullptr;
  int offset_out = 0;
  pcre* result = pcre_compile(/*pattern=*/nullptr, /*options=*/0, &error_out, &offset_out, /*tableptr=*/nullptr);
  EXPECT_EQ(result, nullptr);
}
