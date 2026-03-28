#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "exiv2/exiv2.hpp"
#include "tiffcomposite_int.hpp"
#include "tiffimage_int.hpp"
#include "tiffvisitor_int.hpp"

#include <sstream>
#include <cstring>

using namespace Exiv2;
using namespace Exiv2::Internal;
using ::testing::_;
using ::testing::Return;
using ::testing::AtLeast;

namespace {

// A simple binary writer that captures what is written
class TestIoWrapper {
public:
    std::vector<byte> data;
    
    void write(const byte* buf, size_t len) {
        data.insert(data.end(), buf, buf + len);
    }
    
    void putb(byte b) {
        data.push_back(b);
    }
};

} // anonymous namespace

class TiffDataEntryTest_379 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    
    void TearDown() override {
    }
};

// Test that doWriteData returns 0 when pValue() is null (no value set)
TEST_F(TiffDataEntryTest_379, ReturnsZeroWhenNoValue_379) {
    // Create a TiffDataEntry with a tag that has no value set
    TiffDataEntry entry(0x0111, IfdId::ifd0Id);
    
    // Since no value is set, pValue() should return nullptr and doWriteData should return 0
    std::ostringstream stream;
    IoWrapper ioWrapper(stream, nullptr, 0, nullptr);
    
    size_t imageIdx = 0;
    size_t result = entry.doWriteData(ioWrapper, littleEndian, 0, 0, imageIdx);
    
    EXPECT_EQ(0u, result);
}

// Test that doWriteData writes data area when value has data area with even size
TEST_F(TiffDataEntryTest_379, WritesEvenSizeDataArea_379) {
    TiffDataEntry entry(0x0111, IfdId::ifd0Id);
    
    // Create a value with a data area of even size
    auto value = std::make_unique<Exiv2::DataValue>();
    byte testData[] = {0x01, 0x02, 0x03, 0x04};
    
    // We need to set both value and data area
    value->read(testData, 4);
    
    // The data area is separate from the value data
    DataBuf dataArea(testData, 4);
    value->setDataArea(dataArea.c_data(), dataArea.size());
    
    entry.setValue(std::move(value));
    
    std::ostringstream stream;
    IoWrapper ioWrapper(stream, nullptr, 0, nullptr);
    
    size_t imageIdx = 0;
    size_t result = entry.doWriteData(ioWrapper, littleEndian, 0, 0, imageIdx);
    
    // Even size (4), no padding needed, result should be 4
    EXPECT_EQ(4u, result);
}

// Test that doWriteData pads odd-sized data area to even alignment
TEST_F(TiffDataEntryTest_379, PadsOddSizeDataArea_379) {
    TiffDataEntry entry(0x0111, IfdId::ifd0Id);
    
    auto value = std::make_unique<Exiv2::DataValue>();
    byte testData[] = {0x01, 0x02, 0x03};
    
    value->read(testData, 3);
    
    DataBuf dataArea(testData, 3);
    value->setDataArea(dataArea.c_data(), dataArea.size());
    
    entry.setValue(std::move(value));
    
    std::ostringstream stream;
    IoWrapper ioWrapper(stream, nullptr, 0, nullptr);
    
    size_t imageIdx = 0;
    size_t result = entry.doWriteData(ioWrapper, littleEndian, 0, 0, imageIdx);
    
    // Odd size (3) + 1 padding = 4
    EXPECT_EQ(4u, result);
}

// Test with empty data area - should return 0
TEST_F(TiffDataEntryTest_379, ReturnsZeroForEmptyDataArea_379) {
    TiffDataEntry entry(0x0111, IfdId::ifd0Id);
    
    auto value = std::make_unique<Exiv2::DataValue>();
    byte testData[] = {0x01};
    value->read(testData, 1);
    // Don't set data area - it should be empty by default
    
    entry.setValue(std::move(value));
    
    std::ostringstream stream;
    IoWrapper ioWrapper(stream, nullptr, 0, nullptr);
    
    size_t imageIdx = 0;
    size_t result = entry.doWriteData(ioWrapper, littleEndian, 0, 0, imageIdx);
    
    // Empty data area means nothing written
    EXPECT_EQ(0u, result);
}

// Test with single byte data area (odd size)
TEST_F(TiffDataEntryTest_379, SingleByteDataAreaGetsPadded_379) {
    TiffDataEntry entry(0x0111, IfdId::ifd0Id);
    
    auto value = std::make_unique<Exiv2::DataValue>();
    byte testData[] = {0xAB};
    value->read(testData, 1);
    
    DataBuf dataArea(testData, 1);
    value->setDataArea(dataArea.c_data(), dataArea.size());
    
    entry.setValue(std::move(value));
    
    std::ostringstream stream;
    IoWrapper ioWrapper(stream, nullptr, 0, nullptr);
    
    size_t imageIdx = 0;
    size_t result = entry.doWriteData(ioWrapper, littleEndian, 0, 0, imageIdx);
    
    // 1 byte + 1 padding = 2
    EXPECT_EQ(2u, result);
}

