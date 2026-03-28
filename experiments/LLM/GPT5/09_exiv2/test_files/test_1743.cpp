#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/cr2image.hpp"
#include "exiv2/basicio.hpp"
#include "exiv2/error.hpp"

namespace Exiv2 {

class MockBasicIo : public BasicIo {
public:
    MOCK_METHOD(int, open, (), (override));
    MOCK_METHOD(int, close, (), (override));
    MOCK_METHOD(size_t, write, (const byte* data, size_t wcount), (override));
    MOCK_METHOD(DataBuf, read, (size_t rcount), (override));
    MOCK_METHOD(size_t, read, (byte* buf, size_t rcount), (override));
    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));
    MOCK_METHOD(const bool, eof, (), (override));
    MOCK_METHOD(const int, error, (), (override));
    MOCK_METHOD(const std::string&, path, (), (override));
    MOCK_METHOD(bool, isopen, (), (override));
    MOCK_METHOD(const size_t, size, (), (override));
};

class Cr2ImageTest : public ::testing::Test {
protected:
    std::unique_ptr<MockBasicIo> io;
    std::unique_ptr<Cr2Image> cr2Image;

    void SetUp() override {
        io = std::make_unique<MockBasicIo>();
    }
};

TEST_F(Cr2ImageTest, ReadMetadata_Success) {
    // TEST_ID: 1743
    EXPECT_CALL(*io, open()).WillOnce(::testing::Return(0));  // Simulate successful opening
    EXPECT_CALL(*io, eof()).WillOnce(::testing::Return(false));  // Simulate no EOF
    EXPECT_CALL(*io, error()).WillOnce(::testing::Return(0));  // Simulate no error
    EXPECT_CALL(*io, path()).WillOnce(::testing::Return("test.cr2"));

    cr2Image = std::make_unique<Cr2Image>(std::move(io), true);
    
    EXPECT_NO_THROW(cr2Image->readMetadata());
}

TEST_F(Cr2ImageTest, ReadMetadata_Failure_OpenFailed) {
    // TEST_ID: 1744
    EXPECT_CALL(*io, open()).WillOnce(::testing::Return(1));  // Simulate failure to open
    EXPECT_CALL(*io, path()).WillOnce(::testing::Return("test.cr2"));

    cr2Image = std::make_unique<Cr2Image>(std::move(io), true);
    
    EXPECT_THROW(cr2Image->readMetadata(), Error);
}

TEST_F(Cr2ImageTest, ReadMetadata_Failure_NotCr2) {
    // TEST_ID: 1745
    EXPECT_CALL(*io, open()).WillOnce(::testing::Return(0));  // Simulate successful opening
    EXPECT_CALL(*io, eof()).WillOnce(::testing::Return(false));  // Simulate no EOF
    EXPECT_CALL(*io, error()).WillOnce(::testing::Return(0));  // Simulate no error
    EXPECT_CALL(*io, path()).WillOnce(::testing::Return("test.cr2"));

    cr2Image = std::make_unique<Cr2Image>(std::move(io), true);
    
    // Simulate failure in type check
    EXPECT_THROW(cr2Image->readMetadata(), Error);
}

TEST_F(Cr2ImageTest, ReadMetadata_Failure_FailedToReadImageData) {
    // TEST_ID: 1746
    EXPECT_CALL(*io, open()).WillOnce(::testing::Return(0));  // Simulate successful opening
    EXPECT_CALL(*io, error()).WillOnce(::testing::Return(1));  // Simulate error reading data
    EXPECT_CALL(*io, path()).WillOnce(::testing::Return("test.cr2"));

    cr2Image = std::make_unique<Cr2Image>(std::move(io), true);
    
    EXPECT_THROW(cr2Image->readMetadata(), Error);
}

TEST_F(Cr2ImageTest, ByteOrder_Setting) {
    // TEST_ID: 1747
    EXPECT_CALL(*io, open()).WillOnce(::testing::Return(0));  // Simulate successful opening
    EXPECT_CALL(*io, eof()).WillOnce(::testing::Return(false));  // Simulate no EOF
    EXPECT_CALL(*io, error()).WillOnce(::testing::Return(0));  // Simulate no error
    EXPECT_CALL(*io, path()).WillOnce(::testing::Return("test.cr2"));

    cr2Image = std::make_unique<Cr2Image>(std::move(io), true);

    cr2Image->readMetadata();  // Ensure no exceptions thrown
    
    // Verify that byte order was set correctly
    ByteOrder byteOrder = cr2Image->byteOrder();
    EXPECT_NE(byteOrder, invalidByteOrder);
}

}  // namespace Exiv2