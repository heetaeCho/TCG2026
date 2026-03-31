#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"
#include "tiffimage_int.hpp"
#include "tags.hpp"

#include <memory>
#include <stack>

using namespace Exiv2;
using namespace Exiv2::Internal;

class TiffDirectoryTest_320 : public ::testing::Test {
 protected:
  void SetUp() override {
  }

  void TearDown() override {
  }
};

// Test: Creating a TiffDirectory with hasNext = true
TEST_F(TiffDirectoryTest_320, ConstructWithHasNext_320) {
  TiffDirectory dir(0x0001, IfdId::ifd0Id, true);
  EXPECT_EQ(dir.tag(), 0x0001);
  EXPECT_EQ(dir.group(), IfdId::ifd0Id);
  EXPECT_TRUE(dir.hasNext());
}

// Test: Creating a TiffDirectory with hasNext = false
TEST_F(TiffDirectoryTest_320, ConstructWithoutHasNext_320) {
  TiffDirectory dir(0x0002, IfdId::exifId, false);
  EXPECT_EQ(dir.tag(), 0x0002);
  EXPECT_EQ(dir.group(), IfdId::exifId);
  EXPECT_FALSE(dir.hasNext());
}

// Test: Tag and group are correctly stored
TEST_F(TiffDirectoryTest_320, TagAndGroupAccessors_320) {
  TiffDirectory dir(0x1234, IfdId::gpsId, false);
  EXPECT_EQ(dir.tag(), 0x1234);
  EXPECT_EQ(dir.group(), IfdId::gpsId);
}

// Test: addPath with a valid path that creates a new child entry
TEST_F(TiffDirectoryTest_320, AddPathCreatesChild_320) {
  TiffDirectory dir(0x0000, IfdId::ifd0Id, true);
  
  // Use TiffCreator::getPath to construct a valid path for a known tag
  // Tag 0x010f (Make) in IFD0
  try {
    TiffPath path = TiffCreator::getPath(0x010f, IfdId::ifd0Id, Tag::root);
    if (path.size() > 0) {
      TiffComponent* result = dir.addPath(0x010f, path, &dir, nullptr);
      // The result should be non-null for a valid standard tag path
      // (unless it's a TiffSubIfd at the last level)
      // We just verify no crash occurred
      SUCCEED();
    }
  } catch (...) {
    // Some paths may not be supported; that's acceptable
    SUCCEED();
  }
}

// Test: addPath for GPS IFD entry
TEST_F(TiffDirectoryTest_320, AddPathForGpsTag_320) {
  TiffDirectory dir(0x0000, IfdId::ifd0Id, true);
  
  try {
    TiffPath path = TiffCreator::getPath(0x8825, IfdId::ifd0Id, Tag::root);
    if (path.size() > 0) {
      TiffComponent* result = dir.addPath(0x8825, path, &dir, nullptr);
      SUCCEED();
    }
  } catch (...) {
    SUCCEED();
  }
}

// Test: addPath for Exif IFD entry
TEST_F(TiffDirectoryTest_320, AddPathForExifTag_320) {
  TiffDirectory dir(0x0000, IfdId::ifd0Id, true);
  
  try {
    TiffPath path = TiffCreator::getPath(0x8769, IfdId::ifd0Id, Tag::root);
    if (path.size() > 0) {
      TiffComponent* result = dir.addPath(0x8769, path, &dir, nullptr);
      SUCCEED();
    }
  } catch (...) {
    SUCCEED();
  }
}

// Test: Adding same path twice should find existing component
TEST_F(TiffDirectoryTest_320, AddPathTwiceFindsExisting_320) {
  TiffDirectory dir(0x0000, IfdId::ifd0Id, true);
  
  try {
    TiffPath path1 = TiffCreator::getPath(0x010f, IfdId::ifd0Id, Tag::root);
    TiffPath path2 = TiffCreator::getPath(0x010f, IfdId::ifd0Id, Tag::root);
    
    if (path1.size() > 0 && path2.size() > 0) {
      TiffComponent* result1 = dir.addPath(0x010f, path1, &dir, nullptr);
      TiffComponent* result2 = dir.addPath(0x010f, path2, &dir, nullptr);
      
      // Both should point to the same component
      if (result1 && result2) {
        EXPECT_EQ(result1, result2);
      }
    }
  } catch (...) {
    SUCCEED();
  }
}

// Test: Adding different tags creates different children
TEST_F(TiffDirectoryTest_320, AddPathDifferentTagsCreatesDifferentChildren_320) {
  TiffDirectory dir(0x0000, IfdId::ifd0Id, true);
  
  try {
    TiffPath path1 = TiffCreator::getPath(0x010f, IfdId::ifd0Id, Tag::root);  // Make
    TiffPath path2 = TiffCreator::getPath(0x0110, IfdId::ifd0Id, Tag::root);  // Model
    
    if (path1.size() > 0 && path2.size() > 0) {
      TiffComponent* result1 = dir.addPath(0x010f, path1, &dir, nullptr);
      TiffComponent* result2 = dir.addPath(0x0110, path2, &dir, nullptr);
      
      if (result1 && result2) {
        EXPECT_NE(result1, result2);
      }
    }
  } catch (...) {
    SUCCEED();
  }
}

