// TEST: RadioButtonGroup ctor interactions (black-box via collaborators)
// File: test-radiobuttongroup-2766.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <vector>
#include <string>
#include <utility>

// ---------- Minimal stand-ins to compile the provided implementation (no internal logic inferred) ----------

// Minimal "qDebug()" stream sink
struct DebugSink {
  template <typename T>
  DebugSink &operator<<(const T &) { return *this; }
};
inline DebugSink qDebug() { return DebugSink{}; }

// Minimal QString used by the snippet (only what is required)
class QString {
public:
  QString() = default;
  explicit QString(std::string s) : s_(std::move(s)) {}

  static QString number(int v) { return QString(std::to_string(v)); }

  const std::string &toStdString() const { return s_; }

  friend bool operator==(const QString &a, const QString &b) { return a.s_ == b.s_; }

private:
  std::string s_;
};

// Provide std::as_const for C++14 if needed
#if __cplusplus < 201703L
namespace std {
template <class T>
constexpr const T &as_const(T &t) noexcept { return t; }
template <class T>
void as_const(const T &&) = delete;
} // namespace std
#endif

// Minimal Object/Array stand-ins (only methods used by the snippet)
enum ObjType {
  objNone = 0,
  objInt = 1,
  objRef = 2
};

class Object {
public:
  static Object MakeRef(int refNum) {
    Object o;
    o.type_ = objRef;
    o.refNum_ = refNum;
    return o;
  }

  static Object MakeNonRef(ObjType t = objInt, int refNumForTest = 0) {
    Object o;
    o.type_ = t;
    o.refNum_ = refNumForTest; // what getRefNum() returns if asked
    return o;
  }

  bool isRef() const { return type_ == objRef; }
  ObjType getType() const { return type_; }
  int getRefNum() const { return refNum_; }

private:
  ObjType type_ = objNone;
  int refNum_ = 0;
};

class Array {
public:
  void add(Object o) { elems_.push_back(std::move(o)); }
  int getLength() const { return static_cast<int>(elems_.size()); }
  const Object &getNF(int i) const { return elems_.at(static_cast<size_t>(i)); }

private:
  std::vector<Object> elems_;
};

// Forward decls per snippet
namespace Poppler {
class OptContentModelPrivate;
class RadioButtonGroup;
class OptContentItem {
public:
  virtual ~OptContentItem() = default;
  virtual void appendRBGroup(RadioButtonGroup *group) = 0;
};

class OptContentModelPrivate {
public:
  virtual ~OptContentModelPrivate() = default;
  virtual OptContentItem *itemFromRef(const QString &ref) = 0;
};
} // namespace Poppler

// ---------- Class under test: pasted implementation (treated as black box) ----------
namespace Poppler {
class RadioButtonGroup {
public:
  RadioButtonGroup(OptContentModelPrivate *ocModel, Array *rbarray)
  {
    itemsInGroup.reserve(static_cast<size_t>(rbarray->getLength()));
    for (int i = 0; i < rbarray->getLength(); ++i) {
      const Object &ref = rbarray->getNF(i);
      if (!ref.isRef()) {
        qDebug() << "expected ref, but got:" << ref.getType();
      }
      OptContentItem *item = ocModel->itemFromRef(QString::number(ref.getRefNum()));
      itemsInGroup.push_back(item);
    }
    for (OptContentItem *item : std::as_const(itemsInGroup)) {
      item->appendRBGroup(this);
    }
  }

private:
  std::vector<OptContentItem *> itemsInGroup;
};
} // namespace Poppler

// ---------- Mocks ----------
namespace Poppler {
class MockOptContentItem : public OptContentItem {
public:
  MOCK_METHOD(void, appendRBGroup, (RadioButtonGroup *group), (override));
};

class MockOptContentModelPrivate : public OptContentModelPrivate {
public:
  MOCK_METHOD(OptContentItem *, itemFromRef, (const QString &ref), (override));
};
} // namespace Poppler

using ::testing::_;
using ::testing::InSequence;
using ::testing::Return;
using ::testing::StrictMock;

