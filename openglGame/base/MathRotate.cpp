#include "MathRotate.h"
#include <cmath>

#define CV_PI 3.141592654

static const float CV_PI_R = CV_PI / 180;


//���ռ����X����ת
//������� y zΪ�ռ��ԭʼy z����
//thetaxΪ�ռ����X����ת���ٶȣ��Ƕ��Ʒ�Χ��-180��180
//outy outzΪ��ת��Ľ������
void codeRotateByX(double y, double z, double thetax, double& outy, double& outz)
{
	double y1 = y;//����������һ�Σ���֤&y == &y���������Ҳ�ܼ�����ȷ
	double z1 = z;
	double rx = thetax * CV_PI_R;
	outy = cos(rx) * y1 - sin(rx) * z1;
	outz = cos(rx) * z1 + sin(rx) * y1;
}


//���ռ����Y����ת
//������� x zΪ�ռ��ԭʼx z����
//thetayΪ�ռ����Y����ת���ٶȣ��Ƕ��Ʒ�Χ��-180��180
//outx outzΪ��ת��Ľ������
void codeRotateByY(double x, double z, double thetay, double& outx, double& outz)
{
	double x1 = x;
	double z1 = z;
	double ry = thetay * CV_PI_R;
	outx = cos(ry) * x1 + sin(ry) * z1;
	outz = cos(ry) * z1 - sin(ry) * x1;
}


//���ռ����Z����ת
//������� x yΪ�ռ��ԭʼx y����
//thetazΪ�ռ����Z����ת���ٶȣ��Ƕ��Ʒ�Χ��-180��180
//outx outyΪ��ת��Ľ������
void codeRotateByZ(double x, double y, double thetaz, double& outx, double& outy)
{
	double x1 = x;//����������һ�Σ���֤&x == &outx���������Ҳ�ܼ�����ȷ
	double y1 = y;
	double rz = thetaz * CV_PI_R;
	outx = cos(rz) * x1 - sin(rz) * y1;
	outy = sin(rz) * x1 + cos(rz) * y1;

}


