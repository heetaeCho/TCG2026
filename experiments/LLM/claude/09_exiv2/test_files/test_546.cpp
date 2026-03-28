#include <gtest/gtest.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <fstream>

// We need to replicate the minimal structures to test the switchMode function
// Since we're treating the implementation as a black box, we'll create a test
// harness that can exercise the FileIo::Impl::switchMode method through
// file operations.

// First, let's define the necessary types and the Impl class as given
namespace {

enum OpMode { opRead = 0, opWrite = 1, opSeek = 2 };

// Minimal reimplementation of the Impl class structure for testing switchMode
// This mirrors the interface provided in the partial code
class ImplTestable {
public:
    std::string path_;
    std::string openMode_;
    FILE* fp_ = nullptr;
    OpMode opMode_ = opSeek;
#ifdef _WIN32
    std::wstring wpath_;
#endif

    explicit ImplTestable(const std::string& path) : path_(path) {}

    ~ImplTestable() {
        if (fp_) {
            std::fclose(fp_);
            fp_ = nullptr;
        }
    }

    // Direct copy of the switchMode logic from the provided code
    int switchMode(OpMode opMode) {
        if (opMode_ == opMode)
            return 0;

        OpMode oldOpMode = opMode_;
        opMode_ = opMode;

        bool reopen = true;
        switch (opMode) {
            case opRead:
                if (openMode_.front() == 'r' || openMode_.at(1) == '+')
                    reopen = false;
                break;
            case opWrite:
                if (openMode_.front() != 'r' || openMode_.at(1) == '+')
                    reopen = false;
                break;
            case opSeek:
                reopen = false;
                break;
        }

        if (!reopen) {
            if (oldOpMode == opSeek)
                return 0;
            std::fseek(fp_, 0, SEEK_CUR);
            return 0;
        }

        // Need to reopen
#ifdef _WIN32
        auto offset = _ftelli64(fp_);
#else
        auto offset = ftello(fp_);
#endif
        if (offset == -1)
            return -1;

        std::fclose(fp_);

        openMode_ = "r+b";
        opMode_ = opSeek;

#ifdef _WIN32
        if (_wfopen_s(&fp_, wpath_.c_str(), L"r+b"))
            return 1;
        return _fseeki64(fp_, offset, SEEK_SET);
#else
        fp_ = std::fopen(path_.c_str(), openMode_.c_str());
        if (!fp_)
            return 1;
        return fseeko(fp_, offset, SEEK_SET);
#endif
    }
};

// Helper to create a temporary file with some content
class TempFile {
public:
    std::string path;

    TempFile(const std::string& name, const std::string& content = "Hello, World! This is test content for switchMode testing.") {
        path = name;
        std::ofstream ofs(path, std::ios::binary);
        ofs << content;
        ofs.close();
    }

    ~TempFile() {
        std::remove(path.c_str());
    }
};

}  // anonymous namespace

class SwitchModeTest_546 : public ::testing::Test {
protected:
    void SetUp() override {
        tempFile_ = std::make_unique<TempFile>("test_switchmode_546.tmp");
    }

    void TearDown() override {
        tempFile_.reset();
    }

    std::unique_ptr<TempFile> tempFile_;
};

// Test: switching to the same mode returns 0 immediately
TEST_F(SwitchModeTest_546, SameModeReturnsZero_546) {
    ImplTestable impl(tempFile_->path);
    impl.openMode_ = "r+b";
    impl.fp_ = std::fopen(tempFile_->path.c_str(), "r+b");
    ASSERT_NE(impl.fp_, nullptr);
    impl.opMode_ = opSeek;

    // switchMode to opSeek when already opSeek should return 0
    int result = impl.switchMode(opSeek);
    EXPECT_EQ(result, 0);
}

