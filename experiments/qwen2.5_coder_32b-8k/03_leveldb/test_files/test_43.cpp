#include <gtest/gtest.h>

#include "port/port_stdcxx.h"



class CRC32CTest : public ::testing::Test {

protected:

    uint32_t initial_crc = 0;

    const char* test_buffer = "123456789";

    size_t buffer_size = 9;

};



TEST_F(CRC32CTest_43, NormalOperation_43) {

    uint32_t result = leveldb::port::AcceleratedCRC32C(initial_crc, test_buffer, buffer_size);

#ifdef HAVE_CRC32C

    EXPECT_NE(result, initial_crc);  // Assuming CRC32C changes the value

#else

    EXPECT_EQ(result, 0);           // Without CRC32C support, it should return 0

#endif

}



TEST_F(CRC32CTest_43, ZeroSizeBuffer_43) {

    uint32_t result = leveldb::port::AcceleratedCRC32C(initial_crc, test_buffer, 0);

    EXPECT_EQ(result, initial_crc); // Zero size should not change the CRC

}



TEST_F(CRC32CTest_43, NullBufferPointer_43) {

    uint32_t result = leveldb::port::AcceleratedCRC32C(initial_crc, nullptr, buffer_size);

#ifdef HAVE_CRC32C

    EXPECT_NE(result, initial_crc);  // Behavior might still change even with null buffer

#else

    EXPECT_EQ(result, 0);           // Without CRC32C support, it should return 0

#endif

}



TEST_F(CRC32CTest_43, LargeBufferSize_43) {

    std::string large_buffer(1024 * 1024, 'A');  // 1MB buffer filled with 'A'

    uint32_t result = leveldb::port::AcceleratedCRC32C(initial_crc, large_buffer.c_str(), large_buffer.size());

#ifdef HAVE_CRC32C

    EXPECT_NE(result, initial_crc);  // Large buffer should produce a different CRC

#else

    EXPECT_EQ(result, 0);           // Without CRC32C support, it should return 0

#endif

}
