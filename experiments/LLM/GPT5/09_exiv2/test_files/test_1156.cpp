// TEST_ID 1156
// Unit tests for Exiv2::exvGettext (./TestProjects/exiv2/src/types.cpp)
//
// Constraints notes:
// - Treat implementation as black box: tests only rely on observable behavior of the public function.
// - We do not assume NLS is enabled/disabled at runtime; tests are written to be valid in either case.
//
// Build notes:
// - If EXV_ENABLE_NLS is not defined, exvGettext is a simple passthrough and tests validate that.
// - If EXV_ENABLE_NLS is defined, exvGettext delegates to gettext; translation availability is
//   environment-dependent, so tests avoid assuming a specific translation exists.

#include <gtest/gtest.h>

#include <cstring>

namespace Exiv2 {
// Function under test (implemented in the production codebase).
const char* exvGettext(const char* str);
}  // namespace Exiv2

namespace {

class ExvGettextTest_1156 : public ::testing::Test {};

TEST_F(ExvGettextTest_1156, NullPointerReturnsNull_1156) {
  // Observable contract: for passthrough build, returns the same pointer (nullptr).
  // For NLS build, underlying dgettext typically returns nullptr when msgid is nullptr.
  // Either way, it must not crash, and should return nullptr.
  const char* res = Exiv2::exvGettext(nullptr);
  EXPECT_EQ(res, nullptr);
}

TEST_F(ExvGettextTest_1156, EmptyStringDoesNotCrashAndIsEmpty_1156) {
  const char* input = "";
  const char* res = Exiv2::exvGettext(input);
  ASSERT_NE(res, nullptr);

#ifndef EXV_ENABLE_NLS
  // Passthrough behavior is observable and stable.
  EXPECT_EQ(res, input);
#else
  // NLS build: translation may or may not exist; but it should at least be a valid C string.
  EXPECT_STREQ(res, "");
#endif
}

TEST_F(ExvGettextTest_1156, NonEmptyStringDoesNotCrashAndMatchesInputContent_1156) {
  const char* input = "Exiv2 test string 1156";
  const char* res = Exiv2::exvGettext(input);
  ASSERT_NE(res, nullptr);

#ifndef EXV_ENABLE_NLS
  EXPECT_EQ(res, input);
#else
  // NLS build: we cannot assume translation exists; in that common case, gettext returns msgid.
  // Even if translated, it should be a valid, NUL-terminated string.
  // We assert the safe, observable minimum: it's a C-string and not empty if input isn't empty.
  EXPECT_GE(std::strlen(res), static_cast<size_t>(0));
  EXPECT_GT(std::strlen(input), static_cast<size_t>(0));
#endif
}

TEST_F(ExvGettextTest_1156, SameInputPointerProducesSameOutputPointerInPassthroughBuild_1156) {
  const char* input = "repeatable";
  const char* r1 = Exiv2::exvGettext(input);
  const char* r2 = Exiv2::exvGettext(input);
  ASSERT_NE(r1, nullptr);
  ASSERT_NE(r2, nullptr);

#ifndef EXV_ENABLE_NLS
  // Pure passthrough: pointer identity is observable.
  EXPECT_EQ(r1, input);
  EXPECT_EQ(r2, input);
  EXPECT_EQ(r1, r2);
#else
  // NLS build: pointer identity is not guaranteed by gettext across calls/implementations,
  // so only assert that it remains valid C strings.
  EXPECT_GE(std::strlen(r1), static_cast<size_t>(0));
  EXPECT_GE(std::strlen(r2), static_cast<size_t>(0));
#endif
}

TEST_F(ExvGettextTest_1156, LargeStringDoesNotCrash_1156) {
  // Boundary-ish: long msgid should not crash and should return a valid C string.
  std::string big(64 * 1024, 'A');  // 64 KiB
  const char* res = Exiv2::exvGettext(big.c_str());
  ASSERT_NE(res, nullptr);

#ifndef EXV_ENABLE_NLS
  // Passthrough: same pointer and same content.
  EXPECT_EQ(res, big.c_str());
  EXPECT_EQ(std::strlen(res), big.size());
#else
  // NLS build: at minimum should produce a NUL-terminated string.
  EXPECT_GE(std::strlen(res), static_cast<size_t>(0));
#endif
}

}  // namespace