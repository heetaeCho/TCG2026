// poppler-attachment-get-description-test_2273.cc
//
// Unit tests for poppler_attachment_get_description()
// Constraints: black-box testing via public interface only.
//
// NOTE: The provided header snippet in the prompt appears "stubbed"/inaccurate
// (e.g., description typed as int*). We only rely on the C API signature of
// poppler_attachment_get_description() and the fact it returns a const gchar*.
//
// If your build uses the real Poppler headers, include them instead of these
// minimal forward declarations.

#include <gtest/gtest.h>

#include <glib.h>

extern "C" {

// Forward declare PopplerAttachment as an opaque-ish struct for tests.
// In real builds, include "poppler-attachment.h" from poppler-glib.
typedef struct _PopplerAttachment PopplerAttachment;

// Function under test (from poppler-attachment.cc).
const gchar *poppler_attachment_get_description(PopplerAttachment *attachment);
}  // extern "C"

// Minimal test-local layout that matches what the function reads:
// it dereferences `attachment->description`.
// We intentionally only include fields needed for observable behavior.
struct _PopplerAttachment {
  int parent;
  int *name;
  const gchar *description;
  int GTime;
  int ctime;
  int GString;
};

class PopplerAttachmentGetDescriptionTest_2273 : public ::testing::Test {
 protected:
  PopplerAttachment attachment_{};
};

TEST_F(PopplerAttachmentGetDescriptionTest_2273, ReturnsSamePointerForNonNullDescription_2273) {
  const gchar kDesc[] = "hello description";
  attachment_.description = kDesc;

  const gchar *out = poppler_attachment_get_description(&attachment_);
  EXPECT_EQ(out, kDesc);
  EXPECT_STREQ(out, "hello description");
}

TEST_F(PopplerAttachmentGetDescriptionTest_2273, ReturnsNullWhenDescriptionIsNull_2273) {
  attachment_.description = nullptr;

  const gchar *out = poppler_attachment_get_description(&attachment_);
  EXPECT_EQ(out, nullptr);
}

TEST_F(PopplerAttachmentGetDescriptionTest_2273, WorksWithEmptyStringDescription_2273) {
  const gchar kEmpty[] = "";
  attachment_.description = kEmpty;

  const gchar *out = poppler_attachment_get_description(&attachment_);
  ASSERT_NE(out, nullptr);
  EXPECT_EQ(out, kEmpty);
  EXPECT_STREQ(out, "");
}

TEST_F(PopplerAttachmentGetDescriptionTest_2273, ReturnsStablePointerAcrossMultipleCalls_2273) {
  const gchar kDesc[] = "stable";
  attachment_.description = kDesc;

  const gchar *out1 = poppler_attachment_get_description(&attachment_);
  const gchar *out2 = poppler_attachment_get_description(&attachment_);
  EXPECT_EQ(out1, out2);
  EXPECT_EQ(out1, kDesc);
}

TEST_F(PopplerAttachmentGetDescriptionTest_2273, ReflectsUpdatedDescriptionBetweenCalls_2273) {
  const gchar kDesc1[] = "first";
  const gchar kDesc2[] = "second";

  attachment_.description = kDesc1;
  const gchar *out1 = poppler_attachment_get_description(&attachment_);
  EXPECT_EQ(out1, kDesc1);
  EXPECT_STREQ(out1, "first");

  attachment_.description = kDesc2;
  const gchar *out2 = poppler_attachment_get_description(&attachment_);
  EXPECT_EQ(out2, kDesc2);
  EXPECT_STREQ(out2, "second");
}

// Exceptional/error cases:
// There is no observable error handling in the interface for nullptr attachment.
// Passing nullptr would be undefined behavior (would likely crash), so we avoid it
// to keep tests robust and non-crashy.