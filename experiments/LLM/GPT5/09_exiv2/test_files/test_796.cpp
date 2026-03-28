// =================================================================================================
// UNIT TESTS for Exiv2::DataValue (value.cpp / value.hpp)
// TEST_ID: 796
//
// Constraints respected:
// - Treat implementation as black box (no private/internal state access)
// - Tests use only public interface and observable behavior
// - No internal logic re-implementation
// =================================================================================================

#include <gtest/gtest.h>

#include <cstring>
#include <string>
#include <vector>

#include "exiv2/types.hpp"
#include "exiv2/value.hpp"

namespace {

class DataValueTest_796 : public ::testing::Test {
 protected:
  static Exiv2::TypeId kTypeId() {
    // Pick a commonly available TypeId in Exiv2.
    // If your build uses different names, adjust here.
    return Exiv2::unsignedByte;
  }

  static Exiv2::ByteOrder kByteOrder() {
    // ByteOrder is required by interface; DataValue may or may not use it.
    return Exiv2::littleEndian;
  }
};

TEST_F(DataValueTest_796, SizeInitiallyZero_796) {
  Exiv2::DataValue dv(kTypeId());

  // Observable: size() returns a size_t.
  // For a freshly constructed value container, size is expected to be 0.
  EXPECT_EQ(0u, dv.size());
}

TEST_F(DataValueTest_796, ReadFromEmptyBufferKeepsSizeZero_796) {
  Exiv2::DataValue dv(kTypeId());

  const Exiv2::byte* nullBuf = nullptr;
  EXPECT_NO_THROW({
    // len=0 should be a boundary condition; must not crash.
    (void)dv.read(nullBuf, 0u, kByteOrder());
  });

  EXPECT_EQ(0u, dv.size());
}

TEST_F(DataValueTest_796, ReadFromBufferSetsSizeAndCopyRoundTripsBytes_796) {
  Exiv2::DataValue dv(kTypeId());

  const std::vector<Exiv2::byte> input = {0x00, 0x7F, 0x80, 0xFF};
  const int rc = dv.read(input.data(), input.size(), kByteOrder());

  // Observable: read returns an int; success is typically 0 in Exiv2.
  // We only assert it's non-negative to avoid over-specifying error conventions.
  EXPECT_GE(rc, 0);

  // Observable behavior expectation: size reflects the stored payload size.
  EXPECT_EQ(input.size(), dv.size());

  std::vector<Exiv2::byte> out(dv.size());
  const size_t copied = dv.copy(out.data(), kByteOrder());

  EXPECT_EQ(out.size(), copied);
  EXPECT_EQ(input, out);
}

TEST_F(DataValueTest_796, ReadFromStringSetsSizeAndCopyMatchesBytes_796) {
  Exiv2::DataValue dv(kTypeId());

  const std::string s = std::string("abc\0def", 7);  // include embedded NUL as boundary-ish content
  const int rc = dv.read(s);

  EXPECT_GE(rc, 0);
  EXPECT_EQ(s.size(), dv.size());

  std::vector<Exiv2::byte> out(dv.size());
  const size_t copied = dv.copy(out.data(), kByteOrder());
  EXPECT_EQ(out.size(), copied);

  // Compare byte-wise against the string payload.
  ASSERT_EQ(s.size(), out.size());
  EXPECT_EQ(0, std::memcmp(s.data(), out.data(), s.size()));
}

TEST_F(DataValueTest_796, LargeBufferReadMaintainsSizeAndCopy_796) {
  Exiv2::DataValue dv(kTypeId());

  std::vector<Exiv2::byte> input(1024);
  for (size_t i = 0; i < input.size(); ++i) {
    input[i] = static_cast<Exiv2::byte>(i & 0xFF);
  }

  const int rc = dv.read(input.data(), input.size(), kByteOrder());
  EXPECT_GE(rc, 0);
  EXPECT_EQ(input.size(), dv.size());

  std::vector<Exiv2::byte> out(dv.size());
  const size_t copied = dv.copy(out.data(), kByteOrder());
  EXPECT_EQ(out.size(), copied);
  EXPECT_EQ(input, out);
}

TEST_F(DataValueTest_796, CloneProducesIndependentObjectWithSameSizeAndContent_796) {
  Exiv2::DataValue dv(kTypeId());

  const std::vector<Exiv2::byte> input = {0x10, 0x20, 0x30};
  ASSERT_GE(dv.read(input.data(), input.size(), kByteOrder()), 0);
  ASSERT_EQ(input.size(), dv.size());

  // Observable: clone() returns a UniquePtr; should be non-null.
  auto cloned = dv.clone();
  ASSERT_NE(nullptr, cloned.get());

  // Observable: cloned object should report same size via virtual interface.
  EXPECT_EQ(dv.size(), cloned->size());

  std::vector<Exiv2::byte> out(cloned->size());
  const size_t copied = cloned->copy(out.data(), kByteOrder());
  EXPECT_EQ(out.size(), copied);
  EXPECT_EQ(input, out);

  // Boundary/independence check via observable behavior:
  // Mutate original, ensure clone remains unchanged.
  const std::vector<Exiv2::byte> input2 = {0xAA, 0xBB};
  ASSERT_GE(dv.read(input2.data(), input2.size(), kByteOrder()), 0);

  std::vector<Exiv2::byte> out2(cloned->size());
  const size_t copied2 = cloned->copy(out2.data(), kByteOrder());
  EXPECT_EQ(out2.size(), copied2);
  EXPECT_EQ(input, out2);
}

}  // namespace