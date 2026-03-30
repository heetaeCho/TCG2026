#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Stream.h"

#include <memory>



using namespace std;



class EmbedStreamTest_176 : public ::testing::Test {

protected:

    Stream mock_stream;

    Object dict; // Assuming Object is default-constructible and usable as a placeholder

    const bool limited = false;

    const Goffset length = 0;

    const bool reusable = false;



    unique_ptr<EmbedStream> embed_stream;



    void SetUp() override {

        embed_stream = make_unique<EmbedStream>(&mock_stream, move(dict), limited, length, reusable);

    }

};



TEST_F(EmbedStreamTest_176, GetKindDelegatesToUnderlyingStream_176) {

    EXPECT_CALL(mock_stream, getKind()).WillOnce(::testing::Return(strFile));

    EXPECT_EQ(embed_stream->getKind(), strFile);

}



TEST_F(EmbedStreamTest_176, RewindCallsUnderlyingStreamRewind_176) {

    EXPECT_CALL(mock_stream, rewind()).WillOnce(::testing::Return(true));

    EXPECT_TRUE(embed_stream->rewind());

}



TEST_F(EmbedStreamTest_176, GetCharDelegatesToUnderlyingStream_176) {

    EXPECT_CALL(mock_stream, getChar()).WillOnce(::testing::Return('a'));

    EXPECT_EQ(embed_stream->getChar(), 'a');

}



TEST_F(EmbedStreamTest_176, LookCharDelegatesToUnderlyingStream_176) {

    EXPECT_CALL(mock_stream, lookChar()).WillOnce(::testing::Return('b'));

    EXPECT_EQ(embed_stream->lookChar(), 'b');

}



TEST_F(EmbedStreamTest_176, GetPosDelegatesToUnderlyingStream_176) {

    EXPECT_CALL(mock_stream, getPos()).WillOnce(::testing::Return(Goffset{0}));

    EXPECT_EQ(embed_stream->getPos(), Goffset{0});

}



TEST_F(EmbedStreamTest_176, SetPosDelegatesToUnderlyingStream_176) {

    EXPECT_CALL(mock_stream, setPos(Goffset{5}, 0)).WillOnce(::testing::Return());

    embed_stream->setPos(Goffset{5}, 0);

}



TEST_F(EmbedStreamTest_176, GetUnfilteredCharDelegatesToUnderlyingStream_176) {

    EXPECT_CALL(mock_stream, getUnfilteredChar()).WillOnce(::testing::Return('c'));

    EXPECT_EQ(embed_stream->getUnfilteredChar(), 'c');

}



TEST_F(EmbedStreamTest_176, UnfilteredRewindCallsUnderlyingStreamUnfilteredRewind_176) {

    EXPECT_CALL(mock_stream, unfilteredRewind()).WillOnce(::testing::Return(true));

    EXPECT_TRUE(embed_stream->unfilteredRewind());

}
