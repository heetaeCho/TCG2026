// poppler-page-transition-copy-test.cc
#include <gtest/gtest.h>

extern "C" {
#include "poppler-page.h"
}

// The function under test (implemented in poppler-page.cc):
// PopplerPageTransition *poppler_page_transition_copy(PopplerPageTransition *transition);

namespace {

struct TransitionDeleter {
  void operator()(PopplerPageTransition* t) const {
    if (!t)
      return;
    // poppler-glib typically exposes a free function for this boxed struct.
    poppler_page_transition_free(t);
  }
};

using TransitionPtr = std::unique_ptr<PopplerPageTransition, TransitionDeleter>;

static PopplerPageTransition MakeTransition(int type,
                                            int alignment,
                                            int direction,
                                            int scale,
                                            int rectangular,
                                            int duration_real) {
  PopplerPageTransition t{};
  t.type = static_cast<PopplerPageTransitionType>(type);
  t.alignment = static_cast<PopplerPageTransitionAlignment>(alignment);
  t.direction = static_cast<PopplerPageTransitionDirection>(direction);
  t.scale = scale;
  t.rectangular = rectangular;
  t.duration_real = duration_real;
  return t;
}

static void ExpectTransitionEq(const PopplerPageTransition& a, const PopplerPageTransition& b) {
  EXPECT_EQ(a.type, b.type);
  EXPECT_EQ(a.alignment, b.alignment);
  EXPECT_EQ(a.direction, b.direction);
  EXPECT_EQ(a.scale, b.scale);
  EXPECT_EQ(a.rectangular, b.rectangular);
  EXPECT_EQ(a.duration_real, b.duration_real);
}

}  // namespace

TEST(PopplerPageTransitionCopyTest_2490, ReturnsNewNonNullPointer_2490) {
  TransitionPtr src(poppler_page_transition_new());
  ASSERT_NE(src.get(), nullptr);

  // Set some values (don’t assume any defaults).
  *src = MakeTransition(/*type=*/0, /*alignment=*/1, /*direction=*/2,
                        /*scale=*/100, /*rectangular=*/1, /*duration_real=*/3);

  TransitionPtr dst(poppler_page_transition_copy(src.get()));
  ASSERT_NE(dst.get(), nullptr);
  EXPECT_NE(dst.get(), src.get());
}

TEST(PopplerPageTransitionCopyTest_2490, CopiesAllFieldsExactly_2490) {
  TransitionPtr src(poppler_page_transition_new());
  ASSERT_NE(src.get(), nullptr);

  PopplerPageTransition expected =
      MakeTransition(/*type=*/2, /*alignment=*/0, /*direction=*/1,
                     /*scale=*/42, /*rectangular=*/0, /*duration_real=*/999);

  *src = expected;

  TransitionPtr dst(poppler_page_transition_copy(src.get()));
  ASSERT_NE(dst.get(), nullptr);

  ExpectTransitionEq(*dst, expected);
}

TEST(PopplerPageTransitionCopyTest_2490, CopyIsIndependentFromSourceAfterCopy_2490) {
  TransitionPtr src(poppler_page_transition_new());
  ASSERT_NE(src.get(), nullptr);

  PopplerPageTransition initial =
      MakeTransition(/*type=*/1, /*alignment=*/1, /*direction=*/1,
                     /*scale=*/7, /*rectangular=*/1, /*duration_real=*/11);
  *src = initial;

  TransitionPtr dst(poppler_page_transition_copy(src.get()));
  ASSERT_NE(dst.get(), nullptr);

  // Mutate the source after copying; copy should retain original values.
  *src = MakeTransition(/*type=*/3, /*alignment=*/2, /*direction=*/0,
                        /*scale=*/1234, /*rectangular=*/0, /*duration_real=*/-5);

  ExpectTransitionEq(*dst, initial);
}

TEST(PopplerPageTransitionCopyTest_2490, PreservesExtremeAndNegativeIntegers_2490) {
  TransitionPtr src(poppler_page_transition_new());
  ASSERT_NE(src.get(), nullptr);

  PopplerPageTransition expected =
      MakeTransition(/*type=*/-1, /*alignment=*/123, /*direction=*/-7,
                     /*scale=*/INT32_MIN, /*rectangular=*/INT32_MAX, /*duration_real=*/-999999);

  *src = expected;

  TransitionPtr dst(poppler_page_transition_copy(src.get()));
  ASSERT_NE(dst.get(), nullptr);

  ExpectTransitionEq(*dst, expected);
}

#if GTEST_HAS_DEATH_TEST
TEST(PopplerPageTransitionCopyTest_2490, NullInputDiesOrCrashes_2490) {
  // The interface does not specify nullptr handling. If it is invalid, a crash is observable.
  // This test documents that passing nullptr is not supported (or must be handled).
  ASSERT_DEATH(
      {
        volatile PopplerPageTransition* out = poppler_page_transition_copy(nullptr);
        (void)out;
      },
      ".*");
}
#endif