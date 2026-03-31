#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <optional>
#include <string>
#include <QString>

// Forward declarations and minimal stubs needed for compilation

struct Ref {
    int num;
    int gen;
    static constexpr Ref INVALID() { return {-1, -1}; }
    bool operator==(const Ref &other) const { return num == other.num && gen == other.gen; }
};

// Mock FontInfo class to avoid needing the full Poppler internals
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

    MOCK_CONST_METHOD0(getName, const std::optional<std::string> &());
    MOCK_CONST_METHOD0(getSubstituteName, const std::optional<std::string> &());
    MOCK_CONST_METHOD0(getFile, const std::optional<std::string> &());
    MOCK_CONST_METHOD0(getEncoding, const std::string &());
    MOCK_CONST_METHOD0(getType, Type());
    MOCK_CONST_METHOD0(getEmbedded, bool());
    MOCK_CONST_METHOD0(getSubset, bool());
    MOCK_CONST_METHOD0(getToUnicode, bool());
    MOCK_CONST_METHOD0(getRef, Ref());
    MOCK_CONST_METHOD0(getEmbRef, Ref());
};

// Replicate the Poppler namespace structures
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
    QString fontName;
    QString fontSubstituteName;
    QString fontFile;
    bool isEmbedded;
    bool isSubset;
    Poppler::FontInfo::Type type;
    Ref embRef;

    FontInfoData() : isEmbedded(false), isSubset(false), type(Poppler::FontInfo::unknown), embRef(Ref::INVALID()) {}

    explicit FontInfoData(::FontInfo *fi)
    {
        const std::optional<std::string> &fiName = fi->getName();
        if (fiName) {
            fontName = QString::fromStdString(fiName.value());
        }

        const std::optional<std::string> &fiFile = fi->getFile();
        if (fiFile) {
            fontFile = QString::fromStdString(fiFile.value());
        }

        const std::optional<std::string> &fiSubstituteName = fi->getSubstituteName();
        if (fiSubstituteName) {
            fontSubstituteName = QString::fromStdString(fiSubstituteName.value());
        }

        isEmbedded = fi->getEmbedded();
        isSubset = fi->getSubset();
        type = (Poppler::FontInfo::Type)fi->getType();
        embRef = fi->getEmbRef();
    }

    FontInfoData(const FontInfoData &fid) = default;
    FontInfoData &operator=(const FontInfoData &) = default;
};

} // namespace Poppler

// Test fixture
class FontInfoDataTest_2763 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(FontInfoDataTest_2763, DefaultConstructor_2763)
{
    Poppler::FontInfoData fid;

    EXPECT_TRUE(fid.fontName.isEmpty());
    EXPECT_TRUE(fid.fontSubstituteName.isEmpty());
    EXPECT_TRUE(fid.fontFile.isEmpty());
    EXPECT_FALSE(fid.isEmbedded);
    EXPECT_FALSE(fid.isSubset);
    EXPECT_EQ(fid.type, Poppler::FontInfo::unknown);
    EXPECT_EQ(fid.embRef, Ref::INVALID());
}

TEST_F(FontInfoDataTest_2763, ConstructFromFontInfoWithAllFieldsPopulated_2763)
{
    ::FontInfo mockFi;

    std::optional<std::string> name = std::string("Arial");
    std::optional<std::string> substituteName = std::string("Helvetica");
    std::optional<std::string> file = std::string("/usr/share/fonts/arial.ttf");
    Ref ref = {42, 0};

    EXPECT_CALL(mockFi, getName()).WillRepeatedly(::testing::ReturnRef(name));
    EXPECT_CALL(mockFi, getSubstituteName()).WillRepeatedly(::testing::ReturnRef(substituteName));
    EXPECT_CALL(mockFi, getFile()).WillRepeatedly(::testing::ReturnRef(file));
    EXPECT_CALL(mockFi, getEmbedded()).WillRepeatedly(::testing::Return(true));
    EXPECT_CALL(mockFi, getSubset()).WillRepeatedly(::testing::Return(true));
    EXPECT_CALL(mockFi, getType()).WillRepeatedly(::testing::Return(::FontInfo::TrueType));
    EXPECT_CALL(mockFi, getEmbRef()).WillRepeatedly(::testing::Return(ref));

    Poppler::FontInfoData fid(&mockFi);

    EXPECT_EQ(fid.fontName, QString("Arial"));
    EXPECT_EQ(fid.fontSubstituteName, QString("Helvetica"));
    EXPECT_EQ(fid.fontFile, QString("/usr/share/fonts/arial.ttf"));
    EXPECT_TRUE(fid.isEmbedded);
    EXPECT_TRUE(fid.isSubset);
    EXPECT_EQ(fid.type, Poppler::FontInfo::TrueType);
    EXPECT_EQ(fid.embRef.num, 42);
    EXPECT_EQ(fid.embRef.gen, 0);
}

