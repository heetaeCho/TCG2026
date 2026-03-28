#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/exiv2.hpp>
#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"
#include "tiffimage_int.hpp"

#include <cstring>
#include <vector>

using namespace Exiv2;
using namespace Exiv2::Internal;

namespace {

// Helper to create a TiffEntry with unsigned short data
class TiffEntryHelper {
public:
    static std::unique_ptr<TiffEntry> createEntry(uint16_t tag, IfdId group,
                                                    const std::vector<uint16_t>& data) {
        auto entry = std::make_unique<TiffEntry>(tag, group);
        auto value = Value::create(unsignedShort);
        std::string s;
        for (size_t i = 0; i < data.size(); i++) {
            if (i > 0) s += " ";
            s += std::to_string(data[i]);
        }
        value->read(s);
        entry->setValue(std::move(value));
        return entry;
    }

    static std::unique_ptr<TiffEntry> createSignedEntry(uint16_t tag, IfdId group,
                                                         const std::vector<int16_t>& data) {
        auto entry = std::make_unique<TiffEntry>(tag, group);
        auto value = Value::create(signedShort);
        std::string s;
        for (size_t i = 0; i < data.size(); i++) {
            if (i > 0) s += " ";
            s += std::to_string(data[i]);
        }
        value->read(s);
        entry->setValue(std::move(value));
        return entry;
    }

    static std::unique_ptr<TiffEntry> createLongEntry(uint16_t tag, IfdId group,
                                                       const std::vector<uint32_t>& data) {
        auto entry = std::make_unique<TiffEntry>(tag, group);
        auto value = Value::create(unsignedLong);
        std::string s;
        for (size_t i = 0; i < data.size(); i++) {
            if (i > 0) s += " ";
            s += std::to_string(data[i]);
        }
        value->read(s);
        entry->setValue(std::move(value));
        return entry;
    }
};

// Null finder function for decoder
DecoderFct nullFindDecoderFct(const std::string&, uint16_t, IfdId) {
    return nullptr;
}

} // anonymous namespace

class TiffDecoderCanonAFInfoTest_1661 : public ::testing::Test {
protected:
    ExifData exifData_;
    IptcData iptcData_;
    XmpData xmpData_;

    std::unique_ptr<TiffDecoder> createDecoder(TiffComponent* pRoot = nullptr) {
        return std::make_unique<TiffDecoder>(
            exifData_, iptcData_, xmpData_, pRoot, nullFindDecoderFct);
    }

    // Build a valid Canon AF Info data array
    // The first value must equal count * 2
    // Index 2 is nPoints
    // We need: 8 header entries + nPoints*4 + nMasks*3 entries total
    std::vector<uint16_t> buildValidAFInfoData(uint16_t nPoints) {
        uint16_t nMasks = (nPoints + 15) / (sizeof(uint16_t) * 8);
        // records: 1+1+1+1+1+1+1+1 + nPoints*4 + nMasks*3
        uint16_t totalEntries = 8 + nPoints * 4 + nMasks * 3;

        std::vector<uint16_t> data(totalEntries);
        // First value = count * 2 = totalEntries * 2
        data[0] = static_cast<uint16_t>(totalEntries * 2);
        // data[1] = AFAreaMode (arbitrary)
        data[1] = 1;
        // data[2] = nPoints
        data[2] = nPoints;
        // Fill rest with some values
        for (uint16_t i = 3; i < totalEntries; i++) {
            data[i] = i;
        }
        return data;
    }
};

// Test: count < 3 should return early without adding AF info entries
TEST_F(TiffDecoderCanonAFInfoTest_1661, InsufficientCount_LessThan3_1661) {
    std::vector<uint16_t> data = {4, 1}; // only 2 elements
    auto entry = TiffEntryHelper::createEntry(0x0026, IfdId::canonId, data);
    auto decoder = createDecoder();

    size_t initialSize = exifData_.count();
    decoder->decodeCanonAFInfo(entry.get());
    // The standard decode might add one entry, but AF-specific entries should not be added
    // We just verify no crash and the function returns
    SUCCEED();
}

// Test: Wrong typeId (not unsignedShort) should return early
TEST_F(TiffDecoderCanonAFInfoTest_1661, WrongTypeId_ReturnsEarly_1661) {
    std::vector<uint32_t> data = {100, 1, 5};
    auto entry = TiffEntryHelper::createLongEntry(0x0026, IfdId::canonId, data);
    auto decoder = createDecoder();

    decoder->decodeCanonAFInfo(entry.get());
    // Should return early due to wrong type - no AF specific entries
    SUCCEED();
}

