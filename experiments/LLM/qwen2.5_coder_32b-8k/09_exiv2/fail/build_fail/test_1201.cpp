#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/bmffimage.hpp"

#include "exiv2/basicio.hpp"

#include <sstream>



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte * data, size_t wcount), (override));

    MOCK_METHOD(int, putb, (byte data), (override));

    MOCK_METHOD(DataBuf, read, (size_t rcount), (override));

    MOCK_METHOD(size_t, read, (byte * buf, size_t rcount), (override));

    MOCK_METHOD(void, readOrThrow, (byte * buf, size_t rcount, ErrorCode err), (override));

    MOCK_METHOD(int, getb, (), (override));

    MOCK_METHOD(void, transfer, (BasicIo & src), (override));

    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

    MOCK_METHOD(byte *, mmap, (bool isWriteable), (override));

    MOCK_METHOD(int, munmap, (), (override));

    MOCK_METHOD(const size_t, tell, (), (const override));

    MOCK_METHOD(const size_t, size, (), (const override));

    MOCK_METHOD(const bool, isopen, (), (const override));

    MOCK_METHOD(const int, error, (), (const override));

    MOCK_METHOD(const bool, eof, (), (const override));

    MOCK_METHOD(const std::string &, path, (), (const override));

};



class BmffImageTest_1201 : public ::testing::Test {

protected:

    void SetUp() override {

        io = std::make_unique<MockBasicIo>();

        image = new BmffImage(std::move(io), false, 10);

    }



    void TearDown() override {

        delete image;

    }



    std::unique_ptr<MockBasicIo> io;

    BmffImage* image;

};



TEST_F(BmffImageTest_1201, PrintStructure_DefaultOption_1201) {

    std::ostringstream out;

    image->printStructure(out, kpsNone, 0);

    EXPECT_EQ(out.str(), "");

}



TEST_F(BmffImageTest_1201, PrintStructure_IccProfile_NoData_1201) {

    std::ostringstream out;

    image->printStructure(out, kpsIccProfile, 0);

    EXPECT_EQ(out.str(), "");

}



TEST_F(BmffImageTest_1201, PrintStructure_Xmp_EmptyXmpData_1201) {

    std::ostringstream out;

    EXPECT_CALL(*io, size()).WillOnce(Return(0));

    image->printStructure(out, kpsXMP, 0);

    EXPECT_EQ(out.str(), "");

}



TEST_F(BmffImageTest_1201, PrintStructure_Xmp_EncodeError_1201) {

    std::ostringstream out;

    EXPECT_CALL(*io, size()).WillOnce(Return(10));

    EXPECT_THROW(image->printStructure(out, kpsXMP, 0), Error);

}



TEST_F(BmffImageTest_1201, PrintStructure_BasicOption_1201) {

    std::ostringstream out;

    EXPECT_CALL(*io, size()).WillOnce(Return(10));

    EXPECT_CALL(*io, seek(0, BasicIo::beg)).WillOnce(Return(0));

    image->printStructure(out, kpsBasic, 0);

    // We can't predict the exact output here, but we ensure it doesn't crash.

}



TEST_F(BmffImageTest_1201, PrintStructure_RecursiveOption_1201) {

    std::ostringstream out;

    EXPECT_CALL(*io, size()).WillOnce(Return(10));

    EXPECT_CALL(*io, seek(0, BasicIo::beg)).WillOnce(Return(0));

    image->printStructure(out, kpsRecursive, 0);

    // We can't predict the exact output here, but we ensure it doesn't crash.

}



TEST_F(BmffImageTest_1201, PrintStructure_IccProfile_DataPresent_1201) {

    std::ostringstream out;

    image->iccProfile_.alloc(5);

    image->iccProfile_.write_uint8(0, 'A');

    image->iccProfile_.write_uint8(1, 'B');

    image->printStructure(out, kpsIccProfile, 0);

    EXPECT_EQ(out.str(), "AB");

}
