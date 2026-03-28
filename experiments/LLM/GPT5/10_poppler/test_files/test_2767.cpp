// OptContentItemTest_2767.cpp
#include <gtest/gtest.h>

#include <QString>

// -----------------------------------------------------------------------------
// Test doubles for external dependencies used by OptContentItem(OptionalContentGroup*).
// These are *not* re-implementations of OptContentItem. They only provide the
// minimal collaborator surface needed to construct the real OptContentItem.
// -----------------------------------------------------------------------------

// Minimal GooString stand-in (Poppler core type).
class GooString {
public:
  explicit GooString(const char *s) : str_(s ? s : "") {}
  const char *c_str() const { return str_.c_str(); }

private:
  std::string str_;
};

// Minimal OptionalContentGroup stand-in (Poppler core type).
class OptionalContentGroup {
public:
  enum State { On = 0, Off = 1 };

  explicit OptionalContentGroup(const char *name, State st)
      : name_(name), state_(st) {}

  const GooString *getName() { return &name_; }
  State getState() const { return state_; }
  void setState(State st) { state_ = st; }

private:
  GooString name_;
  State state_;
};

// Minimal helper used by OptContentItem ctor in the provided snippet.
static inline QString UnicodeParsedString(const GooString *s) {
  return QString::fromUtf8(s ? s->c_str() : "");
}

// -----------------------------------------------------------------------------
// Include the interface under test.
// IMPORTANT: This must come after the test doubles above so the header can
// resolve OptionalContentGroup/GooString/UnicodeParsedString.
// -----------------------------------------------------------------------------
#include "./TestProjects/poppler/qt5/src/poppler-optcontent-private.h"

// -----------------------------------------------------------------------------
// Tests
// -----------------------------------------------------------------------------

namespace {

class OptContentItemTest_2767 : public ::testing::Test {};

TEST_F(OptContentItemTest_2767, CtorFromGroup_SetsGroupAndParentNull_2767) {
  OptionalContentGroup group("LayerA", OptionalContentGroup::On);

  Poppler::OptContentItem item(&group);

  EXPECT_EQ(item.group(), &group);
  EXPECT_EQ(item.parent(), nullptr);
}

TEST_F(OptContentItemTest_2767, CtorFromGroup_EnabledIsTrue_2767) {
  OptionalContentGroup group("LayerA", OptionalContentGroup::On);

  Poppler::OptContentItem item(&group);

  EXPECT_TRUE(item.isEnabled());
}

TEST_F(OptContentItemTest_2767, CtorFromGroup_StateReflectsGroupOn_2767) {
  OptionalContentGroup group("LayerA", OptionalContentGroup::On);

  Poppler::OptContentItem item(&group);

  EXPECT_EQ(item.state(), Poppler::OptContentItem::On);
}

TEST_F(OptContentItemTest_2767, CtorFromGroup_StateReflectsGroupOff_2767) {
  OptionalContentGroup group("LayerA", OptionalContentGroup::Off);

  Poppler::OptContentItem item(&group);

  EXPECT_EQ(item.state(), Poppler::OptContentItem::Off);
}

TEST_F(OptContentItemTest_2767, CtorFromGroup_NameUsesGroupName_2767) {
  OptionalContentGroup group("My Optional Layer", OptionalContentGroup::On);

  Poppler::OptContentItem item(&group);

  EXPECT_EQ(item.name(), QString("My Optional Layer"));
}

TEST_F(OptContentItemTest_2767, CtorFromGroup_EmptyNameBoundary_2767) {
  OptionalContentGroup group("", OptionalContentGroup::On);

  Poppler::OptContentItem item(&group);

  EXPECT_EQ(item.name(), QString(""));
  EXPECT_EQ(item.state(), Poppler::OptContentItem::On);
  EXPECT_TRUE(item.isEnabled());
}

TEST_F(OptContentItemTest_2767, CtorFromGroup_LongNameBoundary_2767) {
  const QString longName = QString(5000, QChar(u'A'));
  const QByteArray utf8 = longName.toUtf8();

  OptionalContentGroup group(utf8.constData(), OptionalContentGroup::Off);

  Poppler::OptContentItem item(&group);

  EXPECT_EQ(item.name(), longName);
  EXPECT_EQ(item.state(), Poppler::OptContentItem::Off);
}

} // namespace