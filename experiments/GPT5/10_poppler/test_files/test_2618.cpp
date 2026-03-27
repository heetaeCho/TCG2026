// File: HtmlFonts_getColor_test_2618.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <type_traits>
#include <cstring>
#include <limits>
#include <utility>

// Class under test
#include "TestProjects/poppler/utils/HtmlFonts.h"

// Poppler types needed to construct HtmlFont's dependencies.
#include "poppler/GfxFont.h"
#include "poppler/GfxState.h"
#include "poppler/Object.h"
#include "goo/GooString.h"

namespace {

template <typename T>
constexpr bool HasEqOperatorV =
    requires(const T &a, const T &b) { { a == b } -> std::convertible_to<bool>; };

template <typename T>
void ExpectColorEqual(const T &a, const T &b)
{
    if constexpr (HasEqOperatorV<T>) {
        EXPECT_TRUE(a == b);
    } else if constexpr (std::is_trivially_copyable_v<T>) {
        EXPECT_EQ(0, std::memcmp(&a, &b, sizeof(T)));
    } else {
        // Best-effort fallback: if the type isn't comparable, at least ensure the calls succeeded.
        SUCCEED();
    }
}

// Minimal concrete GfxFont to satisfy HtmlFont's ctor dependency without relying on Poppler internals.
class TestGfxFont final : public GfxFont
{
public:
    TestGfxFont(const char *tagA,
                Ref idA,
                std::optional<std::string> &&nameA,
                GfxFontType typeA,
                Ref embFontIDA)
        : GfxFont(tagA, idA, std::move(nameA), typeA, embFontIDA)
    {
        // Make common getters safe to call.
        ok = true;
        family = std::make_unique<GooString>("TestFamily");
        stretch = Stretch::Normal;
        weight = Weight::W400;
        flags = 0;
        embFontName.reset();
        hasToUnicode = false;
        encodingName.clear();

        fontMat = {0, 0, 0, 0, 0, 0};
        fontBBox = {0, 0, 0, 0};
        missingWidth = 0.0;
        ascent = 0.0;
        descent = 0.0;
    }

    const CharCodeToUnicode *getToUnicode() const override { return nullptr; }

    int getNextChar(const char * /*s*/,
                    int /*len*/,
                    CharCode * /*code*/,
                    Unicode const ** /*u*/,
                    int * /*uLen*/,
                    double * /*dx*/,
                    double * /*dy*/,
                    double * /*ox*/,
                    double * /*oy*/) const override
    {
        return 0;
    }
};

static GfxRGB MakeRgb(unsigned short r, unsigned short g, unsigned short b)
{
    GfxRGB rgb;
    rgb.r = r;
    rgb.g = g;
    rgb.b = b;
    return rgb;
}

class HtmlFontTest_2618 : public ::testing::Test
{
protected:
    static TestGfxFont MakeFont()
    {
        // Use a deterministic Ref; emb font id invalid.
        Ref id;
        id.num = 1;
        id.gen = 0;

        return TestGfxFont("F1", id, std::optional<std::string>(std::string("TestFont")), fontType1, Ref::INVALID());
    }
};

} // namespace

TEST_F(HtmlFontTest_2618, GetColor_CanBeCalledOnConstObject_2618)
{
    const auto gfxFont = MakeFont();
    const HtmlFont font(gfxFont, /*_size=*/12, MakeRgb(0, 0, 0), /*opacity=*/1.0);

    // Compile-time check: getColor() is callable on const.
    const HtmlFont &constRef = font;
    (void)constRef.getColor();

    SUCCEED();
}

TEST_F(HtmlFontTest_2618, GetColor_ReturnValueIsStableAcrossCalls_2618)
{
    const auto gfxFont = MakeFont();
    const HtmlFont font(gfxFont, /*_size=*/12, MakeRgb(0, 0, 0), /*opacity=*/1.0);

    const auto c1 = font.getColor();
    const auto c2 = font.getColor();

    ExpectColorEqual(c1, c2);
}

TEST_F(HtmlFontTest_2618, GetColor_DoesNotDependOnNonConstAccess_2618)
{
    const auto gfxFont = MakeFont();
    HtmlFont font(gfxFont, /*_size=*/12, MakeRgb(0, 0, 0), /*opacity=*/1.0);

    const auto c1 = font.getColor();

    const HtmlFont &constRef = font;
    const auto c2 = constRef.getColor();

    ExpectColorEqual(c1, c2);
}

TEST_F(HtmlFontTest_2618, GetColor_BoundaryOpacityZero_DoesNotCrashAndIsStable_2618)
{
    const auto gfxFont = MakeFont();
    const HtmlFont font(gfxFont, /*_size=*/12, MakeRgb(0, 0, 0), /*opacity=*/0.0);

    const auto c1 = font.getColor();
    const auto c2 = font.getColor();

    ExpectColorEqual(c1, c2);
}

TEST_F(HtmlFontTest_2618, GetColor_BoundaryOpacityOne_DoesNotCrashAndIsStable_2618)
{
    const auto gfxFont = MakeFont();
    const HtmlFont font(gfxFont, /*_size=*/12, MakeRgb(65535, 65535, 65535), /*opacity=*/1.0);

    const auto c1 = font.getColor();
    const auto c2 = font.getColor();

    ExpectColorEqual(c1, c2);
}

TEST_F(HtmlFontTest_2618, GetColor_BoundarySizeZero_DoesNotCrash_2618)
{
    const auto gfxFont = MakeFont();
    const HtmlFont font(gfxFont, /*_size=*/0, MakeRgb(0, 0, 0), /*opacity=*/1.0);

    (void)font.getColor();
    SUCCEED();
}

TEST_F(HtmlFontTest_2618, GetColor_BoundaryNegativeSize_DoesNotCrash_2618)
{
    const auto gfxFont = MakeFont();
    const HtmlFont font(gfxFont, /*_size=*/-1, MakeRgb(0, 0, 0), /*opacity=*/1.0);

    (void)font.getColor();
    SUCCEED();
}

TEST_F(HtmlFontTest_2618, GetColor_OpacityNaN_DoesNotCrash_2618)
{
    const auto gfxFont = MakeFont();
    const double nanOpacity = std::numeric_limits<double>::quiet_NaN();
    const HtmlFont font(gfxFont, /*_size=*/12, MakeRgb(0, 0, 0), /*opacity=*/nanOpacity);

    (void)font.getColor();
    SUCCEED();
}