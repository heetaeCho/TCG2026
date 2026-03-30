// TEST_ID: 939
#include <gtest/gtest.h>

#include "poppler/OptionalContent.h"

namespace {

class OCGsTest_939 : public ::testing::Test {
protected:
  // Use a default-constructed Object and nullptr XRef as the most neutral inputs.
  // We do not assume anything about parsing/validity beyond being constructible.
  Object ocgObject_;
  XRef *xref_ = nullptr;
};

TEST_F(OCGsTest_939, GetOCGs_ReturnsSameReferenceAcrossCalls_939)
{
  OCGs ocgs(ocgObject_, xref_);

  const auto *first = &ocgs.getOCGs();
  const auto *second = &ocgs.getOCGs();

  EXPECT_EQ(first, second);
}

TEST_F(OCGsTest_939, GetOCGs_WorksThroughConstObject_939)
{
  OCGs ocgs(ocgObject_, xref_);
  const OCGs &cocgs = ocgs;

  const auto *p1 = &cocgs.getOCGs();
  const auto *p2 = &cocgs.getOCGs();

  EXPECT_EQ(p1, p2);
}

TEST_F(OCGsTest_939, GetOCGs_DoesNotThrow_939)
{
  OCGs ocgs(ocgObject_, xref_);

  EXPECT_NO_THROW({
    (void)ocgs.getOCGs();
  });
}

TEST_F(OCGsTest_939, GetOCGs_AllowsSafeIteration_939)
{
  OCGs ocgs(ocgObject_, xref_);

  const auto &m = ocgs.getOCGs();

  // Boundary/robustness: iteration should be safe regardless of whether the map is empty or populated.
  size_t count = 0;
  for (const auto &kv : m) {
    (void)kv; // We don't assume anything about keys/values.
    ++count;
  }

  // Pure sanity check: count can't exceed size and should match size for an unordered_map iteration.
  EXPECT_EQ(count, m.size());
}

} // namespace