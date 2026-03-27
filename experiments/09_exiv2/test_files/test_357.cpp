#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;



class TiffComponentTest : public ::testing::Test {

protected:

    TiffComponent* tiffComponent;



    void SetUp() override {

        tiffComponent = new TiffComponent(0, IfdId::rootIFD);

    }



    void TearDown() override {

        delete tiffComponent;

    }

};



TEST_F(TiffComponentTest_357, Count_ReturnsExpectedValue_357) {

    // Assuming count() returns a non-zero value in normal operation

    EXPECT_NE(tiffComponent->count(), 0);

}



TEST_F(TiffComponentTest_357, Count_BoundaryCondition_NoChildren_357) {

    // Assuming count() returns 0 when there are no children

    TiffComponent* emptyComponent = new TiffComponent(1, IfdId::rootIFD);

    EXPECT_EQ(emptyComponent->count(), 0);

    delete emptyComponent;

}



TEST_F(TiffComponentTest_357, AddChild_ReturnsSelfOnSuccess_357) {

    auto child = std::make_shared<TiffComponent>(2, IfdId::rootIFD);

    EXPECT_EQ(tiffComponent->addChild(child), tiffComponent);

}



TEST_F(TiffComponentTest_357, AddNext_ReturnsSelfOnSuccess_357) {

    auto nextComponent = TiffComponent::UniquePtr(new TiffComponent(2, IfdId::rootIFD));

    EXPECT_EQ(tiffComponent->addNext(std::move(nextComponent)), tiffComponent);

}



TEST_F(TiffComponentTest_357, AddPath_ReturnsSelfOnSuccess_357) {

    TiffPath path;

    auto object = TiffComponent::UniquePtr(new TiffComponent(2, IfdId::rootIFD));

    EXPECT_EQ(tiffComponent->addPath(1, path, tiffComponent, std::move(object)), tiffComponent);

}



TEST_F(TiffComponentTest_357, Accept_VisitorInteraction_357) {

    class MockTiffVisitor : public TiffVisitor {

    public:

        MOCK_METHOD(void, visit, (const TiffComponent&), (override));

    };



    MockTiffVisitor mockVisitor;

    EXPECT_CALL(mockVisitor, visit(::testing::Ref(*tiffComponent)));



    tiffComponent->accept(mockVisitor);

}



TEST_F(TiffComponentTest_357, Clone_ReturnsNonNullPointer_357) {

    auto clonedComponent = tiffComponent->clone();

    EXPECT_NE(clonedComponent.get(), nullptr);

}



TEST_F(TiffComponentTest_357, Write_ReturnsSizeOnSuccess_357) {

    class MockIoWrapper : public IoWrapper {

    public:

        MOCK_METHOD(size_t, write, (const byte*, size_t), (override));

    };



    MockIoWrapper mockIoWrapper;

    EXPECT_CALL(mockIoWrapper, write(_, _)).WillOnce(::testing::Return(10));



    ByteOrder byteOrder = littleEndian;

    size_t offset = 0;

    size_t valueIdx = 0;

    size_t dataIdx = 0;

    size_t imageIdx = 0;



    EXPECT_EQ(tiffComponent->write(mockIoWrapper, byteOrder, offset, valueIdx, dataIdx, imageIdx), 10);

}



TEST_F(TiffComponentTest_357, WriteData_ReturnsSizeOnSuccess_357) {

    class MockIoWrapper : public IoWrapper {

    public:

        MOCK_METHOD(size_t, write, (const byte*, size_t), (override));

    };



    MockIoWrapper mockIoWrapper;

    EXPECT_CALL(mockIoWrapper, write(_, _)).WillOnce(::testing::Return(10));



    ByteOrder byteOrder = littleEndian;

    size_t offset = 0;

    size_t dataIdx = 0;

    size_t imageIdx = 0;



    EXPECT_EQ(tiffComponent->writeData(mockIoWrapper, byteOrder, offset, dataIdx, imageIdx), 10);

}



TEST_F(TiffComponentTest_357, WriteImage_ReturnsSizeOnSuccess_357) {

    class MockIoWrapper : public IoWrapper {

    public:

        MOCK_METHOD(size_t, write, (const byte*, size_t), (override));

    };



    MockIoWrapper mockIoWrapper;

    EXPECT_CALL(mockIoWrapper, write(_, _)).WillOnce(::testing::Return(10));



    ByteOrder byteOrder = littleEndian;



    EXPECT_EQ(tiffComponent->writeImage(mockIoWrapper, byteOrder), 10);

}



TEST_F(TiffComponentTest_357, Size_ReturnsNonNegativeValue_357) {

    EXPECT_GE(tiffComponent->size(), 0);

}



TEST_F(TiffComponentTest_357, SizeData_ReturnsNonNegativeValue_357) {

    EXPECT_GE(tiffComponent->sizeData(), 0);

}



TEST_F(TiffComponentTest_357, SizeImage_ReturnsNonNegativeValue_357) {

    EXPECT_GE(tiffComponent->sizeImage(), 0);

}
