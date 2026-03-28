#include <gtest/gtest.h>

#include "tiffvisitor_int.hpp"



namespace Exiv2 {

namespace Internal {



class TiffReaderTest_1693 : public ::testing::Test {

protected:

    TiffRwState state_{ByteOrder::bigEndian, 0};

    byte data_[10];

    TiffComponent root_;

    TiffReader reader_{data_, sizeof(data_), &root_, state_};



    void SetUp() override {}

    void TearDown() override {}

};



TEST_F(TiffReaderTest_1693, ByteOrder_ReturnsCorrectValue_1693) {

    EXPECT_EQ(reader_.byteOrder(), ByteOrder::bigEndian);

}



TEST_F(TiffReaderTest_1693, BaseOffset_ReturnsCorrectValue_1693) {

    EXPECT_EQ(reader_.baseOffset(), 0u);

}



// Test boundary conditions for baseOffset

TEST_F(TiffReaderTest_1693, BaseOffset_BoundaryCondition_Zero_1693) {

    TiffRwState state{ByteOrder::bigEndian, 0};

    TiffReader reader(data_, sizeof(data_), &root_, state);

    EXPECT_EQ(reader.baseOffset(), 0u);

}



TEST_F(TiffReaderTest_1693, BaseOffset_BoundaryCondition_MaxSizeT_1693) {

    TiffRwState state{ByteOrder::bigEndian, std::numeric_limits<size_t>::max()};

    TiffReader reader(data_, sizeof(data_), &root_, state);

    EXPECT_EQ(reader.baseOffset(), std::numeric_limits<size_t>::max());

}



// Test different byte orders

TEST_F(TiffReaderTest_1693, ByteOrder_LittleEndian_1693) {

    TiffRwState state{ByteOrder::littleEndian, 0};

    TiffReader reader(data_, sizeof(data_), &root_, state);

    EXPECT_EQ(reader.byteOrder(), ByteOrder::littleEndian);

}



TEST_F(TiffReaderTest_1693, ByteOrder_BigEndian_1693) {

    TiffRwState state{ByteOrder::bigEndian, 0};

    TiffReader reader(data_, sizeof(data_), &root_, state);

    EXPECT_EQ(reader.byteOrder(), ByteOrder::bigEndian);

}



// Test exceptional or error cases (if observable through the interface)

// In this case, there are no clear exceptional or error cases that can be observed from the public interface.



}  // namespace Internal

}  // namespace Exiv2
