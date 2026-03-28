// ***************************************************************** -*- C++ -*-
// Unit tests for Exiv2::XmpData::findKey(const XmpKey&) const
// *****************************************************************

#include <gtest/gtest.h>

#include <exiv2/properties.hpp>
#include <exiv2/xmp_exiv2.hpp>

#include <string>

namespace {

class XmpDataFindKeyConstTest_1305 : public ::testing::Test {
 protected:
  static constexpr const char* kKey1 = "Xmp.dc.title";
  static constexpr const char* kKey2 = "Xmp.dc.creator";
  static constexpr const char* kKey3 = "Xmp.dc.description";
};

TEST_F(XmpDataFindKeyConstTest_1305, EmptyDataReturnsEnd_1305) {
  Exiv2::XmpData xmp;
  const Exiv2::XmpData& cxmp = xmp;

  const Exiv2::XmpKey key(kKey1);
  auto it = cxmp.findKey(key);

  EXPECT_EQ(it, cxmp.end());
}

TEST_F(XmpDataFindKeyConstTest_1305, FindsExistingKeyInsertedWithOperatorIndex_1305) {
  Exiv2::XmpData xmp;
  (void)xmp[std::string(kKey1)];  // Create/ensure datum exists via public interface.
  const Exiv2::XmpData& cxmp = xmp;

  const Exiv2::XmpKey key(kKey1);
  auto it = cxmp.findKey(key);

  ASSERT_NE(it, cxmp.end());
  EXPECT_EQ(it->key(), std::string(kKey1));
}

TEST_F(XmpDataFindKeyConstTest_1305, MissingKeyReturnsEndEvenWhenOtherKeysExist_1305) {
  Exiv2::XmpData xmp;
  (void)xmp[std::string(kKey1)];
  (void)xmp[std::string(kKey2)];
  const Exiv2::XmpData& cxmp = xmp;

  const Exiv2::XmpKey missing("Xmp.dc.subject");
  auto it = cxmp.findKey(missing);

  EXPECT_EQ(it, cxmp.end());
}

TEST_F(XmpDataFindKeyConstTest_1305, FindsCorrectKeyAmongMultipleEntries_1305) {
  Exiv2::XmpData xmp;
  (void)xmp[std::string(kKey1)];
  (void)xmp[std::string(kKey2)];
  (void)xmp[std::string(kKey3)];
  const Exiv2::XmpData& cxmp = xmp;

  const Exiv2::XmpKey key(kKey2);
  auto it = cxmp.findKey(key);

  ASSERT_NE(it, cxmp.end());
  EXPECT_EQ(it->key(), std::string(kKey2));
}

TEST_F(XmpDataFindKeyConstTest_1305, AfterEraseIteratorKeyIsNotFound_1305) {
  Exiv2::XmpData xmp;
  (void)xmp[std::string(kKey1)];
  (void)xmp[std::string(kKey2)];

  // Erase the element found via the non-const findKey overload (public interface).
  Exiv2::XmpData::iterator it_nonconst = xmp.findKey(Exiv2::XmpKey(kKey1));
  ASSERT_NE(it_nonconst, xmp.end());
  xmp.erase(it_nonconst);

  const Exiv2::XmpData& cxmp = xmp;
  auto it = cxmp.findKey(Exiv2::XmpKey(kKey1));

  EXPECT_EQ(it, cxmp.end());
}

TEST_F(XmpDataFindKeyConstTest_1305, AfterClearPreviouslyPresentKeyIsNotFound_1305) {
  Exiv2::XmpData xmp;
  (void)xmp[std::string(kKey1)];
  ASSERT_FALSE(xmp.empty());

  xmp.clear();
  const Exiv2::XmpData& cxmp = xmp;

  auto it = cxmp.findKey(Exiv2::XmpKey(kKey1));
  EXPECT_EQ(it, cxmp.end());
  EXPECT_TRUE(cxmp.empty());
}

TEST_F(XmpDataFindKeyConstTest_1305, SortByKeyDoesNotBreakFindKeyForExistingKey_1305) {
  Exiv2::XmpData xmp;
  (void)xmp[std::string(kKey3)];
  (void)xmp[std::string(kKey1)];
  (void)xmp[std::string(kKey2)];

  xmp.sortByKey();
  const Exiv2::XmpData& cxmp = xmp;

  auto it = cxmp.findKey(Exiv2::XmpKey(kKey1));
  ASSERT_NE(it, cxmp.end());
  EXPECT_EQ(it->key(), std::string(kKey1));
}

}  // namespace