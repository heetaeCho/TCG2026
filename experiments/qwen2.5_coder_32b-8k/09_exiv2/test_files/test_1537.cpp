#include <gtest/gtest.h>

#include "exiv2/makernote_int.hpp"

#include "exiv2/tiffcomposite_int.hpp"



using namespace Exiv2;

using namespace Internal;



class NikonCryptTest_1537 : public ::testing::Test {

protected:

    TiffComponent* pRoot;

    TiffEntryBase* te00a7;

    TiffEntryBase* te001d;

    

    void SetUp() override {

        pRoot = new TiffComponent(0x00a7, IfdId::nikon3Id);

        

        // Mocking data for tag 0x00a7

        te00a7 = new TiffEntryBase(0x00a7, IfdId::nikon3Id, TiffType::unsignedLong);

        auto value00a7 = Value::create(TypeId::uint32);

        value00a7->read(reinterpret_cast<const byte*>("\x11\x22\x33\x44"), 4, littleEndian);

        te00a7->setDataArea(value00a7->dataArea().c_data(), value00a7->sizeDataArea());

        pRoot->addChild(SharedPtr(te00a7));

        

        // Mocking data for tag 0x001d

        te001d = new TiffEntryBase(0x001d, IfdId::nikon3Id, TiffType::unsignedLong);

        auto value001d = Value::create(TypeId::uint32);

        value001d->read(reinterpret_cast<const byte*>("\x55\x66\x77\x88"), 4, littleEndian);

        te001d->setDataArea(value001d->dataArea().c_data(), value001d->sizeDataArea());

        pRoot->addChild(SharedPtr(te001d));

    }



    void TearDown() override {

        delete pRoot;

    }

};



TEST_F(NikonCryptTest_1537, NormalOperation_1537) {

    byte pData[] = { 0x01, 0x02, 0x03, 0x04, 0x05 };

    uint16_t tag = 145;

    size_t size = sizeof(pData);

    

    DataBuf result = nikonCrypt(tag, pData, size, pRoot);



    EXPECT_EQ(result.size(), size);

}



TEST_F(NikonCryptTest_1537, SizeLessThanFour_1537) {

    byte pData[] = { 0x01, 0x02 };

    uint16_t tag = 145;

    size_t size = sizeof(pData);



    DataBuf result = nikonCrypt(tag, pData, size, pRoot);

    

    EXPECT_TRUE(result.empty());

}



TEST_F(NikonCryptTest_1537, TagNotFoundInNikonArrayIdx_1537) {

    byte pData[] = { 0x01, 0x02, 0x03, 0x04 };

    uint16_t tag = 999;

    size_t size = sizeof(pData);



    DataBuf result = nikonCrypt(tag, pData, size, pRoot);

    

    EXPECT_TRUE(result.empty());

}



TEST_F(NikonCryptTest_1537, StartGreaterThanSizeInNikonArrayIdx_1537) {

    byte pData[] = { 0x01, 0x02, 0x03, 0x04 };

    uint16_t tag = 145;

    size_t size = sizeof(pData);



    // Modifying the nikonArrayIdx to have a start value greater than size

    NikonArrayIdx nci = { 145, "0208", 5, 0, 4 };

    

    auto originalNikonArrayIdx = nikonArrayIdx;

    nikonArrayIdx[0] = nci;



    DataBuf result = nikonCrypt(tag, pData, size, pRoot);

    

    EXPECT_TRUE(result.empty());



    // Restore the original array

    nikonArrayIdx = originalNikonArrayIdx;

}



TEST_F(NikonCryptTest_1537, InvalidSerialNumberStringConversion_1537) {

    byte pData[] = { 0x01, 0x02, 0x03, 0x04 };

    uint16_t tag = 145;

    size_t size = sizeof(pData);



    // Mocking data for tag 0x001d with invalid string

    te001d->setDataArea(reinterpret_cast<const byte*>("invalid"), strlen("invalid"));

    

    DataBuf result = nikonCrypt(tag, pData, size, pRoot);

    

    EXPECT_EQ(result.size(), size); // Default serial number is used, so it should not be empty

}



TEST_F(NikonCryptTest_1537, ModelContainsD50_1537) {

    byte pData[] = { 0x01, 0x02, 0x03, 0x04 };

    uint16_t tag = 145;

    size_t size = sizeof(pData);



    // Mocking data for tag 0x001d with invalid string

    te001d->setDataArea(reinterpret_cast<const byte*>("invalid"), strlen("invalid"));



    // Mock getExifModel to return "D50"

    EXPECT_CALL(*this, getExifModel(pRoot)).WillOnce(testing::Return("D50"));

    

    DataBuf result = nikonCrypt(tag, pData, size, pRoot);

    

    EXPECT_EQ(result.size(), size); // Default serial number for D50 is used

}



TEST_F(NikonCryptTest_1537, ModelDoesNotContainD50_1537) {

    byte pData[] = { 0x01, 0x02, 0x03, 0x04 };

    uint16_t tag = 145;

    size_t size = sizeof(pData);



    // Mocking data for tag 0x001d with invalid string

    te001d->setDataArea(reinterpret_cast<const byte*>("invalid"), strlen("invalid"));



    // Mock getExifModel to return "D750"

    EXPECT_CALL(*this, getExifModel(pRoot)).WillOnce(testing::Return("D750"));

    

    DataBuf result = nikonCrypt(tag, pData, size, pRoot);

    

    EXPECT_EQ(result.size(), size); // Default serial number for non-D50 models is used

}



// Mock function to override getExifModel behavior

std::string NikonCryptTest_1537::getExifModel(TiffComponent* pRoot) {

    return "D50";  // This will be overridden in specific tests

}
