// SPDX-License-Identifier: GPL-2.0-or-later
// File: exifdatum_typesize_test_755.cpp
//
// Unit tests for Exiv2::Exifdatum::typeSize()
// Focus: observable contract from interface: typeSize() == TypeInfo::typeSize(typeId()).

#include <gtest/gtest.h>

#include <cstdint>
#include <string>

#include <exiv2/exif.hpp>
#include <exiv2/types.hpp>

namespace {

using Exiv2::Exifdatum;
using Exiv2::ExifKey;
using Exiv2::TypeInfo;

class ExifdatumTypeSizeTest_755 : public ::testing::Test {
 protected:
  static Exifdatum MakeDatumNoValue() {
    // Key choice is arbitrary; tests only rely on public API behavior.
    // Passing nullptr is allowed by the constructor signature (const Value* pValue).
    return Exifdatum(ExifKey("Exif.Image.Make"), nullptr);
  }
};

TEST_F(ExifdatumTypeSizeTest_755, TypeSizeMatchesTypeInfoForDefaultConstructedValue_755) {
  Exifdatum d = MakeDatumNoValue();

  EXPECT_NO_THROW({
    const auto tid = d.typeId();
    const auto ts = d.typeSize();
    EXPECT_EQ(ts, TypeInfo::typeSize(tid));
  });
}

TEST_F(ExifdatumTypeSizeTest_755, TypeSizeMatchesTypeInfoAfterAssigningUint16_755) {
  Exifdatum d = MakeDatumNoValue();

  d = static_cast<uint16_t>(1);

  const auto tid = d.typeId();
  const auto ts = d.typeSize();
  EXPECT_EQ(ts, TypeInfo::typeSize(tid));
}

TEST_F(ExifdatumTypeSizeTest_755, TypeSizeMatchesTypeInfoAfterAssigningUint32_755) {
  Exifdatum d = MakeDatumNoValue();

  d = static_cast<uint32_t>(0xDEADBEEF);

  const auto tid = d.typeId();
  const auto ts = d.typeSize();
  EXPECT_EQ(ts, TypeInfo::typeSize(tid));
}

TEST_F(ExifdatumTypeSizeTest_755, TypeSizeMatchesTypeInfoAfterAssigningString_755) {
  Exifdatum d = MakeDatumNoValue();

  d = std::string("hello");

  const auto tid = d.typeId();
  const auto ts = d.typeSize();
  EXPECT_EQ(ts, TypeInfo::typeSize(tid));
}

TEST_F(ExifdatumTypeSizeTest_755, TypeSizeStableAcrossMultipleCalls_755) {
  Exifdatum d = MakeDatumNoValue();
  d = static_cast<uint16_t>(42);

  const auto tid1 = d.typeId();
  const auto ts1 = d.typeSize();

  const auto tid2 = d.typeId();
  const auto ts2 = d.typeSize();

  EXPECT_EQ(tid1, tid2);
  EXPECT_EQ(ts1, ts2);
  EXPECT_EQ(ts1, TypeInfo::typeSize(tid1));
}

TEST_F(ExifdatumTypeSizeTest_755, TypeSizeUpdatesWhenTypeIdChangesAfterReassignment_755) {
  Exifdatum d = MakeDatumNoValue();

  d = static_cast<uint16_t>(7);
  const auto tid_before = d.typeId();
  const auto ts_before = d.typeSize();
  EXPECT_EQ(ts_before, TypeInfo::typeSize(tid_before));

  d = std::string("changed-type");
  const auto tid_after = d.typeId();
  const auto ts_after = d.typeSize();
  EXPECT_EQ(ts_after, TypeInfo::typeSize(tid_after));

  // Observable boundary-ish check: if typeId differs, typeSize may differ too.
  // We don't require inequality (implementation-defined), but ensure consistency holds.
  (void)tid_before;
  (void)tid_after;
}

}  // namespace