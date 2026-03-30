// File: capture_names_walker_test_364.cc

#include <map>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "re2/regexp.h"

using re2::Regexp;
using re2::RegexpOp;
using re2::kRegexpCapture;

namespace {

// Recursively collect all nodes in the regexp tree (public API only).
static void CollectAll(Regexp* re, std::vector<Regexp*>& out) {
  if (re == nullptr) return;
  out.push_back(re);
  const int n = re->nsub();
  if (n <= 0) return;
  Regexp** subs = re->sub();
  for (int i = 0; i < n; ++i) {
    CollectAll(subs[i], out);
  }
}

// Find all capture nodes.
static std::vector<Regexp*> FindCaptures(Regexp* root) {
  std::vector<Regexp*> nodes, caps;
  CollectAll(root, nodes);
  for (auto* n : nodes) {
    if (n->op() == kRegexpCapture) caps.push_back(n);
  }
  return caps;
}

// Find first named capture node (name() != nullptr), or nullptr if none.
static Regexp* FindFirstNamedCapture(Regexp* root) {
  auto caps = FindCaptures(root);
  for (auto* c : caps) {
    if (c->name() != nullptr) return c;
  }
  return nullptr;
}

}  // namespace

// ---------- Tests ----------

TEST(CaptureNamesWalkerTest_364, PreVisit_ReturnsIgnoredUnchanged_364) {
  // Parse a simple literal; ensures non-capture node.
  auto flags = static_cast<Regexp::ParseFlags>(0);
  Regexp* root = Regexp::Parse("a", flags, /*status=*/nullptr);
  ASSERT_NE(root, nullptr);

  re2::CaptureNamesWalker walker;

  bool stop = false;
  int ignored_in = 123;
  int ignored_out = walker.PreVisit(root, ignored_in, &stop);

  EXPECT_EQ(ignored_out, ignored_in);     // Must return the same value.
  EXPECT_FALSE(stop);                      // PreVisit doesn't modify stop.
  // Since it's not a capture, no map should have been created.
  std::map<int, std::string>* m = walker.TakeMap();
  EXPECT_EQ(m, nullptr);

  root->Decref();
}

TEST(CaptureNamesWalkerTest_364, NonCaptureNode_DoesNotCreateMap_364) {
  auto flags = static_cast<Regexp::ParseFlags>(0);
  // Create a literal node directly.
  Regexp* lit = Regexp::NewLiteral('x', flags);
  ASSERT_NE(lit, nullptr);

  re2::CaptureNamesWalker walker;

  bool stop = false;
  (void)walker.PreVisit(lit, /*ignored=*/0, &stop);

  // No capture + no name => map remains null.
  std::map<int, std::string>* m = walker.TakeMap();
  EXPECT_EQ(m, nullptr);

  lit->Decref();
}

TEST(CaptureNamesWalkerTest_364, UnnamedCapture_DoesNotCreateMap_364) {
  auto flags = static_cast<Regexp::ParseFlags>(0);

  Regexp* lit = Regexp::NewLiteral('y', flags);
  ASSERT_NE(lit, nullptr);

  // Wrap in an unnamed capturing group.
  Regexp* cap = Regexp::Capture(lit, flags, /*cap index*/1);
  ASSERT_NE(cap, nullptr);
  // Sanity: unnamed capture should have null name pointer.
  EXPECT_EQ(cap->name(), nullptr);

  re2::CaptureNamesWalker walker;
  bool stop = false;
  (void)walker.PreVisit(cap, /*ignored=*/0, &stop);

  // Since name() == nullptr, map should not be created/updated.
  std::map<int, std::string>* m = walker.TakeMap();
  EXPECT_EQ(m, nullptr);

  cap->Decref();  // also releases 'lit'
}

TEST(CaptureNamesWalkerTest_364, NamedCapture_AddsSingleEntry_364) {
  auto flags = static_cast<Regexp::ParseFlags>(0);

  // Parse a pattern with a single *named* capture.
  // RE2 supports Python-style named groups: (?P<name>...)
  Regexp* root = Regexp::Parse("(?P<foo>a)", flags, /*status=*/nullptr);
  ASSERT_NE(root, nullptr);

  // Find the capture node with a name via the public API.
  Regexp* named = FindFirstNamedCapture(root);
  ASSERT_NE(named, nullptr);
  ASSERT_NE(named->name(), nullptr);  // Confirm it is actually named.

  re2::CaptureNamesWalker walker;
  bool stop = false;
  (void)walker.PreVisit(named, /*ignored=*/0, &stop);

  std::map<int, std::string>* m = walker.TakeMap();
  ASSERT_NE(m, nullptr);
  // Expect exactly one entry mapping cap() -> *name()
  ASSERT_EQ(m->size(), 1u);
  auto it = m->find(named->cap());
  ASSERT_NE(it, m->end());
  EXPECT_EQ(it->second, *named->name());

  delete m;  // TakeMap() transfers ownership.
  root->Decref();
}

TEST(CaptureNamesWalkerTest_364, MultipleNamedCaptures_AllInserted_364) {
  auto flags = static_cast<Regexp::ParseFlags>(0);

  // Two named groups with different names (and usually different cap indices).
  Regexp* root = Regexp::Parse("(?P<first>a)(?P<second>b)", flags, /*status=*/nullptr);
  ASSERT_NE(root, nullptr);

  auto caps = FindCaptures(root);
  // Keep only named captures.
  std::vector<Regexp*> named_caps;
  for (auto* c : caps) {
    if (c->name() != nullptr) named_caps.push_back(c);
  }
  ASSERT_GE(named_caps.size(), 2u) << "Expected at least two named captures";

  re2::CaptureNamesWalker walker;
  bool stop = false;

  for (auto* c : named_caps) {
    (void)walker.PreVisit(c, /*ignored=*/0, &stop);
  }

  std::map<int, std::string>* m = walker.TakeMap();
  ASSERT_NE(m, nullptr);

  // Verify each named capture created/updated its entry by observable API.
  for (auto* c : named_caps) {
    auto it = m->find(c->cap());
    ASSERT_NE(it, m->end());
    ASSERT_NE(c->name(), nullptr);
    EXPECT_EQ(it->second, *c->name());
  }

  delete m;
  root->Decref();
}
