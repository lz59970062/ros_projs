#ifndef __KALMAN__
#define __KALMAN__
#include <Arduino.h>
#include "BasicLinearAlgebra.h"
using namespace BLA;
class KalmanFilter3D
{
public:
    KalmanFilter3D(Matrix<3, 1> &x, Matrix<3, 3> &P, Matrix<3, 3> &Q, Matrix<3, 3> &R, Matrix<3, 3> &F, Matrix<3, 3> &H, Matrix<3, 3> &B);
    KalmanFilter3D();
    void setX(Matrix<3, 1> &x);
    void setP(Matrix<3, 3> &P);
    void setQ(Matrix<3, 3> &Q);
    void setR(Matrix<3, 3> &R);
    void setF(Matrix<3, 3> &F);
    void setH(Matrix<3, 3> &H);
    void setB(Matrix<3, 3> &G);
    void setU(Matrix<3, 1> &u);
    void update(Matrix<3, 1> &z);
    void predict();
    Matrix<3, 1> getX();
    Matrix<3, 3> getP();
    Matrix<3, 1> x;
    Matrix<3, 3> K;
    Matrix<3, 3> P;

private:
    Matrix<3, 1> u;
    Matrix<3, 1> z;
   
    Matrix<3, 3> Q;
    Matrix<3, 3> R;
    Matrix<3, 3> F;
    Matrix<3, 3> H;
    Matrix<3, 3> B;
};

class KalmanFilter2D
{
public:
    KalmanFilter2D(Matrix<2, 1> &x, Matrix<2, 2> &P, Matrix<2, 2> &Q, Matrix<2, 2> &R, Matrix<2, 2> &F, Matrix<2, 2> &H, Matrix<2, 2> &B);
    KalmanFilter2D();
    void setX(Matrix<2, 1> &x);
    void setP(Matrix<2, 2> &P);
    void setQ(Matrix<2, 2> &Q);
    void setR(Matrix<2, 2> &R);
    void setF(Matrix<2, 2> &F);
    void setH(Matrix<2, 2> &H);
    void setB(Matrix<2, 2> &G);
    void setU(Matrix<2, 1> &u);
    void update(Matrix<2, 1> &z);
    void predict();
    Matrix<2, 1> getX();
    Matrix<2, 2> getP();
    Matrix<2, 2> getF();
    Matrix<2, 2> getK();
    Matrix<2, 1> x;
    Matrix<2, 2> K;
    Matrix<2, 2> F;
    Matrix<2, 2> P;

private:
    Matrix<2, 1> u;
    Matrix<2, 1> z;

    Matrix<2, 2> Q;
    Matrix<2, 2> R;

    Matrix<2, 2> H;
    Matrix<2, 2> B;
};

#endif
