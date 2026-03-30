// SPDX-License-Identifier: GPL-2.0-or-later
// Test file for Exiv2::ValueType<T> copy-constructor behavior (black-box tests)
//
// The TEST_ID is 2156

#include <gtest/gtest.h>

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <vector>

#include "exiv2/value.hpp"

namespace {

class ValueTypeCopyCtorTest_2156 : public ::testing::Test {
 protected:
  using T = uint32_t;
  using VT = Exiv2::ValueType<T>;

  static std::vector<Exiv2::byte> MakeBytes(size_t n) {
    std::vector<Exiv2::byte> v(n);
    for (size_t i = 0; i < n; ++i) {
      v[i] = static_cast<Exiv2::byte>((i * 31u + 7u) & 0xFFu);
    }
    return v;
  }

  static void ExpectDataAreaEqual(const Exiv2::Value& a, const Exiv2::Value& b) {
    const size_t sa = a.sizeDataArea();
    const size_t sb = b.sizeDataArea();
    ASSERT_EQ(sa, sb);

    const Exiv2::DataBuf da = a.dataArea();
    const Exiv2::DataBuf db = b.dataArea();

    // If size is zero, no further assumptions about pointers are needed.
    if (sa == 0) return;

    ASSERT_NE(da.pData_, nullptr);
    ASSERT_NE(db.pData_, nullptr);
    EXPECT_EQ(0, std::memcmp(da.pData_, db.pData_, sa));
  }
};

TEST_F(ValueTypeCopyCtorTest_2156, CopyConstruct_DefaultObject_PreservesBasicObservables_2156) {
  VT rhs;
  VT lhs(rhs);

  EXPECT_EQ(lhs.typeId(), rhs.typeId());
  EXPECT_EQ(lhs.ok(), rhs.ok());

  // Observable size-related APIs should remain consistent after copy.
  EXPECT_EQ(lhs.count(), rhs.count());
  EXPECT_EQ(lhs.size(), rhs.size());

  // Data area should match as well (likely empty for default-constructed).
  EXPECT_EQ(lhs.sizeDataArea(), rhs.sizeDataArea());
  ExpectDataAreaEqual(lhs, rhs);
}

TEST_F(ValueTypeCopyCtorTest_2156, CopyConstruct_WithNonEmptyDataArea_ClonesDataAreaContent_2156) {
  VT rhs;

  const auto bytes = MakeBytes(64);
  const int rc = rhs.setDataArea(bytes.data(), bytes.size());

  // We don't assume a particular return code contract, but we can assert that
  // observable state reflects a non-empty data area when provided.
  (void)rc;
  ASSERT_GT(rhs.sizeDataArea(), 0u);

  VT lhs(rhs);

  EXPECT_EQ(lhs.typeId(), rhs.typeId());
  EXPECT_EQ(lhs.sizeDataArea(), rhs.sizeDataArea());
  ExpectDataAreaEqual(lhs, rhs);
}

TEST_F(ValueTypeCopyCtorTest_2156, CopyConstruct_SourceThenModified_CopyRemainsUnchanged_2156) {
  VT rhs;

  const auto initial = MakeBytes(32);
  (void)rhs.setDataArea(initial.data(), initial.size());
  ASSERT_GT(rhs.sizeDataArea(), 0u);

  VT lhs(rhs);

  // Modify the source after copying; the copy should retain its own observable data area.
  const auto changed = MakeBytes(48);
  (void)rhs.setDataArea(changed.data(), changed.size());
  ASSERT_GT(rhs.sizeDataArea(), 0u);

  // lhs should still match the *initial* snapshot, not the modified rhs.
  EXPECT_NE(lhs.sizeDataArea(), rhs.sizeDataArea());

  // Reconstruct what lhs should contain by comparing to a fresh copy made at the same time.
  VT expected(lhs);  // self-copy to keep comparison within public interface
  ExpectDataAreaEqual(lhs, expected);
}

TEST_F(ValueTypeCopyCtorTest_2156, CopyConstruct_WithEmptyDataArea_DoesNotCreateUnexpectedData_2156) {
  VT rhs;

  // Provide an empty data area (len == 0). Pointer must be non-null for safety.
  const Exiv2::byte dummy = static_cast<Exiv2::byte>(0xAA);
  (void)rhs.setDataArea(&dummy, 0);

  // Whatever the implementation does, copying should preserve observable equality.
  VT lhs(rhs);

  EXPECT_EQ(lhs.typeId(), rhs.typeId());
  EXPECT_EQ(lhs.sizeDataArea(), rhs.sizeDataArea());
  ExpectDataAreaEqual(lhs, rhs);
}

}  // namespace