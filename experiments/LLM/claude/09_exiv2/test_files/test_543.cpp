#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>

using namespace Exiv2;

class AfPointTest_543 : public ::testing::Test {
protected:
    ExifData ed;
    
    void SetUp() override {
        ed.clear();
    }
};

// Test that afPoint returns end() when ExifData is empty
TEST_F(AfPointTest_543, EmptyExifDataReturnsEnd_543) {
    ExifData::const_iterator it = afPoint(ed);
    EXPECT_EQ(it, ed.end());
}

// Test that afPoint finds CanonPi.AFPointsUsed
TEST_F(AfPointTest_543, FindsCanonPiAFPointsUsed_543) {
    ed["Exif.CanonPi.AFPointsUsed"] = uint16_t(3);
    ExifData::const_iterator it = afPoint(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.CanonPi.AFPointsUsed");
}

// Test that afPoint finds CanonPi.AFPointsUsed20D
TEST_F(AfPointTest_543, FindsCanonPiAFPointsUsed20D_543) {
    ed["Exif.CanonPi.AFPointsUsed20D"] = uint16_t(5);
    ExifData::const_iterator it = afPoint(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.CanonPi.AFPointsUsed20D");
}

// Test that afPoint finds CanonSi.AFPointUsed
TEST_F(AfPointTest_543, FindsCanonSiAFPointUsed_543) {
    ed["Exif.CanonSi.AFPointUsed"] = uint16_t(1);
    ExifData::const_iterator it = afPoint(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.CanonSi.AFPointUsed");
}

// Test that afPoint finds CanonCs.AFPoint
TEST_F(AfPointTest_543, FindsCanonCsAFPoint_543) {
    ed["Exif.CanonCs.AFPoint"] = uint16_t(2);
    ExifData::const_iterator it = afPoint(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.CanonCs.AFPoint");
}

// Test that afPoint finds MinoltaCs7D.AFPoints
TEST_F(AfPointTest_543, FindsMinoltaCs7DAFPoints_543) {
    ed["Exif.MinoltaCs7D.AFPoints"] = uint16_t(7);
    ExifData::const_iterator it = afPoint(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.MinoltaCs7D.AFPoints");
}

// Test that afPoint finds Nikon1.AFFocusPos
TEST_F(AfPointTest_543, FindsNikon1AFFocusPos_543) {
    ed["Exif.Nikon1.AFFocusPos"] = uint16_t(0);
    ExifData::const_iterator it = afPoint(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Nikon1.AFFocusPos");
}

// Test that afPoint finds NikonAf.AFPoint
TEST_F(AfPointTest_543, FindsNikonAfAFPoint_543) {
    ed["Exif.NikonAf.AFPoint"] = uint16_t(4);
    ExifData::const_iterator it = afPoint(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.NikonAf.AFPoint");
}

// Test that afPoint finds NikonAf.AFPointsInFocus
TEST_F(AfPointTest_543, FindsNikonAfAFPointsInFocus_543) {
    ed["Exif.NikonAf.AFPointsInFocus"] = uint16_t(6);
    ExifData::const_iterator it = afPoint(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.NikonAf.AFPointsInFocus");
}

// Test that afPoint finds NikonAf2.AFPointsUsed
TEST_F(AfPointTest_543, FindsNikonAf2AFPointsUsed_543) {
    ed["Exif.NikonAf2.AFPointsUsed"] = uint16_t(8);
    ExifData::const_iterator it = afPoint(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.NikonAf2.AFPointsUsed");
}

// Test that afPoint finds NikonAf2.PrimaryAFPoint
TEST_F(AfPointTest_543, FindsNikonAf2PrimaryAFPoint_543) {
    ed["Exif.NikonAf2.PrimaryAFPoint"] = uint16_t(9);
    ExifData::const_iterator it = afPoint(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.NikonAf2.PrimaryAFPoint");
}

// Test that afPoint finds OlympusFi.AFPoint
TEST_F(AfPointTest_543, FindsOlympusFiAFPoint_543) {
    ed["Exif.OlympusFi.AFPoint"] = uint16_t(10);
    ExifData::const_iterator it = afPoint(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.OlympusFi.AFPoint");
}

// Test that afPoint finds Pentax.AFPoint
TEST_F(AfPointTest_543, FindsPentaxAFPoint_543) {
    ed["Exif.Pentax.AFPoint"] = uint16_t(11);
    ExifData::const_iterator it = afPoint(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Pentax.AFPoint");
}

// Test that afPoint finds Pentax.AFPointInFocus
TEST_F(AfPointTest_543, FindsPentaxAFPointInFocus_543) {
    ed["Exif.Pentax.AFPointInFocus"] = uint16_t(12);
    ExifData::const_iterator it = afPoint(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Pentax.AFPointInFocus");
}

// Test that afPoint finds PentaxDng.AFPoint
TEST_F(AfPointTest_543, FindsPentaxDngAFPoint_543) {
    ed["Exif.PentaxDng.AFPoint"] = uint16_t(13);
    ExifData::const_iterator it = afPoint(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.PentaxDng.AFPoint");
}

// Test that afPoint finds PentaxDng.AFPointInFocus
TEST_F(AfPointTest_543, FindsPentaxDngAFPointInFocus_543) {
    ed["Exif.PentaxDng.AFPointInFocus"] = uint16_t(14);
    ExifData::const_iterator it = afPoint(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.PentaxDng.AFPointInFocus");
}

// Test that afPoint finds Sony1.AFPointSelected
TEST_F(AfPointTest_543, FindsSony1AFPointSelected_543) {
    ed["Exif.Sony1.AFPointSelected"] = uint16_t(15);
    ExifData::const_iterator it = afPoint(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony1.AFPointSelected");
}

// Test that afPoint finds Sony2.AFPointSelected
TEST_F(AfPointTest_543, FindsSony2AFPointSelected_543) {
    ed["Exif.Sony2.AFPointSelected"] = uint16_t(16);
    ExifData::const_iterator it = afPoint(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony2.AFPointSelected");
}

// Test that afPoint finds Casio.AFPoint
TEST_F(AfPointTest_543, FindsCasioAFPoint_543) {
    ed["Exif.Casio.AFPoint"] = uint16_t(22);
    ExifData::const_iterator it = afPoint(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Casio.AFPoint");
}

// Test that afPoint finds Casio2.AFPointPosition
TEST_F(AfPointTest_543, FindsCasio2AFPointPosition_543) {
    ed["Exif.Casio2.AFPointPosition"] = uint16_t(23);
    ExifData::const_iterator it = afPoint(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Casio2.AFPointPosition");
}

// Test priority: when multiple matching keys exist, the first one in the priority list is returned
TEST_F(AfPointTest_543, PriorityFirstKeyWins_543) {
    // CanonCs.AFPoint is at index 3 in the keys list
    // NikonAf.AFPoint is at index 6 in the keys list
    // So CanonCs.AFPoint should be returned since it has higher priority
    ed["Exif.NikonAf.AFPoint"] = uint16_t(100);
    ed["Exif.CanonCs.AFPoint"] = uint16_t(200);
    ExifData::const_iterator it = afPoint(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.CanonCs.AFPoint");
}

// Test priority: CanonPi.AFPointsUsed has highest priority
TEST_F(AfPointTest_543, CanonPiHasHighestPriority_543) {
    ed["Exif.Casio2.AFPointPosition"] = uint16_t(50);
    ed["Exif.CanonPi.AFPointsUsed"] = uint16_t(1);
    ed["Exif.NikonAf2.PrimaryAFPoint"] = uint16_t(3);
    ExifData::const_iterator it = afPoint(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.CanonPi.AFPointsUsed");
}

// Test that unrelated keys don't match
TEST_F(AfPointTest_543, UnrelatedKeyReturnsEnd_543) {
    ed["Exif.Image.Make"] = "Canon";
    ed["Exif.Photo.ExposureTime"] = "1/100";
    ExifData::const_iterator it = afPoint(ed);
    EXPECT_EQ(it, ed.end());
}

// Test with a single matching key among irrelevant ones
TEST_F(AfPointTest_543, SingleMatchAmongIrrelevant_543) {
    ed["Exif.Image.Make"] = "Nikon";
    ed["Exif.Photo.FocalLength"] = "50";
    ed["Exif.NikonAf.AFPointsInFocus"] = uint16_t(42);
    ed["Exif.Image.Model"] = "D800";
    ExifData::const_iterator it = afPoint(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.NikonAf.AFPointsInFocus");
}

// Test Sony1Cs.LocalAFAreaPoint
TEST_F(AfPointTest_543, FindsSony1CsLocalAFAreaPoint_543) {
    ed["Exif.Sony1Cs.LocalAFAreaPoint"] = uint16_t(17);
    ExifData::const_iterator it = afPoint(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony1Cs.LocalAFAreaPoint");
}

// Test Sony2Cs.LocalAFAreaPoint
TEST_F(AfPointTest_543, FindsSony2CsLocalAFAreaPoint_543) {
    ed["Exif.Sony2Cs.LocalAFAreaPoint"] = uint16_t(18);
    ExifData::const_iterator it = afPoint(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony2Cs.LocalAFAreaPoint");
}

// Test Sony1Cs2.LocalAFAreaPoint
TEST_F(AfPointTest_543, FindsSony1Cs2LocalAFAreaPoint_543) {
    ed["Exif.Sony1Cs2.LocalAFAreaPoint"] = uint16_t(19);
    ExifData::const_iterator it = afPoint(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony1Cs2.LocalAFAreaPoint");
}

// Test Sony2Cs2.LocalAFAreaPoint
TEST_F(AfPointTest_543, FindsSony2Cs2LocalAFAreaPoint_543) {
    ed["Exif.Sony2Cs2.LocalAFAreaPoint"] = uint16_t(20);
    ExifData::const_iterator it = afPoint(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony2Cs2.LocalAFAreaPoint");
}

// Test Sony1MltCsA100.LocalAFAreaPoint
TEST_F(AfPointTest_543, FindsSony1MltCsA100LocalAFAreaPoint_543) {
    ed["Exif.Sony1MltCsA100.LocalAFAreaPoint"] = uint16_t(21);
    ExifData::const_iterator it = afPoint(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony1MltCsA100.LocalAFAreaPoint");
}

// Test that the function is consistent across multiple calls
TEST_F(AfPointTest_543, ConsistentResults_543) {
    ed["Exif.Pentax.AFPoint"] = uint16_t(5);
    ExifData::const_iterator it1 = afPoint(ed);
    ExifData::const_iterator it2 = afPoint(ed);
    ASSERT_NE(it1, ed.end());
    ASSERT_NE(it2, ed.end());
    EXPECT_EQ(it1->key(), it2->key());
}

// Test with const ExifData
TEST_F(AfPointTest_543, WorksWithConstExifData_543) {
    ed["Exif.OlympusFi.AFPoint"] = uint16_t(99);
    const ExifData& constEd = ed;
    ExifData::const_iterator it = afPoint(constEd);
    ASSERT_NE(it, constEd.end());
    EXPECT_EQ(it->key(), "Exif.OlympusFi.AFPoint");
}
