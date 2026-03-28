// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_xmpdata_erasefamily_1313.cpp

#include <gtest/gtest.h>

#include <exiv2/xmp_exiv2.hpp>

namespace {

using Exiv2::XmpData;
using Exiv2::XmpKey;

class XmpDataEraseFamilyTest_1313 : public ::testing::Test {
 protected:
  static void AddText(XmpData& data, const std::string& key, const std::string& value) {
    // Use only the public interface (operator[] + setValue(string)).
    Exiv2::Xmpdatum& d = data[key];
    (void)d.setValue(value);
  }

  static XmpData MakeSampleData() {
    XmpData d;

    // Family base key and keys that are expected to be adjacent after sortByKey().
    AddText(d, "Xmp.dc.title", "base");
    AddText(d, "Xmp.dc.titleAlt", "alt");
    AddText(d, "Xmp.dc.titleAlt.lang", "lang");

    // Neighbor keys from other "families" (not starting with "Xmp.dc.title").
    AddText(d, "Xmp.dc.creator", "creator");
    AddText(d, "Xmp.xmp.CreateDate", "date");

    d.sortByKey();
    return d;
  }
};

TEST_F(XmpDataEraseFamilyTest_1313, EraseFamily_RemovesPrefixedKeysAndMovesPosToNext_1313) {
  XmpData d = MakeSampleData();

  const long before = d.count();
  ASSERT_GT(before, 0);

  XmpData::iterator pos = d.findKey(XmpKey("Xmp.dc.title"));
  ASSERT_NE(pos, d.end());
  ASSERT_EQ(pos->key(), "Xmp.dc.title");

  d.eraseFamily(pos);

  // Removed: base + two prefixed keys
  EXPECT_EQ(d.findKey(XmpKey("Xmp.dc.title")), d.end());
  EXPECT_EQ(d.findKey(XmpKey("Xmp.dc.titleAlt")), d.end());
  EXPECT_EQ(d.findKey(XmpKey("Xmp.dc.titleAlt.lang")), d.end());

  // Not removed: unrelated keys
  EXPECT_NE(d.findKey(XmpKey("Xmp.dc.creator")), d.end());
  EXPECT_NE(d.findKey(XmpKey("Xmp.xmp.CreateDate")), d.end());

  EXPECT_EQ(d.count(), before - 3);

  // Iterator is passed by reference; expected to now point at the first key
  // after the erased family (or end()).
  ASSERT_NE(pos, d.end());
  EXPECT_NE(pos->key(), "Xmp.dc.title");
  EXPECT_NE(pos->key(), "Xmp.dc.titleAlt");
  EXPECT_NE(pos->key(), "Xmp.dc.titleAlt.lang");
}

TEST_F(XmpDataEraseFamilyTest_1313, EraseFamily_FamilyAtEnd_SetsPosToEnd_1313) {
  XmpData d;

  XmpDataEraseFamilyTest_1313::AddText(d, "Xmp.dc.creator", "creator");
  XmpDataEraseFamilyTest_1313::AddText(d, "Xmp.xmp.CreateDate", "date");

  // Put family keys that will sort after the above keys.
  XmpDataEraseFamilyTest_1313::AddText(d, "Xmp.z.family", "base");
  XmpDataEraseFamilyTest_1313::AddText(d, "Xmp.z.family.child", "child");

  d.sortByKey();

  const long before = d.count();
  ASSERT_EQ(before, 4);

  XmpData::iterator pos = d.findKey(XmpKey("Xmp.z.family"));
  ASSERT_NE(pos, d.end());
  ASSERT_EQ(pos->key(), "Xmp.z.family");

  d.eraseFamily(pos);

  EXPECT_EQ(d.findKey(XmpKey("Xmp.z.family")), d.end());
  EXPECT_EQ(d.findKey(XmpKey("Xmp.z.family.child")), d.end());

  EXPECT_NE(d.findKey(XmpKey("Xmp.dc.creator")), d.end());
  EXPECT_NE(d.findKey(XmpKey("Xmp.xmp.CreateDate")), d.end());

  EXPECT_EQ(d.count(), before - 2);

  // Since the erased family was at the end, pos should now be end().
  EXPECT_EQ(pos, d.end());
}

TEST_F(XmpDataEraseFamilyTest_1313, EraseFamily_SingleKeyFamily_RemovesOnlyThatKey_1313) {
  XmpData d;

  XmpDataEraseFamilyTest_1313::AddText(d, "Xmp.dc.creator", "creator");
  XmpDataEraseFamilyTest_1313::AddText(d, "Xmp.dc.title", "base");
  // Intentionally do NOT add any keys starting with "Xmp.dc.title".
  XmpDataEraseFamilyTest_1313::AddText(d, "Xmp.xmp.CreateDate", "date");

  d.sortByKey();

  const long before = d.count();
  ASSERT_EQ(before, 3);

  XmpData::iterator pos = d.findKey(XmpKey("Xmp.dc.title"));
  ASSERT_NE(pos, d.end());
  ASSERT_EQ(pos->key(), "Xmp.dc.title");

  d.eraseFamily(pos);

  EXPECT_EQ(d.findKey(XmpKey("Xmp.dc.title")), d.end());
  EXPECT_NE(d.findKey(XmpKey("Xmp.dc.creator")), d.end());
  EXPECT_NE(d.findKey(XmpKey("Xmp.xmp.CreateDate")), d.end());

  EXPECT_EQ(d.count(), before - 1);

  // pos should now be the first element after the erased key (or end()).
  if (pos != d.end()) {
    EXPECT_NE(pos->key(), "Xmp.dc.title");
  }
}

TEST_F(XmpDataEraseFamilyTest_1313, EraseFamily_DoesNotRemoveNonPrefixSimilarKeys_1313) {
  XmpData d;

  // Base family
  XmpDataEraseFamilyTest_1313::AddText(d, "Xmp.dc.title", "base");
  XmpDataEraseFamilyTest_1313::AddText(d, "Xmp.dc.titleAlt", "alt");

  // Similar-looking but NOT a prefix match (case differs)
  XmpDataEraseFamilyTest_1313::AddText(d, "Xmp.dc.TitleAlt", "case-different");

  // Unrelated
  XmpDataEraseFamilyTest_1313::AddText(d, "Xmp.dc.creator", "creator");

  d.sortByKey();

  const long before = d.count();
  ASSERT_EQ(before, 4);

  XmpData::iterator pos = d.findKey(XmpKey("Xmp.dc.title"));
  ASSERT_NE(pos, d.end());

  d.eraseFamily(pos);

  // Prefix family removed
  EXPECT_EQ(d.findKey(XmpKey("Xmp.dc.title")), d.end());
  EXPECT_EQ(d.findKey(XmpKey("Xmp.dc.titleAlt")), d.end());

  // Case-different key should remain (not a starts_with match on the exact base key string).
  EXPECT_NE(d.findKey(XmpKey("Xmp.dc.TitleAlt")), d.end());

  // Unrelated remains
  EXPECT_NE(d.findKey(XmpKey("Xmp.dc.creator")), d.end());

  EXPECT_EQ(d.count(), before - 2);
}

}  // namespace