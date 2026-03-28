#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "tiffcomposite_int.hpp"

namespace Exiv2 { namespace Internal {

class MockTiffComponent : public TiffComponent {
public:
    MOCK_METHOD(TiffComponent*, addPath, (uint16_t tag, TiffPath & tiffPath, TiffComponent* pRoot, TiffComponent::UniquePtr object), (override));
    MOCK_METHOD(TiffComponent*, addChild, (TiffComponent::SharedPtr tiffComponent), (override));
    MOCK_METHOD(void, accept, (TiffVisitor & visitor), (override));
    MOCK_METHOD(size_t, write, (IoWrapper & ioWrapper, ByteOrder byteOrder, size_t offset, size_t valueIdx, size_t dataIdx, size_t & imageIdx), (override));
    MOCK_METHOD(size_t, count, (), (const, override));
};

class TiffSubIfdTest : public ::testing::Test {
protected:
    uint16_t tag = 1001;
    IfdId group = IfdId::Exif;
    IfdId newGroup = IfdId::ExifIfd;

    TiffSubIfdTest() : subIfd(tag, group, newGroup) {}

    TiffSubIfd subIfd;
};

TEST_F(TiffSubIfdTest, ConstructorInitializesCorrectly_321) {
    EXPECT_EQ(subIfd.tag(), tag);
    EXPECT_EQ(subIfd.group(), group);
    EXPECT_EQ(subIfd.newGroup_, newGroup);
}

TEST_F(TiffSubIfdTest, AddPathHandlesEmptyPathCorrectly_322) {
    TiffPath tiffPath;
    TiffComponent::UniquePtr object = nullptr;
    TiffComponent* root = nullptr;

    // Adding an empty path should call addChild
    EXPECT_CALL(subIfd, addChild(testing::_)).Times(1);
    subIfd.doAddPath(tag, tiffPath, root, std::move(object));
}

TEST_F(TiffSubIfdTest, AddPathHandlesValidPath_323) {
    TiffPath tiffPath;
    tiffPath.push(TiffPathItem(100, IfdId::Exif));  // Pushing an item to path
    TiffComponent::UniquePtr object = nullptr;
    TiffComponent* root = nullptr;

    // Check if we call addPath of internal ifds_
    EXPECT_CALL(subIfd, addPath(tag, tiffPath, root, std::move(object))).Times(1);
    subIfd.doAddPath(tag, tiffPath, root, std::move(object));
}

TEST_F(TiffSubIfdTest, AddPathHandlesNonEmptyPath_324) {
    TiffPath tiffPath;
    tiffPath.push(TiffPathItem(200, IfdId::Exif));  // Valid tag and group
    TiffComponent::UniquePtr object = nullptr;
    TiffComponent* root = nullptr;

    // Check if we return the appropriate child for the non-empty path
    EXPECT_CALL(subIfd, addChild(testing::_)).Times(1);
    subIfd.doAddPath(tag, tiffPath, root, std::move(object));
}

TEST_F(TiffSubIfdTest, DoAddChildWorks_325) {
    TiffComponent::SharedPtr childComponent = std::make_shared<MockTiffComponent>();
    
    // Expect that addChild is called when doAddChild is invoked
    EXPECT_CALL(subIfd, addChild(childComponent)).Times(1);
    subIfd.doAddChild(childComponent);
}

TEST_F(TiffSubIfdTest, DoAcceptVisitor_326) {
    TiffVisitor mockVisitor;

    // Verify that accept method works with visitor
    EXPECT_CALL(subIfd, accept(mockVisitor)).Times(1);
    subIfd.doAccept(mockVisitor);
}

TEST_F(TiffSubIfdTest, WriteMethodWorks_327) {
    IoWrapper mockIoWrapper;
    ByteOrder mockByteOrder = ByteOrder::BigEndian;
    size_t offset = 0, valueIdx = 0, dataIdx = 0, imageIdx = 0;

    // Expect write to be called once
    EXPECT_CALL(subIfd, write(mockIoWrapper, mockByteOrder, offset, valueIdx, dataIdx, imageIdx)).Times(1);
    subIfd.write(mockIoWrapper, mockByteOrder, offset, valueIdx, dataIdx, imageIdx);
}

TEST_F(TiffSubIfdTest, CountMethodWorks_328) {
    // Check if count method works correctly
    EXPECT_CALL(subIfd, count()).WillOnce(testing::Return(5));
    EXPECT_EQ(subIfd.count(), 5);
}

} }  // namespace Exiv2::Internal