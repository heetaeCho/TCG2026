// File: test_iptc_record_667.cpp
// TEST_ID: 667

#include <gtest/gtest.h>

#include <cstdint>
#include <memory>
#include <string>

// Exiv2 headers (from the codebase)
#include <exiv2/datasets.hpp>
#include <exiv2/iptc.hpp>
#include <exiv2/value.hpp>

namespace {

class IptcdatumTest_667 : public ::testing::Test {
 protected:
  static std::unique_ptr<Exiv2::Value> MakeStringValue(const std::string& s) {
    // Use Exiv2's public factory to avoid depending on any specific concrete Value type.
    auto v = Exiv2::Value::create(Exiv2::string);
    if (v) {
      (void)v->read(s);
    }
    return v;
  }
};

TEST_F(IptcdatumTest_667, RecordReturnsRecordFromKey_TagRecordCtor_667) {
  const uint16_t tag = 0x1234;
  const uint16_t record = 0x0002;

  Exiv2::IptcKey key(tag, record);
  auto v = MakeStringValue("hello");

  Exiv2::Iptcdatum datum(key, v.get());

  EXPECT_EQ(datum.record(), record);
}

TEST_F(IptcdatumTest_667, RecordReturnsZeroWhenKeyRecordIsZero_667) {
  const uint16_t tag = 0x0001;
  const uint16_t record = 0x0000;

  Exiv2::IptcKey key(tag, record);
  auto v = MakeStringValue("x");

  Exiv2::Iptcdatum datum(key, v.get());

  EXPECT_EQ(datum.record(), 0u);
}

TEST_F(IptcdatumTest_667, RecordSupportsMaxUInt16Boundary_667) {
  const uint16_t tag = 0xFFFF;
  const uint16_t record = 0xFFFF;

  Exiv2::IptcKey key(tag, record);
  auto v = MakeStringValue("boundary");

  Exiv2::Iptcdatum datum(key, v.get());

  EXPECT_EQ(datum.record(), record);
}

TEST_F(IptcdatumTest_667, RecordIsPreservedByCopyConstruction_667) {
  const uint16_t tag = 0x0042;
  const uint16_t record = 0x0007;

  Exiv2::IptcKey key(tag, record);
  auto v = MakeStringValue("copy");

  Exiv2::Iptcdatum original(key, v.get());
  Exiv2::Iptcdatum copy(original);

  EXPECT_EQ(original.record(), record);
  EXPECT_EQ(copy.record(), record);
}

TEST_F(IptcdatumTest_667, RecordIsPreservedByCopyAssignment_667) {
  const uint16_t tagA = 0x0010;
  const uint16_t recordA = 0x0005;

  const uint16_t tagB = 0x0020;
  const uint16_t recordB = 0x0009;

  Exiv2::IptcKey keyA(tagA, recordA);
  Exiv2::IptcKey keyB(tagB, recordB);

  auto vA = MakeStringValue("a");
  auto vB = MakeStringValue("b");

  Exiv2::Iptcdatum a(keyA, vA.get());
  Exiv2::Iptcdatum b(keyB, vB.get());

  ASSERT_EQ(a.record(), recordA);
  ASSERT_EQ(b.record(), recordB);

  b = a;

  EXPECT_EQ(b.record(), recordA);
  EXPECT_EQ(a.record(), recordA);
}

TEST_F(IptcdatumTest_667, RecordSelfAssignmentDoesNotChangeObservableRecord_667) {
  const uint16_t tag = 0x0100;
  const uint16_t record = 0x0001;

  Exiv2::IptcKey key(tag, record);
  auto v = MakeStringValue("self");

  Exiv2::Iptcdatum datum(key, v.get());
  ASSERT_EQ(datum.record(), record);

  datum = datum;

  EXPECT_EQ(datum.record(), record);
}

TEST_F(IptcdatumTest_667, RecordWorksWithStringKeyCtor_CommonIptcKey_667) {
  // Use a commonly used IPTC key string; the test only verifies that record()
  // returns *some* stable value that matches the key-derived record for that key.
  // (No assumptions about what that value is.)
  const std::string keyStr = "Iptc.Application2.ObjectName";

  Exiv2::IptcKey key(keyStr);
  auto v = MakeStringValue("obj");

  Exiv2::Iptcdatum datum(key, v.get());

  // Observable behavior: Iptcdatum::record() should match IptcKey::record().
  EXPECT_EQ(datum.record(), key.record());
}

}  // namespace