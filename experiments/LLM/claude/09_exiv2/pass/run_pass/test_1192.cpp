#include <gtest/gtest.h>
#include <cstdint>

// Reproduce the TAG enum as defined in the dependency
enum TAG {
    ftyp = 1718909296,
    avci = 1635148649,
    avcs = 1635148659,
    avif = 1635150182,
    avio = 1635150191,
    avis = 1635150195,
    heic = 1751476579,
    heif = 1751476582,
    heim = 1751476589,
    heis = 1751476595,
    heix = 1751476600,
    j2is = 1781688691,
    j2ki = 1781689193,
    mif1 = 1835623985,
    crx  = 1668446240,
    jxl  = 1786276896,
    moov = 1836019574,
    meta = 1835365473,
    mdat = 1835295092,
    uuid = 1970628964,
    dinf = 1684631142,
    iprp = 1768977008,
    ipco = 1768973167,
    iinf = 1768517222,
    iloc = 1768714083,
    ispe = 1769173093,
    infe = 1768842853,
    ipma = 1768975713,
    cmt1 = 1129141297,
    cmt2 = 1129141298,
    cmt3 = 1129141299,
    cmt4 = 1129141300,
    colr = 1668246642,
    exif = 1165519206,
    xml  = 2020437024,
    brob = 1651666786,
    thmb = 1414024514,
    prvw = 1347573335
};

// Reproduce the function under test as defined in the source
namespace Exiv2 {
static bool skipBox(uint32_t box) {
    return box == 0 || box == TAG::mdat;
}
}  // namespace Exiv2

class SkipBoxTest_1192 : public ::testing::Test {
protected:
};

// Test that box value 0 should be skipped
TEST_F(SkipBoxTest_1192, ZeroBoxShouldBeSkipped_1192) {
    EXPECT_TRUE(Exiv2::skipBox(0));
}

// Test that mdat box should be skipped
TEST_F(SkipBoxTest_1192, MdatBoxShouldBeSkipped_1192) {
    EXPECT_TRUE(Exiv2::skipBox(TAG::mdat));
}

// Test that mdat box value as raw uint32_t should be skipped
TEST_F(SkipBoxTest_1192, MdatRawValueShouldBeSkipped_1192) {
    EXPECT_TRUE(Exiv2::skipBox(1835295092));
}

// Test that ftyp box should NOT be skipped
TEST_F(SkipBoxTest_1192, FtypBoxShouldNotBeSkipped_1192) {
    EXPECT_FALSE(Exiv2::skipBox(TAG::ftyp));
}

// Test that moov box should NOT be skipped
TEST_F(SkipBoxTest_1192, MoovBoxShouldNotBeSkipped_1192) {
    EXPECT_FALSE(Exiv2::skipBox(TAG::moov));
}

// Test that meta box should NOT be skipped
TEST_F(SkipBoxTest_1192, MetaBoxShouldNotBeSkipped_1192) {
    EXPECT_FALSE(Exiv2::skipBox(TAG::meta));
}

// Test that uuid box should NOT be skipped
TEST_F(SkipBoxTest_1192, UuidBoxShouldNotBeSkipped_1192) {
    EXPECT_FALSE(Exiv2::skipBox(TAG::uuid));
}

// Test that heic box should NOT be skipped
TEST_F(SkipBoxTest_1192, HeicBoxShouldNotBeSkipped_1192) {
    EXPECT_FALSE(Exiv2::skipBox(TAG::heic));
}

// Test that avif box should NOT be skipped
TEST_F(SkipBoxTest_1192, AvifBoxShouldNotBeSkipped_1192) {
    EXPECT_FALSE(Exiv2::skipBox(TAG::avif));
}

// Test that iloc box should NOT be skipped
TEST_F(SkipBoxTest_1192, IlocBoxShouldNotBeSkipped_1192) {
    EXPECT_FALSE(Exiv2::skipBox(TAG::iloc));
}

// Test that iprp box should NOT be skipped
TEST_F(SkipBoxTest_1192, IprpBoxShouldNotBeSkipped_1192) {
    EXPECT_FALSE(Exiv2::skipBox(TAG::iprp));
}

