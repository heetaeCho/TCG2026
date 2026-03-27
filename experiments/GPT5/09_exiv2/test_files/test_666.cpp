// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_iptcdatum_recordname_666.cpp

#include <gtest/gtest.h>

#include <exiv2/datasets.hpp>  // Exiv2::IptcKey
#include <exiv2/iptc.hpp>      // Exiv2::Iptcdatum

namespace {

class IptcdatumTest_666 : public ::testing::Test {};

TEST_F(IptcdatumTest_666, RecordNameMatchesKey_FromNumericCtor_666) {
  const Exiv2::IptcKey key(/*tag=*/0x0005, /*record=*/0x0002);
  const Exiv2::Iptcdatum datum(key, /*pValue=*/nullptr);

  // Black-box check: Iptcdatum::recordName() should reflect the underlying key.
  EXPECT_EQ(datum.recordName(), key.recordName());
}

TEST_F(IptcdatumTest_666, RecordNameMatchesKey_FromStringCtor_666) {
  // Use a plausible IPTC key string (exact mapping is intentionally not assumed).
  const Exiv2::IptcKey key(std::string("Iptc.Application2.ObjectName"));
  const Exiv2::Iptcdatum datum(key, /*pValue=*/nullptr);

  EXPECT_EQ(datum.recordName(), key.recordName());
}

TEST_F(IptcdatumTest_666, RecordNamePreservedByCopyConstructor_666) {
  const Exiv2::IptcKey key(std::string("Iptc.Application2.Caption"));
  const Exiv2::Iptcdatum original(key, /*pValue=*/nullptr);

  const Exiv2::Iptcdatum copy(original);

  EXPECT_EQ(copy.recordName(), original.recordName());
  EXPECT_EQ(copy.recordName(), key.recordName());
}

TEST_F(IptcdatumTest_666, RecordNamePreservedByCopyAssignment_666) {
  const Exiv2::IptcKey keyA(std::string("Iptc.Application2.Keywords"));
  const Exiv2::Iptcdatum a(keyA, /*pValue=*/nullptr);

  const Exiv2::IptcKey keyB(std::string("Iptc.Application2.City"));
  Exiv2::Iptcdatum b(keyB, /*pValue=*/nullptr);

  b = a;

  EXPECT_EQ(b.recordName(), a.recordName());
  EXPECT_EQ(b.recordName(), keyA.recordName());
}

TEST_F(IptcdatumTest_666, RecordNameCallableOnConstObject_666) {
  const Exiv2::IptcKey key(std::string("Iptc.Application2.CountryName"));
  const Exiv2::Iptcdatum datum(key, /*pValue=*/nullptr);

  const Exiv2::Iptcdatum& cdatum = datum;
  EXPECT_EQ(cdatum.recordName(), key.recordName());
}

}  // namespace