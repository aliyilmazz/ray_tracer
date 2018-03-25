#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include <iostream>
#include "Vector3.h"
#include "Image.h"
#include "Ray.h"


using namespace std;

class Camera {
  

public:

      struct {
        Vector3 Forward, Up, Right;
    } _space;

    struct {
        float Left, Right, Bottom, Top;
        float Distance;

        int Width;
        int Height;

    } _imagePlane;

    Vector3 _position;

    string _outputFile;


    Camera(Vector3 pos, Vector3 gaze, Vector3 _up, float _left, float _right, float _bottom, float _top, float _distance, int _horres, int _verres, string outp)
    {
        _position = pos;
        _space.Forward = gaze;
        _space.Up = _up;
        _space.Right = crossProduct(_space.Forward,_space.Up);
        _imagePlane.Left = _left;
        _imagePlane.Right = _right;
        _imagePlane.Bottom = _bottom;
        _imagePlane.Top = _top;
        _imagePlane.Distance = _distance;
        _imagePlane.Width = _horres;
        _imagePlane.Height = _verres;
        _outputFile = outp;
    }

    /*
     * BEWARE! You should render each camera by using this function, we will grade it according to regulations!
     */
    const std::string& OutputFile() const
    {
        return _outputFile;
    }
    
    friend ostream& operator<<(ostream& os, Camera& mycam)
    {
        os << "## Camera Info ##" << endl;
        os << "Position: " << mycam._position << endl;
        os << "Forward: " << mycam._space.Forward << endl;
        os << "Up: " << mycam._space.Up << endl;
        os << "Right: " << mycam._space.Right << endl;
        os << "Left-Right-Bottom-Top-Distance: " << mycam._imagePlane.Left 
                                          << " " << mycam._imagePlane.Right 
                                          << " " << mycam._imagePlane.Bottom 
                                          << " " << mycam._imagePlane.Top 
                                          << " " << mycam._imagePlane.Distance 
                                          << endl;
        os << "Width-Height: " << mycam._imagePlane.Width << " " << mycam._imagePlane.Height << endl;
        os << "OutputFileName: " << mycam._outputFile << endl;
        return os; 
    }

    Image Render() const;


};
    inline Color computeColor(RayHitInfo& hitinfo, Vector3 v);
    inline Color rayTrace(Ray& cameraray, int refl_count);

#endif //RAYTRACER_CAMERA_H
