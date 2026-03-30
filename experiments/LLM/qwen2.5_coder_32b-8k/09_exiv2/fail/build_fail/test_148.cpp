#include <gtest/gtest.h>

#include "exiv2/value.hpp"



using namespace Exiv2;



// Test fixture for ValueType<int>

class ValueTypeIntTest_148 : public ::testing::Test {

protected:

    ValueType<int> valueInt;

};



TEST_F(ValueTypeIntTest_148, ReadNormalOperation_148) {

    byte buf[] = {0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00};

    int result = valueInt.read(buf, sizeof(buf), littleEndian);

    EXPECT_EQ(result, 0);

    EXPECT_EQ(valueInt.count(), 2);

}



TEST_F(ValueTypeIntTest_148, ReadBoundaryCondition_ZeroLength_148) {

    byte buf[] = {0x01, 0x00, 0x00, 0x00};

    int result = valueInt.read(buf, 0, littleEndian);

    EXPECT_EQ(result, 0);

    EXPECT_EQ(valueInt.count(), 0);

}



TEST_F(ValueTypeIntTest_148, ReadBoundaryCondition_PartialData_148) {

    byte buf[] = {0x01, 0x00, 0x00};

    int result = valueInt.read(buf, sizeof(buf), littleEndian);

    EXPECT_EQ(result, 0);

    EXPECT_EQ(valueInt.count(), 0); // Partial data should not be read

}



TEST_F(ValueTypeIntTest_148, ReadBoundaryCondition_UnalignedData_148) {

    byte buf[] = {0x01, 0x00, 0x00, 0x02, 0x00, 0x00};

    int result = valueInt.read(buf, sizeof(buf), littleEndian);

    EXPECT_EQ(result, 0);

    EXPECT_EQ(valueInt.count(), 1); // Only one complete integer should be read

}



TEST_F(ValueTypeIntTest_148, CountNormalOperation_148) {

    byte buf[] = {0x01, 0x00, 0x00, 0x00};

    valueInt.read(buf, sizeof(buf), littleEndian);

    EXPECT_EQ(valueInt.count(), 1);

}



TEST_F(ValueTypeIntTest_148, SizeDataAreaNormalOperation_148) {

    byte buf[] = {0x01, 0x00, 0x00, 0x00};

    valueInt.read(buf, sizeof(buf), littleEndian);

    EXPECT_EQ(valueInt.sizeDataArea(), 4); // One int takes 4 bytes

}



TEST_F(ValueTypeIntTest_148, DataAreaNormalOperation_148) {

    byte buf[] = {0x01, 0x00, 0x00, 0x00};

    valueInt.read(buf, sizeof(buf), littleEndian);

    const DataBuf dataBuf = valueInt.dataArea();

    EXPECT_EQ(dataBuf.pData_, reinterpret_cast<const byte*>(buf));

    EXPECT_EQ(dataBuf.size_, 4); // One int takes 4 bytes

}
