#ifndef RAYTRACER_MESH_H
#define RAYTRACER_MESH_H

#include "Triangle.h"
#include <vector>

using namespace std;

class Mesh {


	public:
	int triangle_count;
	int material_id;
	vector<Triangle> triangles;

		Mesh(int tricount, int matid)
		{
			triangle_count = tricount;
			material_id = matid;
		}

		void AddTriangle(Vector3 v1, Vector3 v2, Vector3 v3)
		{
			Triangle a(v1,v2,v3,material_id);
			triangles.push_back(a);
		}

		friend ostream& operator<<(ostream& os, Mesh& mesh)
		{
			os << "triangle count: " << mesh.triangle_count << endl;
			os << "material id: " << mesh.material_id << endl;
			for(vector<Triangle>::iterator it_tri = mesh.triangles.begin(); it_tri!=mesh.triangles.end(); ++it_tri){os << *it_tri << endl;}
			return os;
 		}

        void Intersect(const Ray& ray, RayHitInfo& hitInfo)
        {
        	for(vector<Triangle>::iterator it_tri = triangles.begin(); it_tri!=triangles.end(); ++it_tri)
        	{
        		(*it_tri).Intersect(ray, hitInfo);
        	}
        }
};

#endif //RAYTRACER_MESH_H
