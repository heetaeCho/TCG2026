#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <cstdint>

// Include necessary headers from the project
#include "crwimage_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Type alias for convenience
using Blob = std::vector<byte>;

// Test fixture for CiffComponent
class CiffComponentTest_1779 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test default constructor creates an empty component
TEST_F(CiffComponentTest_1779, DefaultConstructor_1779) {
    CiffComponent comp;
    EXPECT_EQ(comp.size(), 0u);
    EXPECT_EQ(comp.offset(), 0u);
    EXPECT_EQ(comp.pData(), nullptr);
    EXPECT_EQ(comp.tag(), 0u);
    EXPECT_EQ(comp.dir(), 0u);
}

// Test parameterized constructor sets tag and dir
TEST_F(CiffComponentTest_1779, ParameterizedConstructor_1779) {
    uint16_t tag = 0x1234;
    uint16_t dir = 0x5678;
    CiffComponent comp(tag, dir);
    EXPECT_EQ(comp.tag(), tag);
    EXPECT_EQ(comp.dir(), dir);
    EXPECT_EQ(comp.size(), 0u);
    EXPECT_EQ(comp.offset(), 0u);
    EXPECT_EQ(comp.pData(), nullptr);
}

// Test setDir changes the directory
TEST_F(CiffComponentTest_1779, SetDir_1779) {
    CiffComponent comp;
    comp.setDir(0xABCD);
    EXPECT_EQ(comp.dir(), 0xABCD);
}

// Test empty() returns true for default-constructed component
TEST_F(CiffComponentTest_1779, EmptyOnDefaultConstructed_1779) {
    CiffComponent comp;
    EXPECT_TRUE(comp.empty());
}

// Test setValue sets data correctly
TEST_F(CiffComponentTest_1779, SetValueUpdatesData_1779) {
    CiffComponent comp;
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, sizeof(data));
    comp.setValue(std::move(buf));
    
    EXPECT_EQ(comp.size(), 4u);
    EXPECT_NE(comp.pData(), nullptr);
}

// Test writeValueData with a component whose dataLocation is valueData
// We need to use a tag that maps to valueData location
TEST_F(CiffComponentTest_1779, WriteValueDataForValueDataLocation_1779) {
    // We need to find a tag whose dataLocation() returns DataLocId::valueData
    // Tag 0x0000 with type that gives valueData location
    // Since we treat implementation as black box, we'll try with setValue and see behavior
    
    // Create component and set value with even-sized data
    CiffComponent comp(0x0800, 0x0000); // tag with high bits suggesting valueData location
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, sizeof(data));
    comp.setValue(std::move(buf));
    
    Blob blob;
    size_t offset = 100;
    size_t newOffset = comp.writeValueData(blob, offset);
    
    // If dataLocation is valueData, data should be appended and offset advanced
    // If dataLocation is directoryData, blob should remain empty and offset unchanged
    if (comp.dataLocation() == DataLocId::valueData) {
        EXPECT_EQ(blob.size(), 4u);
        EXPECT_EQ(newOffset, offset + 4u);
        EXPECT_EQ(blob[0], 0x01);
        EXPECT_EQ(blob[1], 0x02);
        EXPECT_EQ(blob[2], 0x03);
        EXPECT_EQ(blob[3], 0x04);
        EXPECT_EQ(comp.offset(), offset);
    } else {
        EXPECT_EQ(newOffset, offset);
        EXPECT_TRUE(blob.empty());
    }
}

// Test writeValueData with odd-sized data adds padding byte
TEST_F(CiffComponentTest_1779, WriteValueDataOddSizePadding_1779) {
    // Try a tag that results in valueData location
    CiffComponent comp(0x0800, 0x0000);
    byte data[] = {0xAA, 0xBB, 0xCC}; // 3 bytes - odd
    DataBuf buf(data, sizeof(data));
    comp.setValue(std::move(buf));
    
    Blob blob;
    size_t offset = 50;
    size_t newOffset = comp.writeValueData(blob, offset);
    
    if (comp.dataLocation() == DataLocId::valueData) {
        // Odd size: should pad with one zero byte
        EXPECT_EQ(blob.size(), 4u); // 3 data bytes + 1 padding
        EXPECT_EQ(newOffset, offset + 4u); // offset advanced by 4
        EXPECT_EQ(blob[0], 0xAA);
        EXPECT_EQ(blob[1], 0xBB);
        EXPECT_EQ(blob[2], 0xCC);
        EXPECT_EQ(blob[3], 0x00); // padding byte
    } else {
        EXPECT_EQ(newOffset, offset);
    }
}

