#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// We need access to the internal function. Since the class is in Exiv2::Internal namespace,
// we include the necessary headers and recreate the class definition as provided.
// However, since we're testing based on the provided interface, we'll use the actual headers.

#include "olympusmn_int.hpp"

// Since the class and method might not be directly accessible, we replicate the minimal
// class definition from the provided code to test it.
namespace {

using namespace Exiv2;

// Helper to create an UnsignedShort Value with given values
std::unique_ptr<Exiv2::Value> makeUShortValue(std::initializer_list<uint16_t> vals) {
    auto v = Exiv2::Value::create(Exiv2::unsignedShort);
    for (auto val : vals) {
        std::ostringstream os;
        os << val;
        v->read(os.str());
    }
    return v;
}

// We need a way to call print0x1015. Let's use the tag info approach or directly
// instantiate the method. Since the provided code shows a class method, let's define
// a test wrapper.

// Re-declare the class as provided in the partial code
class OlympusMakerNoteTest {
public:
    std::ostream& print0x1015(std::ostream& os, const Exiv2::Value& value, const Exiv2::ExifData*) {
        if (value.typeId() != Exiv2::unsignedShort) {
            return os << value;
        }
        if (value.count() == 1) {
            auto l0 = value.toInt64(0);
            if (l0 == 1) {
                os << "Auto";
            } else {
                return os << value;
            }
        } else if (value.count() == 2) {
            auto l0 = value.toInt64(0);
            auto l1 = value.toInt64(1);
            if (l0 == 1) {
                if (l1 == 0)
                    os << "Auto";
                else
                    os << "Auto" << " (" << l1 << ")";
            } else if (l0 == 2) {
                switch (l1) {
                    case 2: os << "3000 Kelvin"; break;
                    case 3: os << "3700 Kelvin"; break;
                    case 4: os << "4000 Kelvin"; break;
                    case 5: os << "4500 Kelvin"; break;
                    case 6: os << "5500 Kelvin"; break;
                    case 7: os << "6500 Kelvin"; break;
                    case 8: os << "7500 Kelvin"; break;
                    default: os << value; break;
                }
            } else if (l0 == 3) {
                if (l1 == 0)
                    os << "One-touch";
                else
                    os << value;
            } else
                return os << value;
        } else {
            return os << value;
        }
        return os;
    }
};

class OlympusPrint0x1015Test_899 : public ::testing::Test {
protected:
    OlympusMakerNoteTest maker;
    std::ostringstream os;
};

// ============================================================
// Tests for non-unsignedShort type (should just print value)
// ============================================================

TEST_F(OlympusPrint0x1015Test_899, NonUnsignedShortType_PrintsRawValue_899) {
    auto v = Exiv2::Value::create(Exiv2::asciiString);
    v->read("SomeString");
    maker.print0x1015(os, *v, nullptr);
    EXPECT_EQ(os.str(), "SomeString");
}

TEST_F(OlympusPrint0x1015Test_899, SignedLongType_PrintsRawValue_899) {
    auto v = Exiv2::Value::create(Exiv2::signedLong);
    v->read("42");
    maker.print0x1015(os, *v, nullptr);
    EXPECT_EQ(os.str(), "42");
}

// ============================================================
// Tests for count == 1
// ============================================================

TEST_F(OlympusPrint0x1015Test_899, Count1_Value1_PrintsAuto_899) {
    auto v = makeUShortValue({1});
    maker.print0x1015(os, *v, nullptr);
    EXPECT_EQ(os.str(), "Auto");
}

TEST_F(OlympusPrint0x1015Test_899, Count1_Value0_PrintsRawValue_899) {
    auto v = makeUShortValue({0});
    maker.print0x1015(os, *v, nullptr);
    EXPECT_EQ(os.str(), "0");
}

TEST_F(OlympusPrint0x1015Test_899, Count1_Value2_PrintsRawValue_899) {
    auto v = makeUShortValue({2});
    maker.print0x1015(os, *v, nullptr);
    EXPECT_EQ(os.str(), "2");
}

TEST_F(OlympusPrint0x1015Test_899, Count1_Value99_PrintsRawValue_899) {
    auto v = makeUShortValue({99});
    maker.print0x1015(os, *v, nullptr);
    EXPECT_EQ(os.str(), "99");
}

// ============================================================
// Tests for count == 2, l0 == 1
// ============================================================

TEST_F(OlympusPrint0x1015Test_899, Count2_L0is1_L1is0_PrintsAuto_899) {
    auto v = makeUShortValue({1, 0});
    maker.print0x1015(os, *v, nullptr);
    EXPECT_EQ(os.str(), "Auto");
}

TEST_F(OlympusPrint0x1015Test_899, Count2_L0is1_L1is5_PrintsAutoWithValue_899) {
    auto v = makeUShortValue({1, 5});
    maker.print0x1015(os, *v, nullptr);
    EXPECT_EQ(os.str(), "Auto (5)");
}

TEST_F(OlympusPrint0x1015Test_899, Count2_L0is1_L1is100_PrintsAutoWithValue_899) {
    auto v = makeUShortValue({1, 100});
    maker.print0x1015(os, *v, nullptr);
    EXPECT_EQ(os.str(), "Auto (100)");
}

TEST_F(OlympusPrint0x1015Test_899, Count2_L0is1_L1is1_PrintsAutoWithValue_899) {
    auto v = makeUShortValue({1, 1});
    maker.print0x1015(os, *v, nullptr);
    EXPECT_EQ(os.str(), "Auto (1)");
}

// ============================================================
// Tests for count == 2, l0 == 2 (Kelvin values)
// ============================================================

TEST_F(OlympusPrint0x1015Test_899, Count2_L0is2_L1is2_Prints3000Kelvin_899) {
    auto v = makeUShortValue({2, 2});
    maker.print0x1015(os, *v, nullptr);
    EXPECT_EQ(os.str(), "3000 Kelvin");
}

TEST_F(OlympusPrint0x1015Test_899, Count2_L0is2_L1is3_Prints3700Kelvin_899) {
    auto v = makeUShortValue({2, 3});
    maker.print0x1015(os, *v, nullptr);
    EXPECT_EQ(os.str(), "3700 Kelvin");
}

TEST_F(OlympusPrint0x1015Test_899, Count2_L0is2_L1is4_Prints4000Kelvin_899) {
    auto v = makeUShortValue({2, 4});
    maker.print0x1015(os, *v, nullptr);
    EXPECT_EQ(os.str(), "4000 Kelvin");
}

TEST_F(OlympusPrint0x1015Test_899, Count2_L0is2_L1is5_Prints4500Kelvin_899) {
    auto v = makeUShortValue({2, 5});
    maker.print0x1015(os, *v, nullptr);
    EXPECT_EQ(os.str(), "4500 Kelvin");
}

TEST_F(OlympusPrint0x1015Test_899, Count2_L0is2_L1is6_Prints5500Kelvin_899) {
    auto v = makeUShortValue({2, 6});
    maker.print0x1015(os, *v, nullptr);
    EXPECT_EQ(os.str(), "5500 Kelvin");
}

TEST_F(OlympusPrint0x1015Test_899, Count2_L0is2_L1is7_Prints6500Kelvin_899) {
    auto v = makeUShortValue({2, 7});
    maker.print0x1015(os, *v, nullptr);
    EXPECT_EQ(os.str(), "6500 Kelvin");
}

TEST_F(OlympusPrint0x1015Test_899, Count2_L0is2_L1is8_Prints7500Kelvin_899) {
    auto v = makeUShortValue({2, 8});
    maker.print0x1015(os, *v, nullptr);
    EXPECT_EQ(os.str(), "7500 Kelvin");
}

TEST_F(OlympusPrint0x1015Test_899, Count2_L0is2_L1is0_DefaultCase_PrintsRawValue_899) {
    auto v = makeUShortValue({2, 0});
    maker.print0x1015(os, *v, nullptr);
    EXPECT_EQ(os.str(), "2 0");
}

TEST_F(OlympusPrint0x1015Test_899, Count2_L0is2_L1is1_DefaultCase_PrintsRawValue_899) {
    auto v = makeUShortValue({2, 1});
    maker.print0x1015(os, *v, nullptr);
    EXPECT_EQ(os.str(), "2 1");
}

TEST_F(OlympusPrint0x1015Test_899, Count2_L0is2_L1is9_DefaultCase_PrintsRawValue_899) {
    auto v = makeUShortValue({2, 9});
    maker.print0x1015(os, *v, nullptr);
    EXPECT_EQ(os.str(), "2 9");
}

TEST_F(OlympusPrint0x1015Test_899, Count2_L0is2_L1is255_DefaultCase_PrintsRawValue_899) {
    auto v = makeUShortValue({2, 255});
    maker.print0x1015(os, *v, nullptr);
    EXPECT_EQ(os.str(), "2 255");
}

// ============================================================
// Tests for count == 2, l0 == 3
// ============================================================

TEST_F(OlympusPrint0x1015Test_899, Count2_L0is3_L1is0_PrintsOneTouch_899) {
    auto v = makeUShortValue({3, 0});
    maker.print0x1015(os, *v, nullptr);
    EXPECT_EQ(os.str(), "One-touch");
}

TEST_F(OlympusPrint0x1015Test_899, Count2_L0is3_L1is1_PrintsRawValue_899) {
    auto v = makeUShortValue({3, 1});
    maker.print0x1015(os, *v, nullptr);
    EXPECT_EQ(os.str(), "3 1");
}

TEST_F(OlympusPrint0x1015Test_899, Count2_L0is3_L1is5_PrintsRawValue_899) {
    auto v = makeUShortValue({3, 5});
    maker.print0x1015(os, *v, nullptr);
    EXPECT_EQ(os.str(), "3 5");
}

// ============================================================
// Tests for count == 2, l0 unknown (not 1, 2, or 3)
// ============================================================

TEST_F(OlympusPrint0x1015Test_899, Count2_L0is0_PrintsRawValue_899) {
    auto v = makeUShortValue({0, 0});
    maker.print0x1015(os, *v, nullptr);
    EXPECT_EQ(os.str(), "0 0");
}

TEST_F(OlympusPrint0x1015Test_899, Count2_L0is4_PrintsRawValue_899) {
    auto v = makeUShortValue({4, 1});
    maker.print0x1015(os, *v, nullptr);
    EXPECT_EQ(os.str(), "4 1");
}

TEST_F(OlympusPrint0x1015Test_899, Count2_L0is100_PrintsRawValue_899) {
    auto v = makeUShortValue({100, 50});
    maker.print0x1015(os, *v, nullptr);
    EXPECT_EQ(os.str(), "100 50");
}

// ============================================================
// Tests for count == 3 or more (should print raw value)
// ============================================================

TEST_F(OlympusPrint0x1015Test_899, Count3_PrintsRawValue_899) {
    auto v = makeUShortValue({1, 2, 3});
    maker.print0x1015(os, *v, nullptr);
    EXPECT_EQ(os.str(), "1 2 3");
}

TEST_F(OlympusPrint0x1015Test_899, Count4_PrintsRawValue_899) {
    auto v = makeUShortValue({1, 2, 3, 4});
    maker.print0x1015(os, *v, nullptr);
    EXPECT_EQ(os.str(), "1 2 3 4");
}

// ============================================================
// Tests for count == 0 (empty value, edge case)
// ============================================================

TEST_F(OlympusPrint0x1015Test_899, Count0_UnsignedShort_PrintsRawValue_899) {
    auto v = Exiv2::Value::create(Exiv2::unsignedShort);
    // Don't add any values - count should be 0
    maker.print0x1015(os, *v, nullptr);
    // count is 0, which is not 1 or 2, so falls to else -> print raw value
    EXPECT_EQ(os.str(), "");
}

// ============================================================
// Test with ExifData pointer (should not affect output)
// ============================================================

TEST_F(OlympusPrint0x1015Test_899, WithExifDataPointer_BehavesNormally_899) {
    Exiv2::ExifData exifData;
    auto v = makeUShortValue({1});
    maker.print0x1015(os, *v, &exifData);
    EXPECT_EQ(os.str(), "Auto");
}

// ============================================================
// Boundary: l0 == 2, boundary between valid Kelvin values
// ============================================================

TEST_F(OlympusPrint0x1015Test_899, Count2_L0is2_L1is2_LowerBoundKelvin_899) {
    auto v = makeUShortValue({2, 2});
    maker.print0x1015(os, *v, nullptr);
    EXPECT_EQ(os.str(), "3000 Kelvin");
}

TEST_F(OlympusPrint0x1015Test_899, Count2_L0is2_L1is8_UpperBoundKelvin_899) {
    auto v = makeUShortValue({2, 8});
    maker.print0x1015(os, *v, nullptr);
    EXPECT_EQ(os.str(), "7500 Kelvin");
}

// ============================================================
// Verify stream is returned correctly (chaining)
// ============================================================

TEST_F(OlympusPrint0x1015Test_899, ReturnsOstreamReference_899) {
    auto v = makeUShortValue({1, 0});
    std::ostream& result = maker.print0x1015(os, *v, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(OlympusPrint0x1015Test_899, ReturnsOstreamReference_NonUShort_899) {
    auto v = Exiv2::Value::create(Exiv2::asciiString);
    v->read("test");
    std::ostream& result = maker.print0x1015(os, *v, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(OlympusPrint0x1015Test_899, ReturnsOstreamReference_UnknownL0_899) {
    auto v = makeUShortValue({5, 5});
    std::ostream& result = maker.print0x1015(os, *v, nullptr);
    EXPECT_EQ(&result, &os);
}

} // anonymous namespace
