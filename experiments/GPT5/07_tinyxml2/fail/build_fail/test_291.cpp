// File: ./TestProjects/tinyxml2/xmlprinter_write_test_291.cpp

#include <gtest/gtest.h>

#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

#include "tinyxml2.h"

namespace tinyxml2 {

// Expose protected XMLPrinter::Write(const char*, size_t) for testing.
class XMLPrinterWriteProbe_291 : public XMLPrinter {
public:
    explicit XMLPrinterWriteProbe_291(FILE* file)
        : XMLPrinter(file, /*compact=*/false, /*depth=*/0, /*aposInAttributes=*/tinyxml2::XMLPrinter::EscapeAposCharsInAttributes::NO) {}

    void WriteBytes(const char* data, size_t size) { Write(data, size); }
};

class XMLPrinterWriteTest_291 : public ::testing::Test {
protected:
    static std::string ReadAllFromFile(FILE* fp) {
        std::string out;
        std::rewind(fp);

        char buf[256];
        while (true) {
            const size_t n = std::fread(buf, 1, sizeof(buf), fp);
            if (n > 0) out.append(buf, n);
            if (n < sizeof(buf)) break; // EOF or error
        }
        return out;
    }
};

// Normal operation: when constructed with nullptr FILE*, Write should append to internal buffer.
TEST_F(XMLPrinterWriteTest_291, WriteToBuffer_AppendsAndNullTerminates_291) {
    XMLPrinterWriteProbe_291 printer(nullptr);

    const char* a = "Hello";
    printer.WriteBytes(a, std::strlen(a));

    ASSERT_NE(printer.CStr(), nullptr);
    EXPECT_EQ(std::string(printer.CStr()), "Hello");
    EXPECT_EQ(printer.CStrSize(), std::strlen("Hello"));
}

// Normal operation: multiple calls should append in buffer mode.
TEST_F(XMLPrinterWriteTest_291, WriteToBuffer_MultipleWritesAppend_291) {
    XMLPrinterWriteProbe_291 printer(nullptr);

    printer.WriteBytes("ABC", 3);
    printer.WriteBytes("DEF", 3);
    printer.WriteBytes("!", 1);

    EXPECT_EQ(std::string(printer.CStr()), "ABCDEF!");
    EXPECT_EQ(printer.CStrSize(), std::strlen("ABCDEF!"));
}

// Boundary: size==0 should be a no-op (no visible change) in buffer mode.
TEST_F(XMLPrinterWriteTest_291, WriteToBuffer_SizeZeroDoesNotChange_291) {
    XMLPrinterWriteProbe_291 printer(nullptr);

    printer.WriteBytes("X", 1);
    const std::string before = std::string(printer.CStr());
    const size_t beforeSize = printer.CStrSize();

    // size==0 should not add anything.
    printer.WriteBytes("SHOULD_NOT_APPEAR", 0);

    EXPECT_EQ(std::string(printer.CStr()), before);
    EXPECT_EQ(printer.CStrSize(), beforeSize);
}

// Boundary: allow embedded NUL bytes; buffer content/size should reflect exact bytes written.
TEST_F(XMLPrinterWriteTest_291, WriteToBuffer_AllowsEmbeddedNullBytes_291) {
    XMLPrinterWriteProbe_291 printer(nullptr);

    const char bytes[] = {'a', 'b', '\0', 'c', 'd'};
    printer.WriteBytes(bytes, sizeof(bytes));

    // Use CStrSize() to reconstruct full payload including embedded NUL.
    ASSERT_NE(printer.CStr(), nullptr);
    ASSERT_EQ(printer.CStrSize(), sizeof(bytes));

    std::string reconstructed(printer.CStr(), printer.CStrSize());
    EXPECT_EQ(reconstructed.size(), sizeof(bytes));
    EXPECT_EQ(0, std::memcmp(reconstructed.data(), bytes, sizeof(bytes)));

    // CStr() is a C-string, so printing as std::string(printer.CStr()) would truncate at '\0' —
    // we intentionally avoid that here.
}

// Normal operation: when constructed with a valid FILE*, Write should write bytes to that file.
TEST_F(XMLPrinterWriteTest_291, WriteToFile_WritesExactBytes_291) {
    FILE* fp = std::tmpfile();
    ASSERT_NE(fp, nullptr);

    XMLPrinterWriteProbe_291 printer(fp);

    const char* msg = "file-output";
    printer.WriteBytes(msg, std::strlen(msg));

    const std::string fileContent = ReadAllFromFile(fp);
    EXPECT_EQ(fileContent, "file-output");

    std::fclose(fp);
}

// Normal operation: multiple calls should append in file mode.
TEST_F(XMLPrinterWriteTest_291, WriteToFile_MultipleWritesAppend_291) {
    FILE* fp = std::tmpfile();
    ASSERT_NE(fp, nullptr);

    XMLPrinterWriteProbe_291 printer(fp);

    printer.WriteBytes("123", 3);
    printer.WriteBytes("456", 3);
    printer.WriteBytes("789", 3);

    const std::string fileContent = ReadAllFromFile(fp);
    EXPECT_EQ(fileContent, "123456789");

    std::fclose(fp);
}

// Boundary: size==0 should not change the file.
TEST_F(XMLPrinterWriteTest_291, WriteToFile_SizeZeroDoesNotChange_291) {
    FILE* fp = std::tmpfile();
    ASSERT_NE(fp, nullptr);

    XMLPrinterWriteProbe_291 printer(fp);

    printer.WriteBytes("A", 1);
    const std::string before = ReadAllFromFile(fp);

    printer.WriteBytes("IGNORED", 0);
    const std::string after = ReadAllFromFile(fp);

    EXPECT_EQ(before, after);
    EXPECT_EQ(after, "A");

    std::fclose(fp);
}

// Boundary: embedded NUL bytes should be written to file exactly (binary-safe).
TEST_F(XMLPrinterWriteTest_291, WriteToFile_AllowsEmbeddedNullBytes_291) {
    FILE* fp = std::tmpfile();
    ASSERT_NE(fp, nullptr);

    XMLPrinterWriteProbe_291 printer(fp);

    const char bytes[] = {'x', '\0', 'y', '\0', 'z'};
    printer.WriteBytes(bytes, sizeof(bytes));

    const std::string fileContent = ReadAllFromFile(fp);
    ASSERT_EQ(fileContent.size(), sizeof(bytes));
    EXPECT_EQ(0, std::memcmp(fileContent.data(), bytes, sizeof(bytes)));

    std::fclose(fp);
}

// Error/exceptional (observable): nullptr data with size==0 should not require dereferencing.
// This test avoids undefined behavior by keeping size==0.
TEST_F(XMLPrinterWriteTest_291, Write_NullDataWithZeroSize_DoesNotCrash_291) {
    XMLPrinterWriteProbe_291 printer(nullptr);

    // If implementation treats (nullptr, 0) as a no-op, this should be safe.
    ASSERT_NO_FATAL_FAILURE(printer.WriteBytes(nullptr, 0));
}

}  // namespace tinyxml2
