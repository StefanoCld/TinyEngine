#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "transform.h"
#include "shapes3d.h"
#include "camera.h"

namespace mgd {

    class GameObj {
    public:
        Transform transform;

        Sphere body, nose;

        GameObj() :
            transform(),
            body(Vector3(0, 0, 0), 1),
            nose(Vector3(1, 0, 0), 0.7)
        {
        }
    };

    class Scene {
    public:

        std::vector<GameObj> obj; // a set with GameObj (each with its own transform)

		Disk floorDisk = Disk(Vector3(0, -1, 6), Vector3(0, 1, 0), 2);

        // use this method to fill the scene with objects
        void populate() {
            GameObj someoneNew;
            someoneNew.transform.translate = Vector3(0, 0, 6);
            obj.push_back(someoneNew);
            GameObj someoneNew2;
            someoneNew2.transform.translate = Vector3(0, 0, -6);
            obj.push_back(someoneNew2);
            GameObj someoneNew3;
            someoneNew3.transform.translate = Vector3(6, 0, 0);
            obj.push_back(someoneNew3);
            GameObj someoneNew4;
            someoneNew4.transform.translate = Vector3(-6, 0, 0);
            obj.push_back(someoneNew4);
        }

        // produces a vector of spheres in world space
        std::vector<Sphere> toWorld() const {
            std::vector<Sphere> res;
            res.clear();

            for (const GameObj& g : obj) {
                res.push_back(apply(g.transform, g.nose));
                res.push_back(apply(g.transform, g.body));
            }
            return res;
        }

        std::vector<Sphere> toView(Transform camera) const {
            std::vector<Sphere> res;
            res.clear();

            camera.invert();

            for (const GameObj& g : obj) {
                res.push_back(apply(camera * g.transform, g.nose));
                res.push_back(apply(camera * g.transform, g.body));
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

    void rayCasting(const std::vector<Sphere>& sphereVector) {
        Camera c(2.0, 44, 44);

        std::string screenBuffer; // a string to get ready and print all at once

        for (int y = 0; y < c.pixelDimY; y++) {
            for (int x = 0; x < c.pixelDimX; x++) {
                Point3 hitPos;
                Point3 hitNorm;
                Scalar distMax = 1000.0;

                for (Sphere s : sphereVector) {
                    rayCast(c.primaryRay(x, y), s, hitPos, hitNorm, distMax);
                }

                screenBuffer += lighting(hitNorm);
            }
            screenBuffer += "\n";
        }
        std::cout << screenBuffer;
    }
}
// end of namespace mgd
