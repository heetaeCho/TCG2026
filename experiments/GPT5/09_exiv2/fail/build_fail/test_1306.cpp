// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_xmpdata_clear_1306.cpp
//
// Unit tests for Exiv2::XmpData::clear() (black-box via public interface)

#include <gtest/gtest.h>

#include <exiv2/xmp_exiv2.hpp>

namespace {

class XmpDataClearTest_1306 : public ::testing::Test {
 protected:
  Exiv2::XmpData xmp_;
};

TEST_F(XmpDataClearTest_1306, ClearOnDefaultConstructedKeepsEmpty_1306) {
  EXPECT_TRUE(xmp_.empty());
  EXPECT_EQ(0, xmp_.count());
  EXPECT_EQ(xmp_.begin(), xmp_.end());

  EXPECT_NO_THROW(xmp_.clear());

  EXPECT_TRUE(xmp_.empty());
  EXPECT_EQ(0, xmp_.count());
  EXPECT_EQ(xmp_.begin(), xmp_.end());
}

TEST_F(XmpDataClearTest_1306, ClearRemovesSingleInsertedEntry_1306) {
  EXPECT_TRUE(xmp_.empty());
  EXPECT_EQ(0, xmp_.count());

  // Insert via operator[] + setValue (observable through empty/count/begin/end).
  Exiv2::Xmpdatum& d = xmp_["Xmp.dc.title"];
  d.setValue("hello");

  EXPECT_FALSE(xmp_.empty());
  EXPECT_GT(xmp_.count(), 0);
  EXPECT_NE(xmp_.begin(), xmp_.end());

  xmp_.clear();

  EXPECT_TRUE(xmp_.empty());
  EXPECT_EQ(0, xmp_.count());
  EXPECT_EQ(xmp_.begin(), xmp_.end());
}

TEST_F(XmpDataClearTest_1306, ClearRemovesMultipleInsertedEntries_1306) {
  // Insert multiple entries with distinct keys.
  xmp_["Xmp.dc.title"].setValue("t");
  xmp_["Xmp.dc.creator"].setValue("c");
  xmp_["Xmp.dc.description"].setValue("d");

  EXPECT_FALSE(xmp_.empty());
  EXPECT_GT(xmp_.count(), 0);
  EXPECT_NE(xmp_.begin(), xmp_.end());

  xmp_.clear();

  EXPECT_TRUE(xmp_.empty());
  EXPECT_EQ(0, xmp_.count());
  EXPECT_EQ(xmp_.begin(), xmp_.end());
}

TEST_F(XmpDataClearTest_1306, ClearIsIdempotent_1306) {
  xmp_["Xmp.dc.title"].setValue("hello");
  EXPECT_FALSE(xmp_.empty());
  EXPECT_GT(xmp_.count(), 0);

  xmp_.clear();
  EXPECT_TRUE(xmp_.empty());
  EXPECT_EQ(0, xmp_.count());
  EXPECT_EQ(xmp_.begin(), xmp_.end());

  // Calling clear() again should keep it empty and not throw.
  EXPECT_NO_THROW(xmp_.clear());
  EXPECT_TRUE(xmp_.empty());
  EXPECT_EQ(0, xmp_.count());
  EXPECT_EQ(xmp_.begin(), xmp_.end());
}

TEST_F(XmpDataClearTest_1306, ClearAfterEraseLeavesEmpty_1306) {
  xmp_["Xmp.dc.title"].setValue("t");
  xmp_["Xmp.dc.creator"].setValue("c");

  ASSERT_FALSE(xmp_.empty());
  ASSERT_NE(xmp_.begin(), xmp_.end());

  // Erase one element (observable effect: count should decrease or remain >0 depending on library behavior).
  // We only rely on the fact that erase(pos) is callable and returns an iterator.
  auto it = xmp_.begin();
  EXPECT_NO_THROW((void)xmp_.erase(it));

  // Now clear should still reliably empty the container.
  EXPECT_NO_THROW(xmp_.clear());
  EXPECT_TRUE(xmp_.empty());
  EXPECT_EQ(0, xmp_.count());
  EXPECT_EQ(xmp_.begin(), xmp_.end());
}

TEST_F(XmpDataClearTest_1306, ClearWorksWithManyEntriesBoundary_1306) {
  // Boundary-ish: add a moderate number of entries to ensure clear handles non-trivial size.
  for (int i = 0; i < 100; ++i) {
    xmp_[std::string("Xmp.dc.subject[") + std::to_string(i) + "]"].setValue(std::to_string(i));
  }

  EXPECT_FALSE(xmp_.empty());
  EXPECT_GT(xmp_.count(), 0);

  xmp_.clear();

  EXPECT_TRUE(xmp_.empty());
  EXPECT_EQ(0, xmp_.count());
  EXPECT_EQ(xmp_.begin(), xmp_.end());
}

}  // namespace