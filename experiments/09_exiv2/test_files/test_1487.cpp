#include <gtest/gtest.h>

#include <gmock/gmock.h>



namespace Exiv2 { namespace Internal {



class PentaxMnHeader {

public:

    bool read(const byte* pData, size_t size, ByteOrder) {

        if (!pData || size < sizeOfSignature()) return false;

        header_.alloc(sizeOfSignature());

        std::copy_n(pData, header_.size(), header_.begin());

        return header_.size() >= sizeOfSignature() && 0 == header_.cmpBytes(0, signature_, 3);

    }



private:

    // Mocking the internal details of the class

    struct Array {

        void alloc(size_t) {}

        size_t size() const { return 3; }

        std::vector<byte>::iterator begin() { return data.begin(); }

        int cmpBytes(size_t, const byte*, size_t) const { return 0; }



    private:

        std::vector<byte> data;

    };



    Array header_;

    static constexpr byte signature_[3] = { 'P', 'E', 'N' };

    size_t sizeOfSignature() const { return sizeof(signature_); }

};



} } // namespace Exiv2::Internal



using namespace Exiv2::Internal;



class PentaxMnHeaderTest_1487 : public ::testing::Test {

protected:

    PentaxMnHeader header;

    byte testData[3] = {'P', 'E', 'N'};

};



TEST_F(PentaxMnHeaderTest_1487, ReadValidData_1487) {

    EXPECT_TRUE(header.read(testData, 3, littleEndian));

}



TEST_F(PentaxMnHeaderTest_1487, ReadInvalidSignature_1487) {

    byte invalidData[3] = {'I', 'N', 'V'};

    EXPECT_FALSE(header.read(invalidData, 3, littleEndian));

}



TEST_F(PentaxMnHeaderTest_1487, ReadNullPointer_1487) {

    EXPECT_FALSE(header.read(nullptr, 3, littleEndian));

}



TEST_F(PentaxMnHeaderTest_1487, ReadInsufficientSize_1487) {

    EXPECT_FALSE(header.read(testData, 2, littleEndian));

}



TEST_F(PentaxMnHeaderTest_1487, ReadExactSignatureLength_1487) {

    EXPECT_TRUE(header.read(testData, 3, littleEndian));

}
