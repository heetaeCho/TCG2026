#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/pgfimage.hpp"

#include "exiv2/basicio.hpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte * data, size_t wcount), (override));

    MOCK_METHOD(byte *, mmap, (bool isWriteable), (override));

    MOCK_METHOD(int, munmap, (), (override));

    MOCK_METHOD(const size_t, tell, (), (const override));

    MOCK_METHOD(const size_t, size, (), (const override));

    MOCK_METHOD(const bool, isopen, (), (const override));

    MOCK_METHOD(const int, error, (), (const override));

    MOCK_METHOD(const bool, eof, (), (const override));

    MOCK_METHOD(const std::string &, path, (), (const override));

};



class PgfImageTest : public ::testing::Test {

protected:

    std::unique_ptr<MockBasicIo> mockIo;

    BasicIo::UniquePtr io;



    void SetUp() override {

        mockIo = std::make_unique<MockBasicIo>();

        io.reset(mockIo.release());

    }

};



TEST_F(PgfImageTest, ConstructorDoesNotCreate_2203) {

    EXPECT_CALL(*mockIo, open()).Times(0);

    EXPECT_CALL(*mockIo, write(_, _)).Times(0);



    PgfImage image(std::move(io), false);

}



TEST_F(PgfImageTest, ConstructorCreatesSuccessfully_2203) {

    const unsigned char pgfBlank[106] = {80, 71, 70, 54, 16, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 24, 3, 3, 0, 0, 0, 20, 0, 103, 8, 32, 0, 192, 1, 0, 0, 55, 0, 0, 120, 0, 0, 0, 0, 1, 0, 0, 0, 55, 0, 0, 120, 0, 0, 0, 0, 1, 0, 0, 0, 55, 0, 0, 120, 0, 0, 0, 0, 1, 0, 0, 0, 55, 0, 0, 120, 0, 0, 0, 0, 1, 0, 0, 0, 55, 0, 0, 120, 0, 0, 0, 0, 1, 0, 0, 0};



    EXPECT_CALL(*mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, write(pgfBlank, sizeof(pgfBlank))).WillOnce(Return(sizeof(pgfBlank)));



    PgfImage image(std::move(io), true);

}



TEST_F(PgfImageTest, ConstructorFailsToCreate_2203) {

    const unsigned char pgfBlank[106] = {80, 71, 70, 54, 16, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 24, 3, 3, 0, 0, 0, 20, 0, 103, 8, 32, 0, 192, 1, 0, 0, 55, 0, 0, 120, 0, 0, 0, 0, 1, 0, 0, 0, 55, 0, 0, 120, 0, 0, 0, 0, 1, 0, 0, 0, 55, 0, 0, 120, 0, 0, 0, 0, 1, 0, 0, 0, 55, 0, 0, 120, 0, 0, 0, 0, 1, 0, 0, 0};



    EXPECT_CALL(*mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, write(pgfBlank, sizeof(pgfBlank))).WillOnce(Return(0));



    PgfImage image(std::move(io), true);

}



TEST_F(PgfImageTest, ConstructorOpenFails_2203) {

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(-1));

    EXPECT_CALL(*mockIo, write(_, _)).Times(0);



    PgfImage image(std::move(io), true);

}
