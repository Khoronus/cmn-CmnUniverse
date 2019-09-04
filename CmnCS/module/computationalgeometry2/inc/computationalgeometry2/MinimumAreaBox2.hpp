// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2015
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.5 (2015/03/10)

#pragma once

#include "GteOrientedBox.h"
#include "GteConvexHull2.h"
#include "GteBSRational.h"
#include <type_traits>

// Compute a minimum-area oriented box containing the specified points.  The
// algorithm uses the rotating calipers method.
//   http://www-cgrl.cs.mcgill.ca/~godfried/research/calipers.html
//   http://cgm.cs.mcgill.ca/~orm/rotcal.html
// The box is supported by the convex hull of the points, so the algorithm
// is really about computing the minimum-area box containing a convex polygon.
// The rotating calipers approach is O(n) in time for n polygon edges.
//
// The naive algorithm is to process an edge as follows.  Let U0 be a
// unit-length direction for the edge.  Let U1 be a unit-length vector that
// is perpendicular to U0.  For each vertex P[i] of the polygon, compute its
// projection (x0[i],x1[i]), where P[i] = x0[i]*U0 + x1[i]*U1.  Compute
// x0min = min(x0[i]), x0max = max(x0[i]), x1min = min(x1[i]), and
// x1max = max(x1[i]).  The bounding box has axes U0 and U1, extents
// e0 = (x0max - x0min)/2 and e1 = (x1max - x1min)/2, and center C =
// ((x0max + x0min)/2)*U0 + ((x1max + x1min)/2)*U1.  Compute the bounding
// box for each of n edges, each edge requiring n projections, thus leading
// to an O(n^2) algorithm.
//
// NOTE: This algorithm guarantees a correct output only when ComputeType is
// an exact arithmetic type that supports division.  In GTEngine, one such
// type is BSRational<UIntegerAP32> (arbitrary precision).  Another such type
// is BSRational<UIntegerFP32<N>> (fixed precision), where N is chosen large
// enough for your input data sets.  If you choose ComputeType to be 'float'
// or 'double', the output is not guaranteed to be correct.
//
// See GeometricTools/GTEngine/Samples/Geometrics/MinimumAreaBox2 for an
// example of how to use the code.

namespace CmnCS
{
namespace computationalgeometry2
{

template <typename InputType, typename ComputeType>
class MinimumAreaBox2
{
public:
    // The class is a functor to support computing the minimum-area box of
    // multiple data sets using the same class object.
    MinimumAreaBox2();

    // The points are arbitrary, so we must compute the convex hull from
    // them in order to compute the minimum-area box.  The input parameters
    // are necessary for using ConvexHull2.  NOTE:  ConvexHull2 guarantees
    // that the hull does not have three consecutive collinear points.
    OrientedBox2<InputType> operator()(int numPoints,
        Vector2<InputType> const* points,
        bool useRotatingCalipers =
            !std::is_floating_point<ComputeType>::value);

    // The points already form a counterclockwise, nondegenerate convex
    // polygon.  If the points directly are the convex polygon, set
    // numIndices to 0 and indices to nullptr.  If the polygon vertices
    // are a subset of the incoming points, that subset is identified by
    // numIndices >= 3 and indices having numIndices elements.
    OrientedBox2<InputType> operator()(int numPoints,
        Vector2<InputType> const* points, int numIndices, int const* indices,
        bool useRotatingCalipers =
            !std::is_floating_point<ComputeType>::value);

    // Member access.
    inline int GetNumPoints() const;
    inline Vector2<InputType> const* GetPoints() const;
    inline std::vector<int> const& GetHull() const;

private:
    // Flags for the rotating calipers algorithm.  EXT_B is bottom, EXT_R is
    // right, EXT_T is top, and EXT_L is left.
    enum { EXT_B, EXT_R, EXT_T, EXT_L };

    // The box axes are U[i] and are usually not unit-length in order to allow
    // exact arithmetic.  The box is supported by mPoints[index[i]], where i
    // is one of the enumerations above.  The box axes are not necessarily unit
    // length, but they have the same length.  They need to be normalized for
    // conversion back to InputType.
    struct Box
    {
        Vector2<ComputeType> U[2];
        std::array<int, 4> index;
        ComputeType area;
    };

