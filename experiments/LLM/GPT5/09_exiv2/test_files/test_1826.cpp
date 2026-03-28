#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "photoshop.hpp"  // Include the appropriate header for the Photoshop class.

using namespace Exiv2;

// Mock external dependencies if needed.
class MockHandler {
public:
    MOCK_METHOD(void, handleError, (int errorCode), ());
};

// Test fixture for Photoshop class
class PhotoshopTest : public ::testing::Test {
protected:
    PhotoshopTest() {}

    // Setup and teardown can be placed here if necessary.
};

// Test for normal operation: valid Photoshop data with matching psTag.
TEST_F(PhotoshopTest, LocateIrb_ValidData_MatchingTag) {
    const uint16_t psTag = 1234;
    const byte psData[] = { /* Valid Photoshop data with a matching tag */ };
    const size_t sizePsData = sizeof(psData);
    
    const byte* record = nullptr;
    uint32_t sizeHdr = 0, sizeData = 0;

    int result = Photoshop::locateIrb(psData, sizePsData, psTag, &record, sizeHdr, sizeData);

    EXPECT_EQ(result, 0);  // Expect success (0)
    EXPECT_NE(record, nullptr);  // Ensure a record is found.
    EXPECT_GT(sizeHdr, 0);  // Ensure sizeHdr is set.
    EXPECT_GT(sizeData, 0);  // Ensure sizeData is set.
}

// Test for boundary condition: Photoshop data too small.
TEST_F(PhotoshopTest, LocateIrb_DataTooSmall) {
    const uint16_t psTag = 1234;
    const byte psData[] = {};  // Empty data
    const size_t sizePsData = sizeof(psData);

    const byte* record = nullptr;
    uint32_t sizeHdr = 0, sizeData = 0;

    int result = Photoshop::locateIrb(psData, sizePsData, psTag, &record, sizeHdr, sizeData);

    EXPECT_EQ(result, 3);  // Expect failure due to insufficient data
}

// Test for boundary condition: Invalid Photoshop data (too short to contain IRB).
TEST_F(PhotoshopTest, LocateIrb_InvalidData) {
    const uint16_t psTag = 1234;
    const byte psData[] = {0x00, 0x01, 0x02};  // Invalid Photoshop data
    const size_t sizePsData = sizeof(psData);

    const byte* record = nullptr;
    uint32_t sizeHdr = 0, sizeData = 0;

    int result = Photoshop::locateIrb(psData, sizePsData, psTag, &record, sizeHdr, sizeData);

    EXPECT_EQ(result, -2);  // Expect failure due to invalid data.
}

// Test for boundary condition: Valid data but no matching psTag.
TEST_F(PhotoshopTest, LocateIrb_ValidData_NoMatchingTag) {
    const uint16_t psTag = 1234;
    const byte psData[] = { /* Valid Photoshop data but with a different tag */ };
    const size_t sizePsData = sizeof(psData);

    const byte* record = nullptr;
    uint32_t sizeHdr = 0, sizeData = 0;

    int result = Photoshop::locateIrb(psData, sizePsData, psTag, &record, sizeHdr, sizeData);

    EXPECT_EQ(result, 3);  // Expect failure due to no matching tag.
}

// Test for exceptional condition: Data size is too large for IRB.
TEST_F(PhotoshopTest, LocateIrb_DataSizeTooLarge) {
    const uint16_t psTag = 1234;
    const byte psData[] = { /* Valid data, but with a data size too large to handle */ };
    const size_t sizePsData = sizeof(psData);

    const byte* record = nullptr;
    uint32_t sizeHdr = 0, sizeData = 0;

    int result = Photoshop::locateIrb(psData, sizePsData, psTag, &record, sizeHdr, sizeData);

    EXPECT_EQ(result, -2);  // Expect failure due to invalid data size.
}

// Test for verifying external interaction: Mock handler for error notification.
TEST_F(PhotoshopTest, LocateIrb_ErrorHandling_NotifyHandler) {
    const uint16_t psTag = 1234;
    const byte psData[] = {0x00, 0x01};  // Invalid data to trigger an error
    const size_t sizePsData = sizeof(psData);

    MockHandler handler;
    EXPECT_CALL(handler, handleError(-2));  // Expect the error handler to be called for error code -2

    const byte* record = nullptr;
    uint32_t sizeHdr = 0, sizeData = 0;
    int result = Photoshop::locateIrb(psData, sizePsData, psTag, &record, sizeHdr, sizeData);

    EXPECT_EQ(result, -2);  // Expect failure due to invalid data.
}