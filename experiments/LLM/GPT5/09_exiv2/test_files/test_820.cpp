// -----------------------------------------------------------------------------
// TEST_ID: 820
// Unit tests for Exiv2::CommentValue::read(const byte* buf, size_t len, ByteOrder)
// File under test: ./TestProjects/exiv2/src/value.cpp (partial)
// -----------------------------------------------------------------------------

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "exiv2/value.hpp"

namespace {

using Exiv2::CommentValue;
using Exiv2::ByteOrder;
using Exiv2::byte;

// Helper: best-effort selection of two distinct ByteOrder values.
// We avoid relying on specific enumerator names beyond common Exiv2 ones.
// If your build uses different names, adjust these two lines.
static constexpr ByteOrder kOrderA = Exiv2::littleEndian;
static constexpr ByteOrder kOrderB = Exiv2::bigEndian;

static std::vector<byte> MakeBuf(std::initializer_list<uint8_t> bytes) {
  std::vector<byte> v;
  v.reserve(bytes.size());
  for (auto b : bytes) v.push_back(static_cast<byte>(b));
  return v;
}

class CommentValueTest_820 : public ::testing::Test {};

TEST_F(CommentValueTest_820, ReadWithSameInputReturnsSameResultAcrossByteOrders_820) {
  // Observable behavior from the provided implementation:
  // - CommentValue::read stores byteOrder_ then returns StringValueBase::read(...)
  // - StringValueBase::read(const byte*, size_t, ByteOrder) ignores byteOrder
  // Therefore, the return value should be invariant to ByteOrder for identical input.
  const auto buf = MakeBuf({0x41, 0x42, 0x43, 0x00, 0xFF, 0x10, 0x20, 0x30});

  CommentValue v1;
  CommentValue v2;

  const int r1 = v1.read(buf.data(), buf.size(), kOrderA);
  const int r2 = v2.read(buf.data(), buf.size(), kOrderB);

  EXPECT_EQ(r1, r2);
}

TEST_F(CommentValueTest_820, ReadWithZeroLengthNonNullBufferReturnsSameResultAcrossByteOrders_820) {
  const auto buf = MakeBuf({0xAB});  // Non-null pointer, but len==0.

  CommentValue v1;
  CommentValue v2;

  const int r1 = v1.read(buf.data(), 0u, kOrderA);
  const int r2 = v2.read(buf.data(), 0u, kOrderB);

  EXPECT_EQ(r1, r2);
}

TEST_F(CommentValueTest_820, ReadWithNullBufferAndZeroLengthDoesNotThrow_820) {
  // Boundary/robustness case: nullptr with len==0 is a common API edge.
  // We only assert "no throw" and that the result is stable across byte orders
  // (per observable behavior described in the partial implementation + signature).
  CommentValue v1;
  CommentValue v2;

  int r1 = 0;
  int r2 = 0;

  EXPECT_NO_THROW({ r1 = v1.read(nullptr, 0u, kOrderA); });
  EXPECT_NO_THROW({ r2 = v2.read(nullptr, 0u, kOrderB); });

  EXPECT_EQ(r1, r2);
}

TEST_F(CommentValueTest_820, ReadBoundaryLengthsReturnValueInvariantAcrossByteOrders_820) {
  // Boundary sizes around common comment encodings (without assuming any parsing rules).
  const auto buf = MakeBuf({
      0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
      0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
  });

  for (size_t len : {1u, 7u, 8u, 9u, buf.size()}) {
    CommentValue v1;
    CommentValue v2;

    const int r1 = v1.read(buf.data(), len, kOrderA);
    const int r2 = v2.read(buf.data(), len, kOrderB);

    EXPECT_EQ(r1, r2) << "len=" << len;
  }
}

TEST_F(CommentValueTest_820, ReadDoesNotPreventSubsequentCopyOnSameInstance_820) {
  // Observable contract: methods are callable; we don't assert formatting.
  // This test checks a normal workflow: read(...) then copy(...).
  const auto buf = MakeBuf({0x11, 0x22, 0x33, 0x44, 0x00});

  CommentValue v;
  (void)v.read(buf.data(), buf.size(), kOrderA);

  std::vector<byte> out(64, static_cast<byte>(0));
  size_t copied = 0;

  EXPECT_NO_THROW({ copied = v.copy(out.data(), kOrderB); });
  // Only verify minimal observable constraints.
  EXPECT_LE(copied, out.size());
}

}  // namespace