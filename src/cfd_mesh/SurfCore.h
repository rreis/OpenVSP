//
// This file is released under the terms of the NASA Open Source Agreement (NOSA)
// version 1.3 as detailed in the LICENSE file which accompanies this software.
//

#if !defined(SURF_CORE__INCLUDED_)
#define SURF_CORE__INCLUDED_

#include "Vec3d.h"

#include "eli/code_eli.hpp"

#include "eli/geom/surface/bezier.hpp"
#include "eli/geom/surface/piecewise.hpp"
#include "eli/geom/curve/piecewise_creator.hpp"
#include "eli/geom/surface/piecewise_general_skinning_surface_creator.hpp"

typedef eli::geom::surface::bezier<double, 3> surface_patch_type;
typedef eli::geom::surface::piecewise<eli::geom::surface::bezier, double, 3> piecewise_surface_type;

typedef piecewise_surface_type::tolerance_type surface_tolerance_type;
typedef eli::geom::curve::piecewise_cubic_spline_creator<double, 3, surface_tolerance_type> piecewise_cubic_spline_creator_type;
typedef eli::geom::surface::connection_data<double, 3, surface_tolerance_type> rib_data_type;

#include <vector>
using std::vector;

//////////////////////////////////////////////////////////////////////
class SurfCore
{
public:

    SurfCore();
    virtual ~SurfCore();

    //===== Bezier Funcs ====//
    vec3d CompPnt( double u, double w );
    vec3d CompTanU( double u, double w );
    vec3d CompTanW( double u, double w );

    vec3d CompPnt01( double u, double w );
    vec3d CompTanU01( double u, double w );
    vec3d CompTanW01( double u, double w );

    void CompCurvature( double u, double w, double& k1, double& k2, double& ka, double& kg );

    double GetUWArea()
    {
        return GetMaxU() * GetMaxW();
    }

    int GetNumUPatches()
    {
        return m_Surface.number_u_patches();
    }
    int GetNumWPatches()
    {
        return m_Surface.number_v_patches();
    }
    double GetMaxU()
    {
        return m_Surface.get_umax();
    }
    double GetMaxW()
    {
        return m_Surface.get_vmax();
    }

    void SetControlPnts( vector< vector < vec3d > > pnts );
    vector< vector< vec3d > > GetControlPnts();


    bool LessThanY( double val );
    bool OnYZeroPlane();
    bool PlaneAtYZero();

    void LoadBorderCurves( vector< vector <vec3d> > & borderCurves );

    bool SurfMatch( SurfCore* otherSurf );

protected:

    int m_NumU;
    int m_NumW;

    piecewise_surface_type m_Surface;

    vec3d CompTanUU( double u, double w );
    vec3d CompTanWW( double u, double w );
    vec3d CompTanUW( double u, double w );
};

#endif