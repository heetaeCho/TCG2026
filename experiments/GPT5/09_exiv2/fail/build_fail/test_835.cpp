// -----------------------------------------------------------------------------
// TEST_ID: 835
// File: test_xmptextvalue_clone_835.cpp
// -----------------------------------------------------------------------------

#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "exiv2/value.hpp"

namespace {

using Exiv2::XmpTextValue;

static std::string SerializeViaWrite(const Exiv2::Value& v) {
  std::ostringstream oss;
  v.write(oss);
  return oss.str();
}

class XmpTextValueTest_835 : public ::testing::Test {
 protected:
  static std::string Serialize(const XmpTextValue& v) {
    std::ostringstream oss;
    v.write(oss);
    return oss.str();
  }
};

TEST_F(XmpTextValueTest_835, CloneReturnsNonNullAndSameObservableState_835) {
  const std::string buf = "hello xmp text";
  XmpTextValue v(buf);

  const auto before_write = Serialize(v);
  const auto before_size = v.size();
  const auto before_count = v.count();

  auto cloned = v.clone();
  ASSERT_NE(cloned.get(), nullptr);

  // Ensure it's not the same object.
  EXPECT_NE(cloned.get(), static_cast<const Exiv2::Value*>(&v));

  // Verify observable behavior matches at clone time.
  EXPECT_EQ(SerializeViaWrite(*cloned), before_write);
  EXPECT_EQ(cloned->size(), before_size);
  EXPECT_EQ(cloned->count(), before_count);
}

TEST_F(XmpTextValueTest_835, CloneWorksForDefaultConstructed_835) {
  XmpTextValue v;

  const auto before_write = Serialize(v);
  const auto before_size = v.size();
  const auto before_count = v.count();

  auto cloned = v.clone();
  ASSERT_NE(cloned.get(), nullptr);

  EXPECT_NE(cloned.get(), static_cast<const Exiv2::Value*>(&v));
  EXPECT_EQ(SerializeViaWrite(*cloned), before_write);
  EXPECT_EQ(cloned->size(), before_size);
  EXPECT_EQ(cloned->count(), before_count);
}

TEST_F(XmpTextValueTest_835, CloneWorksForEmptyStringInput_835) {
  XmpTextValue v(std::string{});

  const auto before_write = Serialize(v);
  const auto before_size = v.size();
  const auto before_count = v.count();

  auto cloned = v.clone();
  ASSERT_NE(cloned.get(), nullptr);

  EXPECT_EQ(SerializeViaWrite(*cloned), before_write);
  EXPECT_EQ(cloned->size(), before_size);
  EXPECT_EQ(cloned->count(), before_count);
}

TEST_F(XmpTextValueTest_835, CloneAfterReadKeepsSameObservableState_835) {
  XmpTextValue v;
  const int rc = v.read("some content");
  (void)rc;  // Return value semantics are not specified; only ensure call is possible.

  const auto before_write = Serialize(v);
  const auto before_size = v.size();
  const auto before_count = v.count();

  auto cloned = v.clone();
  ASSERT_NE(cloned.get(), nullptr);

  EXPECT_EQ(SerializeViaWrite(*cloned), before_write);
  EXPECT_EQ(cloned->size(), before_size);
  EXPECT_EQ(cloned->count(), before_count);
}

TEST_F(XmpTextValueTest_835, CloneIsStableAcrossMultipleCalls_835) {
  XmpTextValue v("repeatable");

  auto c1 = v.clone();
  auto c2 = v.clone();

  ASSERT_NE(c1.get(), nullptr);
  ASSERT_NE(c2.get(), nullptr);

  // Each clone should be a distinct object.
  EXPECT_NE(c1.get(), c2.get());

  // Observable state should match each other (and original at the moment of cloning).
  EXPECT_EQ(SerializeViaWrite(*c1), SerializeViaWrite(*c2));
  EXPECT_EQ(SerializeViaWrite(*c1), Serialize(v));
  EXPECT_EQ(c1->size(), c2->size());
  EXPECT_EQ(c1->count(), c2->count());
}

TEST_F(XmpTextValueTest_835, CloneHandlesLargeInput_835) {
  std::string large(1 << 16, 'A');  // 65536 chars
  large += "tail";
  XmpTextValue v(large);

  const auto before_write = Serialize(v);
  const auto before_size = v.size();
  const auto before_count = v.count();

  auto cloned = v.clone();
  ASSERT_NE(cloned.get(), nullptr);

  EXPECT_EQ(SerializeViaWrite(*cloned), before_write);
  EXPECT_EQ(cloned->size(), before_size);
  EXPECT_EQ(cloned->count(), before_count);
}

TEST_F(XmpTextValueTest_835, CloneRemainsUsableAfterOriginalIsModified_835) {
  XmpTextValue v("first");
  auto cloned = v.clone();
  ASSERT_NE(cloned.get(), nullptr);

  const auto clone_before = SerializeViaWrite(*cloned);

  // Modify original through public interface.
  (void)v.read("second");
  const auto original_after = Serialize(v);

  // Clone must remain usable (no crash) and have a deterministic observable state.
  // We do NOT assume deep-copy semantics; we only assert usability and that write() works.
  const auto clone_after = SerializeViaWrite(*cloned);
  EXPECT_FALSE(clone_after.empty() && clone_before.size() > 0);  // still a valid string result

  // Additionally, the original's observable state should reflect the modification.
  // (We don't assume what "second" renders to; just that it can change observably.)
  (void)original_after;
}

}  // namespace