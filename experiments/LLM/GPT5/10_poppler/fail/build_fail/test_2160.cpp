// File: poppler-dest-compare-keys-test_2160.cc
//
// Unit tests for:
//   static gint _poppler_dest_compare_keys(gconstpointer a, gconstpointer b, gpointer /*user_data*/)
//
// Constraints note:
// - We treat the function as a black box and only verify observable behavior via return values.
// - We do not rely on internal state.
// - We include normal, boundary, and error-ish (NULL) cases.

#include <gtest/gtest.h>

#include <glib.h>

// Forward declaration of the function under test (it is `static` in the .cc file).
// In your build, ensure this test is compiled in a way that can link to the symbol.
// Common approaches in this codebase are:
//  - compiling this test TU by including the implementation .cc, or
//  - building the test in the same TU, or
//  - exposing a test hook wrapper (if already present).
extern "C" gint _poppler_dest_compare_keys(gconstpointer a, gconstpointer b, gpointer user_data);

namespace {

class PopplerDestCompareKeysTest_2160 : public ::testing::Test {};

TEST_F(PopplerDestCompareKeysTest_2160, EqualStringsReturnZero_2160) {
  const gchar* a = "KeyA";
  const gchar* b = "KeyA";

  gint r = _poppler_dest_compare_keys(static_cast<gconstpointer>(a),
                                     static_cast<gconstpointer>(b),
                                     nullptr);

  EXPECT_EQ(r, 0);
}

TEST_F(PopplerDestCompareKeysTest_2160, LexicographicLessReturnsNegative_2160) {
  const gchar* a = "A";
  const gchar* b = "B";

  gint r = _poppler_dest_compare_keys(static_cast<gconstpointer>(a),
                                     static_cast<gconstpointer>(b),
                                     nullptr);

  EXPECT_LT(r, 0);
}

TEST_F(PopplerDestCompareKeysTest_2160, LexicographicGreaterReturnsPositive_2160) {
  const gchar* a = "B";
  const gchar* b = "A";

  gint r = _poppler_dest_compare_keys(static_cast<gconstpointer>(a),
                                     static_cast<gconstpointer>(b),
                                     nullptr);

  EXPECT_GT(r, 0);
}

TEST_F(PopplerDestCompareKeysTest_2160, PrefixShorterIsLess_2160) {
  const gchar* a = "abc";
  const gchar* b = "abcd";

  gint r = _poppler_dest_compare_keys(static_cast<gconstpointer>(a),
                                     static_cast<gconstpointer>(b),
                                     nullptr);

  EXPECT_LT(r, 0);
}

TEST_F(PopplerDestCompareKeysTest_2160, NullVsNullReturnsZero_2160) {
  gint r = _poppler_dest_compare_keys(nullptr, nullptr, nullptr);
  EXPECT_EQ(r, 0);
}

TEST_F(PopplerDestCompareKeysTest_2160, NullVsNonNullReturnsNegative_2160) {
  const gchar* b = "non-null";
  gint r = _poppler_dest_compare_keys(nullptr, static_cast<gconstpointer>(b), nullptr);
  EXPECT_LT(r, 0);
}

TEST_F(PopplerDestCompareKeysTest_2160, NonNullVsNullReturnsPositive_2160) {
  const gchar* a = "non-null";
  gint r = _poppler_dest_compare_keys(static_cast<gconstpointer>(a), nullptr, nullptr);
  EXPECT_GT(r, 0);
}

TEST_F(PopplerDestCompareKeysTest_2160, UserDataDoesNotAffectResult_2160) {
  const gchar* a = "A";
  const gchar* b = "B";

  gint r1 = _poppler_dest_compare_keys(static_cast<gconstpointer>(a),
                                      static_cast<gconstpointer>(b),
                                      nullptr);

  gpointer dummy = reinterpret_cast<gpointer>(0x1);
  gint r2 = _poppler_dest_compare_keys(static_cast<gconstpointer>(a),
                                      static_cast<gconstpointer>(b),
                                      dummy);

  // Observable contract: comparator result should depend only on keys; user_data is ignored.
  EXPECT_EQ((r1 < 0), (r2 < 0));
  EXPECT_EQ((r1 > 0), (r2 > 0));
  EXPECT_EQ((r1 == 0), (r2 == 0));
}

}  // namespace