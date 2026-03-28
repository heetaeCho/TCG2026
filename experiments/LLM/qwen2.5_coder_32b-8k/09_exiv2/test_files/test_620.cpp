#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/basicio.hpp"

#include "exiv2/types.hpp"



namespace {



using ::testing::_;

using ::testing::Return;

using ::testing::Throw;



class MockFileIo : public Exiv2::FileIo {

public:

    MOCK_METHOD(int, open, (const std::string& mode), (override));

    MOCK_METHOD(size_t, write, (const byte* data, size_t wcount), (override));

};



TEST(writeFileTest_620, NormalOperation_620) {

    MockFileIo mockFileIo("test_path");

    Exiv2::DataBuf buf(10);

    memset(buf.data(), 'A', 10);



    EXPECT_CALL(mockFileIo, open("wb")).WillOnce(Return(0));

    EXPECT_CALL(mockFileIo, write(_, 10)).WillOnce(Return(10));



    size_t bytesWritten = Exiv2::writeFile(buf, "test_path");

    EXPECT_EQ(bytesWritten, 10);

}



TEST(writeFileTest_620, ZeroSizeBuffer_620) {

    MockFileIo mockFileIo("test_path");

    Exiv2::DataBuf buf(0);



    EXPECT_CALL(mockFileIo, open("wb")).WillOnce(Return(0));

    EXPECT_CALL(mockFileIo, write(_, 0)).WillOnce(Return(0));



    size_t bytesWritten = Exiv2::writeFile(buf, "test_path");

    EXPECT_EQ(bytesWritten, 0);

}



TEST(writeFileTest_620, FileOpenFailed_620) {

    MockFileIo mockFileIo("test_path");

    Exiv2::DataBuf buf(10);

    memset(buf.data(), 'A', 10);



    EXPECT_CALL(mockFileIo, open("wb")).WillOnce(Return(-1));



    EXPECT_THROW(Exiv2::writeFile(buf, "test_path"), Exiv2::Error);

}



TEST(writeFileTest_620, PartialWrite_620) {

    MockFileIo mockFileIo("test_path");

    Exiv2::DataBuf buf(10);

    memset(buf.data(), 'A', 10);



    EXPECT_CALL(mockFileIo, open("wb")).WillOnce(Return(0));

    EXPECT_CALL(mockFileIo, write(_, 10)).WillOnce(Return(5));



    size_t bytesWritten = Exiv2::writeFile(buf, "test_path");

    EXPECT_EQ(bytesWritten, 5);

}



}  // namespace