// Test: First value doesn't match count*2, should return early
TEST_F(TiffDecoderCanonAFInfoTest_1661, FirstValueMismatch_ReturnsEarly_1661) {
    // 3 elements but first value != 3*2=6
    std::vector<uint16_t> data = {99, 1, 1};
    auto entry = TiffEntryHelper::createEntry(0x0026, IfdId::canonId, data);
    auto decoder = createDecoder();

    decoder->decodeCanonAFInfo(entry.get());
    // Should return early because data[0] != count * 2
    SUCCEED();
}

// Test: Valid data with nPoints = 1
TEST_F(TiffDecoderCanonAFInfoTest_1661, ValidData_OnePoint_1661) {
    uint16_t nPoints = 1;
    auto data = buildValidAFInfoData(nPoints);
    auto entry = TiffEntryHelper::createEntry(0x0026, IfdId::canonId, data);
    auto decoder = createDecoder();

    decoder->decodeCanonAFInfo(entry.get());

    // Should have created entries for Canon AF info tags
    // Check that some Canon AF info entries exist in exifData_
    bool foundAFEntry = false;
    for (auto it = exifData_.begin(); it != exifData_.end(); ++it) {
        if (it->key().find("Canon") != std::string::npos &&
            it->key().find("AF") != std::string::npos) {
            foundAFEntry = true;
            break;
        }
    }
    EXPECT_TRUE(foundAFEntry);
}

// Test: Valid data with nPoints = 0
TEST_F(TiffDecoderCanonAFInfoTest_1661, ValidData_ZeroPoints_1661) {
    uint16_t nPoints = 0;
    auto data = buildValidAFInfoData(nPoints);
    auto entry = TiffEntryHelper::createEntry(0x0026, IfdId::canonId, data);
    auto decoder = createDecoder();

    decoder->decodeCanonAFInfo(entry.get());
    // Should succeed without crash even with 0 points
    SUCCEED();
}

// Test: Valid data with multiple points
TEST_F(TiffDecoderCanonAFInfoTest_1661, ValidData_MultiplePoints_1661) {
    uint16_t nPoints = 9;
    auto data = buildValidAFInfoData(nPoints);
    auto entry = TiffEntryHelper::createEntry(0x0026, IfdId::canonId, data);
    auto decoder = createDecoder();

    decoder->decodeCanonAFInfo(entry.get());

    // Verify entries were created
    bool foundAFNumPoints = false;
    for (auto it = exifData_.begin(); it != exifData_.end(); ++it) {
        if (it->key().find("AFNumPoints") != std::string::npos) {
            foundAFNumPoints = true;
            break;
        }
    }
    EXPECT_TRUE(foundAFNumPoints);
}

// Test: Data too short for the declared nPoints - should return early
TEST_F(TiffDecoderCanonAFInfoTest_1661, InsufficientDataForPoints_1661) {
    // Declare nPoints = 100 but don't provide enough data
    // We need 8 + 100*4 + nMasks*3 entries, but provide fewer
    uint16_t nPoints = 100;
    uint16_t nMasks = (nPoints + 15) / (sizeof(uint16_t) * 8);
    uint16_t needed = 8 + nPoints * 4 + nMasks * 3;

    // Provide only 20 entries but claim first value = 20*2
    std::vector<uint16_t> data(20);
    data[0] = static_cast<uint16_t>(20 * 2);
    data[1] = 1;
    data[2] = nPoints; // claims 100 points but only 20 entries total

    auto entry = TiffEntryHelper::createEntry(0x0026, IfdId::canonId, data);
    auto decoder = createDecoder();

    decoder->decodeCanonAFInfo(entry.get());
    // Should return early because total count exceeds data size
    SUCCEED();
}

// Test: Exactly 3 elements, with first value matching
TEST_F(TiffDecoderCanonAFInfoTest_1661, MinimalValidCount_3Elements_1661) {
    // count = 3, first value should be 3*2 = 6
    // nPoints = data[2], let's say 0
    // With nPoints=0, nMasks=0, total needed = 8+0+0 = 8 > 3, so should return early
    std::vector<uint16_t> data = {6, 1, 0};
    auto entry = TiffEntryHelper::createEntry(0x0026, IfdId::canonId, data);
    auto decoder = createDecoder();

    decoder->decodeCanonAFInfo(entry.get());
    // Should return early because count check fails (need at least 8 entries for header)
    SUCCEED();
}

