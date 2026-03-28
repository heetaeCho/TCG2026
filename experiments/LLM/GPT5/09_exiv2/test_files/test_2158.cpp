// SPDX-License-Identifier: GPL-2.0-or-later

#include <gtest/gtest.h>

#include <exiv2/datasets.hpp>
#include <exiv2/metadatum.hpp>

#include <cstdint>
#include <limits>
#include <sstream>
#include <string>

namespace {

class IptcKeyTest_2158 : public ::testing::Test {};

TEST_F(IptcKeyTest_2158, ConstructFromTagRecord_2158) {
  const uint16_t tag = 5;
  const uint16_t record = 2;

  ASSERT_NO_THROW({
    Exiv2::IptcKey key(tag, record);

    EXPECT_EQ(key.tag(), tag);
    EXPECT_EQ(key.record(), record);

    // Basic sanity: these should be callable and return stable types.
    EXPECT_NO_THROW((void)key.key());
    EXPECT_NO_THROW((void)key.familyName());
    EXPECT_NO_THROW((void)key.groupName());
    EXPECT_NO_THROW((void)key.tagName());
    EXPECT_NO_THROW((void)key.tagLabel());
    EXPECT_NO_THROW((void)key.tagDesc());
    EXPECT_NO_THROW((void)key.recordName());

    // The family name is a C-string; ensure it is non-null.
    EXPECT_NE(key.familyName(), nullptr);
  });
}

TEST_F(IptcKeyTest_2158, BoundaryValuesMaxU16_2158) {
  const uint16_t tag = std::numeric_limits<uint16_t>::max();
  const uint16_t record = std::numeric_limits<uint16_t>::max();

  Exiv2::IptcKey key(tag, record);
  EXPECT_EQ(key.tag(), tag);
  EXPECT_EQ(key.record(), record);

  // Ensure these don't throw for boundary values.
  EXPECT_NO_THROW((void)key.key());
  EXPECT_NO_THROW((void)key.recordName());
}

TEST_F(IptcKeyTest_2158, CopyConstructPreservesObservableState_2158) {
  Exiv2::IptcKey original(static_cast<uint16_t>(25), static_cast<uint16_t>(2));
  const std::string originalKeyStr = original.key();

  Exiv2::IptcKey copy(original);

  EXPECT_EQ(copy.tag(), original.tag());
  EXPECT_EQ(copy.record(), original.record());
  EXPECT_EQ(copy.key(), originalKeyStr);

  EXPECT_STREQ(copy.familyName(), original.familyName());
  EXPECT_EQ(copy.groupName(), original.groupName());
  EXPECT_EQ(copy.tagName(), original.tagName());
  EXPECT_EQ(copy.tagLabel(), original.tagLabel());
  EXPECT_EQ(copy.tagDesc(), original.tagDesc());
  EXPECT_EQ(copy.recordName(), original.recordName());
}

TEST_F(IptcKeyTest_2158, CopyAssignPreservesObservableState_2158) {
  Exiv2::IptcKey a(static_cast<uint16_t>(1), static_cast<uint16_t>(2));
  Exiv2::IptcKey b(static_cast<uint16_t>(99), static_cast<uint16_t>(88));

  const auto aKey = a.key();
  const auto aGroup = a.groupName();
  const auto aTagName = a.tagName();
  const auto aTagLabel = a.tagLabel();
  const auto aTagDesc = a.tagDesc();
  const auto aRecordName = a.recordName();

  b = a;

  EXPECT_EQ(b.tag(), a.tag());
  EXPECT_EQ(b.record(), a.record());
  EXPECT_EQ(b.key(), aKey);

  EXPECT_STREQ(b.familyName(), a.familyName());
  EXPECT_EQ(b.groupName(), aGroup);
  EXPECT_EQ(b.tagName(), aTagName);
  EXPECT_EQ(b.tagLabel(), aTagLabel);
  EXPECT_EQ(b.tagDesc(), aTagDesc);
  EXPECT_EQ(b.recordName(), aRecordName);
}

TEST_F(IptcKeyTest_2158, CloneProducesEquivalentKey_2158) {
  Exiv2::IptcKey original(static_cast<uint16_t>(10), static_cast<uint16_t>(2));

  // Clone through the interface.
  auto cloned = original.clone();
  ASSERT_TRUE(static_cast<bool>(cloned));

  // Verify observable behavior is equivalent via the Key interface.
  EXPECT_EQ(cloned->key(), original.key());
  EXPECT_STREQ(cloned->familyName(), original.familyName());
  EXPECT_EQ(cloned->groupName(), original.groupName());
  EXPECT_EQ(cloned->tagName(), original.tagName());
  EXPECT_EQ(cloned->tagLabel(), original.tagLabel());
  EXPECT_EQ(cloned->tagDesc(), original.tagDesc());
  EXPECT_EQ(cloned->tag(), original.tag());

  // Also verify that the clone is independent (different object address).
  EXPECT_NE(cloned.get(), static_cast<const Exiv2::Key*>(&original));
}

TEST_F(IptcKeyTest_2158, WriteToStreamProducesOutput_2158) {
  Exiv2::IptcKey key(static_cast<uint16_t>(7), static_cast<uint16_t>(2));

  std::ostringstream os;
  EXPECT_NO_THROW(key.write(os));

  // We don't assume formatting, only that something was written.
  EXPECT_FALSE(os.str().empty());
}

TEST_F(IptcKeyTest_2158, ConstructFromStringDoesNotCrash_2158) {
  // We do not assume exact key string formats here; this test only verifies
  // the constructor is usable and public methods are callable afterward.
  const std::string input = "Iptc.Application2.ObjectName";

  ASSERT_NO_THROW({
    Exiv2::IptcKey key(input);

    EXPECT_NO_THROW((void)key.key());
    EXPECT_NO_THROW((void)key.familyName());
    EXPECT_NO_THROW((void)key.groupName());
    EXPECT_NO_THROW((void)key.tagName());
    EXPECT_NO_THROW((void)key.tagLabel());
    EXPECT_NO_THROW((void)key.tagDesc());
    EXPECT_NO_THROW((void)key.tag());
    EXPECT_NO_THROW((void)key.record());
    EXPECT_NO_THROW((void)key.recordName());

    EXPECT_NE(key.familyName(), nullptr);

    // Clone should be possible regardless of how the key decomposes internally.
    auto cloned = key.clone();
    ASSERT_TRUE(static_cast<bool>(cloned));
    EXPECT_EQ(cloned->key(), key.key());
  });
}

TEST_F(IptcKeyTest_2158, ConstructFromEmptyStringIsHandled_2158) {
  // Error/edge case: empty key string. Behavior may be "valid but empty",
  // or it may throw; we only assert it is handled deterministically (no crash).
  const std::string input;

  try {
    Exiv2::IptcKey key(input);
    // If construction succeeds, the object should still be usable.
    EXPECT_NO_THROW((void)key.key());
    EXPECT_NO_THROW((void)key.tag());
    EXPECT_NO_THROW((void)key.record());
  } catch (...) {
    SUCCEED() << "IptcKey(empty) threw an exception (acceptable error handling).";
  }
}

}  // namespace