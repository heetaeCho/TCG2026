#include <gtest/gtest.h>

#include "GfxFont.h"



class GfxFontTest_1151 : public ::testing::Test {

protected:

    std::unique_ptr<GfxFont> createMockGfxFont(bool fixedWidth) {

        // Assuming there's a way to create a GfxFont with specific flags for testing

        // This is a placeholder implementation. Actual creation would depend on the codebase.

        class MockGfxFont : public GfxFont {

        public:

            explicit MockGfxFont(int flags) : GfxFont("", Ref(), "", gfxFontType1, Ref()), flags(flags) {}

            int getFlags() const override { return flags; }

        private:

            int flags;

        };

        return std::make_unique<MockGfxFont>(fixedWidth ? fontFixedWidth : 0);

    }

};



TEST_F(GfxFontTest_1151, IsFixedWidth_ReturnsTrue_WhenFlagSet_1151) {

    auto gfxFont = createMockGfxFont(true);

    EXPECT_TRUE(gfxFont->isFixedWidth());

}



TEST_F(GfxFontTest_1151, IsFixedWidth_ReturnsFalse_WhenFlagNotSet_1151) {

    auto gfxFont = createMockGfxFont(false);

    EXPECT_FALSE(gfxFont->isFixedWidth());

}
