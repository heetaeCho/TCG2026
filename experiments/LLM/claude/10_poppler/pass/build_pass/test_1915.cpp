#include <gtest/gtest.h>

// Forward declarations and necessary definitions from the codebase
enum PSObjectType { psBool = 0, psInt = 1, psReal = 2, psOperator = 3, psBlock = 4 };

const int psStackSize = 100;

struct PSObject {
    PSObjectType type;
    union {
        bool booln;
        int intg;
        double real;
    };
};

class PSStack {
public:
    PSStack() { sp = psStackSize; }

    void copy(int n);
    void roll(int n, int j);
    void clear() { sp = psStackSize; }

    void pushBool(bool booln) {
        if (checkOverflow()) {
            stack[--sp].type = psBool;
            stack[sp].booln = booln;
        }
    }

    void pushInt(int intg) {
        if (checkOverflow()) {
            stack[--sp].type = psInt;
            stack[sp].intg = intg;
        }
    }

    void pushReal(double real) {
        if (checkOverflow()) {
            stack[--sp].type = psReal;
            stack[sp].real = real;
        }
    }

    bool popBool() {
        if (checkUnderflow() && checkType(psBool, psBool)) {
            return stack[sp++].booln;
        }
        return false;
    }

    int popInt() {
        if (checkUnderflow() && checkType(psInt, psInt)) {
            return stack[sp++].intg;
        }
        return 0;
    }

    double popNum() {
        if (checkUnderflow() && checkType(psInt, psReal)) {
            double ret = (stack[sp].type == psInt) ? (double)stack[sp].intg : stack[sp].real;
            ++sp;
            return ret;
        }
        return 0;
    }

    bool empty() const { return sp == psStackSize; }

    bool topIsInt() { return sp < psStackSize && stack[sp].type == psInt; }

    bool topTwoAreInts() {
        return sp < psStackSize - 1 && stack[sp].type == psInt && stack[sp + 1].type == psInt;
    }

    bool topIsReal() { return sp < psStackSize && stack[sp].type == psReal; }

    bool topTwoAreNums() {
        return sp < psStackSize - 1 &&
               (stack[sp].type == psInt || stack[sp].type == psReal) &&
               (stack[sp + 1].type == psInt || stack[sp + 1].type == psReal);
    }

    void index(int i) {
        if (!checkOverflow()) {
            return;
        }
        if (sp + i >= psStackSize) {
            return;
        }
        --sp;
        stack[sp] = stack[sp + 1 + i];
    }

    void pop() {
        if (checkUnderflow()) {
            ++sp;
        }
    }

private:
    bool checkOverflow(int n = 1) const {
        if (sp - n < 0) {
            return false;
        }
        return true;
    }

    bool checkUnderflow() const {
        if (sp == psStackSize) {
            return false;
        }
        return true;
    }

    bool checkType(PSObjectType t1, PSObjectType t2) {
        if (stack[sp].type != t1 && stack[sp].type != t2) {
            return false;
        }
        return true;
    }

    PSObject stack[psStackSize];
    int sp;
};

// Test Fixture
class PSStackTest_1915 : public ::testing::Test {
protected:
    PSStack stack;
};

// ============================================================
// Tests for empty()
// ============================================================

TEST_F(PSStackTest_1915, EmptyOnConstruction_1915) {
    EXPECT_TRUE(stack.empty());
}

TEST_F(PSStackTest_1915, NotEmptyAfterPushInt_1915) {
    stack.pushInt(42);
    EXPECT_FALSE(stack.empty());
}

TEST_F(PSStackTest_1915, EmptyAfterPushAndPop_1915) {
    stack.pushInt(10);
    stack.pop();
    EXPECT_TRUE(stack.empty());
}

// ============================================================
// Tests for pushInt / popInt
// ============================================================

TEST_F(PSStackTest_1915, PushIntAndPopInt_1915) {
    stack.pushInt(42);
    EXPECT_EQ(stack.popInt(), 42);
}

TEST_F(PSStackTest_1915, PushMultipleIntsAndPopInOrder_1915) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);
    EXPECT_EQ(stack.popInt(), 3);
    EXPECT_EQ(stack.popInt(), 2);
    EXPECT_EQ(stack.popInt(), 1);
}

TEST_F(PSStackTest_1915, PopIntFromEmptyReturnsZero_1915) {
    EXPECT_EQ(stack.popInt(), 0);
}

