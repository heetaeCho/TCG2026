// poppler_link_mapping_free_test_2485.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <glib.h>

extern "C" {

// Include the public struct definition.
#include "poppler-page.h"

// Forward declaration is enough for black-box pointer passing in tests.
struct _PopplerAction;
typedef struct _PopplerAction PopplerAction;

// Function under test (implemented in poppler-page.cc).
void poppler_link_mapping_free(PopplerLinkMapping *mapping);

// Dependency we want to observe (called only when mapping->action != nullptr).
void poppler_action_free(PopplerAction *action);
}  // extern "C"

using ::testing::_;
using ::testing::StrictMock;

namespace {

class PopplerActionFreeMock {
public:
  MOCK_METHOD(void, Free, (PopplerAction *action), ());
};

PopplerActionFreeMock* g_action_free_mock = nullptr;

// Link-time substitution hook:
// The production code calls poppler_action_free(). In unit tests, we provide
// a symbol with the same name to observe calls without touching internals.
extern "C" void poppler_action_free(PopplerAction *action) {
  if (g_action_free_mock) {
    g_action_free_mock->Free(action);
  }
}

class PopplerLinkMappingFreeTest_2485 : public ::testing::Test {
protected:
  void SetUp() override {
    g_action_free_mock = &mock_;
  }
  void TearDown() override {
    g_action_free_mock = nullptr;
  }

  StrictMock<PopplerActionFreeMock> mock_;
};

TEST_F(PopplerLinkMappingFreeTest_2485, NullMappingDoesNothing_2485) {
  // Should be a no-op (no crash, no external interaction).
  EXPECT_CALL(mock_, Free(_)).Times(0);

  poppler_link_mapping_free(nullptr);
}

TEST_F(PopplerLinkMappingFreeTest_2485, MappingWithNullActionDoesNotCallActionFree_2485) {
  EXPECT_CALL(mock_, Free(_)).Times(0);

  PopplerLinkMapping *mapping = g_slice_new0(PopplerLinkMapping);
  ASSERT_NE(mapping, nullptr);
  mapping->action = nullptr;

  poppler_link_mapping_free(mapping);
}

TEST_F(PopplerLinkMappingFreeTest_2485, MappingWithNonNullActionCallsActionFreeOnceWithSamePointer_2485) {
  PopplerLinkMapping *mapping = g_slice_new0(PopplerLinkMapping);
  ASSERT_NE(mapping, nullptr);

  // Use a stable, non-null sentinel pointer; it is never dereferenced.
  PopplerAction *sentinel_action = reinterpret_cast<PopplerAction*>(static_cast<uintptr_t>(0x1));
  mapping->action = sentinel_action;

  EXPECT_CALL(mock_, Free(sentinel_action)).Times(1);

  poppler_link_mapping_free(mapping);
}

}  // namespace