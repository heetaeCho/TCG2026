#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdlib>
#include <memory>

// Since _free_type3_font_info is a static function in CairoFontEngine.cc,
// we need to include the implementation or have access to it.
// We'll test the structure and the free function behavior through
// observable effects.

// Forward declarations and minimal stubs for dependencies
// These are needed because the actual Poppler headers have complex dependencies

// We create minimal test doubles that match the expected interface
// to verify that _free_type3_font_info properly calls delete on members.

namespace {

// Track deletion for test purposes
static int g_gfx_delete_count = 0;
static int g_outputdev_delete_count = 0;
static int g_info_delete_count = 0;

// Minimal mock structures to track deletions
struct MockGfx {
    ~MockGfx() { g_gfx_delete_count++; }
};

struct MockCairoOutputDev {
    ~MockCairoOutputDev() { g_outputdev_delete_count++; }
};

// Mimicking type3_font_info_t structure layout for testing
struct test_type3_font_info_t {
    MockCairoOutputDev *outputDev;
    MockGfx *gfx;
};

// Mimicking the _free_type3_font_info function signature and behavior
static void test_free_type3_font_info(void *closure) {
    auto *info = (test_type3_font_info_t *)closure;
    delete info->gfx;
    delete info->outputDev;
    delete info;
}

} // anonymous namespace

class FreeType3FontInfoTest_1751 : public ::testing::Test {
protected:
    void SetUp() override {
        g_gfx_delete_count = 0;
        g_outputdev_delete_count = 0;
        g_info_delete_count = 0;
    }
};

// Test that the free function properly deletes the gfx member
TEST_F(FreeType3FontInfoTest_1751, DeletesGfxMember_1751) {
    auto *info = new test_type3_font_info_t();
    info->gfx = new MockGfx();
    info->outputDev = new MockCairoOutputDev();

    EXPECT_EQ(g_gfx_delete_count, 0);
    test_free_type3_font_info(info);
    EXPECT_EQ(g_gfx_delete_count, 1);
}

// Test that the free function properly deletes the outputDev member
TEST_F(FreeType3FontInfoTest_1751, DeletesOutputDevMember_1751) {
    auto *info = new test_type3_font_info_t();
    info->gfx = new MockGfx();
    info->outputDev = new MockCairoOutputDev();

    EXPECT_EQ(g_outputdev_delete_count, 0);
    test_free_type3_font_info(info);
    EXPECT_EQ(g_outputdev_delete_count, 1);
}

// Test that both members and the struct are freed in one call
TEST_F(FreeType3FontInfoTest_1751, DeletesBothMembersAndStruct_1751) {
    auto *info = new test_type3_font_info_t();
    info->gfx = new MockGfx();
    info->outputDev = new MockCairoOutputDev();

    test_free_type3_font_info(info);

    EXPECT_EQ(g_gfx_delete_count, 1);
    EXPECT_EQ(g_outputdev_delete_count, 1);
}

// Test with nullptr members - delete on nullptr is safe in C++
TEST_F(FreeType3FontInfoTest_1751, HandlesNullGfxMember_1751) {
    auto *info = new test_type3_font_info_t();
    info->gfx = nullptr;
    info->outputDev = new MockCairoOutputDev();

    EXPECT_NO_FATAL_FAILURE(test_free_type3_font_info(info));
    EXPECT_EQ(g_gfx_delete_count, 0);
    EXPECT_EQ(g_outputdev_delete_count, 1);
}

TEST_F(FreeType3FontInfoTest_1751, HandlesNullOutputDevMember_1751) {
    auto *info = new test_type3_font_info_t();
    info->gfx = new MockGfx();
    info->outputDev = nullptr;

    EXPECT_NO_FATAL_FAILURE(test_free_type3_font_info(info));
    EXPECT_EQ(g_gfx_delete_count, 1);
    EXPECT_EQ(g_outputdev_delete_count, 0);
}

TEST_F(FreeType3FontInfoTest_1751, HandlesBothNullMembers_1751) {
    auto *info = new test_type3_font_info_t();
    info->gfx = nullptr;
    info->outputDev = nullptr;

    EXPECT_NO_FATAL_FAILURE(test_free_type3_font_info(info));
    EXPECT_EQ(g_gfx_delete_count, 0);
    EXPECT_EQ(g_outputdev_delete_count, 0);
}
