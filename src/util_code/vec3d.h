//
// This file is released under the terms of the NASA Open Source Agreement (NOSA)
// version 1.3 as detailed in the LICENSE file which accompanies this software.
//

//******************************************************************************
//    
//   3D Point Double Class
//   
//   J.R. Gloudemans - 7/7/93
//******************************************************************************

#ifndef VEC3D_H
#define VEC3D_H

#include "defines.h"
#include "vec2d.h"

#include <iostream>
#include <vector>
using namespace std;

class vec3d;

//==== Forward declare to get around MS Compiler bug ====//
vec3d operator+(const vec3d& a, const vec3d& b);
vec3d operator-(const vec3d& a, const vec3d& b);
vec3d operator*(const vec3d& a, double b);
vec3d operator*(const vec3d& a, const vec3d& b);
vec3d operator/(const vec3d& a, double b); 

class VSPDLL vec3d
{
private:


public:
    double v[3];

     vec3d();			// vec3d x or new vec3d

    ~vec3d()  {}		// delete vec3d

     vec3d(double xx, double yy, double zz);

     vec3d(const vec3d& a);	// vec3d x = y

     vec3d& operator=(const vec3d& a);	// x = y
     vec3d& operator=(double a);		// x = 35.

 	double& operator [] (int i)					{ return v[i]; }
	const double& operator [] (int i) const		{ return v[i]; }


    // Set Point Values
     vec3d& set_xyz(double xx, double yy, double zz);
     vec3d& set_x(double xx);
     vec3d& set_y(double yy);
     vec3d& set_z(double zz);

    // Get Point Values
     void get_pnt(double pnt[3]) const	{ pnt[0] = v[0]; pnt[1] = v[1]; pnt[2] = v[2];  }
     void get_pnt(float  pnt[3]) const	{ pnt[0] = (float)v[0]; pnt[1] = (float)v[1]; pnt[2] = (float)v[2];  }
     double x()	const			{ return( v[0] ); }
     double y()	const			{ return( v[1] ); }
     double z()	const			{ return( v[2] ); }

	 double* data()				{ return( v ); }

    // Rotate About Axis --> Change Internal Values
    void rotate_x(double cos_alpha, double sin_alpha)	
	{ double old_y = v[1]; v[1] = cos_alpha*v[1] + sin_alpha*v[2];  v[2] = -sin_alpha*old_y + cos_alpha*v[2]; }
    void rotate_y(double cos_alpha, double sin_alpha)	
	{ double old_x = v[0]; v[0] = cos_alpha*v[0] - sin_alpha*v[2];  v[2] =  sin_alpha*old_x + cos_alpha*v[2]; }
    void rotate_z(double cos_alpha, double sin_alpha)	
	{ double old_x = v[0]; v[0] = cos_alpha*v[0] + sin_alpha*v[1];  v[1] = -sin_alpha*old_x + cos_alpha*v[1]; }

    // Scale Up Single Coord  --> Change Internal Values
    void scale_x(double scale)		{ v[0] *= scale; };
    void scale_y(double scale)		{ v[1] *= scale; };
    void scale_z(double scale)		{ v[2] *= scale; };

    void offset_x(double offset)		{ v[0] += offset; };
    void offset_y(double offset)		{ v[1] += offset; };
    void offset_z(double offset)		{ v[2] += offset; };

    // Rotate About Axis : Assume Zero Coord --> Change Internal Values
    void rotate_z_zero_x(double cos_alpha, double sin_alpha)	
	{ v[0] = sin_alpha*v[1] + v[0];  v[1] = cos_alpha*v[1]; }
    void rotate_z_zero_y(double cos_alpha, double sin_alpha)	
	{ v[0] = cos_alpha*v[0];  v[1] = -sin_alpha*v[0] + v[1]; }

    // Transform Matrix
    vec3d transform(float mat[4][4]);
    vec3d transform(double mat[4][4]);
    vec3d reflect_xy()			{ return(vec3d( v[0],  v[1], -v[2])); }
    vec3d reflect_xz()			{ return(vec3d( v[0], -v[1],  v[2])); }
    vec3d reflect_yz()			{ return(vec3d(-v[0],  v[1],  v[2])); }

    // x = a + b, x = a - b, a*scale, a/scale
    friend vec3d operator+(const vec3d& a, const vec3d& b);
    friend vec3d operator-(const vec3d& a, const vec3d& b);
    friend vec3d operator*(const vec3d& a, double b);
    friend vec3d operator*(const vec3d& a, const vec3d& b);
    friend vec3d operator/(const vec3d& a, double b);

