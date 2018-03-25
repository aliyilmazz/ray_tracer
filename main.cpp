#include "Scene.h"
#include <iostream>
#include <cstring>

using namespace std;

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Please provide scene and camera files" << std::endl;
        return 1;
    }   

    if (ReadScene(argc,argv)) return -1;
 //   CurrentScene->sceneData();

    for (const auto& camera : CurrentScene->Cameras())
    {
         Image img = camera.Render();

         ///////////////////////
         // BEWARE !
         // RUN YOUR TESTS HERE!
         ///////////////////////

         std::ofstream out(camera.OutputFile());
         out << img;
    }
    
   delete CurrentScene;
    return 0;
}