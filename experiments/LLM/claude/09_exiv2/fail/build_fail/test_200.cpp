#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// Include the internal header for PentaxMakerNote
#include "pentaxmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class PentaxShutterCountTest_200 : public ::testing::Test {
protected:
    std::ostringstream os;

    // Helper to create a Value with specified byte components
    std::unique_ptr<Value> createUndefinedValue(const std::vector<uint8_t>& bytes) {
        auto val = Value::create(undefinedId);
        val->read(bytes.data(), bytes.size(), bigEndian);
        return val;
    }

    // Helper to set up date entry in ExifData using string representation
    void setDateEntry(ExifData& exifData, const std::string& keyStr, const std::vector<uint8_t>& bytes) {
        auto val = Value::create(undefinedId);
        val->read(bytes.data(), bytes.size(), bigEndian);
        exifData.add(ExifKey(keyStr), val.get());
    }

    void setTimeEntry(ExifData& exifData, const std::string& keyStr, const std::vector<uint8_t>& bytes) {
        auto val = Value::create(undefinedId);
        val->read(bytes.data(), bytes.size(), bigEndian);
        exifData.add(ExifKey(keyStr), val.get());
    }
};

// Test: nullptr metadata returns "undefined"
TEST_F(PentaxShutterCountTest_200, NullMetadataReturnsUndefined_200) {
    auto value = createUndefinedValue({0x00, 0x00, 0x00, 0x01});
    PentaxMakerNote::printShutterCount(os, *value, nullptr);
    EXPECT_EQ(os.str(), "undefined");
}

// Test: Missing date and time entries returns "undefined"
TEST_F(PentaxShutterCountTest_200, MissingDateAndTimeReturnsUndefined_200) {
    ExifData exifData;
    auto value = createUndefinedValue({0x00, 0x00, 0x00, 0x01});
    PentaxMakerNote::printShutterCount(os, *value, &exifData);
    EXPECT_EQ(os.str(), "undefined");
}

// Test: Missing date entry only returns "undefined"
TEST_F(PentaxShutterCountTest_200, MissingDateReturnsUndefined_200) {
    ExifData exifData;
    setTimeEntry(exifData, "Exif.Pentax.Time", {0x0A, 0x1E, 0x00});
    auto value = createUndefinedValue({0x00, 0x00, 0x00, 0x01});
    PentaxMakerNote::printShutterCount(os, *value, &exifData);
    EXPECT_EQ(os.str(), "undefined");
}

// Test: Missing time entry only returns "undefined"
TEST_F(PentaxShutterCountTest_200, MissingTimeReturnsUndefined_200) {
    ExifData exifData;
    setDateEntry(exifData, "Exif.Pentax.Date", {0x07, 0xE1, 0x06, 0x0F});
    auto value = createUndefinedValue({0x00, 0x00, 0x00, 0x01});
    PentaxMakerNote::printShutterCount(os, *value, &exifData);
    EXPECT_EQ(os.str(), "undefined");
}

// Test: Date with wrong size (not 4 bytes) returns "undefined"
TEST_F(PentaxShutterCountTest_200, DateWrongSizeReturnsUndefined_200) {
    ExifData exifData;
    setDateEntry(exifData, "Exif.Pentax.Date", {0x07, 0xE1, 0x06});  // 3 bytes instead of 4
    setTimeEntry(exifData, "Exif.Pentax.Time", {0x0A, 0x1E, 0x00});
    auto value = createUndefinedValue({0x00, 0x00, 0x00, 0x01});
    PentaxMakerNote::printShutterCount(os, *value, &exifData);
    EXPECT_EQ(os.str(), "undefined");
}