    // cout << a			
//    friend ostream& operator<< (ostream& out, const vec3d& a);
  
    friend double dist(const vec3d& a, const vec3d& b);
    friend double dist_squared(const vec3d& a, const vec3d& b);

    double mag() const;                // x = a.mag()
    void normalize();           // a.normalize()
 
    friend double dot(const vec3d& a, const vec3d& b);   // x = dot(a,b)
    friend vec3d cross(const vec3d& a, const vec3d& b);  // a = cross(b,c)
    friend double angle(const vec3d& a, const vec3d& b); 
	friend double signed_angle(const vec3d& a, const vec3d& b, const vec3d& ref );
    friend double cos_angle(const vec3d& a, const vec3d& b);
    friend double radius_of_circle(vec3d& p1, vec3d& p2, vec3d& p3); 
    friend void center_of_circle(vec3d& p1, vec3d& p2, vec3d& p3, vec3d& center); 
    friend double dist_pnt_2_plane(vec3d& org, vec3d& norm, vec3d& pnt); 
    friend double dist_pnt_2_line(vec3d& line_pt1, vec3d& line_pt2, vec3d& pnt); 
 //   friend double dist_pnt_2_line_seg( vec3d& line_pt1,  vec3d& line_pt2,  vec3d& pnt); 
    friend vec3d proj_pnt_on_line_seg(const vec3d& line_pt1, const vec3d& line_pt2, const vec3d& pnt); 
    friend vec3d proj_pnt_on_ray(const vec3d& line_pt1, const vec3d& line_pt2, const vec3d& pnt); 
    friend vec3d proj_pnt_on_line(const vec3d& line_pt1, const vec3d& line_pt2, const vec3d& pnt); 
    friend vec3d proj_pnt_to_plane(vec3d& org, vec3d& plane_ln1, vec3d& plane_ln2, vec3d& pnt); 
    friend int tri_seg_intersect(vec3d& A, vec3d& B, vec3d& C, vec3d& D, vec3d& E, 
                 double& u, double& w, double& t); 
    friend int tri_ray_intersect(vec3d& A, vec3d& B, vec3d& C, vec3d& D, vec3d& E, 
                 double& u, double& w, double& t); 
    friend int plane_ray_intersect(vec3d& A, vec3d& B, vec3d& C, vec3d& D, vec3d& E, double& t); 
    friend int plane_ray_intersect(vec3d& orig, vec3d& norm, vec3d& D, vec3d& E, double& t); 
	friend int ray_ray_intersect(vec3d& A, vec3d& B, vec3d& C, vec3d& D, vec3d& int_pnt1, vec3d& int_pnt2); 
    friend double tetra_volume(vec3d& A, vec3d& B, vec3d& C);
    friend double area_squared(vec3d& A, vec3d& B, vec3d& C);
    friend double area(vec3d& A, vec3d& B, vec3d& C);
	friend double poly_area( vector< vec3d > & pnt_vec, vec3d& center );
	friend double dist3D_Segment_to_Segment( vec3d& S1P0, vec3d& S1P1, vec3d& S2P0, vec3d& S2P1);
	friend double dist3D_Segment_to_Segment( vec3d& S1P0, vec3d& S1P1, vec3d& S2P0, vec3d& S2P1, 
								 double* Lt, vec3d* Ln, double* St, vec3d* Sn );
	friend double nearSegSeg(const vec3d& L0,const vec3d& L1,const vec3d& S0,const vec3d& S1, double* Lt, vec3d* Ln, double* St,  vec3d* Sn );
	friend double pointLineDistSquared( vec3d & p, vec3d& lp0, vec3d& lp1, double* t );
	friend double pointSegDistSquared( vec3d& p, vec3d& sp0, vec3d& sp1, double* t );

	friend  vec2d MapToPlane( vec3d & p, vec3d & planeOrig, vec3d & planeVec1, vec3d & planeVec2 );
	friend  vec3d MapFromPlane( vec2d & uw, vec3d & planeOrig, vec3d & planeVec1, vec3d & planeVec2 );

 	friend int plane_half_space( vec3d & planeOrig, vec3d & planeNorm, vec3d & pnt );

	friend bool line_line_intersect( vec3d & p1, vec3d & p2, vec3d & p3, vec3d & p4, double* s, double* t );
    
	friend vec3d RotateArbAxis(vec3d & p, double theta, vec3d & r);

};

#endif


		
