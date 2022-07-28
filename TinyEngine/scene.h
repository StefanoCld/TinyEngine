#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "camera.h"
#include "gameobj.h"
#include "sphere.h"

namespace mgd {

    class Scene {
    public:

        std::vector<GameObj*> obj; // a set with GameObj (each with its own transform)


        void populate() {
            Sphere* someoneNew = new Sphere();
            someoneNew->transform.translate = Vector3(0, 0, 6);
            obj.push_back(someoneNew);
			Sphere* someoneNew2 = new Sphere();
			someoneNew2->transform.translate = Vector3(0, 0, -6);
			obj.push_back(someoneNew2);
        }

        // produces a vector of spheres in world space
        std::vector<GameObj*> toWorld() const {
            std::vector<GameObj*> res;
            res.clear();

            for (GameObj* g : obj) {
                res.push_back(g->applyTransform(g->transform));
            }
            return res;

        }

        std::vector<GameObj*> toView(Transform camera) const {
            std::vector<GameObj*> res;
            res.clear();

            camera.invert();

			for (GameObj* g : obj) {
				res.push_back(g->applyTransform(camera * g->transform));
			}

            return res;
        };
    };

    // ascii art: convert an intensity value (0 to 1) into a sequence of two chars
    const char* intensityToCstr(Scalar intensity) {
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

    const char* lighting(Versor3 normal) {
        Versor3 lightDir = Versor3(1, 2, -2).normalized();

        Scalar diffuse = dot(normal, lightDir);
        if (diffuse < 0) diffuse = 0;

        return intensityToCstr(diffuse);
    }

    void rayCasting(const std::vector<GameObj*> sphereVector) {
        Camera c(2.0, 44, 44);

        std::string screenBuffer; // a string to get ready and print all at once

        for (int y = 0; y < c.pixelDimY; y++) {
            for (int x = 0; x < c.pixelDimX; x++) {
                Point3 hitPos;
                Point3 hitNorm;
                Scalar distMax = 1000.0;

                for (GameObj* g : sphereVector) {
                    g->rayCast(c.primaryRay(x, y), hitPos, hitNorm, distMax);
                }

                screenBuffer += lighting(hitNorm);
            }
            screenBuffer += "\n";
        }
        std::cout << screenBuffer;
    }
}
// end of namespace mgd
