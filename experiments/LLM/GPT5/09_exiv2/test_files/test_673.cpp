// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_iptcdatum_tag_673.cpp
//
// Unit tests for Exiv2::Iptcdatum::tag() based strictly on the public interface
// and observable behavior.
//
// TEST_ID: 673

#include <gtest/gtest.h>

#include <cstdint>

#include <exiv2/iptc.hpp>  // Exiv2::Iptcdatum, Exiv2::IptcKey

namespace {

// The provided partial implementation shows:
//   uint16_t tag() const { return key_ ? key_->tag() : 0; }
// We treat the class as a black box and only validate observable outcomes.

class IptcdatumTagTest_673 : public ::testing::Test {};

}  // namespace

TEST_F(IptcdatumTagTest_673, ReturnsTagFromKey_673) {
  const uint16_t tag = 0x1234;
  const uint16_t record = 0x0002;

  const Exiv2::IptcKey key(tag, record);
  Exiv2::Iptcdatum datum(key, /*pValue=*/nullptr);

  EXPECT_EQ(datum.tag(), tag);
}

TEST_F(IptcdatumTagTest_673, ReturnsZeroWhenConstructedWithZeroTagKey_673) {
  const uint16_t tag = 0;
  const uint16_t record = 0x0001;

  const Exiv2::IptcKey key(tag, record);
  Exiv2::Iptcdatum datum(key, /*pValue=*/nullptr);

  EXPECT_EQ(datum.tag(), 0u);
}

TEST_F(IptcdatumTagTest_673, CopyConstructionPreservesTag_673) {
  const uint16_t tag = 0x00FF;
  const uint16_t record = 0x0007;

  const Exiv2::IptcKey key(tag, record);
  Exiv2::Iptcdatum original(key, /*pValue=*/nullptr);

  Exiv2::Iptcdatum copy(original);

  EXPECT_EQ(copy.tag(), original.tag());
  EXPECT_EQ(copy.tag(), tag);
}

TEST_F(IptcdatumTagTest_673, CopyAssignmentPreservesTag_673) {
  const uint16_t tagA = 0x1111;
  const uint16_t recordA = 0x0001;
  const Exiv2::IptcKey keyA(tagA, recordA);
  Exiv2::Iptcdatum a(keyA, /*pValue=*/nullptr);

  const uint16_t tagB = 0x2222;
  const uint16_t recordB = 0x0002;
  const Exiv2::IptcKey keyB(tagB, recordB);
  Exiv2::Iptcdatum b(keyB, /*pValue=*/nullptr);

  // Sanity before assignment
  EXPECT_EQ(a.tag(), tagA);
  EXPECT_EQ(b.tag(), tagB);

  b = a;

  EXPECT_EQ(b.tag(), a.tag());
  EXPECT_EQ(b.tag(), tagA);
}

TEST_F(IptcdatumTagTest_673, SelfAssignmentKeepsTagStable_673) {
  const uint16_t tag = 0x0A0B;
  const uint16_t record = 0x0003;

  const Exiv2::IptcKey key(tag, record);
  Exiv2::Iptcdatum datum(key, /*pValue=*/nullptr);

  const uint16_t before = datum.tag();
  datum = datum;
  const uint16_t after = datum.tag();

  EXPECT_EQ(after, before);
  EXPECT_EQ(after, tag);
}

TEST_F(IptcdatumTagTest_673, TagUnaffectedByAssigningNumericValue_673) {
  const uint16_t tag = 0x0C0D;
  const uint16_t record = 0x0004;

  const Exiv2::IptcKey key(tag, record);
  Exiv2::Iptcdatum datum(key, /*pValue=*/nullptr);

  datum = static_cast<uint16_t>(42);

  EXPECT_EQ(datum.tag(), tag);
}

TEST_F(IptcdatumTagTest_673, TagUnaffectedByAssigningStringValue_673) {
  const uint16_t tag = 0xABCD;
  const uint16_t record = 0x0005;

  const Exiv2::IptcKey key(tag, record);
  Exiv2::Iptcdatum datum(key, /*pValue=*/nullptr);

  datum = std::string("hello");

  EXPECT_EQ(datum.tag(), tag);
}

TEST_F(IptcdatumTagTest_673, BoundaryTagValuesRoundTrip_673) {
  // Boundary conditions for uint16_t.
  const uint16_t minTag = 0;
  const uint16_t maxTag = 0xFFFF;

  const uint16_t record = 0x0001;

  {
    const Exiv2::IptcKey key(minTag, record);
    Exiv2::Iptcdatum datum(key, /*pValue=*/nullptr);
    EXPECT_EQ(datum.tag(), minTag);
  }

  {
    const Exiv2::IptcKey key(maxTag, record);
    Exiv2::Iptcdatum datum(key, /*pValue=*/nullptr);
    EXPECT_EQ(datum.tag(), maxTag);
  }
}

// Exceptional/error cases:
// From the provided interface, there is no public way to construct an Iptcdatum
// without a valid key_ (constructors require an IptcKey), and tag() is not
// specified to throw. Therefore, we only validate that tag() is callable and
// stable across typical operations.

TEST_F(IptcdatumTagTest_673, TagCallableRepeatedlyWithoutThrowing_673) {
  const uint16_t tag = 0x1357;
  const uint16_t record = 0x0009;

  const Exiv2::IptcKey key(tag, record);
  Exiv2::Iptcdatum datum(key, /*pValue=*/nullptr);

  EXPECT_NO_THROW({
    for (int i = 0; i < 10; ++i) {
      EXPECT_EQ(datum.tag(), tag);
    }
  });
}