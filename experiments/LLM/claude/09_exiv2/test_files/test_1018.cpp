#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>

// Forward declarations for the functions and types we need
namespace Exiv2 {
namespace Internal {

struct TagDetails {
    int64_t val_;
    const char* label_;
    bool operator==(int64_t key) const { return val_ == key; }
};

extern const TagDetails minoltaSonyLensID[];

std::ostream& resolvedLens(std::ostream& os, long lensID, long index);

} // namespace Internal

// We need the find function template
template <typename T, int N>
const T* find(const T (&table)[N], int64_t key) {
    for (int i = 0; i < N; ++i) {
        if (table[i] == key)
            return &table[i];
    }
    return nullptr;
}

} // namespace Exiv2

class ResolvedLensTest_1018 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test: Single lens label (no pipe separator), index 1 should return the full label
TEST_F(ResolvedLensTest_1018, SingleLensLabel_Index1_1018) {
    // lensID 0 => "Minolta AF 28-85mm F3.5-4.5 New" (single label, no pipe)
    Exiv2::Internal::resolvedLens(os, 0, 1);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("Minolta AF 28-85mm F3.5-4.5 New"), std::string::npos);
}

// Test: Multi-lens label with pipe, index 1 should return first lens
TEST_F(ResolvedLensTest_1018, MultiLensLabel_Index1_1018) {
    // lensID 7 => "Minolta AF 100-300mm F4.5-5.6 (D) APO [New] | Minolta AF 100-400mm F4.5-6.7 (D) | Sigma AF 100-300mm F4 EX DG IF"
    Exiv2::Internal::resolvedLens(os, 7, 1);
    std::string result = os.str();
    EXPECT_NE(result.find("Minolta AF 100-300mm F4.5-5.6 (D) APO [New]"), std::string::npos);
}

// Test: Multi-lens label with pipe, index 2 should return second lens
TEST_F(ResolvedLensTest_1018, MultiLensLabel_Index2_1018) {
    // lensID 7 => second token is "Minolta AF 100-400mm F4.5-6.7 (D)"
    Exiv2::Internal::resolvedLens(os, 7, 2);
    std::string result = os.str();
    EXPECT_NE(result.find("Minolta AF 100-400mm F4.5-6.7 (D)"), std::string::npos);
}

// Test: Multi-lens label with pipe, index 3 should return third lens
TEST_F(ResolvedLensTest_1018, MultiLensLabel_Index3_1018) {
    // lensID 7 => third token is "Sigma AF 100-300mm F4 EX DG IF"
    Exiv2::Internal::resolvedLens(os, 7, 3);
    std::string result = os.str();
    EXPECT_NE(result.find("Sigma AF 100-300mm F4 EX DG IF"), std::string::npos);
}

// Test: Two-option lens label, index 1
TEST_F(ResolvedLensTest_1018, TwoOptionLabel_Index1_1018) {
    // lensID 48 => "Carl Zeiss Vario-Sonnar T* 24-70mm F2.8 ZA SSM (SAL2470Z) | Carl Zeiss Vario-Sonnar T* 24-70mm F2.8 ZA SSM II (SAL2470Z2)"
    Exiv2::Internal::resolvedLens(os, 48, 1);
    std::string result = os.str();
    EXPECT_NE(result.find("Carl Zeiss Vario-Sonnar T* 24-70mm F2.8 ZA SSM (SAL2470Z)"), std::string::npos);
}

// Test: Two-option lens label, index 2
TEST_F(ResolvedLensTest_1018, TwoOptionLabel_Index2_1018) {
    Exiv2::Internal::resolvedLens(os, 48, 2);
    std::string result = os.str();
    EXPECT_NE(result.find("Carl Zeiss Vario-Sonnar T* 24-70mm F2.8 ZA SSM II (SAL2470Z2)"), std::string::npos);
}

// Test: Known single-label lens at higher ID
TEST_F(ResolvedLensTest_1018, HighLensID_SingleLabel_1018) {
    // lensID 25500 => "Minolta AF 50mm F1.7"
    Exiv2::Internal::resolvedLens(os, 25500, 1);
    std::string result = os.str();
    EXPECT_NE(result.find("Minolta AF 50mm F1.7"), std::string::npos);
}

// Test: Lens with many pipe-separated options (lensID 128 has many options)
TEST_F(ResolvedLensTest_1018, ManyOptions_FirstOption_1018) {
    // lensID 128 has many pipe-separated options, first is "Sigma 70-200mm F2.8 APO EX DG MACRO"
    Exiv2::Internal::resolvedLens(os, 128, 1);
    std::string result = os.str();
    EXPECT_NE(result.find("Sigma 70-200mm F2.8 APO EX DG MACRO"), std::string::npos);
}

