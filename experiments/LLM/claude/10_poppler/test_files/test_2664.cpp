#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdio>
#include <cstring>
#include <memory>
#include <string>

#include "Object.h"
#include "Dict.h"
#include "UnicodeMap.h"
#include "GooString.h"

// We need to include the source to access the static function
// In practice, the static function would need to be made accessible for testing
// For this test, we assume the function is accessible (e.g., via a test header or
// by including the .cc file in a controlled manner)

// Forward declaration - assuming the function is made accessible for testing
extern void printInfoString(Dict *infoDict, const char *key, const char *text, const UnicodeMap *uMap);

namespace {

// Helper to capture stdout output
class StdoutCapture {
public:
    StdoutCapture() : captured_("") {
        tmpfile_ = std::tmpfile();
        if (tmpfile_) {
            old_stdout_ = stdout;
            // Redirect stdout to our temp file
            fflush(stdout);
            saved_fd_ = dup(fileno(stdout));
            dup2(fileno(tmpfile_), fileno(stdout));
        }
    }

    ~StdoutCapture() {
        if (tmpfile_) {
            dup2(saved_fd_, fileno(stdout));
            close(saved_fd_);
            fclose(tmpfile_);
        }
    }

    std::string getOutput() {
        fflush(stdout);
        rewind(tmpfile_);
        char buf[4096] = {};
        size_t n = fread(buf, 1, sizeof(buf) - 1, tmpfile_);
        buf[n] = '\0';
        return std::string(buf, n);
    }

private:
    FILE *tmpfile_ = nullptr;
    FILE *old_stdout_ = nullptr;
    int saved_fd_ = -1;
    std::string captured_;
};

class PrintInfoStringTest_2664 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a Dict with nullptr XRef - may need a valid XRef depending on implementation
        dict_ = new Dict(static_cast<XRef*>(nullptr));
        
        // Try to parse a basic UnicodeMap (Latin1 or similar)
        uMap_ = UnicodeMap::parse("Latin1");
    }

    void TearDown() override {
        delete dict_;
    }

    Dict *dict_ = nullptr;
    std::unique_ptr<UnicodeMap> uMap_;
};

// Test that when the key exists and maps to a string, text and string value are printed
TEST_F(PrintInfoStringTest_2664, PrintsStringValueWhenKeyExists_2664) {
    // Add a string entry to the dict
    dict_->add("Title", Object(std::make_unique<GooString>("Hello World")));

    FILE *tmp = std::tmpfile();
    ASSERT_NE(tmp, nullptr);

    // Save and redirect stdout
    fflush(stdout);
    int saved = dup(fileno(stdout));
    dup2(fileno(tmp), fileno(stdout));

    printInfoString(dict_, "Title", "Title:          ", uMap_.get());

    fflush(stdout);
    dup2(saved, fileno(stdout));
    close(saved);

    // Read what was written
    rewind(tmp);
    char buf[4096] = {};
    size_t n = fread(buf, 1, sizeof(buf) - 1, tmp);
    buf[n] = '\0';
    fclose(tmp);

    std::string output(buf, n);
    // Should start with the text prefix
    EXPECT_TRUE(output.find("Title:          ") == 0)
        << "Output was: " << output;
    // Should contain the string value
    EXPECT_TRUE(output.find("Hello World") != std::string::npos)
        << "Output was: " << output;
    // Should end with a newline
    EXPECT_EQ(output.back(), '\n');
}

// Test that when the key does not exist, nothing is printed
TEST_F(PrintInfoStringTest_2664, PrintsNothingWhenKeyDoesNotExist_2664) {
    // Dict is empty, "NonExistent" key doesn't exist

    FILE *tmp = std::tmpfile();
    ASSERT_NE(tmp, nullptr);

    fflush(stdout);
    int saved = dup(fileno(stdout));
    dup2(fileno(tmp), fileno(stdout));

    printInfoString(dict_, "NonExistent", "SomeText: ", uMap_.get());

    fflush(stdout);
    dup2(saved, fileno(stdout));
    close(saved);

    rewind(tmp);
    char buf[4096] = {};
    size_t n = fread(buf, 1, sizeof(buf) - 1, tmp);
    fclose(tmp);

    EXPECT_EQ(n, 0u) << "Expected no output when key doesn't exist";
}

// Test that when the key exists but is not a string (e.g., an integer), nothing is printed
TEST_F(PrintInfoStringTest_2664, PrintsNothingWhenValueIsNotString_2664) {
    // Add a non-string entry
    dict_->add("Count", Object(42));

    FILE *tmp = std::tmpfile();
    ASSERT_NE(tmp, nullptr);

    fflush(stdout);
    int saved = dup(fileno(stdout));
    dup2(fileno(tmp), fileno(stdout));

    printInfoString(dict_, "Count", "Count: ", uMap_.get());

    fflush(stdout);
    dup2(saved, fileno(stdout));
    close(saved);

    rewind(tmp);
    char buf[4096] = {};
    size_t n = fread(buf, 1, sizeof(buf) - 1, tmp);
    fclose(tmp);

    EXPECT_EQ(n, 0u) << "Expected no output when value is not a string";
}

// Test that when the key exists but maps to a boolean, nothing is printed
TEST_F(PrintInfoStringTest_2664, PrintsNothingWhenValueIsBoolean_2664) {
    dict_->add("Flag", Object(true));

    FILE *tmp = std::tmpfile();
    ASSERT_NE(tmp, nullptr);

    fflush(stdout);
    int saved = dup(fileno(stdout));
    dup2(fileno(tmp), fileno(stdout));

    printInfoString(dict_, "Flag", "Flag: ", uMap_.get());

    fflush(stdout);
    dup2(saved, fileno(stdout));
    close(saved);

    rewind(tmp);
    char buf[4096] = {};
    size_t n = fread(buf, 1, sizeof(buf) - 1, tmp);
    fclose(tmp);

    EXPECT_EQ(n, 0u) << "Expected no output when value is a boolean";
}

