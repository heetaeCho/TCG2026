#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"

#include "exiv2/error.hpp"



using namespace Exiv2::Internal;

using namespace testing;



class MockTiffComponent : public TiffComponent {

public:

    MOCK_METHOD(size_t, writeImage, (IoWrapper& ioWrapper, ByteOrder byteOrder), (const, override));

};



class MockIoWrapper : public IoWrapper {

public:

    MockIoWrapper(BasicIo &io, const byte *pHeader, size_t size, OffsetWriter *pow)

        : IoWrapper(io, pHeader, size, pow) {}



    MOCK_METHOD(size_t, write, (const byte* pData, size_t wcount), (override));

    MOCK_METHOD(int, putb, (byte data), (override));

    MOCK_METHOD(void, setTarget, (int id, size_t target), (override));

};



class TiffDirectoryTest_383 : public Test {

protected:

    MockIoWrapper mockIoWrapper;

    NiceMock<MockTiffComponent> mockComponent1, mockComponent2, mockSubIfd, mockNextDirectory;



    TiffDirectory directory{0x014a, IfdId::IFD0, true};



    void SetUp() override {

        // Initialize components with unique tags

        ON_CALL(mockComponent1, tag()).WillByDefault(Return(0x0102));

        ON_CALL(mockComponent2, tag()).WillByDefault(Return(0x0103));

        ON_CALL(mockSubIfd, tag()).WillByDefault(Return(0x014a));



        // Add components to directory

        directory.addChild(std::make_shared<MockTiffComponent>(mockComponent1));

        directory.addChild(std::make_shared<MockTiffComponent>(mockComponent2));

        directory.addPath(0x014a, TiffPath{}, nullptr, std::make_unique<MockTiffComponent>(mockSubIfd));



        // Set next directory

        directory.pNext_ = std::make_unique<MockTiffComponent>(mockNextDirectory);

    }

};



TEST_F(TiffDirectoryTest_383, NormalOperation_WriteImage_ReturnsTotalLength_383) {

    EXPECT_CALL(mockComponent1, writeImage(_, _)).WillOnce(Return(10));

    EXPECT_CALL(mockComponent2, writeImage(_, _)).WillOnce(Return(20));

    EXPECT_CALL(mockSubIfd, writeImage(_, _)).WillOnce(Return(30));

    EXPECT_CALL(mockNextDirectory, writeImage(_, _)).WillOnce(Return(40));



    size_t result = directory.doWriteImage(mockIoWrapper, ByteOrder::little);

    EXPECT_EQ(result, 10 + 20 + 30 + 40);

}



TEST_F(TiffDirectoryTest_383, NoComponents_WriteImage_ReturnsZero_383) {

    TiffDirectory emptyDirectory{0x014a, IfdId::IFD0, false};

    size_t result = emptyDirectory.doWriteImage(mockIoWrapper, ByteOrder::little);

    EXPECT_EQ(result, 0);

}



TEST_F(TiffDirectoryTest_383, SingleComponent_WriteImage_ReturnsLength_383) {

    TiffDirectory singleComponentDirectory{0x014a, IfdId::IFD0, false};

    singleComponentDirectory.addChild(std::make_shared<MockTiffComponent>(mockComponent1));

    EXPECT_CALL(mockComponent1, writeImage(_, _)).WillOnce(Return(50));



    size_t result = singleComponentDirectory.doWriteImage(mockIoWrapper, ByteOrder::little);

    EXPECT_EQ(result, 50);

}



TEST_F(TiffDirectoryTest_383, MultipleSubIfds_WriteImage_LogsWarningAndUsesFirstSubIfd_383) {

    MockTiffComponent mockSubIfd2;

    ON_CALL(mockSubIfd2, tag()).WillByDefault(Return(0x014a));

    directory.addPath(0x014a, TiffPath{}, nullptr, std::make_unique<MockTiffComponent>(mockSubIfd2));



    EXPECT_CALL(mockComponent1, writeImage(_, _)).WillOnce(Return(10));

    EXPECT_CALL(mockComponent2, writeImage(_, _)).WillOnce(Return(20));

    EXPECT_CALL(mockSubIfd, writeImage(_, _)).WillOnce(Return(30));

    EXPECT_CALL(mockNextDirectory, writeImage(_, _)).WillOnce(Return(40));



    testing::internal::CaptureStderr();

    size_t result = directory.doWriteImage(mockIoWrapper, ByteOrder::little);

    std::string output = testing::internal::GetCapturedStderr();



    EXPECT_EQ(result, 10 + 20 + 30 + 40);

    EXPECT_TRUE(output.find("Multiple sub-IFD image data tags found") != std::string::npos);

}



TEST_F(TiffDirectoryTest_383, NoNextDirectory_WriteImage_ReturnsLengthWithoutNext_383) {

    directory.pNext_.reset();

    EXPECT_CALL(mockComponent1, writeImage(_, _)).WillOnce(Return(10));

    EXPECT_CALL(mockComponent2, writeImage(_, _)).WillOnce(Return(20));

    EXPECT_CALL(mockSubIfd, writeImage(_, _)).WillOnce(Return(30));



    size_t result = directory.doWriteImage(mockIoWrapper, ByteOrder::little);

    EXPECT_EQ(result, 10 + 20 + 30);

}
