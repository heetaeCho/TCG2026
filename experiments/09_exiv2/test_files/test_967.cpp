#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/pngimage.hpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;



class PngImageTest_967 : public ::testing::Test {

protected:

    class MockBasicIo : public BasicIo {

    public:

        MOCK_METHOD(void, readMemory, (byte* data, size_t length), (override));

        MOCK_METHOD(void, writeMemory, (const byte* data, size_t length), (override));

        MOCK_METHOD(void, seek, (long offset, Position pos), (override));

        MOCK_METHOD(size_t, tell, (), (override));

        MOCK_METHOD(void, close, (), (override));

    };



    std::unique_ptr<MockBasicIo> mockIo;

    PngImageTest_967() : mockIo(std::make_unique<MockBasicIo>()) {}

};



TEST_F(PngImageTest_967, MimeTypeReturnsCorrectType_967) {

    PngImage pngImage(std::move(mockIo), false);

    EXPECT_EQ(pngImage.mimeType(), "image/png");

}



TEST_F(PngImageTest_967, ReadMetadataDoesNotThrowOnValidInput_967) {

    PngImage pngImage(std::move(mockIo), false);

    EXPECT_NO_THROW(pngImage.readMetadata());

}



TEST_F(PngImageTest_967, WriteMetadataDoesNotThrowOnValidInput_967) {

    PngImage pngImage(std::move(mockIo), false);

    EXPECT_NO_THROW(pngImage.writeMetadata());

}



TEST_F(PngImageTest_967, PrintStructureDoesNotThrowOnValidInput_967) {

    PngImage pngImage(std::move(mockIo), false);

    std::ostringstream out;

    EXPECT_NO_THROW(pngImage.printStructure(out, PrintStructureOption(), 0));

}
