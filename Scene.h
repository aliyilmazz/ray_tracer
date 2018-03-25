#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H

#include <vector>
#include "Camera.h"
#include "Sphere.h"
#include "Mesh.h"
#include "Color.h"
#include "PointLight.h"

using namespace std;

class Scene {


public:


    vector<Vector3> _vectors;
    vector<Camera> _cameras;
    vector<Sphere> _spheres;
    vector<Mesh>   _meshes;
    vector<Material> _materials;
    vector<PointLight> _lights;

    int _rayReflect;
    Color _background;
    Color _ambient;
    
    Scene(){}
    ~Scene(){}

    const std::vector<Camera>& Cameras() const {
        return _cameras;
    }
    const std::vector<PointLight>& Lights() const {
        return _lights;
    }

    void sceneData();


    //////////////////////////////
    // READ SCENE FUNCTIONS HERE !
    //////////////////////////////
};

extern Scene* CurrentScene;
int ReadScene(int argc, char** argv);


#endif //RAYTRACER_SCENE_H