TEST_F(PSStackTest_1915, PushIntNegativeValue_1915) {
    stack.pushInt(-99);
    EXPECT_EQ(stack.popInt(), -99);
}

TEST_F(PSStackTest_1915, PushIntZero_1915) {
    stack.pushInt(0);
    EXPECT_EQ(stack.popInt(), 0);
}

// ============================================================
// Tests for pushReal / popNum
// ============================================================

TEST_F(PSStackTest_1915, PushRealAndPopNum_1915) {
    stack.pushReal(3.14);
    EXPECT_DOUBLE_EQ(stack.popNum(), 3.14);
}

TEST_F(PSStackTest_1915, PushIntAndPopNumReturnsAsDouble_1915) {
    stack.pushInt(7);
    EXPECT_DOUBLE_EQ(stack.popNum(), 7.0);
}

TEST_F(PSStackTest_1915, PopNumFromEmptyReturnsZero_1915) {
    EXPECT_DOUBLE_EQ(stack.popNum(), 0.0);
}

TEST_F(PSStackTest_1915, PushRealNegative_1915) {
    stack.pushReal(-2.718);
    EXPECT_DOUBLE_EQ(stack.popNum(), -2.718);
}

// ============================================================
// Tests for pushBool / popBool
// ============================================================

TEST_F(PSStackTest_1915, PushBoolTrueAndPopBool_1915) {
    stack.pushBool(true);
    EXPECT_TRUE(stack.popBool());
}

TEST_F(PSStackTest_1915, PushBoolFalseAndPopBool_1915) {
    stack.pushBool(false);
    EXPECT_FALSE(stack.popBool());
}

TEST_F(PSStackTest_1915, PopBoolFromEmptyReturnsFalse_1915) {
    EXPECT_FALSE(stack.popBool());
}

// ============================================================
// Tests for topIsInt
// ============================================================

TEST_F(PSStackTest_1915, TopIsIntWhenIntPushed_1915) {
    stack.pushInt(5);
    EXPECT_TRUE(stack.topIsInt());
}

TEST_F(PSStackTest_1915, TopIsIntFalseWhenRealPushed_1915) {
    stack.pushReal(1.0);
    EXPECT_FALSE(stack.topIsInt());
}

TEST_F(PSStackTest_1915, TopIsIntFalseWhenBoolPushed_1915) {
    stack.pushBool(true);
    EXPECT_FALSE(stack.topIsInt());
}

TEST_F(PSStackTest_1915, TopIsIntFalseWhenEmpty_1915) {
    EXPECT_FALSE(stack.topIsInt());
}

// ============================================================
// Tests for topIsReal
// ============================================================

TEST_F(PSStackTest_1915, TopIsRealWhenRealPushed_1915) {
    stack.pushReal(2.5);
    EXPECT_TRUE(stack.topIsReal());
}

TEST_F(PSStackTest_1915, TopIsRealFalseWhenIntPushed_1915) {
    stack.pushInt(5);
    EXPECT_FALSE(stack.topIsReal());
}

TEST_F(PSStackTest_1915, TopIsRealFalseWhenEmpty_1915) {
    EXPECT_FALSE(stack.topIsReal());
}

// ============================================================
// Tests for topTwoAreInts
// ============================================================

TEST_F(PSStackTest_1915, TopTwoAreIntsWhenTwoIntsPushed_1915) {
    stack.pushInt(1);
    stack.pushInt(2);
    EXPECT_TRUE(stack.topTwoAreInts());
}

TEST_F(PSStackTest_1915, TopTwoAreIntsFalseWhenOnlyOneInt_1915) {
    stack.pushInt(1);
    EXPECT_FALSE(stack.topTwoAreInts());
}

TEST_F(PSStackTest_1915, TopTwoAreIntsFalseWhenTopIsReal_1915) {
    stack.pushInt(1);
    stack.pushReal(2.0);
    EXPECT_FALSE(stack.topTwoAreInts());
}

TEST_F(PSStackTest_1915, TopTwoAreIntsFalseWhenSecondIsReal_1915) {
    stack.pushReal(1.0);
    stack.pushInt(2);
    EXPECT_FALSE(stack.topTwoAreInts());
}

TEST_F(PSStackTest_1915, TopTwoAreIntsFalseWhenEmpty_1915) {
    EXPECT_FALSE(stack.topTwoAreInts());
}

