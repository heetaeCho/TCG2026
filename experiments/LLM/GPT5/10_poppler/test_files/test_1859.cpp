#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <png.h>

namespace ImageEmbeddingUtils {

    // The class under test
    class PngEmbedder {
    public:
        class LibpngInputStream {
        private:
            std::vector<char> m_fileContent;
            char * m_iterator;
            png_size_t m_remainingSize;
        
        public:
            explicit LibpngInputStream(std::vector<char> &&fileContent) 
                : m_fileContent(std::move(fileContent)), m_iterator(m_fileContent.data()), m_remainingSize(m_fileContent.size()) {}

            LibpngInputStream() = delete;
            LibpngInputStream(const LibpngInputStream &) = delete;
            LibpngInputStream &operator=(const LibpngInputStream &) = delete;
            ~LibpngInputStream() = default;

            void read(png_bytep out, const png_size_t size) {
                if (size > m_remainingSize) {
                    // If the read size exceeds remaining size, set it to the remaining size
                    size = m_remainingSize;
                }

                std::memcpy(out, m_iterator, size);
                m_iterator += size;
                m_remainingSize -= size;
            }

            static void readCallback(png_structp png, png_bytep out, png_size_t size) {
                auto *stream = (LibpngInputStream *)png_get_io_ptr(png);
                if (stream) {
                    stream->read(out, size);
                }
            }
        };
    };

} // namespace ImageEmbeddingUtils


// TEST CASES

// Normal Operation Test
TEST_F(PngEmbedder_LibpngInputStream_1859, ReadCallback_ValidData_1859) {
    std::vector<char> fileContent = {'a', 'b', 'c', 'd', 'e'};
    ImageEmbeddingUtils::LibpngInputStream stream(std::move(fileContent));
    png_structp png = nullptr;  // Simulate the PNG structure, since we don't need real png data for this test
    png_bytep out = new png_byte[3]; // Output buffer for reading

    // Setting the callback for the read function
    png_set_read_fn(png, &stream, &ImageEmbeddingUtils::LibpngInputStream::readCallback);

    // Simulate a read operation
    png_read_data(png, out, 3);

    // Check if the data read matches what is expected
    EXPECT_EQ(out[0], 'a');
    EXPECT_EQ(out[1], 'b');
    EXPECT_EQ(out[2], 'c');

    delete[] out;
}

// Boundary Condition Test (Read exactly the available content)
TEST_F(PngEmbedder_LibpngInputStream_1859, ReadCallback_FullData_1859) {
    std::vector<char> fileContent = {'a', 'b', 'c', 'd', 'e'};
    ImageEmbeddingUtils::LibpngInputStream stream(std::move(fileContent));
    png_structp png = nullptr;
    png_bytep out = new png_byte[5];

    // Simulate the full read operation
    png_set_read_fn(png, &stream, &ImageEmbeddingUtils::LibpngInputStream::readCallback);
    png_read_data(png, out, 5);

    // Check if the data read matches the entire content
    EXPECT_EQ(out[0], 'a');
    EXPECT_EQ(out[1], 'b');
    EXPECT_EQ(out[2], 'c');
    EXPECT_EQ(out[3], 'd');
    EXPECT_EQ(out[4], 'e');

    delete[] out;
}

// Error Case (Attempt to read more data than available)
TEST_F(PngEmbedder_LibpngInputStream_1859, ReadCallback_Overflow_1859) {
    std::vector<char> fileContent = {'a', 'b', 'c'};
    ImageEmbeddingUtils::LibpngInputStream stream(std::move(fileContent));
    png_structp png = nullptr;
    png_bytep out = new png_byte[5];  // Trying to read 5 bytes while only 3 are available

    // Simulate a read operation with overflow
    png_set_read_fn(png, &stream, &ImageEmbeddingUtils::LibpngInputStream::readCallback);
    png_read_data(png, out, 5);

    // Check that only 3 bytes were read, the last two should not be overwritten
    EXPECT_EQ(out[0], 'a');
    EXPECT_EQ(out[1], 'b');
    EXPECT_EQ(out[2], 'c');
    EXPECT_EQ(out[3], 0);  // These should remain 0 because there wasn't enough data
    EXPECT_EQ(out[4], 0);  

    delete[] out;
}