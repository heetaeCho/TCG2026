// CairoOutputDev_type3GlyphHasColor_1736_test.cc
#include <gtest/gtest.h>

#include "CairoOutputDev.h"

namespace {

class CairoOutputDevTest_1736 : public ::testing::Test {
protected:
  CairoOutputDevTest_1736() = default;
  ~CairoOutputDevTest_1736() override = default;
};

// Normal operation: callable on a default-constructed instance and returns a bool.
TEST_F(CairoOutputDevTest_1736, Type3GlyphHasColor_DefaultConstruct_Callable_1736)
{
  CairoOutputDev dev;
  EXPECT_NO_THROW({
    const bool v = dev.type3GlyphHasColor();
    (void)v;
  });
}

// Boundary-ish: callable on a const instance (const-correctness) and stable across repeated calls
// when no other observable operations are performed.
TEST_F(CairoOutputDevTest_1736, Type3GlyphHasColor_ConstAndRepeatable_1736)
{
  const CairoOutputDev dev;

  const bool v1 = dev.type3GlyphHasColor();
  const bool v2 = dev.type3GlyphHasColor();
  const bool v3 = dev.type3GlyphHasColor();

  EXPECT_EQ(v1, v2);
  EXPECT_EQ(v2, v3);
}

// Boundary: works when accessed through an owning pointer (lifetime/indirection safety).
TEST_F(CairoOutputDevTest_1736, Type3GlyphHasColor_ThroughPointer_1736)
{
  auto dev = std::make_unique<CairoOutputDev>();

  const bool v1 = dev->type3GlyphHasColor();
  const bool v2 = dev->type3GlyphHasColor();

  EXPECT_EQ(v1, v2);
}

} // namespace