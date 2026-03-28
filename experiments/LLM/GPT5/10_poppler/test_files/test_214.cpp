// ASCII85Encoder_test_214.cpp
#include <gtest/gtest.h>

#include <poppler/Object.h>
#include <poppler/Stream.h>

namespace {

class ASCII85EncoderTest_214 : public ::testing::Test
{
protected:
    static MemStream MakeMemStream(const char *data, int len)
    {
        // MemStream takes an Object&& dictionary; objNull is sufficient for testing.
        return MemStream(data, /*startA=*/0, /*lengthA=*/len, Object(objNull));
    }
};

TEST_F(ASCII85EncoderTest_214, GetKindReturnsStrWeird_214)
{
    const char input[] = "Hello";
    auto src = MakeMemStream(input, 5);
    ASCII85Encoder enc(&src);

    EXPECT_EQ(enc.getKind(), strWeird);
}

TEST_F(ASCII85EncoderTest_214, GetPSFilterReturnsNullptr_214)
{
    const char input[] = "Hello";
    auto src = MakeMemStream(input, 5);
    ASCII85Encoder enc(&src);

    EXPECT_EQ(enc.getPSFilter(/*psLevel=*/2, /*indent=*/"  "), nullptr);
}

TEST_F(ASCII85EncoderTest_214, IsBinaryAndIsEncoderHaveExpectedValues_214)
{
    const char input[] = "Hello";
    auto src = MakeMemStream(input, 5);
    ASCII85Encoder enc(&src);

    EXPECT_FALSE(enc.isBinary(/*last=*/true));
    EXPECT_FALSE(enc.isBinary(/*last=*/false));
    EXPECT_TRUE(enc.isEncoder());
}

TEST_F(ASCII85EncoderTest_214, LookCharMatchesGetCharWhenNotEof_214)
{
    const char input[] = "Hello";
    auto src = MakeMemStream(input, 5);
    ASCII85Encoder enc(&src);

    enc.reset();

    const int c1 = enc.lookChar();
    if (c1 != EOF) {
        const int c2 = enc.getChar();
        EXPECT_EQ(c2, c1);
    } else {
        // If an implementation ever reports EOF immediately, getChar must also report EOF.
        EXPECT_EQ(enc.getChar(), EOF);
    }
}

TEST_F(ASCII85EncoderTest_214, EmptyInputReturnsEof_214)
{
    auto src = MakeMemStream(/*data=*/"", /*len=*/0);
    ASCII85Encoder enc(&src);

    enc.reset();
    EXPECT_EQ(enc.lookChar(), EOF);
    EXPECT_EQ(enc.getChar(), EOF);
}

TEST_F(ASCII85EncoderTest_214, ResetAllowsReadingFromBeginningAgain_214)
{
    const char input[] = "Hello";
    auto src = MakeMemStream(input, 5);
    ASCII85Encoder enc(&src);

    enc.reset();
    const int first = enc.getChar();

    enc.reset();
    const int firstAfterReset = enc.getChar();

    EXPECT_EQ(firstAfterReset, first);
}

} // namespace