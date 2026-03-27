#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "epsimage.hpp"

#include "basicio.hpp"

#include "error.hpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte* data, size_t wcount), (override));

};



TEST_F(EpsImageTest_2205, ConstructorDoesNotCreateFileIfFlagIsFalse_2205) {

    auto mockIo = std::make_unique<MockBasicIo>();

    EXPECT_CALL(*mockIo, open()).Times(0);

    EpsImage image(std::move(mockIo), false);

}



TEST_F(EpsImageTest_2205, ConstructorCreatesFileAndWritesBlankEPSIfFlagIsTrue_2205) {

    auto mockIo = std::make_unique<MockBasicIo>();

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, write(_, _)).WillOnce(Return(strlen("%!PS-Adobe-3.0 EPSF-3.0\n%%BoundingBox: 0 0 0 0\n")));

    EpsImage image(std::move(mockIo), true);

}



TEST_F(EpsImageTest_2205, ConstructorThrowsIfWriteFails_2205) {

    auto mockIo = std::make_unique<MockBasicIo>();

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, write(_, _)).WillOnce(Return(0)); // Simulate write failure

    EXPECT_THROW(EpsImage(std::move(mockIo), true), Error);

}



TEST_F(EpsImageTest_2205, ConstructorDoesNotThrowIfOpenFails_2205) {

    auto mockIo = std::make_unique<MockBasicIo>();

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(-1)); // Simulate open failure

    EXPECT_NO_THROW(EpsImage(std::move(mockIo), true));

}



TEST_F(EpsImageTest_2205, ConstructorWritesCorrectData_2205) {

    auto mockIo = std::make_unique<MockBasicIo>();

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, write(_, strlen("%!PS-Adobe-3.0 EPSF-3.0\n%%BoundingBox: 0 0 0 0\n")))

        .WillOnce([](const byte* data, size_t wcount) -> size_t {

            EXPECT_STREQ(reinterpret_cast<const char*>(data), "%!PS-Adobe-3.0 EPSF-3.0\n%%BoundingBox: 0 0 0 0\n");

            return wcount;

        });

    EpsImage image(std::move(mockIo), true);

}



TEST_F(EpsImageTest_2205, MimeTypeReturnsCorrectType_2205) {

    auto mockIo = std::make_unique<MockBasicIo>();

    EpsImage image(std::move(mockIo), false);

    EXPECT_EQ(image.mimeType(), "application/postscript");

}
