#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/cr2image.hpp"

#include "exiv2/basicio.hpp"

#include "exiv2/error.hpp"



using namespace Exiv2;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte *data, size_t wcount), (override));

    MOCK_METHOD(int, putb, (byte data), (override));

    MOCK_METHOD(DataBuf, read, (size_t rcount), (override));

    MOCK_METHOD(size_t, read, (byte *buf, size_t rcount), (override));

    MOCK_METHOD(void, readOrThrow, (byte *buf, size_t rcount, ErrorCode err), (override));

    MOCK_METHOD(int, getb, (), (override));

    MOCK_METHOD(void, transfer, (BasicIo &src), (override));

    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

    MOCK_METHOD(void, seekOrThrow, (int64_t offset, Position pos, ErrorCode err), (override));

    MOCK_METHOD(byte *, mmap, (bool isWriteable), (override));

    MOCK_METHOD(int, munmap, (), (override));

    MOCK_METHOD(size_t, tell, (), (const, override));

    MOCK_METHOD(size_t, size, (), (const, override));

    MOCK_METHOD(bool, isopen, (), (const, override));

    MOCK_METHOD(int, error, (), (const, override));

    MOCK_METHOD(bool, eof, (), (const, override));

    MOCK_METHOD(const std::string &, path, (), (const, override));

    MOCK_METHOD(void, populateFakeData, (), (override));

};



class Cr2ImageTest : public ::testing::Test {

protected:

    void SetUp() override {

        mock_io = std::make_unique<MockBasicIo>();

        cr2_image = std::make_unique<Cr2Image>(std::move(mock_io), false);

    }



    std::unique_ptr<MockBasicIo> mock_io;

    std::unique_ptr<Cr2Image> cr2_image;

};



TEST_F(Cr2ImageTest_1742, PrintStructure_SuccessfulOpenAndSeek_1742) {

    EXPECT_CALL(*mock_io, open()).WillOnce(::testing::Return(0));

    EXPECT_CALL(*mock_io, seek(0, BasicIo::beg)).WillOnce(::testing::Return(0));



    std::ostringstream out;

    cr2_image->printStructure(out, PrintStructureOption::kpsNone, 0);

}



TEST_F(Cr2ImageTest_1742, PrintStructure_OpenFailed_1742) {

    EXPECT_CALL(*mock_io, open()).WillOnce(::testing::Return(1));



    std::ostringstream out;

    EXPECT_THROW(cr2_image->printStructure(out, PrintStructureOption::kpsNone, 0), Error);

}



TEST_F(Cr2ImageTest_1742, PrintStructure_SeekFailed_1742) {

    EXPECT_CALL(*mock_io, open()).WillOnce(::testing::Return(0));

    EXPECT_CALL(*mock_io, seek(0, BasicIo::beg)).WillOnce(::testing::Return(-1));



    std::ostringstream out;

    EXPECT_THROW(cr2_image->printStructure(out, PrintStructureOption::kpsNone, 0), Error);

}



TEST_F(Cr2ImageTest_1742, PrintStructure_NormalOperation_1742) {

    EXPECT_CALL(*mock_io, open()).WillOnce(::testing::Return(0));

    EXPECT_CALL(*mock_io, seek(0, BasicIo::beg)).WillOnce(::testing::Return(0));



    std::ostringstream out;

    cr2_image->printStructure(out, PrintStructureOption::kpsRecursive, 1);

}



TEST_F(Cr2ImageTest_1742, PrintStructure_DepthBoundaryCondition_1742) {

    EXPECT_CALL(*mock_io, open()).WillOnce(::testing::Return(0));

    EXPECT_CALL(*mock_io, seek(0, BasicIo::beg)).WillOnce(::testing::Return(0));



    std::ostringstream out;

    cr2_image->printStructure(out, PrintStructureOption::kpsNone, 10);

}
