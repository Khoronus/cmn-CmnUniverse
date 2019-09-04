/**
* @file geometry_geometry.hpp
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
* @version 0.1.2.1
*
*/

#ifndef CMNMATH_GEOMETRY_GEOMETRY_HPP__
#define CMNMATH_GEOMETRY_GEOMETRY_HPP__

#include "inc/geometry/parametric_twodim_circle.hpp"

#include "inc/geometry/vector_operation.hpp"
#include "inc/geometry/vector_operation_xyz.hpp"

#include "inc/geometry/sign_zerodim_point.hpp"
#include "inc/geometry/generator_zerodim_loxodrome.hpp"
#include "inc/geometry/generator_zerodim_ellipse.hpp"
#include "inc/geometry/generator_zerodim_icosphere.hpp"
#include "inc/geometry/distance_zerodim_point.hpp"
#include "inc/geometry/subset_zerodim_point.hpp"
#include "inc/geometry/transform_zerodim_point.hpp"
#include "inc/geometry/transform_twodim_triangle.hpp"

#include "inc/geometry/contain_onedim.hpp"
#include "inc/geometry/distance_onedim_line.hpp"
#include "inc/geometry/distance_threedim_sphere.hpp"
#include "inc/geometry/intersection_onedim_linexy.hpp"
#include "inc/geometry/intersection_onedim_linexyz.hpp"

#include "inc/geometry/projection_onedim_linexy.hpp"
#include "inc/geometry/projection_onedim_linexyz.hpp"
#include "inc/geometry/projection_threedim_sphere.hpp"

#include "inc/geometry/intersection_twodim_plane.hpp"
#include "inc/geometry/intersection_twodim_triangle.hpp"
#include "inc/geometry/intersection_twodim_trianglexyz.hpp"
#include "inc/geometry/intersection_twodim_ellipse.hpp"
#include "inc/geometry/intersection_twodim_circle.hpp"

#include "inc/geometry/intersection_threedim_sphere.hpp"

#include "inc/geometry/barycentric_twodim_trianglexyz.hpp"

#include "inc/geometry/bisection_onedim_line.hpp"
#include "inc/geometry/bisection_twodim_arcnaive.hpp"

#include "inc/geometry/orientation_zerodim.hpp"
#include "inc/geometry/rotation2d.hpp"

#include "inc/geometry/area_twodim_triangle.hpp"

#include "inc/geometry/normal_threedim_surface.hpp"

#endif // CMNMATH_GEOMETRY_GEOMETRY_HPP__
