#include <gtest/gtest.h>

#include "exiv2/image.hpp"

#include "exiv2/basicio.hpp"



using namespace Exiv2;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte * data, size_t wcount), (override));

    MOCK_METHOD(size_t, write, (BasicIo & src), (override));

    MOCK_METHOD(int, putb, (byte data), (override));

    MOCK_METHOD(DataBuf, read, (size_t rcount), (override));

    MOCK_METHOD(size_t, read, (byte * buf, size_t rcount), (override));

    MOCK_METHOD(void, readOrThrow, (byte * buf, size_t rcount, ErrorCode err), (override));

    MOCK_METHOD(int, getb, (), (override));

    MOCK_METHOD(void, transfer, (BasicIo & src), (override));

    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

    MOCK_METHOD(void, seekOrThrow, (int64_t offset, Position pos, ErrorCode err), (override));

    MOCK_METHOD(byte *, mmap, (bool isWriteable), (override));

    MOCK_METHOD(int, munmap, (), (override));

    MOCK_METHOD(const size_t, tell, (), (const, override));

    MOCK_METHOD(const size_t, size, (), (const, override));

    MOCK_METHOD(const bool, isopen, (), (const, override));

    MOCK_METHOD(const int, error, (), (const, override));

    MOCK_METHOD(const bool, eof, (), (const, override));

    MOCK_METHOD(const std::string &, path, (), (const, override));

};



class ImageTest : public ::testing::Test {

protected:

    MockBasicIo mock_io;

    ImageType image_type = ImageType::jpeg;

    uint16_t supported_metadata = 0x1F; // Assuming some valid metadata flags



    void SetUp() override {

        EXPECT_CALL(mock_io, open()).WillOnce(::testing::Return(0));

        EXPECT_CALL(mock_io, isopen()).WillRepeatedly(::testing::Return(true));

        image.reset(new Image(image_type, supported_metadata, std::make_unique<MockBasicIo>(mock_io)));

    }



    void TearDown() override {

        image.reset();

    }



    Image::UniquePtr image;

};



TEST_F(ImageTest_1096, GoodReturnsTrueWhenOpenSucceedsAndTypeIsCorrect_1096) {

    EXPECT_CALL(mock_io, open()).WillOnce(::testing::Return(0));

    EXPECT_CALL(*ImageFactory::createIo("dummy_path", false), isopen()).WillRepeatedly(::testing::Return(true));

    EXPECT_CALL(ImageFactory::checkType(image_type, testing::Ref(mock_io), false)).WillOnce(::testing::Return(true));



    bool result = image->good();

    ASSERT_TRUE(result);

}



TEST_F(ImageTest_1096, GoodReturnsFalseWhenOpenFails_1096) {

    EXPECT_CALL(mock_io, open()).WillOnce(::testing::Return(1));

    EXPECT_CALL(*ImageFactory::createIo("dummy_path", false), isopen()).WillRepeatedly(::testing::Return(false));



    bool result = image->good();

    ASSERT_FALSE(result);

}



TEST_F(ImageTest_1096, GoodReturnsFalseWhenTypeCheckFails_1096) {

    EXPECT_CALL(mock_io, open()).WillOnce(::testing::Return(0));

    EXPECT_CALL(*ImageFactory::createIo("dummy_path", false), isopen()).WillRepeatedly(::testing::Return(true));

    EXPECT_CALL(ImageFactory::checkType(image_type, testing::Ref(mock_io), false)).WillOnce(::testing::Return(false));



    bool result = image->good();

    ASSERT_FALSE(result);

}
