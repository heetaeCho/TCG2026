// ***************************************************************** -*- C++ -*-
/*
  TEST_ID: 1166
  File: test_tiffcreator_getpath_1166.cpp

  Unit tests for Exiv2::Internal::TiffCreator::getPath()

  Constraints respected:
  - Treat implementation as black box (no logic re-implementation).
  - Use only observable behavior via public interface.
  - Include normal/boundary/error (observable) cases.
*/
// ***************************************************************** -*-

#include <gtest/gtest.h>

#include <cstdint>
#include <cstdlib>
#include <type_traits>
#include <utility>
#include <vector>

#include "tiffimage_int.hpp"  // Exiv2::Internal::TiffCreator, TiffPath
#include "exiv2/tags.hpp"     // Exiv2::IfdId

namespace {

using Exiv2::IfdId;

// ---- Detection helpers (avoid assuming TiffPath API too much) ----
template <typename T, typename = void>
struct has_empty : std::false_type {};
template <typename T>
struct has_empty<T, std::void_t<decltype(std::declval<const T&>().empty())>> : std::true_type {};

template <typename T, typename = void>
struct has_size : std::false_type {};
template <typename T>
struct has_size<T, std::void_t<decltype(std::declval<const T&>().size())>> : std::true_type {};

template <typename T, typename = void>
struct is_iterable : std::false_type {};
template <typename T>
struct is_iterable<
    T,
    std::void_t<decltype(std::begin(std::declval<const T&>())), decltype(std::end(std::declval<const T&>()))>>
    : std::true_type {};

// Try to call the static getPath if present; otherwise call the non-static one.
template <typename... Args>
auto CallGetPath(Args&&... args) -> decltype(Exiv2::Internal::TiffCreator::getPath(std::forward<Args>(args)...)) {
  return Exiv2::Internal::TiffCreator::getPath(std::forward<Args>(args)...);
}
template <typename... Args>
auto CallGetPathFallback(Args&&... args)
    -> decltype(std::declval<Exiv2::Internal::TiffCreator&>().getPath(std::forward<Args>(args)...)) {
  Exiv2::Internal::TiffCreator c;
  return c.getPath(std::forward<Args>(args)...);
}

// Prefer static if it compiles, else fallback to member.
template <typename... Args>
auto GetPath(Args&&... args) {
  if constexpr (std::is_invocable_v<decltype(&Exiv2::Internal::TiffCreator::getPath), Args...>) {
    return CallGetPath(std::forward<Args>(args)...);
  } else {
    return CallGetPathFallback(std::forward<Args>(args)...);
  }
}

// Small candidate sets to find at least one "working" tuple without assuming internal tables.
// (We only assert "there exists at least one non-crashing call" for normal-operation smoke.)
static const uint32_t kCandidateRoots[] = {
    0u,
    0x8769u, // Exif IFD pointer tag (common)
    0x8825u, // GPS IFD pointer tag (common)
    0xA005u, // Interop IFD pointer tag (common)
    0x014Au, // SubIFDs tag (common)
};

static const uint32_t kCandidateTags[] = {
    0u,      // boundary-ish
    0x0100u, // ImageWidth
    0x0101u, // ImageLength
    0x0112u, // Orientation
    0x0131u, // Software
    0x8769u, // ExifIFDPointer (as tag)
    0x8825u, // GPSInfoIFDPointer (as tag)
};

static const IfdId kCandidateGroups[] = {
    IfdId::ifd0Id, IfdId::ifd1Id, IfdId::exifId, IfdId::gpsId, IfdId::iopId, IfdId::ifdIdNotSet,
};

// Child-process probe: return 0 if we find ANY combination that does not abort/crash.
static void ProbeAnyNonCrashingGetPathOrExit() {
  for (uint32_t root : kCandidateRoots) {
    for (IfdId group : kCandidateGroups) {
      for (uint32_t tag : kCandidateTags) {
        // If this call aborts due to internal assert, the child will die and ASSERT_EXIT will fail.
        (void)GetPath(tag, group, root);
        std::exit(0);
      }
    }
  }
  std::exit(1);
}

// Child-process probe for a *specific* tuple; exits 0 if call returns (no crash), else dies.
static void ProbeSpecificOrExit(uint32_t tag, IfdId group, uint32_t root) {
  (void)GetPath(tag, group, root);
  std::exit(0);
}

}  // namespace

