// TEST_ID 696
// Unit tests for Exiv2::IptcData::findKey(const IptcKey&) const
//
// File under test (partial): ./TestProjects/exiv2/src/iptc.cpp

#include <gtest/gtest.h>

#include <algorithm>
#include <iterator>
#include <memory>
#include <string>

#include "exiv2/datasets.hpp"
#include "exiv2/iptc.hpp"
#include "exiv2/value.hpp"
#include "exiv2/types.hpp"

namespace {

class IptcDataTest_696 : public ::testing::Test {
 protected:
  static Exiv2::Value::UniquePtr makeAsciiValue(const std::string& s) {
    // Use only the public Value factory + public parsing API.
    Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::asciiString);
    if (v) {
      v->read(s);
    }
    return v;
  }

  static Exiv2::IptcData::const_iterator cendFromNonConst(Exiv2::IptcData& d) {
    // Many Exiv2 iterators follow STL conventions where iterator -> const_iterator is convertible.
    return d.end();
  }
};

TEST_F(IptcDataTest_696, FindKeyOnEmptyReturnsEnd_696) {
  Exiv2::IptcData data;
  const Exiv2::IptcData& cdata = data;

  const Exiv2::IptcKey key(/*tag=*/5, /*record=*/1);

  auto it = cdata.findKey(key);
  EXPECT_TRUE(it == cendFromNonConst(data));
}

TEST_F(IptcDataTest_696, FindKeyAfterAddFindsExisting_696) {
  Exiv2::IptcData data;
  const Exiv2::IptcData& cdata = data;

  const Exiv2::IptcKey key(/*tag=*/120, /*record=*/2);
  auto v = makeAsciiValue("hello");

  ASSERT_NE(v.get(), nullptr);
  EXPECT_EQ(0, data.add(key, v.get()));

  auto it_const = cdata.findKey(key);
  EXPECT_TRUE(it_const != cendFromNonConst(data));

  // Cross-check that const/non-const findKey agree on the position.
  auto it_nc = data.findKey(key);
  EXPECT_TRUE(it_nc != data.end());
  EXPECT_TRUE(it_const == it_nc);
}

TEST_F(IptcDataTest_696, FindKeyForMissingKeyReturnsEnd_696) {
  Exiv2::IptcData data;
  const Exiv2::IptcData& cdata = data;

  const Exiv2::IptcKey present(/*tag=*/25, /*record=*/2);
  auto v = makeAsciiValue("x");
  ASSERT_NE(v.get(), nullptr);
  ASSERT_EQ(0, data.add(present, v.get()));

  const Exiv2::IptcKey missingDifferentTag(/*tag=*/26, /*record=*/2);
  auto it = cdata.findKey(missingDifferentTag);
  EXPECT_TRUE(it == cendFromNonConst(data));

  const Exiv2::IptcKey missingDifferentRecord(/*tag=*/25, /*record=*/3);
  it = cdata.findKey(missingDifferentRecord);
  EXPECT_TRUE(it == cendFromNonConst(data));
}

TEST_F(IptcDataTest_696, FindKeyDistinguishesBetweenDifferentRecords_696) {
  Exiv2::IptcData data;
  const Exiv2::IptcData& cdata = data;

  const uint16_t tag = 55;
  const Exiv2::IptcKey keyA(/*tag=*/tag, /*record=*/1);
  const Exiv2::IptcKey keyB(/*tag=*/tag, /*record=*/2);

  auto v1 = makeAsciiValue("a");
  auto v2 = makeAsciiValue("b");
  ASSERT_NE(v1.get(), nullptr);
  ASSERT_NE(v2.get(), nullptr);

  ASSERT_EQ(0, data.add(keyA, v1.get()));
  ASSERT_EQ(0, data.add(keyB, v2.get()));

  auto itA = cdata.findKey(keyA);
  auto itB = cdata.findKey(keyB);

  EXPECT_TRUE(itA != cendFromNonConst(data));
  EXPECT_TRUE(itB != cendFromNonConst(data));

  // The iterators for different keys should not be equal.
  EXPECT_FALSE(itA == itB);
}

TEST_F(IptcDataTest_696, FindKeyAfterEraseNoLongerFindsErasedEntry_696) {
  Exiv2::IptcData data;
  const Exiv2::IptcData& cdata = data;

  const Exiv2::IptcKey key(/*tag=*/80, /*record=*/1);
  auto v = makeAsciiValue("to-erase");
  ASSERT_NE(v.get(), nullptr);
  ASSERT_EQ(0, data.add(key, v.get()));

  auto it = data.findKey(key);
  ASSERT_TRUE(it != data.end());

  (void)data.erase(it);

  auto it_const = cdata.findKey(key);
  EXPECT_TRUE(it_const == cendFromNonConst(data));
}

TEST_F(IptcDataTest_696, FindKeyAfterClearReturnsEnd_696) {
  Exiv2::IptcData data;
  const Exiv2::IptcData& cdata = data;

  const Exiv2::IptcKey key(/*tag=*/1, /*record=*/1);
  auto v = makeAsciiValue("x");
  ASSERT_NE(v.get(), nullptr);
  ASSERT_EQ(0, data.add(key, v.get()));
  ASSERT_FALSE(data.empty());

  data.clear();
  ASSERT_TRUE(data.empty());

  auto it = cdata.findKey(key);
  EXPECT_TRUE(it == cendFromNonConst(data));
}

TEST_F(IptcDataTest_696, FindKeyWorksAfterSortByKeyAndSortByTag_696) {
  Exiv2::IptcData data;
  const Exiv2::IptcData& cdata = data;

  const Exiv2::IptcKey key1(/*tag=*/90, /*record=*/2);
  const Exiv2::IptcKey key2(/*tag=*/10, /*record=*/2);

  auto v1 = makeAsciiValue("v1");
  auto v2 = makeAsciiValue("v2");
  ASSERT_NE(v1.get(), nullptr);
  ASSERT_NE(v2.get(), nullptr);

  ASSERT_EQ(0, data.add(key1, v1.get()));
  ASSERT_EQ(0, data.add(key2, v2.get()));

  data.sortByKey();
  EXPECT_TRUE(cdata.findKey(key1) != cendFromNonConst(data));
  EXPECT_TRUE(cdata.findKey(key2) != cendFromNonConst(data));

  data.sortByTag();
  EXPECT_TRUE(cdata.findKey(key1) != cendFromNonConst(data));
  EXPECT_TRUE(cdata.findKey(key2) != cendFromNonConst(data));
}

}  // namespace