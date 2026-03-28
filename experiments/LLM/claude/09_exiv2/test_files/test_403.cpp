namespace Exiv2 { namespace Internal { class TiffIfdMakernote { public: size_t doSizeData() const { return 0; } }; } }
#include <gtest/gtest.h>
#include <cstddef>

// Minimal reproduction of the class as provided in the implementation file
namespace Exiv2 {
namespace Internal {

class TiffIfdMakernote {
 public:
  size_t doSizeData() const { return 0; }
};

}  // namespace Internal
}  // namespace Exiv2

using Exiv2::Internal::TiffIfdMakernote;

class TiffIfdMakernoteTest_403 : public ::testing::Test {
 protected:
  TiffIfdMakernote makernote_;
};

// Test that doSizeData returns 0 for a default-constructed object
TEST_F(TiffIfdMakernoteTest_403, DoSizeDataReturnsZero_403) {
  EXPECT_EQ(0u, makernote_.doSizeData());
}

// Test that doSizeData consistently returns 0 on multiple calls
TEST_F(TiffIfdMakernoteTest_403, DoSizeDataIsConsistent_403) {
  EXPECT_EQ(makernote_.doSizeData(), makernote_.doSizeData());
  EXPECT_EQ(0u, makernote_.doSizeData());
}

// Test that doSizeData returns 0 for a different instance
TEST_F(TiffIfdMakernoteTest_403, DoSizeDataDifferentInstance_403) {
  TiffIfdMakernote another;
  EXPECT_EQ(0u, another.doSizeData());
}

// Test that doSizeData return type is size_t and value is exactly zero
TEST_F(TiffIfdMakernoteTest_403, DoSizeDataReturnType_403) {
  size_t result = makernote_.doSizeData();
  EXPECT_EQ(static_cast<size_t>(0), result);
}

// Test that doSizeData on const object works correctly
TEST_F(TiffIfdMakernoteTest_403, DoSizeDataConstCorrectness_403) {
  const TiffIfdMakernote constMakernote;
  EXPECT_EQ(0u, constMakernote.doSizeData());
}

// Test multiple instances all return 0
TEST_F(TiffIfdMakernoteTest_403, DoSizeDataMultipleInstances_403) {
  TiffIfdMakernote a, b, c;
  EXPECT_EQ(0u, a.doSizeData());
  EXPECT_EQ(0u, b.doSizeData());
  EXPECT_EQ(0u, c.doSizeData());
  EXPECT_EQ(a.doSizeData(), b.doSizeData());
  EXPECT_EQ(b.doSizeData(), c.doSizeData());
}

// Test that doSizeData on heap-allocated object returns 0
TEST_F(TiffIfdMakernoteTest_403, DoSizeDataHeapAllocated_403) {
  auto* heapObj = new TiffIfdMakernote();
  EXPECT_EQ(0u, heapObj->doSizeData());
  delete heapObj;
}
