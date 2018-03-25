#ifndef RAYTRACER_TRIANGLE_H
#define RAYTRACER_TRIANGLE_H

#include "Ray.h"

class Triangle
{
public:
    Vector3 _a, _b, _c;
    int material_id;
    // This function gets a ray, and if the triangle intersects with the ray, returns true and fills the hitInfo struct
    // Else return false and leave hitInfo unchanged
    Triangle(Vector3 __a,Vector3 __b,Vector3 __c, int mid): _a(__a), _b(__b), _c(__c), material_id(mid) {}
    Vector3 a() {return _a;}
    Vector3 b() {return _b;}
    Vector3 c() {return _c;}
    bool Intersect(const Ray& ray, RayHitInfo& hitinfo) const
    {
        // cout << "ucgen noktalari -a,b,c-:" << endl;
        // cout << "a: " << _a << "b: " << _b << "c: " << _c << endl;
        // cout << "ray noktalari -o,d-:" << endl;
        // cout << ray.Origin() << ray.Direction() << endl;
            /*************key**************
            a = xa-xb, b = ya-yb, c = za-zb
            d = xa-xc, e = ya-yc, f = za-zc
            g,h,i = xd,yd,zd
            j,k,l = xa-xe, ya-ye, za-ze
            γ = i(ak − jb) + h(jc − al) + g(bl − kc)  /  M
            β = j(ei − hf) + k(gf − di) + l(dh − eg)  /  M
            t = −f(ak − jb) + e(jc − al) + d(bl − kc) / M 
            M = a(ei − hf) + b(gf − di) + c(dh − eg). 
            ******************************/
        float a = _a.x()-_b.x();            // xa-xb
        float b = _a.y()-_b.y();            // ya-yb
        float c = _a.z()-_b.z();            // za-zb
        float d = _a.x()-_c.x();            // xa-xc
        float e = _a.y()-_c.y();            // ya-yc
        float f = _a.z()-_c.z();            // za-zc
        float g = ray.Direction().x();      // xd
        float h = ray.Direction().y();      // yd
        float i = ray.Direction().z();      // zd
        float j = _a.x()-ray.Origin().x();  // xa-xe
        float k = _a.y()-ray.Origin().y();  // ya-ye
        float l = _a.z()-ray.Origin().z();  // za-ze
        float M = a*(e*i-h*f) + b*(g*f-d*i) + c*(d*h-e*g);
        float gamma = (i*(a*k-j*b) + h*(j*c-a*l) + g*(b*l-k*c)) / M;
        // cout << "xa-xb: " << a << endl;
        // cout << "ya-yb: " << b << endl;
        // cout << "za-zb: " << c << endl;
        // cout << "xa-xc: " << d << endl;
        // cout << "ya-yc: " << e << endl;
        // cout << "za-zc: " << f << endl;
        // cout << "xd: " << g << endl;
        // cout << "yd: " << h << endl;
        // cout << "zd: " << i << endl;
        // cout << "xa-xe: " << j << endl;
        // cout << "ya-ye: " << k << endl;
        // cout << "za-ze: " << l << endl;
        // cout << "M: " << M << endl;
        // cout << "gamma: " << gamma << endl;
        if (gamma<0 || gamma > 1) {/* cout << "gamma sıçtı return false" << endl; */return false; }
        float beta = (j*(e*i-h*f) + k*(g*f-d*i) + l*(d*h-e*g)) / M;
        // cout << "beta: " << beta << endl;
        if (beta<0 || beta > (1-gamma)) { return false; }
        // fill hitinfo here
        // cout << "anaa messi laaaeegg!!  " << endl;
        // cout << "messiiggg!!  " << endl;
        // cout << "atacanmi bugun!??!  " << endl;
        float ucgen_hittime = -1*((f*(a*k-j*b) + e*(j*c-a*l) + d*(b*l-k*c)) / M);


        if (hitinfo.golgeflag) // golgem varsa buraya gir, 0.1 arasindaysa bakip isini gor cik hitinfolarıma bulasma.
        {
            if (ucgen_hittime > 0 && ucgen_hittime < 1) // lightrayi kesiyor.
            {
                return true;
            }
            else
            {
                return false;
            }
        }


        if (ucgen_hittime > 0 && ucgen_hittime < LONG_MAX)
        {
            if (ucgen_hittime < hitinfo.Parameter)
            {
                hitinfo.Parameter = ucgen_hittime;
                hitinfo.material_id =  material_id;
                hitinfo.Position = ray.Origin() + ray.Direction()*hitinfo.Parameter;
                Vector3 normal_1 = _a-hitinfo.Position;
                Vector3 normal_2 = _b-hitinfo.Position;
                hitinfo.Normal = normalize(crossProduct(normal_1, normal_2));
            }
            // if ((hitinfo.Normal * ray.Direction()) > 0.0f) { hitinfo.Normal = (hitinfo.Normal * -1); } // normal negate
            return true;
        }
        else
        {
            return false;
        }
        // cout << "time: " << ucgxen_hittime << endl;
     }

    friend std::ostream& operator<<(std::ostream& os, Triangle& tri)
    {
        os << tri.a() << " " << tri.b() << " " << tri.c();
        return os;
    }
};

#endif //RAYTRACER_TRIANGLE_H

