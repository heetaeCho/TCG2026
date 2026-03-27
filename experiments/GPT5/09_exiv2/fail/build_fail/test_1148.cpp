// =====================================================================================
// TEST_ID: 1148
// File: test_types_ur2Data_1148.cpp
// =====================================================================================

#include <gtest/gtest.h>

#include <algorithm>
#include <cstdint>
#include <vector>

#include "exiv2/types.hpp"

namespace {

class TypesUr2DataTest_1148 : public ::testing::Test {
 protected:
  static std::vector<Exiv2::byte> WriteWithUr2Data(const Exiv2::URational& r, Exiv2::ByteOrder bo, size_t& outSize) {
    std::vector<Exiv2::byte> buf(64, static_cast<Exiv2::byte>(0xAA));
    outSize = Exiv2::ur2Data(buf.data(), r, bo);
    buf.resize(outSize);
    return buf;
  }

  static std::vector<Exiv2::byte> WriteWithUl2DataTwice(const Exiv2::URational& r, Exiv2::ByteOrder bo,
                                                        size_t& outSize) {
    std::vector<Exiv2::byte> buf(64, static_cast<Exiv2::byte>(0xAA));
    size_t o = Exiv2::ul2Data(buf.data(), r.first, bo);
    o += Exiv2::ul2Data(buf.data() + o, r.second, bo);
    outSize = o;
    buf.resize(outSize);
    return buf;
  }
};

TEST_F(TypesUr2DataTest_1148, MatchesUl2DataTwice_LittleEndian_1148) {
  const Exiv2::URational r{1u, 2u};

  size_t urSize = 0;
  size_t refSize = 0;
  const auto urBuf = WriteWithUr2Data(r, Exiv2::littleEndian, urSize);
  const auto refBuf = WriteWithUl2DataTwice(r, Exiv2::littleEndian, refSize);

  EXPECT_EQ(urSize, refSize);
  EXPECT_EQ(urBuf, refBuf);
}

TEST_F(TypesUr2DataTest_1148, MatchesUl2DataTwice_BigEndian_1148) {
  const Exiv2::URational r{1u, 2u};

  size_t urSize = 0;
  size_t refSize = 0;
  const auto urBuf = WriteWithUr2Data(r, Exiv2::bigEndian, urSize);
  const auto refBuf = WriteWithUl2DataTwice(r, Exiv2::bigEndian, refSize);

  EXPECT_EQ(urSize, refSize);
  EXPECT_EQ(urBuf, refBuf);
}

TEST_F(TypesUr2DataTest_1148, ZeroNumeratorAndDenominator_1148) {
  const Exiv2::URational r{0u, 0u};

  size_t urSize = 0;
  size_t refSize = 0;
  const auto urBuf = WriteWithUr2Data(r, Exiv2::littleEndian, urSize);
  const auto refBuf = WriteWithUl2DataTwice(r, Exiv2::littleEndian, refSize);

  EXPECT_EQ(urSize, refSize);
  EXPECT_EQ(urBuf, refBuf);
}

TEST_F(TypesUr2DataTest_1148, MaxValuesBoundary_1148) {
  const Exiv2::URational r{0xFFFFFFFFu, 0xFFFFFFFFu};

  size_t urSize = 0;
  size_t refSize = 0;
  const auto urBuf = WriteWithUr2Data(r, Exiv2::bigEndian, urSize);
  const auto refBuf = WriteWithUl2DataTwice(r, Exiv2::bigEndian, refSize);

  EXPECT_EQ(urSize, refSize);
  EXPECT_EQ(urBuf, refBuf);
}

TEST_F(TypesUr2DataTest_1148, DoesNotWriteBeyondReturnedSize_1148) {
  const Exiv2::URational r{123456789u, 987654321u};

  std::vector<Exiv2::byte> buf(64, static_cast<Exiv2::byte>(0xAA));
  const size_t written = Exiv2::ur2Data(buf.data(), r, Exiv2::littleEndian);

  ASSERT_LE(written, buf.size());

  // Bytes after the returned size should remain untouched (still 0xAA).
  EXPECT_TRUE(std::all_of(buf.begin() + static_cast<std::ptrdiff_t>(written), buf.end(),
                          [](Exiv2::byte b) { return b == static_cast<Exiv2::byte>(0xAA); }));
}

TEST_F(TypesUr2DataTest_1148, DeterministicForSameInput_1148) {
  const Exiv2::URational r{42u, 17u};

  std::vector<Exiv2::byte> buf1(64, static_cast<Exiv2::byte>(0xAA));
  std::vector<Exiv2::byte> buf2(64, static_cast<Exiv2::byte>(0xAA));

  const size_t n1 = Exiv2::ur2Data(buf1.data(), r, Exiv2::bigEndian);
  const size_t n2 = Exiv2::ur2Data(buf2.data(), r, Exiv2::bigEndian);

  ASSERT_EQ(n1, n2);
  buf1.resize(n1);
  buf2.resize(n2);
  EXPECT_EQ(buf1, buf2);
}

}  // namespace