TEST_F(PSStackTest_1915, TopTwoAreIntsFalseWhenBothReals_1915) {
    stack.pushReal(1.0);
    stack.pushReal(2.0);
    EXPECT_FALSE(stack.topTwoAreInts());
}

TEST_F(PSStackTest_1915, TopTwoAreIntsFalseWhenBoolAndInt_1915) {
    stack.pushBool(true);
    stack.pushInt(1);
    EXPECT_FALSE(stack.topTwoAreInts());
}

// ============================================================
// Tests for topTwoAreNums
// ============================================================

TEST_F(PSStackTest_1915, TopTwoAreNumsWhenTwoInts_1915) {
    stack.pushInt(1);
    stack.pushInt(2);
    EXPECT_TRUE(stack.topTwoAreNums());
}

TEST_F(PSStackTest_1915, TopTwoAreNumsWhenTwoReals_1915) {
    stack.pushReal(1.0);
    stack.pushReal(2.0);
    EXPECT_TRUE(stack.topTwoAreNums());
}

TEST_F(PSStackTest_1915, TopTwoAreNumsWhenIntAndReal_1915) {
    stack.pushInt(1);
    stack.pushReal(2.0);
    EXPECT_TRUE(stack.topTwoAreNums());
}

TEST_F(PSStackTest_1915, TopTwoAreNumsWhenRealAndInt_1915) {
    stack.pushReal(1.0);
    stack.pushInt(2);
    EXPECT_TRUE(stack.topTwoAreNums());
}

TEST_F(PSStackTest_1915, TopTwoAreNumsFalseWhenOnlyOne_1915) {
    stack.pushInt(1);
    EXPECT_FALSE(stack.topTwoAreNums());
}

TEST_F(PSStackTest_1915, TopTwoAreNumsFalseWhenEmpty_1915) {
    EXPECT_FALSE(stack.topTwoAreNums());
}

TEST_F(PSStackTest_1915, TopTwoAreNumsFalseWhenBoolInvolved_1915) {
    stack.pushBool(true);
    stack.pushInt(1);
    EXPECT_FALSE(stack.topTwoAreNums());
}

// ============================================================
// Tests for clear
// ============================================================

TEST_F(PSStackTest_1915, ClearMakesStackEmpty_1915) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);
    stack.clear();
    EXPECT_TRUE(stack.empty());
}

TEST_F(PSStackTest_1915, ClearOnEmptyStackIsNoOp_1915) {
    stack.clear();
    EXPECT_TRUE(stack.empty());
}

// ============================================================
// Tests for pop
// ============================================================

TEST_F(PSStackTest_1915, PopRemovesTopElement_1915) {
    stack.pushInt(10);
    stack.pushInt(20);
    stack.pop();
    EXPECT_EQ(stack.popInt(), 10);
}

TEST_F(PSStackTest_1915, PopOnEmptyDoesNotCrash_1915) {
    stack.pop();
    EXPECT_TRUE(stack.empty());
}

// ============================================================
// Tests for index
// ============================================================

TEST_F(PSStackTest_1915, IndexDuplicatesTopElement_1915) {
    stack.pushInt(10);
    stack.pushInt(20);
    stack.index(0);  // duplicate top
    EXPECT_EQ(stack.popInt(), 20);
    EXPECT_EQ(stack.popInt(), 20);
    EXPECT_EQ(stack.popInt(), 10);
}

TEST_F(PSStackTest_1915, IndexCopiesSecondElement_1915) {
    stack.pushInt(10);
    stack.pushInt(20);
    stack.index(1);  // copy element at position 1
    EXPECT_EQ(stack.popInt(), 10);
    EXPECT_EQ(stack.popInt(), 20);
    EXPECT_EQ(stack.popInt(), 10);
}

// ============================================================
// Tests for stack overflow
// ============================================================

TEST_F(PSStackTest_1915, PushUpToStackSizeDoesNotCrash_1915) {
    for (int i = 0; i < 100; ++i) {
        stack.pushInt(i);
    }
    EXPECT_FALSE(stack.empty());
    // Pushing beyond should not crash
    stack.pushInt(999);
}

TEST_F(PSStackTest_1915, StackFullThenPopWorks_1915) {
    for (int i = 0; i < 100; ++i) {
        stack.pushInt(i);
    }
    // Top should be 99
    EXPECT_EQ(stack.popInt(), 99);
}

