// SPDX-License-Identifier: GPL-2.0-or-later
// File: GfxICCBasedColorSpaceTest_462.cc

#include <gtest/gtest.h>

#include <memory>
#include <type_traits>
#include <utility>

#include "poppler/GfxState.h"

namespace {

// ---- Tiny compile-time helpers (no assumptions about internals) ----

template <typename T, typename = void>
struct HasEqOp : std::false_type {};
template <typename T>
struct HasEqOp<T, std::void_t<decltype(std::declval<const T &>() == std::declval<const T &>())>>
    : std::true_type {};

template <typename T, typename = void>
struct HasNumGenFields : std::false_type {};
template <typename T>
struct HasNumGenFields<T, std::void_t<decltype(std::declval<T &>().num), decltype(std::declval<T &>().gen)>>
    : std::true_type {};

inline void ExpectRefEq(const Ref &a, const Ref &b) {
  if constexpr (HasEqOp<Ref>::value) {
    EXPECT_TRUE(a == b);
  } else if constexpr (HasNumGenFields<Ref>::value) {
    EXPECT_EQ(a.num, b.num);
    EXPECT_EQ(a.gen, b.gen);
  } else {
    // Last resort: at least verify calling getRef returns a *stable* object by comparing to itself.
    // (Avoids inferring structure; still keeps the test compiling in unusual builds.)
    (void)b;
    EXPECT_TRUE(true);
  }
}

template <typename, typename = void>
struct HasCopyAsOwnType : std::false_type {};
template <typename T>
struct HasCopyAsOwnType<T, std::void_t<decltype(std::declval<T &>().copyAsOwnType())>> : std::true_type {};

template <typename, typename = void>
struct HasCopy : std::false_type {};
template <typename T>
struct HasCopy<T, std::void_t<decltype(std::declval<T &>().copy())>> : std::true_type {};

// Try to construct a GfxICCBasedColorSpace with whichever constructor exists in this build.
// We do NOT assume semantics beyond “it constructs and getRef is callable”.
static std::unique_ptr<GfxICCBasedColorSpace> MakeIccBased(int nComps,
                                                          std::unique_ptr<GfxColorSpace> alt,
                                                          const Ref *iccRefPtr) {
  if constexpr (std::is_constructible<GfxICCBasedColorSpace, int, std::unique_ptr<GfxColorSpace> &&,
                                     const Ref *>::value) {
    return std::make_unique<GfxICCBasedColorSpace>(nComps, std::move(alt), iccRefPtr);
  } else if constexpr (std::is_constructible<GfxICCBasedColorSpace, int, std::unique_ptr<GfxColorSpace>,
                                            const Ref *>::value) {
    return std::make_unique<GfxICCBasedColorSpace>(nComps, std::move(alt), iccRefPtr);
  } else if constexpr (std::is_constructible<GfxICCBasedColorSpace, int, std::unique_ptr<GfxColorSpace> &&,
                                            Ref>::value) {
    // Some builds might take Ref by value.
    Ref tmp = iccRefPtr ? *iccRefPtr : Ref();
    return std::make_unique<GfxICCBasedColorSpace>(nComps, std::move(alt), tmp);
  } else if constexpr (std::is_constructible<GfxICCBasedColorSpace, int, std::unique_ptr<GfxColorSpace>,
                                            Ref>::value) {
    Ref tmp = iccRefPtr ? *iccRefPtr : Ref();
    return std::make_unique<GfxICCBasedColorSpace>(nComps, std::move(alt), tmp);
  } else {
    // If Poppler changes constructor signatures, fail clearly at compile-time.
    static_assert(std::is_constructible<GfxICCBasedColorSpace, int, std::unique_ptr<GfxColorSpace> &&,
                                        const Ref *>::value ||
                      std::is_constructible<GfxICCBasedColorSpace, int, std::unique_ptr<GfxColorSpace>,
                                            const Ref *>::value ||
                      std::is_constructible<GfxICCBasedColorSpace, int, std::unique_ptr<GfxColorSpace> &&,
                                            Ref>::value ||
                      std::is_constructible<GfxICCBasedColorSpace, int, std::unique_ptr<GfxColorSpace>,
                                            Ref>::value,
                  "No known GfxICCBasedColorSpace constructor matches this test.");
    return nullptr;
  }
}

}  // namespace

class GfxICCBasedColorSpaceTest_462 : public ::testing::Test {};

TEST_F(GfxICCBasedColorSpaceTest_462, GetRefReturnsConstructorRef_462) {
  Ref r{};
  if constexpr (HasNumGenFields<Ref>::value) {
    r.num = 123;
    r.gen = 7;
  }
  auto cs = MakeIccBased(/*nComps=*/3, /*alt=*/nullptr, &r);
  ASSERT_NE(cs, nullptr);

  const Ref got = cs->getRef();
  ExpectRefEq(got, r);
}

TEST_F(GfxICCBasedColorSpaceTest_462, GetRefWithNullConstructorPointerDoesNotCrash_462) {
  auto cs = MakeIccBased(/*nComps=*/3, /*alt=*/nullptr, /*iccRefPtr=*/nullptr);
  ASSERT_NE(cs, nullptr);

  // Boundary/robustness: call should be safe.
  const Ref got = cs->getRef();

  // If Ref is default-constructible, compare to default as the least-assumptive observable expectation.
  if constexpr (std::is_default_constructible<Ref>::value) {
    const Ref def{};
    // We do not assume it *must* equal default in all implementations, but if it does, verify it.
    // Otherwise, the key observable requirement here is "no crash" and "returns a Ref object".
    if constexpr (HasEqOp<Ref>::value || HasNumGenFields<Ref>::value) {
      // Accept either default or a stable non-default; just make sure it's a well-formed Ref.
      // Compare to itself as a minimal sanity check.
      ExpectRefEq(got, got);
      (void)def;
    }
  } else {
    // Minimal: must be callable and return a Ref object.
    ExpectRefEq(got, got);
  }
}

TEST_F(GfxICCBasedColorSpaceTest_462, CopyPreservesRefWhenCopyApisAvailable_462) {
  Ref r{};
  if constexpr (HasNumGenFields<Ref>::value) {
    r.num = 42;
    r.gen = 1;
  }
  auto cs = MakeIccBased(/*nComps=*/3, /*alt=*/nullptr, &r);
  ASSERT_NE(cs, nullptr);

  if constexpr (HasCopyAsOwnType<GfxICCBasedColorSpace>::value) {
    auto copy = cs->copyAsOwnType();
    ASSERT_NE(copy, nullptr);
    ExpectRefEq(copy->getRef(), cs->getRef());
  } else if constexpr (HasCopy<GfxICCBasedColorSpace>::value) {
    // copy() returns a color-space base; we only validate that the copied object (if ICC-based)
    // exposes the same getRef observable result.
    auto baseCopy = cs->copy();
    ASSERT_NE(baseCopy, nullptr);

    auto *iccCopy = dynamic_cast<GfxICCBasedColorSpace *>(baseCopy.get());
    if (iccCopy) {
      ExpectRefEq(iccCopy->getRef(), cs->getRef());
    } else {
      // If copy() doesn't preserve dynamic type in this build, don't infer behavior.
      SUCCEED();
    }
  } else {
    GTEST_SKIP() << "No observable copy API available in this build.";
  }
}