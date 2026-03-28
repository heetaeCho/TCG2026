// TEST_ID 1131
#include <gtest/gtest.h>

#include <algorithm>
#include <cstdint>
#include <iterator>
#include <type_traits>
#include <vector>

#include "exiv2/types.hpp"

namespace {

using Exiv2::byte;
using Exiv2::DataBuf;

// --- detection helpers (C++17) ---
template <typename T, typename = void>
struct has_std_begin_end : std::false_type {};
template <typename T>
struct has_std_begin_end<T, std::void_t<decltype(std::begin(std::declval<T&>())),
                                       decltype(std::end(std::declval<T&>()))>> : std::true_type {};

template <typename T, typename = void>
struct has_data_method : std::false_type {};
template <typename T>
struct has_data_method<T, std::void_t<decltype(std::declval<T&>().data())>> : std::true_type {};

template <typename T, typename = void>
struct has_size_method : std::false_type {};
template <typename T>
struct has_size_method<T, std::void_t<decltype(std::declval<T&>().size())>> : std::true_type {};

template <typename SliceLike>
std::vector<byte> SliceToVector(const SliceLike& s) {
  if constexpr (has_std_begin_end<SliceLike>::value) {
    std::vector<byte> out;
    for (auto it = std::begin(s); it != std::end(s); ++it) {
      out.push_back(static_cast<byte>(*it));
    }
    return out;
  } else if constexpr (has_data_method<SliceLike>::value && has_size_method<SliceLike>::value) {
    const auto* p = s.data();
    const auto n = static_cast<size_t>(s.size());
    return std::vector<byte>(p, p + n);
  } else {
    static_assert(has_std_begin_end<SliceLike>::value ||
                      (has_data_method<SliceLike>::value && has_size_method<SliceLike>::value),
                  "Slice must be iterable (begin/end) or provide data()/size().");
    return {};
  }
}

DataBuf MakeSequentialBuf(size_t n) {
  DataBuf buf(n);
  for (size_t i = 0; i < n; ++i) {
    buf.write_uint8(i, static_cast<uint8_t>(i & 0xFF));
  }
  return buf;
}

class MakeSliceTest_1131 : public ::testing::Test {};

}  // namespace

TEST_F(MakeSliceTest_1131, ReturnsExpectedSubrange_Normal_1131) {
  auto buf = MakeSequentialBuf(10);

  auto slice = Exiv2::makeSlice(buf, 2, 5);

  const std::vector<byte> got = SliceToVector(slice);
  ASSERT_EQ(got.size(), 3u);
  EXPECT_EQ(static_cast<uint8_t>(got[0]), 2u);
  EXPECT_EQ(static_cast<uint8_t>(got[1]), 3u);
  EXPECT_EQ(static_cast<uint8_t>(got[2]), 4u);
}

TEST_F(MakeSliceTest_1131, EmptyWhenBeginEqualsEnd_Boundary_1131) {
  auto buf = MakeSequentialBuf(8);

  EXPECT_NO_THROW({
    auto slice = Exiv2::makeSlice(buf, 3, 3);
    const std::vector<byte> got = SliceToVector(slice);
    EXPECT_TRUE(got.empty());
  });
}

TEST_F(MakeSliceTest_1131, FullRangeWhenEndEqualsSize_Boundary_1131) {
  auto buf = MakeSequentialBuf(6);

  auto slice = Exiv2::makeSlice(buf, 0, buf.size());

  const std::vector<byte> got = SliceToVector(slice);
  ASSERT_EQ(got.size(), 6u);
  for (size_t i = 0; i < got.size(); ++i) {
    EXPECT_EQ(static_cast<uint8_t>(got[i]), static_cast<uint8_t>(i));
  }
}

TEST_F(MakeSliceTest_1131, DoesNotThrowWhenEndEqualsSize_Boundary_1131) {
  auto buf = MakeSequentialBuf(1);

  EXPECT_NO_THROW({
    auto slice = Exiv2::makeSlice(buf, 0, buf.size());
    (void)slice;
  });
}

TEST_F(MakeSliceTest_1131, ThrowsWhenEndIsOutOfBounds_Error_1131) {
  auto buf = MakeSequentialBuf(4);

  EXPECT_ANY_THROW({
    auto slice = Exiv2::makeSlice(buf, 0, buf.size() + 1);
    (void)slice;
  });
}