#include <gtest/gtest.h>

#include <asf/asf.h> // Assuming necessary header files are included



using namespace std;



// Test fixture for AsfHeaderExtension class

class AsfHeaderExtensionTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize any objects or variables needed for the tests here

    }



    void TearDown() override {

        // Clean up any resources used by the tests here

    }

};



// Test case to check if the GUID matches a known GUID from GUIDReference

TEST_F(AsfHeaderExtensionTest, CheckGUIDKnownValue) {

    DataReader dataReader;

    Asf::AsfFile asfFile;

    Asf::AsfHeaderExtension headerExtension(dataReader, asfFile);

    

    // Example GUID for testing (Stream_Properties)

    uint8_t guidData[16] = {0x91, 0x07, 0xD9, 0xB7, 0x4A, 0xCB, 0x43, 0xD4,

                            0x80, 0xE5, 0xA8, 0x6B, 0xF1, 0xBF, 0x4E, 0x8F};

    DataReader guidReader(guidData, sizeof(guidData));

    

    // Create GUID object

    GUID guid = guidReader.ReadGUID();

    

    EXPECT_EQ(guidReference[Stream_Properties], guid);

}



// Test case to check the parsing of an unknown GUID

TEST_F(AsfHeaderExtensionTest, CheckUnknownGUID) {

    DataReader dataReader;

    Asf::AsfFile asfFile;

    Asf::AsfHeaderExtension headerExtension(dataReader, asfFile);



    // Example GUID for testing (unknown)

    uint8_t guidData[16] = {0x91, 0x07, 0xD9, 0xB7, 0x4A, 0xCB, 0x43, 0xD4,

                            0x80, 0xE5, 0xA8, 0x6B, 0xF1, 0xBF, 0x4E, 0x9F};

    DataReader guidReader(guidData, sizeof(guidData));



    // Create GUID object

    GUID guid = guidReader.ReadGUID();



    EXPECT_EQ(guidReference.end(), guidReference.find(guid));

}



// Test case to check if the size of the GUID is correctly handled

TEST_F(AsfHeaderExtensionTest, CheckGUIDSize) {

    DataReader dataReader;

    Asf::AsfFile asfFile;

    Asf::AsfHeaderExtension headerExtension(dataReader, asfFile);



    // Example GUID for testing with incorrect size (should be 16 bytes)

    uint8_t guidData[15] = {0x91, 0x07, 0xD9, 0xB7, 0x4A, 0xCB, 0x43, 0xD4,

                            0x80, 0xE5, 0xA8, 0x6B, 0xF1, 0xBF, 0x4E};

    DataReader guidReader(guidData, sizeof(guidData));



    // Create GUID object

    GUID guid = guidReader.ReadGUID();



    EXPECT_EQ(false, guid.IsValid());

}



// Test case to check if the AsfHeaderExtension class reads the correct data size

TEST_F(AsfHeaderExtensionTest, CheckCorrectDataSize) {

    DataReader dataReader;

    Asf::AsfFile asfFile;

    Asf::AsfHeaderExtension headerExtension(dataReader, asfFile);



    // Mock data for testing with known data size (assuming 32 bytes of data)

    uint8_t testData[40] = { /* GUID data (16 bytes) */

                            0x91, 0x07, 0xD9, 0xB7, 0x4A, 0xCB, 0x43, 0xD4,

                            0x80, 0xE5, 0xA8, 0x6B, 0xF1, 0xBF, 0x4E, 0x8F,

                            /* Data Size (4 bytes) */

                            0x20, 0x00, 0x00, 0x00,

                            /* Additional data (16 bytes) */

                            0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,

                            0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10 };

    DataReader testDataReader(testData, sizeof(testData));



    // Parse the header extension

    Asf::AsfHeaderExtension testHeaderExtension(testDataReader, asfFile);



    EXPECT_EQ(32u, testHeaderExtension.GetDataSize());

}



// Test case to check if the AsfHeaderExtension class reads the correct GUID reference type

