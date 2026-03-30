// ============================================================================
// TEST_ID: 694
// Unit tests for Exiv2::IptcData::add(const IptcKey&, const Value*)
// File: ./TestProjects/exiv2/src/iptc.cpp
// ============================================================================

#include <gtest/gtest.h>

#include <exiv2/datasets.hpp>
#include <exiv2/iptc.hpp>
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>

#include <cstdint>
#include <memory>
#include <string>

namespace {

class IptcDataTest_694 : public ::testing::Test {
 protected:
  static Exiv2::Value::UniquePtr MakeAsciiValue(const std::string& s) {
    // Use a common, stable Exiv2 Value type. Treat implementation as black-box.
    auto v = Exiv2::Value::create(Exiv2::asciiString);
    if (v) {
      (void)v->read(s);
    }
    return v;
  }

  static Exiv2::IptcKey KeyFromString(const std::string& key) { return Exiv2::IptcKey(key); }

  static Exiv2::IptcKey KeyFromId(uint16_t tag, uint16_t record) { return Exiv2::IptcKey(tag, record); }
};

TEST_F(IptcDataTest_694, AddWithKeyAndValue_IfSuccessThenFindable_694) {
  Exiv2::IptcData data;

  const Exiv2::IptcKey key = KeyFromString("Iptc.Application2.ObjectName");
  auto value = MakeAsciiValue("hello");

  const size_t before = data.size();
  const int rc = data.add(key, value.get());
  const size_t after = data.size();

  // Observable invariant: size() should not decrease after an add attempt.
  EXPECT_GE(after, before);

  const auto it = data.findKey(key);

  // Only assert what is observable and consistent: if add reports success (rc == 0),
  // the element should be findable. If it reports failure, it should not have appeared.
  if (rc == 0) {
    EXPECT_NE(it, data.end());
    EXPECT_FALSE(data.empty());
  } else {
    EXPECT_EQ(it, data.end());
  }
}

TEST_F(IptcDataTest_694, AddDelegatesToIptcdatumOverload_ResultMatches_694) {
  // Compare behavior across two fresh objects (avoid double-inserting into one object).
  Exiv2::IptcData viaKeyValue;
  Exiv2::IptcData viaDatum;

  const Exiv2::IptcKey key = KeyFromString("Iptc.Application2.Caption");
  auto value1 = MakeAsciiValue("caption-1");
  auto value2 = MakeAsciiValue("caption-1");

  // Build an Iptcdatum only from public interface types.
  Exiv2::Iptcdatum datum(key, value2.get());

  const int rc1 = viaKeyValue.add(key, value1.get());
  const int rc2 = viaDatum.add(datum);

  EXPECT_EQ(rc1, rc2);
  EXPECT_EQ(viaKeyValue.size(), viaDatum.size());

  const bool found1 = (viaKeyValue.findKey(key) != viaKeyValue.end());
  const bool found2 = (viaDatum.findKey(key) != viaDatum.end());
  EXPECT_EQ(found1, found2);
}

TEST_F(IptcDataTest_694, AddTwoDifferentKeys_SizeNonDecreasingAndFindableOnSuccess_694) {
  Exiv2::IptcData data;

  const Exiv2::IptcKey key1 = KeyFromString("Iptc.Application2.ObjectName");
  const Exiv2::IptcKey key2 = KeyFromString("Iptc.Application2.Byline");

  auto v1 = MakeAsciiValue("name");
  auto v2 = MakeAsciiValue("author");

  const size_t s0 = data.size();
  const int rc1 = data.add(key1, v1.get());
  const size_t s1 = data.size();
  EXPECT_GE(s1, s0);

  const int rc2 = data.add(key2, v2.get());
  const size_t s2 = data.size();
  EXPECT_GE(s2, s1);

  if (rc1 == 0) {
    EXPECT_NE(data.findKey(key1), data.end());
  }
  if (rc2 == 0) {
    EXPECT_NE(data.findKey(key2), data.end());
  }
}

TEST_F(IptcDataTest_694, AddSameKeyTwice_SizeNeverDecreases_694) {
  Exiv2::IptcData data;

  const Exiv2::IptcKey key = KeyFromString("Iptc.Application2.ObjectName");
  auto v1 = MakeAsciiValue("v1");
  auto v2 = MakeAsciiValue("v2");

  const size_t s0 = data.size();
  const int rc1 = data.add(key, v1.get());
  const size_t s1 = data.size();
  EXPECT_GE(s1, s0);

  const int rc2 = data.add(key, v2.get());
  const size_t s2 = data.size();
  EXPECT_GE(s2, s1);

  // If either call reports success, the key should be findable.
  if (rc1 == 0 || rc2 == 0) {
    EXPECT_NE(data.findKey(key), data.end());
  }
}

TEST_F(IptcDataTest_694, AddNullValue_ThrowsOrReturnsError_694) {
  Exiv2::IptcData data;
  const Exiv2::IptcKey key = KeyFromString("Iptc.Application2.ObjectName");

  try {
    const int rc = data.add(key, nullptr);
    // If no exception, require an observable "error" signal via return code.
    EXPECT_NE(rc, 0);
    // And it should not have inserted anything successfully.
    EXPECT_EQ(data.findKey(key), data.end());
  } catch (...) {
    SUCCEED();
  }
}

TEST_F(IptcDataTest_694, AddWithEmptyKeyString_ThrowsOrDoesNotInsertOnFailure_694) {
  Exiv2::IptcData data;
  const Exiv2::IptcKey key = KeyFromString("");
  auto v = MakeAsciiValue("x");

  try {
    const int rc = data.add(key, v.get());
    if (rc == 0) {
      EXPECT_NE(data.findKey(key), data.end());
    } else {
      EXPECT_EQ(data.findKey(key), data.end());
    }
  } catch (...) {
    SUCCEED();
  }
}

TEST_F(IptcDataTest_694, AddWithBoundaryTagAndRecord_MaxUint16_694) {
  Exiv2::IptcData data;

  const Exiv2::IptcKey key = KeyFromId(static_cast<uint16_t>(0xFFFF), static_cast<uint16_t>(0xFFFF));
  auto v = MakeAsciiValue("boundary");

  const size_t before = data.size();

  try {
    const int rc = data.add(key, v.get());
    const size_t after = data.size();
    EXPECT_GE(after, before);

    if (rc == 0) {
      EXPECT_NE(data.findKey(key), data.end());
    } else {
      EXPECT_EQ(data.findKey(key), data.end());
    }
  } catch (...) {
    // Exception is an observable error case; accept it for boundary inputs.
    SUCCEED();
  }
}

}  // namespace