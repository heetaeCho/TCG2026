#include <gtest/gtest.h>

#include "util/crc32c.h"



namespace leveldb {

namespace crc32c {



class CRC32CTest : public ::testing::Test {

protected:

    // No additional setup or teardown required for this simple function test.

};



TEST_F(CRC32CTest_322, Unmask_ReturnsCorrectValueForZeroInput_322) {

    uint32_t masked_crc = 0;

    uint32_t expected_unmasked_crc = Unmask(masked_crc);

    EXPECT_EQ(expected_unmasked_crc, 0U);

}



TEST_F(CRC32CTest_322, Unmask_ReturnsCorrectValueForMaxInput_322) {

    uint32_t masked_crc = UINT32_MAX;

    uint32_t expected_unmasked_crc = Unmask(masked_crc);

    EXPECT_EQ(expected_unmasked_crc, 4061359782U); // Calculated based on the given kMaskDelta

}



TEST_F(CRC32CTest_322, Unmask_ReturnsCorrectValueForRandomInput_322) {

    uint32_t masked_crc = 1234567890;

    uint32_t expected_unmasked_crc = 129012259; // Calculated based on the given kMaskDelta

    EXPECT_EQ(Unmask(masked_crc), expected_unmasked_crc);

}



TEST_F(CRC32CTest_322, Unmask_ReturnsCorrectValueForMaskDeltaInput_322) {

    uint32_t masked_crc = kMaskDelta;

    uint32_t expected_unmasked_crc = 0U; // Since rotating kMaskDelta by itself should result in 0

    EXPECT_EQ(Unmask(masked_crc), expected_unmasked_crc);

}



} // namespace crc32c

} // namespace leveldb
