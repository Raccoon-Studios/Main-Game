#pragma once
#include <glm\gtx\transform.hpp>
#include <math.h>

//#ifndef Shape
//#define Shape

class Shape; 

class Obb
{
public:
	//glm::vec3 c; //center
	//glm::vec3 u[3]; //model x y z axes in world space
	//float e[3]; //half-width in x y and z dimensions
	bool CollCheck(Obb* obb1); //check for collision with other obb
	int GetObbNum();
	glm::vec3 GetCenter();
	void SetCenter(glm::vec3 c2);
	glm:: vec3* GetAxes();
	void SetAxes(glm::vec3 * u);
	float* GetWidths();
	void SetWidths(float es[3]);
	void SetObbNum(int i);
	Obb();
	Obb(glm::vec3 c, glm::vec4 u[3], float e[3]);
	~Obb();
	bool GetIsBall();
	void SetIsBall(bool value);
	bool GetIsRightPaddle();
	void SetIsRightPaddle(bool value);
	bool GetIsLeftPaddle();
	void SetIsLeftPaddle(bool value);
	bool GetIsWall();
	void SetIsWall(bool value);

	int GetCollidingWith(Obb* obb1);

	Shape* GetShape();
	void SetShape(Shape* shape1);

private:
	int obbNum;
	glm::vec3 c; //center
	glm::vec3 u[3]; //model x y z axes in world space
	float e[3]; //half-width in x y and z dimensions
	bool isRightPaddle, isLeftPaddle, isBall, isWall;
	Shape* shape;
};

