#include "Obb.h"

Obb::Obb(glm::vec3 cent, glm::vec4 us[3], float es[3])
{
	c = cent;
	for (int i = 0; i < 3; i++)
	{
		u[i].x = us[i].x;
		u[i].y = us[i].y;
		u[i].z = us[i].z;
	}

	e[0] = es[0];
	e[1] = es[1];
	e[2] = es[2];

}
Obb::Obb()
{

}

Obb::~Obb()
{
}

// false = no collision true = collision
bool Obb::CollCheck(Obb obb1)
{
	float ra, rb;
	glm::mat3x3 R, AbsR;

	//compute rotation matrix expressing obb1 in this coordinate frame

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			R[i][j] = glm::dot(u[i], obb1.u[j]);
	}

	//calculate translation vector t
	glm::vec3 t = obb1.c - c;

	//bring translation into this coordinate frame
	//POSSIBLE TYPO IN ERICSON TEXT, used u2 for both second and third
	t = glm::vec3(glm::dot(t, u[0]), glm::dot(t, u[1]), glm::dot(t, u[2]));

	//compute common subexpressions
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			AbsR[i][j] = abs(R[i][j]) + FLT_EPSILON;
	}



	//Test axes L = A0, L = A1, L= A2
	for (int i = 0; i < 3; i++)
	{
		ra = e[i];
		rb = obb1.e[0] * AbsR[i][0] + obb1.e[1] * AbsR[i][0] + obb1.e[2] * AbsR[i][2];
		if (abs(t[i]) > ra + rb) return false;
	}

	//test axes L=B0, L= B1, L=B2
	for (int i = 0; i < 3; i++)
	{
		ra = e[0] * AbsR[0][i] + e[1] * AbsR[1][i] + e[2] * AbsR[2][i];
		rb = obb1.e[i];
		if (abs(t[0] * R[0][i] + t[1] * R[1][i] + t[2] * R[2][i]) > ra + rb) return false;
	}

	//test axis L = A0 X B0
	ra = e[1] * AbsR[2][0] + e[2] * AbsR[1][0];
	rb = obb1.e[1] * AbsR[0][2] + obb1.e[2] * AbsR[0][1];
	if (abs(t[2] * R[1][0] - t[1] * R[2][0]) > ra + rb) return false;

	//test axis L = A1 x B0
	ra = e[0] * AbsR[2][0] + e[2] * AbsR[0][0];
	rb = obb1.e[1] * AbsR[1][2] + obb1.e[2] * AbsR[1][1];
	if (abs(t[0] * R[2][0] - t[2] * R[0][0]) > ra + rb) return false;

	//Test axis L = A1 X B1
	ra = e[0] * AbsR[2][1] + e[2] * AbsR[0][1];
	rb = obb1.e[0] * AbsR[1][2] + obb1.e[2] * AbsR[1][0];
	if (abs(t[0] * R[2][1] - t[2] * R[0][1]) > ra + rb) return false;

	//Test axis L = A1 X B2
	ra = e[0] * AbsR[2][2] + e[2] * AbsR[0][2];
	rb = obb1.e[0] * AbsR[1][1] + obb1.e[1] * AbsR[1][0];
	if (abs(t[0] * R[2][2] - t[2] * R[0][2]) > ra + rb) return false;

	//Test axis L = A2 x B0
	ra = e[0] * AbsR[1][0] + e[1] * AbsR[0][0];
	rb = obb1.e[1] * AbsR[2][2] + obb1.e[2] * AbsR[2][1];
	if (abs(t[1] * R[0][0] - t[0] * R[1][0]) > ra + rb) return false;

	//Test axis L = A2 x B1
	ra = e[0] * AbsR[1][1] + e[1] * AbsR[0][1];
	rb = obb1.e[0] * AbsR[2][2] + obb1.e[2] * AbsR[2][0];
	if (abs(t[1] * R[0][1] - t[0] * R[1][1]) > ra + rb) return false;

	//Test axis L = A2 x B2
	ra = e[0] * AbsR[1][2] + e[1] * AbsR[0][2];
	rb = obb1.e[0] * AbsR[2][1] + obb1.e[1] * AbsR[2][0];
	if (abs(t[1] * R[0][2] - t[0] * R[1][2]) > ra + rb) return false;

	return true;


}

int Obb::GetObbNum()
{
	return obbNum;
}

void Obb::SetObbNum(int i)
{
	obbNum = i;
}

glm::vec3 Obb::GetCenter()
{
	return c;
}

void Obb::SetCenter(glm::vec3 c2)
{
	c = c2;
}

glm::vec3* Obb::GetAxes()
{
	return u;
}

void Obb::SetAxes(glm::vec3 * u2)
{
	//u = u2;
}

float* Obb::GetWidths()
{
	return e;
}