TEST_F(AsfHeaderExtensionTest, CheckGUIDReferenceType) {

    DataReader dataReader;

    Asf::AsfFile asfFile;

    Asf::AsfHeaderExtension headerExtension(dataReader, asfFile);



    // Mock data for testing with known GUID (Stream_Properties)

    uint8_t testData[20] = { /* GUID data (16 bytes) */

                            0x91, 0x07, 0xD9, 0xB7, 0x4A, 0xCB, 0x43, 0xD4,

                            0x80, 0xE5, 0xA8, 0x6B, 0xF1, 0xBF, 0x4E, 0x8F,

                            /* Data Size (4 bytes) */

                            0x20, 0x00, 0x00, 0x00 };

    DataReader testDataReader(testData, sizeof(testData));



    // Parse the header extension

    Asf::AsfHeaderExtension testHeaderExtension(testDataReader, asfFile);



    EXPECT_EQ(Stream_Properties, testHeaderExtension.GetGUIDReferenceType());

}



// Test case to check if the AsfHeaderExtension class handles a GUID that is too small

TEST_F(AsfHeaderExtensionTest, CheckTooSmallGUID) {

    DataReader dataReader;

    Asf::AsfFile asfFile;

    Asf::AsfHeaderExtension headerExtension(dataReader, asfFile);



    // Mock data for testing with known GUID (too short)

    uint8_t testData[20] = { /* GUID data (15 bytes) */

                            0x91, 0x07, 0xD9, 0xB7, 0x4A, 0xCB, 0x43, 0xD4,

                            0x80, 0xE5, 0xA8, 0x6B, 0xF1, 0xBF, 0x4E,

                            /* Data Size (4 bytes) */

                            0x20, 0x00, 0x00, 0x00 };

    DataReader testDataReader(testData, sizeof(testData));



    // Parse the header extension

    Asf::AsfHeaderExtension testHeaderExtension(testDataReader, asfFile);



    EXPECT_EQ(false, testHeaderExtension.GetGUID().IsValid());

}



// Test case to check if the AsfHeaderExtension class handles a GUID that is too large

TEST_F(AsfHeaderExtensionTest, CheckTooLargeGUID) {

    DataReader dataReader;

    Asf::AsfFile asfFile;

    Asf::AsfHeaderExtension headerExtension(dataReader, asfFile);



    // Mock data for testing with known GUID (too long)

    uint8_t testData[24] = { /* GUID data (17 bytes) */

                            0x91, 0x07, 0xD9, 0xB7, 0x4A, 0xCB, 0x43, 0xD4,

                            0x80, 0xE5, 0xA8, 0x6B, 0xF1, 0xBF, 0x4E, 0x8F,

                            0xFF,

                            /* Data Size (4 bytes) */

                            0x20, 0x00, 0x00, 0x00 };

    DataReader testDataReader(testData, sizeof(testData));



    // Parse the header extension

    Asf::AsfHeaderExtension testHeaderExtension(testDataReader, asfFile);



    EXPECT_EQ(false, testHeaderExtension.GetGUID().IsValid());

}



// Test case to check if the GUID is correctly read from DataReader

TEST_F(AsfHeaderExtensionTest, CheckReadGUID) {

    DataReader dataReader;

    Asf::AsfFile asfFile;

    Asf::AsfHeaderExtension headerExtension(dataReader, asfFile);



    // Mock data for testing with known GUID (Stream_Properties)

    uint8_t testData[20] = { /* GUID data (16 bytes) */

                            0x91, 0x07, 0xD9, 0xB7, 0x4A, 0xCB, 0x43, 0xD4,

                            0x80, 0xE5, 0xA8, 0x6B, 0xF1, 0xBF, 0x4E, 0x8F,

                            /* Data Size (4 bytes) */

                            0x20, 0x00, 0x00, 0x00 };

    DataReader testDataReader(testData, sizeof(testData));



    // Parse the header extension

    Asf::AsfHeaderExtension testHeaderExtension(testDataReader, asfFile);



    GUID expectedGUID = guidReference[Stream_Properties];

    EXPECT_EQ(expectedGUID, testHeaderExtension.GetGUID());

}
