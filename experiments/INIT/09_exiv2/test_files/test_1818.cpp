#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/image.hpp"
#include "exiv2/basicio.hpp"

namespace Exiv2 {

class MockBasicIo : public BasicIo {
public:
    MOCK_METHOD(bool, open, (), (override));
    MOCK_METHOD(void, close, (), (override));
    MOCK_METHOD(bool, seek, (size_t), (override));
    MOCK_METHOD(size_t, tell, (), (override));
    MOCK_METHOD(size_t, read, (void*, size_t), (override));
    MOCK_METHOD(size_t, write, (const void*, size_t), (override));
};

class CrwImageTest : public ::testing::Test {
protected:
    MockBasicIo mockIo;
    bool create = true;
    Image::UniquePtr image;

    virtual void SetUp() {
        image = newCrwInstance(std::make_unique<MockBasicIo>(mockIo), create);
    }
};

TEST_F(CrwImageTest, newCrwInstance_CreationSucceeds_1818) {
    EXPECT_CALL(mockIo, open()).WillOnce(::testing::Return(true));

    auto image = newCrwInstance(std::make_unique<MockBasicIo>(mockIo), true);
    ASSERT_NE(image, nullptr);
    EXPECT_TRUE(image->good());
}

TEST_F(CrwImageTest, newCrwInstance_CreationFails_1819) {
    EXPECT_CALL(mockIo, open()).WillOnce(::testing::Return(false));

    auto image = newCrwInstance(std::make_unique<MockBasicIo>(mockIo), true);
    ASSERT_EQ(image, nullptr);
}

TEST_F(CrwImageTest, newCrwInstance_WithInvalidIo_1820) {
    EXPECT_CALL(mockIo, open()).WillOnce(::testing::Return(false));
    
    auto image = newCrwInstance(std::make_unique<MockBasicIo>(mockIo), false);
    ASSERT_EQ(image, nullptr);
}

TEST_F(CrwImageTest, newCrwInstance_WithValidIo_1821) {
    EXPECT_CALL(mockIo, open()).WillOnce(::testing::Return(true));
    
    auto image = newCrwInstance(std::make_unique<MockBasicIo>(mockIo), false);
    ASSERT_NE(image, nullptr);
    EXPECT_TRUE(image->good());
}

TEST_F(CrwImageTest, newCrwInstance_CheckIoOpen_1822) {
    EXPECT_CALL(mockIo, open()).Times(1).WillOnce(::testing::Return(true));
    
    auto image = newCrwInstance(std::make_unique<MockBasicIo>(mockIo), true);
    ASSERT_NE(image, nullptr);
}

TEST_F(CrwImageTest, newCrwInstance_WithCreateFalse_1823) {
    EXPECT_CALL(mockIo, open()).WillOnce(::testing::Return(true));
    
    auto image = newCrwInstance(std::make_unique<MockBasicIo>(mockIo), false);
    ASSERT_NE(image, nullptr);
}

TEST_F(CrwImageTest, newCrwInstance_InvalidIoAfterCreateFalse_1824) {
    EXPECT_CALL(mockIo, open()).WillOnce(::testing::Return(false));
    
    auto image = newCrwInstance(std::make_unique<MockBasicIo>(mockIo), false);
    ASSERT_EQ(image, nullptr);
}

} // namespace Exiv2