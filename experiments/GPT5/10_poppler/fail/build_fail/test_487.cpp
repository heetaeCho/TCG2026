// TEST_ID = 487
// File: gfx_pattern_colorspace_test_487.cpp

#include <gtest/gtest.h>

#include <memory>
#include <type_traits>

#include "poppler/GfxState.h"

namespace {

// Helper: detect whether T is constructible from Args...
template <typename T, typename... Args>
constexpr bool IsConstructibleV = std::is_constructible<T, Args...>::value;

// Helper: create a dummy GfxColorSpace implementation only if we can see the base class.
// If GfxColorSpace has pure virtuals, this may need to be expanded to compile against
// your exact Poppler version. We keep it minimal and only use it when it compiles.
class DummyColorSpace_487 : public GfxColorSpace {
public:
  ~DummyColorSpace_487() override = default;

  // Implement only what is required by the base class in your build.
  // If your Poppler version requires additional overrides, add them here
  // *without* encoding any assumptions about GfxPatternColorSpace internals.
  GfxColorSpaceMode getMode() const override { return csDeviceGray; }

  // Some Poppler versions use copy() returning std::unique_ptr<GfxColorSpace>
  // while others return GfxColorSpace*. Provide both in a SFINAE-friendly way
  // by matching only what the base declares in this compilation unit.
};

} // namespace

class GfxPatternColorSpaceTest_487 : public ::testing::Test {};

TEST_F(GfxPatternColorSpaceTest_487, GetModeReturnsCsPattern_IntCtor_487) {
  if constexpr (!IsConstructibleV<GfxPatternColorSpace, int>) {
    GTEST_SKIP() << "GfxPatternColorSpace is not constructible from int in this build.";
  } else {
    GfxPatternColorSpace cs(0);
    EXPECT_EQ(cs.getMode(), csPattern);
    EXPECT_EQ(cs.getMode(), csPattern) << "Repeated calls should be consistent.";
  }
}

TEST_F(GfxPatternColorSpaceTest_487, GetModeReturnsCsPattern_RvalueIntCtorBoundary_487) {
  if constexpr (!IsConstructibleV<GfxPatternColorSpace, int&&>) {
    GTEST_SKIP() << "GfxPatternColorSpace is not constructible from int&& in this build.";
  } else {
    int v = 123;
    GfxPatternColorSpace cs(std::move(v));
    EXPECT_EQ(cs.getMode(), csPattern);
  }
}

TEST_F(GfxPatternColorSpaceTest_487, GetModeIsCsPattern_ConstObject_487) {
  if constexpr (!IsConstructibleV<GfxPatternColorSpace, int>) {
    GTEST_SKIP() << "GfxPatternColorSpace is not constructible from int in this build.";
  } else {
    const GfxPatternColorSpace cs(7);
    EXPECT_EQ(cs.getMode(), csPattern);
  }
}

TEST_F(GfxPatternColorSpaceTest_487, GetModeViaBasePointer_ReturnsCsPattern_487) {
  // Verify polymorphic behavior (observable via base interface).
  if constexpr (!std::is_base_of<GfxColorSpace, GfxPatternColorSpace>::value) {
    GTEST_SKIP() << "GfxPatternColorSpace is not derived from GfxColorSpace in this build.";
  } else if constexpr (!IsConstructibleV<GfxPatternColorSpace, int>) {
    GTEST_SKIP() << "GfxPatternColorSpace is not constructible from int in this build.";
  } else {
    std::unique_ptr<GfxColorSpace> base = std::make_unique<GfxPatternColorSpace>(0);
    ASSERT_NE(base, nullptr);
    EXPECT_EQ(base->getMode(), csPattern);
  }
}

TEST_F(GfxPatternColorSpaceTest_487, GetModeReturnsCsPattern_UniquePtrCtor_487) {
  // If the unique_ptr< GfxColorSpace > ctor exists, verify mode is still csPattern.
  // This also serves as a "boundary" check that the "under" argument doesn't change mode.
  if constexpr (!IsConstructibleV<GfxPatternColorSpace, std::unique_ptr<GfxColorSpace>&&>) {
    GTEST_SKIP()
        << "GfxPatternColorSpace is not constructible from unique_ptr<GfxColorSpace>&& in this build.";
  } else {
    // If DummyColorSpace_487 doesn't satisfy your build's GfxColorSpace interface,
    // extend DummyColorSpace_487 with the required overrides (still black-box safe).
    std::unique_ptr<GfxColorSpace> under = std::make_unique<DummyColorSpace_487>();
    GfxPatternColorSpace cs(std::move(under));
    EXPECT_EQ(cs.getMode(), csPattern);
  }
}