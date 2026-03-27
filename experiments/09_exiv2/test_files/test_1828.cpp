#include <gtest/gtest.h>

#include "exiv2/photoshop.hpp"



using namespace Exiv2;



class PhotoshopTest_1828 : public ::testing::Test {

protected:

    const byte* psData;

    size_t sizePsData;

    const byte** record;

    uint32_t sizeHdr;

    uint32_t sizeData;



    void SetUp() override {

        // Example setup, replace with actual data if needed

        psData = nullptr; // Assuming null for invalid cases or provide valid test data

        sizePsData = 0;

        record = nullptr;

        sizeHdr = 0;

        sizeData = 0;

    }

};



TEST_F(PhotoshopTest_1828, LocatePreviewIrb_ValidData_1828) {

    // Arrange

    byte testData[] = { /* valid photoshop data */ };

    psData = testData;

    sizePsData = sizeof(testData);



    // Act

    int result = Photoshop().locatePreviewIrb(psData, sizePsData, record, sizeHdr, sizeData);



    // Assert

    EXPECT_GE(result, 0); // Assuming success returns a non-negative value

}



TEST_F(PhotoshopTest_1828, LocatePreviewIrb_NullData_1828) {

    // Arrange

    psData = nullptr;

    sizePsData = 0;



    // Act

    int result = Photoshop().locatePreviewIrb(psData, sizePsData, record, sizeHdr, sizeData);



    // Assert

    EXPECT_LT(result, 0); // Assuming failure returns a negative value

}



TEST_F(PhotoshopTest_1828, LocatePreviewIrb_ZeroSize_1828) {

    // Arrange

    byte testData[] = { /* valid photoshop data */ };

    psData = testData;

    sizePsData = 0;



    // Act

    int result = Photoshop().locatePreviewIrb(psData, sizePsData, record, sizeHdr, sizeData);



    // Assert

    EXPECT_LT(result, 0); // Assuming failure returns a negative value

}



TEST_F(PhotoshopTest_1828, LocatePreviewIrb_ValidSizeButNoRecord_1828) {

    // Arrange

    byte testData[] = { /* invalid photoshop data that does not contain preview IRB */ };

    psData = testData;

    sizePsData = sizeof(testData);



    // Act

    int result = Photoshop().locatePreviewIrb(psData, sizePsData, record, sizeHdr, sizeData);



    // Assert

    EXPECT_LT(result, 0); // Assuming failure returns a negative value

}



TEST_F(PhotoshopTest_1828, LocatePreviewIrb_RecordFound_1828) {

    // Arrange

    byte testData[] = { /* photoshop data containing preview IRB */ };

    psData = testData;

    sizePsData = sizeof(testData);



    // Act

    int result = Photoshop().locatePreviewIrb(psData, sizePsData, record, sizeHdr, sizeData);



    // Assert

    EXPECT_GE(result, 0); // Assuming success returns a non-negative value

    EXPECT_NE(record, nullptr);

    EXPECT_GT(sizeHdr, 0);

    EXPECT_GT(sizeData, 0);

}
