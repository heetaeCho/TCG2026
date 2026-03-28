// FontInfoDataTest_2763.cpp
#include <gtest/gtest.h>

#include <optional>
#include <string>

#if __has_include(<QString>)
#  include <QString>
#elif __has_include(<QtCore/QString>)
#  include <QtCore/QString>
#endif

// Try to include Poppler Qt6 public header (for Poppler::FontInfo::Type).
#if __has_include("poppler-qt6.h")
#  include "poppler-qt6.h"
#elif __has_include(<poppler-qt6.h>)
#  include <poppler-qt6.h>
#endif

// -----------------------------------------------------------------------------
// Test double for ::FontInfo and Ref
//
// We intentionally avoid relying on Poppler core internals. FontInfoData only
// depends on the observable interface of ::FontInfo getters. If the production
// build includes the real poppler/FontInfo.h through poppler-private.h, this
// shim may conflict; in many Poppler Qt builds poppler-private.h only forward
// declares ::FontInfo, so this is safe.
//
// If you see a redefinition error for ::FontInfo or Ref, remove this shim and
// construct a real ::FontInfo from your environment instead.
// -----------------------------------------------------------------------------
#ifndef POPPLER_TEST_SHIM_REF_2763
#define POPPLER_TEST_SHIM_REF_2763
struct Ref {
    int num;
    int gen;
};
#endif

#ifndef POPPLER_TEST_SHIM_FONTINFO_2763
#define POPPLER_TEST_SHIM_FONTINFO_2763

class FontInfo {
public:
    using OptStr = std::optional<std::string>;

    FontInfo() = default;

    // Setters for test arrangement
    void setName(std::optional<std::string> v) { name_ = std::move(v); }
    void setFile(std::optional<std::string> v) { file_ = std::move(v); }
    void setSubstituteName(std::optional<std::string> v) { sub_ = std::move(v); }
    void setEmbedded(bool v) { embedded_ = v; }
    void setSubset(bool v) { subset_ = v; }
    void setType(int v) { type_ = v; }
    void setEmbRef(Ref r) { embRef_ = r; }

    // Interface used by Poppler::FontInfoData (black-box dependency surface)
    const OptStr &getName() const { return name_; }
    const OptStr &getFile() const { return file_; }
    const OptStr &getSubstituteName() const { return sub_; }

    bool getEmbedded() const { return embedded_; }
    bool getSubset() const { return subset_; }

    // In Poppler core this is a specific enum type. FontInfoData casts it to
    // Poppler::FontInfo::Type, so returning an int is sufficient for the cast.
    int getType() const { return type_; }

    Ref getEmbRef() const { return embRef_; }

private:
    OptStr name_;
    OptStr file_;
    OptStr sub_;
    bool embedded_ = false;
    bool subset_ = false;
    int type_ = 0;
    Ref embRef_{0, 0};
};
#endif

// Include the class under test.
#include "poppler-private.h"

