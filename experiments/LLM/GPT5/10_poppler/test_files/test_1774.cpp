// StructElement_isTextString_1774_test.cc
#include <gtest/gtest.h>

#include <memory>
#include <string>

// Include required public headers first.
#include "Object.h"
#include "GooString.h"

// NOTE:
// `isTextString` is a `static` function in StructElement.cc (internal linkage).
// To test it as a black box via its real implementation, we include the .cc file
// into this test translation unit so the symbol is visible here.
#include "StructElement.cc"

namespace {

class IsTextStringTest_1774 : public ::testing::Test {};

TEST_F(IsTextStringTest_1774, ReturnsTrueForStringObject_1774)
{
  Object sObj(std::string("hello"));
  EXPECT_TRUE(isTextString(&sObj));
}

TEST_F(IsTextStringTest_1774, ReturnsTrueForEmptyString_1774)
{
  Object emptyObj(std::string(""));
  EXPECT_TRUE(isTextString(&emptyObj));
}

TEST_F(IsTextStringTest_1774, ReturnsTrueForLargeString_1774)
{
  std::string big(10000, 'x');
  Object bigObj(std::move(big));
  EXPECT_TRUE(isTextString(&bigObj));
}

TEST_F(IsTextStringTest_1774, ReturnsFalseForNonStringPrimitiveTypes_1774)
{
  Object bObj(true);
  Object iObj(123);
  Object rObj(3.14159);
  Object i64Obj(static_cast<long long>(-1234567890123LL));

  EXPECT_FALSE(isTextString(&bObj));
  EXPECT_FALSE(isTextString(&iObj));
  EXPECT_FALSE(isTextString(&rObj));
  EXPECT_FALSE(isTextString(&i64Obj));
}

TEST_F(IsTextStringTest_1774, ReturnsFalseForSpecialObjects_1774)
{
  Object nObj = Object::null();
  Object eObj = Object::eof();
  Object errObj = Object::error();

  EXPECT_FALSE(isTextString(&nObj));
  EXPECT_FALSE(isTextString(&eObj));
  EXPECT_FALSE(isTextString(&errObj));
}

TEST_F(IsTextStringTest_1774, ReturnsFalseForNameObject_1774)
{
  // Construct as a name, not a string.
  Object nameObj(objName, "MyName");
  EXPECT_FALSE(isTextString(&nameObj));
}

TEST_F(IsTextStringTest_1774, ReturnsFalseForCmdObject_1774)
{
  // Construct as a command, not a string.
  Object cmdObj(objCmd, "q");
  EXPECT_FALSE(isTextString(&cmdObj));
}

TEST_F(IsTextStringTest_1774, DeathOnNullptr_1774)
{
#if GTEST_HAS_DEATH_TEST
  EXPECT_DEATH_IF_SUPPORTED(
      {
        Object *p = nullptr;
        (void)isTextString(p);
      },
      ".*");
#else
  GTEST_SKIP() << "Death tests are not supported on this platform/configuration.";
#endif
}

} // namespace