// File: test_exifdatum_groupname_744.cpp
// Unit tests for Exiv2::Exifdatum::groupName()
// The TEST_ID is 744

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/tags.hpp>

#include <string>

namespace {

// Keep all tests under a single fixture tied to TEST_ID 744.
class ExifdatumGroupNameTest_744 : public ::testing::Test {
 protected:
  // Helper to construct an Exifdatum without assuming anything about Value handling.
  // We intentionally pass nullptr for pValue to avoid depending on any specific Value subtype.
  static Exiv2::Exifdatum MakeDatum(const Exiv2::ExifKey& key) {
    return Exiv2::Exifdatum(key, nullptr);
  }
};

TEST_F(ExifdatumGroupNameTest_744, ReturnsSameAsKeyGroupName_ForTagAndGroupCtor_744) {
  const std::string kGroup = "TestGroup744";
  Exiv2::ExifKey key(/*tag=*/0x010F, kGroup);  // tag value arbitrary; only interface matters

  Exiv2::Exifdatum datum = MakeDatum(key);

  // Observable contract: Exifdatum::groupName() is derived from its key (black-box),
  // so we compare to ExifKey::groupName() rather than hardcoding.
  EXPECT_EQ(datum.groupName(), key.groupName());
}

TEST_F(ExifdatumGroupNameTest_744, ReturnsSameAsKeyGroupName_ForStringKeyCtor_744) {
  // Use a key-string form; we don't assume parsing rules, only that key exposes groupName().
  Exiv2::ExifKey key(std::string("Exif.Photo.Make"));

  Exiv2::Exifdatum datum = MakeDatum(key);

  EXPECT_EQ(datum.groupName(), key.groupName());
}

TEST_F(ExifdatumGroupNameTest_744, ReturnsEmptyWhenKeyGroupNameIsEmpty_744) {
  const std::string kEmptyGroup;
  Exiv2::ExifKey key(/*tag=*/0x0001, kEmptyGroup);

  Exiv2::Exifdatum datum = MakeDatum(key);

  EXPECT_EQ(key.groupName(), std::string());        // boundary: empty group name
  EXPECT_EQ(datum.groupName(), key.groupName());    // datum mirrors key's observable groupName
  EXPECT_EQ(datum.groupName(), std::string());      // also empty
}

TEST_F(ExifdatumGroupNameTest_744, RepeatedCallsAreConsistent_744) {
  Exiv2::ExifKey key(/*tag=*/0x0132, std::string("RepeatGroup744"));
  Exiv2::Exifdatum datum = MakeDatum(key);

  const std::string first = datum.groupName();
  const std::string second = datum.groupName();
  const std::string third = datum.groupName();

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
  EXPECT_EQ(first, key.groupName());
}

TEST_F(ExifdatumGroupNameTest_744, CopyConstructorPreservesGroupName_744) {
  Exiv2::ExifKey key(/*tag=*/0x829A, std::string("CopyCtorGroup744"));
  Exiv2::Exifdatum original = MakeDatum(key);

  Exiv2::Exifdatum copy(original);

  EXPECT_EQ(copy.groupName(), original.groupName());
  EXPECT_EQ(copy.groupName(), key.groupName());
}

TEST_F(ExifdatumGroupNameTest_744, CopyAssignmentPreservesGroupName_744) {
  Exiv2::ExifKey keyA(/*tag=*/0x0002, std::string("GroupA744"));
  Exiv2::ExifKey keyB(/*tag=*/0x0003, std::string("GroupB744"));

  Exiv2::Exifdatum a = MakeDatum(keyA);
  Exiv2::Exifdatum b = MakeDatum(keyB);

  ASSERT_EQ(a.groupName(), keyA.groupName());
  ASSERT_EQ(b.groupName(), keyB.groupName());

  b = a;

  EXPECT_EQ(b.groupName(), a.groupName());
  EXPECT_EQ(b.groupName(), keyA.groupName());
}

TEST_F(ExifdatumGroupNameTest_744, SelfAssignmentDoesNotChangeGroupName_744) {
  Exiv2::ExifKey key(/*tag=*/0x9003, std::string("SelfAssignGroup744"));
  Exiv2::Exifdatum datum = MakeDatum(key);

  const std::string before = datum.groupName();
  datum = datum;  // self-assignment should be safe/observable no-op

  EXPECT_EQ(datum.groupName(), before);
  EXPECT_EQ(datum.groupName(), key.groupName());
}

TEST_F(ExifdatumGroupNameTest_744, HandlesLongGroupName_744) {
  std::string longGroup(1024, 'G');
  longGroup.replace(0, 12, "LongGroup744");

  Exiv2::ExifKey key(/*tag=*/0xA002, longGroup);
  Exiv2::Exifdatum datum = MakeDatum(key);

  EXPECT_EQ(datum.groupName(), key.groupName());
  EXPECT_EQ(datum.groupName().size(), key.groupName().size());
}

}  // namespace