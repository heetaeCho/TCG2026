#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

// Forward declarations and minimal stubs needed for testing

// Minimal Annot class stub
class Annot {
public:
    enum AnnotSubtype {
        typeUnknown = 0,
        typeText = 1,
        typeLink = 2,
        typeFreeText = 3,
        typeLine = 4,
        typeSquare = 5,
        typeCircle = 6,
        typePolygon = 7,
        typePolyLine = 8,
        typeHighlight = 9,
        typeUnderline = 10,
        typeSquiggly = 11,
        typeStrikeOut = 12,
        typeStamp = 13,
        typeCaret = 14,
        typeInk = 15,
        typePopup = 16,
        typeFileAttachment = 17,
        typeSound = 18,
        typeMovie = 19,
        typeWidget = 20,
        typeScreen = 21,
        typePrinterMark = 22,
        typeTrapNet = 23,
        typeWatermark = 24,
        type3D = 25,
        typeRichMedia = 26
    };

    virtual ~Annot() = default;
    virtual AnnotSubtype getType() const { return subtype_; }

    void setType(AnnotSubtype t) { subtype_ = t; }

private:
    AnnotSubtype subtype_ = typeUnknown;
};

// Poppler annotation type enum matching the glib binding
typedef enum {
    POPPLER_ANNOT_UNKNOWN = 0,
    POPPLER_ANNOT_TEXT,
    POPPLER_ANNOT_LINK,
    POPPLER_ANNOT_FREE_TEXT,
    POPPLER_ANNOT_LINE,
    POPPLER_ANNOT_SQUARE,
    POPPLER_ANNOT_CIRCLE,
    POPPLER_ANNOT_POLYGON,
    POPPLER_ANNOT_POLY_LINE,
    POPPLER_ANNOT_HIGHLIGHT,
    POPPLER_ANNOT_UNDERLINE,
    POPPLER_ANNOT_SQUIGGLY,
    POPPLER_ANNOT_STRIKE_OUT,
    POPPLER_ANNOT_STAMP,
    POPPLER_ANNOT_CARET,
    POPPLER_ANNOT_INK,
    POPPLER_ANNOT_POPUP,
    POPPLER_ANNOT_FILE_ATTACHMENT,
    POPPLER_ANNOT_SOUND,
    POPPLER_ANNOT_MOVIE,
    POPPLER_ANNOT_WIDGET,
    POPPLER_ANNOT_SCREEN,
    POPPLER_ANNOT_PRINTER_MARK,
    POPPLER_ANNOT_TRAP_NET,
    POPPLER_ANNOT_WATERMARK,
    POPPLER_ANNOT_3D
} PopplerAnnotType;

// Minimal PopplerAnnot structure
struct _PopplerAnnot {
    std::shared_ptr<Annot> annot;
    bool is_valid; // simulate GObject type check
};
typedef struct _PopplerAnnot PopplerAnnot;

// Simulate POPPLER_IS_ANNOT macro
#define POPPLER_IS_ANNOT(obj) ((obj) != nullptr && (obj)->is_valid)

// Simulate g_return_val_if_fail
#define g_return_val_if_fail(cond, val) do { if (!(cond)) return (val); } while(0)

// Simulate g_warning (no-op for tests)
#define g_warning(...) do {} while(0)

