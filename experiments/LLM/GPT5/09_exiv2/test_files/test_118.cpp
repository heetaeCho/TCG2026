#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "helper_functions.hpp"
#include "exiv2/types.hpp"
#include "exiv2/basicio.hpp"
#include "exiv2/error.hpp"

namespace Exiv2 {
    class MockBasicIo : public BasicIo {
    public:
        MOCK_METHOD(DataBuf, read, (size_t rcount), (override));
        MOCK_METHOD(void, readOrThrow, (byte* buf, size_t rcount, ErrorCode err), (override));
        MOCK_METHOD(size_t, tell, (), (const, override));
        MOCK_METHOD(size_t, size, (), (const, override));
    };

    // Test case for normal operation
    TEST_F(HelperFunctionsTest_118, readWORDTag_ReturnsExpectedWordValue_118) {
        MockBasicIo mockIo;
        DataBuf expectedBuf(2);
        expectedBuf.write_uint16(0, 0x1234, littleEndian);

        EXPECT_CALL(mockIo, read(Exiv2::WORD))
            .WillOnce(testing::Return(expectedBuf));

        uint16_t result = readWORDTag(mockIo);

        EXPECT_EQ(result, 0x1234);
    }

    // Test case for boundary condition (reading at the beginning of the file)
    TEST_F(HelperFunctionsTest_118, readWORDTag_AtBeginning_118) {
        MockBasicIo mockIo;
        DataBuf expectedBuf(2);
        expectedBuf.write_uint16(0, 0xABCD, littleEndian);

        EXPECT_CALL(mockIo, read(Exiv2::WORD))
            .WillOnce(testing::Return(expectedBuf));

        uint16_t result = readWORDTag(mockIo);

        EXPECT_EQ(result, 0xABCD);
    }

    // Test case for error condition (data corruption, size is insufficient)
    TEST_F(HelperFunctionsTest_118, readWORDTag_ThrowsOnCorruptedMetadata_118) {
        MockBasicIo mockIo;

        EXPECT_CALL(mockIo, read(Exiv2::WORD))
            .WillOnce(testing::Return(DataBuf()));  // Returning empty buffer (corrupted)

        EXPECT_THROW(readWORDTag(mockIo), std::runtime_error);
    }

    // Test case for boundary condition (reading at the end of the file)
    TEST_F(HelperFunctionsTest_118, readWORDTag_AtEndOfFile_118) {
        MockBasicIo mockIo;
        DataBuf expectedBuf(2);
        expectedBuf.write_uint16(0, 0x5555, littleEndian);

        EXPECT_CALL(mockIo, read(Exiv2::WORD))
            .WillOnce(testing::Return(expectedBuf));

        EXPECT_CALL(mockIo, tell())
            .WillOnce(testing::Return(10));  // Simulate end-of-file scenario

        uint16_t result = readWORDTag(mockIo);

        EXPECT_EQ(result, 0x5555);
    }

    // Test case for error condition: size mismatch (insufficient data to read)
    TEST_F(HelperFunctionsTest_118, readWORDTag_ThrowsOnSizeMismatch_118) {
        MockBasicIo mockIo;
        DataBuf insufficientData(1); // 1 byte instead of 2

        EXPECT_CALL(mockIo, read(Exiv2::WORD))
            .WillOnce(testing::Return(insufficientData));

        EXPECT_THROW(readWORDTag(mockIo), std::runtime_error);
    }
}