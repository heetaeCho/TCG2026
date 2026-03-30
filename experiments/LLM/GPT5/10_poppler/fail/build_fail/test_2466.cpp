// poppler-rectangle-free-test-2466.cc
#include <gtest/gtest.h>

#include <glib.h>

// Minimal dependency surface provided by the prompt.
struct _PopplerRectangle {
  int x2;
  int y2;
};
using PopplerRectangle = _PopplerRectangle;

extern "C" void poppler_rectangle_free(PopplerRectangle *rectangle);

namespace {

class PopplerRectangleFreeTest_2466 : public ::testing::Test {};

TEST_F(PopplerRectangleFreeTest_2466, NullptrIsSafe_2466) {
  // Boundary: freeing a null pointer should be a no-op (must not crash).
  EXPECT_NO_FATAL_FAILURE(poppler_rectangle_free(nullptr));
}

TEST_F(PopplerRectangleFreeTest_2466, NullptrCanBeCalledRepeatedly_2466) {
  // Boundary: repeated calls with nullptr should remain safe.
  EXPECT_NO_FATAL_FAILURE(poppler_rectangle_free(nullptr));
  EXPECT_NO_FATAL_FAILURE(poppler_rectangle_free(nullptr));
  EXPECT_NO_FATAL_FAILURE(poppler_rectangle_free(nullptr));
}

TEST_F(PopplerRectangleFreeTest_2466, NullptrDoesNotRequireGlibInit_2466) {
  // Boundary: should be safe even without explicit GLib type/system init,
  // as long as the input is nullptr (no observable side effects expected).
  EXPECT_NO_FATAL_FAILURE(poppler_rectangle_free(nullptr));
}

}  // namespace