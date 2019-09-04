/**
* @file geometry_headers.hpp
* @brief Header of all the files related to the geometry
*
* @section LICENSE
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR/AUTHORS BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
* THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* @original author Alessandro Moro
* @bug No known bugs.
* @version 0.1.2.0
*
*/

#ifndef CMNMATH_GEOMETRY_GEOMETRYHEADERS_HPP__
#define CMNMATH_GEOMETRY_GEOMETRYHEADERS_HPP__

#include "parametric_twodim_circle.hpp"

#include "vector_operation.hpp"
#include "vector_operation_xyz.hpp"

#include "sign_zerodim_point.hpp"
#include "generator_zerodim_loxodrome.hpp"
#include "generator_zerodim_ellipse.hpp"
#include "generator_zerodim_icosphere.hpp"
#include "distance_zerodim_point.hpp"
#include "subset_zerodim_point.hpp"
#include "transform_zerodim_point.hpp"
#include "transform_twodim_triangle.hpp"

#include "contain_onedim.hpp"
#include "distance_onedim_line.hpp"
#include "distance_threedim_sphere.hpp"
#include "intersection_onedim_linexy.hpp"
#include "intersection_onedim_linexyz.hpp"

#include "projection_onedim_linexy.hpp"
#include "projection_onedim_linexyz.hpp"
#include "projection_threedim_sphere.hpp"

#include "intersection_twodim_plane.hpp"
#include "intersection_twodim_triangle.hpp"
#include "intersection_twodim_trianglexyz.hpp"
#include "intersection_twodim_ellipse.hpp"
#include "intersection_twodim_circle.hpp"

#include "intersection_threedim_sphere.hpp"

#include "barycentric_twodim_trianglexyz.hpp"

#include "bisection_onedim_line.hpp"
#include "bisection_twodim_arcnaive.hpp"

#include "orientation_zerodim.hpp"
#include "rotation2d.hpp"

#include "area_twodim_triangle.hpp"

#include "normal_threedim_surface.hpp"

#endif /* CMNMATH_GEOMETRY_GEOMETRYHEADERS_HPP__ */
