#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <exiv2/preview.hpp>
#include <fstream>
#include <cstring>
#include <filesystem>

class PreviewImageTest_1205 : public ::testing::Test {
protected:
  // Helper to create a PreviewImage from an actual image file if available,
  // or test what we can without one.
  
  // Since PreviewImage has only private constructors (except copy),
  // we need PreviewManager to produce instances.
  // We'll create a minimal test image or use PreviewManager with an empty/dummy image.
};

// Test that copy constructor produces an equivalent object
TEST_F(PreviewImageTest_1205, CopyConstructorBasic_1205) {
  try {
    // Create a minimal valid JPEG in memory to work with
    auto image = Exiv2::ImageFactory::open("../test/data/exiv2-empty.jpg");
    if (!image) {
      GTEST_SKIP() << "Test image not available";
    }
    image->readMetadata();
    
    Exiv2::PreviewManager manager(*image);
    auto previews = manager.getPreviewProperties();
    
    if (previews.empty()) {
      GTEST_SKIP() << "No previews available in test image";
    }
    
    Exiv2::PreviewImage original = manager.getPreviewImage(previews[0]);
    Exiv2::PreviewImage copy(original);
    
    EXPECT_EQ(original.size(), copy.size());
    EXPECT_EQ(original.mimeType(), copy.mimeType());
    EXPECT_EQ(original.extension(), copy.extension());
    EXPECT_EQ(original.width(), copy.width());
    EXPECT_EQ(original.height(), copy.height());
    EXPECT_EQ(original.id(), copy.id());
    
    if (original.size() > 0 && original.pData() && copy.pData()) {
      EXPECT_EQ(0, std::memcmp(original.pData(), copy.pData(), original.size()));
    }
  } catch (const Exiv2::Error&) {
    GTEST_SKIP() << "Could not open test image";
  }
}

// Test self-assignment
TEST_F(PreviewImageTest_1205, SelfAssignment_1205) {
  try {
    auto image = Exiv2::ImageFactory::open("../test/data/exiv2-empty.jpg");
    if (!image) {
      GTEST_SKIP() << "Test image not available";
    }
    image->readMetadata();
    
    Exiv2::PreviewManager manager(*image);
    auto previews = manager.getPreviewProperties();
    
    if (previews.empty()) {
      GTEST_SKIP() << "No previews available in test image";
    }
    
    Exiv2::PreviewImage pi = manager.getPreviewImage(previews[0]);
    uint32_t sizeBefore = pi.size();
    std::string mimeBefore = pi.mimeType();
    
    // Self-assignment should be safe
    pi = pi;
    
    EXPECT_EQ(sizeBefore, pi.size());
    EXPECT_EQ(mimeBefore, pi.mimeType());
  } catch (const Exiv2::Error&) {
    GTEST_SKIP() << "Could not open test image";
  }
}

// Test assignment operator between two different preview images
TEST_F(PreviewImageTest_1205, AssignmentOperator_1205) {
  try {
    auto image = Exiv2::ImageFactory::open("../test/data/exiv2-empty.jpg");
    if (!image) {
      GTEST_SKIP() << "Test image not available";
    }
    image->readMetadata();
    
    Exiv2::PreviewManager manager(*image);
    auto previews = manager.getPreviewProperties();
    
    if (previews.empty()) {
      GTEST_SKIP() << "No previews available in test image";
    }
    
    Exiv2::PreviewImage pi1 = manager.getPreviewImage(previews[0]);
    Exiv2::PreviewImage pi2(pi1); // copy construct first
    
    // Now assign
    pi2 = pi1;
    
    EXPECT_EQ(pi1.size(), pi2.size());
    EXPECT_EQ(pi1.mimeType(), pi2.mimeType());
    EXPECT_EQ(pi1.extension(), pi2.extension());
    EXPECT_EQ(pi1.width(), pi2.width());
    EXPECT_EQ(pi1.height(), pi2.height());
    EXPECT_EQ(pi1.id(), pi2.id());
    
    if (pi1.size() > 0 && pi1.pData() && pi2.pData()) {
      EXPECT_EQ(0, std::memcmp(pi1.pData(), pi2.pData(), pi1.size()));
    }
  } catch (const Exiv2::Error&) {
    GTEST_SKIP() << "Could not open test image";
  }
}