// Test: Time with wrong size (not 3 bytes) returns "undefined"
TEST_F(PentaxShutterCountTest_200, TimeWrongSizeReturnsUndefined_200) {
    ExifData exifData;
    setDateEntry(exifData, "Exif.Pentax.Date", {0x07, 0xE1, 0x06, 0x0F});
    setTimeEntry(exifData, "Exif.Pentax.Time", {0x0A, 0x1E, 0x00, 0x00});  // 4 bytes instead of 3
    auto value = createUndefinedValue({0x00, 0x00, 0x00, 0x01});
    PentaxMakerNote::printShutterCount(os, *value, &exifData);
    EXPECT_EQ(os.str(), "undefined");
}

// Test: Value with wrong size (not 4 bytes) returns "undefined"
TEST_F(PentaxShutterCountTest_200, ValueWrongSizeReturnsUndefined_200) {
    ExifData exifData;
    setDateEntry(exifData, "Exif.Pentax.Date", {0x07, 0xE1, 0x06, 0x0F});
    setTimeEntry(exifData, "Exif.Pentax.Time", {0x0A, 0x1E, 0x00});
    auto value = createUndefinedValue({0x00, 0x00, 0x01});  // 3 bytes instead of 4
    PentaxMakerNote::printShutterCount(os, *value, &exifData);
    EXPECT_EQ(os.str(), "undefined");
}

// Test: Valid data using Exif.Pentax.Date and Exif.Pentax.Time produces a numeric result
TEST_F(PentaxShutterCountTest_200, ValidPentaxDateTimeProducesCount_200) {
    ExifData exifData;
    setDateEntry(exifData, "Exif.Pentax.Date", {0x07, 0xE1, 0x06, 0x0F});
    setTimeEntry(exifData, "Exif.Pentax.Time", {0x0A, 0x1E, 0x00});
    auto value = createUndefinedValue({0x00, 0x00, 0x00, 0x00});
    PentaxMakerNote::printShutterCount(os, *value, &exifData);
    // The result should be a number (the XOR computation)
    std::string result = os.str();
    EXPECT_NE(result, "undefined");
    // Verify it's a valid number
    EXPECT_NO_THROW(std::stoul(result));
}

