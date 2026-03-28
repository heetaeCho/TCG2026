#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/bmffimage.hpp"
#include "exiv2/basicio.hpp"

using namespace Exiv2;
using ::testing::_;
using ::testing::Mock;
using ::testing::Return;
using ::testing::NiceMock;

class MockBasicIo : public BasicIo {
public:
    MOCK_METHOD(void, read, (byte* buf, size_t rcount), (override));
    MOCK_METHOD(int, error, (), (const, override));
    MOCK_METHOD(bool, eof, (), (const, override));
    MOCK_METHOD(int64_t, seek, (int64_t offset, Position pos), (override));
};

TEST_F(BmffImageTest_1204, IsBmffType_FTYP_Success_1204) {
    NiceMock<MockBasicIo> mockIo;

    // Prepare the buffer to return for the FTYP type
    byte buf[12] = {0};
    buf[4] = 'f'; buf[5] = 't'; buf[6] = 'y'; buf[7] = 'p';
    
    // Expect read to populate the buffer
    EXPECT_CALL(mockIo, read(_, 12)).Times(1).WillOnce([buf](byte* buffer, size_t rcount) {
        std::memcpy(buffer, buf, rcount);
    });
    EXPECT_CALL(mockIo, error()).WillOnce(Return(0)); // No error
    EXPECT_CALL(mockIo, eof()).WillOnce(Return(false)); // Not EOF

    // Call the method under test
    bool result = isBmffType(mockIo, true);

    // Validate that the result is correct for FTYP
    EXPECT_TRUE(result);
}

TEST_F(BmffImageTest_1204, IsBmffType_JXL_Success_1204) {
    NiceMock<MockBasicIo> mockIo;

    // Prepare the buffer to return for JXL type
    byte buf[12] = {0};
    buf[4] = 'J'; buf[5] = 'X'; buf[6] = 'L'; buf[7] = ' ';
    
    // Expect read to populate the buffer
    EXPECT_CALL(mockIo, read(_, 12)).Times(1).WillOnce([buf](byte* buffer, size_t rcount) {
        std::memcpy(buffer, buf, rcount);
    });
    EXPECT_CALL(mockIo, error()).WillOnce(Return(0)); // No error
    EXPECT_CALL(mockIo, eof()).WillOnce(Return(false)); // Not EOF

    // Call the method under test
    bool result = isBmffType(mockIo, true);

    // Validate that the result is correct for JXL
    EXPECT_TRUE(result);
}

TEST_F(BmffImageTest_1204, IsBmffType_FTYP_Failure_1204) {
    NiceMock<MockBasicIo> mockIo;

    // Prepare the buffer to return for non-BMFF type
    byte buf[12] = {0};
    buf[4] = 'A'; buf[5] = 'B'; buf[6] = 'C'; buf[7] = 'D';
    
    // Expect read to populate the buffer
    EXPECT_CALL(mockIo, read(_, 12)).Times(1).WillOnce([buf](byte* buffer, size_t rcount) {
        std::memcpy(buffer, buf, rcount);
    });
    EXPECT_CALL(mockIo, error()).WillOnce(Return(0)); // No error
    EXPECT_CALL(mockIo, eof()).WillOnce(Return(false)); // Not EOF

    // Call the method under test
    bool result = isBmffType(mockIo, true);

    // Validate that the result is false for non-BMFF type
    EXPECT_FALSE(result);
}

TEST_F(BmffImageTest_1204, IsBmffType_Read_Error_1204) {
    NiceMock<MockBasicIo> mockIo;

    // Prepare the buffer to return for FTYP type
    byte buf[12] = {0};
    buf[4] = 'f'; buf[5] = 't'; buf[6] = 'y'; buf[7] = 'p';
    
    // Expect read to populate the buffer, and simulate error
    EXPECT_CALL(mockIo, read(_, 12)).Times(1).WillOnce([buf](byte* buffer, size_t rcount) {
        std::memcpy(buffer, buf, rcount);
    });
    EXPECT_CALL(mockIo, error()).WillOnce(Return(1)); // Simulate error
    EXPECT_CALL(mockIo, eof()).WillOnce(Return(false)); // Not EOF

    // Call the method under test
    bool result = isBmffType(mockIo, true);

    // Validate that the result is false due to read error
    EXPECT_FALSE(result);
}

TEST_F(BmffImageTest_1204, IsBmffType_EOF_Error_1204) {
    NiceMock<MockBasicIo> mockIo;

    // Prepare the buffer to return for FTYP type
    byte buf[12] = {0};
    buf[4] = 'f'; buf[5] = 't'; buf[6] = 'y'; buf[7] = 'p';
    
    // Expect read to populate the buffer, and simulate EOF error
    EXPECT_CALL(mockIo, read(_, 12)).Times(1).WillOnce([buf](byte* buffer, size_t rcount) {
        std::memcpy(buffer, buf, rcount);
    });
    EXPECT_CALL(mockIo, error()).WillOnce(Return(0)); // No error
    EXPECT_CALL(mockIo, eof()).WillOnce(Return(true)); // Simulate EOF

    // Call the method under test
    bool result = isBmffType(mockIo, true);

    // Validate that the result is false due to EOF
    EXPECT_FALSE(result);
}

TEST_F(BmffImageTest_1204, IsBmffType_Seek_1204) {
    NiceMock<MockBasicIo> mockIo;

    // Prepare the buffer to return for FTYP type
    byte buf[12] = {0};
    buf[4] = 'f'; buf[5] = 't'; buf[6] = 'y'; buf[7] = 'p';
    
    // Expect read to populate the buffer
    EXPECT_CALL(mockIo, read(_, 12)).Times(1).WillOnce([buf](byte* buffer, size_t rcount) {
        std::memcpy(buffer, buf, rcount);
    });
    EXPECT_CALL(mockIo, error()).WillOnce(Return(0)); // No error
    EXPECT_CALL(mockIo, eof()).WillOnce(Return(false)); // Not EOF
    EXPECT_CALL(mockIo, seek(0, BasicIo::beg)).Times(1); // Verify seek is called

    // Call the method under test with advance=true, which should trigger seek
    bool result = isBmffType(mockIo, true);

    // Validate that the result is true and seek is called
    EXPECT_TRUE(result);
}