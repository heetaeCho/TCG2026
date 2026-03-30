// File: test-poppler-optcontent-item-2768.cc
#include <gtest/gtest.h>

#include <QString>

// Poppler Qt5 private header (as provided in the prompt).
// Adjust include path if your build system uses a different include layout.
#include "poppler-optcontent-private.h"

namespace {

using Poppler::OptContentItem;

TEST(OptContentItemTest_2768, CtorWithQString_SetsNameAndDefaults_2768)
{
    const QString label = QStringLiteral("Layer 1");
    OptContentItem item(label);

    EXPECT_EQ(item.name(), label);

    // Observable defaults from the provided implementation snippet.
    EXPECT_EQ(item.parent(), nullptr);
    EXPECT_EQ(item.group(), nullptr);
    EXPECT_TRUE(item.isEnabled());

    // ItemState enum values given: On=0, Off=1, HeadingOnly=2
    EXPECT_EQ(static_cast<int>(item.state()), 2);
}

TEST(OptContentItemTest_2768, CtorWithQString_AllowsEmptyLabel_2768)
{
    const QString emptyLabel = QString();
    OptContentItem item(emptyLabel);

    EXPECT_EQ(item.name(), emptyLabel);
    EXPECT_EQ(item.name().size(), 0);

    EXPECT_EQ(item.parent(), nullptr);
    EXPECT_EQ(item.group(), nullptr);
    EXPECT_TRUE(item.isEnabled());
    EXPECT_EQ(static_cast<int>(item.state()), 2);
}

TEST(OptContentItemTest_2768, CtorWithQString_PreservesUnicodeLabel_2768)
{
    const QString label = QString::fromUtf8("레이어-α-✓-中文");
    OptContentItem item(label);

    EXPECT_EQ(item.name(), label);
    EXPECT_FALSE(item.name().isEmpty());

    EXPECT_EQ(item.parent(), nullptr);
    EXPECT_EQ(item.group(), nullptr);
    EXPECT_TRUE(item.isEnabled());
    EXPECT_EQ(static_cast<int>(item.state()), 2);
}

TEST(OptContentItemTest_2768, CtorWithQString_HandlesLongLabel_2768)
{
    QString longLabel;
    longLabel.reserve(4096);
    for (int i = 0; i < 4096; ++i) {
        longLabel.append(QChar(u'a' + (i % 26)));
    }

    OptContentItem item(longLabel);

    EXPECT_EQ(item.name(), longLabel);
    EXPECT_EQ(item.name().size(), longLabel.size());

    EXPECT_EQ(item.parent(), nullptr);
    EXPECT_EQ(item.group(), nullptr);
    EXPECT_TRUE(item.isEnabled());
    EXPECT_EQ(static_cast<int>(item.state()), 2);
}

TEST(OptContentItemTest_2768, CtorWithQString_DistinctInstancesHaveDistinctNames_2768)
{
    const QString labelA = QStringLiteral("A");
    const QString labelB = QStringLiteral("B");

    OptContentItem itemA(labelA);
    OptContentItem itemB(labelB);

    EXPECT_EQ(itemA.name(), labelA);
    EXPECT_EQ(itemB.name(), labelB);
    EXPECT_NE(itemA.name(), itemB.name());

    // Both should still have the same observable defaults.
    EXPECT_EQ(itemA.parent(), nullptr);
    EXPECT_EQ(itemB.parent(), nullptr);
    EXPECT_EQ(itemA.group(), nullptr);
    EXPECT_EQ(itemB.group(), nullptr);
    EXPECT_TRUE(itemA.isEnabled());
    EXPECT_TRUE(itemB.isEnabled());
    EXPECT_EQ(static_cast<int>(itemA.state()), 2);
    EXPECT_EQ(static_cast<int>(itemB.state()), 2);
}

} // namespace