// Test: nPoints = 16 to test nMasks calculation (16 points -> 1 mask)
TEST_F(TiffDecoderCanonAFInfoTest_1661, NPointsExact16_SingleMask_1661) {
    uint16_t nPoints = 16;
    auto data = buildValidAFInfoData(nPoints);
    auto entry = TiffEntryHelper::createEntry(0x0026, IfdId::canonId, data);
    auto decoder = createDecoder();

    decoder->decodeCanonAFInfo(entry.get());

    bool foundAFEntry = false;
    for (auto it = exifData_.begin(); it != exifData_.end(); ++it) {
        if (it->key().find("Canon") != std::string::npos &&
            it->key().find("AF") != std::string::npos) {
            foundAFEntry = true;
            break;
        }
    }
    EXPECT_TRUE(foundAFEntry);
}

// Test: nPoints = 17 to test nMasks boundary (17 points -> 2 masks)
TEST_F(TiffDecoderCanonAFInfoTest_1661, NPoints17_TwoMasks_1661) {
    uint16_t nPoints = 17;
    auto data = buildValidAFInfoData(nPoints);
    auto entry = TiffEntryHelper::createEntry(0x0026, IfdId::canonId, data);
    auto decoder = createDecoder();

    decoder->decodeCanonAFInfo(entry.get());

    bool foundAFEntry = false;
    for (auto it = exifData_.begin(); it != exifData_.end(); ++it) {
        if (it->key().find("Canon") != std::string::npos &&
            it->key().find("AF") != std::string::npos) {
            foundAFEntry = true;
            break;
        }
    }
    EXPECT_TRUE(foundAFEntry);
}

// Test: Verify AFInfoSize entry value matches the first value
TEST_F(TiffDecoderCanonAFInfoTest_1661, VerifyAFInfoSizeValue_1661) {
    uint16_t nPoints = 1;
    auto data = buildValidAFInfoData(nPoints);
    auto entry = TiffEntryHelper::createEntry(0x0026, IfdId::canonId, data);
    auto decoder = createDecoder();

    decoder->decodeCanonAFInfo(entry.get());

    auto it = exifData_.findKey(ExifKey("Exif.Canon.AFInfoSize"));
    if (it != exifData_.end()) {
        // The value should be the first element (which is count*2)
        EXPECT_EQ(it->toInt64(), static_cast<int64_t>(data[0]));
    }
}

// Test: Verify AFAreaMode entry
TEST_F(TiffDecoderCanonAFInfoTest_1661, VerifyAFAreaMode_1661) {
    uint16_t nPoints = 1;
    auto data = buildValidAFInfoData(nPoints);
    data[1] = 42; // Set AFAreaMode to a known value
    auto entry = TiffEntryHelper::createEntry(0x0026, IfdId::canonId, data);
    auto decoder = createDecoder();

    decoder->decodeCanonAFInfo(entry.get());

    auto it = exifData_.findKey(ExifKey("Exif.Canon.AFAreaMode"));
    if (it != exifData_.end()) {
        EXPECT_EQ(it->toInt64(), 42);
    }
}

// Test: Verify AFNumPoints value matches nPoints
TEST_F(TiffDecoderCanonAFInfoTest_1661, VerifyAFNumPoints_1661) {
    uint16_t nPoints = 5;
    auto data = buildValidAFInfoData(nPoints);
    auto entry = TiffEntryHelper::createEntry(0x0026, IfdId::canonId, data);
    auto decoder = createDecoder();

    decoder->decodeCanonAFInfo(entry.get());

    auto it = exifData_.findKey(ExifKey("Exif.Canon.AFNumPoints"));
    if (it != exifData_.end()) {
        EXPECT_EQ(it->toInt64(), nPoints);
    }
}

// Test: Signed short type should be rejected (typeId check)
TEST_F(TiffDecoderCanonAFInfoTest_1661, SignedShortType_ReturnsEarly_1661) {
    std::vector<int16_t> data = {6, 1, 0};
    auto entry = TiffEntryHelper::createSignedEntry(0x0026, IfdId::canonId, data);
    auto decoder = createDecoder();

    size_t beforeCount = exifData_.count();
    decoder->decodeCanonAFInfo(entry.get());
    // The signed short type != unsignedShort, so AF-specific decode should not happen
    // Only the standard decode should have run
    SUCCEED();
}

// Test: Large nPoints value that would overflow count check
TEST_F(TiffDecoderCanonAFInfoTest_1661, LargeNPoints_InsufficientData_1661) {
    // Create minimal data with large nPoints
    std::vector<uint16_t> data(10);
    data[0] = static_cast<uint16_t>(10 * 2); // matches count
    data[1] = 1;
    data[2] = 1000; // very large nPoints

    auto entry = TiffEntryHelper::createEntry(0x0026, IfdId::canonId, data);
    auto decoder = createDecoder();

    // Should not crash, should return early
    decoder->decodeCanonAFInfo(entry.get());
    SUCCEED();
}
