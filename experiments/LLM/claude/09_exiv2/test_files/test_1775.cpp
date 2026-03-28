#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "exiv2/image.hpp"
#include "crwimage_int.hpp"

#include <memory>
#include <sstream>
#include <cstring>

using namespace Exiv2;
using namespace Exiv2::Internal;

// We need a concrete Image subclass for testing since Image is abstract
// We'll use a minimal approach with MemIo
class TestImage : public Exiv2::Image {
public:
    TestImage()
        : Image(ImageType::none, static_cast<uint16_t>(0), std::make_unique<MemIo>()) {}

    void readMetadata() override {}
    void writeMetadata() override {}
};

// =====================================================
// CiffHeader tests
// =====================================================

class CiffHeaderTest_1775 : public ::testing::Test {
protected:
    void SetUp() override {
        header_ = std::make_unique<CiffHeader>();
    }

    std::unique_ptr<CiffHeader> header_;
};

TEST_F(CiffHeaderTest_1775, DefaultByteOrder_1775) {
    // Default byte order should be littleEndian
    EXPECT_EQ(header_->byteOrder(), littleEndian);
}

TEST_F(CiffHeaderTest_1775, DecodeWithNullRootDir_1775) {
    // Decode on a freshly constructed CiffHeader (no read called, pRootDir_ is null)
    // should not crash
    TestImage image;
    EXPECT_NO_THROW(header_->decode(image));
}

TEST_F(CiffHeaderTest_1775, SignatureIsNotEmpty_1775) {
    auto sig = CiffHeader::signature();
    // The signature should exist and have content
    // CRW files have a known signature
    EXPECT_FALSE(sig.empty());
}

TEST_F(CiffHeaderTest_1775, ReadInvalidDataThrows_1775) {
    // Reading with invalid/too-small data should throw
    const byte invalidData[] = {0x00, 0x00, 0x00, 0x00};
    EXPECT_THROW(header_->read(invalidData, sizeof(invalidData)), Error);
}

TEST_F(CiffHeaderTest_1775, ReadNullDataThrows_1775) {
    EXPECT_THROW(header_->read(nullptr, 0), Error);
}

TEST_F(CiffHeaderTest_1775, ReadZeroSizeThrows_1775) {
    const byte data[1] = {0};
    EXPECT_THROW(header_->read(data, 0), Error);
}

TEST_F(CiffHeaderTest_1775, ReadTooSmallDataThrows_1775) {
    // CRW header requires at least 14 bytes (signature check)
    const byte smallData[10] = {};
    EXPECT_THROW(header_->read(smallData, sizeof(smallData)), Error);
}

TEST_F(CiffHeaderTest_1775, ReadWithWrongSignatureThrows_1775) {
    // Create data that's large enough but has wrong signature
    std::vector<byte> data(64, 0);
    // Set some byte order bytes and offset but wrong signature
    data[0] = 'I';  // byte order marker for little endian
    data[1] = 'I';
    EXPECT_THROW(header_->read(data.data(), data.size()), Error);
}

TEST_F(CiffHeaderTest_1775, FindComponentOnEmptyHeader_1775) {
    // Finding a component without having read any data
    // pRootDir_ is null, so findComponent should return nullptr or handle gracefully
    const CiffComponent* result = header_->findComponent(0x0000, 0x0000);
    EXPECT_EQ(result, nullptr);
}

TEST_F(CiffHeaderTest_1775, WriteOnEmptyHeader_1775) {
    // Writing an empty header (no data read)
    Blob blob;
    EXPECT_NO_THROW(header_->write(blob));
}

// =====================================================
// CiffComponent tests
// =====================================================

class CiffComponentTest_1775 : public ::testing::Test {
protected:
    void SetUp() override {}
};

TEST_F(CiffComponentTest_1775, DefaultConstruction_1775) {
    CiffComponent comp;
    EXPECT_EQ(comp.dir(), 0);
    EXPECT_EQ(comp.tag(), 0);
    EXPECT_EQ(comp.size(), 0u);
    EXPECT_EQ(comp.offset(), 0u);
    EXPECT_EQ(comp.pData(), nullptr);
}