// Test with two byte data area (even size)
TEST_F(TiffDataEntryTest_379, TwoByteDataAreaNoPadding_379) {
    TiffDataEntry entry(0x0111, IfdId::ifd0Id);
    
    auto value = std::make_unique<Exiv2::DataValue>();
    byte testData[] = {0xAB, 0xCD};
    value->read(testData, 2);
    
    DataBuf dataArea(testData, 2);
    value->setDataArea(dataArea.c_data(), dataArea.size());
    
    entry.setValue(std::move(value));
    
    std::ostringstream stream;
    IoWrapper ioWrapper(stream, nullptr, 0, nullptr);
    
    size_t imageIdx = 0;
    size_t result = entry.doWriteData(ioWrapper, littleEndian, 0, 0, imageIdx);
    
    // 2 bytes, even, no padding
    EXPECT_EQ(2u, result);
}

// Test with big endian byte order
TEST_F(TiffDataEntryTest_379, WorksWithBigEndian_379) {
    TiffDataEntry entry(0x0111, IfdId::ifd0Id);
    
    auto value = std::make_unique<Exiv2::DataValue>();
    byte testData[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    value->read(testData, 5);
    
    DataBuf dataArea(testData, 5);
    value->setDataArea(dataArea.c_data(), dataArea.size());
    
    entry.setValue(std::move(value));
    
    std::ostringstream stream;
    IoWrapper ioWrapper(stream, nullptr, 0, nullptr);
    
    size_t imageIdx = 0;
    size_t result = entry.doWriteData(ioWrapper, bigEndian, 0, 0, imageIdx);
    
    // 5 bytes + 1 padding = 6
    EXPECT_EQ(6u, result);
}

// Test with larger data area
TEST_F(TiffDataEntryTest_379, LargerDataArea_379) {
    TiffDataEntry entry(0x0111, IfdId::ifd0Id);
    
    auto value = std::make_unique<Exiv2::DataValue>();
    std::vector<byte> testData(256);
    for (size_t i = 0; i < 256; ++i) {
        testData[i] = static_cast<byte>(i & 0xFF);
    }
    value->read(testData.data(), testData.size());
    
    DataBuf dataArea(testData.data(), testData.size());
    value->setDataArea(dataArea.c_data(), dataArea.size());
    
    entry.setValue(std::move(value));
    
    std::ostringstream stream;
    IoWrapper ioWrapper(stream, nullptr, 0, nullptr);
    
    size_t imageIdx = 0;
    size_t result = entry.doWriteData(ioWrapper, littleEndian, 0, 0, imageIdx);
    
    // 256 bytes, even, no padding
    EXPECT_EQ(256u, result);
}

// Test verifying stream content for even data area
TEST_F(TiffDataEntryTest_379, StreamContentCorrectForEvenData_379) {
    TiffDataEntry entry(0x0111, IfdId::ifd0Id);
    
    auto value = std::make_unique<Exiv2::DataValue>();
    byte testData[] = {0xDE, 0xAD, 0xBE, 0xEF};
    value->read(testData, 4);
    
    DataBuf dataArea(testData, 4);
    value->setDataArea(dataArea.c_data(), dataArea.size());
    
    entry.setValue(std::move(value));
    
    std::ostringstream stream;
    IoWrapper ioWrapper(stream, nullptr, 0, nullptr);
    
    size_t imageIdx = 0;
    entry.doWriteData(ioWrapper, littleEndian, 0, 0, imageIdx);
    
    std::string output = stream.str();
    ASSERT_EQ(4u, output.size());
    EXPECT_EQ(static_cast<char>(0xDE), output[0]);
    EXPECT_EQ(static_cast<char>(0xAD), output[1]);
    EXPECT_EQ(static_cast<char>(0xBE), output[2]);
    EXPECT_EQ(static_cast<char>(0xEF), output[3]);
}

// Test verifying stream content for odd data area includes padding byte
TEST_F(TiffDataEntryTest_379, StreamContentCorrectForOddDataWithPadding_379) {
    TiffDataEntry entry(0x0111, IfdId::ifd0Id);
    
    auto value = std::make_unique<Exiv2::DataValue>();
    byte testData[] = {0xCA, 0xFE, 0xBA};
    value->read(testData, 3);
    
    DataBuf dataArea(testData, 3);
    value->setDataArea(dataArea.c_data(), dataArea.size());
    
    entry.setValue(std::move(value));
    
    std::ostringstream stream;
    IoWrapper ioWrapper(stream, nullptr, 0, nullptr);
    
    size_t imageIdx = 0;
    entry.doWriteData(ioWrapper, littleEndian, 0, 0, imageIdx);
    
    std::string output = stream.str();
    ASSERT_EQ(4u, output.size());
    EXPECT_EQ(static_cast<char>(0xCA), output[0]);
    EXPECT_EQ(static_cast<char>(0xFE), output[1]);
    EXPECT_EQ(static_cast<char>(0xBA), output[2]);
    EXPECT_EQ(static_cast<char>(0x00), output[3]); // padding byte
}
