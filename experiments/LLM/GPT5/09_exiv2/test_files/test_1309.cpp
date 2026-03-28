// File: test_xmpdata_end_const_1309.cpp
// TEST_ID: 1309

#include <gtest/gtest.h>

#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

#include <exiv2/xmp_exiv2.hpp>

namespace {

// These tests treat XmpData as a black box and only validate observable behavior
// through the public interface (iterators, count/empty, add/clear, etc.).

class XmpDataEndConstTest_1309 : public ::testing::Test {
 protected:
  static Exiv2::Xmpdatum MakeDatum(const std::string& keyStr, const std::string& valueStr) {
    Exiv2::XmpKey key(keyStr);
    Exiv2::Xmpdatum d(key);
    d.setValue(valueStr);
    return d;
  }

  static void AddSome(Exiv2::XmpData& xd, int n) {
    for (int i = 0; i < n; ++i) {
      const std::string k = "Xmp.dc.title[" + std::to_string(i) + "]";
      const std::string v = "v" + std::to_string(i);
      (void)xd.add(MakeDatum(k, v));
    }
  }
};

TEST_F(XmpDataEndConstTest_1309, DefaultConstructed_ConstBeginEqualsConstEnd_1309) {
  Exiv2::XmpData xd;
  const Exiv2::XmpData& cxd = xd;

  EXPECT_TRUE(cxd.empty());
  EXPECT_EQ(cxd.count(), 0);

  // Core observable behavior: for an empty container, begin == end.
  EXPECT_EQ(cxd.begin(), cxd.end());
}

TEST_F(XmpDataEndConstTest_1309, AfterClear_ConstBeginEqualsConstEnd_1309) {
  Exiv2::XmpData xd;
  AddSome(xd, 3);
  ASSERT_GE(xd.count(), 1);

  xd.clear();
  const Exiv2::XmpData& cxd = xd;

  EXPECT_TRUE(cxd.empty());
  EXPECT_EQ(cxd.count(), 0);
  EXPECT_EQ(cxd.begin(), cxd.end());
}

TEST_F(XmpDataEndConstTest_1309, NonEmpty_ConstBeginNotEqualConstEnd_1309) {
  Exiv2::XmpData xd;
  (void)xd.add(MakeDatum("Xmp.dc.title", "hello"));

  const Exiv2::XmpData& cxd = xd;

  EXPECT_FALSE(cxd.empty());
  EXPECT_GE(cxd.count(), 1);

  // Core observable behavior: for a non-empty container, begin != end.
  EXPECT_NE(cxd.begin(), cxd.end());
}

TEST_F(XmpDataEndConstTest_1309, ConstEndSupportsDistanceThatMatchesCount_1309) {
  Exiv2::XmpData xd;
  AddSome(xd, 5);

  const Exiv2::XmpData& cxd = xd;

  ASSERT_FALSE(cxd.empty());
  ASSERT_GE(cxd.count(), 1);

  const auto dist = static_cast<long>(std::distance(cxd.begin(), cxd.end()));
  EXPECT_EQ(dist, cxd.count());
}

TEST_F(XmpDataEndConstTest_1309, ConstEndRemainsAValidSentinelAfterSortByKey_1309) {
  Exiv2::XmpData xd;
  // Insert in an order that likely differs from sorted-by-key order.
  (void)xd.add(MakeDatum("Xmp.dc.title[2]", "v2"));
  (void)xd.add(MakeDatum("Xmp.dc.title[0]", "v0"));
  (void)xd.add(MakeDatum("Xmp.dc.title[1]", "v1"));

  const long beforeCount = xd.count();
  ASSERT_GE(beforeCount, 1);

  xd.sortByKey();

  const Exiv2::XmpData& cxd = xd;
  EXPECT_EQ(cxd.count(), beforeCount);

  // Observable: end() works as a sentinel for iteration after sorting too.
  const auto dist = static_cast<long>(std::distance(cxd.begin(), cxd.end()));
  EXPECT_EQ(dist, cxd.count());
}

TEST_F(XmpDataEndConstTest_1309, EraseThenIterateToConstEnd_DistanceMatchesCount_1309) {
  Exiv2::XmpData xd;
  AddSome(xd, 4);
  ASSERT_GE(xd.count(), 2);

  // Erase using only public iterator API.
  Exiv2::XmpData::iterator it = xd.begin();
  it = xd.erase(it);

  const Exiv2::XmpData& cxd = xd;
  ASSERT_GE(cxd.count(), 1);

  const auto dist = static_cast<long>(std::distance(cxd.begin(), cxd.end()));
  EXPECT_EQ(dist, cxd.count());

  // Also ensure we can advance from begin to end without stepping past end.
  auto cit = cxd.begin();
  for (long i = 0; i < cxd.count(); ++i) {
    ASSERT_NE(cit, cxd.end());
    ++cit;
  }
  EXPECT_EQ(cit, cxd.end());
}

}  // namespace