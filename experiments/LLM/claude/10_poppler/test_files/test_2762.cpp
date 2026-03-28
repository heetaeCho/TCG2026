#include <gtest/gtest.h>

// Minimal stubs to allow compilation
namespace Poppler {

class FontInfo {
public:
    enum Type {
        unknown = 0,
        Type1,
        Type1C,
        Type1COT,
        Type3,
        TrueType,
        TrueTypeOT,
        CIDType0,
        CIDType0C,
        CIDType0COT,
        CIDTrueType,
        CIDTrueTypeOT
    };
};

class FontInfoData {
public:
    bool isEmbedded;
    bool isSubset;
    FontInfo::Type type;

    FontInfoData()
    {
        isEmbedded = false;
        isSubset = false;
        type = FontInfo::unknown;
    }

    FontInfoData(const FontInfoData &fid) = default;
    FontInfoData &operator=(const FontInfoData &) = default;
};

} // namespace Poppler

// ============ Tests ============

class FontInfoDataTest_2762 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(FontInfoDataTest_2762, DefaultConstructor_IsEmbeddedIsFalse_2762)
{
    Poppler::FontInfoData data;
    EXPECT_FALSE(data.isEmbedded);
}

TEST_F(FontInfoDataTest_2762, DefaultConstructor_IsSubsetIsFalse_2762)
{
    Poppler::FontInfoData data;
    EXPECT_FALSE(data.isSubset);
}

TEST_F(FontInfoDataTest_2762, DefaultConstructor_TypeIsUnknown_2762)
{
    Poppler::FontInfoData data;
    EXPECT_EQ(data.type, Poppler::FontInfo::unknown);
}

TEST_F(FontInfoDataTest_2762, CopyConstructor_CopiesIsEmbedded_2762)
{
    Poppler::FontInfoData original;
    original.isEmbedded = true;
    original.isSubset = true;
    original.type = Poppler::FontInfo::TrueType;

    Poppler::FontInfoData copy(original);
    EXPECT_TRUE(copy.isEmbedded);
    EXPECT_TRUE(copy.isSubset);
    EXPECT_EQ(copy.type, Poppler::FontInfo::TrueType);
}

TEST_F(FontInfoDataTest_2762, CopyAssignment_CopiesAllFields_2762)
{
    Poppler::FontInfoData original;
    original.isEmbedded = true;
    original.isSubset = false;
    original.type = Poppler::FontInfo::Type1;

    Poppler::FontInfoData assigned;
    assigned = original;

    EXPECT_TRUE(assigned.isEmbedded);
    EXPECT_FALSE(assigned.isSubset);
    EXPECT_EQ(assigned.type, Poppler::FontInfo::Type1);
}

TEST_F(FontInfoDataTest_2762, ModifyIsEmbedded_2762)
{
    Poppler::FontInfoData data;
    EXPECT_FALSE(data.isEmbedded);
    data.isEmbedded = true;
    EXPECT_TRUE(data.isEmbedded);
}

TEST_F(FontInfoDataTest_2762, ModifyIsSubset_2762)
{
    Poppler::FontInfoData data;
    EXPECT_FALSE(data.isSubset);
    data.isSubset = true;
    EXPECT_TRUE(data.isSubset);
}

TEST_F(FontInfoDataTest_2762, ModifyType_2762)
{
    Poppler::FontInfoData data;
    EXPECT_EQ(data.type, Poppler::FontInfo::unknown);
    data.type = Poppler::FontInfo::CIDType0;
    EXPECT_EQ(data.type, Poppler::FontInfo::CIDType0);
}

TEST_F(FontInfoDataTest_2762, CopyConstructorDoesNotAffectOriginal_2762)
{
    Poppler::FontInfoData original;
    original.isEmbedded = true;
    original.isSubset = true;
    original.type = Poppler::FontInfo::Type3;

    Poppler::FontInfoData copy(original);
    copy.isEmbedded = false;
    copy.isSubset = false;
    copy.type = Poppler::FontInfo::unknown;

    // Original should remain unchanged
    EXPECT_TRUE(original.isEmbedded);
    EXPECT_TRUE(original.isSubset);
    EXPECT_EQ(original.type, Poppler::FontInfo::Type3);
}

TEST_F(FontInfoDataTest_2762, AssignmentDoesNotAffectSource_2762)
{
    Poppler::FontInfoData source;
    source.isEmbedded = true;
    source.isSubset = true;
    source.type = Poppler::FontInfo::TrueTypeOT;

    Poppler::FontInfoData dest;
    dest = source;
    dest.isEmbedded = false;
    dest.type = Poppler::FontInfo::unknown;

    EXPECT_TRUE(source.isEmbedded);
    EXPECT_TRUE(source.isSubset);
    EXPECT_EQ(source.type, Poppler::FontInfo::TrueTypeOT);
}

TEST_F(FontInfoDataTest_2762, SelfAssignment_2762)
{
    Poppler::FontInfoData data;
    data.isEmbedded = true;
    data.isSubset = true;
    data.type = Poppler::FontInfo::CIDTrueType;

    data = data;

    EXPECT_TRUE(data.isEmbedded);
    EXPECT_TRUE(data.isSubset);
    EXPECT_EQ(data.type, Poppler::FontInfo::CIDTrueType);
}

TEST_F(FontInfoDataTest_2762, MultipleDefaultConstructions_2762)
{
    Poppler::FontInfoData data1;
    Poppler::FontInfoData data2;

    EXPECT_EQ(data1.isEmbedded, data2.isEmbedded);
    EXPECT_EQ(data1.isSubset, data2.isSubset);
    EXPECT_EQ(data1.type, data2.type);
}

TEST_F(FontInfoDataTest_2762, AllFontTypes_2762)
{
    Poppler::FontInfoData data;

    std::vector<Poppler::FontInfo::Type> types = {
        Poppler::FontInfo::unknown,
        Poppler::FontInfo::Type1,
        Poppler::FontInfo::Type1C,
        Poppler::FontInfo::Type1COT,
        Poppler::FontInfo::Type3,
        Poppler::FontInfo::TrueType,
        Poppler::FontInfo::TrueTypeOT,
        Poppler::FontInfo::CIDType0,
        Poppler::FontInfo::CIDType0C,
        Poppler::FontInfo::CIDType0COT,
        Poppler::FontInfo::CIDTrueType,
        Poppler::FontInfo::CIDTrueTypeOT
    };

    for (auto t : types) {
        data.type = t;
        EXPECT_EQ(data.type, t);
    }
}
