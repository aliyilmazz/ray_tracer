#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

#include "Ray.h"
#include <climits>

using namespace std;

class Sphere {
	
public:

	Vector3 _center;
    float _r;
    int material_id;

    // This function gets a ray, and if the sphere intersects with the ray, returns true and fills the hitInfo struct
    // Else return false and leave hitInfo unchanged
    Sphere(Vector3 mycenter, float myr, int matid): _center(mycenter), _r(myr), material_id(matid) {}
    
    Vector3 Center() {return _center;}
    float R(){return _r;}
    int MID(){return material_id;}

    bool Intersect(Ray& ray, RayHitInfo& hitinfo) const
    {
        float a = ray.Direction()*ray.Direction();
        float b = (ray.Direction()*2)*(ray.Origin()-_center);
        float c = (ray.Origin()-_center)*(ray.Origin()-_center)-(_r*_r);
        float discriminant = b*b-4*a*c;
        float temptime, temptime1, temptime2;
        temptime1 = ((-1*b)-sqrt(discriminant)) / (2*a);
        temptime2 = ((-1*b)+sqrt(discriminant)) / (2*a);
        if (discriminant!=0)
        {
            if (temptime1<=0 && temptime2 <=0) { return false; }
            if (temptime1<=0) {temptime1=LONG_MAX;}
            if (temptime2<=0) {temptime2=LONG_MAX;}
            temptime = fmin(temptime1,temptime2);
        }
        else
        {
            temptime = temptime1;
        }
        if (hitinfo.golgeflag)
        {
            if (temptime > 0 && temptime < 1)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        if (temptime > 0 && temptime < LONG_MAX)
        {
            if (temptime < hitinfo.Parameter)
            {
                hitinfo.Parameter = temptime;
                hitinfo.Position = ray.Origin() + ray.Direction()*temptime;
                hitinfo.material_id = material_id;
                hitinfo.Normal = (hitinfo.Position - _center) / _r;
            }
            return true;
        }
        else
        {
            return false;
        }
    }
    friend ostream& operator<<(ostream& os, Sphere& sph)
    {
        os << "Center: " << sph.Center() << " R: " << sph.R() << " MatID: " << sph.MID(); 
        return os;
    }
};

        // a = (d.d)
        // b = (2*d).(e-c)
        // c = (e-c).(e-c)-R^2
        // cout << "a: " << a << endl;
        // cout << "b: " << b << endl;
        // cout << "c: " << c << endl;  
        // if (discriminant < 0) cout << "delta<0, no soln!" << endl;
        // if (discriminant == 0) cout << "delta=0, teget!" << endl;
        // if (discriminant > 0) cout << "delta>0, 2 solns!" << endl;
        // cout << "delta= " << discriminant << endl;
        // cout << "temptime1: " << temptime1 << endl;
        // cout << "temptime2: " << temptime2 << endl;
        // cout << "temptime: " << temptime << endl;

#endif //RAYTRACER_SPHERE_H