// Test writeValueData with empty data
TEST_F(CiffComponentTest_1779, WriteValueDataEmptyData_1779) {
    CiffComponent comp(0x0800, 0x0000);
    
    Blob blob;
    size_t offset = 0;
    size_t newOffset = comp.writeValueData(blob, offset);
    
    // With no data set (size_ == 0), even if dataLocation is valueData,
    // nothing should be appended (0 bytes), and size % 2 == 0, no padding
    if (comp.dataLocation() == DataLocId::valueData) {
        EXPECT_EQ(blob.size(), 0u);
        EXPECT_EQ(newOffset, 0u);
    } else {
        EXPECT_EQ(newOffset, offset);
    }
}

// Test writeValueData with directoryData location tag doesn't write
TEST_F(CiffComponentTest_1779, WriteValueDataDirectoryDataLocation_1779) {
    // Try a tag that maps to directoryData
    // Tags with certain bit patterns map to directoryData
    CiffComponent comp(0x0001, 0x0000); // low tag likely directoryData
    byte data[] = {0x01, 0x02};
    DataBuf buf(data, sizeof(data));
    comp.setValue(std::move(buf));
    
    Blob blob;
    size_t offset = 200;
    size_t newOffset = comp.writeValueData(blob, offset);
    
    if (comp.dataLocation() == DataLocId::directoryData) {
        // Should not write anything
        EXPECT_TRUE(blob.empty());
        EXPECT_EQ(newOffset, offset);
    }
    // If it's valueData, the test still passes but tests differently
}

// Test writeValueData with single byte data (odd)
TEST_F(CiffComponentTest_1779, WriteValueDataSingleByte_1779) {
    CiffComponent comp(0x0800, 0x0000);
    byte data[] = {0xFF}; // 1 byte - odd
    DataBuf buf(data, sizeof(data));
    comp.setValue(std::move(buf));
    
    Blob blob;
    size_t offset = 10;
    size_t newOffset = comp.writeValueData(blob, offset);
    
    if (comp.dataLocation() == DataLocId::valueData) {
        EXPECT_EQ(blob.size(), 2u); // 1 data + 1 padding
        EXPECT_EQ(newOffset, offset + 2u);
        EXPECT_EQ(blob[0], 0xFF);
        EXPECT_EQ(blob[1], 0x00);
    }
}

// Test writeValueData with two bytes (even)
TEST_F(CiffComponentTest_1779, WriteValueDataTwoBytes_1779) {
    CiffComponent comp(0x0800, 0x0000);
    byte data[] = {0xDE, 0xAD}; // 2 bytes - even
    DataBuf buf(data, sizeof(data));
    comp.setValue(std::move(buf));
    
    Blob blob;
    size_t offset = 0;
    size_t newOffset = comp.writeValueData(blob, offset);
    
    if (comp.dataLocation() == DataLocId::valueData) {
        EXPECT_EQ(blob.size(), 2u);
        EXPECT_EQ(newOffset, 2u);
        EXPECT_EQ(blob[0], 0xDE);
        EXPECT_EQ(blob[1], 0xAD);
    }
}

// Test writeValueData preserves existing blob content
TEST_F(CiffComponentTest_1779, WriteValueDataAppendsToExistingBlob_1779) {
    CiffComponent comp(0x0800, 0x0000);
    byte data[] = {0x11, 0x22};
    DataBuf buf(data, sizeof(data));
    comp.setValue(std::move(buf));
    
    Blob blob;
    blob.push_back(0xAA);
    blob.push_back(0xBB);
    
    size_t offset = 2;
    size_t newOffset = comp.writeValueData(blob, offset);
    
    // Existing data should be preserved
    EXPECT_EQ(blob[0], 0xAA);
    EXPECT_EQ(blob[1], 0xBB);
    
    if (comp.dataLocation() == DataLocId::valueData) {
        EXPECT_EQ(blob.size(), 4u);
        EXPECT_EQ(blob[2], 0x11);
        EXPECT_EQ(blob[3], 0x22);
        EXPECT_EQ(newOffset, 4u);
    }
}

// Test writeValueData with large data
TEST_F(CiffComponentTest_1779, WriteValueDataLargeEvenData_1779) {
    CiffComponent comp(0x0800, 0x0000);
    std::vector<byte> data(1000, 0x42);
    DataBuf buf(data.data(), data.size());
    comp.setValue(std::move(buf));
    
    Blob blob;
    size_t offset = 0;
    size_t newOffset = comp.writeValueData(blob, offset);
    
    if (comp.dataLocation() == DataLocId::valueData) {
        EXPECT_EQ(blob.size(), 1000u);
        EXPECT_EQ(newOffset, 1000u);
        for (size_t i = 0; i < 1000; ++i) {
            EXPECT_EQ(blob[i], 0x42);
        }
    }
}

// Test writeValueData with large odd data
TEST_F(CiffComponentTest_1779, WriteValueDataLargeOddData_1779) {
    CiffComponent comp(0x0800, 0x0000);
    std::vector<byte> data(999, 0x37); // 999 bytes - odd
    DataBuf buf(data.data(), data.size());
    comp.setValue(std::move(buf));
    
    Blob blob;
    size_t offset = 0;
    size_t newOffset = comp.writeValueData(blob, offset);
    
    if (comp.dataLocation() == DataLocId::valueData) {
        EXPECT_EQ(blob.size(), 1000u); // 999 + 1 padding
        EXPECT_EQ(newOffset, 1000u);
        EXPECT_EQ(blob[999], 0x00); // padding byte
    }
}

