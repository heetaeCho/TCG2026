#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/tiffcomposite_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::Return;



class MockTiffComponent : public TiffComponent {

public:

    MOCK_METHOD(TiffComponent*, addPath, (uint16_t tag, TiffPath& tiffPath, TiffComponent* pRoot, UniquePtr object), (override));

    MOCK_METHOD(void, accept, (TiffVisitor& visitor), (override));

    MOCK_METHOD(size_t, write, (IoWrapper& ioWrapper, ByteOrder byteOrder, size_t offset, size_t valueIdx, size_t dataIdx, size_t & imageIdx), (const, override));

    MOCK_METHOD(const UniquePtr, clone, (), (const, override));

    MOCK_METHOD(size_t, writeData, (IoWrapper& ioWrapper, ByteOrder byteOrder, size_t offset, size_t dataIdx, size_t & imageIdx), (const, override));

    MOCK_METHOD(size_t, writeImage, (IoWrapper& ioWrapper, ByteOrder byteOrder), (const, override));

    MOCK_METHOD(size_t, size, (), (const, override));

    MOCK_METHOD(size_t, count, (), (const, override));

    MOCK_METHOD(size_t, sizeData, (), (const, override));

    MOCK_METHOD(size_t, sizeImage, (), (const, override));

};



class TiffIfdMakernoteTest : public ::testing::Test {

protected:

    std::unique_ptr<MockTiffComponent> mockRoot = std::make_unique<MockTiffComponent>();

    std::unique_ptr<MnHeader> mockHeader = std::make_unique<MnHeader>();

    TiffPath tiffPath;

    uint16_t tag = 0x0112; // Example tag

    IfdId group = ifdExif;

    IfdId mnGroup = ifdExif;

    bool hasNext = false;



    std::unique_ptr<TiffIfdMakernote> tiffIfdMakernote = std::make_unique<TiffIfdMakernote>(tag, group, mnGroup, std::move(mockHeader), hasNext);

};



TEST_F(TiffIfdMakernoteTest_323, DoAddPath_CallsRootAddPath_323) {

    TiffComponent::UniquePtr mockObject = std::make_unique<MockTiffComponent>();

    EXPECT_CALL(*mockRoot, addPath(tag, testing::Ref(tiffPath), mockRoot.get(), testing::_))

        .WillOnce(Return(mockObject.release()));



    tiffIfdMakernote->doAddPath(tag, tiffPath, mockRoot.get(), std::move(mockObject));

}



TEST_F(TiffIfdMakernoteTest_323, DoAddPath_ReturnsNonNullPointer_323) {

    TiffComponent::UniquePtr mockObject = std::make_unique<MockTiffComponent>();

    EXPECT_CALL(*mockRoot, addPath(tag, testing::Ref(tiffPath), mockRoot.get(), testing::_))

        .WillOnce(Return(mockObject.release()));



    TiffComponent* result = tiffIfdMakernote->doAddPath(tag, tiffPath, mockRoot.get(), std::move(mockObject));

    ASSERT_NE(result, nullptr);

}



TEST_F(TiffIfdMakernoteTest_323, DoAddPath_ReturnsNullPointerWhenRootIsNull_323) {

    TiffComponent* pRoot = nullptr;

    TiffComponent::UniquePtr mockObject = std::make_unique<MockTiffComponent>();

    EXPECT_CALL(*mockRoot, addPath(tag, testing::Ref(tiffPath), pRoot, testing::_)).Times(0);



    TiffComponent* result = tiffIfdMakernote->doAddPath(tag, tiffPath, pRoot, std::move(mockObject));

    ASSERT_EQ(result, nullptr);

}



TEST_F(TiffIfdMakernoteTest_323, DoAddPath_ReturnsNullPointerWhenObjectIsNull_323) {

    TiffComponent::UniquePtr mockObject = nullptr;

    EXPECT_CALL(*mockRoot, addPath(tag, testing::Ref(tiffPath), mockRoot.get(), testing::_)).Times(0);



    TiffComponent* result = tiffIfdMakernote->doAddPath(tag, tiffPath, mockRoot.get(), std::move(mockObject));

    ASSERT_EQ(result, nullptr);

}
