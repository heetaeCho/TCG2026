// poppler-text-span-free-test_2543.cc
#include <gtest/gtest.h>

// We intentionally keep PopplerTextSpan opaque here.
// The provided interface guarantees observable safety for nullptr only (early return),
// and we must not guess struct layout/size (would be unsafe with g_slice_free()).
typedef struct _PopplerTextSpan PopplerTextSpan;

extern "C" void poppler_text_span_free(PopplerTextSpan *poppler_text_span);

namespace {

class PopplerTextSpanFreeTest_2543 : public ::testing::Test {};

TEST_F(PopplerTextSpanFreeTest_2543, NullptrDoesNotCrash_2543)
{
  EXPECT_NO_THROW(poppler_text_span_free(nullptr));
}

TEST_F(PopplerTextSpanFreeTest_2543, NullptrIsIdempotent_2543)
{
  // Boundary case: multiple calls with nullptr should remain safe.
  EXPECT_NO_THROW(poppler_text_span_free(nullptr));
  EXPECT_NO_THROW(poppler_text_span_free(nullptr));
  EXPECT_NO_THROW(poppler_text_span_free(nullptr));
}

TEST_F(PopplerTextSpanFreeTest_2543, NullptrSafeInTightLoop_2543)
{
  // Boundary/stress-ish: ensure no crash even when called repeatedly.
  for (int i = 0; i < 1000; ++i) {
    poppler_text_span_free(nullptr);
  }
  SUCCEED();
}

} // namespace