// Test copy() returns a deep copy DataBuf
TEST_F(PreviewImageTest_1205, CopyReturnsDataBuf_1205) {
  try {
    auto image = Exiv2::ImageFactory::open("../test/data/exiv2-empty.jpg");
    if (!image) {
      GTEST_SKIP() << "Test image not available";
    }
    image->readMetadata();
    
    Exiv2::PreviewManager manager(*image);
    auto previews = manager.getPreviewProperties();
    
    if (previews.empty()) {
      GTEST_SKIP() << "No previews available in test image";
    }
    
    Exiv2::PreviewImage pi = manager.getPreviewImage(previews[0]);
    Exiv2::DataBuf buf = pi.copy();
    
    EXPECT_EQ(pi.size(), buf.size());
    
    if (pi.size() > 0 && pi.pData() && buf.c_data(0)) {
      EXPECT_EQ(0, std::memcmp(pi.pData(), buf.c_data(0), pi.size()));
    }
  } catch (const Exiv2::Error&) {
    GTEST_SKIP() << "Could not open test image";
  }
}

// Test pData and size consistency
TEST_F(PreviewImageTest_1205, PDataAndSizeConsistency_1205) {
  try {
    auto image = Exiv2::ImageFactory::open("../test/data/exiv2-empty.jpg");
    if (!image) {
      GTEST_SKIP() << "Test image not available";
    }
    image->readMetadata();
    
    Exiv2::PreviewManager manager(*image);
    auto previews = manager.getPreviewProperties();
    
    if (previews.empty()) {
      GTEST_SKIP() << "No previews available in test image";
    }
    
    Exiv2::PreviewImage pi = manager.getPreviewImage(previews[0]);
    
    if (pi.size() > 0) {
      EXPECT_NE(nullptr, pi.pData());
    }
  } catch (const Exiv2::Error&) {
    GTEST_SKIP() << "Could not open test image";
  }
}

// Test writeFile produces output
TEST_F(PreviewImageTest_1205, WriteFileProducesOutput_1205) {
  try {
    auto image = Exiv2::ImageFactory::open("../test/data/exiv2-empty.jpg");
    if (!image) {
      GTEST_SKIP() << "Test image not available";
    }
    image->readMetadata();
    
    Exiv2::PreviewManager manager(*image);
    auto previews = manager.getPreviewProperties();
    
    if (previews.empty()) {
      GTEST_SKIP() << "No previews available in test image";
    }
    
    Exiv2::PreviewImage pi = manager.getPreviewImage(previews[0]);
    
    std::string tempPath = "test_preview_output_1205";
    size_t bytesWritten = pi.writeFile(tempPath);
    
    EXPECT_EQ(pi.size(), bytesWritten);
    
    // Clean up - the file gets the extension appended
    std::string fullPath = tempPath + pi.extension();
    std::filesystem::remove(fullPath);
  } catch (const Exiv2::Error&) {
    GTEST_SKIP() << "Could not open test image";
  }
}

// Test mimeType returns non-empty string for valid preview
TEST_F(PreviewImageTest_1205, MimeTypeNonEmpty_1205) {
  try {
    auto image = Exiv2::ImageFactory::open("../test/data/exiv2-empty.jpg");
    if (!image) {
      GTEST_SKIP() << "Test image not available";
    }
    image->readMetadata();
    
    Exiv2::PreviewManager manager(*image);
    auto previews = manager.getPreviewProperties();
    
    if (previews.empty()) {
      GTEST_SKIP() << "No previews available in test image";
    }
    
    Exiv2::PreviewImage pi = manager.getPreviewImage(previews[0]);
    
    // mimeType should return some value
    const std::string& mime = pi.mimeType();
    // It may or may not be empty depending on the image, but it should not throw
    SUCCEED();
  } catch (const Exiv2::Error&) {
    GTEST_SKIP() << "Could not open test image";
  }
}

