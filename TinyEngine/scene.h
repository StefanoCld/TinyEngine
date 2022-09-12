#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "transform.h"
#include "shapes3d.h"
#include "camera.h"
#include "entity.h" 
#include "sphereEntity.h"
#include "diskEntity.h"
#include "planeEntity.h"

namespace mgd {

    class Scene {
    public:

		std::vector<Entity*> obj;

        void populate() {
            /*
            for (int j = 0; j < 5; j++) 
            {
				Entity* someoneNew = new DiskEntity(2);
                someoneNew->transform.translate = Vector3(0, -2, 5*j);
				obj.push_back(someoneNew);
            }
            
			for (int j = 0; j < 5; j++)
			{
				Entity* someoneNew = new SphereEntity(2);
				someoneNew->transform.translate = Vector3(-4, 0, 5 * j);
				obj.push_back(someoneNew);
			}
            */
            /*
			for (int j = 0; j < 5; j++)
			{
				Entity* someoneNew = new SphereEntity(2);
				someoneNew->transform.translate = Vector3(5, 0, 5 * j);
				obj.push_back(someoneNew);
			}
            */

			Entity* someoneNew = new SphereEntity(2);
			someoneNew->transform.translate = Vector3(0, 0, 5);
			obj.push_back(someoneNew);

			Entity* someoneNew2 = new PlaneEntity();
			someoneNew2->transform.translate = Vector3(0, -2, 0);
			obj.push_back(someoneNew2);
		}

        std::vector<Entity*> toWorld() const {
            std::vector<Entity*> res;
            res.clear();

            for (Entity* g : obj) {
                res.push_back(g->apply(Transform()));
            }
            return res;
        }

        std::vector<Entity*> toView(Transform camera) const {
            std::vector<Entity*> res;
            res.clear();

            camera.invert();

			for (Entity* g : obj) {
                Entity* e = g->apply(camera);
				res.push_back(e);
			}

            return res;
        };
    };

    // ascii art: convert an intensity value (0 to 1) into a sequence of two chars
    const char* intensityToCstr(float intensity) {
        switch (int(round(intensity * 8))) {
        case 0: return "  "; // darkest
        case 1: return " '";
        case 2: return " +";
        case 3: return " *";
        case 4: return " #";
        case 5: return "'#";
        case 6: return "+#";
        case 7: return "*#";
        case 8: return "##"; // lightest
        default:
        case 10: return "##";
        }
    }

    const char* lighting(Vector3 normal) {
        Vector3 lightDir = Vector3(1, 2, -2).normalized();

        float diffuse = dot(normal, lightDir);
        if (diffuse < 0) diffuse = 0;

        return intensityToCstr(diffuse);
    }

    void rayCasting(const std::vector<Entity*> entityVector, Vector3 watcherPos) {
        Camera c(2.0, 44, 44);
        std::string screenBuffer; // a string to get ready and print all at once

        for (int y = 0; y < c.pixelDimY; y++) {
            for (int x = 0; x < c.pixelDimX; x++) {
                Vector3 hitPos;
                Vector3 hitNorm;
                float distMax = 1000.0;
                float diffuse = 0;

                for (Entity* s : entityVector) {
					s->rayCast(c.primaryRay(x, y), hitPos, hitNorm, distMax);
                    diffuse = (s->Lighting(hitNorm, watcherPos));
                }

				//screenBuffer += lighting(hitNorm);
				screenBuffer += intensityToCstr(diffuse);
            }
            screenBuffer += "\n";
        }
        std::cout << screenBuffer;
    }
}
// end of namespace mgd