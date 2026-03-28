#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/image.hpp"

#include "TestProjects/exiv2/src/epsimage.cpp"



namespace Exiv2 {

    class MockBasicIo : public BasicIo {

    public:

        MOCK_METHOD(void, open, (OpenMode mode), (override));

        MOCK_METHOD(void, close, (), (override));

        MOCK_METHOD(bool, good, (), (const, override));

        MOCK_METHOD(size_t, read, (byte* data, size_t count), (override));

        MOCK_METHOD(size_t, write, (const byte* data, size_t count), (override));

        MOCK_METHOD(void, seek, (int64_t offset, Position pos), (override));

        MOCK_METHOD(int64_t, tell, (), (const, override));

        MOCK_METHOD(void, truncate, (size_t size), (override));

        MOCK_METHOD(size_t, size, (), (const, override));

    };

}



using namespace Exiv2;



class EpsImageTest : public ::testing::Test {

protected:

    void SetUp() override {

        mockIo = std::make_unique<MockBasicIo>();

    }



    std::unique_ptr<MockBasicIo> mockIo;

};



TEST_F(EpsImageTest, NewEpsInstance_ReturnsNullptr_WhenIoIsNull_1755) {

    EXPECT_CALL(*mockIo, good()).WillOnce(::testing::Return(false));



    auto image = newEpsInstance(std::move(mockIo), false);

    ASSERT_EQ(image.get(), nullptr);

}



TEST_F(EpsImageTest, NewEpsInstance_ReturnsValidImage_WhenIoIsGoodAndCreateIsFalse_1755) {

    EXPECT_CALL(*mockIo, good()).WillOnce(::testing::Return(true));



    auto image = newEpsInstance(std::move(mockIo), false);

    ASSERT_NE(image.get(), nullptr);

}



TEST_F(EpsImageTest, NewEpsInstance_ReturnsValidImage_WhenIoIsGoodAndCreateIsTrue_1755) {

    EXPECT_CALL(*mockIo, good()).WillOnce(::testing::Return(true));



    auto image = newEpsInstance(std::move(mockIo), true);

    ASSERT_NE(image.get(), nullptr);

}
