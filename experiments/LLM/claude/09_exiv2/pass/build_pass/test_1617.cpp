#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "sonymn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class SonyMakerNoteTest_1617 : public ::testing::Test {
protected:
    std::ostringstream os;

    // Helper to create ExifData with a specific model
    void setModel(ExifData& exifData, const std::string& model) {
        exifData["Exif.Image.Model"] = model;
    }

    // Helper to create a Value with a single integer
    std::unique_ptr<Value> createValue(int64_t val) {
        auto v = Value::create(unsignedShort);
        std::string s = std::to_string(val);
        v->read(s);
        return v;
    }

    // Helper to create a Value with multiple integers
    std::unique_ptr<Value> createMultiValue(const std::vector<int64_t>& vals) {
        auto v = Value::create(unsignedShort);
        std::string s;
        for (size_t i = 0; i < vals.size(); ++i) {
            if (i > 0) s += " ";
            s += std::to_string(vals[i]);
        }
        v->read(s);
        return v;
    }
};

// Test: null metadata returns value in parentheses
TEST_F(SonyMakerNoteTest_1617, PrintLensZoomPosition_NullMetadata_1617) {
    auto value = createValue(512);
    SonyMakerNote::printSonyMisc2bLensZoomPosition(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: multi-count value returns value in parentheses
TEST_F(SonyMakerNoteTest_1617, PrintLensZoomPosition_MultiCount_1617) {
    auto value = createMultiValue({512, 100});
    ExifData exifData;
    setModel(exifData, "ILCE-7M3");
    SonyMakerNote::printSonyMisc2bLensZoomPosition(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: SLT model returns "n/a"
TEST_F(SonyMakerNoteTest_1617, PrintLensZoomPosition_SLTModel_1617) {
    auto value = createValue(512);
    ExifData exifData;
    setModel(exifData, "SLT-A77");
    SonyMakerNote::printSonyMisc2bLensZoomPosition(os, *value, &exifData);
    std::string result = os.str();
    // Should contain "n/a" (possibly translated)
    EXPECT_TRUE(result.find("n/a") != std::string::npos || result.find("N/A") != std::string::npos || result.find("Not applicable") != std::string::npos);
}

// Test: HV model returns "n/a"
TEST_F(SonyMakerNoteTest_1617, PrintLensZoomPosition_HVModel_1617) {
    auto value = createValue(512);
    ExifData exifData;
    setModel(exifData, "HV");
    SonyMakerNote::printSonyMisc2bLensZoomPosition(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_TRUE(result.find("n/a") != std::string::npos || result.find("N/A") != std::string::npos || result.find("Not applicable") != std::string::npos);
}

// Test: ILCA model returns "n/a"
TEST_F(SonyMakerNoteTest_1617, PrintLensZoomPosition_ILCAModel_1617) {
    auto value = createValue(512);
    ExifData exifData;
    setModel(exifData, "ILCA-99M2");
    SonyMakerNote::printSonyMisc2bLensZoomPosition(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_TRUE(result.find("n/a") != std::string::npos || result.find("N/A") != std::string::npos || result.find("Not applicable") != std::string::npos);
}

// Test: ILCE model (non-SLT, non-HV, non-ILCA) returns percentage
TEST_F(SonyMakerNoteTest_1617, PrintLensZoomPosition_ILCEModel_ReturnsPercentage_1617) {
    auto value = createValue(1024);
    ExifData exifData;
    setModel(exifData, "ILCE-7M3");
    SonyMakerNote::printSonyMisc2bLensZoomPosition(os, *value, &exifData);
    std::string result = os.str();
    // 1024 / 10.24 = 100, so should be "100%"
    EXPECT_TRUE(result.find("100%") != std::string::npos);
}

// Test: value 0 returns "0%"
TEST_F(SonyMakerNoteTest_1617, PrintLensZoomPosition_ZeroValue_1617) {
    auto value = createValue(0);
    ExifData exifData;
    setModel(exifData, "ILCE-7M3");
    SonyMakerNote::printSonyMisc2bLensZoomPosition(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_TRUE(result.find("0%") != std::string::npos);
}

// Test: value 512 returns approximately "50%"
TEST_F(SonyMakerNoteTest_1617, PrintLensZoomPosition_MidValue_1617) {
    auto value = createValue(512);
    ExifData exifData;
    setModel(exifData, "ILCE-7M3");
    SonyMakerNote::printSonyMisc2bLensZoomPosition(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_TRUE(result.find("50%") != std::string::npos);
}

// Test: NEX model (non-SLT, non-HV, non-ILCA) returns percentage
TEST_F(SonyMakerNoteTest_1617, PrintLensZoomPosition_NEXModel_ReturnsPercentage_1617) {
    auto value = createValue(256);
    ExifData exifData;
    setModel(exifData, "NEX-7");
    SonyMakerNote::printSonyMisc2bLensZoomPosition(os, *value, &exifData);
    std::string result = os.str();
    // 256 / 10.24 = 25, so should be "25%"
    EXPECT_TRUE(result.find("25%") != std::string::npos);
}

// Test: SLT- prefix at various positions in model name
TEST_F(SonyMakerNoteTest_1617, PrintLensZoomPosition_SLTInModelName_1617) {
    auto value = createValue(512);
    ExifData exifData;
    setModel(exifData, "Sony SLT-A65");
    SonyMakerNote::printSonyMisc2bLensZoomPosition(os, *value, &exifData);
    std::string result = os.str();
    // Model contains "SLT-" so should return n/a
    EXPECT_TRUE(result.find("n/a") != std::string::npos || result.find("N/A") != std::string::npos || result.find("Not applicable") != std::string::npos);
}

// Test: model with HV substring
TEST_F(SonyMakerNoteTest_1617, PrintLensZoomPosition_ModelContainsHV_1617) {
    auto value = createValue(512);
    ExifData exifData;
    setModel(exifData, "Sony HV Model");
    SonyMakerNote::printSonyMisc2bLensZoomPosition(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_TRUE(result.find("n/a") != std::string::npos || result.find("N/A") != std::string::npos || result.find("Not applicable") != std::string::npos);
}

// Test: Rounding behavior for non-integer percentage
TEST_F(SonyMakerNoteTest_1617, PrintLensZoomPosition_RoundingBehavior_1617) {
    // 100 / 10.24 ≈ 9.765625, lround => 10
    auto value = createValue(100);
    ExifData exifData;
    setModel(exifData, "ILCE-7M3");
    SonyMakerNote::printSonyMisc2bLensZoomPosition(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_TRUE(result.find("10%") != std::string::npos);
}

// Test: Empty ExifData (no model tag) - should return value in parentheses
TEST_F(SonyMakerNoteTest_1617, PrintLensZoomPosition_EmptyExifData_1617) {
    auto value = createValue(512);
    ExifData exifData;
    // No model set
    SonyMakerNote::printSonyMisc2bLensZoomPosition(os, *value, &exifData);
    std::string result = os.str();
    // getModel should fail, returning value in parentheses
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: ILCA- at start of model returns n/a
TEST_F(SonyMakerNoteTest_1617, PrintLensZoomPosition_ILCAAtStart_1617) {
    auto value = createValue(768);
    ExifData exifData;
    setModel(exifData, "ILCA-77M2");
    SonyMakerNote::printSonyMisc2bLensZoomPosition(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_TRUE(result.find("n/a") != std::string::npos || result.find("N/A") != std::string::npos || result.find("Not applicable") != std::string::npos);
}

// Test: DSC model (not SLT, HV, ILCA) returns percentage
TEST_F(SonyMakerNoteTest_1617, PrintLensZoomPosition_DSCModel_1617) {
    auto value = createValue(768);
    ExifData exifData;
    setModel(exifData, "DSC-RX100M5");
    SonyMakerNote::printSonyMisc2bLensZoomPosition(os, *value, &exifData);
    std::string result = os.str();
    // 768 / 10.24 = 75, so should be "75%"
    EXPECT_TRUE(result.find("75%") != std::string::npos);
}
