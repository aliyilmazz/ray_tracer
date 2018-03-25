#include "Scene.h"

Scene* CurrentScene;


void Scene::sceneData()
{
    cout << "Printing Scene Data..." << endl;
    cout << "Ray Reflect Value: " << _rayReflect << endl;
    cout << "Background Color (RGB): " << _background << endl;
    cout << "Ambient Intensity (RGB): " << _ambient << endl;
    cout << "PointLight Count: " << _lights.size() << endl;
    cout << "PointLights: " << endl;
    for(vector<PointLight>::iterator it_pl = _lights.begin(); it_pl!=_lights.end(); ++it_pl){cout << *it_pl << endl;}
    cout << "Materials: " << endl;
    for(vector<Material>::iterator it_mat = _materials.begin(); it_mat!=_materials.end(); ++it_mat){cout << *it_mat << endl << endl;}
  //  cout << "Vectors: " << endl;
  //  for(vector<Vector3>::iterator it_vec = _vectors.begin(); it_vec!=_vectors.end(); ++it_vec){cout << *it_vec << endl;}
 //   cout << "Meshes: " << endl;
  //  for(vector<Mesh>::iterator it_mesh = _meshes.begin(); it_mesh!=_meshes.end(); ++it_mesh){cout << *it_mesh << endl;}
    cout << "Spheres: " << endl;
    for(vector<Sphere>::iterator it_sph = _spheres.begin(); it_sph!=_spheres.end(); ++it_sph){cout << *it_sph << endl;}
    cout << "Cameras: " << endl;
    for(vector<Camera>::iterator it_cam = _cameras.begin(); it_cam!=_cameras.end(); ++it_cam){cout << *it_cam << endl;}
}

