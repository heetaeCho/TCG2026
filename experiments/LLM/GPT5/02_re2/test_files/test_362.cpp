// File: capture_names_walker_test_362.cc
#include <gtest/gtest.h>
#include <map>
#include <string>
#include <type_traits>

// Forward declarations matching the provided interface only.
// (Linkage will bind to the actual implementation in the codebase.)
namespace re2 {
  typedef int Ignored;

  class Regexp;  // Not used directly in these tests.

  class CaptureNamesWalker {
   public:
    CaptureNamesWalker();
    ~CaptureNamesWalker();

    // Observable API
    std::map<int, std::string>* TakeMap();

    // Present in interface but not exercised here due to missing Regexp construction.
    virtual Ignored PreVisit(Regexp* re, Ignored ignored, bool* stop);
    virtual Ignored ShortVisit(Regexp* re, Ignored ignored);

    // Non-copyable, non-assignable per interface (no need to use in tests).
   private:
    CaptureNamesWalker(const CaptureNamesWalker&) = delete;
    CaptureNamesWalker& operator=(const CaptureNamesWalker&) = delete;
  };
}  // namespace re2

class CaptureNamesWalkerTest_362 : public ::testing::Test {};

// [362] Type trait check for the public typedef.
TEST_F(CaptureNamesWalkerTest_362, IgnoredIsInt_362) {
  static_assert(std::is_same<re2::Ignored, int>::value,
                "re2::Ignored must be an alias of int");
  SUCCEED(); // Explicit success for clarity in output.
}

// [362] Destruction of a default-constructed object should be safe.
TEST_F(CaptureNamesWalkerTest_362, DefaultConstructAndDestroy_NoCrash_362) {
  re2::CaptureNamesWalker walker;  // Constructor should not throw.
  // End of scope: destructor should not crash.
  SUCCEED();
}

// [362] TakeMap can be called multiple times; after the first call, it should return nullptr.
// This asserts idempotence of the "take" operation without inferring internal details.
TEST_F(CaptureNamesWalkerTest_362, TakeMap_IsIdempotent_362) {
  re2::CaptureNamesWalker walker;

  std::map<int, std::string>* first = walker.TakeMap();
  std::map<int, std::string>* second = walker.TakeMap();

  // After one "take", a subsequent take should yield nullptr (nothing left to take).
  EXPECT_EQ(second, nullptr);

  // Clean up only if ownership was actually transferred (non-null).
  delete first;
}

// [362] If TakeMap transfers ownership, the returned map should remain valid
// even after the walker is destroyed. We guard with a skip if the first call returns nullptr,
// which is permissible behavior for a fresh object per the interface (no guarantees provided).
TEST_F(CaptureNamesWalkerTest_362, TakeMap_OwnershipAfterDestruction_362) {
  auto* walker = new re2::CaptureNamesWalker();
  std::map<int, std::string>* taken = walker->TakeMap();

  // Destroy the walker. If ownership was transferred, it should not delete 'taken'.
  delete walker;

  if (taken == nullptr) {
    GTEST_SKIP() << "TakeMap returned nullptr; no ownership to verify for this build/config.";
  }

  // Using the taken map should be safe if ownership was transferred.
  ASSERT_NE(taken, nullptr);
  EXPECT_TRUE(taken->empty());
  (*taken)[1] = "name";
  EXPECT_EQ(taken->at(1), "name");

  // Caller is responsible for deleting if ownership was transferred.
  delete taken;
}
