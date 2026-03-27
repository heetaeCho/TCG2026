#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/jp2image.hpp"

#include "exiv2/basicio.hpp"



using namespace Exiv2;

using namespace testing;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte *data, size_t wcount), (override));

    MOCK_METHOD(size_t, read, (byte *buf, size_t rcount), (override));

    MOCK_METHOD(bool, isopen, (), (const, override));

    MOCK_METHOD(const std::string &, path, (), (const, override));

};



class Jp2ImageTest : public Test {

protected:

    NiceMock<MockBasicIo> mock_io;

    BasicIo::UniquePtr io_ptr;



    void SetUp() override {

        io_ptr.reset(&mock_io);

    }



    void TearDown() override {

        io_ptr.release();

    }

};



TEST_F(Jp2ImageTest_2153, Constructor_CreatesJpeg2000ImageInMemory_2153) {

    EXPECT_CALL(mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(mock_io, write(_, Jp2Blank.size())).WillOnce(Return(Jp2Blank.size()));



    Jp2Image jp2_image(std::move(io_ptr), true);

}



TEST_F(Jp2ImageTest_2153, Constructor_DoesNotWriteWhenOpenFails_2153) {

    EXPECT_CALL(mock_io, open()).WillOnce(Return(-1));

    EXPECT_CALL(mock_io, write(_, _)).Times(0);



    Jp2Image jp2_image(std::move(io_ptr), true);

}



TEST_F(Jp2ImageTest_2153, Constructor_DoesNotWriteWhenWriteFails_2153) {

    EXPECT_CALL(mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(mock_io, write(_, Jp2Blank.size())).WillOnce(Return(0));



    Jp2Image jp2_image(std::move(io_ptr), true);

}



TEST_F(Jp2ImageTest_2153, Constructor_DoesNotOpenWhenCreateIsFalse_2153) {

    EXPECT_CALL(mock_io, open()).Times(0);

    EXPECT_CALL(mock_io, write(_, _)).Times(0);



    Jp2Image jp2_image(std::move(io_ptr), false);

}



TEST_F(Jp2ImageTest_2153, ReadMetadata_CallsBaseReadMetadata_2153) {

    EXPECT_CALL(mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(mock_io, write(_, Jp2Blank.size())).WillOnce(Return(Jp2Blank.size()));



    Jp2Image jp2_image(std::move(io_ptr), true);

    EXPECT_NO_THROW(jp2_image.readMetadata());

}



TEST_F(Jp2ImageTest_2153, WriteMetadata_CallsBaseWriteMetadata_2153) {

    EXPECT_CALL(mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(mock_io, write(_, Jp2Blank.size())).WillOnce(Return(Jp2Blank.size()));



    Jp2Image jp2_image(std::move(io_ptr), true);

    EXPECT_NO_THROW(jp2_image.writeMetadata());

}



TEST_F(Jp2ImageTest_2153, PrintStructure_CallsBasePrintStructure_2153) {

    EXPECT_CALL(mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(mock_io, write(_, Jp2Blank.size())).WillOnce(Return(Jp2Blank.size()));



    Jp2Image jp2_image(std::move(io_ptr), true);

    std::ostringstream oss;

    EXPECT_NO_THROW(jp2_image.printStructure(oss, PrintStructureOption(), 0));

}



TEST_F(Jp2ImageTest_2153, SetComment_CallsBaseSetComment_2153) {

    EXPECT_CALL(mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(mock_io, write(_, Jp2Blank.size())).WillOnce(Return(Jp2Blank.size()));



    Jp2Image jp2_image(std::move(io_ptr), true);

    EXPECT_NO_THROW(jp2_image.setComment("test comment"));

}



TEST_F(Jp2ImageTest_2153, MimeType_ReturnsJpeg2000MimeType_2153) {

    EXPECT_CALL(mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(mock_io, write(_, Jp2Blank.size())).WillOnce(Return(Jp2Blank.size()));



    Jp2Image jp2_image(std::move(io_ptr), true);

    EXPECT_EQ(jp2_image.mimeType(), "image/jp2");

}