namespace {

// Helper matcher for our minimal QString
MATCHER_P(QStringEq, s, "") {
  return arg.toStdString() == s;
}

TEST(RadioButtonGroupTest_2766, CtorCallsItemFromRefAndAppendsGroupForEachRef_2766)
{
  StrictMock<Poppler::MockOptContentModelPrivate> model;
  StrictMock<Poppler::MockOptContentItem> item1;
  StrictMock<Poppler::MockOptContentItem> item2;
  StrictMock<Poppler::MockOptContentItem> item3;

  Array arr;
  arr.add(Object::MakeRef(1));
  arr.add(Object::MakeRef(2));
  arr.add(Object::MakeRef(3));

  {
    InSequence seq;
    EXPECT_CALL(model, itemFromRef(QStringEq("1"))).WillOnce(Return(&item1));
    EXPECT_CALL(model, itemFromRef(QStringEq("2"))).WillOnce(Return(&item2));
    EXPECT_CALL(model, itemFromRef(QStringEq("3"))).WillOnce(Return(&item3));
  }

  // The constructor should append the group to each returned item.
  // We don't assert the exact pointer value beyond "same instance" across calls.
  Poppler::RadioButtonGroup *seenGroup = nullptr;
  EXPECT_CALL(item1, appendRBGroup(_)).WillOnce([&](Poppler::RadioButtonGroup *g) { seenGroup = g; });
  EXPECT_CALL(item2, appendRBGroup(_)).WillOnce([&](Poppler::RadioButtonGroup *g) { EXPECT_EQ(g, seenGroup); });
  EXPECT_CALL(item3, appendRBGroup(_)).WillOnce([&](Poppler::RadioButtonGroup *g) { EXPECT_EQ(g, seenGroup); });

  Poppler::RadioButtonGroup group(&model, &arr);
  (void)group;
}

TEST(RadioButtonGroupTest_2766, CtorWithEmptyArrayDoesNotCallModelOrItems_2766)
{
  StrictMock<Poppler::MockOptContentModelPrivate> model;
  Array empty;

  EXPECT_CALL(model, itemFromRef(_)).Times(0);

  Poppler::RadioButtonGroup group(&model, &empty);
  (void)group;
}

TEST(RadioButtonGroupTest_2766, CtorHandlesNonRefObjectByStillQueryingModelAndAppending_2766)
{
  StrictMock<Poppler::MockOptContentModelPrivate> model;
  StrictMock<Poppler::MockOptContentItem> itemA;
  StrictMock<Poppler::MockOptContentItem> itemB;

  Array arr;
  // First element is non-ref; our stand-in returns refNum=0 for it.
  arr.add(Object::MakeNonRef(objInt, /*refNumForTest=*/0));
  // Second element is a ref.
  arr.add(Object::MakeRef(9));

  {
    InSequence seq;
    EXPECT_CALL(model, itemFromRef(QStringEq("0"))).WillOnce(Return(&itemA));
    EXPECT_CALL(model, itemFromRef(QStringEq("9"))).WillOnce(Return(&itemB));
  }

  Poppler::RadioButtonGroup *seenGroup = nullptr;
  EXPECT_CALL(itemA, appendRBGroup(_)).WillOnce([&](Poppler::RadioButtonGroup *g) { seenGroup = g; });
  EXPECT_CALL(itemB, appendRBGroup(_)).WillOnce([&](Poppler::RadioButtonGroup *g) { EXPECT_EQ(g, seenGroup); });

  Poppler::RadioButtonGroup group(&model, &arr);
  (void)group;
}

TEST(RadioButtonGroupTest_2766, CtorDiesIfModelReturnsNullptrItem_2766)
{
  StrictMock<Poppler::MockOptContentModelPrivate> model;

  Array arr;
  arr.add(Object::MakeRef(42));

  EXPECT_CALL(model, itemFromRef(QStringEq("42"))).WillOnce(Return(nullptr));

  // Observable error case: constructor will attempt to call appendRBGroup on nullptr.
  ASSERT_DEATH(
    {
      Poppler::RadioButtonGroup group(&model, &arr);
      (void)group;
    },
    ""
  );
}

} // namespace