TEST_F(FontInfoDataTest_2763, ConstructFromFontInfoWithNulloptName_2763)
{
    ::FontInfo mockFi;

    std::optional<std::string> name = std::nullopt;
    std::optional<std::string> substituteName = std::string("Courier");
    std::optional<std::string> file = std::string("/tmp/font.ttf");
    Ref ref = {10, 1};

    EXPECT_CALL(mockFi, getName()).WillRepeatedly(::testing::ReturnRef(name));
    EXPECT_CALL(mockFi, getSubstituteName()).WillRepeatedly(::testing::ReturnRef(substituteName));
    EXPECT_CALL(mockFi, getFile()).WillRepeatedly(::testing::ReturnRef(file));
    EXPECT_CALL(mockFi, getEmbedded()).WillRepeatedly(::testing::Return(false));
    EXPECT_CALL(mockFi, getSubset()).WillRepeatedly(::testing::Return(false));
    EXPECT_CALL(mockFi, getType()).WillRepeatedly(::testing::Return(::FontInfo::Type1));
    EXPECT_CALL(mockFi, getEmbRef()).WillRepeatedly(::testing::Return(ref));

    Poppler::FontInfoData fid(&mockFi);

    EXPECT_TRUE(fid.fontName.isEmpty());
    EXPECT_EQ(fid.fontSubstituteName, QString("Courier"));
    EXPECT_EQ(fid.fontFile, QString("/tmp/font.ttf"));
    EXPECT_FALSE(fid.isEmbedded);
    EXPECT_FALSE(fid.isSubset);
}

TEST_F(FontInfoDataTest_2763, ConstructFromFontInfoWithNulloptFile_2763)
{
    ::FontInfo mockFi;

    std::optional<std::string> name = std::string("TimesNewRoman");
    std::optional<std::string> substituteName = std::nullopt;
    std::optional<std::string> file = std::nullopt;
    Ref ref = Ref::INVALID();

    EXPECT_CALL(mockFi, getName()).WillRepeatedly(::testing::ReturnRef(name));
    EXPECT_CALL(mockFi, getSubstituteName()).WillRepeatedly(::testing::ReturnRef(substituteName));
    EXPECT_CALL(mockFi, getFile()).WillRepeatedly(::testing::ReturnRef(file));
    EXPECT_CALL(mockFi, getEmbedded()).WillRepeatedly(::testing::Return(false));
    EXPECT_CALL(mockFi, getSubset()).WillRepeatedly(::testing::Return(true));
    EXPECT_CALL(mockFi, getType()).WillRepeatedly(::testing::Return(::FontInfo::Type3));
    EXPECT_CALL(mockFi, getEmbRef()).WillRepeatedly(::testing::Return(ref));

    Poppler::FontInfoData fid(&mockFi);

    EXPECT_EQ(fid.fontName, QString("TimesNewRoman"));
    EXPECT_TRUE(fid.fontSubstituteName.isEmpty());
    EXPECT_TRUE(fid.fontFile.isEmpty());
    EXPECT_FALSE(fid.isEmbedded);
    EXPECT_TRUE(fid.isSubset);
    EXPECT_EQ(fid.type, Poppler::FontInfo::Type3);
}

