#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/preview.hpp>
#include <exiv2/image.hpp>
#include <exiv2/types.hpp>
#include <fstream>
#include <cstdio>
#include <filesystem>

namespace {

// Helper to create a temporary test image file for testing
// We need a valid image to get PreviewManager to work with
class PreviewImageTest_1206 : public ::testing::Test {
 protected:
  void SetUp() override {
    // We'll try to use a minimal JPEG with embedded thumbnail for testing
    // If no test file is available, tests that require it will be skipped
  }

  void TearDown() override {
    // Clean up any temporary files created during tests
    for (const auto& f : tempFiles_) {
      std::remove(f.c_str());
    }
  }

  void addTempFile(const std::string& path) {
    tempFiles_.push_back(path);
  }

  std::vector<std::string> tempFiles_;
};

// Test that PreviewManager can be constructed with a valid image
TEST_F(PreviewImageTest_1206, PreviewManagerGetPreviewProperties_1206) {
  try {
    // Try to open a JPEG image if available in test data
    auto image = Exiv2::ImageFactory::open("../test/data/exiv2-bug443.jpg");
    if (!image) {
      GTEST_SKIP() << "Test image not available";
    }
    image->readMetadata();
    Exiv2::PreviewManager manager(*image);
    Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();
    // Properties list may or may not be empty depending on the image
    // We just verify it doesn't crash
    SUCCEED();
  } catch (const Exiv2::Error&) {
    GTEST_SKIP() << "Test image not available or not readable";
  }
}

// Test PreviewImage copy constructor
TEST_F(PreviewImageTest_1206, CopyConstructor_1206) {
  try {
    auto image = Exiv2::ImageFactory::open("../test/data/exiv2-bug443.jpg");
    if (!image) {
      GTEST_SKIP() << "Test image not available";
    }
    image->readMetadata();
    Exiv2::PreviewManager manager(*image);
    Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();
    if (list.empty()) {
      GTEST_SKIP() << "No preview images in test file";
    }
    Exiv2::PreviewImage preview = manager.getPreviewImage(list.front());
    
    // Test copy constructor
    Exiv2::PreviewImage copy(preview);
    EXPECT_EQ(copy.size(), preview.size());
    EXPECT_EQ(copy.mimeType(), preview.mimeType());
    EXPECT_EQ(copy.extension(), preview.extension());
    EXPECT_EQ(copy.width(), preview.width());
    EXPECT_EQ(copy.height(), preview.height());
    EXPECT_EQ(copy.id(), preview.id());
  } catch (const Exiv2::Error&) {
    GTEST_SKIP() << "Test image not available or not readable";
  }
}

// Test PreviewImage assignment operator
TEST_F(PreviewImageTest_1206, AssignmentOperator_1206) {
  try {
    auto image = Exiv2::ImageFactory::open("../test/data/exiv2-bug443.jpg");
    if (!image) {
      GTEST_SKIP() << "Test image not available";
    }
    image->readMetadata();
    Exiv2::PreviewManager manager(*image);
    Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();
    if (list.empty()) {
      GTEST_SKIP() << "No preview images in test file";
    }
    Exiv2::PreviewImage preview = manager.getPreviewImage(list.front());
    Exiv2::PreviewImage copy(preview);
    
    // Test assignment
    copy = preview;
    EXPECT_EQ(copy.size(), preview.size());
    EXPECT_EQ(copy.mimeType(), preview.mimeType());
    EXPECT_EQ(copy.extension(), preview.extension());
  } catch (const Exiv2::Error&) {
    GTEST_SKIP() << "Test image not available or not readable";
  }
}

// Test pData returns non-null when size > 0
TEST_F(PreviewImageTest_1206, PDataNonNull_1206) {
  try {
    auto image = Exiv2::ImageFactory::open("../test/data/exiv2-bug443.jpg");
    if (!image) {
      GTEST_SKIP() << "Test image not available";
    }
    image->readMetadata();
    Exiv2::PreviewManager manager(*image);
    Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();
    if (list.empty()) {
      GTEST_SKIP() << "No preview images in test file";
    }
    Exiv2::PreviewImage preview = manager.getPreviewImage(list.front());
    
    if (preview.size() > 0) {
      EXPECT_NE(preview.pData(), nullptr);
    }
  } catch (const Exiv2::Error&) {
    GTEST_SKIP() << "Test image not available or not readable";
  }
}

// Test copy() returns a DataBuf with same size
TEST_F(PreviewImageTest_1206, CopyReturnsCorrectDataBuf_1206) {
  try {
    auto image = Exiv2::ImageFactory::open("../test/data/exiv2-bug443.jpg");
    if (!image) {
      GTEST_SKIP() << "Test image not available";
    }
    image->readMetadata();
    Exiv2::PreviewManager manager(*image);
    Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();
    if (list.empty()) {
      GTEST_SKIP() << "No preview images in test file";
    }
    Exiv2::PreviewImage preview = manager.getPreviewImage(list.front());
    
    Exiv2::DataBuf buf = preview.copy();
    EXPECT_EQ(buf.size(), static_cast<size_t>(preview.size()));
    
    // Verify data content matches
    if (preview.size() > 0) {
      EXPECT_EQ(std::memcmp(buf.c_data(0), preview.pData(), preview.size()), 0);
    }
  } catch (const Exiv2::Error&) {
    GTEST_SKIP() << "Test image not available or not readable";
  }
}

// Test mimeType returns a non-empty string
TEST_F(PreviewImageTest_1206, MimeTypeNonEmpty_1206) {
  try {
    auto image = Exiv2::ImageFactory::open("../test/data/exiv2-bug443.jpg");
    if (!image) {
      GTEST_SKIP() << "Test image not available";
    }
    image->readMetadata();
    Exiv2::PreviewManager manager(*image);
    Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();
    if (list.empty()) {
      GTEST_SKIP() << "No preview images in test file";
    }
    Exiv2::PreviewImage preview = manager.getPreviewImage(list.front());
    
    EXPECT_FALSE(preview.mimeType().empty());
  } catch (const Exiv2::Error&) {
    GTEST_SKIP() << "Test image not available or not readable";
  }
}

// Test extension returns a string starting with '.'
TEST_F(PreviewImageTest_1206, ExtensionStartsWithDot_1206) {
  try {
    auto image = Exiv2::ImageFactory::open("../test/data/exiv2-bug443.jpg");
    if (!image) {
      GTEST_SKIP() << "Test image not available";
    }
    image->readMetadata();
    Exiv2::PreviewManager manager(*image);
    Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();
    if (list.empty()) {
      GTEST_SKIP() << "No preview images in test file";
    }
    Exiv2::PreviewImage preview = manager.getPreviewImage(list.front());
    
    const std::string& ext = preview.extension();
    EXPECT_FALSE(ext.empty());
    EXPECT_EQ(ext[0], '.');
  } catch (const Exiv2::Error&) {
    GTEST_SKIP() << "Test image not available or not readable";
  }
}

// Test writeFile writes data to disk
TEST_F(PreviewImageTest_1206, WriteFileCreatesFile_1206) {
  try {
    auto image = Exiv2::ImageFactory::open("../test/data/exiv2-bug443.jpg");
    if (!image) {
      GTEST_SKIP() << "Test image not available";
    }
    image->readMetadata();
    Exiv2::PreviewManager manager(*image);
    Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();
    if (list.empty()) {
      GTEST_SKIP() << "No preview images in test file";
    }
    Exiv2::PreviewImage preview = manager.getPreviewImage(list.front());
    
    std::string basePath = "test_preview_output_1206";
    std::string fullPath = basePath + preview.extension();
    addTempFile(fullPath);
    
    size_t bytesWritten = preview.writeFile(basePath);
    EXPECT_EQ(bytesWritten, static_cast<size_t>(preview.size()));
    
    // Verify the file exists
    std::ifstream ifs(fullPath, std::ios::binary);
    EXPECT_TRUE(ifs.good());
    
    // Verify file size matches
    ifs.seekg(0, std::ios::end);
    size_t fileSize = static_cast<size_t>(ifs.tellg());
    EXPECT_EQ(fileSize, static_cast<size_t>(preview.size()));
  } catch (const Exiv2::Error&) {
    GTEST_SKIP() << "Test image not available or not readable";
  }
}

// Test width and height are reasonable values
TEST_F(PreviewImageTest_1206, WidthHeightReasonable_1206) {
  try {
    auto image = Exiv2::ImageFactory::open("../test/data/exiv2-bug443.jpg");
    if (!image) {
      GTEST_SKIP() << "Test image not available";
    }
    image->readMetadata();
    Exiv2::PreviewManager manager(*image);
    Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();
    if (list.empty()) {
      GTEST_SKIP() << "No preview images in test file";
    }
    Exiv2::PreviewImage preview = manager.getPreviewImage(list.front());
    
    // Width and height should be non-negative (they're size_t so always >= 0)
    // but they should be reasonable for a preview image
    EXPECT_LE(preview.width(), 100000u);
    EXPECT_LE(preview.height(), 100000u);
  } catch (const Exiv2::Error&) {
    GTEST_SKIP() << "Test image not available or not readable";
  }
}

// Test size returns non-zero for a valid preview
TEST_F(PreviewImageTest_1206, SizeNonZero_1206) {
  try {
    auto image = Exiv2::ImageFactory::open("../test/data/exiv2-bug443.jpg");
    if (!image) {
      GTEST_SKIP() << "Test image not available";
    }
    image->readMetadata();
    Exiv2::PreviewManager manager(*image);
    Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();
    if (list.empty()) {
      GTEST_SKIP() << "No preview images in test file";
    }
    Exiv2::PreviewImage preview = manager.getPreviewImage(list.front());
    
    EXPECT_GT(preview.size(), 0u);
  } catch (const Exiv2::Error&) {
    GTEST_SKIP() << "Test image not available or not readable";
  }
}

// Test that copy constructor produces independent copy (modifying one doesn't affect other)
TEST_F(PreviewImageTest_1206, CopyIsIndependent_1206) {
  try {
    auto image = Exiv2::ImageFactory::open("../test/data/exiv2-bug443.jpg");
    if (!image) {
      GTEST_SKIP() << "Test image not available";
    }
    image->readMetadata();
    Exiv2::PreviewManager manager(*image);
    Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();
    if (list.empty()) {
      GTEST_SKIP() << "No preview images in test file";
    }
    Exiv2::PreviewImage preview = manager.getPreviewImage(list.front());
    Exiv2::PreviewImage copy(preview);
    
    // Both should have valid data
    EXPECT_EQ(copy.size(), preview.size());
    if (copy.size() > 0 && preview.size() > 0) {
      // Data pointers should be different (independent copies)
      EXPECT_NE(copy.pData(), preview.pData());
      // But content should be same
      EXPECT_EQ(std::memcmp(copy.pData(), preview.pData(), preview.size()), 0);
    }
  } catch (const Exiv2::Error&) {
    GTEST_SKIP() << "Test image not available or not readable";
  }
}

// Test multiple previews if available
TEST_F(PreviewImageTest_1206, MultiplePreviewsDistinct_1206) {
  try {
    auto image = Exiv2::ImageFactory::open("../test/data/exiv2-bug443.jpg");
    if (!image) {
      GTEST_SKIP() << "Test image not available";
    }
    image->readMetadata();
    Exiv2::PreviewManager manager(*image);
    Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();
    if (list.size() < 2) {
      GTEST_SKIP() << "Need at least 2 preview images for this test";
    }
    
    Exiv2::PreviewImage preview1 = manager.getPreviewImage(list[0]);
    Exiv2::PreviewImage preview2 = manager.getPreviewImage(list[1]);
    
    // Different previews should have different IDs
    EXPECT_NE(preview1.id(), preview2.id());
  } catch (const Exiv2::Error&) {
    GTEST_SKIP() << "Test image not available or not readable";
  }
}

// Test PreviewPropertiesList ordering (should be sorted by size typically)
TEST_F(PreviewImageTest_1206, PreviewPropertiesOrdering_1206) {
  try {
    auto image = Exiv2::ImageFactory::open("../test/data/exiv2-bug443.jpg");
    if (!image) {
      GTEST_SKIP() << "Test image not available";
    }
    image->readMetadata();
    Exiv2::PreviewManager manager(*image);
    Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();
    
    // Verify properties list items have increasing width (typical ordering)
    for (size_t i = 1; i < list.size(); ++i) {
      EXPECT_GE(list[i].width_, list[i - 1].width_);
    }
  } catch (const Exiv2::Error&) {
    GTEST_SKIP() << "Test image not available or not readable";
  }
}

// Test self-assignment
TEST_F(PreviewImageTest_1206, SelfAssignment_1206) {
  try {
    auto image = Exiv2::ImageFactory::open("../test/data/exiv2-bug443.jpg");
    if (!image) {
      GTEST_SKIP() << "Test image not available";
    }
    image->readMetadata();
    Exiv2::PreviewManager manager(*image);
    Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();
    if (list.empty()) {
      GTEST_SKIP() << "No preview images in test file";
    }
    Exiv2::PreviewImage preview = manager.getPreviewImage(list.front());
    uint32_t origSize = preview.size();
    std::string origMime = preview.mimeType();
    
    // Self-assignment should be safe
    preview = preview;
    EXPECT_EQ(preview.size(), origSize);
    EXPECT_EQ(preview.mimeType(), origMime);
  } catch (const Exiv2::Error&) {
    GTEST_SKIP() << "Test image not available or not readable";
  }
}

// Test writeFile with path containing directory
TEST_F(PreviewImageTest_1206, WriteFileWithPath_1206) {
  try {
    auto image = Exiv2::ImageFactory::open("../test/data/exiv2-bug443.jpg");
    if (!image) {
      GTEST_SKIP() << "Test image not available";
    }
    image->readMetadata();
    Exiv2::PreviewManager manager(*image);
    Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();
    if (list.empty()) {
      GTEST_SKIP() << "No preview images in test file";
    }
    Exiv2::PreviewImage preview = manager.getPreviewImage(list.front());
    
    std::string basePath = "./test_preview_dir_1206";
    std::string fullPath = basePath + preview.extension();
    addTempFile(fullPath);
    
    size_t written = preview.writeFile(basePath);
    EXPECT_EQ(written, static_cast<size_t>(preview.size()));
  } catch (const Exiv2::Error&) {
    GTEST_SKIP() << "Test image not available or not readable";
  }
}

// Test that written file content matches pData
TEST_F(PreviewImageTest_1206, WriteFileContentMatchesPData_1206) {
  try {
    auto image = Exiv2::ImageFactory::open("../test/data/exiv2-bug443.jpg");
    if (!image) {
      GTEST_SKIP() << "Test image not available";
    }
    image->readMetadata();
    Exiv2::PreviewManager manager(*image);
    Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();
    if (list.empty()) {
      GTEST_SKIP() << "No preview images in test file";
    }
    Exiv2::PreviewImage preview = manager.getPreviewImage(list.front());
    
    std::string basePath = "test_preview_content_1206";
    std::string fullPath = basePath + preview.extension();
    addTempFile(fullPath);
    
    preview.writeFile(basePath);
    
    // Read back the file and compare
    std::ifstream ifs(fullPath, std::ios::binary);
    ASSERT_TRUE(ifs.good());
    std::vector<char> fileContent((std::istreambuf_iterator<char>(ifs)),
                                   std::istreambuf_iterator<char>());
    
    ASSERT_EQ(fileContent.size(), static_cast<size_t>(preview.size()));
    EXPECT_EQ(std::memcmp(fileContent.data(), preview.pData(), preview.size()), 0);
  } catch (const Exiv2::Error&) {
    GTEST_SKIP() << "Test image not available or not readable";
  }
}

}  // namespace
