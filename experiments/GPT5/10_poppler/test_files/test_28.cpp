// TEST_ID: 28
//
// Unit tests for ImgWriter (black-box via public interface only)
//
// File under test: ./TestProjects/poppler/goo/ImgWriter.h

#include <gtest/gtest.h>

#include <cstdio>
#include <memory>
#include <vector>

// Include the real header from your codebase.
#include "goo/ImgWriter.h"

namespace {

class ImgWriterTest_28 : public ::testing::Test {
protected:
  static FILE* OpenTmpFile() {
#if defined(_WIN32)
    // tmpfile() exists on Windows too, but can fail depending on permissions.
    // Keep it simple; tests tolerate nullptr (boundary cases).
#endif
    return std::tmpfile();
  }
};

TEST_F(ImgWriterTest_28, SupportCMYK_DefaultIsFalse_28) {
  ImgWriter writer;
  EXPECT_FALSE(writer.supportCMYK());
}

TEST_F(ImgWriterTest_28, SupportCMYK_MultipleCallsAreConsistent_28) {
  ImgWriter writer;
  const bool first = writer.supportCMYK();
  const bool second = writer.supportCMYK();
  const bool third = writer.supportCMYK();

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
  // And for the provided partial implementation, this should be false.
  EXPECT_FALSE(first);
}

TEST_F(ImgWriterTest_28, SupportCMYK_CanBeCalledViaBasePointer_28) {
  auto writer = std::make_unique<ImgWriter>();
  ImgWriter* base = writer.get();
  ASSERT_NE(base, nullptr);
  EXPECT_FALSE(base->supportCMYK());
}

// Boundary-ish: ensure default-constructed object is usable for the call.
TEST_F(ImgWriterTest_28, SupportCMYK_AfterDefaultConstruction_28) {
  ImgWriter writer{};
  EXPECT_FALSE(writer.supportCMYK());
}

}  // namespace