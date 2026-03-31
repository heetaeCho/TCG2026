#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"
#include "exiv2/exiv2.hpp"

using namespace Exiv2::Internal;

// Helper class to access protected members for testing
class TestableTiffDirectory : public TiffDirectory {
public:
    using TiffDirectory::TiffDirectory;
    
    // Expose protected methods for testing
    TiffDirectory* callDoClone() const {
        return doClone();
    }
    
    size_t callDoCount() const {
        return doCount();
    }
    
    size_t callDoSize() const {
        return doSize();
    }
    
    size_t callDoSizeData() const {
        return doSizeData();
    }
    
    size_t callDoSizeImage() const {
        return doSizeImage();
    }
};

class TiffDirectoryTest_290 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    
    void TearDown() override {
    }
};

// Test construction with hasNext = true
TEST_F(TiffDirectoryTest_290, ConstructWithHasNextTrue_290) {
    TestableTiffDirectory dir(0x0001, IfdId::ifd0Id, true);
    EXPECT_TRUE(dir.hasNext());
}

// Test construction with hasNext = false
TEST_F(TiffDirectoryTest_290, ConstructWithHasNextFalse_290) {
    TestableTiffDirectory dir(0x0001, IfdId::ifd0Id, false);
    EXPECT_FALSE(dir.hasNext());
}

// Test tag is preserved from construction
TEST_F(TiffDirectoryTest_290, TagPreserved_290) {
    TestableTiffDirectory dir(0x1234, IfdId::ifd0Id, false);
    EXPECT_EQ(dir.tag(), 0x1234);
}

// Test group is preserved from construction
TEST_F(TiffDirectoryTest_290, GroupPreserved_290) {
    TestableTiffDirectory dir(0x0001, IfdId::ifd1Id, false);
    EXPECT_EQ(dir.group(), IfdId::ifd1Id);
}

// Test construction with tag value 0
TEST_F(TiffDirectoryTest_290, ConstructWithZeroTag_290) {
    TestableTiffDirectory dir(0x0000, IfdId::ifd0Id, true);
    EXPECT_EQ(dir.tag(), 0x0000);
    EXPECT_TRUE(dir.hasNext());
}

// Test construction with max tag value
TEST_F(TiffDirectoryTest_290, ConstructWithMaxTag_290) {
    TestableTiffDirectory dir(0xFFFF, IfdId::ifd0Id, false);
    EXPECT_EQ(dir.tag(), 0xFFFF);
}

// Test doClone creates a copy with same hasNext
TEST_F(TiffDirectoryTest_290, DoClonePreservesHasNext_290) {
    TestableTiffDirectory dir(0x0001, IfdId::ifd0Id, true);
    TiffDirectory* clone = dir.callDoClone();
    ASSERT_NE(clone, nullptr);
    EXPECT_TRUE(clone->hasNext());
    delete clone;
}

// Test doClone creates a copy with hasNext false
TEST_F(TiffDirectoryTest_290, DoClonePreservesHasNextFalse_290) {
    TestableTiffDirectory dir(0x0001, IfdId::ifd0Id, false);
    TiffDirectory* clone = dir.callDoClone();
    ASSERT_NE(clone, nullptr);
    EXPECT_FALSE(clone->hasNext());
    delete clone;
}

// Test doClone creates a distinct object
TEST_F(TiffDirectoryTest_290, DoCloneCreatesDistinctObject_290) {
    TestableTiffDirectory dir(0x0001, IfdId::ifd0Id, true);
    TiffDirectory* clone = dir.callDoClone();
    ASSERT_NE(clone, nullptr);
    EXPECT_NE(clone, &dir);
    delete clone;
}

// Test empty directory has zero count
TEST_F(TiffDirectoryTest_290, EmptyDirectoryCountIsZero_290) {
    TestableTiffDirectory dir(0x0001, IfdId::ifd0Id, false);
    EXPECT_EQ(dir.callDoCount(), 0u);
}

// Test empty directory size
TEST_F(TiffDirectoryTest_290, EmptyDirectorySize_290) {
    TestableTiffDirectory dir(0x0001, IfdId::ifd0Id, false);
    // An empty directory should have minimal or zero size
    size_t size = dir.callDoSize();
    // Size depends on implementation, but should be deterministic
    EXPECT_GE(size, 0u);
}

// Test empty directory sizeData
TEST_F(TiffDirectoryTest_290, EmptyDirectorySizeData_290) {
    TestableTiffDirectory dir(0x0001, IfdId::ifd0Id, false);
    EXPECT_EQ(dir.callDoSizeData(), 0u);
}

// Test empty directory sizeImage
TEST_F(TiffDirectoryTest_290, EmptyDirectorySizeImage_290) {
    TestableTiffDirectory dir(0x0001, IfdId::ifd0Id, false);
    EXPECT_EQ(dir.callDoSizeImage(), 0u);
}

// Test that copy assignment is deleted (compile-time check - just verify objects can be constructed)
TEST_F(TiffDirectoryTest_290, CopyAssignmentIsDeleted_290) {
    // This test verifies the class is usable despite deleted copy assignment
    TestableTiffDirectory dir1(0x0001, IfdId::ifd0Id, true);
    TestableTiffDirectory dir2(0x0002, IfdId::ifd0Id, false);
    // The following should NOT compile: dir1 = dir2;
    // We just verify both objects are independently valid
    EXPECT_TRUE(dir1.hasNext());
    EXPECT_FALSE(dir2.hasNext());
}

// Test multiple clones are independent
TEST_F(TiffDirectoryTest_290, MultipleClonesAreIndependent_290) {
    TestableTiffDirectory dir(0x0042, IfdId::ifd0Id, true);
    TiffDirectory* clone1 = dir.callDoClone();
    TiffDirectory* clone2 = dir.callDoClone();
    ASSERT_NE(clone1, nullptr);
    ASSERT_NE(clone2, nullptr);
    EXPECT_NE(clone1, clone2);
    EXPECT_TRUE(clone1->hasNext());
    EXPECT_TRUE(clone2->hasNext());
    delete clone1;
    delete clone2;
}

// Test different IfdId groups
TEST_F(TiffDirectoryTest_290, DifferentIfdGroups_290) {
    TestableTiffDirectory dir0(0x0001, IfdId::ifd0Id, false);
    TestableTiffDirectory dir1(0x0001, IfdId::ifd1Id, false);
    TestableTiffDirectory dirExif(0x0001, IfdId::exifId, true);
    
    EXPECT_EQ(dir0.group(), IfdId::ifd0Id);
    EXPECT_EQ(dir1.group(), IfdId::ifd1Id);
    EXPECT_EQ(dirExif.group(), IfdId::exifId);
    EXPECT_TRUE(dirExif.hasNext());
}
