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
	// scene stuff
	Scene s;
	s.populate();

	unsigned int sphereNumber = s.obj.size();
	unsigned int index = 0;

	// game object reference
	Transform* currentTransform = &(s.obj.at(index).transform);

	// caching variables
	char key_press;

	int ascii_value;

	bool isFirstPerson = false;
	bool isTransitioning = false;

	// movement multipliers
	const float deltaMov = 0.3f;
	const float deltaRot = 3.f;

	// current rotation amount (on Y-axis)
	float dX = 0.f;

	// external camera 
	Transform t = Transform();

	// first render
	rayCasting(s.toWorld());

	
	while (1)
	{
		////////
		// Relative Coordinates - Game Object
		////////
		if (isFirstPerson) {
			key_press = _getch();
			ascii_value = key_press;

			// w - Forward
			if (ascii_value == 119) {
				currentTransform->translate += currentTransform->forward() * deltaMov;

				rayCasting(s.toView(*currentTransform));
			}

			// s - Backward
			else if (ascii_value == 115) {
				currentTransform->translate -= currentTransform->forward() * deltaMov;

				rayCasting(s.toView(*currentTransform));
			}

			// a
			else if (ascii_value == 97) {
				dX -= deltaRot;
				currentTransform->rotate = Quaternion::fromAngleAxis(dX, Vector3(0, 1, 0));

				rayCasting(s.toView(*currentTransform));
			}

			// d
			else if (ascii_value == 100) {
				dX += deltaRot;
				currentTransform->rotate = Quaternion::fromAngleAxis(dX, Vector3(0, 1, 0));

				rayCasting(s.toView(*currentTransform));
			}

			// g - Change to External Camera
			else if (ascii_value == 103) {
				isFirstPerson = false;
				dX = 0.f;
				rayCasting(s.toView(Transform()));
			}

			// n - Select next Game Object
			else if (ascii_value == 110) {
				dX = 0.f;

				index++;
				if (index > (sphereNumber - 1))
					index = 0;

				currentTransform = &(s.obj.at(index).transform);

				rayCasting(s.toView(*currentTransform));
			}
		}
		
		////////
		// Relative Coordinates - External Camera
		////////
		else {
			key_press = _getch();
			ascii_value = key_press;

			// w
			if (ascii_value == 119) {
				t.translate += t.forward() * deltaMov;

				rayCasting(s.toView(t));
			}

			// s
			else if (ascii_value == 115) {
				t.translate -= t.forward() * deltaMov;

				rayCasting(s.toView(t));
			}

			// a
			else if (ascii_value == 97) {
				dX -= deltaRot;
				t.rotate = Quaternion::fromAngleAxis(dX, Vector3(0, 1, 0));

				rayCasting(s.toView(t));
			}

			// d
			else if (ascii_value == 100) {
				dX += deltaRot;
				t.rotate = Quaternion::fromAngleAxis(dX, Vector3(0, 1, 0));

				rayCasting(s.toView(t));
			}

			// g - Change to GameObject
			else if (ascii_value == 103) {
				isFirstPerson = true;
				dX = 0.f;
				rayCasting(s.toView(*currentTransform));
			}
		}
	}
	
}