// File: test_iptckey_clone_649.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <memory>
#include <string>
#include <type_traits>

#include "exiv2/datasets.hpp"  // Exiv2::IptcKey

namespace {

class IptcKeyCloneTest_649 : public ::testing::Test {};

TEST_F(IptcKeyCloneTest_649, CloneFromStringKey_CreatesNonNullCopy_649) {
  const Exiv2::IptcKey original(std::string("Iptc.Application2.ObjectName"));

  auto cloned = original.clone();
  ASSERT_NE(cloned.get(), nullptr);

  // Must be a different object.
  EXPECT_NE(cloned.get(), &original);

  // Observable equality through public interface.
  EXPECT_EQ(cloned->key(), original.key());
  EXPECT_EQ(cloned->tag(), original.tag());
  EXPECT_EQ(cloned->record(), original.record());
  EXPECT_STREQ(cloned->familyName(), original.familyName());
  EXPECT_EQ(cloned->groupName(), original.groupName());
  EXPECT_EQ(cloned->tagName(), original.tagName());
  EXPECT_EQ(cloned->tagLabel(), original.tagLabel());
  EXPECT_EQ(cloned->tagDesc(), original.tagDesc());
  EXPECT_EQ(cloned->recordName(), original.recordName());
}

TEST_F(IptcKeyCloneTest_649, CloneFromTagRecord_CopiesTagAndRecord_649) {
  const uint16_t tag = 5;
  const uint16_t record = 2;
  const Exiv2::IptcKey original(tag, record);

  auto cloned = original.clone();
  ASSERT_NE(cloned.get(), nullptr);

  EXPECT_NE(cloned.get(), &original);
  EXPECT_EQ(cloned->tag(), original.tag());
  EXPECT_EQ(cloned->record(), original.record());

  // Also verify other observable strings are consistent.
  EXPECT_EQ(cloned->key(), original.key());
  EXPECT_STREQ(cloned->familyName(), original.familyName());
  EXPECT_EQ(cloned->groupName(), original.groupName());
  EXPECT_EQ(cloned->tagName(), original.tagName());
  EXPECT_EQ(cloned->tagLabel(), original.tagLabel());
  EXPECT_EQ(cloned->tagDesc(), original.tagDesc());
  EXPECT_EQ(cloned->recordName(), original.recordName());
}

TEST_F(IptcKeyCloneTest_649, CloneCanBeCalledOnConstObject_649) {
  const Exiv2::IptcKey original(std::string("Iptc.Application2.Caption"));

  // Compile-time check: clone() is callable on const object.
  static_assert(std::is_same_v<decltype(original.clone()), Exiv2::IptcKey::UniquePtr>,
                "IptcKey::clone() should return IptcKey::UniquePtr");

  auto cloned = original.clone();
  ASSERT_NE(cloned.get(), nullptr);

  EXPECT_NE(cloned.get(), &original);
  EXPECT_EQ(cloned->key(), original.key());
}

TEST_F(IptcKeyCloneTest_649, CloneDoesNotThrowOnBoundaryInputs_649) {
  // Boundary: empty key string
  const Exiv2::IptcKey emptyKey(std::string(""));
  EXPECT_NO_THROW({
    auto c = emptyKey.clone();
    ASSERT_NE(c.get(), nullptr);
    EXPECT_EQ(c->key(), emptyKey.key());
  });

  // Boundary: min/max uint16 values
  const Exiv2::IptcKey minVals(static_cast<uint16_t>(0), static_cast<uint16_t>(0));
  EXPECT_NO_THROW({
    auto c = minVals.clone();
    ASSERT_NE(c.get(), nullptr);
    EXPECT_EQ(c->tag(), minVals.tag());
    EXPECT_EQ(c->record(), minVals.record());
    EXPECT_EQ(c->key(), minVals.key());
  });

  const Exiv2::IptcKey maxVals(static_cast<uint16_t>(0xFFFF), static_cast<uint16_t>(0xFFFF));
  EXPECT_NO_THROW({
    auto c = maxVals.clone();
    ASSERT_NE(c.get(), nullptr);
    EXPECT_EQ(c->tag(), maxVals.tag());
    EXPECT_EQ(c->record(), maxVals.record());
    EXPECT_EQ(c->key(), maxVals.key());
  });
}

}  // namespace