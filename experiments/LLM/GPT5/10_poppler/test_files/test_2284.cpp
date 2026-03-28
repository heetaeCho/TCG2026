// poppler-dest-free-test-2284.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <unistd.h>  // _exit

#include "poppler-action.h"

// Function under test (provided by the Poppler library/object files)
extern "C" void poppler_dest_free(PopplerDest *dest);

class PopplerDestFreeTest_2284 : public ::testing::Test {
protected:
  static PopplerDest* NewSliceDest() {
    // Match the production code's allocator expectations (g_slice_free).
    return static_cast<PopplerDest*>(g_slice_new0(PopplerDest));
  }
};

TEST_F(PopplerDestFreeTest_2284, NullptrIsNoOp_2284) {
  ASSERT_EXIT(
      {
        poppler_dest_free(nullptr);
        _exit(0);
      },
      ::testing::ExitedWithCode(0),
      "");
}

TEST_F(PopplerDestFreeTest_2284, FreesDestWhenNamedDestIsNull_2284) {
  ASSERT_EXIT(
      {
        PopplerDest* dest = NewSliceDest();
        // Boundary/normal: named_dest is null.
        dest->named_dest = nullptr;

        poppler_dest_free(dest);
        _exit(0);
      },
      ::testing::ExitedWithCode(0),
      "");
}

TEST_F(PopplerDestFreeTest_2284, FreesDestWhenNamedDestIsNonNull_2284) {
  ASSERT_EXIT(
      {
        PopplerDest* dest = NewSliceDest();

        // Provide a heap pointer compatible with g_free().
        // NOTE: Header shows int*, but implementation treats it as g_free'able memory.
        int* named = static_cast<int*>(g_malloc0(sizeof(int) * 3));
        named[0] = 1;
        named[1] = 2;
        named[2] = 3;
        dest->named_dest = named;

        poppler_dest_free(dest);
        _exit(0);
      },
      ::testing::ExitedWithCode(0),
      "");
}

TEST_F(PopplerDestFreeTest_2284, FreesDestWithArbitraryFieldValues_2284) {
  ASSERT_EXIT(
      {
        PopplerDest* dest = NewSliceDest();
        // Populate fields to ensure they don't affect freeing behavior.
        dest->type = static_cast<PopplerDestType>(0);
        dest->page_num = -1;  // boundary-ish
        dest->change_left = 1;
        dest->change_top = 0;
        dest->change_zoom = 1;

        // Also set named_dest to a valid allocation.
        dest->named_dest = static_cast<int*>(g_malloc(sizeof(int)));
        *(dest->named_dest) = 42;

        poppler_dest_free(dest);
        _exit(0);
      },
      ::testing::ExitedWithCode(0),
      "");
}