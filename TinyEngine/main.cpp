#include <windows.h>
#include <iostream>
#include <conio.h>
#include <chrono>

#include "camera.h"
#include "quaternion.h"
#include "scene.h"
#include "utils.h"

using namespace mgd;

int main() {
	
	// scene stuff
	Scene s;
	s.populate();

	unsigned int objNumber = s.obj.size();
	unsigned int index = 0;

	// no objects in the scene
	if (objNumber <= 0) {
		std::cout << "The scene is empty!" << std::endl;
		return -1;
	}

	// game object reference
	Entity* currentEntity = (s.obj.at(index));
	
	// external camera cache
	Transform t = Transform();
	//t.translate = Vector3(0, 0, 0);

	// caching variables
	char key_press;
	int ascii_value;
	bool isFirstPerson = false;

	// movement multipliers
	const float deltaMov = 0.3f;
	const float deltaRot = 5.f;

	// first render
	//rayCasting(s.toWorld());

	// intro menu
	std::cout << "W/S to move" << std::endl;
	std::cout << "A/D to rotate" << std::endl;
	std::cout << "G to switch to Game Object Mode / External Camera Mode" << std::endl;
	std::cout << "N to go to the next Game Object" << std::endl;

	while (1)
	{
		/////////////////////////////////////
		///Relative Coordinates - Game Object
		/////////////////////////////////////

		if (isFirstPerson) {
			key_press = _getch();
			ascii_value = key_press;

			// w - Forward
			if (ascii_value == 119) {

				currentEntity->Move(Axis::forward, deltaMov);

				//prevents memory leak
				std::vector<Entity*> tempVec;
				tempVec.clear();

				//tempVec = s.toView(*currentTransform);
				tempVec = s.toView(currentEntity->transform);

				rayCasting(tempVec);

				for (Entity* e : tempVec)
					delete e;

				std::cout << "Camera mode: First person - Object n�= " << index << std::endl;
			}
			
			// s - Backward
			else if (ascii_value == 115) {

				currentEntity->Move(Axis::forward, -deltaMov);

				//prevents memory leak
				std::vector<Entity*> tempVec;
				tempVec.clear();

				//tempVec = s.toView(*currentTransform);
				tempVec = s.toView(currentEntity->transform);

				rayCasting(tempVec);

				for (Entity* e : tempVec)
					delete e;

				std::cout << "Camera mode: First person - Object n�= " << index << std::endl;
			}

			// a
			else if (ascii_value == 97) {

				currentEntity->Rotate(Axis::up, -deltaRot);

				//prevents memory leak
				std::vector<Entity*> tempVec;
				tempVec.clear();

				//tempVec = s.toView(*currentTransform);
				tempVec = s.toView(currentEntity->transform);

				rayCasting(tempVec);

				for (Entity* e : tempVec)
					delete e;

				std::cout << "Camera mode: First person - Object n�= " << index << std::endl;
			}

			// d
			else if (ascii_value == 100) {

				currentEntity->Rotate(Axis::up, deltaRot);
 
				//prevents memory leak
				std::vector<Entity*> tempVec;
				tempVec.clear();

				//tempVec = s.toView(*currentTransform);
				tempVec = s.toView(currentEntity->transform);

				rayCasting(tempVec);

				for (Entity* e : tempVec)
					delete e;

				std::cout << "Camera mode: First person - Object n�= " << index << std::endl;
			}
			
			// g - Change to External Camera
			else if (ascii_value == 103) {

				isFirstPerson = false;
				rayCasting(s.toView(t));

				std::cout << "Camera mode: External" << std::endl;
			}

			// n - Select next Game Object
			else if (ascii_value == 110) {

				index++;
				if (index > (objNumber - 1))
					index = 0;

				currentEntity = (s.obj.at(index));
				
				while (!(currentEntity->CanBePossessed())) 
				{
					index++;
					if (index > (objNumber - 1))
						index = 0;

					currentEntity = (s.obj.at(index));
				}
				
				rayCasting(s.toView(currentEntity->transform));
				std::cout << "Camera mode: First person - Object n�= " << index << std::endl;
			}
		}

		/////////////////////////////////////////
		///Relative Coordinates - External Camera
		/////////////////////////////////////////

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

				std::cout << "Camera mode: External";
				//std::cout << "Camera mode: External" << std::endl;
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

				std::cout << "Camera mode: External";
				//std::cout << "Camera mode: External" << std::endl;
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

				std::cout << "Camera mode: External";
				//std::cout << "Camera mode: External" << std::endl;
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

				std::cout << "Camera mode: External";
				//std::cout << "Camera mode: External" << std::endl;
			}

			// g - Change to GameObject
			else if (ascii_value == 103) {

				isFirstPerson = true;

				currentEntity = (s.obj.at(index));

				while (!(currentEntity->CanBePossessed()))
				{
					index++;
					if (index > (objNumber - 1))
						index = 0;

					currentEntity = (s.obj.at(index));
				}

				//rayCasting(s.toView(*currentTransform));
				rayCasting(s.toView(currentEntity->transform));
				std::cout << "Camera mode: First person - Object n�= " << index << std::endl;
			}
		}
	}
}