int ReadScene(int argc, char** argv)
{
    ifstream scenefile(argv[1]);
    ifstream camerafile(argv[2]);
    string line;

    int pointlight_count;           // #
    PointLight* temppl;             // pos,int
    Vector3 temp_lightpos;
    Color temp_lightint;

    int material_count;             // # 
    string hashtag_material;        // #Material 1
    int material_id;                // amb,dif,spec,refl.
    Material* tempmat;
    Color mat_tempambient;
    Color mat_tempdiffuse;
    Color mat_tempspecular;
    Color mat_tempreflectance;
    float mat_tempspecexp;

    int vector_count;
    string hashtag_vertex;
    string vertex_data;
    Vector3* tempvec;
    float vecx, vecy, vecz;

    int model_count;
    string hashtag_string;

    Mesh* tempmesh;
    int mesh_id;
    int mesh_tempvecindex1;        // 5 6 7 dedi mesela. arrayde 5. 6. 7. indexlere gitcem bunla.
    int mesh_tempvecindex2;        // 5 6 7 dedi mesela. arrayde 5. 6. 7. indexlere gitcem bunla.
    int mesh_tempvecindex3;        // 5 6 7 dedi mesela. arrayde 5. 6. 7. indexlere gitcem bunla.
    int mesh_temptrianglecount;
    int mesh_tempmaterialid;

    Sphere* tempsphere;
    int sphere_id;
    int sphere_tempmatid;
    float sphere_tempradius;
    int sphere_tempcenterindex;

    if(scenefile)
    {
        CurrentScene = new Scene();
        scenefile >> CurrentScene->_rayReflect;
        scenefile >> CurrentScene->_background;
        scenefile >> CurrentScene->_ambient;
        scenefile >> pointlight_count;
        while(pointlight_count)
        {
            scenefile >> temp_lightpos >> temp_lightint;
            temppl = new PointLight(temp_lightpos, temp_lightint);
            CurrentScene->_lights.push_back(*temppl);
            delete temppl;
            pointlight_count--;
        }
        scenefile >> material_count;
        while(material_count)
        {
            scenefile >> hashtag_material >> material_id;
            scenefile >> mat_tempambient >> mat_tempdiffuse >> mat_tempspecular >> mat_tempspecexp >> mat_tempreflectance;
            tempmat = new Material(mat_tempambient, mat_tempdiffuse, mat_tempspecular, mat_tempspecexp, mat_tempreflectance);
            CurrentScene->_materials.push_back(*tempmat);
            delete tempmat;
            material_count--;
        }
        scenefile >> vector_count;
        scenefile >> hashtag_vertex >> vertex_data;
        while(vector_count)
        {
            scenefile >> vecx >> vecy >> vecz;
            tempvec = new Vector3(vecx, vecy, vecz);
            CurrentScene->_vectors.push_back(*tempvec);
            delete tempvec;
            vector_count--;
        }
        scenefile >> model_count;
        while(model_count)
        {
            scenefile >> hashtag_string;
            if (hashtag_string == "#Mesh")
            {
                scenefile >> mesh_id;
                scenefile >> mesh_temptrianglecount >> mesh_tempmaterialid;
                tempmesh = new Mesh(mesh_temptrianglecount, mesh_tempmaterialid);
                while(mesh_temptrianglecount)
                {
                    scenefile >> mesh_tempvecindex1 >> mesh_tempvecindex2 >> mesh_tempvecindex3;
                    mesh_tempvecindex1--; // 5 6 7, arrayde [4], [5], [6] oluyo.
                    mesh_tempvecindex2--; // 5 6 7, arrayde [4], [5], [6] oluyo.
                    mesh_tempvecindex3--; // 5 6 7, arrayde [4], [5], [6] oluyo.
                    tempmesh->AddTriangle(CurrentScene->_vectors[mesh_tempvecindex1],CurrentScene->_vectors[mesh_tempvecindex2], CurrentScene->_vectors[mesh_tempvecindex3]);
                    mesh_temptrianglecount--;
                }
                CurrentScene->_meshes.push_back(*tempmesh);
                delete tempmesh;
            }
            if (hashtag_string == "#Sphere")
            {
                scenefile >> sphere_id;
                scenefile >> sphere_tempmatid >> sphere_tempradius >> sphere_tempcenterindex;
                sphere_tempcenterindex--; // vid1 için 1 diyosa arrayde [0] şeklinde
                tempsphere = new Sphere(CurrentScene->_vectors[sphere_tempcenterindex], sphere_tempradius, sphere_tempmatid);
                CurrentScene->_spheres.push_back(*tempsphere);
                delete tempsphere;
            }
            model_count--;
        }
        scenefile.close();
    }
    else 
    { 
        cout << "error reading scenefile! exiting with status -1..." << endl;
        return -1;
    }


    Camera* tempcam;
    int camera_count;
    string hashtag_camera;
    int camera_id;
    Vector3* cam_temppos;
    Vector3* cam_tempgaze;
    Vector3* cam_tempup;
    float cam_left, cam_right, cam_bottom, cam_top, cam_distance;
    int cam_horres, cam_verres;
    string cam_outputfile; 
    if(camerafile)
    {
        camerafile >> camera_count;
        while(camera_count)
        {
            camerafile >> hashtag_camera >> camera_id;
            camerafile >> vecx >> vecy >> vecz;
            cam_temppos = new Vector3(vecx, vecy, vecz);
            camerafile >> vecx >> vecy >> vecz;
            cam_tempgaze = new Vector3(vecx, vecy, vecz);
            camerafile >> vecx >> vecy >> vecz;
            cam_tempup = new Vector3(vecx, vecy, vecz);
            camerafile >> cam_left >> cam_right >> cam_bottom >> cam_top >> cam_distance;
            camerafile >> cam_horres >> cam_verres >> cam_outputfile;
            tempcam = new Camera(*cam_temppos, *cam_tempgaze, *cam_tempup, cam_left, cam_right, cam_bottom, cam_top, cam_distance, cam_horres, cam_verres, cam_outputfile);
            CurrentScene->_cameras.push_back(*tempcam);
            delete cam_temppos;
            delete cam_tempgaze;
            delete cam_tempup;
            delete tempcam;
            camera_count--;
        }
    }
    else
    {
        cout << "error reading camerafile! exiting with status -2..." << endl;
        return -1;
    }
    return 0;
}
