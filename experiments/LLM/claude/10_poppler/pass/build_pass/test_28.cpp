#include <gtest/gtest.h>
#include "ImgWriter.h"

// Since ImgWriter is abstract (has pure virtual methods), we need a concrete subclass for testing
// the provided non-pure virtual method supportCMYK().
// We create a minimal concrete subclass that implements the pure virtual methods.
class ConcreteImgWriter : public ImgWriter {
public:
    ConcreteImgWriter() = default;
    ~ConcreteImgWriter() override = default;

    bool init(FILE *f, int width, int height, double hDPI, double vDPI) override {
        return true;
    }

    bool writePointers(unsigned char **rowPointers, int rowCount) override {
        return true;
    }

    bool writeRow(unsigned char **row) override {
        return true;
    }

    bool close() override {
        return true;
    }
};

// A subclass that overrides supportCMYK to return true
class CMYKSupportingWriter : public ConcreteImgWriter {
public:
    bool supportCMYK() override {
        return true;
    }
};

class ImgWriterTest_28 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that the default implementation of supportCMYK returns false
TEST_F(ImgWriterTest_28, DefaultSupportCMYKReturnsFalse_28) {
    ConcreteImgWriter writer;
    EXPECT_FALSE(writer.supportCMYK());
}

// Test that a derived class can override supportCMYK to return true
TEST_F(ImgWriterTest_28, OverriddenSupportCMYKReturnsTrue_28) {
    CMYKSupportingWriter writer;
    EXPECT_TRUE(writer.supportCMYK());
}

// Test supportCMYK through a base class pointer (polymorphism) - default case
TEST_F(ImgWriterTest_28, SupportCMYKViaBasePointerDefaultFalse_28) {
    ConcreteImgWriter concreteWriter;
    ImgWriter *writer = &concreteWriter;
    EXPECT_FALSE(writer->supportCMYK());
}

// Test supportCMYK through a base class pointer (polymorphism) - overridden case
TEST_F(ImgWriterTest_28, SupportCMYKViaBasePointerOverriddenTrue_28) {
    CMYKSupportingWriter cmykWriter;
    ImgWriter *writer = &cmykWriter;
    EXPECT_TRUE(writer->supportCMYK());
}

// Test that calling supportCMYK multiple times returns consistent results
TEST_F(ImgWriterTest_28, SupportCMYKConsistentAcrossMultipleCalls_28) {
    ConcreteImgWriter writer;
    EXPECT_FALSE(writer.supportCMYK());
    EXPECT_FALSE(writer.supportCMYK());
    EXPECT_FALSE(writer.supportCMYK());
}

// Test that the concrete subclass can be instantiated and destroyed without issues
TEST_F(ImgWriterTest_28, ConcreteWriterInstantiationAndDestruction_28) {
    ConcreteImgWriter *writer = new ConcreteImgWriter();
    EXPECT_FALSE(writer->supportCMYK());
    delete writer;
}

// Test init method on the concrete writer
TEST_F(ImgWriterTest_28, ConcreteWriterInitReturnsTrue_28) {
    ConcreteImgWriter writer;
    // We pass nullptr as FILE* since our concrete implementation doesn't use it
    EXPECT_TRUE(writer.init(nullptr, 100, 100, 72.0, 72.0));
}

// Test close method on the concrete writer
TEST_F(ImgWriterTest_28, ConcreteWriterCloseReturnsTrue_28) {
    ConcreteImgWriter writer;
    EXPECT_TRUE(writer.close());
}

// Test writeRow on the concrete writer
TEST_F(ImgWriterTest_28, ConcreteWriterWriteRowReturnsTrue_28) {
    ConcreteImgWriter writer;
    unsigned char data[] = {0, 1, 2, 3};
    unsigned char *row = data;
    EXPECT_TRUE(writer.writeRow(&row));
}

// Test writePointers on the concrete writer
TEST_F(ImgWriterTest_28, ConcreteWriterWritePointersReturnsTrue_28) {
    ConcreteImgWriter writer;
    unsigned char data[] = {0, 1, 2, 3};
    unsigned char *rows[] = {data};
    EXPECT_TRUE(writer.writePointers(rows, 1));
}
