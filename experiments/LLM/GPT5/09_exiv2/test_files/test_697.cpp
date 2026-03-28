// SPDX-License-Identifier: GPL-2.0-or-later
// Tests for Exiv2::IptcData::findId(uint16_t dataset, uint16_t record) const
//
// File under test: ./TestProjects/exiv2/src/iptc.cpp (partial)
// Interface (from exiv2/iptc.hpp): Exiv2::IptcData
//
// Constraints respected:
// - Black-box tests using only public API
// - No private/internal state access
// - No re-implementation of logic
// - Cover normal, boundary, and observable error cases

#include <gtest/gtest.h>

#include <exiv2/iptc.hpp>
#include <exiv2/value.hpp>

#include <cstdint>
#include <memory>
#include <string>

namespace {

class IptcDataTest_697 : public ::testing::Test {
 protected:
  static std::unique_ptr<Exiv2::Value> MakeAsciiValue(const std::string& s) {
    // Use Value factory (public API) and populate via read().
    std::unique_ptr<Exiv2::Value> v(Exiv2::Value::create(Exiv2::asciiString));
    EXPECT_NE(v, nullptr);
    v->read(s);
    return v;
  }

  static void AddAscii(Exiv2::IptcData& data, const std::string& keyStr, const std::string& valueStr) {
    const Exiv2::IptcKey key(keyStr);
    auto v = MakeAsciiValue(valueStr);
    ASSERT_NE(v, nullptr);
    // add() copies/clones from the provided Value* (observable via find APIs).
    EXPECT_EQ(0, data.add(key, v.get()));
  }
};

TEST_F(IptcDataTest_697, EmptyDataReturnsEnd_697) {
  const Exiv2::IptcData data;
  // Any id lookup on empty container should not find an entry.
  auto it = data.findId(/*dataset=*/5, /*record=*/2);
  EXPECT_EQ(it, data.end());
}

TEST_F(IptcDataTest_697, FindsExistingIdMatchesFindKey_697) {
  Exiv2::IptcData data;
  AddAscii(data, "Iptc.Application2.ObjectName", "obj-name");

  const Exiv2::IptcKey key("Iptc.Application2.ObjectName");
  const Exiv2::IptcData& cdata = data;

  // Sanity: key lookup works.
  auto itKey = cdata.findKey(key);
  ASSERT_NE(itKey, cdata.end());

  // Known IPTC IIM: Application Record = 2, Dataset for ObjectName = 5.
  auto itId = cdata.findId(/*dataset=*/5, /*record=*/2);
  EXPECT_NE(itId, cdata.end());
  EXPECT_EQ(itId, itKey);
}

TEST_F(IptcDataTest_697, MissingIdReturnsEndWhenOtherEntriesExist_697) {
  Exiv2::IptcData data;
  AddAscii(data, "Iptc.Application2.ObjectName", "obj-name");
  AddAscii(data, "Iptc.Application2.Caption", "caption");

  const Exiv2::IptcData& cdata = data;

  // Use an id that is unlikely to exist in the added set.
  auto it = cdata.findId(/*dataset=*/999, /*record=*/2);
  EXPECT_EQ(it, cdata.end());
}

TEST_F(IptcDataTest_697, BoundaryIdsDoNotCrashAndReturnEndIfAbsent_697) {
  Exiv2::IptcData data;
  AddAscii(data, "Iptc.Application2.ObjectName", "obj-name");

  const Exiv2::IptcData& cdata = data;

  // Boundary values for uint16_t parameters.
  EXPECT_EQ(cdata.findId(/*dataset=*/0, /*record=*/0), cdata.end());
  EXPECT_EQ(cdata.findId(/*dataset=*/0xFFFF, /*record=*/0), cdata.end());
  EXPECT_EQ(cdata.findId(/*dataset=*/0, /*record=*/0xFFFF), cdata.end());
  EXPECT_EQ(cdata.findId(/*dataset=*/0xFFFF, /*record=*/0xFFFF), cdata.end());
}

TEST_F(IptcDataTest_697, FindIdStillFindsAfterSortOperations_697) {
  Exiv2::IptcData data;
  AddAscii(data, "Iptc.Application2.Caption", "caption");
  AddAscii(data, "Iptc.Application2.ObjectName", "obj-name");

  // Sorting is public API; regardless of order, findId should still locate the matching entry.
  data.sortByKey();
  const Exiv2::IptcData& cdata1 = data;
  EXPECT_NE(cdata1.findId(/*dataset=*/5, /*record=*/2), cdata1.end());

  data.sortByTag();
  const Exiv2::IptcData& cdata2 = data;
  EXPECT_NE(cdata2.findId(/*dataset=*/5, /*record=*/2), cdata2.end());
}

}  // namespace