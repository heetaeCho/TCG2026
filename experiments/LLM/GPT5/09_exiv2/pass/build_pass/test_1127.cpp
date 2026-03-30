// TEST_ID 1127
// File: test_databuf_data_1127.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <exception>
#include <type_traits>

#include "exiv2/types.hpp"

namespace {

using Exiv2::byte;
using Exiv2::DataBuf;

// Helper: For potentially-out-of-range offsets, Exiv2 may throw or may return nullptr.
// We treat both as acceptable "observable error handling" without assuming internals.
template <typename F>
static void ExpectThrowOrNullptr(F&& f) {
  try {
    auto* p = f();
    EXPECT_EQ(p, nullptr);
  } catch (...) {
    SUCCEED();
  }
}

}  // namespace

TEST(DataBufTest_1127, DataMatchesCDataPointerAtSameOffset_1127) {
  DataBuf buf(static_cast<size_t>(8));

  const byte* cp = nullptr;
  ASSERT_NO_THROW(cp = buf.c_data(0));
  ASSERT_NE(cp, nullptr);

  byte* p = nullptr;
  ASSERT_NO_THROW(p = buf.data(0));
  ASSERT_NE(p, nullptr);

  EXPECT_EQ(p, const_cast<byte*>(cp));
}

TEST(DataBufTest_1127, DataReturnsWritablePointerAndWriteIsObservableViaReadUint8_1127) {
  DataBuf buf(static_cast<size_t>(4));

  ASSERT_NO_THROW(buf.write_uint8(0, static_cast<uint8_t>(0x12)));
  EXPECT_EQ(buf.read_uint8(0), static_cast<uint8_t>(0x12));

  byte* p = nullptr;
  ASSERT_NO_THROW(p = buf.data(0));
  ASSERT_NE(p, nullptr);

  *p = static_cast<byte>(0x34);
  EXPECT_EQ(buf.read_uint8(0), static_cast<uint8_t>(0x34));
}

TEST(DataBufTest_1127, DataAtNonZeroOffsetWritesAreObservable_1127) {
  DataBuf buf(static_cast<size_t>(6));

  ASSERT_NO_THROW(buf.write_uint8(2, static_cast<uint8_t>(0xAB)));
  EXPECT_EQ(buf.read_uint8(2), static_cast<uint8_t>(0xAB));

  byte* p = nullptr;
  ASSERT_NO_THROW(p = buf.data(2));
  ASSERT_NE(p, nullptr);

  *p = static_cast<byte>(0xCD);
  EXPECT_EQ(buf.read_uint8(2), static_cast<uint8_t>(0xCD));
}

TEST(DataBufTest_1127, DataAtLastByteOffsetIsWritableAndObservable_1127) {
  DataBuf buf(static_cast<size_t>(3));
  const size_t last = buf.size() - 1;

  ASSERT_NO_THROW(buf.write_uint8(last, static_cast<uint8_t>(0x01)));
  EXPECT_EQ(buf.read_uint8(last), static_cast<uint8_t>(0x01));

  byte* p = nullptr;
  ASSERT_NO_THROW(p = buf.data(last));
  ASSERT_NE(p, nullptr);

  *p = static_cast<byte>(0xFE);
  EXPECT_EQ(buf.read_uint8(last), static_cast<uint8_t>(0xFE));
}

TEST(DataBufTest_1127, DataOnEmptyBufferAtOffsetZeroIsHandled_1127) {
  DataBuf buf;
  EXPECT_TRUE(buf.empty());
  EXPECT_EQ(buf.size(), static_cast<size_t>(0));

  ExpectThrowOrNullptr([&]() { return buf.data(0); });
  ExpectThrowOrNullptr([&]() { return buf.c_data(0); });
}

TEST(DataBufTest_1127, DataWithOffsetEqualToSizeIsHandled_1127) {
  DataBuf buf(static_cast<size_t>(2));
  ASSERT_EQ(buf.size(), static_cast<size_t>(2));

  // Offset == size is out-of-range for dereference; implementation may throw or return nullptr.
  const size_t off = buf.size();
  ExpectThrowOrNullptr([&]() { return buf.data(off); });
  ExpectThrowOrNullptr([&]() { return buf.c_data(off); });
}

TEST(DataBufTest_1127, DataWithOffsetGreaterThanSizeIsHandled_1127) {
  DataBuf buf(static_cast<size_t>(2));
  ASSERT_EQ(buf.size(), static_cast<size_t>(2));

  const size_t off = buf.size() + 10;
  ExpectThrowOrNullptr([&]() { return buf.data(off); });
  ExpectThrowOrNullptr([&]() { return buf.c_data(off); });
}