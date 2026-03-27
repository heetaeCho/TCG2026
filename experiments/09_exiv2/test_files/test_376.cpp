#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::NiceMock;



class MockIoWrapper : public IoWrapper {

public:

    MockIoWrapper(BasicIo &io, const byte *pHeader, size_t size, OffsetWriter *pow)

        : IoWrapper(io, pHeader, size, pow) {}



    MOCK_METHOD(size_t, write, (const byte *pData, size_t wcount), (override));

    MOCK_METHOD(int, putb, (byte data), (override));

    MOCK_METHOD(void, setTarget, (int id, size_t target), (override));

};



class TiffDirectoryTest_376 : public ::testing::Test {

protected:

    NiceMock<MockIoWrapper> mockIoWrapper;

    ByteOrder byteOrder = bigEndian;  // or littleEndian as needed

    size_t offset = 0;

    size_t dataIdx = 0;

    size_t imageIdx = 0;



    TiffDirectoryTest_376() : mockIoWrapper(*reinterpret_cast<BasicIo*>(nullptr), nullptr, 0, nullptr) {}



    void addComponent(TiffComponent* component) {

        directory.components_.push_back(std::unique_ptr<TiffComponent>(component));

    }



    TiffDirectory directory{0, ifdExif, false};

};



TEST_F(TiffDirectoryTest_376, NoComponents_ReturnsZeroLength_376) {

    size_t len = directory.doWriteData(mockIoWrapper, byteOrder, offset, dataIdx, imageIdx);

    EXPECT_EQ(len, 0);

}



TEST_F(TiffDirectoryTest_376, SingleComponent_WriteDataCalledOnce_376) {

    auto mockComponent = std::make_unique<NiceMock<TiffComponent>>(0, ifdExif);

    size_t componentLength = 10;

    EXPECT_CALL(*mockComponent, writeData(_, _, _, _, _)).WillOnce(testing::Return(componentLength));



    addComponent(mockComponent.release());



    size_t len = directory.doWriteData(mockIoWrapper, byteOrder, offset, dataIdx, imageIdx);

    EXPECT_EQ(len, componentLength);

}



TEST_F(TiffDirectoryTest_376, MultipleComponents_WriteDataCalledForEach_376) {

    auto mockComponent1 = std::make_unique<NiceMock<TiffComponent>>(0, ifdExif);

    auto mockComponent2 = std::make_unique<NiceMock<TiffComponent>>(1, ifdExif);

    size_t componentLength1 = 10;

    size_t componentLength2 = 20;



    EXPECT_CALL(*mockComponent1, writeData(_, _, _, _, _)).WillOnce(testing::Return(componentLength1));

    EXPECT_CALL(*mockComponent2, writeData(_, _, _, _, _)).WillOnce(testing::Return(componentLength2));



    addComponent(mockComponent1.release());

    addComponent(mockComponent2.release());



    size_t len = directory.doWriteData(mockIoWrapper, byteOrder, offset, dataIdx, imageIdx);

    EXPECT_EQ(len, componentLength1 + componentLength2);

}



TEST_F(TiffDirectoryTest_376, ComponentsIncreaseOffset_Correctly_376) {

    auto mockComponent1 = std::make_unique<NiceMock<TiffComponent>>(0, ifdExif);

    auto mockComponent2 = std::make_unique<NiceMock<TiffComponent>>(1, ifdExif);

    size_t componentLength1 = 5;

    size_t componentLength2 = 7;



    EXPECT_CALL(*mockComponent1, writeData(_, _, offset, dataIdx + 0, _)).WillOnce(testing::Return(componentLength1));

    EXPECT_CALL(*mockComponent2, writeData(_, _, offset + componentLength1, dataIdx + componentLength1, _))

        .WillOnce(testing::Return(componentLength2));



    addComponent(mockComponent1.release());

    addComponent(mockComponent2.release());



    directory.doWriteData(mockIoWrapper, byteOrder, offset, dataIdx, imageIdx);

}



TEST_F(TiffDirectoryTest_376, ExceptionalCase_ComponentThrowsException_376) {

    auto mockComponent = std::make_unique<NiceMock<TiffComponent>>(0, ifdExif);



    EXPECT_CALL(*mockComponent, writeData(_, _, _, _, _)).WillOnce(testing::Throw(std::runtime_error("Test exception")));



    addComponent(mockComponent.release());



    EXPECT_THROW(directory.doWriteData(mockIoWrapper, byteOrder, offset, dataIdx, imageIdx), std::runtime_error);

}
