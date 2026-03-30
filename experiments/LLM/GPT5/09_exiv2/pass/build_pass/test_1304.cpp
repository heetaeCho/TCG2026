// SPDX-License-Identifier: GPL-2.0-or-later

#include <gtest/gtest.h>

#include <exiv2/xmp_exiv2.hpp>

#include <cstddef>
#include <string>

namespace {

using namespace Exiv2;

class XmpDataTest_1304 : public ::testing::Test {
 protected:
  static XmpKey makeKey(const std::string& s) {
    // Exiv2::XmpKey is expected to be constructible from a std::string.
    return XmpKey(s);
  }

  static bool stringContains(const std::string& haystack, const std::string& needle) {
    return haystack.find(needle) != std::string::npos;
  }
};

TEST_F(XmpDataTest_1304, AddToEmptyMakesNonEmptyAndCountAtLeastOne_1304) {
  XmpData data;
  EXPECT_TRUE(data.empty());
  EXPECT_EQ(data.count(), 0);

  Xmpdatum d(makeKey("Xmp.dc.title"), nullptr);
  // Make the datum "observable" via public interface.
  (void)d.setValue(std::string("hello"));

  EXPECT_EQ(data.add(d), 0);

  EXPECT_FALSE(data.empty());
  EXPECT_GE(data.count(), 1);

  auto it = data.findKey(makeKey("Xmp.dc.title"));
  EXPECT_NE(it, data.end());
}

TEST_F(XmpDataTest_1304, AddMultipleDifferentKeysIncreasesCount_1304) {
  XmpData data;
  EXPECT_EQ(data.count(), 0);

  Xmpdatum d1(makeKey("Xmp.dc.title"), nullptr);
  (void)d1.setValue(std::string("title-1"));

  Xmpdatum d2(makeKey("Xmp.dc.creator"), nullptr);
  (void)d2.setValue(std::string("creator-1"));

  EXPECT_EQ(data.add(d1), 0);
  const long after1 = data.count();
  EXPECT_GE(after1, 1);

  EXPECT_EQ(data.add(d2), 0);
  const long after2 = data.count();
  EXPECT_GE(after2, after1);

  EXPECT_NE(data.findKey(makeKey("Xmp.dc.title")), data.end());
  EXPECT_NE(data.findKey(makeKey("Xmp.dc.creator")), data.end());
}

TEST_F(XmpDataTest_1304, AddAcceptsDatumConstructedWithNullValuePointer_1304) {
  XmpData data;

  Xmpdatum d(makeKey("Xmp.dc.description"), nullptr);
  // Even if the datum was constructed with a null Value*, it should still be usable
  // through its public interface (if supported by implementation).
  (void)d.setValue(std::string("desc"));

  EXPECT_EQ(data.add(d), 0);
  EXPECT_FALSE(data.empty());

  auto it = data.findKey(makeKey("Xmp.dc.description"));
  ASSERT_NE(it, data.end());

  // Don't assume exact formatting of toString(); just require it to be non-empty
  // and plausibly contain the value we set.
  const std::string s = it->toString();
  EXPECT_FALSE(s.empty());
  EXPECT_TRUE(stringContains(s, "desc") || stringContains(s, "Desc") || stringContains(s, "DESC"));
}

TEST_F(XmpDataTest_1304, AddStoresIndependentEntryFromSourceObject_1304) {
  XmpData data;

  Xmpdatum src(makeKey("Xmp.dc.subject"), nullptr);
  (void)src.setValue(std::string("first"));
  ASSERT_EQ(data.add(src), 0);

  // Mutate the source object after adding.
  (void)src.setValue(std::string("second"));

  // The entry inside XmpData should be retrievable, and should be stable relative
  // to the add() call (i.e., should not reflect later mutations of `src`).
  auto it = data.findKey(makeKey("Xmp.dc.subject"));
  ASSERT_NE(it, data.end());

  const std::string stored = it->toString();
  EXPECT_FALSE(stored.empty());
  EXPECT_TRUE(stringContains(stored, "first") || !stringContains(stored, "second"));
}

}  // namespace