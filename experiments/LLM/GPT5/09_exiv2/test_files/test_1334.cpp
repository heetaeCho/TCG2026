// File: test_exifkey_operator_assign_1334.cpp
// Unit tests for Exiv2::ExifKey::operator=
// TEST_ID: 1334

#include <gtest/gtest.h>

#include <cstdint>
#include <string>

#include <exiv2/tags.hpp>

namespace {

class ExifKeyAssignmentTest_1334 : public ::testing::Test {
 protected:
  static Exiv2::ExifKey MakeFromKeyString(const std::string& key) {
    return Exiv2::ExifKey(key);
  }

  static Exiv2::ExifKey MakeFromTagAndGroup(uint16_t tag, const std::string& group) {
    return Exiv2::ExifKey(tag, group);
  }
};

TEST_F(ExifKeyAssignmentTest_1334, SelfAssignmentReturnsSameObjectAndKeepsObservables_1334) {
  Exiv2::ExifKey k = MakeFromKeyString("Exif.Image.Make");

  const std::string key_before = k.key();
  const std::string group_before = k.groupName();
  const uint16_t tag_before = k.tag();
  const int idx_before = k.idx();

  Exiv2::ExifKey* const addr_before = &k;
  Exiv2::ExifKey& ret = (k = k);

  EXPECT_EQ(&ret, addr_before);
  EXPECT_EQ(&k, addr_before);

  // Self-assignment should not change observable properties.
  EXPECT_EQ(k.key(), key_before);
  EXPECT_EQ(k.groupName(), group_before);
  EXPECT_EQ(k.tag(), tag_before);
  EXPECT_EQ(k.idx(), idx_before);
}

TEST_F(ExifKeyAssignmentTest_1334, AssignCopiesObservableStateFromRhs_1334) {
  Exiv2::ExifKey lhs = MakeFromKeyString("Exif.Photo.ExposureTime");
  Exiv2::ExifKey rhs = MakeFromKeyString("Exif.Image.Model");

  // Make RHS distinctive via public API where possible.
  EXPECT_NO_THROW(rhs.setIdx(7));

  Exiv2::ExifKey& ret = (lhs = rhs);

  // operator= returns *this
  EXPECT_EQ(&ret, &lhs);

  // After assignment, LHS should match RHS for observable getters.
  EXPECT_EQ(lhs.key(), rhs.key());
  EXPECT_EQ(lhs.familyName(), rhs.familyName());
  EXPECT_EQ(lhs.groupName(), rhs.groupName());
  EXPECT_EQ(lhs.tagName(), rhs.tagName());
  EXPECT_EQ(lhs.tagLabel(), rhs.tagLabel());
  EXPECT_EQ(lhs.tagDesc(), rhs.tagDesc());
  EXPECT_EQ(lhs.tag(), rhs.tag());
  EXPECT_EQ(lhs.idx(), rhs.idx());
}

TEST_F(ExifKeyAssignmentTest_1334, AssignOverwritesPreviousState_1334) {
  Exiv2::ExifKey lhs = MakeFromKeyString("Exif.Photo.FNumber");
  Exiv2::ExifKey rhs1 = MakeFromKeyString("Exif.Image.Software");
  Exiv2::ExifKey rhs2 = MakeFromKeyString("Exif.Image.DateTime");

  EXPECT_NO_THROW(rhs1.setIdx(1));
  EXPECT_NO_THROW(rhs2.setIdx(2));

  lhs = rhs1;

  const std::string key_after_first = lhs.key();
  const int idx_after_first = lhs.idx();

  // Overwrite with a different rhs.
  lhs = rhs2;

  // Ensure it actually updated to rhs2 (observable equality).
  EXPECT_EQ(lhs.key(), rhs2.key());
  EXPECT_EQ(lhs.idx(), rhs2.idx());

  // And it should no longer necessarily match the first assignment state.
  EXPECT_NE(lhs.key(), key_after_first);
  EXPECT_NE(lhs.idx(), idx_after_first);
}

TEST_F(ExifKeyAssignmentTest_1334, ChainedAssignmentAssociatesAndReturnsLhsRef_1334) {
  Exiv2::ExifKey a = MakeFromKeyString("Exif.Image.Artist");
  Exiv2::ExifKey b = MakeFromKeyString("Exif.Image.Copyright");
  Exiv2::ExifKey c = MakeFromKeyString("Exif.Image.XPComment");

  EXPECT_NO_THROW(c.setIdx(42));

  // Chained assignment: a = (b = c)
  Exiv2::ExifKey& b_ret = (b = c);
  EXPECT_EQ(&b_ret, &b);

  Exiv2::ExifKey& a_ret = (a = b_ret);
  EXPECT_EQ(&a_ret, &a);

  // Both a and b should now match c in observable getters.
  EXPECT_EQ(b.key(), c.key());
  EXPECT_EQ(b.groupName(), c.groupName());
  EXPECT_EQ(b.tag(), c.tag());
  EXPECT_EQ(b.idx(), c.idx());

  EXPECT_EQ(a.key(), c.key());
  EXPECT_EQ(a.groupName(), c.groupName());
  EXPECT_EQ(a.tag(), c.tag());
  EXPECT_EQ(a.idx(), c.idx());
}

TEST_F(ExifKeyAssignmentTest_1334, AssignBetweenDifferentConstructionForms_1334) {
  // Boundary-ish: empty key string construction (should be handled by implementation).
  Exiv2::ExifKey lhs = MakeFromKeyString("");
  Exiv2::ExifKey rhs = MakeFromTagAndGroup(/*tag=*/0u, /*group=*/"Image");

  // Make rhs distinctive.
  EXPECT_NO_THROW(rhs.setIdx(-1));

  EXPECT_NO_THROW(lhs = rhs);

  EXPECT_EQ(lhs.key(), rhs.key());
  EXPECT_EQ(lhs.groupName(), rhs.groupName());
  EXPECT_EQ(lhs.tag(), rhs.tag());
  EXPECT_EQ(lhs.idx(), rhs.idx());
}

}  // namespace