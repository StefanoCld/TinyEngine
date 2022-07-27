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
	//Scene stuff
	Scene s;
	s.populate4();

	unsigned int sphereNumber = s.obj.size();
	unsigned int index = 0;

	//Game object reference
	Transform* currentTransform;
	currentTransform = &(s.obj.at(index).transform);

	char key_press;
	int ascii_value;
	bool isFirstPerson = false;

	//Movement multipliers
	const float deltaMov = 0.3f;
	const float deltaRot = 3.f;

	//Current rotation amount (on Y-axis)
	float dX = 0.f;

	//External camera 
	Transform t = Transform();

	//First render
	rayCasting(s.toWorld());

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

			//n - Select next Game Object
			else if (ascii_value == 110) {
				dX = 0.f;

				index++;
				if (index > (sphereNumber - 1))
					index = 0;

				currentTransform = &(s.obj.at(index).transform);

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