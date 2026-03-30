#include <gtest/gtest.h>

#include "tiffcomposite_int.hpp"

#include <gmock/gmock.h>



using namespace Exiv2::Internal;

using ::testing::_;



class TiffComponentTest_404 : public ::testing::Test {

protected:

    TiffComponent* tiffComponent;



    void SetUp() override {

        tiffComponent = new TiffComponent(1, IfdId::rootIFD);

    }



    void TearDown() override {

        delete tiffComponent;

    }

};



TEST_F(TiffComponentTest_404, SizeImage_ReturnsCorrectSize_404) {

    // Assuming sizeImage returns a non-zero value

    EXPECT_GT(tiffComponent->sizeImage(), 0);

}



TEST_F(TiffComponentTest_404, AddPath_ReturnsNonNullPointer_404) {

    TiffPath tiffPath;

    auto object = std::make_unique<TiffComponent>(2, IfdId::rootIFD);

    EXPECT_NE(tiffComponent->addPath(2, tiffPath, tiffComponent, std::move(object)), nullptr);

}



TEST_F(TiffComponentTest_404, AddChild_ReturnsNonNullPointer_404) {

    auto child = std::make_shared<TiffComponent>(3, IfdId::rootIFD);

    EXPECT_NE(tiffComponent->addChild(child), nullptr);

}



TEST_F(TiffComponentTest_404, AddNext_ReturnsNonNullPointer_404) {

    auto next = std::make_unique<TiffComponent>(4, IfdId::rootIFD);

    EXPECT_NE(tiffComponent->addNext(std::move(next)), nullptr);

}



TEST_F(TiffComponentTest_404, Accept_DoesNotThrow_404) {

    class MockTiffVisitor : public TiffVisitor {

    public:

        MOCK_METHOD(void, visit, (TiffComponent&), (override));

    };



    MockTiffVisitor mockVisitor;

    EXPECT_CALL(mockVisitor, visit(::testing::Ref(*tiffComponent)));



    EXPECT_NO_THROW(tiffComponent->accept(mockVisitor));

}



TEST_F(TiffComponentTest_404, Write_ReturnsNonZeroSize_404) {

    class MockIoWrapper : public IoWrapper {

    public:

        MOCK_METHOD(size_t, write, (const byte*, size_t), (override));

    };



    MockIoWrapper mockIoWrapper;

    ByteOrder byteOrder = littleEndian;

    size_t offset = 0, valueIdx = 0, dataIdx = 0, imageIdx = 0;



    EXPECT_CALL(mockIoWrapper, write(_, _)).WillOnce(::testing::Return(1));



    EXPECT_GT(tiffComponent->write(mockIoWrapper, byteOrder, offset, valueIdx, dataIdx, imageIdx), 0);

}



TEST_F(TiffComponentTest_404, WriteData_ReturnsNonZeroSize_404) {

    class MockIoWrapper : public IoWrapper {

    public:

        MOCK_METHOD(size_t, write, (const byte*, size_t), (override));

    };



    MockIoWrapper mockIoWrapper;

    ByteOrder byteOrder = littleEndian;

    size_t offset = 0, dataIdx = 0, imageIdx = 0;



    EXPECT_CALL(mockIoWrapper, write(_, _)).WillOnce(::testing::Return(1));



    EXPECT_GT(tiffComponent->writeData(mockIoWrapper, byteOrder, offset, dataIdx, imageIdx), 0);

}



TEST_F(TiffComponentTest_404, WriteImage_ReturnsNonZeroSize_404) {

    class MockIoWrapper : public IoWrapper {

    public:

        MOCK_METHOD(size_t, write, (const byte*, size_t), (override));

    };



    MockIoWrapper mockIoWrapper;

    ByteOrder byteOrder = littleEndian;



    EXPECT_CALL(mockIoWrapper, write(_, _)).WillOnce(::testing::Return(1));



    EXPECT_GT(tiffComponent->writeImage(mockIoWrapper, byteOrder), 0);

}



TEST_F(TiffComponentTest_404, Size_ReturnsNonZeroSize_404) {

    EXPECT_GT(tiffComponent->size(), 0);

}



TEST_F(TiffComponentTest_404, Count_ReturnsNonNegativeCount_404) {

    EXPECT_GE(tiffComponent->count(), 0);

}



TEST_F(TiffComponentTest_404, SizeData_ReturnsNonZeroSize_404) {

    EXPECT_GT(tiffComponent->sizeData(), 0);

}
