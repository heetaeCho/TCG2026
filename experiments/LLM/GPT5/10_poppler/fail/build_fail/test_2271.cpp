// File: poppler-attachment-get-checksum-test_2271.cc

#include <gtest/gtest.h>

#include <glib.h>

extern "C" {
#include "poppler-attachment.h"

// Function under test (provided by poppler-attachment.cc in the codebase).
const GString *poppler_attachment_get_checksum(PopplerAttachment *attachment);
}

namespace {

class PopplerAttachmentGetChecksumTest_2271 : public ::testing::Test {
protected:
  void TearDown() override {
    if (checksum_) {
      g_string_free(checksum_, TRUE);
      checksum_ = nullptr;
    }
    if (attachment_) {
      g_free(attachment_);
      attachment_ = nullptr;
    }
  }

  PopplerAttachment *attachment_ = nullptr;
  GString *checksum_ = nullptr;
};

TEST_F(PopplerAttachmentGetChecksumTest_2271, ReturnsSamePointerWhenChecksumIsSet_2271) {
  attachment_ = static_cast<PopplerAttachment *>(g_malloc0(sizeof(PopplerAttachment)));
  ASSERT_NE(attachment_, nullptr);

  checksum_ = g_string_new("abc123");
  ASSERT_NE(checksum_, nullptr);

  // The getter should return exactly the stored pointer (as an observable behavior).
  attachment_->checksum = checksum_;

  const GString *out = poppler_attachment_get_checksum(attachment_);
  EXPECT_EQ(out, checksum_);
  ASSERT_NE(out, nullptr);
  EXPECT_STREQ(out->str, "abc123");
  EXPECT_EQ(out->len, static_cast<gsize>(6));
}

TEST_F(PopplerAttachmentGetChecksumTest_2271, ReturnsNullWhenChecksumIsNull_2271) {
  attachment_ = static_cast<PopplerAttachment *>(g_malloc0(sizeof(PopplerAttachment)));
  ASSERT_NE(attachment_, nullptr);

  // Boundary condition: checksum pointer not set (NULL).
  attachment_->checksum = nullptr;

  const GString *out = poppler_attachment_get_checksum(attachment_);
  EXPECT_EQ(out, nullptr);
}

TEST_F(PopplerAttachmentGetChecksumTest_2271, DoesNotModifyChecksumContents_2271) {
  attachment_ = static_cast<PopplerAttachment *>(g_malloc0(sizeof(PopplerAttachment)));
  ASSERT_NE(attachment_, nullptr);

  checksum_ = g_string_new("original");
  ASSERT_NE(checksum_, nullptr);

  attachment_->checksum = checksum_;

  const GString *out1 = poppler_attachment_get_checksum(attachment_);
  ASSERT_NE(out1, nullptr);
  EXPECT_STREQ(out1->str, "original");
  EXPECT_EQ(out1->len, static_cast<gsize>(8));

  // Call again to ensure repeated calls are consistent and do not change observable data.
  const GString *out2 = poppler_attachment_get_checksum(attachment_);
  EXPECT_EQ(out2, checksum_);
  ASSERT_NE(out2, nullptr);
  EXPECT_STREQ(out2->str, "original");
  EXPECT_EQ(out2->len, static_cast<gsize>(8));
}

}  // namespace