TEST_F(FontInfoDataTest_2763, ConstructFromFontInfoWithAllNullopts_2763)
{
    ::FontInfo mockFi;

    std::optional<std::string> name = std::nullopt;
    std::optional<std::string> substituteName = std::nullopt;
    std::optional<std::string> file = std::nullopt;
    Ref ref = Ref::INVALID();

    EXPECT_CALL(mockFi, getName()).WillRepeatedly(::testing::ReturnRef(name));
    EXPECT_CALL(mockFi, getSubstituteName()).WillRepeatedly(::testing::ReturnRef(substituteName));
    EXPECT_CALL(mockFi, getFile()).WillRepeatedly(::testing::ReturnRef(file));
    EXPECT_CALL(mockFi, getEmbedded()).WillRepeatedly(::testing::Return(false));
    EXPECT_CALL(mockFi, getSubset()).WillRepeatedly(::testing::Return(false));
    EXPECT_CALL(mockFi, getType()).WillRepeatedly(::testing::Return(::FontInfo::unknown));
    EXPECT_CALL(mockFi, getEmbRef()).WillRepeatedly(::testing::Return(ref));

    Poppler::FontInfoData fid(&mockFi);

    EXPECT_TRUE(fid.fontName.isEmpty());
    EXPECT_TRUE(fid.fontSubstituteName.isEmpty());
    EXPECT_TRUE(fid.fontFile.isEmpty());
    EXPECT_FALSE(fid.isEmbedded);
    EXPECT_FALSE(fid.isSubset);
    EXPECT_EQ(fid.type, Poppler::FontInfo::unknown);
}

TEST_F(FontInfoDataTest_2763, ConstructFromFontInfoWithEmptyStrings_2763)
{
    ::FontInfo mockFi;

    std::optional<std::string> name = std::string("");
    std::optional<std::string> substituteName = std::string("");
    std::optional<std::string> file = std::string("");
    Ref ref = {0, 0};

    EXPECT_CALL(mockFi, getName()).WillRepeatedly(::testing::ReturnRef(name));
    EXPECT_CALL(mockFi, getSubstituteName()).WillRepeatedly(::testing::ReturnRef(substituteName));
    EXPECT_CALL(mockFi, getFile()).WillRepeatedly(::testing::ReturnRef(file));
    EXPECT_CALL(mockFi, getEmbedded()).WillRepeatedly(::testing::Return(true));
    EXPECT_CALL(mockFi, getSubset()).WillRepeatedly(::testing::Return(false));
    EXPECT_CALL(mockFi, getType()).WillRepeatedly(::testing::Return(::FontInfo::CIDType0));
    EXPECT_CALL(mockFi, getEmbRef()).WillRepeatedly(::testing::Return(ref));

    Poppler::FontInfoData fid(&mockFi);

    EXPECT_EQ(fid.fontName, QString(""));
    EXPECT_EQ(fid.fontSubstituteName, QString(""));
    EXPECT_EQ(fid.fontFile, QString(""));
    EXPECT_TRUE(fid.isEmbedded);
    EXPECT_FALSE(fid.isSubset);
    EXPECT_EQ(fid.type, Poppler::FontInfo::CIDType0);
    EXPECT_EQ(fid.embRef.num, 0);
    EXPECT_EQ(fid.embRef.gen, 0);
}

TEST_F(FontInfoDataTest_2763, CopyConstructor_2763)
{
    ::FontInfo mockFi;

    std::optional<std::string> name = std::string("TestFont");
    std::optional<std::string> substituteName = std::string("SubFont");
    std::optional<std::string> file = std::string("/path/to/font");
    Ref ref = {100, 5};

    EXPECT_CALL(mockFi, getName()).WillRepeatedly(::testing::ReturnRef(name));
    EXPECT_CALL(mockFi, getSubstituteName()).WillRepeatedly(::testing::ReturnRef(substituteName));
    EXPECT_CALL(mockFi, getFile()).WillRepeatedly(::testing::ReturnRef(file));
    EXPECT_CALL(mockFi, getEmbedded()).WillRepeatedly(::testing::Return(true));
    EXPECT_CALL(mockFi, getSubset()).WillRepeatedly(::testing::Return(true));
    EXPECT_CALL(mockFi, getType()).WillRepeatedly(::testing::Return(::FontInfo::TrueTypeOT));
    EXPECT_CALL(mockFi, getEmbRef()).WillRepeatedly(::testing::Return(ref));

    Poppler::FontInfoData original(&mockFi);
    Poppler::FontInfoData copy(original);

    EXPECT_EQ(copy.fontName, QString("TestFont"));
    EXPECT_EQ(copy.fontSubstituteName, QString("SubFont"));
    EXPECT_EQ(copy.fontFile, QString("/path/to/font"));
    EXPECT_TRUE(copy.isEmbedded);
    EXPECT_TRUE(copy.isSubset);
    EXPECT_EQ(copy.type, Poppler::FontInfo::TrueTypeOT);
    EXPECT_EQ(copy.embRef.num, 100);
    EXPECT_EQ(copy.embRef.gen, 5);
}

