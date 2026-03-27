// TEST_ID 610
// Unit tests for Exiv2::RemoteIo::mmap(bool)
//
// Constraints adhered to:
// - Treat RemoteIo as a black box (tests only observe public behavior).
// - No access to private/internal state.
// - No re-implementation of logic.
// - Tests are resilient to constructor availability by conditionally constructing
//   RemoteIo using common signatures; otherwise they GTEST_SKIP().

#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <type_traits>

// Prefer the installed/public Exiv2 headers.
// (If your build uses different include paths, adjust accordingly.)
#include <exiv2/basicio.hpp>

namespace {

class RemoteIoMmapTest_610 : public ::testing::Test {
protected:
  using RemoteIo = Exiv2::RemoteIo;

  static std::unique_ptr<RemoteIo> tryMake() {
    // Try a few common constructor shapes without assuming any are present.
    // If none exist in this build, tests will be skipped.
    try {
      if constexpr (std::is_default_constructible_v<RemoteIo>) {
        return std::make_unique<RemoteIo>();
      } else if constexpr (std::is_constructible_v<RemoteIo, const std::string&>) {
        return std::make_unique<RemoteIo>(std::string{});
      } else if constexpr (std::is_constructible_v<RemoteIo, std::string>) {
        return std::make_unique<RemoteIo>(std::string{});
      } else if constexpr (std::is_constructible_v<RemoteIo, const char*>) {
        return std::make_unique<RemoteIo>("");
      } else {
        return nullptr;
      }
    } catch (...) {
      // If construction throws for the attempted signature, treat as unavailable
      // for these black-box tests (we don't assume error semantics).
      return nullptr;
    }
  }
};

TEST_F(RemoteIoMmapTest_610, MmapDoesNotThrowForEitherFlag_610) {
  auto io = tryMake();
  if (!io) GTEST_SKIP() << "Exiv2::RemoteIo could not be constructed with available/known signatures.";

  EXPECT_NO_THROW((void)io->mmap(false));
  EXPECT_NO_THROW((void)io->mmap(true));
}

TEST_F(RemoteIoMmapTest_610, MmapReturnsStablePointerAcrossRepeatedCalls_610) {
  auto io = tryMake();
  if (!io) GTEST_SKIP() << "Exiv2::RemoteIo could not be constructed with available/known signatures.";

  // Observed behavior: mmap returns a pointer. We verify repeatability of the
  // returned mapping address across repeated calls on the same instance.
  // (If the implementation returns nullptr, stability still holds.)
  Exiv2::byte* p1 = nullptr;
  Exiv2::byte* p2 = nullptr;

  ASSERT_NO_THROW(p1 = io->mmap(false));
  ASSERT_NO_THROW(p2 = io->mmap(false));

  EXPECT_EQ(p1, p2);
}

TEST_F(RemoteIoMmapTest_610, MmapPointerIsIndependentOfWriteableFlag_610) {
  auto io = tryMake();
  if (!io) GTEST_SKIP() << "Exiv2::RemoteIo could not be constructed with available/known signatures.";

  Exiv2::byte* pr = nullptr;
  Exiv2::byte* pw = nullptr;

  ASSERT_NO_THROW(pr = io->mmap(false));
  ASSERT_NO_THROW(pw = io->mmap(true));

  // Observable external behavior: mapping pointer identity for the same instance.
  EXPECT_EQ(pr, pw);
}

TEST_F(RemoteIoMmapTest_610, MmapCanBeCalledMultipleTimesWithoutCrashing_610) {
  auto io = tryMake();
  if (!io) GTEST_SKIP() << "Exiv2::RemoteIo could not be constructed with available/known signatures.";

  // Boundary-ish: repeated calls, alternating flags.
  Exiv2::byte* last = nullptr;
  for (int i = 0; i < 10; ++i) {
    Exiv2::byte* p = nullptr;
    const bool flag = (i % 2) == 0;
    ASSERT_NO_THROW(p = io->mmap(flag));
    if (i == 0) {
      last = p;
    } else {
      EXPECT_EQ(last, p);
    }
  }
}

}  // namespace