// TestProjects/poppler/poppler/GfxStackStateSaver_test_2777.cc

#include <gtest/gtest.h>

#include <type_traits>

// NOTE:
// GfxStackStateSaver is defined in Gfx.cc (per prompt). For in-tree/unit testing of
// TU-local helpers, we include the implementation file to access the type.
#include "Gfx.cc"

namespace {

TEST(GfxStackStateSaverTest_2777, TypeTraits_CopyAndAssignDeleted_2777)
{
  // Copy/assign are explicitly deleted in the provided interface.
  static_assert(!std::is_copy_constructible<GfxStackStateSaver>::value,
                "GfxStackStateSaver must not be copy constructible");
  static_assert(!std::is_copy_assignable<GfxStackStateSaver>::value,
                "GfxStackStateSaver must not be copy assignable");

  // It should be destructible.
  static_assert(std::is_destructible<GfxStackStateSaver>::value,
                "GfxStackStateSaver should be destructible");
}

TEST(GfxStackStateSaverTest_2777, ConstructorIsExplicit_2777)
{
  // Single-arg ctor is 'explicit', so Gfx* should NOT be implicitly convertible.
  static_assert(!std::is_convertible<Gfx *, GfxStackStateSaver>::value,
                "Constructor must be explicit (no implicit conversion from Gfx*)");

  // But it should be constructible with a Gfx* argument.
  static_assert(std::is_constructible<GfxStackStateSaver, Gfx *>::value,
                "Must be constructible from Gfx*");
}

#if GTEST_HAS_DEATH_TEST
TEST(GfxStackStateSaverTest_2777, NullGfxPointerDiesOnConstruction_2777)
{
  // Observable error case: ctor unconditionally calls gfx->saveState() (per prompt),
  // so passing nullptr is expected to crash/abort.
  ASSERT_DEATH_IF_SUPPORTED(
      {
        GfxStackStateSaver saver(nullptr);
        (void)saver;
      },
      "");
}
#endif

} // namespace