// Re-implement the function under test as it appears in the source
// (In a real scenario this would be linked from the library)
PopplerAnnotType poppler_annot_get_annot_type(PopplerAnnot *poppler_annot) {
    g_return_val_if_fail(POPPLER_IS_ANNOT(poppler_annot), POPPLER_ANNOT_UNKNOWN);

    switch (poppler_annot->annot->getType()) {
    case Annot::typeText:
        return POPPLER_ANNOT_TEXT;
    case Annot::typeLink:
        return POPPLER_ANNOT_LINK;
    case Annot::typeFreeText:
        return POPPLER_ANNOT_FREE_TEXT;
    case Annot::typeLine:
        return POPPLER_ANNOT_LINE;
    case Annot::typeSquare:
        return POPPLER_ANNOT_SQUARE;
    case Annot::typeCircle:
        return POPPLER_ANNOT_CIRCLE;
    case Annot::typePolygon:
        return POPPLER_ANNOT_POLYGON;
    case Annot::typePolyLine:
        return POPPLER_ANNOT_POLY_LINE;
    case Annot::typeHighlight:
        return POPPLER_ANNOT_HIGHLIGHT;
    case Annot::typeUnderline:
        return POPPLER_ANNOT_UNDERLINE;
    case Annot::typeSquiggly:
        return POPPLER_ANNOT_SQUIGGLY;
    case Annot::typeStrikeOut:
        return POPPLER_ANNOT_STRIKE_OUT;
    case Annot::typeStamp:
        return POPPLER_ANNOT_STAMP;
    case Annot::typeCaret:
        return POPPLER_ANNOT_CARET;
    case Annot::typeInk:
        return POPPLER_ANNOT_INK;
    case Annot::typePopup:
        return POPPLER_ANNOT_POPUP;
    case Annot::typeFileAttachment:
        return POPPLER_ANNOT_FILE_ATTACHMENT;
    case Annot::typeSound:
        return POPPLER_ANNOT_SOUND;
    case Annot::typeMovie:
        return POPPLER_ANNOT_MOVIE;
    case Annot::typeWidget:
        return POPPLER_ANNOT_WIDGET;
    case Annot::typeScreen:
        return POPPLER_ANNOT_SCREEN;
    case Annot::typePrinterMark:
        return POPPLER_ANNOT_PRINTER_MARK;
    case Annot::typeTrapNet:
        return POPPLER_ANNOT_TRAP_NET;
    case Annot::typeWatermark:
        return POPPLER_ANNOT_WATERMARK;
    case Annot::type3D:
        return POPPLER_ANNOT_3D;
    default:
        g_warning("Unsupported Annot Type");
    }

    return POPPLER_ANNOT_UNKNOWN;
}

// Test fixture
class PopplerAnnotGetAnnotTypeTest_2062 : public ::testing::Test {
protected:
    void SetUp() override {
        annot_obj_ = std::make_shared<Annot>();
        poppler_annot_.annot = annot_obj_;
        poppler_annot_.is_valid = true;
    }

    PopplerAnnot poppler_annot_;
    std::shared_ptr<Annot> annot_obj_;

    PopplerAnnotType getTypeForSubtype(Annot::AnnotSubtype subtype) {
        annot_obj_->setType(subtype);
        return poppler_annot_get_annot_type(&poppler_annot_);
    }
};

// Test NULL input returns UNKNOWN
TEST_F(PopplerAnnotGetAnnotTypeTest_2062, NullAnnotReturnsUnknown_2062) {
    PopplerAnnotType result = poppler_annot_get_annot_type(nullptr);
    EXPECT_EQ(result, POPPLER_ANNOT_UNKNOWN);
}

// Test invalid annot (is_valid == false) returns UNKNOWN
TEST_F(PopplerAnnotGetAnnotTypeTest_2062, InvalidAnnotReturnsUnknown_2062) {
    poppler_annot_.is_valid = false;
    PopplerAnnotType result = poppler_annot_get_annot_type(&poppler_annot_);
    EXPECT_EQ(result, POPPLER_ANNOT_UNKNOWN);
}

// Test typeText maps to POPPLER_ANNOT_TEXT
TEST_F(PopplerAnnotGetAnnotTypeTest_2062, TypeTextMapsCorrectly_2062) {
    EXPECT_EQ(getTypeForSubtype(Annot::typeText), POPPLER_ANNOT_TEXT);
}