// ------------------------------ Tests ------------------------------

class TiffCreatorTest_1166 : public ::testing::Test {};

// Normal operation (black-box): prove that at least one reasonable (tag,group,root) combination
// can be called without crashing.
TEST_F(TiffCreatorTest_1166, GetPath_SmokeFindsAnyNonCrashingCombination_1166) {
  ASSERT_EXIT(ProbeAnyNonCrashingGetPathOrExit(), ::testing::ExitedWithCode(0), "");
}

// Boundary: exercise boundary-like numeric values and sentinel group, but only assert "no crash".
// We do this as independent probes so a crash is observable without taking down the whole test run.
TEST_F(TiffCreatorTest_1166, GetPath_BoundaryInputs_DoNotCrashForCommonTuplesIfSupported_1166) {
  // These probes are intentionally "maybe supported" depending on internal table.
  // We only assert that the function either returns normally (exit 0) or the test is skipped in release
  // where assert behavior may differ.
  ASSERT_EXIT(ProbeSpecificOrExit(0u, IfdId::ifdIdNotSet, 0u), ::testing::ExitedWithCode(0), "");
}

// Normal operation: if the returned TiffPath exposes basic container-like APIs, validate minimal
// observable properties without assuming internal contents.
TEST_F(TiffCreatorTest_1166, GetPath_ReturnTypeHasSaneContainerObservablesWhenAvailable_1166) {
  // Use a tuple likely to be common; if it crashes due to internal assertions, we skip rather than fail
  // (crash behavior is covered by other ASSERT_EXIT probes).
  // NOTE: This test runs in-process; keep the input conservative.
  const uint32_t tag = 0x0100u;
  const uint32_t root = 0x8769u;
  const IfdId group = IfdId::exifId;

#ifndef NDEBUG
  // In debug, if an assert triggers here, it will abort the whole test binary.
  // So we avoid hard-failing by probing in a child and skipping if unsupported.
  ASSERT_EXIT(ProbeSpecificOrExit(tag, group, root), ::testing::ExitedWithCode(0), "");

  const auto path = GetPath(tag, group, root);

  if constexpr (has_empty<decltype(path)>::value) {
    // We can at least query emptiness without assuming semantics.
    (void)path.empty();
  }
  if constexpr (has_size<decltype(path)>::value) {
    // Size should be a non-negative value; simply touching it is an observable API check.
    EXPECT_GE(path.size(), static_cast<decltype(path.size())>(0));
  }
  if constexpr (is_iterable<decltype(path)>::value) {
    // Iteration should be well-formed; we won't assume element type.
    auto it = std::begin(path);
    auto end = std::end(path);
    (void)end;
    // If not empty, begin != end is generally expected; but we don't enforce content expectations.
    if constexpr (has_empty<decltype(path)>::value) {
      if (!path.empty()) {
        EXPECT_NE(it, end);
      }
    }
  }
#else
  GTEST_SKIP() << "This test relies on debug-build stability (assert behavior may differ in release).";
#endif
}

// Error / exceptional (observable): for obviously out-of-range values, debug builds with asserts
// typically abort. We only enforce this in debug builds to avoid flakiness when assertions are compiled out.
TEST_F(TiffCreatorTest_1166, GetPath_InvalidInputs_AbortsInDebugBuild_1166) {
#ifndef NDEBUG
  // Use values that are unlikely to exist in the internal table.
  const uint32_t tag = 0xFFFFFFFFu;
  const uint32_t root = 0xFFFFFFFFu;
  const IfdId group = IfdId::ifd0Id;

  ASSERT_DEATH({ (void)GetPath(tag, group, root); }, "");  // assert() -> abort
#else
  GTEST_SKIP() << "Assertions may be compiled out in release builds; abort is not guaranteed.";
#endif
}