// Test: Lens with many pipe-separated options, second option
TEST_F(ResolvedLensTest_1018, ManyOptions_SecondOption_1018) {
    Exiv2::Internal::resolvedLens(os, 128, 2);
    std::string result = os.str();
    EXPECT_NE(result.find("Tamron AF 18-200mm F3.5-6.3 XR Di II LD Aspherical [IF] Macro"), std::string::npos);
}

// Test: Output stream chaining - function returns reference to the same stream
TEST_F(ResolvedLensTest_1018, ReturnsSameStream_1018) {
    std::ostream& returned = Exiv2::Internal::resolvedLens(os, 0, 1);
    EXPECT_EQ(&returned, &os);
}

// Test: lensID 4 single lens - "Minolta AF 85mm F1.4G"
TEST_F(ResolvedLensTest_1018, SingleLens_ID4_1018) {
    Exiv2::Internal::resolvedLens(os, 4, 1);
    std::string result = os.str();
    EXPECT_NE(result.find("Minolta AF 85mm F1.4G"), std::string::npos);
}

// Test: lensID 24 has many pipe-separated options, pick index 3
TEST_F(ResolvedLensTest_1018, MultiOption_ID24_Index3_1018) {
    // lensID 24: "Minolta/Sony AF 24-105mm F3.5-4.5 (D) | Sigma 18-50mm F2.8 | Sigma 17-70mm F2.8-4.5 (D) | ..."
    Exiv2::Internal::resolvedLens(os, 24, 3);
    std::string result = os.str();
    EXPECT_NE(result.find("Sigma 17-70mm F2.8-4.5 (D)"), std::string::npos);
}

// Test: Last entry in table - lensID 65535
TEST_F(ResolvedLensTest_1018, LastEntry_ID65535_Index1_1018) {
    // lensID 65535 => "Manual lens | Sony E 50mm F1.8 OSS | E PZ 16-50mm F3.5-5.6 OSS"
    Exiv2::Internal::resolvedLens(os, 65535, 1);
    std::string result = os.str();
    EXPECT_NE(result.find("Manual lens"), std::string::npos);
}

// Test: Last entry in table - lensID 65535, index 2
TEST_F(ResolvedLensTest_1018, LastEntry_ID65535_Index2_1018) {
    Exiv2::Internal::resolvedLens(os, 65535, 2);
    std::string result = os.str();
    EXPECT_NE(result.find("Sony E 50mm F1.8 OSS"), std::string::npos);
}

// Test: Last entry in table - lensID 65535, index 3
TEST_F(ResolvedLensTest_1018, LastEntry_ID65535_Index3_1018) {
    Exiv2::Internal::resolvedLens(os, 65535, 3);
    std::string result = os.str();
    EXPECT_NE(result.find("E PZ 16-50mm F3.5-5.6 OSS"), std::string::npos);
}

// Test: lensID 31 with two options separated by pipe
TEST_F(ResolvedLensTest_1018, TwoOptions_ID31_Index1_1018) {
    // lensID 31 => "Minolta/Sony AF 50mm F2.8 Macro (D) | Minolta/Sony AF 50mm F3.5 Macro"
    Exiv2::Internal::resolvedLens(os, 31, 1);
    std::string result = os.str();
    EXPECT_NE(result.find("Minolta/Sony AF 50mm F2.8 Macro (D)"), std::string::npos);
}

TEST_F(ResolvedLensTest_1018, TwoOptions_ID31_Index2_1018) {
    Exiv2::Internal::resolvedLens(os, 31, 2);
    std::string result = os.str();
    EXPECT_NE(result.find("Minolta/Sony AF 50mm F3.5 Macro"), std::string::npos);
}

// Test: Verify trimming - labels with spaces around pipe should be trimmed
TEST_F(ResolvedLensTest_1018, TrimmingApplied_1018) {
    // lensID 7 second token should be trimmed (no leading/trailing spaces)
    Exiv2::Internal::resolvedLens(os, 7, 2);
    std::string result = os.str();
    // Should not start with a space
    EXPECT_NE(result[0], ' ');
}

// Test: Out of range index should throw (std::out_of_range from vector::at)
TEST_F(ResolvedLensTest_1018, OutOfRangeIndex_ThrowsException_1018) {
    // lensID 0 has only 1 token, so index 2 (which maps to at(1)) should throw
    EXPECT_THROW(Exiv2::Internal::resolvedLens(os, 0, 2), std::out_of_range);
}

// Test: Index 0 maps to at(-1) which is effectively at(max_size_t) - should throw
TEST_F(ResolvedLensTest_1018, IndexZero_ThrowsException_1018) {
    // index 0 means at(0-1) = at(SIZE_MAX) which should throw
    EXPECT_THROW(Exiv2::Internal::resolvedLens(os, 0, 0), std::out_of_range);
}
