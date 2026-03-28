// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_value_datavalue_count_792.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "exiv2/value.hpp"

namespace {

class DataValueTest_792 : public ::testing::Test {
 protected:
  static Exiv2::TypeId AnyTypeId() { return static_cast<Exiv2::TypeId>(0); }
  static Exiv2::ByteOrder AnyByteOrder() { return static_cast<Exiv2::ByteOrder>(0); }
};

TEST_F(DataValueTest_792, DefaultConstructed_CountEqualsSize_792) {
  Exiv2::DataValue dv(AnyTypeId());
  EXPECT_EQ(dv.count(), dv.size());
}

TEST_F(DataValueTest_792, ReadEmptyString_MaintainsCountEqualsSize_792) {
  Exiv2::DataValue dv(AnyTypeId());

  EXPECT_NO_THROW({
    (void)dv.read(std::string{});
  });

  EXPECT_EQ(dv.count(), dv.size());
}

TEST_F(DataValueTest_792, ReadNonEmptyString_MaintainsCountEqualsSize_792) {
  Exiv2::DataValue dv(AnyTypeId());

  EXPECT_NO_THROW({
    (void)dv.read(std::string{"abc"});
  });

  EXPECT_EQ(dv.count(), dv.size());
}

TEST_F(DataValueTest_792, ReadEmptyBuffer_MaintainsCountEqualsSize_792) {
  Exiv2::DataValue dv(AnyTypeId());

  const Exiv2::byte* buf = nullptr;
  const size_t len = 0;

  EXPECT_NO_THROW({
    (void)dv.read(buf, len, AnyByteOrder());
  });

  EXPECT_EQ(dv.count(), dv.size());
}

TEST_F(DataValueTest_792, ReadNonEmptyBuffer_MaintainsCountEqualsSize_792) {
  Exiv2::DataValue dv(AnyTypeId());

  const std::vector<Exiv2::byte> buf = {0x01, 0x02, 0x03, 0x04};

  EXPECT_NO_THROW({
    (void)dv.read(buf.data(), buf.size(), AnyByteOrder());
  });

  EXPECT_EQ(dv.count(), dv.size());
}

TEST_F(DataValueTest_792, Clone_PreservesObservableCountAndSize_792) {
  Exiv2::DataValue dv(AnyTypeId());
  (void)dv.read(std::string{"clone-me"});

  auto cloned = dv.clone();
  ASSERT_TRUE(cloned.get() != nullptr);

  EXPECT_EQ(cloned->size(), dv.size());
  EXPECT_EQ(cloned->count(), dv.count());
  EXPECT_EQ(cloned->count(), cloned->size());
}

TEST_F(DataValueTest_792, Copy_DoesNotBreakCountSizeInvariant_792) {
  Exiv2::DataValue dv(AnyTypeId());
  (void)dv.read(std::string{"copy-test"});

  // Allocate a buffer that is safely large enough regardless of internal details.
  std::vector<Exiv2::byte> out(dv.size() + 64U, static_cast<Exiv2::byte>(0));

  size_t copied = 0;
  EXPECT_NO_THROW({
    copied = dv.copy(out.data(), AnyByteOrder());
  });

  EXPECT_LE(copied, out.size());
  EXPECT_EQ(dv.count(), dv.size());
}

}  // namespace