// Test that when the key maps to a null object, nothing is printed
TEST_F(PrintInfoStringTest_2664, PrintsNothingWhenValueIsNull_2664) {
    dict_->add("NullKey", Object::null());

    FILE *tmp = std::tmpfile();
    ASSERT_NE(tmp, nullptr);

    fflush(stdout);
    int saved = dup(fileno(stdout));
    dup2(fileno(tmp), fileno(stdout));

    printInfoString(dict_, "NullKey", "Null: ", uMap_.get());

    fflush(stdout);
    dup2(saved, fileno(stdout));
    close(saved);

    rewind(tmp);
    char buf[4096] = {};
    size_t n = fread(buf, 1, sizeof(buf) - 1, tmp);
    fclose(tmp);

    EXPECT_EQ(n, 0u) << "Expected no output when value is null";
}

// Test with an empty string value - should still print text prefix and newline
TEST_F(PrintInfoStringTest_2664, PrintsTextAndNewlineForEmptyString_2664) {
    dict_->add("Empty", Object(std::make_unique<GooString>("")));

    FILE *tmp = std::tmpfile();
    ASSERT_NE(tmp, nullptr);

    fflush(stdout);
    int saved = dup(fileno(stdout));
    dup2(fileno(tmp), fileno(stdout));

    printInfoString(dict_, "Empty", "Empty: ", uMap_.get());

    fflush(stdout);
    dup2(saved, fileno(stdout));
    close(saved);

    rewind(tmp);
    char buf[4096] = {};
    size_t n = fread(buf, 1, sizeof(buf) - 1, tmp);
    buf[n] = '\0';
    fclose(tmp);

    std::string output(buf, n);
    // Should at least contain the text prefix and end with newline
    EXPECT_TRUE(output.find("Empty: ") == 0)
        << "Output was: " << output;
    EXPECT_EQ(output.back(), '\n');
}

// Test with empty text prefix
TEST_F(PrintInfoStringTest_2664, WorksWithEmptyTextPrefix_2664) {
    dict_->add("Author", Object(std::make_unique<GooString>("John Doe")));

    FILE *tmp = std::tmpfile();
    ASSERT_NE(tmp, nullptr);

    fflush(stdout);
    int saved = dup(fileno(stdout));
    dup2(fileno(tmp), fileno(stdout));

    printInfoString(dict_, "Author", "", uMap_.get());

    fflush(stdout);
    dup2(saved, fileno(stdout));
    close(saved);

    rewind(tmp);
    char buf[4096] = {};
    size_t n = fread(buf, 1, sizeof(buf) - 1, tmp);
    buf[n] = '\0';
    fclose(tmp);

    std::string output(buf, n);
    // Should contain the string value and end with newline
    EXPECT_TRUE(output.find("John Doe") != std::string::npos)
        << "Output was: " << output;
    EXPECT_EQ(output.back(), '\n');
}

// Test with a real-type value - should print nothing
TEST_F(PrintInfoStringTest_2664, PrintsNothingWhenValueIsReal_2664) {
    dict_->add("Version", Object(1.5));

    FILE *tmp = std::tmpfile();
    ASSERT_NE(tmp, nullptr);

    fflush(stdout);
    int saved = dup(fileno(stdout));
    dup2(fileno(tmp), fileno(stdout));

    printInfoString(dict_, "Version", "Version: ", uMap_.get());

    fflush(stdout);
    dup2(saved, fileno(stdout));
    close(saved);

    rewind(tmp);
    char buf[4096] = {};
    size_t n = fread(buf, 1, sizeof(buf) - 1, tmp);
    fclose(tmp);

    EXPECT_EQ(n, 0u) << "Expected no output when value is a real number";
}

// Test multiple calls with different keys
TEST_F(PrintInfoStringTest_2664, MultipleCallsPrintCorrectly_2664) {
    dict_->add("Title", Object(std::make_unique<GooString>("My Title")));
    dict_->add("Author", Object(std::make_unique<GooString>("An Author")));
    dict_->add("PageCount", Object(100));

    FILE *tmp = std::tmpfile();
    ASSERT_NE(tmp, nullptr);

    fflush(stdout);
    int saved = dup(fileno(stdout));
    dup2(fileno(tmp), fileno(stdout));

    printInfoString(dict_, "Title", "Title: ", uMap_.get());
    printInfoString(dict_, "Author", "Author: ", uMap_.get());
    printInfoString(dict_, "PageCount", "Pages: ", uMap_.get());

    fflush(stdout);
    dup2(saved, fileno(stdout));
    close(saved);

    rewind(tmp);
    char buf[8192] = {};
    size_t n = fread(buf, 1, sizeof(buf) - 1, tmp);
    buf[n] = '\0';
    fclose(tmp);

    std::string output(buf, n);
    // Title and Author should be printed, PageCount should not (it's an int)
    EXPECT_TRUE(output.find("Title: ") != std::string::npos)
        << "Output was: " << output;
    EXPECT_TRUE(output.find("Author: ") != std::string::npos)
        << "Output was: " << output;
    EXPECT_TRUE(output.find("Pages: ") == std::string::npos)
        << "Pages should not appear in output. Output was: " << output;
}

} // namespace