// ============================================================
// Tests for type mismatch
// ============================================================

TEST_F(PSStackTest_1915, PopIntWhenTopIsBoolReturnsZero_1915) {
    stack.pushBool(true);
    EXPECT_EQ(stack.popInt(), 0);
}

TEST_F(PSStackTest_1915, PopBoolWhenTopIsIntReturnsFalse_1915) {
    stack.pushInt(1);
    EXPECT_FALSE(stack.popBool());
}

TEST_F(PSStackTest_1915, PopNumWhenTopIsBoolReturnsZero_1915) {
    stack.pushBool(true);
    EXPECT_DOUBLE_EQ(stack.popNum(), 0.0);
}

// ============================================================
// Tests for mixed type sequences
// ============================================================

TEST_F(PSStackTest_1915, MixedTypePushAndPop_1915) {
    stack.pushInt(42);
    stack.pushReal(3.14);
    stack.pushBool(true);

    EXPECT_TRUE(stack.popBool());
    EXPECT_DOUBLE_EQ(stack.popNum(), 3.14);
    EXPECT_EQ(stack.popInt(), 42);
    EXPECT_TRUE(stack.empty());
}

TEST_F(PSStackTest_1915, TopTwoAreIntsAfterPopOfReal_1915) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushReal(3.0);
    EXPECT_FALSE(stack.topTwoAreInts());
    stack.pop();
    EXPECT_TRUE(stack.topTwoAreInts());
}

// ============================================================
// Boundary: single element checks
// ============================================================

TEST_F(PSStackTest_1915, SingleIntOnStack_1915) {
    stack.pushInt(77);
    EXPECT_TRUE(stack.topIsInt());
    EXPECT_FALSE(stack.topIsReal());
    EXPECT_FALSE(stack.topTwoAreInts());
    EXPECT_FALSE(stack.topTwoAreNums());
    EXPECT_FALSE(stack.empty());
}

TEST_F(PSStackTest_1915, SingleRealOnStack_1915) {
    stack.pushReal(1.5);
    EXPECT_FALSE(stack.topIsInt());
    EXPECT_TRUE(stack.topIsReal());
    EXPECT_FALSE(stack.topTwoAreInts());
    EXPECT_FALSE(stack.topTwoAreNums());
    EXPECT_FALSE(stack.empty());
}

TEST_F(PSStackTest_1915, SingleBoolOnStack_1915) {
    stack.pushBool(false);
    EXPECT_FALSE(stack.topIsInt());
    EXPECT_FALSE(stack.topIsReal());
    EXPECT_FALSE(stack.topTwoAreInts());
    EXPECT_FALSE(stack.topTwoAreNums());
    EXPECT_FALSE(stack.empty());
}

// ============================================================
// Test clear then reuse
// ============================================================

TEST_F(PSStackTest_1915, ClearAndReuse_1915) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.clear();
    EXPECT_TRUE(stack.empty());
    stack.pushReal(9.9);
    EXPECT_FALSE(stack.empty());
    EXPECT_TRUE(stack.topIsReal());
    EXPECT_DOUBLE_EQ(stack.popNum(), 9.9);
    EXPECT_TRUE(stack.empty());
}

// ============================================================
// Test large int values
// ============================================================

TEST_F(PSStackTest_1915, PushLargeIntValues_1915) {
    stack.pushInt(INT32_MAX);
    EXPECT_EQ(stack.popInt(), INT32_MAX);
}

TEST_F(PSStackTest_1915, PushMinIntValue_1915) {
    stack.pushInt(INT32_MIN);
    EXPECT_EQ(stack.popInt(), INT32_MIN);
}

// ============================================================
// Test large real values
// ============================================================

TEST_F(PSStackTest_1915, PushLargeRealValue_1915) {
    stack.pushReal(1e308);
    EXPECT_DOUBLE_EQ(stack.popNum(), 1e308);
}

TEST_F(PSStackTest_1915, PushZeroReal_1915) {
    stack.pushReal(0.0);
    EXPECT_DOUBLE_EQ(stack.popNum(), 0.0);
}

TEST_F(PSStackTest_1915, PushNegativeReal_1915) {
    stack.pushReal(-1e-10);
    EXPECT_DOUBLE_EQ(stack.popNum(), -1e-10);
}
