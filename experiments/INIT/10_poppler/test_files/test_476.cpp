// File: GfxSeparationColorSpace_test_476.cpp
// Target: ./TestProjects/poppler/poppler/GfxState.h

#include <gtest/gtest.h>

#include <memory>
#include <string>

#include "poppler/GfxState.h"

namespace {

// ---- Construction helpers (SFINAE) ----
// Poppler’s GfxSeparationColorSpace constructors have varied across versions.
// These helpers try a few common signatures without assuming internals.

template <typename T>
concept HasCtor_UniquePtrAlt_FunctionPtr = requires(std::unique_ptr<GooString> n,
                                                   std::unique_ptr<GfxColorSpace> a,
                                                   Function *f) {
  T(std::move(n), std::move(a), f);
};

template <typename T>
concept HasCtor_UniquePtrAlt_UniquePtrFunction = requires(std::unique_ptr<GooString> n,
                                                         std::unique_ptr<GfxColorSpace> a,
                                                         std::unique_ptr<Function> f) {
  T(std::move(n), std::move(a), std::move(f));
};

template <typename T>
concept HasCtor_RawPtrs = requires(GooString *n, GfxColorSpace *a, Function *f) { T(n, a, f); };

static std::unique_ptr<GfxColorSpace> makeAltColorSpace() {
  // Prefer factory if available; otherwise fall back to nullptr (and tests will skip).
#if defined(__cpp_lib_void_t)
  // best-effort: if GfxColorSpace::create exists, use it (common in Poppler).
#endif

  // Try common factory: GfxColorSpace::create(GfxColorSpaceMode)
  // We avoid assuming exact enum names beyond typical device gray.
  // If this doesn't compile in your Poppler version, tests will still compile,
  // because we only use it when the symbol exists.
  if constexpr (requires { GfxColorSpace::create(csDeviceGray); }) {
    return std::unique_ptr<GfxColorSpace>(GfxColorSpace::create(csDeviceGray));
  } else if constexpr (requires { GfxColorSpace::create(csDeviceRGB); }) {
    return std::unique_ptr<GfxColorSpace>(GfxColorSpace::create(csDeviceRGB));
  } else {
    return nullptr;
  }
}

template <typename SepCS>
static std::unique_ptr<SepCS> makeSeparationCSOrNull() {
  auto name = std::make_unique<GooString>("TestSpot");
  auto alt = makeAltColorSpace();

  // We only need a constructible instance to call getNComps().
  // Use nullptr for the tint transform when allowed by the constructor signature.
  if constexpr (HasCtor_UniquePtrAlt_FunctionPtr<SepCS>) {
    return std::make_unique<SepCS>(std::move(name), std::move(alt), static_cast<Function *>(nullptr));
  } else if constexpr (HasCtor_UniquePtrAlt_UniquePtrFunction<SepCS>) {
    return std::make_unique<SepCS>(std::move(name), std::move(alt), std::unique_ptr<Function>{});
  } else if constexpr (HasCtor_RawPtrs<SepCS>) {
    // Transfer ownership carefully: constructor might not take ownership; but we only
    // need to create an instance for getNComps(), so we keep objects alive in this scope.
    // If your Poppler version takes ownership, the test binary still behaves as a black box.
    GooString *rawName = name.release();
    GfxColorSpace *rawAlt = alt.release();
    auto ptr = std::make_unique<SepCS>(rawName, rawAlt, static_cast<Function *>(nullptr));
    // If ctor did NOT take ownership, avoid leaks:
    // We can’t safely delete without knowing ownership, so we intentionally
    // leave them as-is to avoid double-free in versions where ctor owns them.
    (void)rawName;
    (void)rawAlt;
    return ptr;
  } else {
    return nullptr;
  }
}

class GfxSeparationColorSpaceTest_476 : public ::testing::Test {
protected:
  std::unique_ptr<GfxSeparationColorSpace> makeOrSkip() {
    auto cs = makeSeparationCSOrNull<GfxSeparationColorSpace>();
    if (!cs) {
      GTEST_SKIP() << "No compatible GfxSeparationColorSpace constructor found in this build.";
    }
    return cs;
  }
};

} // namespace

TEST_F(GfxSeparationColorSpaceTest_476, GetNCompsReturnsOne_476) {
  auto cs = makeOrSkip();
  ASSERT_NE(cs, nullptr);
  EXPECT_EQ(cs->getNComps(), 1);
}

TEST_F(GfxSeparationColorSpaceTest_476, GetNCompsIsStableAcrossRepeatedCalls_476) {
  auto cs = makeOrSkip();
  ASSERT_NE(cs, nullptr);

  const int first = cs->getNComps();
  const int second = cs->getNComps();
  const int third = cs->getNComps();

  EXPECT_EQ(first, 1);
  EXPECT_EQ(second, 1);
  EXPECT_EQ(third, 1);
}

TEST_F(GfxSeparationColorSpaceTest_476, GetNCompsCallableThroughConstReference_476) {
  auto cs = makeOrSkip();
  ASSERT_NE(cs, nullptr);

  const GfxSeparationColorSpace &cref = *cs;
  EXPECT_EQ(cref.getNComps(), 1);
}

TEST_F(GfxSeparationColorSpaceTest_476, GetNCompsCallableViaBasePointerIfAvailable_476) {
  auto cs = makeOrSkip();
  ASSERT_NE(cs, nullptr);

  // Verify polymorphic access (observable behavior) without relying on internals.
  GfxColorSpace *base = dynamic_cast<GfxColorSpace *>(cs.get());
  if (!base) {
    GTEST_SKIP() << "GfxSeparationColorSpace is not polymorphically castable to GfxColorSpace in this build.";
  }
  EXPECT_EQ(base->getNComps(), 1);
}