namespace {

class FontInfoDataTest_2763 : public ::testing::Test {
protected:
    static Ref MakeRef(int num, int gen) { return Ref{num, gen}; }
};

TEST_F(FontInfoDataTest_2763, CopiesAllPresentFields_2763)
{
    FontInfo fi;
    fi.setName(std::string("MyFont-Regular"));
    fi.setFile(std::string("/tmp/MyFont-Regular.ttf"));
    fi.setSubstituteName(std::string("SubFont"));
    fi.setEmbedded(true);
    fi.setSubset(true);
    fi.setType(1);
    fi.setEmbRef(MakeRef(12, 0));

    Poppler::FontInfoData data(&fi);

#if defined(QSTRING_H) || __has_include(<QString>) || __has_include(<QtCore/QString>)
    EXPECT_EQ(data.fontName, QString::fromStdString("MyFont-Regular"));
    EXPECT_EQ(data.fontFile, QString::fromStdString("/tmp/MyFont-Regular.ttf"));
    EXPECT_EQ(data.fontSubstituteName, QString::fromStdString("SubFont"));
#endif

    EXPECT_TRUE(data.isEmbedded);
    EXPECT_TRUE(data.isSubset);

    // Type is a cast of fi.getType(); we only verify it reflects the provided value.
    EXPECT_EQ(static_cast<int>(data.type), 1);

    EXPECT_EQ(data.embRef.num, 12);
    EXPECT_EQ(data.embRef.gen, 0);
}

TEST_F(FontInfoDataTest_2763, MissingOptionalsLeaveQStringDefault_2763)
{
    FontInfo fi;
    // name/file/substitute left unset
    fi.setEmbedded(false);
    fi.setSubset(false);
    fi.setType(0);
    fi.setEmbRef(MakeRef(0, 0));

    Poppler::FontInfoData data(&fi);

#if defined(QSTRING_H) || __has_include(<QString>) || __has_include(<QtCore/QString>)
    EXPECT_TRUE(data.fontName.isEmpty());
    EXPECT_TRUE(data.fontFile.isEmpty());
    EXPECT_TRUE(data.fontSubstituteName.isEmpty());
#endif

    EXPECT_FALSE(data.isEmbedded);
    EXPECT_FALSE(data.isSubset);
    EXPECT_EQ(static_cast<int>(data.type), 0);
    EXPECT_EQ(data.embRef.num, 0);
    EXPECT_EQ(data.embRef.gen, 0);
}

TEST_F(FontInfoDataTest_2763, EmptyStringsAreCopiedAsEmptyQStringNotUnset_2763)
{
    FontInfo fi;
    fi.setName(std::string(""));
    fi.setFile(std::string(""));
    fi.setSubstituteName(std::string(""));
    fi.setEmbedded(true);
    fi.setSubset(false);
    fi.setType(2);
    fi.setEmbRef(MakeRef(99, 7));

    Poppler::FontInfoData data(&fi);

#if defined(QSTRING_H) || __has_include(<QString>) || __has_include(<QtCore/QString>)
    EXPECT_EQ(data.fontName, QString::fromStdString(""));
    EXPECT_EQ(data.fontFile, QString::fromStdString(""));
    EXPECT_EQ(data.fontSubstituteName, QString::fromStdString(""));
#endif

    EXPECT_TRUE(data.isEmbedded);
    EXPECT_FALSE(data.isSubset);
    EXPECT_EQ(static_cast<int>(data.type), 2);
    EXPECT_EQ(data.embRef.num, 99);
    EXPECT_EQ(data.embRef.gen, 7);
}

TEST_F(FontInfoDataTest_2763, Utf8NamesConvertToQString_2763)
{
    FontInfo fi;
    fi.setName(std::string(u8"한글폰트"));
    fi.setFile(std::string(u8"/tmp/폰트.ttf"));
    fi.setSubstituteName(std::string(u8"代替フォント"));
    fi.setEmbedded(false);
    fi.setSubset(true);
    fi.setType(3);
    fi.setEmbRef(MakeRef(5, 2));

    Poppler::FontInfoData data(&fi);

#if defined(QSTRING_H) || __has_include(<QString>) || __has_include(<QtCore/QString>)
    EXPECT_EQ(data.fontName, QString::fromStdString(std::string(u8"한글폰트")));
    EXPECT_EQ(data.fontFile, QString::fromStdString(std::string(u8"/tmp/폰트.ttf")));
    EXPECT_EQ(data.fontSubstituteName, QString::fromStdString(std::string(u8"代替フォント")));
#endif

    EXPECT_FALSE(data.isEmbedded);
    EXPECT_TRUE(data.isSubset);
    EXPECT_EQ(static_cast<int>(data.type), 3);
    EXPECT_EQ(data.embRef.num, 5);
    EXPECT_EQ(data.embRef.gen, 2);
}

#if GTEST_HAS_DEATH_TEST
TEST_F(FontInfoDataTest_2763, NullPointerCausesDeathOrAbort_2763)
{
    // If the implementation dereferences fi unconditionally (as it appears),
    // passing nullptr should crash. This is an observable error case.
    EXPECT_DEATH(
        {
            Poppler::FontInfoData data(nullptr);
            (void)data;
        },
        ""
    );
}
#endif

} // namespace