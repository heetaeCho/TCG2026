// ============================================================================
// TEST_ID: 1129
// File: test_types_databuf_c_str_1129.cpp
// Unit tests for Exiv2::DataBuf::c_str(size_t offset) const
// ============================================================================

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "exiv2/types.hpp"

namespace {

class DataBufCStrTest_1129 : public ::testing::Test {
 protected:
  static std::vector<Exiv2::byte> MakeBytes(const std::initializer_list<uint8_t>& vals) {
    std::vector<Exiv2::byte> out;
    out.reserve(vals.size());
    for (auto v : vals) out.push_back(static_cast<Exiv2::byte>(v));
    return out;
  }
};

TEST_F(DataBufCStrTest_1129, DefaultConstructedOffset0_ReturnsSameAddressAsCData_1129) {
  const Exiv2::DataBuf buf;
  const char* s = buf.c_str(0);
  const Exiv2::byte* p = buf.c_data(0);

  // Observable behavior: c_str is a reinterpret_cast of c_data at the same offset.
  EXPECT_EQ(reinterpret_cast<const void*>(s), reinterpret_cast<const void*>(p));
}

TEST_F(DataBufCStrTest_1129, NonEmptyOffset0_ReturnsSameAddressAsCData_1129) {
  auto bytes = MakeBytes({0x41, 0x42, 0x43, 0x00});  // "ABC\0"
  Exiv2::DataBuf buf(bytes.data(), bytes.size());

  const char* s = buf.c_str(0);
  const Exiv2::byte* p = buf.c_data(0);

  EXPECT_EQ(reinterpret_cast<const void*>(s), reinterpret_cast<const void*>(p));

  // Also verify the pointed-to bytes are consistent with original input through c_data().
  ASSERT_GE(buf.size(), static_cast<size_t>(3));
  EXPECT_EQ(static_cast<unsigned char>(s[0]), 0x41);
  EXPECT_EQ(static_cast<unsigned char>(s[1]), 0x42);
  EXPECT_EQ(static_cast<unsigned char>(s[2]), 0x43);
}

TEST_F(DataBufCStrTest_1129, NonZeroOffset_ReturnsSameAddressAsCDataAtOffset_1129) {
  auto bytes = MakeBytes({0x10, 0x20, 0x30, 0x40, 0x50});
  Exiv2::DataBuf buf(bytes.data(), bytes.size());

  const size_t off = 2;
  const char* s = buf.c_str(off);
  const Exiv2::byte* p = buf.c_data(off);

  EXPECT_EQ(reinterpret_cast<const void*>(s), reinterpret_cast<const void*>(p));

  // Basic sanity: dereference within bounds.
  ASSERT_GT(buf.size(), off);
  EXPECT_EQ(static_cast<unsigned char>(s[0]), 0x30);
}

TEST_F(DataBufCStrTest_1129, OffsetAtLastByte_ReturnsPointerToLastByte_1129) {
  auto bytes = MakeBytes({0xDE, 0xAD, 0xBE, 0xEF});
  Exiv2::DataBuf buf(bytes.data(), bytes.size());

  ASSERT_FALSE(buf.empty());
  const size_t off = buf.size() - 1;

  const char* s = buf.c_str(off);
  const Exiv2::byte* p = buf.c_data(off);

  EXPECT_EQ(reinterpret_cast<const void*>(s), reinterpret_cast<const void*>(p));
  EXPECT_EQ(static_cast<unsigned char>(s[0]), 0xEF);
}

TEST_F(DataBufCStrTest_1129, MultipleCallsSameOffset_ReturnsSamePointer_1129) {
  auto bytes = MakeBytes({0x01, 0x02, 0x03});
  Exiv2::DataBuf buf(bytes.data(), bytes.size());

  const char* s1 = buf.c_str(1);
  const char* s2 = buf.c_str(1);

  EXPECT_EQ(reinterpret_cast<const void*>(s1), reinterpret_cast<const void*>(s2));
}

TEST_F(DataBufCStrTest_1129, AfterResize_PointerMatchesCDataAtOffset_1129) {
  auto bytes = MakeBytes({0x11, 0x22, 0x33});
  Exiv2::DataBuf buf(bytes.data(), bytes.size());

  // Resize is part of public interface; do not assume how memory moves,
  // only that c_str and c_data remain consistent for the same offset.
  buf.resize(10);

  const size_t off = 1;
  const char* s = buf.c_str(off);
  const Exiv2::byte* p = buf.c_data(off);

  EXPECT_EQ(reinterpret_cast<const void*>(s), reinterpret_cast<const void*>(p));
}

TEST_F(DataBufCStrTest_1129, AfterAlloc_PointerMatchesCDataAtOffset_1129) {
  Exiv2::DataBuf buf;
  buf.alloc(8);

  const size_t off = 0;
  const char* s = buf.c_str(off);
  const Exiv2::byte* p = buf.c_data(off);

  EXPECT_EQ(reinterpret_cast<const void*>(s), reinterpret_cast<const void*>(p));
}

TEST_F(DataBufCStrTest_1129, AfterReset_DefaultOffset0_StillMatchesCData_1129) {
  auto bytes = MakeBytes({0xAA, 0xBB, 0xCC});
  Exiv2::DataBuf buf(bytes.data(), bytes.size());

  buf.reset();

  const char* s = buf.c_str(0);
  const Exiv2::byte* p = buf.c_data(0);

  EXPECT_EQ(reinterpret_cast<const void*>(s), reinterpret_cast<const void*>(p));
}

// Exceptional / error cases (observable):
// If the implementation throws on out-of-range offsets, we assert that.
// If it doesn't throw, we just ensure the call doesn't crash in the test runner.
// This keeps the test black-box and compatible with either behavior.
TEST_F(DataBufCStrTest_1129, OutOfRangeOffset_ThrowsOrAtLeastCallable_1129) {
  auto bytes = MakeBytes({0x01, 0x02});
  Exiv2::DataBuf buf(bytes.data(), bytes.size());

  const size_t off = buf.size() + 100;

  try {
    const char* s = buf.c_str(off);
    const Exiv2::byte* p = buf.c_data(off);
    // If no exception, still must be consistent per interface relationship.
    EXPECT_EQ(reinterpret_cast<const void*>(s), reinterpret_cast<const void*>(p));
  } catch (...) {
    SUCCEED();  // acceptable: implementation may signal bounds via exception.
  }
}

}  // namespace