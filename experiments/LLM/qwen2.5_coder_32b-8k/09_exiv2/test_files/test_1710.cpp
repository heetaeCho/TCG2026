#include <gtest/gtest.h>

#include "exiv2/types.hpp"

#include "exiv2/image.hpp"



namespace Exiv2 {

    static uint32_t byteSwap_(Exiv2::DataBuf& buf, size_t offset, bool bSwap);

}



class ByteSwapTest : public ::testing::Test {

protected:

    DataBuf data;

    

    void SetUp() override {

        // Initialize a buffer with some sample data

        const byte initialData[] = {0x11, 0x22, 0x33, 0x44};

        data = DataBuf(initialData, sizeof(initialData));

    }

};



TEST_F(ByteSwapTest_1710, NormalOperation_BigEndianToLittleEndian_1710) {

    bool bSwap = true; // Big to Little

    uint32_t result = Exiv2::byteSwap_(data, 0, bSwap);

    EXPECT_EQ(result, 0x44332211); // Expected swapped value

}



TEST_F(ByteSwapTest_1710, NormalOperation_LittleEndianToBigEndian_1710) {

    bool bSwap = true; // First swap to Big Endian

    Exiv2::byteSwap_(data, 0, bSwap);

    bSwap = false; // Now swap back to Little Endian

    uint32_t result = Exiv2::byteSwap_(data, 0, bSwap);

    EXPECT_EQ(result, 0x11223344); // Should be original value

}



TEST_F(ByteSwapTest_1710, BoundaryCondition_ZeroOffset_1710) {

    bool bSwap = true; 

    uint32_t result = Exiv2::byteSwap_(data, 0, bSwap);

    EXPECT_EQ(result, 0x44332211); // Expected swapped value

}



TEST_F(ByteSwapTest_1710, BoundaryCondition_MaxOffset_1710) {

    bool bSwap = true; 

    uint32_t result = Exiv2::byteSwap_(data, data.size() - 4, bSwap);

    EXPECT_EQ(result, 0x44332211); // Expected swapped value

}



TEST_F(ByteSwapTest_1710, ErrorCondition_OffsetTooLarge_1710) {

    bool bSwap = true; 

    EXPECT_THROW(Exiv2::byteSwap_(data, data.size() - 3, bSwap), std::out_of_range); // Should throw due to insufficient size

}



TEST_F(ByteSwapTest_1710, NoSwapOperation_1710) {

    bool bSwap = false; 

    uint32_t result = Exiv2::byteSwap_(data, 0, bSwap);

    EXPECT_EQ(result, 0x11223344); // Should be original value

}
