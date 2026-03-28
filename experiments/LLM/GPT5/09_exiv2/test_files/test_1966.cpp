#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "XMPMeta-Parse.hpp"
#include "XMPUtils.hpp"
#include "XMPCore_Impl.hpp"

// Mock classes
class MockXMPNode : public XMP_Node {
public:
    MockXMPNode(XMP_Node* parent, const XMP_VarString& name, XMP_OptionBits options) 
        : XMP_Node(parent, name, options) {}

    MOCK_METHOD(void, RemoveChildren, (), (override));
    MOCK_METHOD(void, RemoveQualifiers, (), (override));
    MOCK_METHOD(void, ClearNode, (), (override));
};

// Test Fixture
class FixGPSTimeStampTest : public ::testing::Test {
protected:
    XMP_Node* exifSchema;
    XMP_Node* gpsDateTime;
    MockXMPNode* mockExifSchema;
    MockXMPNode* mockGpsDateTime;

    void SetUp() override {
        mockExifSchema = new MockXMPNode(nullptr, "exif:Schema", 0);
        mockGpsDateTime = new MockXMPNode(mockExifSchema, "gps:DateTime", 0);
        exifSchema = mockExifSchema;
        gpsDateTime = mockGpsDateTime;
    }

    void TearDown() override {
        delete mockExifSchema;
        delete mockGpsDateTime;
    }
};

// Normal operation test: Test for successful GPS timestamp fix
TEST_F(FixGPSTimeStampTest, FixGPSTimeStamp_Success_1966) {
    XMP_DateTime gpsBinTime = {2021, 5, 17, 12, 30, 45, 0, 0, 0, 0};
    XMP_DateTime originalDate = {2021, 5, 17, 0, 0, 0, 0, 0, 0, 0};

    // Mock the conversion methods to simulate correct date parsing
    EXPECT_CALL(*mockGpsDateTime, value).WillOnce(testing::Return("2021-05-17T12:30:45"));
    EXPECT_CALL(*mockExifSchema, RemoveChildren()).Times(1);

    // Simulate the conversion logic and GPS timestamp fix.
    FixGPSTimeStamp(exifSchema, gpsDateTime);

    // Check that the value of gpsDateTime has been updated to the new value
    EXPECT_EQ(gpsDateTime->value, "2021-05-17T12:30:45");
}

// Boundary test: Invalid GPS timestamp (should not change the value)
TEST_F(FixGPSTimeStampTest, FixGPSTimeStamp_InvalidGPS_1966) {
    XMP_DateTime gpsBinTime = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    
    // Simulate invalid GPS timestamp
    EXPECT_CALL(*mockGpsDateTime, value).WillOnce(testing::Return("0000-00-00T00:00:00"));

    // Expect that no changes occur in the GPS DateTime
    EXPECT_CALL(*mockExifSchema, RemoveChildren()).Times(0);

    // Simulate the conversion logic for an invalid GPS timestamp
    FixGPSTimeStamp(exifSchema, gpsDateTime);

    // The timestamp value should not change
    EXPECT_EQ(gpsDateTime->value, "0000-00-00T00:00:00");
}

// Test for the scenario where no other date is found (otherDate == nullptr)
TEST_F(FixGPSTimeStampTest, FixGPSTimeStamp_NoOtherDate_1966) {
    // Mock the conversion methods for GPS and EXIF date
    EXPECT_CALL(*mockExifSchema, RemoveChildren()).Times(0);

    // Simulate GPS DateTime being valid but no other date to fall back to
    EXPECT_CALL(*mockGpsDateTime, value).WillOnce(testing::Return("2021-05-17T12:30:45"));

    // Call function and ensure no change happens as no other date is found
    FixGPSTimeStamp(exifSchema, gpsDateTime);

    // Assert no changes to gpsDateTime
    EXPECT_EQ(gpsDateTime->value, "2021-05-17T12:30:45");
}

// Error case: Conversion throws exception
TEST_F(FixGPSTimeStampTest, FixGPSTimeStamp_ConvertToDateThrows_1966) {
    EXPECT_CALL(*mockGpsDateTime, value).WillOnce(testing::Return("invalid date"));

    // Simulate exception thrown by ConvertToDate
    EXPECT_THROW(FixGPSTimeStamp(exifSchema, gpsDateTime), std::exception);
}

// Test for invalid input: Test that function gracefully handles null nodes
TEST_F(FixGPSTimeStampTest, FixGPSTimeStamp_NullNodes_1966) {
    XMP_Node* nullExifSchema = nullptr;
    XMP_Node* nullGpsDateTime = nullptr;

    // Expect that no error occurs for null nodes (simply return)
    EXPECT_NO_THROW(FixGPSTimeStamp(nullExifSchema, nullGpsDateTime));
}