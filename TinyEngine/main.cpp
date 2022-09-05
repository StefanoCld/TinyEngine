#include <windows.h>
#include <iostream>
#include <conio.h>
#include <chrono>

#include "camera.h"
#include "quaternion.h"
#include "scene.h"

using namespace mgd;

int main() {
	
	// scene stuff
	Scene s;
	s.populate();

	unsigned int objNumber = s.obj.size();
	unsigned int index = 0;

	// game object reference
	Transform* currentTransform = &(s.obj.at(index)->transform);
	
	// external camera 
	Transform t = Transform();

	// caching variables
	char key_press;
	int ascii_value;
	bool isFirstPerson = false;

	// movement multipliers
	const float deltaMov = 0.3f;
	const float deltaRot = 3.f;

	// first render
	rayCasting(s.toWorld());

	while (1)
	{
		////////
		///Relative Coordinates - Game Object
		////////

		if (isFirstPerson) {
			key_press = _getch();
			ascii_value = key_press;

			// w - Forward
			if (ascii_value == 119) {
				//wasd movement
				currentTransform->translate += currentTransform->forward() * deltaMov;

				// 
				//prevents memory leak
				std::vector<Entity*> tempVec;
				tempVec.clear();

				tempVec = s.toView(*currentTransform);

				rayCasting(tempVec);

				for (Entity* e : tempVec)
					delete e;
			}
			
			// s - Backward
			else if (ascii_value == 115) {
				//wasd movement
				currentTransform->translate -= currentTransform->forward() * deltaMov;

				// 
				//prevents memory leak
				std::vector<Entity*> tempVec;
				tempVec.clear();
				tempVec = s.toView(*currentTransform);

				rayCasting(tempVec);

				for (Entity* e : tempVec)
					delete e;
			}

			// a
			else if (ascii_value == 97) {
				//rotating
				currentTransform->rotate = currentTransform->rotate * Quaternion::fromAngleAxis(-deltaRot, Vector3(0, 1, 0));

				//wasd movement
				//currentTransform->translate -= currentTransform->right() * deltaMov;

				// 
				//prevents memory leak
				std::vector<Entity*> tempVec;
				tempVec.clear();
				tempVec = s.toView(*currentTransform);

				rayCasting(tempVec);

				for (Entity* e : tempVec)
					delete e;
			}

			// d
			else if (ascii_value == 100) {
				//rotating
				currentTransform->rotate = currentTransform->rotate * Quaternion::fromAngleAxis(deltaRot, Vector3(0, 1, 0));
				
				//wasd movement
				//currentTransform->translate -= currentTransform->right() * -deltaMov;
				
				// 
				//prevents memory leak
				std::vector<Entity*> tempVec;
				tempVec.clear();
				tempVec = s.toView(*currentTransform);

				rayCasting(tempVec);

				for (Entity* e : tempVec)
					delete e;
			}
			
			// g - Change to External Camera
			else if (ascii_value == 103) {
				isFirstPerson = false;
				rayCasting(s.toView(t));
			}

			// n - Select next Game Object
			else if (ascii_value == 110) {
				index++;
				if (index > (objNumber - 1))
					index = 0;

				currentTransform = &(s.obj.at(index)->transform);

				rayCasting(s.toView(*currentTransform));
			}
			
		}
		
		////////
		///Relative Coordinates - External Camera
		////////
		else {
			key_press = _getch();
			ascii_value = key_press;

			// w
			if (ascii_value == 119) {
				t.translate += t.forward() * deltaMov;

				//prevents memory leak
				std::vector<Entity*> tempVec;
				tempVec.clear();
				tempVec = s.toView(t);

				rayCasting(tempVec);

				for (Entity* e : tempVec)
					delete e;
			}

			// s
			else if (ascii_value == 115) {
				t.translate -= t.forward() * deltaMov;

				//prevents memory leak
				std::vector<Entity*> tempVec;
				tempVec.clear();
				tempVec = s.toView(t);

				rayCasting(tempVec);

				for (Entity* e : tempVec)
					delete e;
			}

			// a
			else if (ascii_value == 97) {
				t.rotate = t.rotate * Quaternion::fromAngleAxis(-deltaRot, Vector3(0, 1, 0));

				//prevents memory leak
				std::vector<Entity*> tempVec;
				tempVec.clear();
				tempVec = s.toView(t);

				rayCasting(tempVec);

				for (Entity* e : tempVec)
					delete e;
			}

			// d
			else if (ascii_value == 100) {
				t.rotate = t.rotate * Quaternion::fromAngleAxis(deltaRot, Vector3(0, 1, 0));

				//prevents memory leak
				std::vector<Entity*> tempVec;
				tempVec.clear();
				tempVec = s.toView(t);

				rayCasting(tempVec);

				for (Entity* e : tempVec)
					delete e;
			}

			// g - Change to GameObject
			else if (ascii_value == 103) {
				isFirstPerson = true;
				rayCasting(s.toView(*currentTransform));
			}
		}
	}
}