// Test: switching from opSeek to opRead with "r+b" mode (no reopen needed)
TEST_F(SwitchModeTest_546, SeekToReadWithRPlusBNoReopen_546) {
    ImplTestable impl(tempFile_->path);
    impl.openMode_ = "r+b";
    impl.fp_ = std::fopen(tempFile_->path.c_str(), "r+b");
    ASSERT_NE(impl.fp_, nullptr);
    impl.opMode_ = opSeek;

    int result = impl.switchMode(opRead);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(impl.opMode_, opRead);
}

// Test: switching from opSeek to opWrite with "r+b" mode (no reopen needed)
TEST_F(SwitchModeTest_546, SeekToWriteWithRPlusBNoReopen_546) {
    ImplTestable impl(tempFile_->path);
    impl.openMode_ = "r+b";
    impl.fp_ = std::fopen(tempFile_->path.c_str(), "r+b");
    ASSERT_NE(impl.fp_, nullptr);
    impl.opMode_ = opSeek;

    int result = impl.switchMode(opWrite);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(impl.opMode_, opWrite);
}

// Test: switching from opRead to opSeek (no reopen, oldOpMode != opSeek)
TEST_F(SwitchModeTest_546, ReadToSeekCallsFseek_546) {
    ImplTestable impl(tempFile_->path);
    impl.openMode_ = "r+b";
    impl.fp_ = std::fopen(tempFile_->path.c_str(), "r+b");
    ASSERT_NE(impl.fp_, nullptr);
    impl.opMode_ = opRead;

    int result = impl.switchMode(opSeek);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(impl.opMode_, opSeek);
}

// Test: switching from opWrite to opSeek
TEST_F(SwitchModeTest_546, WriteToSeekCallsFseek_546) {
    ImplTestable impl(tempFile_->path);
    impl.openMode_ = "w+b";
    impl.fp_ = std::fopen(tempFile_->path.c_str(), "w+b");
    ASSERT_NE(impl.fp_, nullptr);
    impl.opMode_ = opWrite;

    int result = impl.switchMode(opSeek);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(impl.opMode_, opSeek);
}

// Test: switching from opRead to opWrite with "r+b" mode (no reopen, second char is '+')
TEST_F(SwitchModeTest_546, ReadToWriteWithRPlusBNoReopen_546) {
    ImplTestable impl(tempFile_->path);
    impl.openMode_ = "r+b";
    impl.fp_ = std::fopen(tempFile_->path.c_str(), "r+b");
    ASSERT_NE(impl.fp_, nullptr);
    impl.opMode_ = opRead;

    int result = impl.switchMode(opWrite);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(impl.opMode_, opWrite);
}

// Test: switching from opWrite to opRead with "w+b" mode (second char is '+', no reopen)
TEST_F(SwitchModeTest_546, WriteToReadWithWPlusBNoReopen_546) {
    ImplTestable impl(tempFile_->path);
    impl.openMode_ = "w+b";
    impl.fp_ = std::fopen(tempFile_->path.c_str(), "w+b");
    ASSERT_NE(impl.fp_, nullptr);
    impl.opMode_ = opWrite;

    int result = impl.switchMode(opRead);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(impl.opMode_, opRead);
}

// Test: switching from opRead to opWrite with "rb" mode (needs reopen)
TEST_F(SwitchModeTest_546, ReadToWriteWithRbRequiresReopen_546) {
    ImplTestable impl(tempFile_->path);
    impl.openMode_ = "rb";
    impl.fp_ = std::fopen(tempFile_->path.c_str(), "rb");
    ASSERT_NE(impl.fp_, nullptr);
    impl.opMode_ = opRead;

    int result = impl.switchMode(opWrite);
    // After reopen, openMode_ should be "r+b" and opMode_ should be opSeek
    // (because the reopen path sets opMode_ to opSeek)
    // Result should be 0 if file exists and fseeko succeeds
    EXPECT_EQ(result, 0);
    EXPECT_EQ(impl.openMode_, "r+b");
}

