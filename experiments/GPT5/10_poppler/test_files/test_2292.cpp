// File: poppler-action-build-goto-remote-test_2292.cc

#include <gtest/gtest.h>

#include <cstring>

// Poppler core
#include "Object.h"
#include "goo/GooString.h"
#include "poppler/Link.h"

// Poppler glib
#include "glib/poppler-action.h"

// NOTE: build_goto_remote() is static in poppler-action.cc.
// To test it directly, we compile it into this test translation unit.
#include "glib/poppler-action.cc"

namespace {

class BuildGotoRemoteTest_2292 : public ::testing::Test {
protected:
  void SetUp() override { std::memset(&action_, 0, sizeof(action_)); }

  void TearDown() override {
    // Best-effort cleanup to avoid leaks if PopplerAction has a public free helper.
    // Not all builds expose it, so guard by declaration presence via ADL isn't possible here.
    // If your tree has poppler_action_free(), feel free to replace this with it.
    //
    // For now, we only free what we can safely observe as plain pointers.
    if (action_.goto_remote.file_name) {
      g_free(action_.goto_remote.file_name);
      action_.goto_remote.file_name = nullptr;
    }
    if (action_.goto_remote.dest) {
      // PopplerDest is typically a boxed type; if poppler_dest_free exists, use it.
      // In many Poppler GLib builds PopplerDest is a plain struct allocated with g_new0
      // and freed with g_free. If your build differs, adjust accordingly.
      g_free(action_.goto_remote.dest);
      action_.goto_remote.dest = nullptr;
    }
  }

  // Tries to create a LinkGoToR that is OK and exposes a named destination (dest == nullptr).
  // We do not assume which Object type (name vs string) LinkGoToR accepts for named destinations;
  // we probe via the public isOk()/getNamedDest()/getDest() interface.
  static std::unique_ptr<LinkGoToR> MakeOkNamedDestLink(const char *file, const char *named) {
    // fileSpecObj as a string
    auto fileStr = std::make_unique<GooString>(file);
    Object fileObj;
    fileObj.initString(fileStr.get());

    // Attempt 1: destObj as name
    Object destNameObj;
    destNameObj.initName(named);

    auto link1 = std::make_unique<LinkGoToR>(&fileObj, &destNameObj);
    if (link1 && link1->isOk() && link1->getDest() == nullptr && link1->getNamedDest() != nullptr) {
      // Transfer ownership of GooString used by Object: Object takes ownership in Poppler.
      // Prevent double delete by releasing our unique_ptr.
      (void)fileStr.release();
      return link1;
    }

    // Attempt 2: destObj as string
    auto fileStr2 = std::make_unique<GooString>(file);
    Object fileObj2;
    fileObj2.initString(fileStr2.get());

    auto namedStr = std::make_unique<GooString>(named);
    Object destStrObj;
    destStrObj.initString(namedStr.get());

    auto link2 = std::make_unique<LinkGoToR>(&fileObj2, &destStrObj);
    if (link2 && link2->isOk() && link2->getDest() == nullptr && link2->getNamedDest() != nullptr) {
      (void)fileStr2.release();
      (void)namedStr.release();
      return link2;
    }

    return nullptr;
  }

  PopplerAction action_;
};

TEST_F(BuildGotoRemoteTest_2292, NotOkLinkSetsDefaultDestAndDoesNotSetFileName_2292) {
  // Observable behavior: when link->isOk() is false, function returns early after setting dest.
  LinkGoToR link(/*fileSpecObj=*/nullptr, /*destObj=*/nullptr);

  ASSERT_FALSE(link.isOk());

  build_goto_remote(&action_, &link);

  EXPECT_EQ(action_.goto_remote.file_name, nullptr);
  EXPECT_NE(action_.goto_remote.dest, nullptr);
}

TEST_F(BuildGotoRemoteTest_2292, OkNamedDestSetsFileNameAndCreatesNamedDest_2292) {
  const char *kFile = "remote.pdf";
  const char *kNamed = "Chapter1";

  auto link = MakeOkNamedDestLink(kFile, kNamed);
  if (!link) {
    GTEST_SKIP() << "Could not construct an OK LinkGoToR with a named destination using public Object initializers.";
  }

  ASSERT_TRUE(link->isOk());
  ASSERT_NE(link->getFileName(), nullptr);
  ASSERT_EQ(link->getDest(), nullptr);
  ASSERT_NE(link->getNamedDest(), nullptr);

  build_goto_remote(&action_, link.get());

  ASSERT_NE(action_.goto_remote.file_name, nullptr);
  EXPECT_STREQ(action_.goto_remote.file_name, kFile);

  EXPECT_NE(action_.goto_remote.dest, nullptr);

  // If PopplerDest exposes a named_dest field publicly, verify it.
  // This is still "public interface" if the struct is defined in headers.
#ifdef POPPLER_DEST_NAMED
  // Some builds use POPPLER_DEST_NAMED; others name it differently.
  // We avoid assuming enum layout; if available in your headers, you can add:
  // EXPECT_EQ(action_.goto_remote.dest->type, POPPLER_DEST_NAMED);
#endif

  // Best-effort: if the struct has a named_dest member, check it.
  // (If your build makes PopplerDest opaque, remove this block.)
#if defined(__GNUC__)
  // Use a compile-time friendly approach: only compile if the member exists.
  // This relies on the headers defining PopplerDest as a struct with named_dest.
  // If it doesn't compile in your environment, delete this section.
  EXPECT_NE(action_.goto_remote.dest->named_dest, nullptr);
  EXPECT_STREQ(action_.goto_remote.dest->named_dest, kNamed);
#endif
}

TEST_F(BuildGotoRemoteTest_2292, OkWithoutDestOrNamedDestCreatesDefaultDest_2292) {
  // Attempt to create an OK link whose getDest() and getNamedDest() are both nullptr.
  auto fileStr = std::make_unique<GooString>("remote.pdf");
  Object fileObj;
  fileObj.initString(fileStr.get());

  Object destObj;
  destObj.initNull();

  LinkGoToR link(&fileObj, &destObj);

  if (!link.isOk()) {
    GTEST_SKIP() << "LinkGoToR with null dest did not become OK in this build; cannot observe the (dest==nullptr && named==nullptr) branch.";
  }

  if (link.getDest() != nullptr || link.getNamedDest() != nullptr) {
    GTEST_SKIP() << "Constructed OK LinkGoToR did not yield both getDest()==nullptr and getNamedDest()==nullptr; cannot observe that branch.";
  }

  build_goto_remote(&action_, &link);

  ASSERT_NE(action_.goto_remote.file_name, nullptr);
  EXPECT_STREQ(action_.goto_remote.file_name, "remote.pdf");
  EXPECT_NE(action_.goto_remote.dest, nullptr);
}

} // namespace