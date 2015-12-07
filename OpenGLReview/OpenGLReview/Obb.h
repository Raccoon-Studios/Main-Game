#include <glm\gtx\transform.hpp>
#include <math.h>
#pragma once

class Obb
{
public:
	//glm::vec3 c; //center
	//glm::vec3 u[3]; //model x y z axes in world space
	//float e[3]; //half-width in x y and z dimensions
	bool CollCheck(Obb); //check for collision with other obb
	int GetObbNum();
	glm::vec3 GetCenter();
	void SetCenter(glm::vec3 c2);
	glm:: vec3* GetAxes();
	void SetAxes(glm::vec3 * u);
	float* GetWidths();
	void SetObbNum(int i);
	Obb();
	Obb(glm::vec3 c, glm::vec4 u[3], float e[3]);
	~Obb();

private:
	int obbNum;
	glm::vec3 c; //center
	glm::vec3 u[3]; //model x y z axes in world space
	float e[3]; //half-width in x y and z dimensions
};

