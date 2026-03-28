#include <gtest/gtest.h>

// Reproduce the minimal interface from the provided code
#define jbig2HuffmanOOB 0xfffffffe
#define jbig2HuffmanLOW 0xfffffffd
#define jbig2HuffmanEOT 0xffffffff

// Forward declaration of segment type enum (inferred from interface)
enum JBIG2SegmentType
{
    jbig2SegBitmap,
    jbig2SegSymbolDict,
    jbig2SegPatternDict,
    jbig2SegCodeTable
};

class JBIG2Segment
{
public:
    explicit JBIG2Segment(unsigned int segNumA)
    {
        segNum = segNumA;
    }

    JBIG2Segment(const JBIG2Segment &) = delete;
    JBIG2Segment &operator=(const JBIG2Segment &) = delete;

    virtual ~JBIG2Segment() { }

    virtual JBIG2SegmentType getType() { return jbig2SegBitmap; }

    void setSegNum(unsigned int segNumA) { segNum = segNumA; }

    unsigned int getSegNum() const { return segNum; }

private:
    unsigned int segNum;
};

// -----------------------------------------------------------
// Test fixture
// -----------------------------------------------------------
class JBIG2SegmentTest_2786 : public ::testing::Test
{
protected:
    void SetUp() override { }
    void TearDown() override { }
};

// -----------------------------------------------------------
// Tests for macro / constant definitions
// -----------------------------------------------------------
TEST_F(JBIG2SegmentTest_2786, HuffmanOOBValue_2786)
{
    EXPECT_EQ(jbig2HuffmanOOB, 0xfffffffeu);
}

TEST_F(JBIG2SegmentTest_2786, HuffmanLOWValue_2786)
{
    EXPECT_EQ(jbig2HuffmanLOW, 0xfffffffdu);
}

TEST_F(JBIG2SegmentTest_2786, HuffmanEOTValue_2786)
{
    EXPECT_EQ(jbig2HuffmanEOT, 0xffffffffu);
}

// -----------------------------------------------------------
// Constructor tests
// -----------------------------------------------------------
TEST_F(JBIG2SegmentTest_2786, ConstructorSetsSegNum_2786)
{
    JBIG2Segment seg(42);
    EXPECT_EQ(seg.getSegNum(), 42u);
}

TEST_F(JBIG2SegmentTest_2786, ConstructorWithZero_2786)
{
    JBIG2Segment seg(0);
    EXPECT_EQ(seg.getSegNum(), 0u);
}

TEST_F(JBIG2SegmentTest_2786, ConstructorWithMaxUint_2786)
{
    unsigned int maxVal = 0xFFFFFFFF;
    JBIG2Segment seg(maxVal);
    EXPECT_EQ(seg.getSegNum(), maxVal);
}

TEST_F(JBIG2SegmentTest_2786, ConstructorWithLargeValue_2786)
{
    JBIG2Segment seg(999999999);
    EXPECT_EQ(seg.getSegNum(), 999999999u);
}

// -----------------------------------------------------------
// setSegNum / getSegNum tests
// -----------------------------------------------------------
TEST_F(JBIG2SegmentTest_2786, SetSegNumChangesValue_2786)
{
    JBIG2Segment seg(1);
    seg.setSegNum(100);
    EXPECT_EQ(seg.getSegNum(), 100u);
}

TEST_F(JBIG2SegmentTest_2786, SetSegNumToZero_2786)
{
    JBIG2Segment seg(55);
    seg.setSegNum(0);
    EXPECT_EQ(seg.getSegNum(), 0u);
}

TEST_F(JBIG2SegmentTest_2786, SetSegNumToMaxUint_2786)
{
    JBIG2Segment seg(0);
    seg.setSegNum(0xFFFFFFFF);
    EXPECT_EQ(seg.getSegNum(), 0xFFFFFFFFu);
}

TEST_F(JBIG2SegmentTest_2786, SetSegNumMultipleTimes_2786)
{
    JBIG2Segment seg(0);
    seg.setSegNum(10);
    EXPECT_EQ(seg.getSegNum(), 10u);
    seg.setSegNum(20);
    EXPECT_EQ(seg.getSegNum(), 20u);
    seg.setSegNum(30);
    EXPECT_EQ(seg.getSegNum(), 30u);
}

TEST_F(JBIG2SegmentTest_2786, SetSegNumSameValue_2786)
{
    JBIG2Segment seg(77);
    seg.setSegNum(77);
    EXPECT_EQ(seg.getSegNum(), 77u);
}

// -----------------------------------------------------------
// getSegNum const correctness test
// -----------------------------------------------------------
TEST_F(JBIG2SegmentTest_2786, GetSegNumIsConst_2786)
{
    const JBIG2Segment seg(123);
    // getSegNum() should be callable on a const object
    EXPECT_EQ(seg.getSegNum(), 123u);
}

// -----------------------------------------------------------
// Boundary value tests
// -----------------------------------------------------------
TEST_F(JBIG2SegmentTest_2786, SegNumBoundaryOne_2786)
{
    JBIG2Segment seg(1);
    EXPECT_EQ(seg.getSegNum(), 1u);
}

TEST_F(JBIG2SegmentTest_2786, SegNumBoundaryMaxMinusOne_2786)
{
    JBIG2Segment seg(0xFFFFFFFE);
    EXPECT_EQ(seg.getSegNum(), 0xFFFFFFFEu);
}

// -----------------------------------------------------------
// Virtual destructor test (ensure no crash on delete through base pointer)
// -----------------------------------------------------------
TEST_F(JBIG2SegmentTest_2786, VirtualDestructorNoCrash_2786)
{
    JBIG2Segment *seg = new JBIG2Segment(5);
    EXPECT_EQ(seg->getSegNum(), 5u);
    delete seg; // Should not crash due to virtual destructor
}

// -----------------------------------------------------------
// Multiple instances are independent
// -----------------------------------------------------------
TEST_F(JBIG2SegmentTest_2786, MultipleInstancesIndependent_2786)
{
    JBIG2Segment seg1(10);
    JBIG2Segment seg2(20);
    JBIG2Segment seg3(30);

    EXPECT_EQ(seg1.getSegNum(), 10u);
    EXPECT_EQ(seg2.getSegNum(), 20u);
    EXPECT_EQ(seg3.getSegNum(), 30u);

    seg1.setSegNum(99);
    EXPECT_EQ(seg1.getSegNum(), 99u);
    EXPECT_EQ(seg2.getSegNum(), 20u);
    EXPECT_EQ(seg3.getSegNum(), 30u);
}

// -----------------------------------------------------------
// Huffman constants are distinct
// -----------------------------------------------------------
TEST_F(JBIG2SegmentTest_2786, HuffmanConstantsAreDistinct_2786)
{
    EXPECT_NE(jbig2HuffmanOOB, jbig2HuffmanLOW);
    EXPECT_NE(jbig2HuffmanOOB, jbig2HuffmanEOT);
    EXPECT_NE(jbig2HuffmanLOW, jbig2HuffmanEOT);
}

// -----------------------------------------------------------
// Huffman constants ordering
// -----------------------------------------------------------
TEST_F(JBIG2SegmentTest_2786, HuffmanConstantsOrdering_2786)
{
    EXPECT_LT(jbig2HuffmanLOW, jbig2HuffmanOOB);
    EXPECT_LT(jbig2HuffmanOOB, jbig2HuffmanEOT);
}
