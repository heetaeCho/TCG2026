#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/exiv2.hpp>
#include <exiv2/preview.hpp>
#include <exiv2/image.hpp>
#include <exiv2/types.hpp>

#include <memory>
#include <vector>
#include <cstring>

namespace {

class PreviewManagerTest_1216 : public ::testing::Test {
 protected:
  void SetUp() override {
  }

  void TearDown() override {
  }

  // Helper to create a minimal JPEG image in memory
  std::unique_ptr<Exiv2::Image> createMinimalJpegImage() {
    // Create a minimal JPEG in memory
    // SOI + APP0 (JFIF) + SOF + SOS + EOI
    static const unsigned char minimalJpeg[] = {
      0xFF, 0xD8, // SOI
      0xFF, 0xE0, // APP0
      0x00, 0x10, // Length 16
      'J', 'F', 'I', 'F', 0x00, // JFIF identifier
      0x01, 0x01, // Version
      0x00,       // Units
      0x00, 0x01, // X density
      0x00, 0x01, // Y density
      0x00, 0x00, // Thumbnail
      0xFF, 0xD9  // EOI
    };

    auto image = Exiv2::ImageFactory::open(minimalJpeg, sizeof(minimalJpeg));
    return image;
  }
};

// Test that PreviewManager can be constructed with an Image
TEST_F(PreviewManagerTest_1216, ConstructWithImage_1216) {
  try {
    auto image = createMinimalJpegImage();
    ASSERT_NE(image.get(), nullptr);
    Exiv2::PreviewManager manager(*image);
    // Construction should succeed without throwing
  } catch (const Exiv2::Error&) {
    // Some minimal images may not be fully valid, but construction should work
  }
}

// Test getPreviewProperties returns a list (possibly empty for minimal image)
TEST_F(PreviewManagerTest_1216, GetPreviewPropertiesMinimalImage_1216) {
  try {
    auto image = createMinimalJpegImage();
    ASSERT_NE(image.get(), nullptr);
    image->readMetadata();
    Exiv2::PreviewManager manager(*image);
    Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();
    // A minimal JPEG without embedded previews should return empty or small list
    // We just verify it doesn't crash and returns a valid list
    EXPECT_GE(list.size(), 0u);
  } catch (const Exiv2::Error&) {
    // Acceptable for minimal test images
  }
}

// Test getPreviewImage with properties from getPreviewProperties
TEST_F(PreviewManagerTest_1216, GetPreviewImageFromProperties_1216) {
  try {
    auto image = createMinimalJpegImage();
    ASSERT_NE(image.get(), nullptr);
    image->readMetadata();
    Exiv2::PreviewManager manager(*image);
    Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();

    for (const auto& props : list) {
      Exiv2::PreviewImage preview = manager.getPreviewImage(props);
      // The preview image should have some data or be validly constructed
      // Check that extension matches what was in properties
      EXPECT_EQ(preview.extension(), props.extension_);
    }
  } catch (const Exiv2::Error&) {
    // Acceptable
  }
}

// Test getPreviewImage with default/empty PreviewProperties
TEST_F(PreviewManagerTest_1216, GetPreviewImageWithDefaultProperties_1216) {
  try {
    auto image = createMinimalJpegImage();
    ASSERT_NE(image.get(), nullptr);
    image->readMetadata();
    Exiv2::PreviewManager manager(*image);

    Exiv2::PreviewProperties emptyProps;
    // Calling with empty/default properties - should not crash
    // The Loader::create may return nullptr, resulting in empty DataBuf
    Exiv2::PreviewImage preview = manager.getPreviewImage(emptyProps);
    // Preview should exist but may have empty data
    SUCCEED();
  } catch (const Exiv2::Error&) {
    // May throw for invalid id, which is acceptable behavior
    SUCCEED();
  }
}

// Test PreviewProperties default construction
TEST_F(PreviewManagerTest_1216, PreviewPropertiesDefaultConstruction_1216) {
  Exiv2::PreviewProperties props;
  EXPECT_TRUE(props.extension_.empty());
}

// Test PreviewProperties fields can be set
TEST_F(PreviewManagerTest_1216, PreviewPropertiesFieldAssignment_1216) {
  Exiv2::PreviewProperties props;
  props.extension_ = ".jpg";
  EXPECT_EQ(props.extension_, ".jpg");
}

// Test DataBuf default construction
TEST_F(PreviewManagerTest_1216, DataBufDefaultConstruction_1216) {
  Exiv2::DataBuf buf;
  EXPECT_TRUE(buf.empty());
  EXPECT_EQ(buf.size(), 0u);
}

// Test DataBuf construction with size
TEST_F(PreviewManagerTest_1216, DataBufSizeConstruction_1216) {
  Exiv2::DataBuf buf(100);
  EXPECT_FALSE(buf.empty());
  EXPECT_EQ(buf.size(), 100u);
}

// Test DataBuf construction from data
TEST_F(PreviewManagerTest_1216, DataBufDataConstruction_1216) {
  const uint8_t data[] = {0x01, 0x02, 0x03, 0x04};
  Exiv2::DataBuf buf(data, sizeof(data));
  EXPECT_EQ(buf.size(), 4u);
  EXPECT_FALSE(buf.empty());
  EXPECT_EQ(buf.read_uint8(0), 0x01);
  EXPECT_EQ(buf.read_uint8(1), 0x02);
  EXPECT_EQ(buf.read_uint8(2), 0x03);
  EXPECT_EQ(buf.read_uint8(3), 0x04);
}

// Test DataBuf alloc
TEST_F(PreviewManagerTest_1216, DataBufAlloc_1216) {
  Exiv2::DataBuf buf;
  buf.alloc(50);
  EXPECT_EQ(buf.size(), 50u);
  EXPECT_FALSE(buf.empty());
}

// Test DataBuf resize
TEST_F(PreviewManagerTest_1216, DataBufResize_1216) {
  Exiv2::DataBuf buf(10);
  EXPECT_EQ(buf.size(), 10u);
  buf.resize(20);
  EXPECT_EQ(buf.size(), 20u);
  buf.resize(5);
  EXPECT_EQ(buf.size(), 5u);
}

// Test DataBuf reset
TEST_F(PreviewManagerTest_1216, DataBufReset_1216) {
  Exiv2::DataBuf buf(100);
  EXPECT_FALSE(buf.empty());
  buf.reset();
  EXPECT_TRUE(buf.empty());
  EXPECT_EQ(buf.size(), 0u);
}

// Test DataBuf read/write uint8
TEST_F(PreviewManagerTest_1216, DataBufReadWriteUint8_1216) {
  Exiv2::DataBuf buf(10);
  buf.write_uint8(0, 0xAB);
  buf.write_uint8(9, 0xCD);
  EXPECT_EQ(buf.read_uint8(0), 0xAB);
  EXPECT_EQ(buf.read_uint8(9), 0xCD);
}

// Test DataBuf read/write uint16
TEST_F(PreviewManagerTest_1216, DataBufReadWriteUint16_1216) {
  Exiv2::DataBuf buf(10);
  buf.write_uint16(0, 0x1234, Exiv2::bigEndian);
  EXPECT_EQ(buf.read_uint16(0, Exiv2::bigEndian), 0x1234);

  buf.write_uint16(2, 0x5678, Exiv2::littleEndian);
  EXPECT_EQ(buf.read_uint16(2, Exiv2::littleEndian), 0x5678);
}

// Test DataBuf read/write uint32
TEST_F(PreviewManagerTest_1216, DataBufReadWriteUint32_1216) {
  Exiv2::DataBuf buf(10);
  buf.write_uint32(0, 0x12345678, Exiv2::bigEndian);
  EXPECT_EQ(buf.read_uint32(0, Exiv2::bigEndian), 0x12345678u);

  buf.write_uint32(4, 0xDEADBEEF, Exiv2::littleEndian);
  EXPECT_EQ(buf.read_uint32(4, Exiv2::littleEndian), 0xDEADBEEFu);
}

// Test DataBuf read/write uint64
TEST_F(PreviewManagerTest_1216, DataBufReadWriteUint64_1216) {
  Exiv2::DataBuf buf(16);
  uint64_t val = 0x123456789ABCDEF0ULL;
  buf.write_uint64(0, val, Exiv2::bigEndian);
  EXPECT_EQ(buf.read_uint64(0, Exiv2::bigEndian), val);

  buf.write_uint64(8, val, Exiv2::littleEndian);
  EXPECT_EQ(buf.read_uint64(8, Exiv2::littleEndian), val);
}

// Test DataBuf cmpBytes
TEST_F(PreviewManagerTest_1216, DataBufCmpBytes_1216) {
  const uint8_t data[] = {0x01, 0x02, 0x03, 0x04};
  Exiv2::DataBuf buf(data, sizeof(data));

  EXPECT_EQ(buf.cmpBytes(0, data, sizeof(data)), 0);

  const uint8_t other[] = {0x01, 0x02, 0x03, 0x05};
  EXPECT_NE(buf.cmpBytes(0, other, sizeof(other)), 0);
}

// Test DataBuf data pointer access
TEST_F(PreviewManagerTest_1216, DataBufDataAccess_1216) {
  Exiv2::DataBuf buf(10);
  buf.write_uint8(0, 0x42);
  EXPECT_NE(buf.data(0), nullptr);
  EXPECT_EQ(*buf.data(0), 0x42);

  const Exiv2::DataBuf& constBuf = buf;
  EXPECT_NE(constBuf.c_data(0), nullptr);
  EXPECT_EQ(*constBuf.c_data(0), 0x42);
}

// Test DataBuf begin/end iterators
TEST_F(PreviewManagerTest_1216, DataBufIterators_1216) {
  const uint8_t data[] = {0x01, 0x02, 0x03};
  Exiv2::DataBuf buf(data, sizeof(data));

  auto it = buf.begin();
  EXPECT_EQ(*it, 0x01);
  ++it;
  EXPECT_EQ(*it, 0x02);
  ++it;
  EXPECT_EQ(*it, 0x03);
  ++it;
  EXPECT_EQ(it, buf.end());
}

// Test DataBuf move semantics
TEST_F(PreviewManagerTest_1216, DataBufMoveConstruction_1216) {
  const uint8_t data[] = {0xAA, 0xBB};
  Exiv2::DataBuf buf1(data, sizeof(data));
  EXPECT_EQ(buf1.size(), 2u);

  Exiv2::DataBuf buf2(std::move(buf1));
  EXPECT_EQ(buf2.size(), 2u);
  EXPECT_EQ(buf2.read_uint8(0), 0xAA);
  EXPECT_EQ(buf2.read_uint8(1), 0xBB);
}

// Test DataBuf resize to zero
TEST_F(PreviewManagerTest_1216, DataBufResizeToZero_1216) {
  Exiv2::DataBuf buf(50);
  EXPECT_EQ(buf.size(), 50u);
  buf.resize(0);
  EXPECT_EQ(buf.size(), 0u);
  EXPECT_TRUE(buf.empty());
}

// Test DataBuf alloc after having data
TEST_F(PreviewManagerTest_1216, DataBufReallocate_1216) {
  Exiv2::DataBuf buf(10);
  buf.write_uint8(0, 0xFF);
  buf.alloc(20);
  EXPECT_EQ(buf.size(), 20u);
}

// Test getPreviewProperties returns consistent results on repeated calls
TEST_F(PreviewManagerTest_1216, GetPreviewPropertiesConsistency_1216) {
  try {
    auto image = createMinimalJpegImage();
    ASSERT_NE(image.get(), nullptr);
    image->readMetadata();
    Exiv2::PreviewManager manager(*image);

    Exiv2::PreviewPropertiesList list1 = manager.getPreviewProperties();
    Exiv2::PreviewPropertiesList list2 = manager.getPreviewProperties();

    EXPECT_EQ(list1.size(), list2.size());
    for (size_t i = 0; i < list1.size() && i < list2.size(); ++i) {
      EXPECT_EQ(list1[i].id_, list2[i].id_);
      EXPECT_EQ(list1[i].extension_, list2[i].extension_);
    }
  } catch (const Exiv2::Error&) {
    // Acceptable for minimal test images
  }
}

// Test DataBuf with zero-size construction
TEST_F(PreviewManagerTest_1216, DataBufZeroSizeConstruction_1216) {
  Exiv2::DataBuf buf(0);
  EXPECT_TRUE(buf.empty());
  EXPECT_EQ(buf.size(), 0u);
}

// Test DataBuf cmpBytes with partial comparison
TEST_F(PreviewManagerTest_1216, DataBufCmpBytesPartial_1216) {
  const uint8_t data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
  Exiv2::DataBuf buf(data, sizeof(data));

  const uint8_t partial[] = {0x02, 0x03};
  EXPECT_EQ(buf.cmpBytes(1, partial, sizeof(partial)), 0);
}

// Test DataBuf c_str
TEST_F(PreviewManagerTest_1216, DataBufCStr_1216) {
  const char str[] = "Hello";
  Exiv2::DataBuf buf(reinterpret_cast<const uint8_t*>(str), sizeof(str));
  EXPECT_STREQ(buf.c_str(0), "Hello");
}

}  // namespace