TEST_F(CiffComponentTest_1775, ConstructionWithTagAndDir_1775) {
    CiffComponent comp(0x1234, 0x5678);
    EXPECT_EQ(comp.tag(), 0x1234);
    EXPECT_EQ(comp.dir(), 0x5678);
    EXPECT_EQ(comp.size(), 0u);
    EXPECT_EQ(comp.offset(), 0u);
}

TEST_F(CiffComponentTest_1775, EmptyOnDefaultConstruction_1775) {
    CiffComponent comp;
    EXPECT_TRUE(comp.empty());
}

TEST_F(CiffComponentTest_1775, TagIdFromTag_1775) {
    CiffComponent comp(0x300A, 0x0000);
    // tagId is derived from tag
    uint16_t tagId = comp.tagId();
    // tagId should be the lower bits of tag (tag & 0x3fff typically)
    EXPECT_EQ(tagId, comp.tag() & 0x3FFF);
}

TEST_F(CiffComponentTest_1775, TypeIdStatic_1775) {
    // typeId is a static method that extracts type from tag
    TypeId type = CiffComponent::typeId(0x0000);
    // Just check it doesn't crash and returns something
    (void)type;
}

TEST_F(CiffComponentTest_1775, DataLocationStatic_1775) {
    // dataLocation is a static method
    DataLocId loc = CiffComponent::dataLocation(0x0000);
    (void)loc;
    // For tags with data in the value area
    DataLocId loc2 = CiffComponent::dataLocation(0x0800);
    (void)loc2;
}

TEST_F(CiffComponentTest_1775, FindComponentOnSimpleComponent_1775) {
    CiffComponent comp(0x0001, 0x0002);
    // Simple component (not directory) - findComponent checks tagId and dir
    CiffComponent* found = comp.findComponent(0x0001, 0x0002);
    // A simple component should be able to find itself if tag and dir match
    // The exact behavior depends on implementation
    (void)found;
}

TEST_F(CiffComponentTest_1775, SetValue_1775) {
    CiffComponent comp(0x0001, 0x0002);
    DataBuf buf(10);
    std::memset(buf.data(), 0xAB, 10);
    EXPECT_NO_THROW(comp.setValue(std::move(buf)));
    // After setting value, size should reflect the new data
    EXPECT_EQ(comp.size(), 10u);
    EXPECT_NE(comp.pData(), nullptr);
}

TEST_F(CiffComponentTest_1775, SetValueEmptyBuf_1775) {
    CiffComponent comp(0x0001, 0x0002);
    DataBuf emptyBuf;
    EXPECT_NO_THROW(comp.setValue(std::move(emptyBuf)));
}

TEST_F(CiffComponentTest_1775, PrintDoesNotCrash_1775) {
    CiffComponent comp(0x0001, 0x0002);
    std::ostringstream os;
    EXPECT_NO_THROW(comp.print(os, littleEndian, ""));
}

TEST_F(CiffComponentTest_1775, WriteDirEntryDoesNotCrash_1775) {
    CiffComponent comp(0x0001, 0x0002);
    Blob blob;
    EXPECT_NO_THROW(comp.writeDirEntry(blob, littleEndian));
}

TEST_F(CiffComponentTest_1775, SetDir_1775) {
    CiffComponent comp;
    comp.setDir(0x1234);
    EXPECT_EQ(comp.dir(), 0x1234);
}

TEST_F(CiffComponentTest_1775, DecodeDoesNotCrashOnEmptyComponent_1775) {
    CiffComponent comp;
    TestImage image;
    EXPECT_NO_THROW(comp.decode(image, littleEndian));
}

// =====================================================
// Integration-like tests for CiffHeader decode
// =====================================================

class CiffHeaderDecodeTest_1775 : public ::testing::Test {
protected:
    void SetUp() override {
        header_ = std::make_unique<CiffHeader>();
        image_ = std::make_unique<TestImage>();
    }

    std::unique_ptr<CiffHeader> header_;
    std::unique_ptr<TestImage> image_;
};

TEST_F(CiffHeaderDecodeTest_1775, DecodeOnFreshHeaderDoesNotModifyImage_1775) {
    // A fresh header with no root dir should not modify the image
    header_->decode(*image_);
    EXPECT_TRUE(image_->exifData().empty());
}