TEST_F(FontInfoDataTest_2763, AssignmentOperator_2763)
{
    ::FontInfo mockFi;

    std::optional<std::string> name = std::string("AssignFont");
    std::optional<std::string> substituteName = std::nullopt;
    std::optional<std::string> file = std::string("/some/path");
    Ref ref = {7, 3};

    EXPECT_CALL(mockFi, getName()).WillRepeatedly(::testing::ReturnRef(name));
    EXPECT_CALL(mockFi, getSubstituteName()).WillRepeatedly(::testing::ReturnRef(substituteName));
    EXPECT_CALL(mockFi, getFile()).WillRepeatedly(::testing::ReturnRef(file));
    EXPECT_CALL(mockFi, getEmbedded()).WillRepeatedly(::testing::Return(false));
    EXPECT_CALL(mockFi, getSubset()).WillRepeatedly(::testing::Return(true));
    EXPECT_CALL(mockFi, getType()).WillRepeatedly(::testing::Return(::FontInfo::CIDTrueType));
    EXPECT_CALL(mockFi, getEmbRef()).WillRepeatedly(::testing::Return(ref));

    Poppler::FontInfoData original(&mockFi);
    Poppler::FontInfoData assigned;
    assigned = original;

    EXPECT_EQ(assigned.fontName, QString("AssignFont"));
    EXPECT_TRUE(assigned.fontSubstituteName.isEmpty());
    EXPECT_EQ(assigned.fontFile, QString("/some/path"));
    EXPECT_FALSE(assigned.isEmbedded);
    EXPECT_TRUE(assigned.isSubset);
    EXPECT_EQ(assigned.type, Poppler::FontInfo::CIDTrueType);
    EXPECT_EQ(assigned.embRef.num, 7);
    EXPECT_EQ(assigned.embRef.gen, 3);
}

TEST_F(FontInfoDataTest_2763, UnicodeStringHandling_2763)
{
    ::FontInfo mockFi;

    std::optional<std::string> name = std::string("Ünïcödé-Fönt");
    std::optional<std::string> substituteName = std::string("替代字体");
    std::optional<std::string> file = std::string("/path/tö/fönt.ttf");
    Ref ref = {1, 0};

    EXPECT_CALL(mockFi, getName()).WillRepeatedly(::testing::ReturnRef(name));
    EXPECT_CALL(mockFi, getSubstituteName()).WillRepeatedly(::testing::ReturnRef(substituteName));
    EXPECT_CALL(mockFi, getFile()).WillRepeatedly(::testing::ReturnRef(file));
    EXPECT_CALL(mockFi, getEmbedded()).WillRepeatedly(::testing::Return(true));
    EXPECT_CALL(mockFi, getSubset()).WillRepeatedly(::testing::Return(false));
    EXPECT_CALL(mockFi, getType()).WillRepeatedly(::testing::Return(::FontInfo::Type1C));
    EXPECT_CALL(mockFi, getEmbRef()).WillRepeatedly(::testing::Return(ref));

    Poppler::FontInfoData fid(&mockFi);

    EXPECT_EQ(fid.fontName, QString::fromStdString("Ünïcödé-Fönt"));
    EXPECT_EQ(fid.fontSubstituteName, QString::fromStdString("替代字体"));
    EXPECT_EQ(fid.fontFile, QString::fromStdString("/path/tö/fönt.ttf"));
}