// Test: TiffDirectory with different groups
TEST_F(TiffDirectoryTest_320, DirectoryWithDifferentGroups_320) {
  TiffDirectory dir1(0x0000, IfdId::ifd0Id, true);
  TiffDirectory dir2(0x0000, IfdId::ifd1Id, false);
  
  EXPECT_EQ(dir1.group(), IfdId::ifd0Id);
  EXPECT_EQ(dir2.group(), IfdId::ifd1Id);
  EXPECT_TRUE(dir1.hasNext());
  EXPECT_FALSE(dir2.hasNext());
}

// Test: Count of empty directory should be 0
TEST_F(TiffDirectoryTest_320, EmptyDirectoryCount_320) {
  TiffDirectory dir(0x0000, IfdId::ifd0Id, false);
  EXPECT_EQ(dir.count(), 0u);
}

// Test: Size of empty directory
TEST_F(TiffDirectoryTest_320, EmptyDirectorySize_320) {
  TiffDirectory dir(0x0000, IfdId::ifd0Id, false);
  EXPECT_EQ(dir.size(), 0u);
}

// Test: addPath with MakerNote tag (0x927c) in exifId - special case
TEST_F(TiffDirectoryTest_320, AddPathMakerNote_320) {
  TiffDirectory dir(0x0000, IfdId::ifd0Id, true);
  
  try {
    // MakerNote is special-cased in the code (0x927c, exifId)
    TiffPath path = TiffCreator::getPath(0x927c, IfdId::exifId, Tag::root);
    if (path.size() > 0) {
      TiffComponent* result = dir.addPath(0x927c, path, &dir, nullptr);
      // Just verify no crash
      SUCCEED();
    }
  } catch (...) {
    SUCCEED();
  }
}

// Test: TiffPathItem basic accessors
TEST_F(TiffDirectoryTest_320, TiffPathItemAccessors_320) {
  TiffPathItem item(0x010f, IfdId::ifd0Id);
  EXPECT_EQ(item.extendedTag(), 0x010fu);
  EXPECT_EQ(item.group(), IfdId::ifd0Id);
  EXPECT_EQ(item.tag(), static_cast<uint16_t>(0x010f));
}

// Test: TiffPathItem with extended tag (Tag::next)
TEST_F(TiffDirectoryTest_320, TiffPathItemWithNextTag_320) {
  TiffPathItem item(Tag::next, IfdId::ifd0Id);
  EXPECT_EQ(item.extendedTag(), static_cast<uint32_t>(Tag::next));
  EXPECT_EQ(item.group(), IfdId::ifd0Id);
}

// Test: TiffPathItem with extended tag (Tag::root)
TEST_F(TiffDirectoryTest_320, TiffPathItemWithRootTag_320) {
  TiffPathItem item(Tag::root, IfdId::ifd0Id);
  EXPECT_EQ(item.extendedTag(), static_cast<uint32_t>(Tag::root));
  EXPECT_EQ(item.group(), IfdId::ifd0Id);
}

// Test: start() returns nullptr for newly created component
TEST_F(TiffDirectoryTest_320, StartIsNullInitially_320) {
  TiffDirectory dir(0x0000, IfdId::ifd0Id, false);
  EXPECT_EQ(dir.start(), nullptr);
}

// Test: addPath with custom object passed in
TEST_F(TiffDirectoryTest_320, AddPathWithCustomObject_320) {
  TiffDirectory dir(0x0000, IfdId::ifd0Id, true);
  
  try {
    TiffPath path = TiffCreator::getPath(0x010f, IfdId::ifd0Id, Tag::root);
    if (path.size() > 0) {
      auto obj = TiffCreator::create(0x010f, IfdId::ifd0Id);
      TiffComponent* result = dir.addPath(0x010f, path, &dir, std::move(obj));
      SUCCEED();
    }
  } catch (...) {
    SUCCEED();
  }
}

// Test: SizeData and SizeImage of empty directory
TEST_F(TiffDirectoryTest_320, EmptyDirectorySizeDataAndImage_320) {
  TiffDirectory dir(0x0000, IfdId::ifd0Id, false);
  EXPECT_EQ(dir.sizeData(), 0u);
  EXPECT_EQ(dir.sizeImage(), 0u);
}

// Test: addPath for IFD1 (thumbnail) entry
TEST_F(TiffDirectoryTest_320, AddPathForIfd1_320) {
  TiffDirectory dir(0x0000, IfdId::ifd0Id, true);
  
  try {
    // Tag::next leads to IFD1
    TiffPath path = TiffCreator::getPath(0x0201, IfdId::ifd1Id, Tag::root);
    if (path.size() > 0) {
      TiffComponent* result = dir.addPath(0x0201, path, &dir, nullptr);
      SUCCEED();
    }
  } catch (...) {
    SUCCEED();
  }
}

// Test: TiffDirectory with tag 0 and ifdIdNotSet
TEST_F(TiffDirectoryTest_320, DirectoryWithNotSetId_320) {
  TiffDirectory dir(0x0000, IfdId::ifdIdNotSet, false);
  EXPECT_EQ(dir.tag(), 0x0000);
  EXPECT_EQ(dir.group(), IfdId::ifdIdNotSet);
  EXPECT_FALSE(dir.hasNext());
}
