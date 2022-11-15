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
#include "triangleEntity.h"
#include "cylinderEntity.h"

namespace mgd 
{

    class Scene {
    public:
        // Scene's entities
		std::vector<Entity*> obj;

		// Sandbox function, used to populate the scene
        void populate() {
            templeScenePopulate();
		}

        void templeScenePopulate() {
            // Example scene

            // Disk floor
            Entity* someoneNew = new DiskEntity(15);
            someoneNew->transform.translate = Vector3(0, -2, 12);
            obj.push_back(someoneNew);
            
            // Cylinders! (Temple's columns)
			Transform e1;
			e1.translate = Vector3(-6, -2, 5);
			Entity* cy1 = new CylinderEntity(2, 5, e1);
			obj.push_back(cy1);

			Transform e2;
			e2.translate = Vector3(6, -2, 5);
			Entity* cy2 = new CylinderEntity(2, 5, e2);
			obj.push_back(cy2);

			Transform e3;
			e3.translate = Vector3(-6, -2, 15);
			Entity* cy3 = new CylinderEntity(2, 5, e3);
			obj.push_back(cy3);

		    Transform e4;
			e4.translate = Vector3(6, -2, 15);
			Entity* cy4 = new CylinderEntity(2, 5, e4);
			obj.push_back(cy4);

            // Spheres (can be moved!)
			Entity* sphere1 = new SphereEntity(1.5f);
            sphere1->transform.translate = Vector3(0, 0, 12);
			obj.push_back(sphere1);

			Entity* sphere2 = new SphereEntity(5.f);
            sphere2->transform.translate = Vector3(0, 10, 30);
			obj.push_back(sphere2);

            // floating Triangles!
			for (int i = 0; i < 3; i++)
			{
				Transform e;
				e.translate = Vector3(-3 + i*3, 3.f, 12);
				e.rotate = Quaternion::identity();

				Entity* triangle = new TriangleEntity(2, e);
				obj.push_back(triangle);
			}
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

    void rayCasting(const std::vector<Entity*> entityVector) {
        Camera c(2.0, 52, 52);
        std::string screenBuffer; // a string to get ready and print all at once

        for (int y = 0; y < c.pixelDimY; y++) {
            for (int x = 0; x < c.pixelDimX; x++) {
                Vector3 hitPos;
                Vector3 hitNorm;
                float distMax = 1000.0;
                float diffuse = 0;
                bool bHasHit = false;

                for (Entity* s : entityVector) 
                {
					bHasHit = s->rayCast(c.primaryRay(x, y), hitPos, hitNorm, distMax);
                    if(bHasHit)
                        diffuse = (s->Lighting(hitNorm));
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