#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/image.hpp"

#include "exiv2/basicio.hpp"

#include "exiv2/error.hpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;

using ::testing::Throw;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(void, readOrThrow, (byte *buf, size_t rcount, ErrorCode err), (override));

};



class ImageTest_1066 : public ::testing::Test {

protected:

    MockBasicIo mock_io;

    std::ostringstream out_stream;

    Image image{ImageType::jpeg, 0, std::make_unique<MockBasicIo>(mock_io)};

};



TEST_F(ImageTest_1066, PrintTiffStructure_BasicOption_Success_1066) {

    EXPECT_CALL(mock_io, readOrThrow(_, 8, ErrorCode::kerCorruptedMetadata))

        .WillOnce([](byte *buf, size_t rcount, ErrorCode err) {

            buf[0] = 'I'; // Little Endian

            buf[4] = 0x12; // Start offset little endian

            buf[5] = 0x34;

        });



    image.printTiffStructure(mock_io, out_stream, kpsBasic, 0);

}



TEST_F(ImageTest_1066, PrintTiffStructure_XmpOption_Success_1066) {

    EXPECT_CALL(mock_io, readOrThrow(_, 8, ErrorCode::kerCorruptedMetadata))

        .WillOnce([](byte *buf, size_t rcount, ErrorCode err) {

            buf[0] = 'M'; // Big Endian

            buf[4] = 0x34; // Start offset big endian

            buf[5] = 0x12;

        });



    image.printTiffStructure(mock_io, out_stream, kpsXMP, 0);

}



TEST_F(ImageTest_1066, PrintTiffStructure_RecursiveOption_Success_1066) {

    EXPECT_CALL(mock_io, readOrThrow(_, 8, ErrorCode::kerCorruptedMetadata))

        .WillOnce([](byte *buf, size_t rcount, ErrorCode err) {

            buf[0] = 'I'; // Little Endian

            buf[4] = 0x56; // Start offset little endian

            buf[5] = 0x78;

        });



    image.printTiffStructure(mock_io, out_stream, kpsRecursive, 0);

}



TEST_F(ImageTest_1066, PrintTiffStructure_IccProfileOption_Success_1066) {

    EXPECT_CALL(mock_io, readOrThrow(_, 8, ErrorCode::kerCorruptedMetadata))

        .WillOnce([](byte *buf, size_t rcount, ErrorCode err) {

            buf[0] = 'M'; // Big Endian

            buf[4] = 0x78; // Start offset big endian

            buf[5] = 0x56;

        });



    image.printTiffStructure(mock_io, out_stream, kpsIccProfile, 0);

}



TEST_F(ImageTest_1066, PrintTiffStructure_OffsetParameter_Success_1066) {

    EXPECT_CALL(mock_io, readOrThrow(_, 8, ErrorCode::kerCorruptedMetadata))

        .WillOnce([](byte *buf, size_t rcount, ErrorCode err) {

            buf[0] = 'I'; // Little Endian

            buf[4] = 0x9A; // Start offset little endian

            buf[5] = 0xBC;

        });



    image.printTiffStructure(mock_io, out_stream, kpsBasic, 0, 10);

}



TEST_F(ImageTest_1066, PrintTiffStructure_CorruptedMetadata_Exception_1066) {

    EXPECT_CALL(mock_io, readOrThrow(_, 8, ErrorCode::kerCorruptedMetadata))

        .WillOnce(Throw(Error(ErrorCode::kerCorruptedMetadata)));



    EXPECT_THROW(image.printTiffStructure(mock_io, out_stream, kpsBasic, 0), Error);

}
