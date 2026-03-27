#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/jpgimage.hpp"

#include "exiv2/basicio.hpp"



using namespace Exiv2;

using ::testing::NiceMock;

using ::testing::Return;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte* data, size_t wcount), (override));

    MOCK_METHOD(size_t, write, (BasicIo & src), (override));

    MOCK_METHOD(int, putb, (byte data), (override));

    MOCK_METHOD(DataBuf, read, (size_t rcount), (override));

    MOCK_METHOD(size_t, read, (byte* buf, size_t rcount), (override));

    MOCK_METHOD(void, readOrThrow, (byte* buf, size_t rcount, ErrorCode err), (override));

    MOCK_METHOD(int, getb, (), (override));

    MOCK_METHOD(void, transfer, (BasicIo & src), (override));

    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

    MOCK_METHOD(void, seekOrThrow, (int64_t offset, Position pos, ErrorCode err), (override));

    MOCK_METHOD(byte*, mmap, (bool isWriteable), (override));

    MOCK_METHOD(int, munmap, (), (override));

    MOCK_METHOD(const size_t, tell, (), (const, override));

    MOCK_METHOD(const size_t, size, (), (const, override));

    MOCK_METHOD(const bool, isopen, (), (const, override));

    MOCK_METHOD(const int, error, (), (const, override));

    MOCK_METHOD(const bool, eof, (), (const, override));

    MOCK_METHOD(const std::string&, path, (), (const, override));

};



class ExvImageTest_1227 : public ::testing::Test {

protected:

    NiceMock<MockBasicIo> mock_io;

    std::unique_ptr<ExvImage> exv_image;



    void SetUp() override {

        exv_image = std::make_unique<ExvImage>(std::make_unique<MockBasicIo>(), false);

    }

};



TEST_F(ExvImageTest_1227, isThisType_AdvanceTrue_ReturnsFalse_1227) {

    EXPECT_CALL(mock_io, isopen()).WillRepeatedly(Return(true));

    EXPECT_CALL(mock_io, read(::testing::_, ::testing::_)).WillOnce(Return(DataBuf()));



    bool result = exv_image->isThisType(mock_io, true);

    EXPECT_FALSE(result);

}



TEST_F(ExvImageTest_1227, isThisType_AdvanceFalse_ReturnsTrue_1227) {

    EXPECT_CALL(mock_io, isopen()).WillRepeatedly(Return(true));

    EXPECT_CALL(mock_io, read(::testing::_, ::testing::_)).WillOnce(Return(DataBuf("EXV", 3)));



    bool result = exv_image->isThisType(mock_io, false);

    EXPECT_TRUE(result);

}



TEST_F(ExvImageTest_1227, isThisType_IoNotOpen_ReturnsFalse_1227) {

    EXPECT_CALL(mock_io, isopen()).WillRepeatedly(Return(false));



    bool result = exv_image->isThisType(mock_io, false);

    EXPECT_FALSE(result);

}



TEST_F(ExvImageTest_1227, isThisType_ReadThrows_ReturnsFalse_1227) {

    EXPECT_CALL(mock_io, isopen()).WillRepeatedly(Return(true));

    EXPECT_CALL(mock_io, read(::testing::_, ::testing::_)).WillOnce(testing::Throw(std::runtime_error("Read error")));



    bool result = exv_image->isThisType(mock_io, false);

    EXPECT_FALSE(result);

}
