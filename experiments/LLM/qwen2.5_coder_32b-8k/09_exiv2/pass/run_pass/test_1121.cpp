#include <gtest/gtest.h>

#include "exiv2/types.hpp"



namespace Exiv2 {

    class DataBufTest_1121 : public ::testing::Test {

    protected:

        void SetUp() override {

            // Setup can be used to initialize objects before each test.

        }



        void TearDown() override {

            // Cleanup can be done here if necessary.

        }

    };



    TEST_F(DataBufTest_1121, WriteWithinBounds_1121) {

        DataBuf buffer(2);

        EXPECT_NO_THROW(buffer.write_uint16(0, 0x1234, littleEndian));

        // Verify the written value if possible through public interface

        EXPECT_EQ(buffer.read_uint16(0, littleEndian), 0x1234);

    }



    TEST_F(DataBufTest_1121, WriteAtBoundary_1121) {

        DataBuf buffer(2);

        EXPECT_NO_THROW(buffer.write_uint16(0, 0xABCD, bigEndian));

        // Verify the written value if possible through public interface

        EXPECT_EQ(buffer.read_uint16(0, bigEndian), 0xABCD);

    }



    TEST_F(DataBufTest_1121, WriteOutOfBounds_1121) {

        DataBuf buffer(2);

        EXPECT_THROW(buffer.write_uint16(1, 0x5678, littleEndian), std::out_of_range);

    }



    TEST_F(DataBufTest_1121, WritePastEnd_1121) {

        DataBuf buffer(1);

        EXPECT_THROW(buffer.write_uint16(0, 0x9ABC, bigEndian), std::out_of_range);

    }



    TEST_F(DataBufTest_1121, EmptyBufferWrite_1121) {

        DataBuf buffer;

        EXPECT_THROW(buffer.write_uint16(0, 0xCDEF, littleEndian), std::out_of_range);

    }

}