TEST_F(FontInfoDataTest_2763, AllFontTypes_2763)
{
    auto testType = [](::FontInfo::Type inputType, Poppler::FontInfo::Type expectedType) {
        ::FontInfo mockFi;
        std::optional<std::string> empty = std::nullopt;
        Ref ref = Ref::INVALID();

        EXPECT_CALL(mockFi, getName()).WillRepeatedly(::testing::ReturnRef(empty));
        EXPECT_CALL(mockFi, getSubstituteName()).WillRepeatedly(::testing::ReturnRef(empty));
        EXPECT_CALL(mockFi, getFile()).WillRepeatedly(::testing::ReturnRef(empty));
        EXPECT_CALL(mockFi, getEmbedded()).WillRepeatedly(::testing::Return(false));
        EXPECT_CALL(mockFi, getSubset()).WillRepeatedly(::testing::Return(false));
        EXPECT_CALL(mockFi, getType()).WillRepeatedly(::testing::Return(inputType));
        EXPECT_CALL(mockFi, getEmbRef()).WillRepeatedly(::testing::Return(ref));

        Poppler::FontInfoData fid(&mockFi);
        EXPECT_EQ(fid.type, expectedType);
    };

    testType(::FontInfo::unknown, Poppler::FontInfo::unknown);
    testType(::FontInfo::Type1, Poppler::FontInfo::Type1);
    testType(::FontInfo::Type1C, Poppler::FontInfo::Type1C);
    testType(::FontInfo::Type1COT, Poppler::FontInfo::Type1COT);
    testType(::FontInfo::Type3, Poppler::FontInfo::Type3);
    testType(::FontInfo::TrueType, Poppler::FontInfo::TrueType);
    testType(::FontInfo::TrueTypeOT, Poppler::FontInfo::TrueTypeOT);
    testType(::FontInfo::CIDType0, Poppler::FontInfo::CIDType0);
    testType(::FontInfo::CIDType0C, Poppler::FontInfo::CIDType0C);
    testType(::FontInfo::CIDType0COT, Poppler::FontInfo::CIDType0COT);
    testType(::FontInfo::CIDTrueType, Poppler::FontInfo::CIDTrueType);
    testType(::FontInfo::CIDTrueTypeOT, Poppler::FontInfo::CIDTrueTypeOT);
}

TEST_F(FontInfoDataTest_2763, LongFontName_2763)
{
    ::FontInfo mockFi;

    std::string longName(1000, 'A');
    std::optional<std::string> name = longName;
    std::optional<std::string> substituteName = std::nullopt;
    std::optional<std::string> file = std::nullopt;
    Ref ref = Ref::INVALID();

    EXPECT_CALL(mockFi, getName()).WillRepeatedly(::testing::ReturnRef(name));
    EXPECT_CALL(mockFi, getSubstituteName()).WillRepeatedly(::testing::ReturnRef(substituteName));
    EXPECT_CALL(mockFi, getFile()).WillRepeatedly(::testing::ReturnRef(file));
    EXPECT_CALL(mockFi, getEmbedded()).WillRepeatedly(::testing::Return(false));
    EXPECT_CALL(mockFi, getSubset()).WillRepeatedly(::testing::Return(false));
    EXPECT_CALL(mockFi, getType()).WillRepeatedly(::testing::Return(::FontInfo::unknown));
    EXPECT_CALL(mockFi, getEmbRef()).WillRepeatedly(::testing::Return(ref));

    Poppler::FontInfoData fid(&mockFi);

    EXPECT_EQ(fid.fontName.length(), 1000);
    EXPECT_EQ(fid.fontName, QString::fromStdString(longName));
}

TEST_F(FontInfoDataTest_2763, EmbeddedTrueSubsetFalse_2763)
{
    ::FontInfo mockFi;

    std::optional<std::string> empty = std::nullopt;
    Ref ref = Ref::INVALID();

    EXPECT_CALL(mockFi, getName()).WillRepeatedly(::testing::ReturnRef(empty));
    EXPECT_CALL(mockFi, getSubstituteName()).WillRepeatedly(::testing::ReturnRef(empty));
    EXPECT_CALL(mockFi, getFile()).WillRepeatedly(::testing::ReturnRef(empty));
    EXPECT_CALL(mockFi, getEmbedded()).WillRepeatedly(::testing::Return(true));
    EXPECT_CALL(mockFi, getSubset()).WillRepeatedly(::testing::Return(false));
    EXPECT_CALL(mockFi, getType()).WillRepeatedly(::testing::Return(::FontInfo::unknown));
    EXPECT_CALL(mockFi, getEmbRef()).WillRepeatedly(::testing::Return(ref));

    Poppler::FontInfoData fid(&mockFi);

    EXPECT_TRUE(fid.isEmbedded);
    EXPECT_FALSE(fid.isSubset);
}

