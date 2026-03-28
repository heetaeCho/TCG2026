#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxState.h"

using ::testing::Test;

// Since we must treat implementation as a black box,
// tests are limited strictly to observable public interface behavior.

class GfxImageColorMapTest_539 : public Test {
protected:
    // Helper to construct a color with predictable values
    GfxColor makeColor(GfxColorComp base) {
        GfxColor color;
        for (int i = 0; i < 32; ++i) {
            color.c[i] = static_cast<GfxColorComp>(base + i);
        }
        return color;
    }
};

// ------------------------------------------------------------
// Normal operation
// ------------------------------------------------------------

TEST_F(GfxImageColorMapTest_539, SetMatteColorStoresAndReturnsColor_539) {
    // Arrange
    GfxImageColorMap *map = reinterpret_cast<GfxImageColorMap*>(
        operator new(sizeof(GfxImageColorMap))
    );

    GfxColor inputColor = makeColor(10);

    // Act
    map->setMatteColor(&inputColor);
    const GfxColor* stored = map->getMatteColor();

    // Assert
    ASSERT_NE(stored, nullptr);
    for (int i = 0; i < 32; ++i) {
        EXPECT_EQ(stored->c[i], inputColor.c[i]);
    }

    operator delete(map);
}

TEST_F(GfxImageColorMapTest_539, SetMatteColorOverwritesPreviousValue_539) {
    GfxImageColorMap *map = reinterpret_cast<GfxImageColorMap*>(
        operator new(sizeof(GfxImageColorMap))
    );

    GfxColor first = makeColor(0);
    GfxColor second = makeColor(100);

    map->setMatteColor(&first);
    map->setMatteColor(&second);

    const GfxColor* stored = map->getMatteColor();
    ASSERT_NE(stored, nullptr);

    for (int i = 0; i < 32; ++i) {
        EXPECT_EQ(stored->c[i], second.c[i]);
    }

    operator delete(map);
}

// ------------------------------------------------------------
// Boundary conditions
// ------------------------------------------------------------

TEST_F(GfxImageColorMapTest_539, SetMatteColorHandlesZeroValues_539) {
    GfxImageColorMap *map = reinterpret_cast<GfxImageColorMap*>(
        operator new(sizeof(GfxImageColorMap))
    );

    GfxColor zeroColor{};
    for (int i = 0; i < 32; ++i) {
        zeroColor.c[i] = static_cast<GfxColorComp>(0);
    }

    map->setMatteColor(&zeroColor);
    const GfxColor* stored = map->getMatteColor();

    ASSERT_NE(stored, nullptr);
    for (int i = 0; i < 32; ++i) {
        EXPECT_EQ(stored->c[i], 0);
    }

    operator delete(map);
}

TEST_F(GfxImageColorMapTest_539, SetMatteColorHandlesMaxComponentValues_539) {
    GfxImageColorMap *map = reinterpret_cast<GfxImageColorMap*>(
        operator new(sizeof(GfxImageColorMap))
    );

    GfxColor maxColor{};
    for (int i = 0; i < 32; ++i) {
        maxColor.c[i] = std::numeric_limits<GfxColorComp>::max();
    }

    map->setMatteColor(&maxColor);
    const GfxColor* stored = map->getMatteColor();

    ASSERT_NE(stored, nullptr);
    for (int i = 0; i < 32; ++i) {
        EXPECT_EQ(stored->c[i], std::numeric_limits<GfxColorComp>::max());
    }

    operator delete(map);
}

// ------------------------------------------------------------
// Exceptional cases (observable via interface)
// ------------------------------------------------------------

TEST_F(GfxImageColorMapTest_539, GetMatteColorReturnsNonNullAfterSet_539) {
    GfxImageColorMap *map = reinterpret_cast<GfxImageColorMap*>(
        operator new(sizeof(GfxImageColorMap))
    );

    GfxColor color = makeColor(5);

    map->setMatteColor(&color);
    const GfxColor* stored = map->getMatteColor();

    EXPECT_NE(stored, nullptr);

    operator delete(map);
}

// ------------------------------------------------------------
// Interface consistency
// ------------------------------------------------------------

TEST_F(GfxImageColorMapTest_539, MultipleSequentialSetMatteColorCalls_539) {
    GfxImageColorMap *map = reinterpret_cast<GfxImageColorMap*>(
        operator new(sizeof(GfxImageColorMap))
    );

    for (int iteration = 0; iteration < 5; ++iteration) {
        GfxColor color = makeColor(static_cast<GfxColorComp>(iteration * 20));
        map->setMatteColor(&color);
        const GfxColor* stored = map->getMatteColor();

        ASSERT_NE(stored, nullptr);
        for (int i = 0; i < 32; ++i) {
            EXPECT_EQ(stored->c[i], color.c[i]);
        }
    }

    operator delete(map);
}