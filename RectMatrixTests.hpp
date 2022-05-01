#ifndef MAIN_CPP_RECTMATRIXTESTS_HPP
#define MAIN_CPP_RECTMATRIXTESTS_HPP

#include "RectMatrix.hpp"

class RectMatrixTests
{
private:
    static void constructorFromHeightAndWidthTest();
    static void equalityTest();
    static void constructorFromAnotherMatrixTest();
    static void constructorFromAnotherMatrixRvalueReferenceTest();
    static void oneEqualAnotherTest();
    static void oneEqualAnotherRvalueReferenceTest();

    static void sumTest();
    static void scalarMultiplyTest();

public:
    static void allTestsTogether();
};

void RectMatrixTests::constructorFromHeightAndWidthTest()
{
    RectMatrix<int> matrix(5, 6);
    assert(matrix.getWidth() == 6);
    assert(matrix.getHeight() == 5);
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 6; j++)
            assert(matrix.get(i, j) == 0);
}

void RectMatrixTests::equalityTest()
{
    RectMatrix<int> matrix1(5, 6);
    RectMatrix<int> matrix2(5, 6);
    assert(matrix1 == matrix2);
    matrix1[0][2] = 15;
    assert(!(matrix1 == matrix2));
    matrix2[0][2] = 15;
    assert(matrix1 == matrix2);
}

void RectMatrixTests::constructorFromAnotherMatrixTest()
{
    RectMatrix<int> matrix1(5, 6);
    RectMatrix<int> matrix2 = matrix1;
    assert(matrix1 == matrix2);
}

void RectMatrixTests::constructorFromAnotherMatrixRvalueReferenceTest()
{
    RectMatrix<int> matrix1(5, 6);
    RectMatrix<int> matrix1Copy = matrix1;
    RectMatrix<int> matrix2 = std::move(matrix1);
    assert(matrix1Copy == matrix2);
}

void RectMatrixTests::oneEqualAnotherTest()
{
    RectMatrix<int> matrix1(5, 6);
    RectMatrix<int> matrix2(2, 3);
    matrix2 = matrix1;
    assert(matrix1 == matrix2);
}

void RectMatrixTests::oneEqualAnotherRvalueReferenceTest()
{
    RectMatrix<int> matrix1(5, 6);
    RectMatrix<int> matrix1Copy = matrix1;
    RectMatrix<int> matrix2(2, 3);
    matrix2 = std::move(matrix1);
    assert(matrix1Copy == matrix2);
}

void RectMatrixTests::sumTest()
{
    RectMatrix<int> matrix1(5, 6);
    RectMatrix<int> matrix2(5, 6);
    matrix1[0][0] = 5;
    matrix2[1][3] = 6;

    RectMatrix<int> result(5, 6);
    result[0][0] = 5; result[1][3] = 6;
    assert(matrix1 + matrix2 == result);
}

void RectMatrixTests::scalarMultiplyTest()
{
    RectMatrix<int> matrix1(5, 6);
    matrix1[0][0] = 5;

    RectMatrix<int> result(5, 6);
    result[0][0] = 15;
    assert(matrix1 * 3 == result);
    assert(3 * matrix1 == result);
}

void RectMatrixTests::allTestsTogether()
{
    constructorFromHeightAndWidthTest();
    equalityTest();
    constructorFromAnotherMatrixTest();
    constructorFromAnotherMatrixRvalueReferenceTest();
    oneEqualAnotherTest();
    oneEqualAnotherRvalueReferenceTest();
    sumTest();
    scalarMultiplyTest();

}

#endif
