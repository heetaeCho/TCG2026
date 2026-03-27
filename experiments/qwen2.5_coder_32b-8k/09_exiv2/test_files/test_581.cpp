#include <gtest/gtest.h>

#include "exiv2/basicio.hpp"



namespace Exiv2 {

    class MemIoTest : public ::testing::Test {

    protected:

        std::unique_ptr<MemIo> memIo;



        void SetUp() override {

            memIo = std::make_unique<MemIo>();

        }

    };



    TEST_F(MemIoTest_581, SeekFromBegValidOffset_581) {

        EXPECT_EQ(memIo->seek(10, BasicIo::beg), 0);

        EXPECT_EQ(memIo->tell(), 10u);

    }



    TEST_F(MemIoTest_581, SeekFromCurValidOffset_581) {

        memIo->seek(10, BasicIo::beg);

        EXPECT_EQ(memIo->seek(5, BasicIo::cur), 0);

        EXPECT_EQ(memIo->tell(), 15u);

    }



    TEST_F(MemIoTest_581, SeekFromEndValidOffset_581) {

        memIo->write(reinterpret_cast<const byte*>("Hello"), 5);

        EXPECT_EQ(memIo->seek(-2, BasicIo::end), 0);

        EXPECT_EQ(memIo->tell(), 3u);

    }



    TEST_F(MemIoTest_581, SeekNegativeOffsetFromCur_581) {

        memIo->seek(10, BasicIo::beg);

        EXPECT_EQ(memIo->seek(-5, BasicIo::cur), 0);

        EXPECT_EQ(memIo->tell(), 5u);

    }



    TEST_F(MemIoTest_581, SeekBeyondEndOfBuffer_581) {

        memIo->write(reinterpret_cast<const byte*>("Hello"), 5);

        EXPECT_EQ(memIo->seek(10, BasicIo::beg), 1);

        EXPECT_TRUE(memIo->eof());

    }



    TEST_F(MemIoTest_581, SeekNegativeOffsetFromBeg_581) {

        EXPECT_EQ(memIo->seek(-5, BasicIo::beg), 1);

        EXPECT_FALSE(memIo->eof());

    }



    TEST_F(MemIoTest_581, SeekEndOfFileMarkerResetAfterSeek_581) {

        memIo->write(reinterpret_cast<const byte*>("Hello"), 5);

        memIo->seek(10, BasicIo::beg); // Set EOF marker

        EXPECT_EQ(memIo->seek(2, BasicIo::beg), 0); // Reset EOF marker by valid seek

        EXPECT_FALSE(memIo->eof());

    }



    TEST_F(MemIoTest_581, SeekBoundaryConditionStart_581) {

        EXPECT_EQ(memIo->seek(0, BasicIo::beg), 0);

        EXPECT_EQ(memIo->tell(), 0u);

    }



    TEST_F(MemIoTest_581, SeekBoundaryConditionEnd_581) {

        memIo->write(reinterpret_cast<const byte*>("Hello"), 5);

        EXPECT_EQ(memIo->seek(5, BasicIo::beg), 0);

        EXPECT_EQ(memIo->tell(), 5u);

    }

}
