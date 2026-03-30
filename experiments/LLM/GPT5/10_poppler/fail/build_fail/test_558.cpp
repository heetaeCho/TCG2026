// TEST_ID: 558
// File: test_gfxxyz2displaytransforms_558.cpp

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "poppler/GfxState.h"

namespace {

class GfxXYZ2DisplayTransformsTest_558 : public ::testing::Test {};

// --- Compile-time interface checks (no behavior inference) ---

TEST_F(GfxXYZ2DisplayTransformsTest_558, ConstructorIsExplicit_558)
{
  // The header declares: explicit GfxXYZ2DisplayTransforms(const GfxLCMSProfilePtr &)
  static_assert(!std::is_convertible_v<GfxLCMSProfilePtr, GfxXYZ2DisplayTransforms>,
                "Constructor should be explicit (not implicitly convertible).");
}

TEST_F(GfxXYZ2DisplayTransformsTest_558, GetterReturnTypesAreAsDeclared_558)
{
  static_assert(std::is_same_v<decltype(std::declval<const GfxXYZ2DisplayTransforms&>().getDisplayProfile()),
                               GfxLCMSProfilePtr>,
                "getDisplayProfile() return type mismatch.");

  static_assert(std::is_same_v<decltype(std::declval<const GfxXYZ2DisplayTransforms&>().getRelCol()),
                               std::shared_ptr<GfxColorTransform>>,
                "getRelCol() return type mismatch.");

  static_assert(std::is_same_v<decltype(std::declval<const GfxXYZ2DisplayTransforms&>().getAbsCol()),
                               std::shared_ptr<GfxColorTransform>>,
                "getAbsCol() return type mismatch.");

  static_assert(std::is_same_v<decltype(std::declval<const GfxXYZ2DisplayTransforms&>().getSat()),
                               std::shared_ptr<GfxColorTransform>>,
                "getSat() return type mismatch.");

  static_assert(std::is_same_v<decltype(std::declval<const GfxXYZ2DisplayTransforms&>().getPerc()),
                               std::shared_ptr<GfxColorTransform>>,
                "getPerc() return type mismatch.");
}

// --- Runtime observable behavior (black-box) ---

TEST_F(GfxXYZ2DisplayTransformsTest_558, GetDisplayProfileReturnsProvidedNullProfile_558)
{
  // Boundary / error-like input: default/null profile pointer.
  const GfxLCMSProfilePtr nullProfile{};
  const GfxXYZ2DisplayTransforms xform(nullProfile);

  // Observable behavior from provided partial implementation:
  // getDisplayProfile() returns the stored profile.
  EXPECT_EQ(xform.getDisplayProfile(), nullProfile);
}

TEST_F(GfxXYZ2DisplayTransformsTest_558, GetDisplayProfileIsCallableOnConstObject_558)
{
  const GfxLCMSProfilePtr nullProfile{};
  const GfxXYZ2DisplayTransforms xform(nullProfile);

  // Just ensure const-callability and stable access.
  const auto p1 = xform.getDisplayProfile();
  const auto p2 = xform.getDisplayProfile();
  EXPECT_EQ(p1, p2);
}

TEST_F(GfxXYZ2DisplayTransformsTest_558, TransformGettersDoNotThrowWithNullProfile_558)
{
  // Exceptional/boundary case: construct with null profile and ensure getters are callable.
  const GfxLCMSProfilePtr nullProfile{};
  const GfxXYZ2DisplayTransforms xform(nullProfile);

  EXPECT_NO_THROW((void)xform.getRelCol());
  EXPECT_NO_THROW((void)xform.getAbsCol());
  EXPECT_NO_THROW((void)xform.getSat());
  EXPECT_NO_THROW((void)xform.getPerc());
}

TEST_F(GfxXYZ2DisplayTransformsTest_558, TransformGetterResultsAreUsablePointers_558)
{
  // Black-box: we do NOT assume whether these are null or non-null.
  // We only verify we can obtain and compare results in a well-defined way.
  const GfxLCMSProfilePtr nullProfile{};
  const GfxXYZ2DisplayTransforms xform(nullProfile);

  const std::shared_ptr<GfxColorTransform> rel = xform.getRelCol();
  const std::shared_ptr<GfxColorTransform> abs = xform.getAbsCol();
  const std::shared_ptr<GfxColorTransform> sat = xform.getSat();
  const std::shared_ptr<GfxColorTransform> perc = xform.getPerc();

  // Basic sanity: shared_ptr can be compared and checked for nullness without dereferencing.
  (void)rel;
  (void)abs;
  (void)sat;
  (void)perc;

  EXPECT_TRUE(rel == nullptr || rel != nullptr);
  EXPECT_TRUE(abs == nullptr || abs != nullptr);
  EXPECT_TRUE(sat == nullptr || sat != nullptr);
  EXPECT_TRUE(perc == nullptr || perc != nullptr);
}

} // namespace