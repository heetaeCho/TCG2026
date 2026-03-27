#include <gtest/gtest.h>

#include "crwimage_int.hpp"



namespace Exiv2 {

    namespace Internal {



TEST_F(CiffComponentTest_1783, SetValueWithEmptyDataBuffer_1783) {

    CiffComponent component;

    DataBuf emptyBuf;

    component.setValue(std::move(emptyBuf));

    EXPECT_EQ(component.size(), 0);

    EXPECT_EQ(component.pData(), nullptr);

}



TEST_F(CiffComponentTest_1783, SetValueWithNonEmptyDataBuffer_1783) {

    CiffComponent component;

    DataBuf buf(5);

    memset(buf.data(0), 0xFF, 5);

    component.setValue(std::move(buf));

    EXPECT_EQ(component.size(), 5);

    EXPECT_NE(component.pData(), nullptr);

}



TEST_F(CiffComponentTest_1783, SetValueWithLargeDataBufferAndDirectoryDataLocation_1783) {

    CiffComponent component;

    component.tag_ = 0x8001; // Assuming this tag has directoryData location

    DataBuf largeBuf(10);

    memset(largeBuf.data(0), 0xFF, 10);

    component.setValue(std::move(largeBuf));

    EXPECT_EQ(component.size(), 10);

    EXPECT_NE(component.pData(), nullptr);

    EXPECT_EQ(component.tag_ & 0xC000, 0); // Check if tag is masked correctly

}



TEST_F(CiffComponentTest_1783, SetValueWithLargeDataBufferAndValueDataLocation_1783) {

    CiffComponent component;

    component.tag_ = 0x4001; // Assuming this tag has valueData location

    DataBuf largeBuf(10);

    memset(largeBuf.data(0), 0xFF, 10);

    component.setValue(std::move(largeBuf));

    EXPECT_EQ(component.size(), 10);

    EXPECT_NE(component.pData(), nullptr);

    EXPECT_EQ(component.tag_ & 0xC000, 0x4000); // Tag should not be masked

}



TEST_F(CiffComponentTest_1783, SetValueWithLargeDataBufferAndBoundaryCondition_1783) {

    CiffComponent component;

    DataBuf largeBuf(8);

    memset(largeBuf.data(0), 0xFF, 8);

    component.setValue(std::move(largeBuf));

    EXPECT_EQ(component.size(), 8);

    EXPECT_NE(component.pData(), nullptr);



    component.tag_ = 0x8001; // Assuming this tag has directoryData location

    DataBuf boundaryBuf(9);

    memset(boundaryBuf.data(0), 0xFF, 9);

    component.setValue(std::move(boundaryBuf));

    EXPECT_EQ(component.size(), 9);

    EXPECT_NE(component.pData(), nullptr);

    EXPECT_EQ(component.tag_ & 0xC000, 0); // Check if tag is masked correctly

}



TEST_F(CiffComponentTest_1783, SetValueWithZeroSizeDataBuffer_1783) {

    CiffComponent component;

    DataBuf zeroSizedBuf(0);

    component.setValue(std::move(zeroSizedBuf));

    EXPECT_EQ(component.size(), 0);

    EXPECT_EQ(component.pData(), nullptr);

}



TEST_F(CiffComponentTest_1783, SetValueMultipleTimes_1783) {

    CiffComponent component;

    DataBuf firstBuf(5);

    memset(firstBuf.data(0), 0xFF, 5);

    component.setValue(std::move(firstBuf));

    EXPECT_EQ(component.size(), 5);

    EXPECT_NE(component.pData(), nullptr);



    DataBuf secondBuf(10);

    memset(secondBuf.data(0), 0x00, 10);

    component.setValue(std::move(secondBuf));

    EXPECT_EQ(component.size(), 10);

    EXPECT_NE(component.pData(), nullptr);

}



    } // namespace Internal

} // namespace Exiv2