TEST_F(FontInfoDataTest_2763, EmbeddedFalseSubsetTrue_2763)
{
    ::FontInfo mockFi;

    std::optional<std::string> empty = std::nullopt;
    Ref ref = Ref::INVALID();

    EXPECT_CALL(mockFi, getName()).WillRepeatedly(::testing::ReturnRef(empty));
    EXPECT_CALL(mockFi, getSubstituteName()).WillRepeatedly(::testing::ReturnRef(empty));
    EXPECT_CALL(mockFi, getFile()).WillRepeatedly(::testing::ReturnRef(empty));
    EXPECT_CALL(mockFi, getEmbedded()).WillRepeatedly(::testing::Return(false));
    EXPECT_CALL(mockFi, getSubset()).WillRepeatedly(::testing::Return(true));
    EXPECT_CALL(mockFi, getType()).WillRepeatedly(::testing::Return(::FontInfo::unknown));
    EXPECT_CALL(mockFi, getEmbRef()).WillRepeatedly(::testing::Return(ref));

    Poppler::FontInfoData fid(&mockFi);

    EXPECT_FALSE(fid.isEmbedded);
    EXPECT_TRUE(fid.isSubset);
}

TEST_F(FontInfoDataTest_2763, EmbRefPreserved_2763)
{
    ::FontInfo mockFi;

    std::optional<std::string> empty = std::nullopt;
    Ref ref = {99999, 65535};

    EXPECT_CALL(mockFi, getName()).WillRepeatedly(::testing::ReturnRef(empty));
    EXPECT_CALL(mockFi, getSubstituteName()).WillRepeatedly(::testing::ReturnRef(empty));
    EXPECT_CALL(mockFi, getFile()).WillRepeatedly(::testing::ReturnRef(empty));
    EXPECT_CALL(mockFi, getEmbedded()).WillRepeatedly(::testing::Return(false));
    EXPECT_CALL(mockFi, getSubset()).WillRepeatedly(::testing::Return(false));
    EXPECT_CALL(mockFi, getType()).WillRepeatedly(::testing::Return(::FontInfo::unknown));
    EXPECT_CALL(mockFi, getEmbRef()).WillRepeatedly(::testing::Return(ref));

    Poppler::FontInfoData fid(&mockFi);

    EXPECT_EQ(fid.embRef.num, 99999);
    EXPECT_EQ(fid.embRef.gen, 65535);
}

TEST_F(FontInfoDataTest_2763, FontNameWithSpecialCharacters_2763)
{
    ::FontInfo mockFi;

    std::optional<std::string> name = std::string("Font+Name-With.Special_Chars!@#$%");
    std::optional<std::string> substituteName = std::nullopt;
    std::optional<std::string> file = std::nullopt;
    Ref ref = Ref::INVALID();

    EXPECT_CALL(mockFi, getName()).WillRepeatedly(::testing::ReturnRef(name));
    EXPECT_CALL(mockFi, getSubstituteName()).WillRepeatedly(::testing::ReturnRef(substituteName));
    EXPECT_CALL(mockFi, getFile()).WillRepeatedly(::testing::ReturnRef(file));
    EXPECT_CALL(mockFi, getEmbedded()).WillRepeatedly(::testing::Return(false));
    EXPECT_CALL(mockFi, getSubset()).WillRepeatedly(::testing::Return(false));
    EXPECT_CALL(mockFi, getType()).WillRepeatedly(::testing::Return(::FontInfo::unknown));
    EXPECT_CALL(mockFi, getEmbRef()).WillRepeatedly(::testing::Return(ref));

    Poppler::FontInfoData fid(&mockFi);

    EXPECT_EQ(fid.fontName, QString("Font+Name-With.Special_Chars!@#$%"));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
