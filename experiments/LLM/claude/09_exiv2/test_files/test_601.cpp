#include <gtest/gtest.h>
#include <exiv2/basicio.hpp>
#include <exiv2/exiv2.hpp>
#include <cstring>

namespace {

// Since RemoteIo requires concrete subclasses (HttpIo, CurlIo, etc.),
// we test through the available concrete types that derive from RemoteIo.
// We'll use HttpIo if available, or test with what's constructible.

class RemoteIoCloseTest_601 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that close() returns 0
TEST_F(RemoteIoCloseTest_601, CloseReturnsZero_601) {
    // Use a dummy HTTP URL - close should still return 0
    try {
        auto io = Exiv2::ImageFactory::createIo("http://localhost:0/nonexistent");
        if (io) {
            int result = io->close();
            EXPECT_EQ(result, 0);
        }
    } catch (const Exiv2::Error&) {
        // If URL scheme not supported, that's acceptable
        GTEST_SKIP() << "HTTP IO not supported in this build";
    }
}

// Test that close() can be called multiple times safely
TEST_F(RemoteIoCloseTest_601, CloseCanBeCalledMultipleTimes_601) {
    try {
        auto io = Exiv2::ImageFactory::createIo("http://localhost:0/nonexistent");
        if (io) {
            EXPECT_EQ(io->close(), 0);
            EXPECT_EQ(io->close(), 0);
            EXPECT_EQ(io->close(), 0);
        }
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "HTTP IO not supported in this build";
    }
}

// Test that bigBlock_ is nullptr after close (observable through mmap/munmap behavior)
TEST_F(RemoteIoCloseTest_601, CloseCleansBigBlock_601) {
    try {
        auto io = Exiv2::ImageFactory::createIo("http://localhost:0/nonexistent");
        if (io) {
            int result = io->close();
            EXPECT_EQ(result, 0);
            // bigBlock_ should be nullptr - verify indirectly by checking no crash on second close
            result = io->close();
            EXPECT_EQ(result, 0);
        }
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "HTTP IO not supported in this build";
    }
}

// Test eof() state after close
TEST_F(RemoteIoCloseTest_601, EofAfterClose_601) {
    try {
        auto io = Exiv2::ImageFactory::createIo("http://localhost:0/nonexistent");
        if (io) {
            io->close();
            // After close, eof should be false (reset by close if blocksMap_ exists)
            // This is observable behavior
            bool eofState = io->eof();
            // Just verify it doesn't crash - the actual value depends on internal state
            (void)eofState;
            SUCCEED();
        }
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "HTTP IO not supported in this build";
    }
}

// Test tell() after close
TEST_F(RemoteIoCloseTest_601, TellAfterCloseIsZero_601) {
    try {
        auto io = Exiv2::ImageFactory::createIo("http://localhost:0/nonexistent");
        if (io) {
            io->close();
            // After close, idx_ should be reset to 0 if blocksMap_ exists
            size_t pos = io->tell();
            EXPECT_EQ(pos, 0u);
        }
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "HTTP IO not supported in this build";
    }
}

// Test close without prior open
TEST_F(RemoteIoCloseTest_601, CloseWithoutOpenReturnsZero_601) {
    try {
        auto io = Exiv2::ImageFactory::createIo("http://localhost:0/test");
        if (io) {
            // Close without opening - should still return 0
            int result = io->close();
            EXPECT_EQ(result, 0);
        }
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "HTTP IO not supported in this build";
    }
}

// Test with MemIo as a baseline comparison for BasicIo interface
class BasicIoInterfaceTest_601 : public ::testing::Test {};

TEST_F(BasicIoInterfaceTest_601, MemIoCloseReturnsZero_601) {
    Exiv2::MemIo memIo;
    int result = memIo.close();
    EXPECT_EQ(result, 0);
}

TEST_F(BasicIoInterfaceTest_601, MemIoCloseMultipleTimes_601) {
    Exiv2::MemIo memIo;
    EXPECT_EQ(memIo.close(), 0);
    EXPECT_EQ(memIo.close(), 0);
}

TEST_F(BasicIoInterfaceTest_601, FileIoCloseReturnsZero_601) {
    // Create a temporary file for testing
    Exiv2::FileIo fileIo("test_close_601.tmp");
    // Close without open should be safe
    int result = fileIo.close();
    EXPECT_EQ(result, 0);
}

TEST_F(BasicIoInterfaceTest_601, FileIoCloseAfterOpen_601) {
    // Create a temporary file
    {
        std::ofstream ofs("test_close_open_601.tmp");
        ofs << "test data";
    }
    Exiv2::FileIo fileIo("test_close_open_601.tmp");
    EXPECT_EQ(fileIo.open(), 0);
    EXPECT_TRUE(fileIo.isopen());
    EXPECT_EQ(fileIo.close(), 0);
    EXPECT_FALSE(fileIo.isopen());
    std::remove("test_close_open_601.tmp");
}

}  // namespace