// Test typeLink maps to POPPLER_ANNOT_LINK
TEST_F(PopplerAnnotGetAnnotTypeTest_2062, TypeLinkMapsCorrectly_2062) {
    EXPECT_EQ(getTypeForSubtype(Annot::typeLink), POPPLER_ANNOT_LINK);
}

// Test typeFreeText maps to POPPLER_ANNOT_FREE_TEXT
TEST_F(PopplerAnnotGetAnnotTypeTest_2062, TypeFreeTextMapsCorrectly_2062) {
    EXPECT_EQ(getTypeForSubtype(Annot::typeFreeText), POPPLER_ANNOT_FREE_TEXT);
}

// Test typeLine maps to POPPLER_ANNOT_LINE
TEST_F(PopplerAnnotGetAnnotTypeTest_2062, TypeLineMapsCorrectly_2062) {
    EXPECT_EQ(getTypeForSubtype(Annot::typeLine), POPPLER_ANNOT_LINE);
}

// Test typeSquare maps to POPPLER_ANNOT_SQUARE
TEST_F(PopplerAnnotGetAnnotTypeTest_2062, TypeSquareMapsCorrectly_2062) {
    EXPECT_EQ(getTypeForSubtype(Annot::typeSquare), POPPLER_ANNOT_SQUARE);
}

// Test typeCircle maps to POPPLER_ANNOT_CIRCLE
TEST_F(PopplerAnnotGetAnnotTypeTest_2062, TypeCircleMapsCorrectly_2062) {
    EXPECT_EQ(getTypeForSubtype(Annot::typeCircle), POPPLER_ANNOT_CIRCLE);
}

// Test typePolygon maps to POPPLER_ANNOT_POLYGON
TEST_F(PopplerAnnotGetAnnotTypeTest_2062, TypePolygonMapsCorrectly_2062) {
    EXPECT_EQ(getTypeForSubtype(Annot::typePolygon), POPPLER_ANNOT_POLYGON);
}

// Test typePolyLine maps to POPPLER_ANNOT_POLY_LINE
TEST_F(PopplerAnnotGetAnnotTypeTest_2062, TypePolyLineMapsCorrectly_2062) {
    EXPECT_EQ(getTypeForSubtype(Annot::typePolyLine), POPPLER_ANNOT_POLY_LINE);
}

// Test typeHighlight maps to POPPLER_ANNOT_HIGHLIGHT
TEST_F(PopplerAnnotGetAnnotTypeTest_2062, TypeHighlightMapsCorrectly_2062) {
    EXPECT_EQ(getTypeForSubtype(Annot::typeHighlight), POPPLER_ANNOT_HIGHLIGHT);
}

// Test typeUnderline maps to POPPLER_ANNOT_UNDERLINE
TEST_F(PopplerAnnotGetAnnotTypeTest_2062, TypeUnderlineMapsCorrectly_2062) {
    EXPECT_EQ(getTypeForSubtype(Annot::typeUnderline), POPPLER_ANNOT_UNDERLINE);
}

// Test typeSquiggly maps to POPPLER_ANNOT_SQUIGGLY
TEST_F(PopplerAnnotGetAnnotTypeTest_2062, TypeSquigglyMapsCorrectly_2062) {
    EXPECT_EQ(getTypeForSubtype(Annot::typeSquiggly), POPPLER_ANNOT_SQUIGGLY);
}

// Test typeStrikeOut maps to POPPLER_ANNOT_STRIKE_OUT
TEST_F(PopplerAnnotGetAnnotTypeTest_2062, TypeStrikeOutMapsCorrectly_2062) {
    EXPECT_EQ(getTypeForSubtype(Annot::typeStrikeOut), POPPLER_ANNOT_STRIKE_OUT);
}

// Test typeStamp maps to POPPLER_ANNOT_STAMP
TEST_F(PopplerAnnotGetAnnotTypeTest_2062, TypeStampMapsCorrectly_2062) {
    EXPECT_EQ(getTypeForSubtype(Annot::typeStamp), POPPLER_ANNOT_STAMP);
}