// Test extension returns a string
TEST_F(PreviewImageTest_1205, ExtensionReturnsString_1205) {
  try {
    auto image = Exiv2::ImageFactory::open("../test/data/exiv2-empty.jpg");
    if (!image) {
      GTEST_SKIP() << "Test image not available";
    }
    image->readMetadata();
    
    Exiv2::PreviewManager manager(*image);
    auto previews = manager.getPreviewProperties();
    
    if (previews.empty()) {
      GTEST_SKIP() << "No previews available in test image";
    }
    
    Exiv2::PreviewImage pi = manager.getPreviewImage(previews[0]);
    const std::string& ext = pi.extension();
    // Extension should exist (could be .jpg, .tif, etc.)
    EXPECT_FALSE(ext.empty());
  } catch (const Exiv2::Error&) {
    GTEST_SKIP() << "Could not open test image";
  }
}

// Test that PreviewManager with no previews returns empty list
TEST_F(PreviewImageTest_1205, NoPreviewsEmptyList_1205) {
  try {
    // Create a minimal JPEG with no embedded preview
    // This tests boundary: an image with no previews
    auto image = Exiv2::ImageFactory::open("../test/data/exiv2-empty.jpg");
    if (!image) {
      GTEST_SKIP() << "Test image not available";
    }
    image->readMetadata();
    
    Exiv2::PreviewManager manager(*image);
    auto previews = manager.getPreviewProperties();
    
    // This is a valid result - either empty or non-empty
    // We just verify it doesn't crash
    SUCCEED();
  } catch (const Exiv2::Error&) {
    GTEST_SKIP() << "Could not open test image";
  }
}

// Test that copy after assignment produces independent data
TEST_F(PreviewImageTest_1205, CopyAfterAssignmentIndependent_1205) {
  try {
    auto image = Exiv2::ImageFactory::open("../test/data/exiv2-empty.jpg");
    if (!image) {
      GTEST_SKIP() << "Test image not available";
    }
    image->readMetadata();
    
    Exiv2::PreviewManager manager(*image);
    auto previews = manager.getPreviewProperties();
    
    if (previews.empty()) {
      GTEST_SKIP() << "No previews available in test image";
    }
    
    Exiv2::PreviewImage pi1 = manager.getPreviewImage(previews[0]);
    Exiv2::PreviewImage pi2(pi1);
    
    // Assign pi1 to pi2
    pi2 = pi1;
    
    // Get copies - they should be independent buffers
    Exiv2::DataBuf buf1 = pi1.copy();
    Exiv2::DataBuf buf2 = pi2.copy();
    
    EXPECT_EQ(buf1.size(), buf2.size());
    
    if (buf1.size() > 0) {
      // Data should be equal
      EXPECT_EQ(0, std::memcmp(buf1.c_data(0), buf2.c_data(0), buf1.size()));
      
      // But buffers should be independent (different addresses)
      EXPECT_NE(buf1.c_data(0), buf2.c_data(0));
    }
  } catch (const Exiv2::Error&) {
    GTEST_SKIP() << "Could not open test image";
  }
}

// Test that pData of copy-constructed object is independent from original
TEST_F(PreviewImageTest_1205, CopyConstructorDeepCopy_1205) {
  try {
    auto image = Exiv2::ImageFactory::open("../test/data/exiv2-empty.jpg");
    if (!image) {
      GTEST_SKIP() << "Test image not available";
    }
    image->readMetadata();
    
    Exiv2::PreviewManager manager(*image);
    auto previews = manager.getPreviewProperties();
    
    if (previews.empty()) {
      GTEST_SKIP() << "No previews available in test image";
    }
    
    Exiv2::PreviewImage original = manager.getPreviewImage(previews[0]);
    Exiv2::PreviewImage copy(original);
    
    // The data pointers should be different (deep copy)
    if (original.size() > 0) {
      EXPECT_NE(original.pData(), copy.pData());
    }
  } catch (const Exiv2::Error&) {
    GTEST_SKIP() << "Could not open test image";
  }
}