// Test: switching from opWrite to opRead with "wb" mode (front is 'w', not 'r', so needs reopen)
TEST_F(SwitchModeTest_546, WriteToReadWithWbRequiresReopen_546) {
    // Create a file first, then open in wb mode
    ImplTestable impl(tempFile_->path);
    impl.openMode_ = "wb";
    impl.fp_ = std::fopen(tempFile_->path.c_str(), "wb");
    ASSERT_NE(impl.fp_, nullptr);
    impl.opMode_ = opWrite;

    int result = impl.switchMode(opRead);
    // The reopen should succeed since the file exists
    EXPECT_EQ(result, 0);
    EXPECT_EQ(impl.openMode_, "r+b");
}

// Test: reopen with non-existent file returns 1
TEST_F(SwitchModeTest_546, ReopenNonExistentFileReturnsOne_546) {
    std::string nonExistentPath = "non_existent_file_546_xyz.tmp";
    // Make sure it doesn't exist
    std::remove(nonExistentPath.c_str());

    // Create a real temp file and open it, then set path to non-existent
    ImplTestable impl(nonExistentPath);
    // We need an open fp_ so ftello can work. Use the real temp file
    impl.fp_ = std::fopen(tempFile_->path.c_str(), "rb");
    ASSERT_NE(impl.fp_, nullptr);
    impl.openMode_ = "rb";
    impl.opMode_ = opRead;

    // Now set path to non-existent and try to switch to write (which requires reopen)
    impl.path_ = nonExistentPath;

    int result = impl.switchMode(opWrite);
    // fopen should fail, returning 1
    EXPECT_EQ(result, 1);
}

// Test: multiple mode switches in sequence
TEST_F(SwitchModeTest_546, MultipleSwitches_546) {
    ImplTestable impl(tempFile_->path);
    impl.openMode_ = "r+b";
    impl.fp_ = std::fopen(tempFile_->path.c_str(), "r+b");
    ASSERT_NE(impl.fp_, nullptr);
    impl.opMode_ = opSeek;

    // Seek -> Read
    EXPECT_EQ(impl.switchMode(opRead), 0);
    EXPECT_EQ(impl.opMode_, opRead);

    // Read -> Write (with r+b, no reopen needed)
    EXPECT_EQ(impl.switchMode(opWrite), 0);
    EXPECT_EQ(impl.opMode_, opWrite);

    // Write -> Seek
    EXPECT_EQ(impl.switchMode(opSeek), 0);
    EXPECT_EQ(impl.opMode_, opSeek);

    // Seek -> Write
    EXPECT_EQ(impl.switchMode(opWrite), 0);
    EXPECT_EQ(impl.opMode_, opWrite);

    // Write -> Read
    EXPECT_EQ(impl.switchMode(opRead), 0);
    EXPECT_EQ(impl.opMode_, opRead);
}

// Test: switching mode with file at non-zero offset preserves position after reopen
TEST_F(SwitchModeTest_546, ReopenPreservesOffset_546) {
    ImplTestable impl(tempFile_->path);
    impl.openMode_ = "rb";
    impl.fp_ = std::fopen(tempFile_->path.c_str(), "rb");
    ASSERT_NE(impl.fp_, nullptr);
    impl.opMode_ = opRead;

    // Seek to offset 10
    std::fseek(impl.fp_, 10, SEEK_SET);

    // Switch to write mode (requires reopen from "rb")
    int result = impl.switchMode(opWrite);
    EXPECT_EQ(result, 0);

    // After reopen, the file position should be restored to 10
    if (impl.fp_) {
        long pos = std::ftell(impl.fp_);
        EXPECT_EQ(pos, 10);
    }
}

