// File: test_IptcKey_familyName_641.cpp
#include <gtest/gtest.h>

#include <cstdint>
#include <cstring>
#include <string>

#include "exiv2/datasets.hpp"

namespace {

class IptcKeyFamilyNameTest_641 : public ::testing::Test {};

TEST_F(IptcKeyFamilyNameTest_641, ReturnsIptcForStringCtor_641) {
  Exiv2::IptcKey key(std::string("Iptc.Application2.ObjectName"));

  const char* fam = key.familyName();
  ASSERT_NE(fam, nullptr);
  EXPECT_STREQ(fam, "Iptc");
}

TEST_F(IptcKeyFamilyNameTest_641, ReturnsIptcForEmptyStringCtor_641) {
  Exiv2::IptcKey key(std::string(""));

  const char* fam = key.familyName();
  ASSERT_NE(fam, nullptr);
  EXPECT_STREQ(fam, "Iptc");
}

TEST_F(IptcKeyFamilyNameTest_641, ReturnsIptcForTagRecordCtor_641) {
  Exiv2::IptcKey key(static_cast<uint16_t>(0), static_cast<uint16_t>(0));

  const char* fam = key.familyName();
  ASSERT_NE(fam, nullptr);
  EXPECT_STREQ(fam, "Iptc");
}

TEST_F(IptcKeyFamilyNameTest_641, ReturnsIptcForMaxTagRecordCtor_641) {
  Exiv2::IptcKey key(static_cast<uint16_t>(0xFFFF), static_cast<uint16_t>(0xFFFF));

  const char* fam = key.familyName();
  ASSERT_NE(fam, nullptr);
  EXPECT_STREQ(fam, "Iptc");
}

TEST_F(IptcKeyFamilyNameTest_641, FamilyNameStableAcrossCalls_641) {
  Exiv2::IptcKey key(std::string("Iptc.Application2.Caption"));

  const char* fam1 = key.familyName();
  const char* fam2 = key.familyName();

  ASSERT_NE(fam1, nullptr);
  ASSERT_NE(fam2, nullptr);
  EXPECT_STREQ(fam1, "Iptc");
  EXPECT_STREQ(fam2, "Iptc");
}

TEST_F(IptcKeyFamilyNameTest_641, FamilyNameConsistentAcrossInstances_641) {
  Exiv2::IptcKey keyA(std::string("Iptc.Application2.Keywords"));
  Exiv2::IptcKey keyB(static_cast<uint16_t>(25), static_cast<uint16_t>(2));

  const char* famA = keyA.familyName();
  const char* famB = keyB.familyName();

  ASSERT_NE(famA, nullptr);
  ASSERT_NE(famB, nullptr);
  EXPECT_STREQ(famA, "Iptc");
  EXPECT_STREQ(famB, "Iptc");
}

}  // namespace