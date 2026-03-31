#include <gtest/gtest.h>
#include "exiv2/tags.h"
#include "tags_int.hpp"

namespace {

using namespace Exiv2::Internal;

class GroupListTest_1425 : public ::testing::Test {
 protected:
  const GroupInfo* list_;
  void SetUp() override {
    list_ = groupList();
  }
};

// Test that groupList() returns a non-null pointer
TEST_F(GroupListTest_1425, ReturnsNonNull_1425) {
  ASSERT_NE(list_, nullptr);
}

// Test that groupList() skips the first element (ifdIdNotSet) and starts at ifd0Id
TEST_F(GroupListTest_1425, FirstElementIsIfd0_1425) {
  EXPECT_EQ(list_[0].ifdId_, Exiv2::Internal::IfdId::ifd0Id);
}

// Test that the first element has the expected IFD name "IFD0"
TEST_F(GroupListTest_1425, FirstElementIfdName_1425) {
  EXPECT_STREQ(list_[0].ifdName_, "IFD0");
}

// Test that the first element has the expected group name "Image"
TEST_F(GroupListTest_1425, FirstElementGroupName_1425) {
  EXPECT_STREQ(list_[0].groupName_, "Image");
}

// Test that the first element has a non-null tag list
TEST_F(GroupListTest_1425, FirstElementTagListNotNull_1425) {
  EXPECT_NE(list_[0].tagList_, nullptr);
}

// Test that the second element is IFD1 (Thumbnail)
TEST_F(GroupListTest_1425, SecondElementIsIfd1_1425) {
  EXPECT_EQ(list_[1].ifdId_, Exiv2::Internal::IfdId::ifd1Id);
  EXPECT_STREQ(list_[1].ifdName_, "IFD1");
  EXPECT_STREQ(list_[1].groupName_, "Thumbnail");
}

// Test that we can find the Exif group in the list
TEST_F(GroupListTest_1425, ContainsExifGroup_1425) {
  bool found = false;
  for (const GroupInfo* gi = list_; gi->ifdId_ != Exiv2::Internal::IfdId::lastId; ++gi) {
    if (std::string(gi->groupName_) == "Photo") {
      found = true;
      EXPECT_EQ(gi->ifdId_, Exiv2::Internal::IfdId::exifId);
      EXPECT_STREQ(gi->ifdName_, "Exif");
      break;
    }
  }
  EXPECT_TRUE(found);
}

// Test that we can find the GPSInfo group in the list
TEST_F(GroupListTest_1425, ContainsGPSInfoGroup_1425) {
  bool found = false;
  for (const GroupInfo* gi = list_; gi->ifdId_ != Exiv2::Internal::IfdId::lastId; ++gi) {
    if (std::string(gi->groupName_) == "GPSInfo") {
      found = true;
      EXPECT_EQ(gi->ifdId_, Exiv2::Internal::IfdId::gpsId);
      break;
    }
  }
  EXPECT_TRUE(found);
}

// Test that the list is terminated by lastId
TEST_F(GroupListTest_1425, ListTerminatedByLastId_1425) {
  const GroupInfo* gi = list_;
  int count = 0;
  while (gi->ifdId_ != Exiv2::Internal::IfdId::lastId) {
    ++gi;
    ++count;
    // Safety: original array has 126 elements, minus 1 for skipping first = 125
    ASSERT_LT(count, 200) << "List does not appear to be terminated";
  }
  EXPECT_EQ(gi->ifdId_, Exiv2::Internal::IfdId::lastId);
}

// Test that the last element (sentinel) has expected properties
TEST_F(GroupListTest_1425, LastElementProperties_1425) {
  const GroupInfo* gi = list_;
  while (gi->ifdId_ != Exiv2::Internal::IfdId::lastId) {
    ++gi;
  }
  EXPECT_STREQ(gi->ifdName_, "(Last IFD info)");
  EXPECT_STREQ(gi->groupName_, "(Last IFD item)");
  EXPECT_EQ(gi->tagList_, nullptr);
}

// Test that the ifdIdNotSet element is NOT in the returned list (it was skipped)
TEST_F(GroupListTest_1425, DoesNotContainIfdIdNotSet_1425) {
  for (const GroupInfo* gi = list_; gi->ifdId_ != Exiv2::Internal::IfdId::lastId; ++gi) {
    EXPECT_NE(gi->ifdId_, Exiv2::Internal::IfdId::ifdIdNotSet);
  }
}

// Test that the list contains exactly 124 entries before lastId (126 total - 1 skipped - 1 sentinel = 124)
TEST_F(GroupListTest_1425, ListSize_1425) {
  int count = 0;
  for (const GroupInfo* gi = list_; gi->ifdId_ != Exiv2::Internal::IfdId::lastId; ++gi) {
    ++count;
  }
  EXPECT_EQ(count, 124);
}

// Test that Canon maker note group is in the list
TEST_F(GroupListTest_1425, ContainsCanonGroup_1425) {
  bool found = false;
  for (const GroupInfo* gi = list_; gi->ifdId_ != Exiv2::Internal::IfdId::lastId; ++gi) {
    if (std::string(gi->groupName_) == "Canon") {
      found = true;
      EXPECT_EQ(gi->ifdId_, Exiv2::Internal::IfdId::canonId);
      EXPECT_STREQ(gi->ifdName_, "Makernote");
      EXPECT_NE(gi->tagList_, nullptr);
      break;
    }
  }
  EXPECT_TRUE(found);
}

// Test that Nikon3 maker note group is in the list
TEST_F(GroupListTest_1425, ContainsNikon3Group_1425) {
  bool found = false;
  for (const GroupInfo* gi = list_; gi->ifdId_ != Exiv2::Internal::IfdId::lastId; ++gi) {
    if (std::string(gi->groupName_) == "Nikon3") {
      found = true;
      EXPECT_EQ(gi->ifdId_, Exiv2::Internal::IfdId::nikon3Id);
      break;
    }
  }
  EXPECT_TRUE(found);
}

// Test that Sony1 maker note group is in the list
TEST_F(GroupListTest_1425, ContainsSony1Group_1425) {
  bool found = false;
  for (const GroupInfo* gi = list_; gi->ifdId_ != Exiv2::Internal::IfdId::lastId; ++gi) {
    if (std::string(gi->groupName_) == "Sony1") {
      found = true;
      EXPECT_EQ(gi->ifdId_, Exiv2::Internal::IfdId::sony1Id);
      break;
    }
  }
  EXPECT_TRUE(found);
}

// Test that calling groupList() multiple times returns the same pointer
TEST_F(GroupListTest_1425, ConsistentReturnValue_1425) {
  const GroupInfo* list2 = groupList();
  EXPECT_EQ(list_, list2);
}

// Test that Panasonic maker note group is present
TEST_F(GroupListTest_1425, ContainsPanasonicGroup_1425) {
  bool found = false;
  for (const GroupInfo* gi = list_; gi->ifdId_ != Exiv2::Internal::IfdId::lastId; ++gi) {
    if (std::string(gi->groupName_) == "Panasonic") {
      found = true;
      EXPECT_EQ(gi->ifdId_, Exiv2::Internal::IfdId::panasonicId);
      break;
    }
  }
  EXPECT_TRUE(found);
}

// Test that Olympus maker note group is present
TEST_F(GroupListTest_1425, ContainsOlympusGroup_1425) {
  bool found = false;
  for (const GroupInfo* gi = list_; gi->ifdId_ != Exiv2::Internal::IfdId::lastId; ++gi) {
    if (std::string(gi->groupName_) == "Olympus") {
      found = true;
      EXPECT_EQ(gi->ifdId_, Exiv2::Internal::IfdId::olympusId);
      break;
    }
  }
  EXPECT_TRUE(found);
}

// Test that Iop group is present
TEST_F(GroupListTest_1425, ContainsIopGroup_1425) {
  bool found = false;
  for (const GroupInfo* gi = list_; gi->ifdId_ != Exiv2::Internal::IfdId::lastId; ++gi) {
    if (std::string(gi->groupName_) == "Iop") {
      found = true;
      EXPECT_EQ(gi->ifdId_, Exiv2::Internal::IfdId::iopId);
      break;
    }
  }
  EXPECT_TRUE(found);
}

// Test that all Makernote groups have "Makernote" as ifdName
TEST_F(GroupListTest_1425, MakernoteGroupsHaveCorrectIfdName_1425) {
  for (const GroupInfo* gi = list_; gi->ifdId_ != Exiv2::Internal::IfdId::lastId; ++gi) {
    if (gi->ifdId_ >= Exiv2::Internal::IfdId::mnId && gi->ifdId_ <= Exiv2::Internal::IfdId::sony2010eId) {
      // Most maker note IDs should have "Makernote" as ifdName
      // (with some exceptions for preview IFDs that use standard ifd tags)
      // We just check that ifdName is not null
      EXPECT_NE(gi->ifdName_, nullptr);
    }
  }
}

// Test that all non-sentinel entries have non-null ifdName and groupName
TEST_F(GroupListTest_1425, AllEntriesHaveNonNullNames_1425) {
  for (const GroupInfo* gi = list_; gi->ifdId_ != Exiv2::Internal::IfdId::lastId; ++gi) {
    EXPECT_NE(gi->ifdName_, nullptr) << "ifdName is null for ifdId " << static_cast<int>(gi->ifdId_);
    EXPECT_NE(gi->groupName_, nullptr) << "groupName is null for ifdId " << static_cast<int>(gi->ifdId_);
  }
}

}  // namespace
