#include <windows.h>
#include <iostream>
#include <conio.h>
#include <chrono>

#include "vector3.h"
#include "shapes3d.h"
#include "camera.h"
#include "quaternion.h"
#include "transform.h"
#include "scene.h"

using namespace mgd;

int main() {
	
	Scene s;
	s.populate4();

	rayCasting(s.toWorld());

	char key_press;
	int ascii_value;

	float delta = 0.3f;
	float deltaRot = 3.f;
	float dZ = 0.f;
	float dX = 0.f;
	float dY = 0.f;

	while (1)
	{
		key_press = _getch();
		ascii_value = key_press;

		//S
		/*
		if (ascii_value == 115) {
			dZ -= delta;
			Transform t = Transform();
			t.translate = Vector3(0, dY, dZ);
			t.rotate = Quaternion::fromAngleAxis(dX, Vector3(0, 1, 0));

			rayCasting(s.toView(t));
		}
		*/

		//W
		if (ascii_value == 119) {
			dZ += delta;
			Transform t = Transform();
			t.translate = Vector3(0, dY, dZ);
			t.rotate = Quaternion::fromAngleAxis(dX, Vector3(0, 1, 0));

			rayCasting(s.toView(t));
		}

		//A
		else if (ascii_value == 97) {
			dX -= deltaRot;
			Transform t = Transform();
			t.translate = Vector3(0, dY, dZ);
			t.rotate = Quaternion::fromAngleAxis(dX, Vector3(0, 1, 0));

			rayCasting(s.toView(t));
		}

		//D
		else if (ascii_value == 100) {
			dX += deltaRot;
			Transform t = Transform();
			t.translate = Vector3(0, dY, dZ);
			t.rotate = Quaternion::fromAngleAxis(dX, Vector3(0, 1, 0));

			rayCasting(s.toView(t));
		}

		/*
		//I
		else if (ascii_value == 105) {
			dY += delta;
			Transform t = Transform();
			t.translate = Vector3(0, dY, dZ);
			t.rotate = Quaternion::fromAngleAxis(dX, Vector3(0, 1, 0));

			rayCasting(s.toView(t));
		}

		//K
		else if (ascii_value == 107) {
			dY -= delta;
			Transform t = Transform();
			t.translate = Vector3(0, dY, dZ);
			t.rotate = Quaternion::fromAngleAxis(dX, Vector3(0, 1, 0));

			rayCasting(s.toView(t));
		}
		*/
	}
}