#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "asfvideo.hpp"

#include "basicio.hpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;

using ::testing::Throw;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(void, readOrThrow, (byte* buf, size_t rcount, ErrorCode err), (override));

    MOCK_METHOD(size_t, tell, (), (const, override));

    MOCK_METHOD(size_t, size, (), (const, override));

};



class AsfVideoHeaderReaderTest : public ::testing::Test {

protected:

    std::unique_ptr<MockBasicIo> mockIo;

    HeaderReader* headerReader;



    void SetUp() override {

        mockIo = std::make_unique<MockBasicIo>();

        headerReader = new HeaderReader(std::move(mockIo));

    }



    void TearDown() override {

        delete headerReader;

    }

};



TEST_F(AsfVideoHeaderReaderTest, NormalOperation_2199) {

    constexpr size_t guidSize = GUID;

    constexpr size_t qwordSize = QWORD;

    constexpr uint64_t expectedSize = guidSize + qwordSize * 2;



    EXPECT_CALL(*mockIo, tell()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, size()).WillOnce(Return(expectedSize));



    byte buffer[guidSize];

    EXPECT_CALL(*mockIo, readOrThrow(buffer, guidSize, ErrorCode::kerCorruptedMetadata));



    headerReader = new HeaderReader(std::move(mockIo));



    EXPECT_EQ(headerReader->getSize(), expectedSize);

    EXPECT_EQ(headerReader->getRemainingSize(), qwordSize);

}



TEST_F(AsfVideoHeaderReaderTest, BoundaryCondition_SizeTooSmall_2199) {

    EXPECT_CALL(*mockIo, tell()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, size()).WillOnce(Return(GUID + QWORD - 1));



    headerReader = new HeaderReader(std::move(mockIo));



    EXPECT_EQ(headerReader->getSize(), 0);

    EXPECT_EQ(headerReader->getRemainingSize(), 0);

}



TEST_F(AsfVideoHeaderReaderTest, BoundaryCondition_SizeJustRight_2199) {

    constexpr size_t guidSize = GUID;

    constexpr size_t qwordSize = QWORD;

    constexpr uint64_t expectedSize = guidSize + qwordSize;



    EXPECT_CALL(*mockIo, tell()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, size()).WillOnce(Return(expectedSize));



    byte buffer[guidSize];

    EXPECT_CALL(*mockIo, readOrThrow(buffer, guidSize, ErrorCode::kerCorruptedMetadata));



    headerReader = new HeaderReader(std::move(mockIo));



    EXPECT_EQ(headerReader->getSize(), expectedSize);

    EXPECT_EQ(headerReader->getRemainingSize(), 0);

}



TEST_F(AsfVideoHeaderReaderTest, ExceptionalCase_ReadOrThrowFails_2199) {

    constexpr size_t guidSize = GUID;



    EXPECT_CALL(*mockIo, tell()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, size()).WillOnce(Return(guidSize + QWORD));



    byte buffer[guidSize];

    EXPECT_CALL(*mockIo, readOrThrow(buffer, guidSize, ErrorCode::kerCorruptedMetadata))

        .WillOnce(Throw(std::runtime_error("Failed to read")));



    EXPECT_THROW(headerReader = new HeaderReader(std::move(mockIo)), std::runtime_error);

}
