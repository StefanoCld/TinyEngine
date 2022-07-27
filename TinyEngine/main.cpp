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

	Transform* currentTransform;
	currentTransform = &(s.obj[0].transform);

	rayCasting(s.toWorld());

	char key_press;
	int ascii_value;
	bool isFirstPerson = false;

	const float deltaMov = 0.3f;
	const float deltaRot = 3.f;

	float dX = 0.f;

	Transform t = Transform();

	while (1)
	{
		//Relative Coordinates - Game Object
		if (isFirstPerson) {
			key_press = _getch();
			ascii_value = key_press;

			//W - Forward
			if (ascii_value == 119) {
				currentTransform->translate += currentTransform->forward() * deltaMov;

				rayCasting(s.toView(*currentTransform));
			}

			//S - Backward
			else if (ascii_value == 115) {
				currentTransform->translate -= currentTransform->forward() * deltaMov;

				rayCasting(s.toView(*currentTransform));
			}

			//A
			else if (ascii_value == 97) {
				dX -= deltaRot;
				currentTransform->rotate = Quaternion::fromAngleAxis(dX, Vector3(0, 1, 0));

				rayCasting(s.toView(*currentTransform));
			}

			//D
			else if (ascii_value == 100) {
				dX += deltaRot;
				currentTransform->rotate = Quaternion::fromAngleAxis(dX, Vector3(0, 1, 0));

				rayCasting(s.toView(*currentTransform));
			}

			//g - Change to External Camera
			else if (ascii_value == 103) {
				isFirstPerson = false;
				dX = 0.f;
				rayCasting(s.toView(Transform()));
			}
		}
		

		//Relative Coordinates - External Camera
		else {
			key_press = _getch();
			ascii_value = key_press;

			//W
			if (ascii_value == 119) {
				t.translate += t.forward() * deltaMov;

				rayCasting(s.toView(t));
			}

			//S
			else if (ascii_value == 115) {
				t.translate -= t.forward() * deltaMov;

				rayCasting(s.toView(t));
			}

			//A
			else if (ascii_value == 97) {
				dX -= deltaRot;
				t.rotate = Quaternion::fromAngleAxis(dX, Vector3(0, 1, 0));

				rayCasting(s.toView(t));
			}

			//D
			else if (ascii_value == 100) {
				dX += deltaRot;
				t.rotate = Quaternion::fromAngleAxis(dX, Vector3(0, 1, 0));

				rayCasting(s.toView(t));
			}

			//g - Change to GameObject
			else if (ascii_value == 103) {
				isFirstPerson = true;
				dX = 0.f;
				rayCasting(s.toView(*currentTransform));
			}
		}
	}
}