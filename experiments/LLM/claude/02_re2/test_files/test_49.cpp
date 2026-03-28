#include <gtest/gtest.h>
#include "absl/strings/string_view.h"
#include <pybind11/pybind11.h>
#include <pybind11/buffer_info.h>
#include <cstring>

namespace py = pybind11;

// Re-declare the function under test since it's in a specific namespace
// We treat it as a black box based on its signature
namespace re2_python {
static inline absl::string_view FromBytes(const py::buffer_info& bytes) {
  char* data = reinterpret_cast<char*>(bytes.ptr);
  ssize_t size = bytes.size;
  return absl::string_view(data, size);
}
}  // namespace re2_python

class FromBytesTest_49 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that FromBytes correctly returns a string_view with the right data and size
// for a normal non-empty buffer.
TEST_F(FromBytesTest_49, NormalBuffer_ReturnsCorrectStringView_49) {
  const char data[] = "hello world";
  ssize_t size = strlen(data);
  // Construct a buffer_info manually:
  // buffer_info(void* ptr, ssize_t itemsize, const std::string& format,
  //             ssize_t ndim, const std::vector<ssize_t>& shape,
  //             const std::vector<ssize_t>& strides)
  py::buffer_info info(
      const_cast<char*>(data),  // ptr
      1,                        // itemsize (sizeof(char))
      py::format_descriptor<char>::format(),  // format
      1,                        // ndim
      {size},                   // shape
      {1}                       // strides
  );

  absl::string_view result = re2_python::FromBytes(info);

  EXPECT_EQ(result.data(), data);
  EXPECT_EQ(result.size(), static_cast<size_t>(size));
  EXPECT_EQ(result, "hello world");
}

// Test that FromBytes handles an empty buffer correctly (size = 0).
TEST_F(FromBytesTest_49, EmptyBuffer_ReturnsEmptyStringView_49) {
  char data[] = "";
  ssize_t size = 0;
  py::buffer_info info(
      data,
      1,
      py::format_descriptor<char>::format(),
      1,
      {size},
      {1}
  );

  absl::string_view result = re2_python::FromBytes(info);

  EXPECT_EQ(result.size(), 0u);
  EXPECT_TRUE(result.empty());
}

// Test that FromBytes handles a single-byte buffer.
TEST_F(FromBytesTest_49, SingleByte_ReturnsCorrectStringView_49) {
  char data[] = "A";
  ssize_t size = 1;
  py::buffer_info info(
      data,
      1,
      py::format_descriptor<char>::format(),
      1,
      {size},
      {1}
  );

  absl::string_view result = re2_python::FromBytes(info);

  EXPECT_EQ(result.size(), 1u);
  EXPECT_EQ(result[0], 'A');
}

// Test that FromBytes handles binary data with embedded null characters.
TEST_F(FromBytesTest_49, BinaryDataWithNulls_ReturnsCorrectSize_49) {
  char data[] = {'h', 'e', '\0', 'l', 'o'};
  ssize_t size = 5;
  py::buffer_info info(
      data,
      1,
      py::format_descriptor<char>::format(),
      1,
      {size},
      {1}
  );

  absl::string_view result = re2_python::FromBytes(info);

  EXPECT_EQ(result.size(), 5u);
  EXPECT_EQ(result[0], 'h');
  EXPECT_EQ(result[1], 'e');
  EXPECT_EQ(result[2], '\0');
  EXPECT_EQ(result[3], 'l');
  EXPECT_EQ(result[4], 'o');
}

// Test that FromBytes returns a string_view pointing to the original data (no copy).
TEST_F(FromBytesTest_49, DataPointerMatchesOriginal_49) {
  char data[] = "test data pointer";
  ssize_t size = strlen(data);
  py::buffer_info info(
      data,
      1,
      py::format_descriptor<char>::format(),
      1,
      {size},
      {1}
  );

  absl::string_view result = re2_python::FromBytes(info);

  EXPECT_EQ(result.data(), static_cast<void*>(data));
}

// Test with a larger buffer to ensure size is handled correctly.
TEST_F(FromBytesTest_49, LargeBuffer_ReturnsCorrectSize_49) {
  const size_t kLargeSize = 10000;
  std::vector<char> data(kLargeSize, 'x');
  py::buffer_info info(
      data.data(),
      1,
      py::format_descriptor<char>::format(),
      1,
      {static_cast<ssize_t>(kLargeSize)},
      {1}
  );

  absl::string_view result = re2_python::FromBytes(info);

  EXPECT_EQ(result.size(), kLargeSize);
  EXPECT_EQ(result.data(), data.data());
  // Verify content
  for (size_t i = 0; i < kLargeSize; ++i) {
    EXPECT_EQ(result[i], 'x') << "Mismatch at index " << i;
  }
}

// Test with buffer containing all possible byte values
TEST_F(FromBytesTest_49, AllByteValues_ReturnsCorrectData_49) {
  char data[256];
  for (int i = 0; i < 256; ++i) {
    data[i] = static_cast<char>(i);
  }
  ssize_t size = 256;
  py::buffer_info info(
      data,
      1,
      py::format_descriptor<char>::format(),
      1,
      {size},
      {1}
  );

  absl::string_view result = re2_python::FromBytes(info);

  EXPECT_EQ(result.size(), 256u);
  for (int i = 0; i < 256; ++i) {
    EXPECT_EQ(static_cast<unsigned char>(result[i]), static_cast<unsigned char>(i))
        << "Mismatch at byte value " << i;
  }
}
