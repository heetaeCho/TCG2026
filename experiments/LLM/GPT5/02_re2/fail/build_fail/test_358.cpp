// File: named_captures_walker_take_map_test_358.cc
#include <gtest/gtest.h>
#include <map>
#include <string>

namespace re2 {
// Minimal forward declaration strictly to access the public interface under test.
// We do NOT re-implement or infer any internal logic.
class NamedCapturesWalker {
public:
  NamedCapturesWalker();
  ~NamedCapturesWalker();
  std::map<std::string, int>* TakeMap();
};
}  // namespace re2

// ----------------------------------------------------------------------------
// Tests verify only observable effects of TakeMap():
//  - It returns the current pointer (which may be nullptr).
//  - It resets the internal pointer so subsequent calls return nullptr.
// No assumptions are made about how/when the map_ is allocated or populated.
// ----------------------------------------------------------------------------

TEST(NamedCapturesWalkerTest_358, TakeMapInitiallyNull_358) {
  // Given a freshly constructed walker
  re2::NamedCapturesWalker walker;

  // When calling TakeMap immediately
  // Then (per known constructor in dependencies) it should be nullptr.
  // If the underlying implementation ever changes to allocate eagerly,
  // this assertion would catch that behavioral change.
  std::map<std::string, int>* first = walker.TakeMap();
  EXPECT_EQ(first, nullptr);
}

TEST(NamedCapturesWalkerTest_358, TakeMapResetsPointer_358) {
  re2::NamedCapturesWalker walker;

  // First call: may return nullptr or a valid pointer depending on implementation.
  std::map<std::string, int>* first = walker.TakeMap();

  // Second call must observe the reset performed by the first call and return nullptr.
  std::map<std::string, int>* second = walker.TakeMap();
  EXPECT_EQ(second, nullptr);

  // Cleanup if ownership was transferred and a map was actually returned.
  delete first;
}

TEST(NamedCapturesWalkerTest_358, RepeatedTakeMapAlwaysNullAfterFirst_358) {
  re2::NamedCapturesWalker walker;

  // Drain whatever pointer is currently held (could be nullptr).
  std::map<std::string, int>* first = walker.TakeMap();

  // Subsequent calls must remain safe and return nullptr consistently.
  std::map<std::string, int>* second = walker.TakeMap();
  std::map<std::string, int>* third  = walker.TakeMap();
  EXPECT_EQ(second, nullptr);
  EXPECT_EQ(third, nullptr);

  // Cleanup if needed.
  delete first;
}
