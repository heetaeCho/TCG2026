// poppler-attachment-get-name-test_2275.cc
#include <gtest/gtest.h>

#include <glib.h>

extern "C" {
#include "poppler-attachment.h"

// The function under test (implemented in poppler-attachment.cc)
const gchar *poppler_attachment_get_name(PopplerAttachment *attachment);
}

class PopplerAttachmentGetNameTest_2275 : public ::testing::Test {
protected:
  // Use the public struct layout from the header. Treat as a black box.
  _PopplerAttachment att_{};

  PopplerAttachment *attachment() {
    return reinterpret_cast<PopplerAttachment *>(&att_);
  }
};

TEST_F(PopplerAttachmentGetNameTest_2275, ReturnsNullWhenNameIsNull_2275) {
  att_.name = nullptr;

  const gchar *ret = poppler_attachment_get_name(attachment());

  EXPECT_EQ(ret, nullptr);
}

TEST_F(PopplerAttachmentGetNameTest_2275, ReturnsSamePointerStoredInName_2275) {
  // Don't rely on any internal behavior besides returning attachment->name.
  // Cast through the header's field type (int*) without dereferencing it.
  const gchar *expected = "attachment-name";
  att_.name = reinterpret_cast<int *>(const_cast<gchar *>(expected));

  const gchar *ret = poppler_attachment_get_name(attachment());

  EXPECT_EQ(ret, expected);
}

TEST_F(PopplerAttachmentGetNameTest_2275, ReturnsUpdatedPointerAfterNameChange_2275) {
  const gchar *name1 = "first";
  const gchar *name2 = "second";

  att_.name = reinterpret_cast<int *>(const_cast<gchar *>(name1));
  const gchar *ret1 = poppler_attachment_get_name(attachment());
  EXPECT_EQ(ret1, name1);

  att_.name = reinterpret_cast<int *>(const_cast<gchar *>(name2));
  const gchar *ret2 = poppler_attachment_get_name(attachment());
  EXPECT_EQ(ret2, name2);
}

TEST_F(PopplerAttachmentGetNameTest_2275, ReturnsNonNullForArbitraryNonNullPointer_2275) {
  // Boundary-ish: an arbitrary non-null pointer value should round-trip as-is.
  // We never dereference it; we only compare pointer identity.
  auto *raw = reinterpret_cast<int *>(static_cast<uintptr_t>(0x1));
  att_.name = raw;

  const gchar *ret = poppler_attachment_get_name(attachment());

  EXPECT_EQ(reinterpret_cast<const void *>(ret), reinterpret_cast<const void *>(raw));
}

#if GTEST_HAS_DEATH_TEST
TEST_F(PopplerAttachmentGetNameTest_2275, DeathOnNullAttachment_2275) {
  // Exceptional/error case: passing nullptr is invalid; observable behavior is a crash.
  ASSERT_DEATH(
      {
        (void)poppler_attachment_get_name(nullptr);
      },
      "");
}
#endif