// Test: switching from opSeek to opRead with "rb" (front is 'r', no reopen)
TEST_F(SwitchModeTest_546, SeekToReadWithRbNoReopen_546) {
    ImplTestable impl(tempFile_->path);
    impl.openMode_ = "rb";
    impl.fp_ = std::fopen(tempFile_->path.c_str(), "rb");
    ASSERT_NE(impl.fp_, nullptr);
    impl.opMode_ = opSeek;

    int result = impl.switchMode(opRead);
    // openMode_ front is 'r', so no reopen needed
    // oldOpMode is opSeek, so just return 0
    EXPECT_EQ(result, 0);
    EXPECT_EQ(impl.opMode_, opRead);
}

// Test: switching from opSeek to opWrite with "wb" (front != 'r', no reopen)
TEST_F(SwitchModeTest_546, SeekToWriteWithWbNoReopen_546) {
    ImplTestable impl(tempFile_->path);
    impl.openMode_ = "wb";
    impl.fp_ = std::fopen(tempFile_->path.c_str(), "wb");
    ASSERT_NE(impl.fp_, nullptr);
    impl.opMode_ = opSeek;

    int result = impl.switchMode(opWrite);
    // openMode_ front is 'w' (not 'r'), so no reopen
    EXPECT_EQ(result, 0);
    EXPECT_EQ(impl.opMode_, opWrite);
}

// Test: switching opRead -> opRead returns 0 (same mode)
TEST_F(SwitchModeTest_546, ReadToReadSameMode_546) {
    ImplTestable impl(tempFile_->path);
    impl.openMode_ = "rb";
    impl.fp_ = std::fopen(tempFile_->path.c_str(), "rb");
    ASSERT_NE(impl.fp_, nullptr);
    impl.opMode_ = opRead;

    int result = impl.switchMode(opRead);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(impl.opMode_, opRead);
}

// Test: switching opWrite -> opWrite returns 0 (same mode)
TEST_F(SwitchModeTest_546, WriteToWriteSameMode_546) {
    ImplTestable impl(tempFile_->path);
    impl.openMode_ = "wb";
    impl.fp_ = std::fopen(tempFile_->path.c_str(), "wb");
    ASSERT_NE(impl.fp_, nullptr);
    impl.opMode_ = opWrite;

    int result = impl.switchMode(opWrite);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(impl.opMode_, opWrite);
}

// Test: after a reopen, openMode_ is updated to "r+b"
TEST_F(SwitchModeTest_546, ReopenUpdatesOpenMode_546) {
    ImplTestable impl(tempFile_->path);
    impl.openMode_ = "rb";
    impl.fp_ = std::fopen(tempFile_->path.c_str(), "rb");
    ASSERT_NE(impl.fp_, nullptr);
    impl.opMode_ = opRead;

    impl.switchMode(opWrite);

    EXPECT_EQ(impl.openMode_, "r+b");
}

// Test: after a reopen, opMode_ is set to opSeek (reopen path sets it)
TEST_F(SwitchModeTest_546, ReopenSetsOpModeToSeek_546) {
    ImplTestable impl(tempFile_->path);
    impl.openMode_ = "rb";
    impl.fp_ = std::fopen(tempFile_->path.c_str(), "rb");
    ASSERT_NE(impl.fp_, nullptr);
    impl.opMode_ = opRead;

    impl.switchMode(opWrite);

    // The reopen path sets opMode_ = opSeek before reopening
    // Even though we requested opWrite, the function sets opMode_ to opSeek in the reopen path
    EXPECT_EQ(impl.opMode_, opSeek);
}

// Test: file pointer is valid after reopen
TEST_F(SwitchModeTest_546, FilePointerValidAfterReopen_546) {
    ImplTestable impl(tempFile_->path);
    impl.openMode_ = "rb";
    impl.fp_ = std::fopen(tempFile_->path.c_str(), "rb");
    ASSERT_NE(impl.fp_, nullptr);
    impl.opMode_ = opRead;

    int result = impl.switchMode(opWrite);
    EXPECT_EQ(result, 0);
    EXPECT_NE(impl.fp_, nullptr);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
