// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_types_makeSlice_1132.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "exiv2/types.hpp"

namespace {

class MakeSliceTest_1132 : public ::testing::Test {};

static std::vector<Exiv2::byte> MakePatternBytes(size_t n) {
  std::vector<Exiv2::byte> v;
  v.reserve(n);
  for (size_t i = 0; i < n; ++i) {
    v.push_back(static_cast<Exiv2::byte>(i & 0xFF));
  }
  return v;
}

TEST_F(MakeSliceTest_1132, FullRangeMatchesUnderlyingBuffer_1132) {
  const auto bytes = MakePatternBytes(16);
  Exiv2::DataBuf buf(bytes.data(), bytes.size());

  const auto s = Exiv2::makeSlice(buf, 0, buf.size());

  const Exiv2::byte* it = s.begin();
  const Exiv2::byte* ed = s.end();

  ASSERT_NE(it, nullptr);
  ASSERT_EQ(static_cast<size_t>(ed - it), bytes.size());

  for (size_t i = 0; i < bytes.size(); ++i) {
    EXPECT_EQ(it[i], bytes[i]);
  }
}

TEST_F(MakeSliceTest_1132, NonZeroBeginMatchesExpectedSubrange_1132) {
  const auto bytes = MakePatternBytes(32);
  Exiv2::DataBuf buf(bytes.data(), bytes.size());

  const size_t begin = 5;
  const size_t end = 20;
  const auto s = Exiv2::makeSlice(buf, begin, end);

  const Exiv2::byte* it = s.begin();
  const Exiv2::byte* ed = s.end();

  ASSERT_NE(it, nullptr);
  ASSERT_EQ(static_cast<size_t>(ed - it), end - begin);

  for (size_t i = 0; i < (end - begin); ++i) {
    EXPECT_EQ(it[i], bytes[begin + i]);
  }
}

TEST_F(MakeSliceTest_1132, EmptySliceWhenBeginEqualsEnd_1132) {
  const auto bytes = MakePatternBytes(8);
  Exiv2::DataBuf buf(bytes.data(), bytes.size());

  const auto s = Exiv2::makeSlice(buf, 3, 3);

  const Exiv2::byte* it = s.begin();
  const Exiv2::byte* ed = s.end();

  ASSERT_NE(it, nullptr);
  EXPECT_EQ(it, ed);
}

TEST_F(MakeSliceTest_1132, EmptySliceAtStartWithZeroEnd_1132) {
  const auto bytes = MakePatternBytes(8);
  Exiv2::DataBuf buf(bytes.data(), bytes.size());

  const auto s = Exiv2::makeSlice(buf, 0, 0);

  const Exiv2::byte* it = s.begin();
  const Exiv2::byte* ed = s.end();

  ASSERT_NE(it, nullptr);
  EXPECT_EQ(it, ed);
}

TEST_F(MakeSliceTest_1132, EndEqualToSizeIsAccepted_1132) {
  const auto bytes = MakePatternBytes(10);
  Exiv2::DataBuf buf(bytes.data(), bytes.size());

  EXPECT_NO_THROW({
    const auto s = Exiv2::makeSlice(buf, 2, buf.size());
    (void)s;
  });
}

TEST_F(MakeSliceTest_1132, EndPastSizeThrows_1132) {
  const auto bytes = MakePatternBytes(10);
  Exiv2::DataBuf buf(bytes.data(), bytes.size());

  // Observable contract from the implementation: bounds check is performed on `end`.
  EXPECT_ANY_THROW({
    const auto s = Exiv2::makeSlice(buf, 0, buf.size() + 1);
    (void)s;
  });
}

TEST_F(MakeSliceTest_1132, WorksWithEmptyBufferWhenEndIsZero_1132) {
  Exiv2::DataBuf buf; // default constructed; expected to be empty

  EXPECT_NO_THROW({
    const auto s = Exiv2::makeSlice(buf, 0, 0);
    EXPECT_EQ(s.begin(), s.end());
  });
}

TEST_F(MakeSliceTest_1132, EmptyBufferWithEndNonZeroThrows_1132) {
  Exiv2::DataBuf buf; // default constructed; expected to be empty

  EXPECT_ANY_THROW({
    const auto s = Exiv2::makeSlice(buf, 0, 1);
    (void)s;
  });
}

}  // namespace