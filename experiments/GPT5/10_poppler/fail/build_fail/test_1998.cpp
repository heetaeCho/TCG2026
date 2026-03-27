#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstring>  // For memcpy

// Mock the JPXData structure used in the callback function
struct JPXData {
    const unsigned char* data;
    OPJ_SIZE_T size;
    OPJ_SIZE_T pos;
};

extern "C" {
    typedef unsigned int OPJ_SIZE_T; // Define OPJ_SIZE_T for simulation
    static OPJ_SIZE_T jpxRead_callback(void *p_buffer, OPJ_SIZE_T p_nb_bytes, void *p_user_data) {
        auto *jpxData = (JPXData *)p_user_data;
        if (unlikely(jpxData->size <= jpxData->pos)) {
            return (OPJ_SIZE_T)-1; // End of file
        }
        OPJ_SIZE_T len = jpxData->size - jpxData->pos;
        if (len > p_nb_bytes) {
            len = p_nb_bytes;
        }
        memcpy(p_buffer, jpxData->data + jpxData->pos, len);
        jpxData->pos += len;
        return len;
    }
}

class JPEG2000StreamTest : public ::testing::Test {
protected:
    // Test setup
    JPXData* jpxData;
    unsigned char testData[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    void SetUp() override {
        jpxData = new JPXData();
        jpxData->data = testData;
        jpxData->size = sizeof(testData);
        jpxData->pos = 0;
    }

    void TearDown() override {
        delete jpxData;
    }
};

// Test normal operation: the callback reads part of the data
TEST_F(JPEG2000StreamTest, jpxRead_callback_ReadsDataCorrectly_1998) {
    unsigned char buffer[5];
    OPJ_SIZE_T bytesRead = jpxRead_callback(buffer, 5, jpxData);
    
    EXPECT_EQ(bytesRead, 5);
    EXPECT_EQ(memcmp(buffer, testData, 5), 0);
    EXPECT_EQ(jpxData->pos, 5);  // Position should have moved forward by 5 bytes
}

// Test boundary case: Read more than available data
TEST_F(JPEG2000StreamTest, jpxRead_callback_ReadsAllData_1999) {
    unsigned char buffer[15];  // Buffer larger than data
    OPJ_SIZE_T bytesRead = jpxRead_callback(buffer, 15, jpxData);
    
    EXPECT_EQ(bytesRead, 10);  // Only 10 bytes available
    EXPECT_EQ(memcmp(buffer, testData, 10), 0);
    EXPECT_EQ(jpxData->pos, 10);  // All data should have been read
}

// Test exceptional case: Reading beyond the end of data
TEST_F(JPEG2000StreamTest, jpxRead_callback_ReadsBeyondEnd_2000) {
    unsigned char buffer[5];
    jpxData->pos = 10;  // Position is at the end
    
    OPJ_SIZE_T bytesRead = jpxRead_callback(buffer, 5, jpxData);
    
    EXPECT_EQ(bytesRead, (OPJ_SIZE_T)-1);  // End of file, should return -1
    EXPECT_EQ(jpxData->pos, 10);  // Position should remain the same
}

// Test boundary condition: No data to read (empty stream)
TEST_F(JPEG2000StreamTest, jpxRead_callback_EmptyData_2001) {
    unsigned char buffer[5];
    jpxData->size = 0;  // No data in the stream
    
    OPJ_SIZE_T bytesRead = jpxRead_callback(buffer, 5, jpxData);
    
    EXPECT_EQ(bytesRead, (OPJ_SIZE_T)-1);  // End of file, should return -1
    EXPECT_EQ(jpxData->pos, 0);  // Position should still be 0
}