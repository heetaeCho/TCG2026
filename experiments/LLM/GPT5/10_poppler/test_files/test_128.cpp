// TEST_ID: 128
// File: BaseStream_getDict_tests_128.cpp

#include <gtest/gtest.h>

#include "poppler/Stream.h"
#include "poppler/Object.h"
#include "poppler/Dict.h"

namespace {

class DummyBaseStream final : public BaseStream {
public:
  DummyBaseStream(Object &&dictA, Goffset lengthA)
      : BaseStream(std::move(dictA), lengthA) {}

  // Implement the minimum set of Stream pure-virtuals (per upstream Poppler design).
  // These are simple stubs to allow instantiation; tests focus only on BaseStream::getDict().
  void reset() override {}
  void close() override {}

  int getChar() override { return EOF; }
  int lookChar() override { return EOF; }
  Goffset getPos() override { return 0; }
};

} // namespace

class BaseStreamGetDictTest_128 : public ::testing::Test {
};

TEST_F(BaseStreamGetDictTest_128, ReturnsSameDictPointerWhenConstructedWithDictObject_128)
{
  Dict *d = new Dict(nullptr);
  Object dictObj(d);

  DummyBaseStream s(std::move(dictObj), /*lengthA=*/0);

  EXPECT_EQ(s.getDict(), d);

  delete d;
}

TEST_F(BaseStreamGetDictTest_128, ReturnsNullptrWhenConstructedWithNonDictObject_128)
{
  Object nonDictObj(42); // int object, not a dict

  DummyBaseStream s(std::move(nonDictObj), /*lengthA=*/0);

  EXPECT_EQ(s.getDict(), nullptr);
}

TEST_F(BaseStreamGetDictTest_128, ReturnsNullptrWhenConstructedWithDefaultObject_128)
{
  Object defaultObj; // default-constructed object (e.g., none)

  DummyBaseStream s(std::move(defaultObj), /*lengthA=*/0);

  EXPECT_EQ(s.getDict(), nullptr);
}

TEST_F(BaseStreamGetDictTest_128, ReflectsUpdatesMadeViaGetDictObject_128)
{
  Dict *d1 = new Dict(nullptr);
  Dict *d2 = new Dict(nullptr);

  DummyBaseStream s(Object(d1), /*lengthA=*/0);
  ASSERT_EQ(s.getDict(), d1);

  // Update via public interface (getDictObject) and verify getDict() reflects it.
  Object *dictObject = s.getDictObject();
  ASSERT_NE(dictObject, nullptr);

  *dictObject = Object(d2);

  EXPECT_EQ(s.getDict(), d2);

  delete d1;
  delete d2;
}

TEST_F(BaseStreamGetDictTest_128, CanBeChangedFromDictToNonDictViaGetDictObject_128)
{
  Dict *d = new Dict(nullptr);

  DummyBaseStream s(Object(d), /*lengthA=*/0);
  ASSERT_EQ(s.getDict(), d);

  Object *dictObject = s.getDictObject();
  ASSERT_NE(dictObject, nullptr);

  *dictObject = Object(0); // set to int object

  EXPECT_EQ(s.getDict(), nullptr);

  delete d;
}