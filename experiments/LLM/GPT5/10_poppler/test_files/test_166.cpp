// TEST_ID = 166
// Unit tests for BaseMemStream::getKind (black-box: only observable interface)

#include <gtest/gtest.h>

#include "Stream.h"

#include <type_traits>
#include <utility>
#include <vector>

namespace {

// ---- Minimal, version-tolerant helper to create a "null" Object ----
template <typename T, typename = void>
struct has_initNull : std::false_type {};
template <typename T>
struct has_initNull<T, std::void_t<decltype(std::declval<T &>().initNull())>> : std::true_type {};

template <typename T, typename = void>
struct has_setToNull : std::false_type {};
template <typename T>
struct has_setToNull<T, std::void_t<decltype(std::declval<T &>().setToNull())>> : std::true_type {};

static Object makeNullObject()
{
    Object obj;
    if constexpr (has_setToNull<Object>::value) {
        obj.setToNull();
    } else if constexpr (has_initNull<Object>::value) {
        obj.initNull();
    } else {
        // Many Poppler versions default-construct to a null object; keep as-is.
    }
    return obj;
}

class BaseMemStreamTest_166 : public ::testing::Test
{
protected:
    static std::unique_ptr<BaseMemStream<unsigned char>> makeStream(unsigned char *buf,
                                                                    Goffset start,
                                                                    Goffset length)
    {
        Object dict = makeNullObject();
        return std::make_unique<BaseMemStream<unsigned char>>(buf, start, length, std::move(dict));
    }
};

} // namespace

TEST_F(BaseMemStreamTest_166, GetKindReturnsStrWeirdForEmptyStream_166)
{
    auto s = makeStream(nullptr, /*start=*/0, /*length=*/0);
    ASSERT_NE(s, nullptr);
    EXPECT_EQ(s->getKind(), strWeird);
}

TEST_F(BaseMemStreamTest_166, GetKindReturnsStrWeirdForNonEmptyStream_166)
{
    std::vector<unsigned char> data = {0x01, 0x02, 0x03, 0x04};
    auto s = makeStream(data.data(), /*start=*/0, /*length=*/static_cast<Goffset>(data.size()));
    ASSERT_NE(s, nullptr);
    EXPECT_EQ(s->getKind(), strWeird);
}

TEST_F(BaseMemStreamTest_166, GetKindWorksOnConstObject_166)
{
    std::vector<unsigned char> data = {0xAA};
    auto s = makeStream(data.data(), /*start=*/0, /*length=*/1);
    ASSERT_NE(s, nullptr);

    const BaseMemStream<unsigned char> &cs = *s;
    EXPECT_EQ(cs.getKind(), strWeird);
}

TEST_F(BaseMemStreamTest_166, GetKindUnaffectedByNonZeroStart_166)
{
    // Boundary-style coverage: start offset differs from 0, but getKind remains observable constant.
    std::vector<unsigned char> data(16, 0x7F);
    auto s = makeStream(data.data(), /*start=*/5, /*length=*/static_cast<Goffset>(data.size()));
    ASSERT_NE(s, nullptr);
    EXPECT_EQ(s->getKind(), strWeird);
}