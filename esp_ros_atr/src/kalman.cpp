#include <kalman.h>

 
//kalman滤波的五个方程
//x(k)=F*x(k-1)+B*u(k-1)
//p(k)=F*p(k-1)*F'+Q

//s(k)=H*p(k)*H'+R
//k(k)=p(k)*H'*s(k)^-1

//x(k)=x(k)+k(k)*y(k)
//p(k)=(I-k(k)*H)*p(k)

KalmanFilter3D::KalmanFilter3D()
{
    x = Matrix<3, 1>(0.0);
    P = Matrix<3, 3>(0.0);
    Q = Matrix<3, 3>(0.0);
    R = Matrix<3, 3>(0.0);
    F = Matrix<3, 3>(0.0);
    H = Matrix<3, 3>(0.0);
    B = Matrix<3, 3>(0.0);
}
KalmanFilter3D::KalmanFilter3D(Matrix<3, 1> &x, Matrix<3, 3> &P, Matrix<3, 3> &Q, Matrix<3, 3> &R,Matrix<3, 3> &F, Matrix<3, 3> &H, Matrix<3, 3> &B)
{
    this->x = x;
    this->P = P;
    this->Q = Q;
    this->R = R;
    this->F = F;
    this->H = H;
    this->B = B;
}
void KalmanFilter3D::setX(Matrix<3, 1> &x)
{
    this->x = x;
}
void KalmanFilter3D::setP(Matrix<3, 3> &P)
{
    this->P = P;
}
void KalmanFilter3D::setQ(Matrix<3, 3> &Q)
{
    this->Q = Q;
}
void KalmanFilter3D::setR(Matrix<3, 3> &R)
{
    this->R = R;
}
void KalmanFilter3D::setF(Matrix<3, 3> &F)
{
    this->F = F;
}
void KalmanFilter3D::setH(Matrix<3, 3> &H)
{
    this->H = H;
}
void KalmanFilter3D::setB(Matrix<3, 3> &B)
{
    this->B = B;
}

void KalmanFilter3D::predict(){
    x = F * x + B * u;
    P = F * P * (~F) + Q;
}
void KalmanFilter3D::update(Matrix<3, 1> &z)
{
    Matrix<3, 1> y = z - H * x;
    Matrix<3, 3> S = H * P * (~H) + R;
    K = P * (~H) * Invert(S);
    x = x + K * y;
    Identity<3,3> I;
    P = (I - K * H) * P;
}
Matrix<3, 1> KalmanFilter3D::getX()
{
    return x;
}
Matrix<3, 3> KalmanFilter3D::getP()
{
    return P;
}

KalmanFilter2D::KalmanFilter2D()
{
    x = Matrix<2, 1>(0.0);
    P = Matrix<2, 2>(0.0);
    Q = Matrix<2, 2>(0.0);
    R = Matrix<2, 2>(0.0);
    F = Matrix<2, 2>(0.0);
    H = Matrix<2, 2>(0.0);
    B = Matrix<2, 2>(0.0);
}

KalmanFilter2D::KalmanFilter2D(Matrix<2, 1> &x, Matrix<2, 2> &P, Matrix<2, 2> &Q, Matrix<2, 2> &R,Matrix<2, 2> &F, Matrix<2, 2> &H, Matrix<2, 2> &B)
{
    this->x = x;
    this->P = P;
    this->Q = Q;
    this->R = R;
    this->F = F;
    this->H = H;
    this->B = B;
}
void KalmanFilter2D::setX(Matrix<2, 1> &x)
{
    this->x = x;
}
void KalmanFilter2D::setP(Matrix<2, 2> &P)
{
    this->P = P;
}
void KalmanFilter2D::setQ(Matrix<2, 2> &Q)
{
    this->Q = Q;
}
void KalmanFilter2D::setR(Matrix<2, 2> &R)
{
    this->R = R;
}
void KalmanFilter2D::setF(Matrix<2, 2> &F)
{
    this->F = F;
}
void KalmanFilter2D::setH(Matrix<2, 2> &H)
{
    this->H = H;
}
void KalmanFilter2D::setB(Matrix<2, 2> &B)
{
    this->B = B;
}
void KalmanFilter2D::update(Matrix<2, 1> &z)
{
    Matrix<2, 1> y = z - H * x;
    Matrix<2, 2> S = H * P * (~H) + R;
    K = P * (~H) * Invert(S);
    x = x + K * y;
    Identity<2,2> I;
    P = (I - K * H) * P;
}

void KalmanFilter2D::predict(){
    x = F * x + B * u;
    P = F * P * (~F) + Q;
    // Serial<<"x:"<<x<<"F:"<<F<<"B:"<<B<<"u:"<<u<<"P:"<<P<<"K:"<<K<<"\n";
}

Matrix<2, 1> KalmanFilter2D::getX()
{
    return x;
}
Matrix<2, 2> KalmanFilter2D::getP()
{
    return P;
}
Matrix<2, 2> KalmanFilter2D::getF()
{
    return F;
}