    // The rotating calipers algorithm has a loop invariant that requires
    // the convex polygon not to have collinear points.  Any such points
    // must be removed first.  The code is also executed for the O(n^2)
    // algorithm to reduce the number of process edges.
    void RemoveCollinearPoints(std::vector<Vector2<ComputeType>>& vertices);

    // This is the slow order O(n^2) search.
    Box ComputeBoxForEdgeOrderNSqr(
        std::vector<Vector2<ComputeType>> const& vertices);

    // This is the rotating calipers version, which is O(n).
    Box ComputeBoxForEdgeOrderN(
        std::vector<Vector2<ComputeType>> const& vertices);

    // Compute the new supporting box from the old supporting points in the
    // rotating calipers algoriothm
    void UpdateRectangle(int numVertices,
        Vector2<ComputeType> const* vertices, Box& rct);

    // The rotating calipers algorithm requires computing a minimum angle
    // formed by edges starting at supporting points of the current rectangle.
    // We must compare Dot(D0/|D0|,E0/|E0|) > Dot(D1/|D1|,E1/|E1|) using exact
    // arithmetic.  It is known that |D0| = |D1|, but generally |E0| and
    // |E1| are different.  We may square each side and compare, but the signs
    // of the dot products must be taken into account.
    bool IsLarger(
        Vector2<ComputeType> const& D0, Vector2<ComputeType> const& E0,
        Vector2<ComputeType> const& D1, Vector2<ComputeType> const& E1);

    // Convert the ComputeType box to the InputType box.  When the ComputeType
    // is an exact rational type, the conversions are performed to avoid
    // precision loss until necessary at the last step.
    void ConvertTo(Box const& minBox,
        std::vector<Vector2<ComputeType>> const& computePoints,
        OrientedBox2<InputType>& itMinBox);

    // The input points to be bound.
    int mNumPoints;
    Vector2<InputType> const* mPoints;

    // The indices into mPoints/mComputePoints for the convex hull vertices.
    std::vector<int> mHull;

