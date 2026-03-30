// File: tests/from_bytes_test_49.cc
//
// Build deps (typical):
//   - gtest, gtest_main
//   - absl::strings (for absl::string_view)
//   - pybind11 headers
//
// NOTE: We include the original .cc as provided to bind the exact function under test.
// If your build prefers a dedicated header, replace the include with that header.
#include <gtest/gtest.h>
#include <absl/strings/string_view.h>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

// Include the implementation unit per the prompt path.
// Adjust include path if your build layout differs.
#include "TestProjects/re2/python/_re2.cc"

namespace py = pybind11;

// Helper to construct a py::buffer_info for a char buffer (1-D contiguous)
static py::buffer_info MakeCharBufferInfo(void* ptr, ssize_t count) {
  return py::buffer_info(
      ptr,                                           // ptr to data
      sizeof(char),                                  // itemsize (bytes per element)
      py::format_descriptor<char>::format(),         // format
      /*ndim*/ 1,                                    // one-dimensional
      std::vector<ssize_t>{count},                   // shape
      std::vector<ssize_t>{static_cast<ssize_t>(sizeof(char))}  // strides
  );
}

// ---------- Tests ----------

TEST(FromBytesTest_49, ReturnsViewWithSameDataAndSize_49) {
  // Arrange
  char buf[] = {'h','e','l','l','o'};
  auto info = MakeCharBufferInfo(static_cast<void*>(buf), /*count=*/5);

  // Act
  absl::string_view sv = re2_python::FromBytes(info);

  // Assert (observable behavior only)
  EXPECT_EQ(sv.size(), static_cast<size_t>(5));
  // The view should point at the same memory region.
  EXPECT_EQ(sv.data(), reinterpret_cast<const char*>(info.ptr));
  EXPECT_EQ(sv, "hello");
}

TEST(FromBytesTest_49, ZeroLengthWithNonNullPointer_49) {
  // Arrange: non-null pointer but zero size
  char dummy = 'x';
  auto info = MakeCharBufferInfo(static_cast<void*>(&dummy), /*count=*/0);

  // Act
  absl::string_view sv = re2_python::FromBytes(info);

  // Assert
  EXPECT_TRUE(sv.empty());
  EXPECT_EQ(sv.size(), 0u);
  // We don't assert the pointer value for empty views; only emptiness is observable/required.
}

TEST(FromBytesTest_49, ZeroLengthWithNullPointer_49) {
  // Arrange: null pointer and zero size (valid empty buffer)
  auto info = MakeCharBufferInfo(nullptr, /*count=*/0);

  // Act
  absl::string_view sv = re2_python::FromBytes(info);

  // Assert
  EXPECT_TRUE(sv.empty());
  EXPECT_EQ(sv.size(), 0u);
}

TEST(FromBytesTest_49, ReflectsUnderlyingMutation_49) {
  // Arrange
  char buf[] = {'a','b','c'};
  auto info = MakeCharBufferInfo(static_cast<void*>(buf), /*count=*/3);

  // Act
  absl::string_view sv = re2_python::FromBytes(info);

  // Mutate the underlying memory after obtaining the view.
  buf[1] = 'Z';

  // Assert: the view observes the change (non-owning, direct view onto the data).
  EXPECT_EQ(sv.size(), static_cast<size_t>(3));
  EXPECT_EQ(std::string(sv), "aZc");
}