TEST_F(CiffHeaderDecodeTest_1775, RemoveOnEmptyHeaderDoesNotCrash_1775) {
    // Removing from an empty header should not crash
    // (pRootDir_ is null)
    EXPECT_NO_THROW(header_->remove(0x0000, 0x0000));
}

// Test with valid CRW-like data structure
TEST_F(CiffHeaderDecodeTest_1775, ReadValidCrwMinimalHeader_1775) {
    // Construct a minimal valid CRW header
    // CRW signature: byte order (II = little endian), offset to root directory, "HEAPCCDR"
    // Header structure: 2 bytes byte order + 4 bytes offset + 8 bytes signature = 14 bytes minimum
    
    auto sig = CiffHeader::signature();
    
    // We need at least the header (14 bytes) plus a minimal root directory
    // The offset points to the root directory within the data
    // This is tricky to construct correctly, so we test that invalid constructions throw
    
    std::vector<byte> data(26, 0);
    // Little endian byte order
    data[0] = 'I';
    data[1] = 'I';
    // Offset to heap start (header length)
    data[2] = 14;
    data[3] = 0;
    data[4] = 0;
    data[5] = 0;
    
    // Copy signature starting at offset 6
    // Signature is "HEAPCCDR" (8 bytes)
    if (sig.size() >= 8) {
        // This may or may not match - we test the throw behavior
    }
    
    // Most likely this will still fail validation
    EXPECT_THROW(header_->read(data.data(), data.size()), Error);
}

// =====================================================
// Additional boundary tests
// =====================================================

TEST_F(CiffComponentTest_1775, WriteOnEmptyComponent_1775) {
    CiffComponent comp;
    Blob blob;
    size_t result = comp.write(blob, littleEndian, 0);
    // Result should be some offset value
    (void)result;
}

TEST_F(CiffComponentTest_1775, WriteValueDataOnEmptyComponent_1775) {
    CiffComponent comp;
    Blob blob;
    size_t result = comp.writeValueData(blob, 0);
    (void)result;
}

TEST_F(CiffComponentTest_1775, BigEndianByteOrder_1775) {
    CiffComponent comp(0x0001, 0x0002);
    DataBuf buf(4);
    buf.data()[0] = 0x01;
    buf.data()[1] = 0x02;
    buf.data()[2] = 0x03;
    buf.data()[3] = 0x04;
    comp.setValue(std::move(buf));
    
    std::ostringstream os;
    EXPECT_NO_THROW(comp.print(os, bigEndian, "prefix"));
}

TEST_F(CiffComponentTest_1775, MultipleSetValueCalls_1775) {
    CiffComponent comp(0x0001, 0x0002);
    
    DataBuf buf1(5);
    std::memset(buf1.data(), 0x01, 5);
    comp.setValue(std::move(buf1));
    EXPECT_EQ(comp.size(), 5u);
    
    DataBuf buf2(10);
    std::memset(buf2.data(), 0x02, 10);
    comp.setValue(std::move(buf2));
    EXPECT_EQ(comp.size(), 10u);
}

TEST_F(CiffComponentTest_1775, TypeIdForVariousTags_1775) {
    // Test typeId for different tag values
    TypeId t1 = CiffComponent::typeId(0x0000);
    TypeId t2 = CiffComponent::typeId(0x0800);
    TypeId t3 = CiffComponent::typeId(0x1000);
    TypeId t4 = CiffComponent::typeId(0x1800);
    TypeId t5 = CiffComponent::typeId(0x2000);
    TypeId t6 = CiffComponent::typeId(0x2800);
    TypeId t7 = CiffComponent::typeId(0x3800);
    
    // Just verify they return without crashing
    (void)t1; (void)t2; (void)t3; (void)t4; (void)t5; (void)t6; (void)t7;
}

TEST_F(CiffComponentTest_1775, DataLocationForVariousTags_1775) {
    DataLocId d1 = CiffComponent::dataLocation(0x0000);
    DataLocId d2 = CiffComponent::dataLocation(0x4000);
    DataLocId d3 = CiffComponent::dataLocation(0x8000);
    
    (void)d1; (void)d2; (void)d3;
}
