#include <gtest/gtest.h>

#include "exiv2/pgfimage.hpp"

#include <memory>



namespace {



class MockBasicIo : public Exiv2::BasicIo {

public:

    MOCK_METHOD(void, read, (byte* buf, long numBytes), (override));

    MOCK_METHOD(void, write, (const byte* buf, long numBytes), (override));

    MOCK_METHOD(long, tellg, (), (const, override));

    MOCK_METHOD(void, seekg, (long offset, Position pos), (override));

};



class PgfImageTest : public ::testing::Test {

protected:

    std::unique_ptr<MockBasicIo> mockIo;

    Exiv2::PgfImage pgfImage;



    PgfImageTest() : mockIo(std::make_unique<MockBasicIo>()), pgfImage(std::move(mockIo), false) {}

};



TEST_F(PgfImageTest, MimeType_ReturnsCorrectMimeType_1043) {

    EXPECT_EQ(pgfImage.mimeType(), "image/pgf");

}



TEST_F(PgfImageTest, ReadMetadata_DoesNotThrowExceptionOnNormalOperation_1043) {

    EXPECT_NO_THROW(pgfImage.readMetadata());

}



TEST_F(PgfImageTest, WriteMetadata_DoesNotThrowExceptionOnNormalOperation_1043) {

    EXPECT_NO_THROW(pgfImage.writeMetadata());

}



}  // namespace