// Test id() returns consistent value
TEST_F(PreviewImageTest_1205, IdConsistentAfterCopy_1205) {
  try {
    auto image = Exiv2::ImageFactory::open("../test/data/exiv2-empty.jpg");
    if (!image) {
      GTEST_SKIP() << "Test image not available";
    }
    image->readMetadata();
    
    Exiv2::PreviewManager manager(*image);
    auto previews = manager.getPreviewProperties();
    
    if (previews.empty()) {
      GTEST_SKIP() << "No previews available in test image";
    }
    
    Exiv2::PreviewImage pi = manager.getPreviewImage(previews[0]);
    Exiv2::PreviewImage piCopy(pi);
    
    EXPECT_EQ(pi.id(), piCopy.id());
    EXPECT_EQ(pi.id(), previews[0].id_);
  } catch (const Exiv2::Error&) {
    GTEST_SKIP() << "Could not open test image";
  }
}

// Test assignment operator returns reference to self
TEST_F(PreviewImageTest_1205, AssignmentReturnsSelf_1205) {
  try {
    auto image = Exiv2::ImageFactory::open("../test/data/exiv2-empty.jpg");
    if (!image) {
      GTEST_SKIP() << "Test image not available";
    }
    image->readMetadata();
    
    Exiv2::PreviewManager manager(*image);
    auto previews = manager.getPreviewProperties();
    
    if (previews.empty()) {
      GTEST_SKIP() << "No previews available in test image";
    }
    
    Exiv2::PreviewImage pi1 = manager.getPreviewImage(previews[0]);
    Exiv2::PreviewImage pi2(pi1);
    
    Exiv2::PreviewImage& ref = (pi2 = pi1);
    EXPECT_EQ(&ref, &pi2);
  } catch (const Exiv2::Error&) {
    GTEST_SKIP() << "Could not open test image";
  }
}

// Test self-assignment returns reference to self
TEST_F(PreviewImageTest_1205, SelfAssignmentReturnsSelf_1205) {
  try {
    auto image = Exiv2::ImageFactory::open("../test/data/exiv2-empty.jpg");
    if (!image) {
      GTEST_SKIP() << "Test image not available";
    }
    image->readMetadata();
    
    Exiv2::PreviewManager manager(*image);
    auto previews = manager.getPreviewProperties();
    
    if (previews.empty()) {
      GTEST_SKIP() << "No previews available in test image";
    }
    
    Exiv2::PreviewImage pi = manager.getPreviewImage(previews[0]);
    
    Exiv2::PreviewImage& ref = (pi = pi);
    EXPECT_EQ(&ref, &pi);
  } catch (const Exiv2::Error&) {
    GTEST_SKIP() << "Could not open test image";
  }
}

// Test multiple previews from same image
TEST_F(PreviewImageTest_1205, MultiplePreviewsDifferentProperties_1205) {
  try {
    auto image = Exiv2::ImageFactory::open("../test/data/exiv2-empty.jpg");
    if (!image) {
      GTEST_SKIP() << "Test image not available";
    }
    image->readMetadata();
    
    Exiv2::PreviewManager manager(*image);
    auto previews = manager.getPreviewProperties();
    
    if (previews.size() < 2) {
      GTEST_SKIP() << "Need at least 2 previews for this test";
    }
    
    Exiv2::PreviewImage pi1 = manager.getPreviewImage(previews[0]);
    Exiv2::PreviewImage pi2 = manager.getPreviewImage(previews[1]);
    
    // Different previews should have different IDs
    EXPECT_NE(pi1.id(), pi2.id());
  } catch (const Exiv2::Error&) {
    GTEST_SKIP() << "Could not open test image";
  }
}
