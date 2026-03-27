#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "jpgimage.hpp"

#include "image.hpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::NiceMock;

using ::testing::Return;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(void, read, (byte* data, size_t count), (override));

    MOCK_METHOD(void, write, (const byte* data, size_t count), (override));

    MOCK_METHOD(size_t, tell, (), (override));

    MOCK_METHOD(void, seek, (size_t offset), (override));

    MOCK_METHOD(bool, good, (), (override));

};



class JpegBaseTest : public ::testing::Test {

protected:

    NiceMock<MockBasicIo> mock_io;

    std::unique_ptr<BasicIo> io_ptr = std::make_unique<NiceMock<MockBasicIo>>();

    const byte initData[] = {0xFF, 0xD8, 0xFF, 0xE0};

    size_t dataSize = sizeof(initData);

};



TEST_F(JpegBaseTest, ConstructorDoesNotThrowOnValidInput_2176) {

    EXPECT_NO_THROW(JpegBase image(mdJpegType, std::move(io_ptr), true, initData, dataSize));

}



TEST_F(JpegBaseTest, ReadMetadataCallsReadOnIo_2176) {

    JpegBase image(mdJpegType, std::make_unique<MockBasicIo>(), false, initData, dataSize);

    EXPECT_CALL(mock_io, read(_, _)).Times(1);



    image.readMetadata();

}



TEST_F(JpegBaseTest, WriteMetadataCallsWriteOnIo_2176) {

    JpegBase image(mdJpegType, std::make_unique<MockBasicIo>(), false, initData, dataSize);

    EXPECT_CALL(mock_io, write(_, _)).Times(AtLeast(1));



    image.writeMetadata();

}



TEST_F(JpegBaseTest, PrintStructureCallsTellOnIo_2176) {

    JpegBase image(mdJpegType, std::make_unique<MockBasicIo>(), false, initData, dataSize);

    EXPECT_CALL(mock_io, tell()).Times(AtLeast(1));



    image.printStructure(std::cout, kpsNone, 0);

}



TEST_F(JpegBaseTest, ConstructorInitializesSupportedMetadata_2176) {

    JpegBase image(mdJpegType, std::make_unique<MockBasicIo>(), false, initData, dataSize);



    EXPECT_TRUE(image.supportsMetadata(mdExif));

    EXPECT_TRUE(image.supportsMetadata(mdIptc));

    EXPECT_TRUE(image.supportsMetadata(mdXmp));

    EXPECT_TRUE(image.supportsMetadata(mdComment));

}



TEST_F(JpegBaseTest, ConstructorSetsIODevice_2176) {

    JpegBase image(mdJpegType, std::move(io_ptr), false, initData, dataSize);



    EXPECT_EQ(&image.io(), io_ptr.get());

}



TEST_F(JpegBaseTest, InitImageReturnsNonNegativeOnValidData_2176) {

    JpegBase image(mdJpegType, std::make_unique<MockBasicIo>(), true, initData, dataSize);



    int result = image.initImage(initData, dataSize);

    EXPECT_GE(result, 0);

}



TEST_F(JpegBaseTest, InitImageThrowsOnInvalidData_2176) {

    const byte invalidData[] = {0x00, 0x00, 0x00, 0x00};

    JpegBase image(mdJpegType, std::make_unique<MockBasicIo>(), true, invalidData, sizeof(invalidData));



    EXPECT_THROW(image.initImage(invalidData, sizeof(invalidData)), Error);

}