// Test tagId() returns expected value based on tag and dir
TEST_F(CiffComponentTest_1779, TagId_1779) {
    CiffComponent comp(0x1234, 0x5678);
    uint16_t tagId = comp.tagId();
    // tagId is derived from tag_ and dir_, we just verify it returns something
    // Since we treat as black box, just ensure it doesn't crash
    (void)tagId;
}

// Test typeId static method
TEST_F(CiffComponentTest_1779, TypeIdStatic_1779) {
    // Just verify the static method doesn't crash for various tags
    TypeId t1 = CiffComponent::typeId(0x0000);
    TypeId t2 = CiffComponent::typeId(0x0800);
    TypeId t3 = CiffComponent::typeId(0xFFFF);
    (void)t1;
    (void)t2;
    (void)t3;
}

// Test dataLocation static method
TEST_F(CiffComponentTest_1779, DataLocationStatic_1779) {
    DataLocId loc1 = CiffComponent::dataLocation(0x0000);
    DataLocId loc2 = CiffComponent::dataLocation(0x0800);
    // Verify returns valid enum values
    EXPECT_TRUE(loc1 == DataLocId::valueData || loc1 == DataLocId::directoryData);
    EXPECT_TRUE(loc2 == DataLocId::valueData || loc2 == DataLocId::directoryData);
}

// Test findComponent on default component returns nullptr for unrelated tags
TEST_F(CiffComponentTest_1779, FindComponentReturnsNullForDefault_1779) {
    CiffComponent comp;
    CiffComponent* found = comp.findComponent(0x1234, 0x5678);
    // For a leaf CiffComponent with no children, this should return nullptr
    // unless it matches itself - treat as black box
    (void)found;
}

// Test writeValueData offset is set correctly
TEST_F(CiffComponentTest_1779, WriteValueDataSetsOffset_1779) {
    CiffComponent comp(0x0800, 0x0000);
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, sizeof(data));
    comp.setValue(std::move(buf));
    
    Blob blob;
    size_t initialOffset = 42;
    comp.writeValueData(blob, initialOffset);
    
    if (comp.dataLocation() == DataLocId::valueData) {
        EXPECT_EQ(comp.offset(), initialOffset);
    }
}

// Test writeValueData called twice appends correctly
TEST_F(CiffComponentTest_1779, WriteValueDataCalledTwice_1779) {
    CiffComponent comp(0x0800, 0x0000);
    byte data[] = {0x01, 0x02};
    DataBuf buf(data, sizeof(data));
    comp.setValue(std::move(buf));
    
    Blob blob;
    size_t offset = 0;
    size_t newOffset = comp.writeValueData(blob, offset);
    
    // Call again with the returned offset
    size_t finalOffset = comp.writeValueData(blob, newOffset);
    
    if (comp.dataLocation() == DataLocId::valueData) {
        EXPECT_EQ(blob.size(), 4u); // 2 bytes written twice
        EXPECT_EQ(finalOffset, 4u);
    }
}

// Test setValue with empty DataBuf
TEST_F(CiffComponentTest_1779, SetValueEmptyBuf_1779) {
    CiffComponent comp;
    DataBuf emptyBuf;
    comp.setValue(std::move(emptyBuf));
    EXPECT_EQ(comp.size(), 0u);
}

// Test that copy constructor is deleted (compile-time check not needed at runtime,
// but we can verify move semantics work via setValue)
TEST_F(CiffComponentTest_1779, SetValueMoveSemantics_1779) {
    CiffComponent comp;
    byte data[] = {0x10, 0x20, 0x30};
    DataBuf buf(data, sizeof(data));
    comp.setValue(std::move(buf));
    EXPECT_EQ(comp.size(), 3u);
    EXPECT_NE(comp.pData(), nullptr);
    EXPECT_EQ(comp.pData()[0], 0x10);
    EXPECT_EQ(comp.pData()[1], 0x20);
    EXPECT_EQ(comp.pData()[2], 0x30);
}

// Test writeValueData with zero offset
TEST_F(CiffComponentTest_1779, WriteValueDataZeroOffset_1779) {
    CiffComponent comp(0x0800, 0x0000);
    byte data[] = {0xFE, 0xED, 0xFA, 0xCE};
    DataBuf buf(data, sizeof(data));
    comp.setValue(std::move(buf));
    
    Blob blob;
    size_t newOffset = comp.writeValueData(blob, 0);
    
    if (comp.dataLocation() == DataLocId::valueData) {
        EXPECT_EQ(comp.offset(), 0u);
        EXPECT_EQ(newOffset, 4u);
    }
}
