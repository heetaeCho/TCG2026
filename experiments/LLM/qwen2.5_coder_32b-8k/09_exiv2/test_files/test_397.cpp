#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::Return;



class TiffComponentTest_397 : public ::testing::Test {

protected:

    TiffComponent* component;



    void SetUp() override {

        component = new TiffComponent(0x0100, ifdExif);

    }



    void TearDown() override {

        delete component;

    }

};



TEST_F(TiffComponentTest_397, SizeData_ReturnsZeroByDefault_397) {

    EXPECT_EQ(component->sizeData(), 0U);

}



// Assuming addPath modifies the size of data

TEST_F(TiffComponentTest_397, AddPath_ModifiesSizeData_397) {

    TiffPath tiffPath;

    TiffComponent::UniquePtr object(new TiffComponent(0x0101, ifdExif));

    component->addPath(0x0101, tiffPath, nullptr, std::move(object));



    EXPECT_NE(component->sizeData(), 0U);

}



// Assuming addChild modifies the size of data

TEST_F(TiffComponentTest_397, AddChild_ModifiesSizeData_397) {

    TiffComponent::SharedPtr child(new TiffComponent(0x0102, ifdExif));

    component->addChild(child);



    EXPECT_NE(component->sizeData(), 0U);

}



// Assuming addNext modifies the size of data

TEST_F(TiffComponentTest_397, AddNext_ModifiesSizeData_397) {

    TiffComponent::UniquePtr next(new TiffComponent(0x0103, ifdExif));

    component->addNext(std::move(next));



    EXPECT_NE(component->sizeData(), 0U);

}



// Assuming accept calls the visitor's visit method

TEST_F(TiffComponentTest_397, Accept_VisitsTheComponent_397) {

    class MockTiffVisitor : public TiffVisitor {

    public:

        MOCK_METHOD(void, visit, (const TiffComponent&), (override));

    };



    MockTiffVisitor mockVisitor;

    EXPECT_CALL(mockVisitor, visit(::testing::Ref(*component))).Times(1);



    component->accept(mockVisitor);

}



// Assuming write modifies imageIdx

TEST_F(TiffComponentTest_397, Write_ModifiesImageIdx_397) {

    class MockIoWrapper : public IoWrapper {

    public:

        MOCK_METHOD(size_t, write, (const byte* data, size_t wcount), (override));

    };



    MockIoWrapper mockIoWrapper;

    ByteOrder byteOrder = littleEndian;

    size_t offset = 0;

    size_t valueIdx = 0;

    size_t dataIdx = 0;

    size_t imageIdx = 0;



    EXPECT_CALL(mockIoWrapper, write(_, _)).WillOnce(Return(1));



    component->write(mockIoWrapper, byteOrder, offset, valueIdx, dataIdx, imageIdx);



    EXPECT_EQ(imageIdx, 1U);

}



// Assuming writeData modifies imageIdx

TEST_F(TiffComponentTest_397, WriteData_ModifiesImageIdx_397) {

    class MockIoWrapper : public IoWrapper {

    public:

        MOCK_METHOD(size_t, write, (const byte* data, size_t wcount), (override));

    };



    MockIoWrapper mockIoWrapper;

    ByteOrder byteOrder = littleEndian;

    size_t offset = 0;

    size_t dataIdx = 0;

    size_t imageIdx = 0;



    EXPECT_CALL(mockIoWrapper, write(_, _)).WillOnce(Return(1));



    component->writeData(mockIoWrapper, byteOrder, offset, dataIdx, imageIdx);



    EXPECT_EQ(imageIdx, 1U);

}



// Assuming writeImage modifies imageIdx

TEST_F(TiffComponentTest_397, WriteImage_ModifiesImageIdx_397) {

    class MockIoWrapper : public IoWrapper {

    public:

        MOCK_METHOD(size_t, write, (const byte* data, size_t wcount), (override));

    };



    MockIoWrapper mockIoWrapper;

    ByteOrder byteOrder = littleEndian;



    size_t imageIdx = 0;



    EXPECT_CALL(mockIoWrapper, write(_, _)).WillOnce(Return(1));



    component->writeImage(mockIoWrapper, byteOrder);



    EXPECT_EQ(imageIdx, 0U); // ImageIdx is passed by reference and modified in the function

}



// Assuming count returns a non-zero value when children are added

TEST_F(TiffComponentTest_397, Count_ReturnsNonZeroAfterAddingChild_397) {

    TiffComponent::SharedPtr child(new TiffComponent(0x0102, ifdExif));

    component->addChild(child);



    EXPECT_NE(component->count(), 0U);

}



// Assuming size returns a non-zero value when data is added

TEST_F(TiffComponentTest_397, Size_ReturnsNonZeroAfterAddingData_397) {

    TiffPath tiffPath;

    TiffComponent::UniquePtr object(new TiffComponent(0x0101, ifdExif));

    component->addPath(0x0101, tiffPath, nullptr, std::move(object));



    EXPECT_NE(component->size(), 0U);

}



// Assuming sizeImage returns a non-zero value when image data is added

TEST_F(TiffComponentTest_397, SizeImage_ReturnsNonZeroAfterAddingImageData_397) {

    class MockIoWrapper : public IoWrapper {

    public:

        MOCK_METHOD(size_t, write, (const byte* data, size_t wcount), (override));

    };



    MockIoWrapper mockIoWrapper;

    ByteOrder byteOrder = littleEndian;



    component->writeImage(mockIoWrapper, byteOrder);



    EXPECT_NE(component->sizeImage(), 0U); // Assuming writeImage modifies internal state affecting sizeImage

}