// Test typeCaret maps to POPPLER_ANNOT_CARET
TEST_F(PopplerAnnotGetAnnotTypeTest_2062, TypeCaretMapsCorrectly_2062) {
    EXPECT_EQ(getTypeForSubtype(Annot::typeCaret), POPPLER_ANNOT_CARET);
}

// Test typeInk maps to POPPLER_ANNOT_INK
TEST_F(PopplerAnnotGetAnnotTypeTest_2062, TypeInkMapsCorrectly_2062) {
    EXPECT_EQ(getTypeForSubtype(Annot::typeInk), POPPLER_ANNOT_INK);
}

// Test typePopup maps to POPPLER_ANNOT_POPUP
TEST_F(PopplerAnnotGetAnnotTypeTest_2062, TypePopupMapsCorrectly_2062) {
    EXPECT_EQ(getTypeForSubtype(Annot::typePopup), POPPLER_ANNOT_POPUP);
}

// Test typeFileAttachment maps to POPPLER_ANNOT_FILE_ATTACHMENT
TEST_F(PopplerAnnotGetAnnotTypeTest_2062, TypeFileAttachmentMapsCorrectly_2062) {
    EXPECT_EQ(getTypeForSubtype(Annot::typeFileAttachment), POPPLER_ANNOT_FILE_ATTACHMENT);
}

// Test typeSound maps to POPPLER_ANNOT_SOUND
TEST_F(PopplerAnnotGetAnnotTypeTest_2062, TypeSoundMapsCorrectly_2062) {
    EXPECT_EQ(getTypeForSubtype(Annot::typeSound), POPPLER_ANNOT_SOUND);
}

// Test typeMovie maps to POPPLER_ANNOT_MOVIE
TEST_F(PopplerAnnotGetAnnotTypeTest_2062, TypeMovieMapsCorrectly_2062) {
    EXPECT_EQ(getTypeForSubtype(Annot::typeMovie), POPPLER_ANNOT_MOVIE);
}

// Test typeWidget maps to POPPLER_ANNOT_WIDGET
TEST_F(PopplerAnnotGetAnnotTypeTest_2062, TypeWidgetMapsCorrectly_2062) {
    EXPECT_EQ(getTypeForSubtype(Annot::typeWidget), POPPLER_ANNOT_WIDGET);
}

// Test typeScreen maps to POPPLER_ANNOT_SCREEN
TEST_F(PopplerAnnotGetAnnotTypeTest_2062, TypeScreenMapsCorrectly_2062) {
    EXPECT_EQ(getTypeForSubtype(Annot::typeScreen), POPPLER_ANNOT_SCREEN);
}

// Test typePrinterMark maps to POPPLER_ANNOT_PRINTER_MARK
TEST_F(PopplerAnnotGetAnnotTypeTest_2062, TypePrinterMarkMapsCorrectly_2062) {
    EXPECT_EQ(getTypeForSubtype(Annot::typePrinterMark), POPPLER_ANNOT_PRINTER_MARK);
}

// Test typeTrapNet maps to POPPLER_ANNOT_TRAP_NET
TEST_F(PopplerAnnotGetAnnotTypeTest_2062, TypeTrapNetMapsCorrectly_2062) {
    EXPECT_EQ(getTypeForSubtype(Annot::typeTrapNet), POPPLER_ANNOT_TRAP_NET);
}

// Test typeWatermark maps to POPPLER_ANNOT_WATERMARK
TEST_F(PopplerAnnotGetAnnotTypeTest_2062, TypeWatermarkMapsCorrectly_2062) {
    EXPECT_EQ(getTypeForSubtype(Annot::typeWatermark), POPPLER_ANNOT_WATERMARK);
}

