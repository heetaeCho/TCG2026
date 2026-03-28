#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "rafimage.hpp"

#include "basicio.hpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;

using ::testing::NiceMock;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(size_t, read, (byte* buf, size_t rcount), (override));

    MOCK_METHOD(void, readOrThrow, (byte* buf, size_t rcount, ErrorCode err), (override));

    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

    MOCK_METHOD(const std::string&, path, (), (const override));

    MOCK_METHOD(bool, isopen, (), (const override));

    MOCK_METHOD(int, error, (), (const override));

    MOCK_METHOD(bool, eof, (), (const override));

};



class RafImageTest : public ::testing::Test {

protected:

    NiceMock<MockBasicIo> mock_io;

    std::unique_ptr<BasicIo> io = std::make_unique<NiceMock<MockBasicIo>>();

    RafImage raf_image{std::move(io), false};

};



TEST_F(RafImageTest, PrintStructure_SuccessfulPrint_220) {

    EXPECT_CALL(mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(mock_io, isopen()).WillRepeatedly(Return(true));



    ON_CALL(mock_io, read(_, _)).WillByDefault([](byte* buf, size_t rcount) -> size_t {

        memset(buf, 0, rcount);

        return rcount;

    });



    std::ostringstream out;

    EXPECT_NO_THROW(raf_image.printStructure(out, kpsBasic, 0));

}



TEST_F(RafImageTest, PrintStructure_OpenFailed_220) {

    EXPECT_CALL(mock_io, open()).WillOnce(Return(-1));



    std::ostringstream out;

    EXPECT_THROW(raf_image.printStructure(out, kpsBasic, 0), Error);

}



TEST_F(RafImageTest, PrintStructure_NotAnRafImage_220) {

    EXPECT_CALL(mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(mock_io, isopen()).WillRepeatedly(Return(true));

    EXPECT_CALL(mock_io, read(_, _)).WillOnce([](byte* buf, size_t rcount) -> size_t {

        memset(buf, 1, rcount); // Not a valid RAF magic number

        return rcount;

    });



    std::ostringstream out;

    EXPECT_THROW(raf_image.printStructure(out, kpsBasic, 0), Error);

}



TEST_F(RafImageTest, PrintStructure_ReadFailed_220) {

    EXPECT_CALL(mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(mock_io, isopen()).WillRepeatedly(Return(true));

    EXPECT_CALL(mock_io, read(_, _)).WillOnce([](byte* buf, size_t rcount) -> size_t {

        memset(buf, 0, rcount);

        return 1; // Short read

    });



    std::ostringstream out;

    EXPECT_THROW(raf_image.printStructure(out, kpsBasic, 0), Error);

}



TEST_F(RafImageTest, PrintStructure_ReadOrThrowFailed_220) {

    EXPECT_CALL(mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(mock_io, isopen()).WillRepeatedly(Return(true));

    EXPECT_CALL(mock_io, readOrThrow(_, _, _)).WillOnce([](byte* buf, size_t rcount, ErrorCode err) -> void {

        throw Error(err);

    });



    std::ostringstream out;

    EXPECT_THROW(raf_image.printStructure(out, kpsBasic, 0), Error);

}



TEST_F(RafImageTest, PrintStructure_PrintRecursive_220) {

    EXPECT_CALL(mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(mock_io, isopen()).WillRepeatedly(Return(true));



    ON_CALL(mock_io, read(_, _)).WillByDefault([](byte* buf, size_t rcount) -> size_t {

        memset(buf, 0, rcount);

        return rcount;

    });



    std::ostringstream out;

    EXPECT_NO_THROW(raf_image.printStructure(out, kpsRecursive, 0));

}



TEST_F(RafImageTest, PrintStructure_PrintBasic_220) {

    EXPECT_CALL(mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(mock_io, isopen()).WillRepeatedly(Return(true));



    ON_CALL(mock_io, read(_, _)).WillByDefault([](byte* buf, size_t rcount) -> size_t {

        memset(buf, 0, rcount);

        return rcount;

    });



    std::ostringstream out;

    EXPECT_NO_THROW(raf_image.printStructure(out, kpsBasic, 0));

}
