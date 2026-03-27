// SPDX-License-Identifier: GPL-2.0-or-later
//
// Unit tests for unicode_to_char (static helper) in poppler-document.cc
//
// TEST_ID: 2215

#include <gtest/gtest.h>

#include <glib.h>

#include <cstdint>
#include <string>
#include <type_traits>
#include <vector>

#if __has_include("poppler/GlobalParams.h")
#include "poppler/GlobalParams.h"
#elif __has_include("GlobalParams.h")
#include "GlobalParams.h"
#endif

#if __has_include("poppler/UnicodeType.h")
#include "poppler/UnicodeType.h"
#elif __has_include("UnicodeType.h")
#include "UnicodeType.h"
#elif __has_include("poppler/Unicode.h")
#include "poppler/Unicode.h"
#elif __has_include("Unicode.h")
#include "Unicode.h"
#endif

// IMPORTANT:
// unicode_to_char is `static` inside poppler-document.cc, so we include that .cc file
// to compile the tests in the same translation unit (so the static symbol is visible).
//
// This pattern is commonly used for testing file-local helpers.
//
// If your build system already compiles poppler-document.cc separately into the test binary,
// you must ensure it is NOT compiled twice (otherwise you'll get duplicate symbols).
#include "TestProjects/poppler/glib/poppler-document.cc"

namespace {

class UnicodeToCharTest_2215 : public ::testing::Test {
protected:
  static void SetUpTestSuite() {
    EnsureGlobalParamsInitialized();
  }

  static void TearDownTestSuite() {
    // Only delete if we created it here. Avoid disturbing global ownership otherwise.
    if (created_global_params_) {
      delete globalParams;
      globalParams = nullptr;
      created_global_params_ = false;
    }
  }

  static void EnsureGlobalParamsInitialized() {
#if defined(globalParams)
    if (globalParams) {
      return;
    }

    // Try a few common GlobalParams constructors without guessing the "right" one.
    // This is purely test plumbing to satisfy unicode_to_char's dependency.
    if constexpr (std::is_constructible_v<GlobalParams, const char *>) {
      globalParams = new GlobalParams(nullptr);
      created_global_params_ = true;
      return;
    }
    if constexpr (std::is_constructible_v<GlobalParams>) {
      globalParams = new GlobalParams();
      created_global_params_ = true;
      return;
    }

    // If neither constructor is available, compilation will fail here and the build
    // environment needs to provide an initialization helper used by your project.
    // (Intentionally no fallback that re-implements Poppler logic.)
    FAIL() << "Could not construct GlobalParams in test environment";
#endif
  }

  static bool created_global_params_;
};

bool UnicodeToCharTest_2215::created_global_params_ = false;

static std::string TakeAndFree(gchar *s) {
  if (!s) {
    return {};
  }
  std::string out(s);
  g_free(s);
  return out;
}

TEST_F(UnicodeToCharTest_2215, EmptyLenWithNullPointerReturnsEmptyString_2215) {
  // Boundary: len == 0 should not require a valid pointer.
  std::string out = TakeAndFree(unicode_to_char(nullptr, 0));
  EXPECT_EQ(out, "");
}

TEST_F(UnicodeToCharTest_2215, EmptyLenWithNonNullPointerReturnsEmptyString_2215) {
  Unicode dummy = static_cast<Unicode>('X');
  std::string out = TakeAndFree(unicode_to_char(&dummy, 0));
  EXPECT_EQ(out, "");
}

TEST_F(UnicodeToCharTest_2215, MapsAsciiSequence_2215) {
  const Unicode u[] = {static_cast<Unicode>('A'), static_cast<Unicode>('B'), static_cast<Unicode>('C')};
  std::string out = TakeAndFree(unicode_to_char(u, 3));
  EXPECT_EQ(out, "ABC");
  EXPECT_TRUE(g_utf8_validate(out.c_str(), static_cast<gssize>(out.size()), nullptr));
}

TEST_F(UnicodeToCharTest_2215, MapsBmpMultibyteCharacterEuroSign_2215) {
  // U+20AC (€) => UTF-8: E2 82 AC
  const Unicode u[] = {static_cast<Unicode>(0x20AC)};
  std::string out = TakeAndFree(unicode_to_char(u, 1));
  EXPECT_EQ(out, std::string("\xE2\x82\xAC", 3));
  EXPECT_TRUE(g_utf8_validate(out.c_str(), static_cast<gssize>(out.size()), nullptr));
}

TEST_F(UnicodeToCharTest_2215, MapsSupplementaryPlaneEmoji_2215) {
  // U+1F600 (GRINNING FACE) => UTF-8: F0 9F 98 80
  const Unicode u[] = {static_cast<Unicode>(0x1F600)};
  std::string out = TakeAndFree(unicode_to_char(u, 1));
  EXPECT_EQ(out, std::string("\xF0\x9F\x98\x80", 4));
  EXPECT_TRUE(g_utf8_validate(out.c_str(), static_cast<gssize>(out.size()), nullptr));
}

TEST_F(UnicodeToCharTest_2215, MapsMixedSequenceConcatenatesInOrder_2215) {
  const Unicode u[] = {
      static_cast<Unicode>('A'),
      static_cast<Unicode>(0x20AC),   // €
      static_cast<Unicode>('B'),
      static_cast<Unicode>(0x1F600),  // 😀
      static_cast<Unicode>('C'),
  };
  std::string out = TakeAndFree(unicode_to_char(u, 5));
  const std::string expected =
      std::string("A") + std::string("\xE2\x82\xAC", 3) + "B" + std::string("\xF0\x9F\x98\x80", 4) + "C";
  EXPECT_EQ(out, expected);
  EXPECT_TRUE(g_utf8_validate(out.c_str(), static_cast<gssize>(out.size()), nullptr));
}

TEST_F(UnicodeToCharTest_2215, LargeInputProducesExpectedLengthForAscii_2215) {
  // Boundary-ish: large len to exercise repeated appends.
  std::vector<Unicode> u(1024, static_cast<Unicode>('a'));
  std::string out = TakeAndFree(unicode_to_char(u.data(), static_cast<int>(u.size())));
  EXPECT_EQ(out.size(), u.size());
  EXPECT_EQ(out, std::string(u.size(), 'a'));
  EXPECT_TRUE(g_utf8_validate(out.c_str(), static_cast<gssize>(out.size()), nullptr));
}

#if GTEST_HAS_DEATH_TEST
TEST_F(UnicodeToCharTest_2215, NullPointerWithPositiveLenDies_2215) {
  // Error case (observable): passing nullptr with len > 0 is invalid usage.
  // We don't assume a specific message; just that it terminates.
  EXPECT_DEATH(
      {
        // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
        gchar *s = unicode_to_char(nullptr, 1);
        // If it unexpectedly returns, free to avoid leaks.
        if (s) {
          g_free(s);
        }
      },
      ".*");
}
#endif

}  // namespace