// Test type3D maps to POPPLER_ANNOT_3D
TEST_F(PopplerAnnotGetAnnotTypeTest_2062, Type3DMapsCorrectly_2062) {
    EXPECT_EQ(getTypeForSubtype(Annot::type3D), POPPLER_ANNOT_3D);
}

// Test typeUnknown (default case) returns POPPLER_ANNOT_UNKNOWN
TEST_F(PopplerAnnotGetAnnotTypeTest_2062, TypeUnknownReturnsUnknown_2062) {
    EXPECT_EQ(getTypeForSubtype(Annot::typeUnknown), POPPLER_ANNOT_UNKNOWN);
}

// Test typeRichMedia (not in switch, falls to default) returns POPPLER_ANNOT_UNKNOWN
TEST_F(PopplerAnnotGetAnnotTypeTest_2062, TypeRichMediaReturnsUnknown_2062) {
    EXPECT_EQ(getTypeForSubtype(Annot::typeRichMedia), POPPLER_ANNOT_UNKNOWN);
}

// Test an out-of-range enum value falls to default and returns POPPLER_ANNOT_UNKNOWN
TEST_F(PopplerAnnotGetAnnotTypeTest_2062, OutOfRangeTypeReturnsUnknown_2062) {
    EXPECT_EQ(getTypeForSubtype(static_cast<Annot::AnnotSubtype>(999)), POPPLER_ANNOT_UNKNOWN);
}

// Test that all known mapped types produce non-UNKNOWN results
TEST_F(PopplerAnnotGetAnnotTypeTest_2062, AllMappedTypesAreNotUnknown_2062) {
    std::vector<Annot::AnnotSubtype> mapped_types = {
        Annot::typeText, Annot::typeLink, Annot::typeFreeText,
        Annot::typeLine, Annot::typeSquare, Annot::typeCircle,
        Annot::typePolygon, Annot::typePolyLine, Annot::typeHighlight,
        Annot::typeUnderline, Annot::typeSquiggly, Annot::typeStrikeOut,
        Annot::typeStamp, Annot::typeCaret, Annot::typeInk,
        Annot::typePopup, Annot::typeFileAttachment, Annot::typeSound,
        Annot::typeMovie, Annot::typeWidget, Annot::typeScreen,
        Annot::typePrinterMark, Annot::typeTrapNet, Annot::typeWatermark,
        Annot::type3D
    };

    for (auto subtype : mapped_types) {
        PopplerAnnotType result = getTypeForSubtype(subtype);
        EXPECT_NE(result, POPPLER_ANNOT_UNKNOWN)
            << "Subtype " << static_cast<int>(subtype) << " should not map to UNKNOWN";
    }
}

// Test that each mapped type produces a unique PopplerAnnotType value
TEST_F(PopplerAnnotGetAnnotTypeTest_2062, AllMappedTypesProduceUniqueResults_2062) {
    std::vector<Annot::AnnotSubtype> mapped_types = {
        Annot::typeText, Annot::typeLink, Annot::typeFreeText,
        Annot::typeLine, Annot::typeSquare, Annot::typeCircle,
        Annot::typePolygon, Annot::typePolyLine, Annot::typeHighlight,
        Annot::typeUnderline, Annot::typeSquiggly, Annot::typeStrikeOut,
        Annot::typeStamp, Annot::typeCaret, Annot::typeInk,
        Annot::typePopup, Annot::typeFileAttachment, Annot::typeSound,
        Annot::typeMovie, Annot::typeWidget, Annot::typeScreen,
        Annot::typePrinterMark, Annot::typeTrapNet, Annot::typeWatermark,
        Annot::type3D
    };

    std::set<PopplerAnnotType> results;
    for (auto subtype : mapped_types) {
        PopplerAnnotType result = getTypeForSubtype(subtype);
        EXPECT_TRUE(results.find(result) == results.end())
            << "Duplicate result for subtype " << static_cast<int>(subtype);
        results.insert(result);
    }
    EXPECT_EQ(results.size(), mapped_types.size());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
