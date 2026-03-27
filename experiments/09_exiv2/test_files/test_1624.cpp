#include <gtest/gtest.h>

#include <gmock/gmock.h>



namespace Exiv2 { namespace Internal {

    static DataBuf sonyTagCipher(uint16_t /* tag */, const byte* bytes, size_t size, const TiffComponent* /*object*/, bool bDecipher);

}}



using namespace Exiv2::Internal;

using ::testing::ElementsAre;



class SonyTagCipherTest_1624 : public ::testing::Test {

protected:

    std::vector<byte> testData = {0, 1, 2, 3, 248, 249, 250, 251, 252, 253, 254, 255};

};



TEST_F(SonyTagCipherTest_1624, CipherAndDecipherIdentity_1624) {

    DataBuf original(testData.data(), testData.size());

    TiffComponent* dummyObject = nullptr;



    // Encrypt the data

    DataBuf encrypted = sonyTagCipher(0, original.pData_, original.size_, dummyObject, false);



    // Decrypt the data

    DataBuf decrypted = sonyTagCipher(0, encrypted.pData_, encrypted.size_, dummyObject, true);



    // Verify that the decrypted data matches the original

    EXPECT_EQ(original, decrypted);

}



TEST_F(SonyTagCipherTest_1624, CipherEmptyData_1624) {

    std::vector<byte> emptyData;

    DataBuf original(emptyData.data(), emptyData.size());

    TiffComponent* dummyObject = nullptr;



    // Encrypt the data

    DataBuf encrypted = sonyTagCipher(0, original.pData_, original.size_, dummyObject, false);



    // Verify that the encrypted data is also empty

    EXPECT_EQ(original, encrypted);

}



TEST_F(SonyTagCipherTest_1624, DecipherEmptyData_1624) {

    std::vector<byte> emptyData;

    DataBuf original(emptyData.data(), emptyData.size());

    TiffComponent* dummyObject = nullptr;



    // Decrypt the data

    DataBuf decrypted = sonyTagCipher(0, original.pData_, original.size_, dummyObject, true);



    // Verify that the decrypted data is also empty

    EXPECT_EQ(original, decrypted);

}



TEST_F(SonyTagCipherTest_1624, CipherSingleByte_1624) {

    std::vector<byte> singleByteData = {42};

    DataBuf original(singleByteData.data(), singleByteData.size());

    TiffComponent* dummyObject = nullptr;



    // Encrypt the data

    DataBuf encrypted = sonyTagCipher(0, original.pData_, original.size_, dummyObject, false);



    // Verify that the encrypted data is of the same size

    EXPECT_EQ(original.size_, encrypted.size_);

}



TEST_F(SonyTagCipherTest_1624, DecipherSingleByte_1624) {

    std::vector<byte> singleByteData = {42};

    DataBuf original(singleByteData.data(), singleByteData.size());

    TiffComponent* dummyObject = nullptr;



    // Decrypt the data

    DataBuf decrypted = sonyTagCipher(0, original.pData_, original.size_, dummyObject, true);



    // Verify that the decrypted data is of the same size

    EXPECT_EQ(original.size_, decrypted.size_);

}



TEST_F(SonyTagCipherTest_1624, CipherBoundaryValues_1624) {

    std::vector<byte> boundaryValues = {0, 248, 249, 250, 251, 252, 253, 254, 255};

    DataBuf original(boundaryValues.data(), boundaryValues.size());

    TiffComponent* dummyObject = nullptr;



    // Encrypt the data

    DataBuf encrypted = sonyTagCipher(0, original.pData_, original.size_, dummyObject, false);



    // Verify that the encrypted data is of the same size

    EXPECT_EQ(original.size_, encrypted.size_);

}



TEST_F(SonyTagCipherTest_1624, DecipherBoundaryValues_1624) {

    std::vector<byte> boundaryValues = {0, 248, 249, 250, 251, 252, 253, 254, 255};

    DataBuf original(boundaryValues.data(), boundaryValues.size());

    TiffComponent* dummyObject = nullptr;



    // Decrypt the data

    DataBuf decrypted = sonyTagCipher(0, original.pData_, original.size_, dummyObject, true);



    // Verify that the decrypted data is of the same size

    EXPECT_EQ(original.size_, decrypted.size_);

}
