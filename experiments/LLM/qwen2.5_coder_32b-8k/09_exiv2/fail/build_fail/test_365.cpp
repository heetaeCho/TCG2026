#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"

#include "error.hpp"

#include "tiffimage_int.hpp"



using namespace Exiv2::Internal;

using namespace testing;



class MockIoWrapper : public IoWrapper {

public:

    MOCK_METHOD(size_t, write, (const byte* pData, size_t wcount), (override));

    MOCK_METHOD(int, putb, (byte data), (override));

    MOCK_METHOD(void, setTarget, (int id, size_t target), (override));



    MockIoWrapper(BasicIo& io, const byte* pHeader, size_t size, OffsetWriter* pow)

        : IoWrapper(io, pHeader, size, pow) {}

};



class TiffDirectoryTest_365 : public Test {

protected:

    std::unique_ptr<MockIoWrapper> mockIoWrapper;

    std::vector<std::unique_ptr<TiffComponent>> components;

    std::unique_ptr<TiffDirectory> tiffDir;



    void SetUp() override {

        BasicIo dummyIo; // Placeholder for actual IoWrapper dependency

        OffsetWriter* offsetWriter = nullptr; // Placeholder for actual OffsetWriter dependency

        mockIoWrapper = std::make_unique<MockIoWrapper>(dummyIo, nullptr, 0, offsetWriter);

        tiffDir = std::make_unique<TiffDirectory>(1, IfdId::ifd0Id, false);



        components.push_back(std::make_unique<TiffComponent>(2, IfdId::ifd0Id));

        components.push_back(std::make_unique<TiffComponent>(3, IfdId::ifd0Id));



        for (auto& component : components) {

            tiffDir->addChild(component->shared_from_this());

        }

    }



    void TearDown() override {

        mockIoWrapper.reset();

        tiffDir.reset();

        components.clear();

    }

};



TEST_F(TiffDirectoryTest_365, NormalOperation_WriteReturnsCorrectSize_365) {

    size_t offset = 0;

    size_t valueIdx = 0;

    size_t dataIdx = 0;

    size_t imageIdx = std::string::npos;



    EXPECT_CALL(*mockIoWrapper, write(_, _)).WillRepeatedly(Return(2));

    EXPECT_CALL(*mockIoWrapper, putb(_)).WillRepeatedly(Return(1));



    size_t result = tiffDir->doWrite(*mockIoWrapper, ByteOrder::littleEndian, offset, valueIdx, dataIdx, imageIdx);

    EXPECT_EQ(result, 36); // Expected size based on the components and their sizes

}



TEST_F(TiffDirectoryTest_365, BoundaryCondition_EmptyComponents_ReturnsZeroSize_365) {

    size_t offset = 0;

    size_t valueIdx = 0;

    size_t dataIdx = 0;

    size_t imageIdx = std::string::npos;



    tiffDir.reset();

    tiffDir = std::make_unique<TiffDirectory>(1, IfdId::ifd0Id, false);



    EXPECT_CALL(*mockIoWrapper, write(_, _)).Times(0);

    EXPECT_CALL(*mockIoWrapper, putb(_)).Times(0);



    size_t result = tiffDir->doWrite(*mockIoWrapper, ByteOrder::littleEndian, offset, valueIdx, dataIdx, imageIdx);

    EXPECT_EQ(result, 0); // No components to write

}



TEST_F(TiffDirectoryTest_365, ExceptionalCase_TooManyEntries_ThrowsError_365) {

    size_t offset = 0;

    size_t valueIdx = 0;

    size_t dataIdx = 0;

    size_t imageIdx = std::string::npos;



    // Adding more components to exceed the limit

    for (size_t i = 0; i < 0xffff - components.size(); ++i) {

        components.push_back(std::make_unique<TiffComponent>(static_cast<uint16_t>(4 + i), IfdId::ifd0Id));

        tiffDir->addChild(components.back()->shared_from_this());

    }



    EXPECT_THROW(tiffDir->doWrite(*mockIoWrapper, ByteOrder::littleEndian, offset, valueIdx, dataIdx, imageIdx), Error);

}



TEST_F(TiffDirectoryTest_365, Verification_Ifd3Group_SetsCr2RawIfdOffset_365) {

    size_t offset = 0x100;

    size_t valueIdx = 0;

    size_t dataIdx = 0;

    size_t imageIdx = std::string::npos;



    tiffDir.reset();

    tiffDir = std::make_unique<TiffDirectory>(1, IfdId::ifd3Id, false);



    EXPECT_CALL(*mockIoWrapper, setTarget(OffsetWriter::cr2RawIfdOffset, offset));



    tiffDir->doWrite(*mockIoWrapper, ByteOrder::littleEndian, offset, valueIdx, dataIdx, imageIdx);

}



TEST_F(TiffDirectoryTest_365, Verification_ComponentAlignment_WritesCorrectlyAlignedData_365) {

    size_t offset = 0;

    size_t valueIdx = 0;

    size_t dataIdx = 0;

    size_t imageIdx = std::string::npos;



    EXPECT_CALL(*mockIoWrapper, write(_, _)).WillRepeatedly(Return(2));

    EXPECT_CALL(*mockIoWrapper, putb(_)).WillOnce(Return(1));



    tiffDir->doWrite(*mockIoWrapper, ByteOrder::littleEndian, offset, valueIdx, dataIdx, imageIdx);

}