// Test: Valid data using Exif.PentaxDng.Date and Exif.PentaxDng.Time
TEST_F(PentaxShutterCountTest_200, ValidPentaxDngDateTimeProducesCount_200) {
    ExifData exifData;
    setDateEntry(exifData, "Exif.PentaxDng.Date", {0x07, 0xE1, 0x06, 0x0F});
    setTimeEntry(exifData, "Exif.PentaxDng.Time", {0x0A, 0x1E, 0x00});
    auto value = createUndefinedValue({0x00, 0x00, 0x00, 0x00});
    PentaxMakerNote::printShutterCount(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_NE(result, "undefined");
}

// Test: Verify the XOR computation with known values
TEST_F(PentaxShutterCountTest_200, VerifyXorComputation_200) {
    ExifData exifData;
    // date = (0 << 24) + (0 << 16) + (0 << 8) + (0 << 0) = 0x00000000
    setDateEntry(exifData, "Exif.Pentax.Date", {0x00, 0x00, 0x00, 0x00});
    // time = (0 << 24) + (0 << 16) + (0 << 8) = 0x00000000
    setTimeEntry(exifData, "Exif.Pentax.Time", {0x00, 0x00, 0x00});
    // countEnc = 0x00000000
    // count = 0x00000000 ^ 0x00000000 ^ (~0x00000000)
    // ~0x00000000 = 0xFFFFFFFF
    // count = 0xFFFFFFFF = 4294967295
    auto value = createUndefinedValue({0x00, 0x00, 0x00, 0x00});
    PentaxMakerNote::printShutterCount(os, *value, &exifData);
    EXPECT_EQ(os.str(), std::to_string(0xFFFFFFFF));
}

// Test: Another specific XOR computation verification
TEST_F(PentaxShutterCountTest_200, VerifyXorComputationSpecific_200) {
    ExifData exifData;
    // date = (0x07 << 24) | (0xE1 << 16) | (0x06 << 8) | 0x0F = 0x07E1060F
    setDateEntry(exifData, "Exif.Pentax.Date", {0x07, 0xE1, 0x06, 0x0F});
    // time = (0x0A << 24) | (0x1E << 16) | (0x00 << 8) = 0x0A1E0000
    setTimeEntry(exifData, "Exif.Pentax.Time", {0x0A, 0x1E, 0x00});

    uint32_t date = 0x07E1060F;
    uint32_t time = 0x0A1E0000;
    uint32_t countEnc = 0x12345678;
    uint32_t expectedCount = countEnc ^ date ^ (~time);

    auto value = createUndefinedValue({0x12, 0x34, 0x56, 0x78});
    PentaxMakerNote::printShutterCount(os, *value, &exifData);
    EXPECT_EQ(os.str(), std::to_string(expectedCount));
}

// Test: PentaxDng.Date takes priority over Pentax.Date when both exist
TEST_F(PentaxShutterCountTest_200, PentaxDngDateTakesPriority_200) {
    ExifData exifData;
    // Add PentaxDng.Date first
    setDateEntry(exifData, "Exif.PentaxDng.Date", {0x01, 0x02, 0x03, 0x04});
    // Add Pentax.Date second (should be ignored)
    setDateEntry(exifData, "Exif.Pentax.Date", {0x05, 0x06, 0x07, 0x08});
    setTimeEntry(exifData, "Exif.Pentax.Time", {0x0A, 0x0B, 0x0C});

    uint32_t date = 0x01020304;  // PentaxDng.Date should be used
    uint32_t time = 0x0A0B0C00;
    uint32_t countEnc = 0xAABBCCDD;
    uint32_t expectedCount = countEnc ^ date ^ (~time);

    auto value = createUndefinedValue({0xAA, 0xBB, 0xCC, 0xDD});
    PentaxMakerNote::printShutterCount(os, *value, &exifData);
    EXPECT_EQ(os.str(), std::to_string(expectedCount));
}

// Test: PentaxDng.Time takes priority over Pentax.Time when both exist
TEST_F(PentaxShutterCountTest_200, PentaxDngTimeTakesPriority_200) {
    ExifData exifData;
    setDateEntry(exifData, "Exif.Pentax.Date", {0x01, 0x02, 0x03, 0x04});
    // Add PentaxDng.Time first
    setTimeEntry(exifData, "Exif.PentaxDng.Time", {0x0A, 0x0B, 0x0C});
    // Add Pentax.Time second (should be ignored)
    setTimeEntry(exifData, "Exif.Pentax.Time", {0x0D, 0x0E, 0x0F});

    uint32_t date = 0x01020304;
    uint32_t time = 0x0A0B0C00;  // PentaxDng.Time should be used
    uint32_t countEnc = 0x11223344;
    uint32_t expectedCount = countEnc ^ date ^ (~time);

    auto value = createUndefinedValue({0x11, 0x22, 0x33, 0x44});
    PentaxMakerNote::printShutterCount(os, *value, &exifData);
    EXPECT_EQ(os.str(), std::to_string(expectedCount));
}

// Test: Returns reference to the same ostream
TEST_F(PentaxShutterCountTest_200, ReturnsOstreamReference_200) {
    auto value = createUndefinedValue({0x00, 0x00, 0x00, 0x01});
    std::ostream& result = PentaxMakerNote::printShutterCount(os, *value, nullptr);
    EXPECT_EQ(&result, &os);
}

// Test: Returns ostream reference on valid data too
TEST_F(PentaxShutterCountTest_200, ReturnsOstreamReferenceOnValidData_200) {
    ExifData exifData;
    setDateEntry(exifData, "Exif.Pentax.Date", {0x07, 0xE1, 0x06, 0x0F});
    setTimeEntry(exifData, "Exif.Pentax.Time", {0x0A, 0x1E, 0x00});
    auto value = createUndefinedValue({0x00, 0x00, 0x00, 0x00});
    std::ostream& result = PentaxMakerNote::printShutterCount(os, *value, &exifData);
    EXPECT_EQ(&result, &os);
}

// Test: All bytes 0xFF
TEST_F(PentaxShutterCountTest_200, AllMaxBytes_200) {
    ExifData exifData;
    setDateEntry(exifData, "Exif.Pentax.Date", {0xFF, 0xFF, 0xFF, 0xFF});
    setTimeEntry(exifData, "Exif.Pentax.Time", {0xFF, 0xFF, 0xFF});
    auto value = createUndefinedValue({0xFF, 0xFF, 0xFF, 0xFF});

    uint32_t date = 0xFFFFFFFF;
    uint32_t time = 0xFFFFFF00;
    uint32_t countEnc = 0xFFFFFFFF;
    uint32_t expectedCount = countEnc ^ date ^ (~time);

    PentaxMakerNote::printShutterCount(os, *value, &exifData);
    EXPECT_EQ(os.str(), std::to_string(expectedCount));
}

// Test: Fallback from PentaxDng to Pentax for date
TEST_F(PentaxShutterCountTest_200, FallbackToPentaxDate_200) {
    ExifData exifData;
    // Only Pentax.Date, no PentaxDng.Date
    setDateEntry(exifData, "Exif.Pentax.Date", {0x01, 0x02, 0x03, 0x04});
    setTimeEntry(exifData, "Exif.Pentax.Time", {0x05, 0x06, 0x07});

    uint32_t date = 0x01020304;
    uint32_t time = 0x05060700;
    uint32_t countEnc = 0x10203040;
    uint32_t expectedCount = countEnc ^ date ^ (~time);

    auto value = createUndefinedValue({0x10, 0x20, 0x30, 0x40});
    PentaxMakerNote::printShutterCount(os, *value, &exifData);
    EXPECT_EQ(os.str(), std::to_string(expectedCount));
}

// Test: Date with 5 bytes returns "undefined"
TEST_F(PentaxShutterCountTest_200, DateFiveBytesReturnsUndefined_200) {
    ExifData exifData;
    setDateEntry(exifData, "Exif.Pentax.Date", {0x07, 0xE1, 0x06, 0x0F, 0x00});  // 5 bytes
    setTimeEntry(exifData, "Exif.Pentax.Time", {0x0A, 0x1E, 0x00});
    auto value = createUndefinedValue({0x00, 0x00, 0x00, 0x01});
    PentaxMakerNote::printShutterCount(os, *value, &exifData);
    EXPECT_EQ(os.str(), "undefined");
}

// Test: Time with 2 bytes returns "undefined"
TEST_F(PentaxShutterCountTest_200, TimeTwoBytesReturnsUndefined_200) {
    ExifData exifData;
    setDateEntry(exifData, "Exif.Pentax.Date", {0x07, 0xE1, 0x06, 0x0F});
    setTimeEntry(exifData, "Exif.Pentax.Time", {0x0A, 0x1E});  // 2 bytes
    auto value = createUndefinedValue({0x00, 0x00, 0x00, 0x01});
    PentaxMakerNote::printShutterCount(os, *value, &exifData);
    EXPECT_EQ(os.str(), "undefined");
}

// Test: Value with 5 bytes returns "undefined"
TEST_F(PentaxShutterCountTest_200, ValueFiveBytesReturnsUndefined_200) {
    ExifData exifData;
    setDateEntry(exifData, "Exif.Pentax.Date", {0x07, 0xE1, 0x06, 0x0F});
    setTimeEntry(exifData, "Exif.Pentax.Time", {0x0A, 0x1E, 0x00});
    auto value = createUndefinedValue({0x00, 0x00, 0x00, 0x01, 0x02});  // 5 bytes
    PentaxMakerNote::printShutterCount(os, *value, &exifData);
    EXPECT_EQ(os.str(), "undefined");
}