    // Convenient values that occur regularly in the code.  When using
    // rational ComputeType, we construct these numbers only once.
    ComputeType mZero, mOne, mNegOne, mHalf;
};

//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
MinimumAreaBox2<InputType, ComputeType>::MinimumAreaBox2()
    :
    mNumPoints(0),
    mPoints(nullptr),
    mZero(0),
    mOne(1),
    mNegOne(-1),
    mHalf((InputType)0.5)
{
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
OrientedBox2<InputType> MinimumAreaBox2<InputType, ComputeType>::operator()(
    int numPoints, Vector2<InputType> const* points, bool useRotatingCalipers)
{
    mNumPoints = numPoints;
    mPoints = points;
    mHull.clear();

    // Get the convex hull of the points.
    ConvexHull2<InputType, ComputeType> ch2;
    ch2(mNumPoints, mPoints, (InputType)0);
    int dimension = ch2.GetDimension();

    OrientedBox2<InputType> minBox;

    if (dimension == 0)
    {
        // The points are all effectively the same (using fuzzy epsilon).
        minBox.center = mPoints[0];
        minBox.axis[0] = Vector2<InputType>::Unit(0);
        minBox.axis[1] = Vector2<InputType>::Unit(1);
        minBox.extent[0] = (InputType)0;
        minBox.extent[1] = (InputType)0;
        mHull.resize(1);
        mHull[0] = 0;
        return minBox;
    }

    if (dimension == 1)
    {
        // The points effectively lie on a line (using fuzzy epsilon).
        // Determine the extreme t-values for the points represented as
        // P = origin + t*direction.  We know that 'origin' is an input
        // vertex, so we can start both t-extremes at zero.
        Line2<InputType> const& line = ch2.GetLine();
        InputType tmin = (InputType)0, tmax = (InputType)0;
        int imin = 0, imax = 0;
        for (int i = 0; i < mNumPoints; ++i)
        {
            Vector2<InputType> diff = mPoints[i] - line.origin;
            InputType t = Dot(diff, line.direction);
            if (t > tmax)
            {
                tmax = t;
                imax = i;
            }
            else if (t < tmin)
            {
                tmin = t;
                imin = i;
            }
        }

        minBox.center = line.origin +
            ((InputType)0.5)*(tmin + tmax) * line.direction;
        minBox.extent[0] = ((InputType)0.5)*(tmax - tmin);
        minBox.extent[1] = (InputType)0;
        minBox.axis[0] = line.direction;
        minBox.axis[1] = -Perp(line.direction);
        mHull.resize(2);
        mHull[0] = imin;
        mHull[1] = imax;
        return minBox;
    }

    mHull = ch2.GetHull();
    Vector2<ComputeType> const* queryPoints = ch2.GetQuery().GetVertices();
    std::vector<Vector2<ComputeType>> computePoints(mHull.size());
    for (size_t i = 0; i < mHull.size(); ++i)
    {
        computePoints[i] = queryPoints[mHull[i]];
    }

    RemoveCollinearPoints(computePoints);

    Box box;
    if (useRotatingCalipers)
    {
        box = ComputeBoxForEdgeOrderN(computePoints);
    }
    else
    {
        box = ComputeBoxForEdgeOrderNSqr(computePoints);
    }

    ConvertTo(box, computePoints, minBox);
    return minBox;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
OrientedBox2<InputType> MinimumAreaBox2<InputType, ComputeType>::operator()(
    int numPoints, Vector2<InputType> const* points, int numIndices,
    int const* indices, bool useRotatingCalipers)
{
    mHull.clear();

    OrientedBox2<InputType> minBox;

    if (numPoints < 3 || !points || (indices && numIndices < 3))
    {
        minBox.center = Vector2<InputType>::Zero();
        minBox.axis[0] = Vector2<InputType>::Unit(0);
        minBox.axis[1] = Vector2<InputType>::Unit(1);
        minBox.extent = Vector2<InputType>::Zero();
        return minBox;
    }

    if (indices)
    {
        mHull.resize(numIndices);
        std::copy(indices, indices + numIndices, mHull.begin());
    }
    else
    {
        numIndices = numPoints;
        mHull.resize(numIndices);
        for (int i = 0; i < numIndices; ++i)
        {
            mHull[i] = i;
        }
    }

    std::vector<Vector2<ComputeType>> computePoints(numIndices);
    for (int i = 0; i < numIndices; ++i)
    {
        int h = mHull[i];
        computePoints[i][0] = (ComputeType)points[h][0];
        computePoints[i][1] = (ComputeType)points[h][1];
    }

    RemoveCollinearPoints(computePoints);

    Box box;
    if (useRotatingCalipers)
    {
        box = ComputeBoxForEdgeOrderN(computePoints);
    }
    else
    {
        box = ComputeBoxForEdgeOrderNSqr(computePoints);
    }

    ConvertTo(box, computePoints, minBox);
    return minBox;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
int MinimumAreaBox2<InputType, ComputeType>::GetNumPoints() const
{
    return mNumPoints;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
Vector2<InputType> const* MinimumAreaBox2<InputType, ComputeType>::GetPoints()
    const
{
    return mPoints;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
std::vector<int> const&
MinimumAreaBox2<InputType, ComputeType>::GetHull() const
{
    return mHull;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
void MinimumAreaBox2<InputType, ComputeType>::RemoveCollinearPoints(
    std::vector<Vector2<ComputeType>>& vertices)
{
    std::vector<Vector2<ComputeType>> tmpVertices = vertices;

    int const numVertices = static_cast<int>(vertices.size());
    int numNoncollinear = 0;
    Vector2<ComputeType> ePrev = tmpVertices[0] - tmpVertices.back();
    for (int i0 = 0, i1 = 1; i0 < numVertices; ++i0)
    {
        Vector2<ComputeType> eNext = tmpVertices[i1] - tmpVertices[i0];

        ComputeType dp = DotPerp(ePrev, eNext);
        if (dp != mZero)
        {
            vertices[numNoncollinear++] = tmpVertices[i0];
        }

        ePrev = eNext;
        if (++i1 == numVertices)
        {
            i1 = 0;
        }
    }

    vertices.resize(numNoncollinear);
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
typename MinimumAreaBox2<InputType, ComputeType>::Box
MinimumAreaBox2<InputType, ComputeType>::ComputeBoxForEdgeOrderNSqr(
    std::vector<Vector2<ComputeType>> const& vertices)
{
    Box box;
    box.area = mNegOne;

    int const numIndices = static_cast<int>(vertices.size());
    for (int i0 = numIndices - 1, i1 = 0; i1 < numIndices; i0 = i1++)
    {
        Vector2<ComputeType> const& P = vertices[i0];
        Vector2<ComputeType> U0 = vertices[i1] - vertices[i0];
        Vector2<ComputeType> U1 = -Perp(U0);

        // Compute the smallest rectangle with edge coincident to the current
        // hull edge.
        ComputeType min0 = mZero, max0 = mZero, max1 = mZero;
        std::array<int, 4> index = { i0, i0, i0, i0 };
        for (int j = 0; j < numIndices; ++j)
        {
            Vector2<ComputeType> diff = vertices[j] - P;

            ComputeType dot = Dot(U0, diff);
            if (dot < min0)
            {
                min0 = dot;
                index[EXT_L] = j;
            }
            else if (dot > max0)
            {
                max0 = dot;
                index[EXT_R] = j;
            }

            dot = Dot(U1, diff);
            if (dot > max1)
            {
                max1 = dot;
                index[EXT_T] = j;
            }
        }

        ComputeType area = (max0 - min0) * max1 / Dot(U0, U0);
        if (box.area == mNegOne || area < box.area)
        {
            box.U[0] = U0;
            box.U[1] = U1;
            box.index = index;
            box.area = area;
        }
    }

    return box;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
typename MinimumAreaBox2<InputType, ComputeType>::Box
MinimumAreaBox2<InputType, ComputeType>::ComputeBoxForEdgeOrderN(
    std::vector<Vector2<ComputeType>> const& vertices)
{
    // The inputs are assumed to be the vertices of a convex polygon that
    // is counterclockwise ordered.  The input points must not contain three
    // consecutive collinear points.

    // When the bounding box corresponding to a polygon edge is computed,
    // we mark the edge as visited.  If the edge is encountered later, the
    // algorithm terminates.
    int numVertices = static_cast<int>(vertices.size());
    std::vector<bool> visited(numVertices);
    std::fill(visited.begin(), visited.end(), false);

    // Start the minimum-area rectangle search with the edge from the last
    // polygon vertex to the first.  When updating the extremes, we want the
    // bottom-most point on the left edge, the top-most point on the right
    // edge, the left-most point on the top edge, and the right-most point
    // on the bottom edge.  The polygon edges starting at these points are
    // then guaranteed not to coincide with a box edge except when an extreme
    // point is shared by two box edges (at a corner).
    Box minBox;
    minBox.U[0] = vertices[0] - vertices[numVertices - 1];
    minBox.U[1] = -Perp(minBox.U[0]);
    UpdateRectangle(numVertices, &vertices[0], minBox);
    visited[minBox.index[EXT_B]] = true;

    // Execute the rotating calipers algorithm.
    Box box = minBox;
    for (;;)
    {
        // Determine the edge that forms the minimum angle with the current
        // box edges.  To support exact arithmetic in the algorithm, the box
        // axes are not usually the same length.  The dot product between
        // consecutive edges cannot be computed with exact arithmetic, but
        // a comparison between two dot products can be; see IsLarger().  This
        // allows us to determine the maximum dot product (minimum angle)
        // using exact arithmetic.  The initial choice for Emax causes the
        // first IsLarger(...) call to return true, so the bottom edge becomes
        // the first candidate for minimum-angle edge.
        int extreme = -1;
        Vector2<ComputeType> Dmax = box.U[0];
        Vector2<ComputeType> Emax = -Dmax;
        Vector2<ComputeType> Dcnd, Ecnd;
        for (int i = 0; i < 4; ++i)
        {
            int k0 = box.index[i], k1 = k0 + 1;
            if (k1 == numVertices)
            {
                k1 = 0;
            }

            // The box edges are ordered in i as U[0], U[1], -U[0], -U[1].
            Vector2<ComputeType> D = ((i & 2) ? -box.U[i & 1] : box.U[i & 1]);
            Vector2<ComputeType> E = vertices[k1] - vertices[k0];
            if (IsLarger(D, E, Dmax, Emax))
            {
                Dmax = D;
                Emax = E;
                extreme = i;
            }
        }

        if (extreme == -1)
        {
            // The polygon is a rectangle, so the search is over.
            break;
        }

        // Rotate the calipers and compute the bounding box.
        box.U[0] = Emax;
        box.U[1] = -Perp(Emax);

        // The right endpoint of the edge forming smallest angle with its
        // box edge becomes the new "bottom" extreme for the next pass.
        int bottom = box.index[extreme] + 1;
        if (bottom == numVertices)
        {
            bottom = 0;
        }

        if (visited[bottom])
        {
            // We have already processed this polygon edge, so the search
            // is over.
            break;
        }
        visited[bottom] = true;

        // We need to update only a subset of the polygon.  To share the code
        // for UpdateRectangle, we need a level of indirection to recapture
        // box.index[] in {0..numVertices-1}.  The new bottom point is used to
        // initialize several quantities in UpdateRectangle.  The four old
        // support points are included because a subset must support the new
        // rectangle.  However, if two or more support points have a 'next'
        // edge that ties the minimum angle, we need to select the endpoint
        // of that next edge as the new support point.  Thus, we have a total
        // of nine points to process.
        std::array<int, 9> indexIndirect;
        std::array<Vector2<ComputeType>, 9> supportVertices;
        indexIndirect[0] = bottom;
        supportVertices[0] = vertices[bottom];
        for (int i = 0, j = 1; i < 4; ++i)
        {
            indexIndirect[j] = box.index[i];
            supportVertices[j] = vertices[indexIndirect[j]];
            ++j;

            indexIndirect[j] = box.index[i] + 1;
            if (indexIndirect[j] == numVertices)
            {
                indexIndirect[j] = 0;
            }
            supportVertices[j] = vertices[indexIndirect[j]];
            ++j;
        }
        UpdateRectangle(9, &supportVertices[0], box); // box.index[] in {0..4}
        box.index[EXT_B] = bottom;
        for (int i = 1; i < 4; ++i)
        {
            box.index[i] = indexIndirect[box.index[i]];
            // box.index[i] in {0..numVertices-1}
        }

        if (box.area < minBox.area)
        {
            minBox = box;
        }
    }

    return minBox;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
void MinimumAreaBox2<InputType, ComputeType>::UpdateRectangle(int numVertices,
    Vector2<ComputeType> const* vertices, Box& rct)
{
    Vector2<ComputeType> const& origin = vertices[0];
    rct.index = { 0, 0, 0, 0 };

    Vector2<ComputeType> support[4];
    support[EXT_B] = { mZero, mZero };
    support[EXT_R] = { mZero, mZero };
    support[EXT_T] = { mZero, mZero };
    support[EXT_L] = { mZero, mZero };

    for (int i = 0; i < numVertices; ++i)
    {
        Vector2<ComputeType> diff = vertices[i] - origin;
        Vector2<ComputeType> v = { Dot(rct.U[0], diff), Dot(rct.U[1], diff) };

        if (v[1] < support[EXT_B][1] ||
            (v[1] == support[EXT_B][1] && v[0] > support[EXT_B][0]))
        {
            // New bottom minimum OR same bottom minimum but closer to right.
            rct.index[EXT_B] = i;
            support[EXT_B] = v;
        }

        if (v[0] > support[EXT_R][0] ||
            (v[0] == support[EXT_R][0] && v[1] > support[EXT_R][1]))
        {
            // New right maximum OR same right maximum but closer to top.
            rct.index[EXT_R] = i;
            support[EXT_R] = v;
        }

        if (v[1] > support[EXT_T][1] ||
            (v[1] == support[EXT_T][1] && v[0] < support[EXT_T][0]))
        {
            // New top maximum OR same top maximum but closer to left.
            rct.index[EXT_T] = i;
            support[EXT_T] = v;
        }

        if (v[0] < support[EXT_L][0] ||
            (v[0] == support[EXT_L][0] && v[1] < support[EXT_L][1]))
        {
            // New left minimum OR same left minimum but closer to bottom.
            rct.index[EXT_L] = i;
            support[EXT_L] = v;
        }
    }

    rct.area =
        (support[EXT_R][0] - support[EXT_L][0]) *
        (support[EXT_T][1] - support[EXT_B][1]) /
        Dot(rct.U[0], rct.U[0]);
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
bool MinimumAreaBox2<InputType, ComputeType>::IsLarger(
    Vector2<ComputeType> const& D0, Vector2<ComputeType> const& E0,
    Vector2<ComputeType> const& D1, Vector2<ComputeType> const& E1)
{
    ComputeType d0e0 = Dot(D0, E0);
    ComputeType d1e1 = Dot(D1, E1);
    ComputeType e0e0, e1e1, tmp0, tmp1;

    if (d0e0 > mZero)
    {
        if (d1e1 <= mZero)
        {
            return true;
        }

        e0e0 = Dot(E0, E0);
        e1e1 = Dot(E1, E1);
        tmp0 = d0e0 * (d0e0 / e0e0);
        tmp1 = d1e1 * (d1e1 / e1e1);
        return tmp0 > tmp1;
    }

    if (d0e0 < mZero)
    {
        if (d1e1 >= mZero)
        {
            return false;
        }

        e0e0 = Dot(E0, E0);
        e1e1 = Dot(E1, E1);
        tmp0 = d0e0 * (d0e0 / e0e0);
        tmp1 = d1e1 * (d1e1 / e1e1);
        return tmp0 < tmp1;
    }

    return d1e1 < mZero;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
void MinimumAreaBox2<InputType, ComputeType>::ConvertTo(Box const& minBox,
    std::vector<Vector2<ComputeType>> const& computePoints,
    OrientedBox2<InputType>& itMinBox)
{
    ComputeType sqrLength = Dot(minBox.U[0], minBox.U[0]);

    Vector2<ComputeType> average[2] =
    {
        computePoints[minBox.index[EXT_R]] +
            computePoints[minBox.index[EXT_L]],
        computePoints[minBox.index[EXT_T]] +
            computePoints[minBox.index[EXT_B]]
    };

    Vector2<ComputeType> range[2] =
    {
        computePoints[minBox.index[EXT_R]]
        - computePoints[minBox.index[EXT_L]],
        computePoints[minBox.index[EXT_T]] -
        computePoints[minBox.index[EXT_B]]
    };

    Vector2<ComputeType> center = mHalf * (
        Dot(minBox.U[0], average[0]) * minBox.U[0] +
        Dot(minBox.U[1], average[1]) * minBox.U[1]) / sqrLength;

    for (int i = 0; i < 2; ++i)
    {
        itMinBox.center[i] = (InputType)center[i];

        // Calculate the squared extent using ComputeType to avoid loss of
        // precision before computing a squared root.
        ComputeType sqrExtent = mHalf * Dot(minBox.U[i], range[i]);
        sqrExtent *= sqrExtent;
        sqrExtent /= sqrLength;
        itMinBox.extent[i] = sqrt((InputType)sqrExtent);

        // Before converting to floating-point, factor out the maximum
        // component using ComputeType to generate rational numbers in a
        // range that avoids loss of precision during the conversion and
        // normalization.
        Vector2<ComputeType> const& axis = minBox.U[i];
        ComputeType cmax = std::max(std::abs(axis[0]), std::abs(axis[1]));
        ComputeType invCMax = mOne / cmax;
        for (int j = 0; j < 2; ++j)
        {
            itMinBox.axis[i][j] = (InputType)(axis[j] * invCMax);
        }
        Normalize(itMinBox.axis[i]);
    }
}
//----------------------------------------------------------------------------

} // namespace computationalgeometry2
} // namespace CmnCS

#endif /* CMNMATH_GEOMETRICPRIMITIVE_LINE2D_HPP__ */