// Test that exif box should NOT be skipped
TEST_F(SkipBoxTest_1192, ExifBoxShouldNotBeSkipped_1192) {
    EXPECT_FALSE(Exiv2::skipBox(TAG::exif));
}

// Test that xml box should NOT be skipped
TEST_F(SkipBoxTest_1192, XmlBoxShouldNotBeSkipped_1192) {
    EXPECT_FALSE(Exiv2::skipBox(TAG::xml));
}

// Test that colr box should NOT be skipped
TEST_F(SkipBoxTest_1192, ColrBoxShouldNotBeSkipped_1192) {
    EXPECT_FALSE(Exiv2::skipBox(TAG::colr));
}

// Boundary: value 1 should NOT be skipped
TEST_F(SkipBoxTest_1192, ValueOneShouldNotBeSkipped_1192) {
    EXPECT_FALSE(Exiv2::skipBox(1));
}

// Boundary: UINT32_MAX should NOT be skipped
TEST_F(SkipBoxTest_1192, Uint32MaxShouldNotBeSkipped_1192) {
    EXPECT_FALSE(Exiv2::skipBox(UINT32_MAX));
}

// Boundary: value just below mdat should NOT be skipped
TEST_F(SkipBoxTest_1192, ValueBelowMdatShouldNotBeSkipped_1192) {
    EXPECT_FALSE(Exiv2::skipBox(TAG::mdat - 1));
}

// Boundary: value just above mdat should NOT be skipped
TEST_F(SkipBoxTest_1192, ValueAboveMdatShouldNotBeSkipped_1192) {
    EXPECT_FALSE(Exiv2::skipBox(TAG::mdat + 1));
}

// Test arbitrary non-special value should NOT be skipped
TEST_F(SkipBoxTest_1192, ArbitraryValueShouldNotBeSkipped_1192) {
    EXPECT_FALSE(Exiv2::skipBox(42));
}

// Test all other TAG enum values are NOT skipped
TEST_F(SkipBoxTest_1192, AllNonMdatTagsShouldNotBeSkipped_1192) {
    uint32_t tags[] = {
        TAG::ftyp, TAG::avci, TAG::avcs, TAG::avif, TAG::avio, TAG::avis,
        TAG::heic, TAG::heif, TAG::heim, TAG::heis, TAG::heix,
        TAG::j2is, TAG::j2ki, TAG::mif1, TAG::crx, TAG::jxl,
        TAG::moov, TAG::meta, TAG::uuid, TAG::dinf, TAG::iprp,
        TAG::ipco, TAG::iinf, TAG::iloc, TAG::ispe, TAG::infe,
        TAG::ipma, TAG::cmt1, TAG::cmt2, TAG::cmt3, TAG::cmt4,
        TAG::colr, TAG::exif, TAG::xml, TAG::brob, TAG::thmb, TAG::prvw
    };
    for (uint32_t tag : tags) {
        EXPECT_FALSE(Exiv2::skipBox(tag)) << "Tag value " << tag << " should not be skipped";
    }
}

// Test that dinf box should NOT be skipped
TEST_F(SkipBoxTest_1192, DinfBoxShouldNotBeSkipped_1192) {
    EXPECT_FALSE(Exiv2::skipBox(TAG::dinf));
}

// Test that crx box should NOT be skipped
TEST_F(SkipBoxTest_1192, CrxBoxShouldNotBeSkipped_1192) {
    EXPECT_FALSE(Exiv2::skipBox(TAG::crx));
}

// Test that jxl box should NOT be skipped
TEST_F(SkipBoxTest_1192, JxlBoxShouldNotBeSkipped_1192) {
    EXPECT_FALSE(Exiv2::skipBox(TAG::jxl));
}

// Test that brob box should NOT be skipped
TEST_F(SkipBoxTest_1192, BrobBoxShouldNotBeSkipped_1192) {
    EXPECT_FALSE(Exiv2::skipBox(TAG::brob));
}
