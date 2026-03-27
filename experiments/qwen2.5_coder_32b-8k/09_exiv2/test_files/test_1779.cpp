#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "crwimage_int.hpp"



using namespace Exiv2::Internal;



class CiffComponentTest_1779 : public ::testing::Test {

protected:

    CiffComponent component;

    Blob blob;

    size_t initialOffset = 0;



    void SetUp() override {

        // Set up a default state for the CiffComponent

        uint8_t data[] = {0x01, 0x02, 0x03};

        DataBuf buffer(data, sizeof(data));

        component.setValue(std::move(buffer));

    }

};



TEST_F(CiffComponentTest_1779, WriteValueData_ValueDataLocation_1779) {

    size_t expectedOffset = initialOffset + component.size();

    if (component.size() % 2 == 1) {

        ++expectedOffset;

    }



    size_t resultOffset = component.writeValueData(blob, initialOffset);



    EXPECT_EQ(resultOffset, expectedOffset);

    EXPECT_EQ(blob.size(), expectedOffset);

}



TEST_F(CiffComponentTest_1779, WriteValueData_AlignedSize_1779) {

    uint8_t alignedData[] = {0x01, 0x02, 0x03, 0x04};

    DataBuf buffer(alignedData, sizeof(alignedData));

    component.setValue(std::move(buffer));



    size_t expectedOffset = initialOffset + component.size();

    size_t resultOffset = component.writeValueData(blob, initialOffset);



    EXPECT_EQ(resultOffset, expectedOffset);

    EXPECT_EQ(blob.size(), expectedOffset);

}



TEST_F(CiffComponentTest_1779, WriteValueData_UnalignedSize_AddsPadding_1779) {

    uint8_t data[] = {0x01, 0x02, 0x03};

    DataBuf buffer(data, sizeof(data));

    component.setValue(std::move(buffer));



    size_t expectedOffset = initialOffset + component.size() + 1;

    size_t resultOffset = component.writeValueData(blob, initialOffset);



    EXPECT_EQ(resultOffset, expectedOffset);

    EXPECT_EQ(blob.size(), expectedOffset);

    EXPECT_EQ(blob.back(), 0x00); // Padding byte

}



TEST_F(CiffComponentTest_1779, WriteValueData_EmptyBlob_1779) {

    component.setSize(0);



    size_t resultOffset = component.writeValueData(blob, initialOffset);



    EXPECT_EQ(resultOffset, initialOffset);

    EXPECT_TRUE(blob.empty());

}



TEST_F(CiffComponentTest_1779, WriteValueData_DirectoryDataLocation_NoWrite_1779) {

    testing::NiceMock<testing::StrictMock<class MockCiffComponent>> mockComponent;

    EXPECT_CALL(mockComponent, tagId()).WillRepeatedly(testing::Return(0x00));

    EXPECT_CALL(mockComponent, dataLocation())

        .WillOnce(testing::Return(DataLocId::directoryData));



    size_t resultOffset = mockComponent.writeValueData(blob, initialOffset);



    EXPECT_EQ(resultOffset, initialOffset);

    EXPECT_TRUE(blob.empty());

}
