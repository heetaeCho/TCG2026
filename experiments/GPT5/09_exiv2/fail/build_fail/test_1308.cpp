// ***************************************************************** -*- C++ -*-
/*
  Unit tests for Exiv2::XmpData::begin() const

  Constraints:
  - Treat implementation as a black box
  - Use only public interface / observable behavior
*/
// ***********************************************************************

#include <gtest/gtest.h>

#include <exiv2/xmp_exiv2.hpp>

#include <iterator>   // std::next, std::distance

namespace {

class XmpDataTest_1308 : public ::testing::Test {
 protected:
  Exiv2::XmpData xmp_;
};

TEST_F(XmpDataTest_1308, BeginConstOnDefaultConstructedIsEnd_1308) {
  const Exiv2::XmpData& cxmp = xmp_;

  // Observable behavior for an empty container-like type:
  // begin() == end() and count() == 0.
  EXPECT_TRUE(cxmp.empty());
  EXPECT_EQ(0L, cxmp.count());

  EXPECT_EQ(cxmp.begin(), cxmp.end());
}

TEST_F(XmpDataTest_1308, BeginConstAfterClearIsEnd_1308) {
  // Create at least one entry via the public API.
  (void)xmp_["Xmp.dc.title"];

  ASSERT_FALSE(xmp_.empty());
  ASSERT_GE(xmp_.count(), 1L);

  xmp_.clear();

  const Exiv2::XmpData& cxmp = xmp_;
  EXPECT_TRUE(cxmp.empty());
  EXPECT_EQ(0L, cxmp.count());
  EXPECT_EQ(cxmp.begin(), cxmp.end());
}

TEST_F(XmpDataTest_1308, BeginConstAfterInsertionIsNotEnd_1308) {
  // Using operator[] is a public way to ensure a key exists.
  (void)xmp_["Xmp.dc.title"];

  const Exiv2::XmpData& cxmp = xmp_;
  ASSERT_FALSE(cxmp.empty());
  ASSERT_EQ(1L, cxmp.count());

  const auto it = cxmp.begin();
  EXPECT_NE(it, cxmp.end());

  // With exactly one element, incrementing once should reach end().
  EXPECT_EQ(std::next(it), cxmp.end());
}

TEST_F(XmpDataTest_1308, BeginConstDistanceMatchesCountForMultipleEntries_1308) {
  (void)xmp_["Xmp.dc.title"];
  (void)xmp_["Xmp.dc.creator"];
  (void)xmp_["Xmp.dc.description"];

  const Exiv2::XmpData& cxmp = xmp_;
  ASSERT_FALSE(cxmp.empty());
  ASSERT_EQ(3L, cxmp.count());

  const auto dist = std::distance(cxmp.begin(), cxmp.end());
  EXPECT_EQ(cxmp.count(), dist);
}

TEST_F(XmpDataTest_1308, BeginConstDoesNotChangeCount_1308) {
  (void)xmp_["Xmp.dc.title"];
  (void)xmp_["Xmp.dc.creator"];

  const Exiv2::XmpData& cxmp = xmp_;
  const long before = cxmp.count();

  // Calling begin() const should be observationally non-mutating.
  (void)cxmp.begin();
  (void)cxmp.begin();  // repeated access

  const long after = cxmp.count();
  EXPECT_EQ(before, after);
}

TEST_F(XmpDataTest_1308, BeginConstAfterErasingOnlyElementIsEnd_1308) {
  (void)xmp_["Xmp.dc.title"];

  ASSERT_EQ(1L, xmp_.count());

  // Erase via iterator API.
  auto it = xmp_.begin();
  xmp_.erase(it);

  const Exiv2::XmpData& cxmp = xmp_;
  EXPECT_TRUE(cxmp.empty());
  EXPECT_EQ(0L, cxmp.count());
  EXPECT_EQ(cxmp.begin(), cxmp.end());
}

}  // namespace