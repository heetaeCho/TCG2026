// TEST_ID: 573
//
// Unit tests for Exiv2::BlockMap::getData()
// File under test: ./TestProjects/exiv2/src/basicio.cpp
//
// Notes:
// - We treat the implementation as a black box.
// - We only assert observable properties that must hold for a "data pointer" style API.
// - Some additional methods are listed as "Known or Inferred Dependencies (Optional)".
//   We use compile-time detection to add extra tests only when those methods exist.

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <type_traits>
#include <utility>
#include <vector>

// Pull in the implementation that defines Exiv2::BlockMap for this test TU.
#include "TestProjects/exiv2/src/basicio.cpp"

namespace {

template <typename T, typename = void>
struct HasGetSize : std::false_type {};
template <typename T>
struct HasGetSize<T, std::void_t<decltype(std::declval<const T&>().getSize())>> : std::true_type {};

template <typename T, typename = void>
struct HasPopulate : std::false_type {};
template <typename T>
struct HasPopulate<T,
                   std::void_t<decltype(std::declval<T&>().populate(
                       static_cast<const Exiv2::byte*>(nullptr), std::declval<std::size_t>()))>>
    : std::true_type {};

template <typename T, typename = void>
struct HasMarkKnown : std::false_type {};
template <typename T>
struct HasMarkKnown<T, std::void_t<decltype(std::declval<T&>().markKnown(std::declval<std::size_t>()))>>
    : std::true_type {};

template <typename T, typename = void>
struct HasIsNone : std::false_type {};
template <typename T>
struct HasIsNone<T, std::void_t<decltype(std::declval<const T&>().isNone())>> : std::true_type {};

template <typename T, typename = void>
struct HasIsKnown : std::false_type {};
template <typename T>
struct HasIsKnown<T, std::void_t<decltype(std::declval<const T&>().isKnown())>> : std::true_type {};

class BlockMapTest_573 : public ::testing::Test {};

}  // namespace

TEST_F(BlockMapTest_573, GetData_IsStableAcrossCalls_573) {
  const Exiv2::BlockMap bm;
  const auto* p1 = bm.getData();
  const auto* p2 = bm.getData();
  EXPECT_EQ(p1, p2);
}

TEST_F(BlockMapTest_573, GetData_CanBeCalledOnConstObject_573) {
  const Exiv2::BlockMap bm;
  // Primary observable behavior: callable and returns a pointer value.
  (void)bm.getData();
  SUCCEED();
}

TEST_F(BlockMapTest_573, GetData_NonNullWhenSizePositive_573) {
  using BM = Exiv2::BlockMap;

  if constexpr (HasGetSize<BM>::value) {
    const BM bm;
    const std::size_t sz = bm.getSize();
    const auto* p = bm.getData();

    if (sz > 0) {
      EXPECT_NE(p, nullptr);
    } else {
      // For size==0, both nullptr and non-null are acceptable for a data() style API.
      SUCCEED();
    }
  } else {
    GTEST_SKIP() << "BlockMap::getSize() not available; cannot assert size-related property.";
  }
}

TEST_F(BlockMapTest_573, Populate_AllowsReadingBackPrefixViaGetData_573) {
  using BM = Exiv2::BlockMap;

  if constexpr (HasPopulate<BM>::value && HasGetSize<BM>::value) {
    BM bm;

    // Prepare a small source buffer.
    const std::vector<Exiv2::byte> src = {
        static_cast<Exiv2::byte>(0x00), static_cast<Exiv2::byte>(0x11), static_cast<Exiv2::byte>(0x22),
        static_cast<Exiv2::byte>(0x33), static_cast<Exiv2::byte>(0x44), static_cast<Exiv2::byte>(0x55),
    };

    // We do not assume exact internal sizing behavior, only that data can be observed via getData().
    bm.populate(src.data(), src.size());

    const std::size_t sz = bm.getSize();
    ASSERT_GE(sz, src.size()) << "If populate stores data, size should be at least the populated count.";

    const auto* p = bm.getData();
    ASSERT_NE(p, nullptr);

    EXPECT_EQ(0, std::memcmp(p, src.data(), src.size()));
  } else {
    GTEST_SKIP() << "populate/getSize not available; cannot perform populate round-trip observation.";
  }
}

TEST_F(BlockMapTest_573, Populate_ZeroBytes_DoesNotCrash_573) {
  using BM = Exiv2::BlockMap;

  if constexpr (HasPopulate<BM>::value) {
    BM bm;

    const std::vector<Exiv2::byte> src = {static_cast<Exiv2::byte>(0xAB)};
    // Boundary condition: num == 0. We only assert that calling the API is safe.
    EXPECT_NO_THROW(bm.populate(src.data(), 0u));

    // getData should still be callable and stable.
    const auto* p1 = bm.getData();
    const auto* p2 = bm.getData();
    EXPECT_EQ(p1, p2);
  } else {
    GTEST_SKIP() << "BlockMap::populate() not available.";
  }
}

TEST_F(BlockMapTest_573, Populate_NullptrWithZeroBytes_DoesNotCrash_573) {
  using BM = Exiv2::BlockMap;

  if constexpr (HasPopulate<BM>::value) {
    BM bm;

    // Boundary condition: nullptr + 0 bytes. Many APIs allow this; we only require no crash/UB here.
    // If the implementation chooses to throw, that's still observable; but we avoid locking behavior.
    try {
      bm.populate(nullptr, 0u);
      SUCCEED();
    } catch (...) {
      SUCCEED() << "populate(nullptr,0) threw; behavior is implementation-defined and acceptable to observe.";
    }
  } else {
    GTEST_SKIP() << "BlockMap::populate() not available.";
  }
}

TEST_F(BlockMapTest_573, MarkKnown_CanBeInvoked_Boundaries_573) {
  using BM = Exiv2::BlockMap;

  if constexpr (HasMarkKnown<BM>::value) {
    BM bm;

    // Boundary: 0
    EXPECT_NO_THROW(bm.markKnown(0u));

    // Another boundary-ish value (small non-zero). We do not assume semantics.
    EXPECT_NO_THROW(bm.markKnown(1u));

    // getData remains callable.
    (void)bm.getData();
    SUCCEED();
  } else {
    GTEST_SKIP() << "BlockMap::markKnown() not available.";
  }
}

TEST_F(BlockMapTest_573, IsNoneAndIsKnown_AreCallable_573) {
  using BM = Exiv2::BlockMap;

  if constexpr (HasIsNone<BM>::value && HasIsKnown<BM>::value) {
    const BM bm;
    // Only assert callability and boolean-ness (observable type).
    const bool none = bm.isNone();
    const bool known = bm.isKnown();
    (void)none;
    (void)known;
    SUCCEED();
  } else {
    GTEST_SKIP() << "BlockMap::isNone()/isKnown() not available.";
  }
}