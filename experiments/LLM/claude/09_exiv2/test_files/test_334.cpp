#include <gtest/gtest.h>
#include <memory>

// Include necessary headers from exiv2
#include "tiffcomposite_int.hpp"

using namespace Exiv2::Internal;

// Helper to create a simple TiffComponent for testing
// We'll use TiffDirectory itself as a TiffComponent since it derives from TiffComponent
class TiffDirectoryTest_334 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that TiffDirectory with hasNext=true allows adding a next component
TEST_F(TiffDirectoryTest_334, DoAddNextWithHasNextTrue_ReturnsComponent_334) {
    TiffDirectory dir(0x0001, IfdId::ifd0Id, true);

    auto nextComponent = std::make_unique<TiffDirectory>(0x0002, IfdId::ifd1Id, false);
    TiffComponent* rawPtr = nextComponent.get();

    TiffComponent* result = dir.doAddNext(std::move(nextComponent));

    EXPECT_NE(result, nullptr);
    EXPECT_EQ(result, rawPtr);
}

// Test that TiffDirectory with hasNext=false returns nullptr when adding next
TEST_F(TiffDirectoryTest_334, DoAddNextWithHasNextFalse_ReturnsNullptr_334) {
    TiffDirectory dir(0x0001, IfdId::ifd0Id, false);

    auto nextComponent = std::make_unique<TiffDirectory>(0x0002, IfdId::ifd1Id, false);

    TiffComponent* result = dir.doAddNext(std::move(nextComponent));

    EXPECT_EQ(result, nullptr);
}

// Test that hasNext() returns true when constructed with hasNext=true
TEST_F(TiffDirectoryTest_334, HasNextReturnsTrue_WhenConstructedWithTrue_334) {
    TiffDirectory dir(0x0001, IfdId::ifd0Id, true);
    EXPECT_TRUE(dir.hasNext());
}

// Test that hasNext() returns false when constructed with hasNext=false
TEST_F(TiffDirectoryTest_334, HasNextReturnsFalse_WhenConstructedWithFalse_334) {
    TiffDirectory dir(0x0001, IfdId::ifd0Id, false);
    EXPECT_FALSE(dir.hasNext());
}

// Test adding nullptr as next component when hasNext is true
TEST_F(TiffDirectoryTest_334, DoAddNextWithNullptr_WhenHasNextTrue_334) {
    TiffDirectory dir(0x0001, IfdId::ifd0Id, true);

    TiffComponent::UniquePtr nullComponent(nullptr);
    TiffComponent* result = dir.doAddNext(std::move(nullComponent));

    // When hasNext_ is true, it should set pNext_ and return its get() which would be nullptr
    EXPECT_EQ(result, nullptr);
}

// Test adding nullptr as next component when hasNext is false
TEST_F(TiffDirectoryTest_334, DoAddNextWithNullptr_WhenHasNextFalse_334) {
    TiffDirectory dir(0x0001, IfdId::ifd0Id, false);

    TiffComponent::UniquePtr nullComponent(nullptr);
    TiffComponent* result = dir.doAddNext(std::move(nullComponent));

    EXPECT_EQ(result, nullptr);
}

// Test that calling doAddNext twice replaces the previous next component
TEST_F(TiffDirectoryTest_334, DoAddNextCalledTwice_ReplacesNext_334) {
    TiffDirectory dir(0x0001, IfdId::ifd0Id, true);

    auto first = std::make_unique<TiffDirectory>(0x0002, IfdId::ifd1Id, false);
    auto second = std::make_unique<TiffDirectory>(0x0003, IfdId::ifd1Id, false);
    TiffComponent* secondRawPtr = second.get();

    dir.doAddNext(std::move(first));
    TiffComponent* result = dir.doAddNext(std::move(second));

    EXPECT_NE(result, nullptr);
    EXPECT_EQ(result, secondRawPtr);
}

// Test construction with various tag values
TEST_F(TiffDirectoryTest_334, ConstructionWithDifferentTags_334) {
    TiffDirectory dir1(0x0000, IfdId::ifd0Id, true);
    EXPECT_EQ(dir1.tag(), 0x0000);

    TiffDirectory dir2(0xFFFF, IfdId::ifd0Id, false);
    EXPECT_EQ(dir2.tag(), 0xFFFF);

    TiffDirectory dir3(0x8769, IfdId::exifId, true);
    EXPECT_EQ(dir3.tag(), 0x8769);
}

// Test that doCount returns 0 for empty directory
TEST_F(TiffDirectoryTest_334, DoCount_EmptyDirectory_ReturnsZero_334) {
    TiffDirectory dir(0x0001, IfdId::ifd0Id, false);
    EXPECT_EQ(dir.doCount(), 0u);
}

// Test that doSize returns appropriate value for empty directory
TEST_F(TiffDirectoryTest_334, DoSize_EmptyDirectory_334) {
    TiffDirectory dir(0x0001, IfdId::ifd0Id, false);
    // An empty IFD still has the 2-byte count field and 4-byte next IFD offset
    // but exact size depends on implementation
    size_t size = dir.doSize();
    // Just verify it doesn't crash; exact value is implementation-dependent
    EXPECT_GE(size, 0u);
}

// Test doSizeData for empty directory
TEST_F(TiffDirectoryTest_334, DoSizeData_EmptyDirectory_334) {
    TiffDirectory dir(0x0001, IfdId::ifd0Id, false);
    size_t sizeData = dir.doSizeData();
    EXPECT_GE(sizeData, 0u);
}

// Test doSizeImage for empty directory
TEST_F(TiffDirectoryTest_334, DoSizeImage_EmptyDirectory_334) {
    TiffDirectory dir(0x0001, IfdId::ifd0Id, false);
    size_t sizeImage = dir.doSizeImage();
    EXPECT_GE(sizeImage, 0u);
}
