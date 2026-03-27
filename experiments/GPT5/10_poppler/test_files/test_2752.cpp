// ObjectConstructorDictTest_2752.cc
#include <gtest/gtest.h>

#include "poppler/Object.h"
#include "poppler/Dict.h"

// Some builds may require XRef to be a complete type for Dict's constructor.
// If your build fails here, add: #include "poppler/XRef.h"

class ObjectTest_2752 : public ::testing::Test {};

TEST_F(ObjectTest_2752, ConstructWithValidDict_SetsTypeAndReturnsSamePointer_2752)
{
    Dict dict(nullptr); // XRef* is allowed to be nullptr in many Poppler use-cases.

    Object obj(&dict);

    EXPECT_EQ(obj.getType(), objDict);
    EXPECT_TRUE(obj.isDict());
    EXPECT_FALSE(obj.isNull());
    EXPECT_EQ(obj.getDict(), &dict);
}

TEST_F(ObjectTest_2752, ConstructWithEmptyDict_DictLengthObservableThroughObject_2752)
{
    Dict dict(nullptr);
    ASSERT_EQ(dict.getLength(), 0);

    Object obj(&dict);

    // Observable behavior via Object's public interface.
    EXPECT_EQ(obj.dictGetLength(), 0);
}

TEST_F(ObjectTest_2752, ConstructWithNullDict_TriggersAssertionDeathInDebug_2752)
{
#if defined(GTEST_HAS_DEATH_TEST) && GTEST_HAS_DEATH_TEST
    // The provided implementation uses assert(dictA). That is typically enabled
    // only in debug/non-NDEBUG builds.
#ifndef NDEBUG
    ASSERT_DEATH(
        {
            Object obj(static_cast<Dict *>(nullptr));
            (void)obj;
        },
        "");
#else
    GTEST_SKIP() << "Asserts are disabled (NDEBUG); cannot observe assertion death.";
#endif
#else
    GTEST_SKIP() << "Death tests are not supported in this build/toolchain.";
#endif
}