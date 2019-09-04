// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2015
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.10 (2015/03/10)

#pragma once

#include "GteOrientedBox.h"
#include "GteConvexHull3.h"
#include "GteMinimumAreaBox2.h"
#include "GteEdgeKey.h"
#include <thread>
#include <type_traits>

// Compute a minimum-volume oriented box containing the specified points.  The
// algorithm is really about computing the minimum-volume box containing the
// convex hull of the points, so we must compute the convex hull or you must
// pass an already built hull to the code.
//
// The minimum-volume oriented box has a face coincident with a hull face
// or has three mutually orthogonal edges coincident with three hull edges
// that (of course) are mutually orthogonal.
//    J.O'Rourke, "Finding minimal enclosing boxes",
//    Internat. J. Comput. Inform. Sci., 14:183-199, 1985.
//
// NOTE: This algorithm guarantees a correct output only when ComputeType is
// an exact arithmetic type that supports division.  In GTEngine, one such
// type is BSRational<UIntegerAP32> (arbitrary precision).  Another such type
// is BSRational<UIntegerFP32<N>> (fixed precision), where N is chosen large
// enough for your input data sets.  If you choose ComputeType to be 'float'
// or 'double', the output is not guaranteed to be correct.
//
// See GeometricTools/GTEngine/Samples/Geometrics/MinimumVolumeBox3 for an
// example of how to use the code.

namespace gte
{

template <typename InputType, typename ComputeType>
class MinimumVolumeBox3
{
public:
    // The class is a functor to support computing the minimum-volume box of
    // multiple data sets using the same class object.  For multithreading
    // in ProcessFaces, choose 'numThreads' subject to the constraints
    //     1 <= numThreads <= std::thread::hardware_concurrency()
    MinimumVolumeBox3(unsigned int numThreads = 1);

    // The points are arbitrary, so we must compute the convex hull from
    // them in order to compute the minimum-area box.  The input parameters
    // are necessary for using ConvexHull3.
    OrientedBox3<InputType> operator()(int numPoints,
        Vector3<InputType> const* points,
        bool useRotatingCalipers =
            !std::is_floating_point<ComputeType>::value);

    // The points form a nondegenerate convex polyhedron.  The indices input
    // must be nonnull and specify the triangle faces.
    OrientedBox3<InputType> operator()(int numPoints,
        Vector3<InputType> const* points, int numIndices, int const* indices,
        bool useRotatingCalipers =
            !std::is_floating_point<ComputeType>::value);

    // Member access.
    inline int GetNumPoints() const;
    inline Vector3<InputType> const* GetPoints() const;
    inline std::vector<int> const& GetHull() const;

private:
    struct Box
    {
        Vector3<ComputeType> P, U[3];
        ComputeType sqrLenU[3], range[3][2], volume;
    };

    enum { EXT_B, EXT_R, EXT_T, EXT_L };

    struct ExtrudeRectangle
    {
        Vector3<ComputeType> U[2];
        std::array<int, 4> index;
        ComputeType area;
    };

    // Compute the minimum-volume box relative to each hull face.
    void ProcessFaces(ETManifoldMesh const& mesh);

    // Compute the minimum-volume box for each triple of orthgonal hull edges.
    void ProcessEdges(ETManifoldMesh const& mesh);

    // Compute the minimum-volume box relative to a single hull face.
    void ProcessFace(ETManifoldMesh::Triangle const* supportTri,
        std::vector<Vector3<ComputeType>> const& normal,
        std::map<ETManifoldMesh::Triangle const*, int> const& triNormalMap,
        ETManifoldMesh::EMap const& emap, Box& localMinBox);

    // The rotating calipers algorithm has a loop invariant that requires
    // the convex polygon not to have collinear points.  Any such points
    // must be removed first.  The code is also executed for the O(n^2)
    // algorithm to reduce the number of process edges.
    void RemoveCollinearPoints(Vector3<ComputeType> const& N,
        std::vector<int>& polyline);

    // This is the slow order O(n^2) search.
    void ComputeBoxForFaceOrderNSqr(Vector3<ComputeType> const& N,
        std::vector<int> const& polyline, Box& box);

    // This is the rotating calipers version, which is O(n).
    void ComputeBoxForFaceOrderN(Vector3<ComputeType> const& N,
        std::vector<int> const& polyline, Box& box);

    // Compute the new supporting box from the old supporting points in the
    // rotating calipers algoriothm
    void UpdateRectangle(int numPolyline, int const* polyline,
        ExtrudeRectangle& rct);

    // The rotating calipers algorithm requires computing a minimum angle
    // formed by edges starting at supporting points of the current rectangle.
    // We must compare Dot(D0/|D0|,E0/|E0|) > Dot(D1/|D1|,E1/|E1|) using exact
    // arithmetic; thus, we may square each side and compare, but the signs of
    // the dot products must be taken into account.
    bool IsLarger(
        Vector3<ComputeType> const& D0, Vector3<ComputeType> const& E0,
        Vector3<ComputeType> const& D1, Vector3<ComputeType> const& E1);

    // Convert the extruded box to the minimum-volume box of InputType.  When
    // the ComputeType is an exact rational type, the conversions are
    // performed to avoid precision loss until necessary at the last step.
    void ConvertTo(OrientedBox3<InputType>& itMinBox);

    // The code is multithreaded, both for convex hull computation and
    // computing minimum-volume extruded boxes for the hull faces.  The
    // default value is 1, which implies a single-threaded computation (on
    // the main thread).
    unsigned int mNumThreads;

    // The input points to be bound.
    int mNumPoints;
    Vector3<InputType> const* mPoints;

    // The ComputeType conversions of the input points.  Only points of the
    // convex hull (vertices of a convex polyhedron) are converted for
    // performance when ComputeType is rational.
    Vector3<ComputeType> const* mComputePoints;

    // The indices into mPoints/mComputePoints for the convex hull vertices.
    std::vector<int> mHull;

    // The unique indices in mHull.  This set allows us to compute only for
    // the hull vertices and avoids redundant computations if the indices
    // were to have repeated indices into mPoints/mComputePoints.  This is
    // a performance improvement for rational ComputeType.
    std::set<int> mUniqueIndices;

    // The caller can specify whether to use rotating calipers or the slower
    // all-edge processing for computing an extruded bounding box.
    bool mUseRotatingCalipers;

    // Convenient values that occur regularly in the code.  When using
    // rational ComputeType, we construct these numbers only once.
    ComputeType mZero, mOne, mNegOne, mHalf;

    // The minimum-volume box computed internally using ComputeType
    // arithmetic.
    Box mMinBox;
};

//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
MinimumVolumeBox3<InputType, ComputeType>::MinimumVolumeBox3(
    unsigned int numThreads)
    :
    mNumThreads(numThreads),
    mNumPoints(0),
    mPoints(nullptr),
    mComputePoints(nullptr),
    mUseRotatingCalipers(true),
    mZero(0),
    mOne(1),
    mNegOne(-1),
    mHalf((InputType)0.5)
{
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
OrientedBox3<InputType> MinimumVolumeBox3<InputType, ComputeType>::operator()(
    int numPoints, Vector3<InputType> const* points, bool useRotatingCalipers)
{
    mNumPoints = numPoints;
    mPoints = points;
    mUseRotatingCalipers = useRotatingCalipers;
    mHull.clear();
    mUniqueIndices.clear();

    // Get the convex hull of the points.
    ConvexHull3<InputType, ComputeType> ch3;
    ch3(mNumPoints, mPoints, (InputType)0);
    int dimension = ch3.GetDimension();

    OrientedBox3<InputType> itMinBox;

    if (dimension == 0)
    {
        // The points are all effectively the same (using fuzzy epsilon).
        itMinBox.center = mPoints[0];
        itMinBox.axis[0] = Vector3<InputType>::Unit(0);
        itMinBox.axis[1] = Vector3<InputType>::Unit(1);
        itMinBox.axis[2] = Vector3<InputType>::Unit(2);
        itMinBox.extent[0] = (InputType)0;
        itMinBox.extent[1] = (InputType)0;
        itMinBox.extent[2] = (InputType)0;
        mHull.resize(1);
        mHull[0] = 0;
        return itMinBox;
    }

    if (dimension == 1)
    {
        // The points effectively lie on a line (using fuzzy epsilon).
        // Determine the extreme t-values for the points represented as
        // P = origin + t*direction.  We know that 'origin' is an input
        // vertex, so we can start both t-extremes at zero.
        Line3<InputType> const& line = ch3.GetLine();
        InputType tmin = (InputType)0, tmax = (InputType)0;
        int imin = 0, imax = 0;
        for (int i = 0; i < mNumPoints; ++i)
        {
            Vector3<InputType> diff = mPoints[i] - line.origin;
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

        itMinBox.center = line.origin +
            ((InputType)0.5)*(tmin + tmax) * line.direction;
        itMinBox.extent[0] = ((InputType)0.5)*(tmax - tmin);
        itMinBox.extent[1] = (InputType)0;
        itMinBox.extent[2] = (InputType)0;
        itMinBox.axis[0] = line.direction;
        ComputeOrthogonalComplement(1, &itMinBox.axis[0]);
        mHull.resize(2);
        mHull[0] = imin;
        mHull[1] = imax;
        return itMinBox;
    }

    if (dimension == 2)
    {
        // The points effectively line on a plane (using fuzzy epsilon).
        // Project the points onto the plane and compute the minimum-area
        // bounding box of them.
        Plane3<InputType> const& plane = ch3.GetPlane();

        // Get a coordinate system relative to the plane of the points.
        // Choose the origin to be any of the input points.
        Vector3<InputType> origin = mPoints[0];
        Vector3<InputType> basis[3];
        basis[0] = plane.normal;
        ComputeOrthogonalComplement(1, basis);

        // Project the input points onto the plane.
        std::vector<Vector2<InputType>> projection(mNumPoints);
        for (int i = 0; i < mNumPoints; ++i)
        {
            Vector3<InputType> diff = mPoints[i] - origin;
            projection[i][0] = Dot(basis[1], diff);
            projection[i][1] = Dot(basis[2], diff);
        }

        // Compute the minimum area box in 2D.
        MinimumAreaBox2<InputType, ComputeType> mab2;
        OrientedBox2<InputType> rectangle = mab2(mNumPoints, &projection[0]);

        // Lift the values into 3D.
        itMinBox.center = origin + rectangle.center[0] * basis[1] +
            rectangle.center[1] * basis[2];
        itMinBox.axis[0] = rectangle.axis[0][0] * basis[1] +
            rectangle.axis[0][1] * basis[2];
        itMinBox.axis[1] = rectangle.axis[1][0] * basis[1] +
            rectangle.axis[1][1] * basis[2];
        itMinBox.axis[2] = basis[0];
        itMinBox.extent[0] = rectangle.extent[0];
        itMinBox.extent[1] = rectangle.extent[1];
        itMinBox.extent[2] = (InputType)0;
        mHull = mab2.GetHull();
        return itMinBox;
    }

    // Get the set of unique indices of the hull.  This is used to project
    // hull vertices onto lines.
    ETManifoldMesh const& mesh = ch3.GetHullMesh();
    mHull.resize(3 * mesh.GetTriangles().size());
    int h = 0;
    for (auto const& element : mesh.GetTriangles())
    {
        for (int i = 0; i < 3; ++i, ++h)
        {
            int index = element.first.V[i];
            mHull[h] = index;
            mUniqueIndices.insert(index);
        }
    }

    mComputePoints = ch3.GetQuery().GetVertices();
    mMinBox.volume = mNegOne;
    ProcessFaces(mesh);
    ProcessEdges(mesh);
    ConvertTo(itMinBox);
    mComputePoints = nullptr;
    return itMinBox;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
OrientedBox3<InputType> MinimumVolumeBox3<InputType, ComputeType>::operator()(
    int numPoints, Vector3<InputType> const* points, int numIndices,
    int const* indices, bool useRotatingCalipers)
{
    mNumPoints = numPoints;
    mPoints = points;
    mUseRotatingCalipers = useRotatingCalipers;
    mUniqueIndices.clear();

    // Build the mesh from the indices.  The box construction uses the edge
    // map of the mesh.
    ETManifoldMesh mesh;
    int numTriangles = numIndices / 3;
    for (int t = 0; t < numTriangles; ++t)
    {
        int v0 = *indices++;
        int v1 = *indices++;
        int v2 = *indices++;
        mesh.Insert(v0, v1, v2);
    }

    // Get the set of unique indices of the hull.  This is used to project
    // hull vertices onto lines.
    mHull.resize(3 * mesh.GetTriangles().size());
    int h = 0;
    for (auto const& element : mesh.GetTriangles())
    {
        for (int i = 0; i < 3; ++i, ++h)
        {
            int index = element.first.V[i];
            mHull[h] = index;
            mUniqueIndices.insert(index);
        }
    }

    // Create the ComputeType points to be used downstream.
    std::vector<Vector3<ComputeType>> computePoints(mNumPoints);
    for (auto i : mUniqueIndices)
    {
        for (int j = 0; j < 3; ++j)
        {
            computePoints[i][j] = (ComputeType)mPoints[i][j];
        }
    }

    OrientedBox3<InputType> itMinBox;
    mComputePoints = &computePoints[0];
    mMinBox.volume = mNegOne;
    ProcessFaces(mesh);
    ProcessEdges(mesh);
    ConvertTo(itMinBox);
    mComputePoints = nullptr;
    return itMinBox;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
int MinimumVolumeBox3<InputType, ComputeType>::GetNumPoints() const
{
    return mNumPoints;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
Vector3<InputType> const*
MinimumVolumeBox3<InputType, ComputeType>::GetPoints() const
{
    return mPoints;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
std::vector<int> const& MinimumVolumeBox3<InputType, ComputeType>::GetHull()
    const
{
    return mHull;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
void MinimumVolumeBox3<InputType, ComputeType>::ProcessFaces(
    ETManifoldMesh const& mesh)
{
    // Get the mesh data structures.
    auto const& tmap = mesh.GetTriangles();
    auto const& emap = mesh.GetEdges();

    // Compute inner-pointing face normals for searching boxes supported by
    // a face and an extreme vertex.  The indirection in triNormalMap, using
    // an integer index instead of the normal/sqrlength pair itself, avoids
    // expensive copies when using exact arithmetic.
    std::vector<Vector3<ComputeType>> normal(tmap.size());
    std::map<ETManifoldMesh::Triangle const*, int> triNormalMap;
    int index = 0;
    for (auto const& element : tmap)
    {
        auto const* tri = element.second;
        Vector3<ComputeType> const& v0 = mComputePoints[tri->V[0]];
        Vector3<ComputeType> const& v1 = mComputePoints[tri->V[1]];
        Vector3<ComputeType> const& v2 = mComputePoints[tri->V[2]];
        Vector3<ComputeType> edge1 = v1 - v0;
        Vector3<ComputeType> edge2 = v2 - v0;
        normal[index] = Cross(edge2, edge1);  // inner-pointing normal
        triNormalMap[tri] = index++;
    }

    // Process the triangle faces.  For each face, compute the polyline of
    // edges that supports the bounding box with a face coincident to the
    // triangle face.  The projection of the polyline onto the plane of the
    // triangle face is a convex polygon, so we can use the method of rotating
    // calipers to compute its minimum-area box efficiently.
    unsigned int numFaces = static_cast<unsigned int>(tmap.size());
    if (mNumThreads > 1 && numFaces >= mNumThreads)
    {
        // Repackage the triangle pointers to support the partitioning of
        // faces for multithreaded face processing.
        std::vector<ETManifoldMesh::Triangle const*> triangles;
        triangles.reserve(numFaces);
        for (auto const& element : tmap)
        {
            triangles.push_back(element.second);
        }

        // Partition the data for multiple threads.
        unsigned int numFacesPerThread = numFaces / mNumThreads;
        std::vector<unsigned int> imin(mNumThreads), imax(mNumThreads);
        std::vector<Box> localMinBox(mNumThreads);
        for (unsigned int t = 0; t < mNumThreads; ++t)
        {
            imin[t] = t * numFacesPerThread;
            imax[t] = imin[t] + numFacesPerThread - 1;
            localMinBox[t].volume = mNegOne;
        }
        imax[mNumThreads - 1] = numFaces - 1;

        // Execute the face processing in multiple threads.
        std::vector<std::thread> process(mNumThreads);
        for (unsigned int t = 0; t < mNumThreads; ++t)
        {
            process[t] = std::thread([this, t, &imin, &imax, &triangles,
                &normal, &triNormalMap, &emap, &localMinBox]()
            {
                for (unsigned int i = imin[t]; i <= imax[t]; ++i)
                {
                    auto const* supportTri = triangles[i];
                    ProcessFace(supportTri, normal, triNormalMap, emap,
                        localMinBox[t]);
                }
            });
        }

        // Wait for all threads to finish.
        for (unsigned int t = 0; t < mNumThreads; ++t)
        {
            process[t].join();

            // Update the minimum-volume box candidate.
            if (mMinBox.volume == mNegOne
                || localMinBox[t].volume < mMinBox.volume)
            {
                mMinBox = localMinBox[t];
            }
        }
    }
    else
    {
        for (auto const& element : tmap)
        {
            auto const* supportTri = element.second;
            ProcessFace(supportTri, normal, triNormalMap, emap, mMinBox);
        }
    }
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
void MinimumVolumeBox3<InputType, ComputeType>::ProcessEdges(
    ETManifoldMesh const& mesh)
{
    // The minimum-volume box can also be supported by three mutually
    // orthogonal edges of the convex hull.  For each triple of orthogonal
    // edges, compute the minimum-volume box for that coordinate frame by
    // projecting the points onto the axes of the frame.  Use a hull vertex
    // as the origin.
    int index = mesh.GetTriangles().begin()->first.V[0];
    Vector3<ComputeType> const& origin = mComputePoints[index];
    Vector3<ComputeType> U[3];
    std::array<ComputeType, 3> sqrLenU;

    auto const& emap = mesh.GetEdges();
    auto e2 = emap.begin(), end = emap.end();
    for (/**/; e2 != end; ++e2)
    {
        U[2] =
            mComputePoints[e2->first.V[1]] -
            mComputePoints[e2->first.V[0]];

        auto e1 = e2;
        for (++e1; e1 != end; ++e1)
        {
            U[1] =
                mComputePoints[e1->first.V[1]] -
                mComputePoints[e1->first.V[0]];
            if (Dot(U[1], U[2]) != mZero)
            {
                continue;
            }
            sqrLenU[1] = Dot(U[1], U[1]);

            auto e0 = e1;
            for (++e0; e0 != end; ++e0)
            {
                U[0] =
                    mComputePoints[e0->first.V[1]] -
                    mComputePoints[e0->first.V[0]];

                sqrLenU[0] = Dot(U[0], U[0]);
                if (Dot(U[0], U[1]) != mZero || Dot(U[0], U[2]) != mZero)
                {
                    continue;
                }

                // The three edges are mutually orthogonal.  To support exact
                // rational arithmetic for volume computation, we replace U[2]
                // by a parallel vector.
                U[2] = Cross(U[0], U[1]);
                sqrLenU[2] = sqrLenU[0] * sqrLenU[1];

                // Project the vertices onto the lines containing the edges.
                // Use vertex 0 as the origin.
                std::array<ComputeType, 3> umin, umax;
                for (int j = 0; j < 3; ++j)
                {
                    umin[j] = mZero;
                    umax[j] = mZero;
                }

                for (auto i : mUniqueIndices)
                {
                    Vector3<ComputeType> diff = mComputePoints[i] - origin;
                    for (int j = 0; j < 3; ++j)
                    {
                        ComputeType dot = Dot(diff, U[j]);
                        if (dot < umin[j])
                        {
                            umin[j] = dot;
                        }
                        else if (dot > umax[j])
                        {
                            umax[j] = dot;
                        }
                    }
                }

                ComputeType volume = (umax[0] - umin[0]) / sqrLenU[0];
                volume *= (umax[1] - umin[1]) / sqrLenU[1];
                volume *= (umax[2] - umin[2]);

                // Update current minimum-volume box (if necessary).
                if (volume < mMinBox.volume)
                {
                    // The edge keys have unordered vertices, so it is
                    // possible that {U[0],U[1],U[2]} is a left-handed set.
                    // We need a right-handed set.
                    if (DotCross(U[0], U[1], U[2]) < mZero)
                    {
                        U[2] = -U[2];
                    }

                    mMinBox.P = origin;
                    for (int j = 0; j < 3; ++j)
                    {
                        mMinBox.U[j] = U[j];
                        mMinBox.sqrLenU[j] = sqrLenU[j];
                        for (int k = 0; k < 3; ++k)
                        {
                            mMinBox.range[k][0] = umin[k];
                            mMinBox.range[k][1] = umax[k];
                        }
                    }
                    mMinBox.volume = volume;

                }
            }
        }
    }
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
void MinimumVolumeBox3<InputType, ComputeType>::ProcessFace(
    ETManifoldMesh::Triangle const* supportTri,
    std::vector<Vector3<ComputeType>> const& normal,
    std::map<ETManifoldMesh::Triangle const*, int> const& triNormalMap,
    ETManifoldMesh::EMap const& emap, Box& localMinBox)
{
    // Get the supporting triangle information.
    Vector3<ComputeType> const& supportNormal =
        normal[triNormalMap.find(supportTri)->second];

    // Build the polyline of supporting edges.  The pair (v,polyline[v])
    // represents an edge directed appropriately (see next set of
    // comments).
    std::vector<int> polyline(mNumPoints);
    int polylineStart = -1;
    for (auto const& edgeElement : emap)
    {
        auto const& edge = *edgeElement.second;
        auto const* tri0 = edge.T[0];
        auto const* tri1 = edge.T[1];
        auto const& normal0 = normal[triNormalMap.find(tri0)->second];
        auto const& normal1 = normal[triNormalMap.find(tri1)->second];
        ComputeType dot0 = Dot(supportNormal, normal0);
        ComputeType dot1 = Dot(supportNormal, normal1);

        ETManifoldMesh::Triangle const* tri = nullptr;
        if (dot0 < mZero && dot1 >= mZero)
        {
            tri = tri0;
        }
        else if (dot1 < mZero && dot0 >= mZero)
        {
            tri = tri1;
        }

        if (tri)
        {
            // The edge supports the bounding box.  Insert the edge in the
            // list using clockwise order relative to tri.  This will lead
            // to a polyline whose projection onto the plane of the hull
            // face is a convex polygon that is counterclockwise oriented.
            for (int j0 = 2, j1 = 0; j1 < 3; j0 = j1++)
            {
                if (tri->V[j1] == edge.V[0])
                {
                    if (tri->V[j0] == edge.V[1])
                    {
                        polyline[edge.V[1]] = edge.V[0];
                    }
                    else
                    {
                        polyline[edge.V[0]] = edge.V[1];
                    }
                    polylineStart = edge.V[0];
                    break;
                }
            }
        }
    }

    // Rearrange the edges to form a closed polyline.  For M vertices, each
    // ComputeBoxFor*() function starts with the edge from closedPolyline[M-1]
    // to closedPolyline[0].
    std::vector<int> closedPolyline(mNumPoints);
    int numClosedPolyline = 0;
    int v = polylineStart;
    for (auto& cp : closedPolyline)
    {
        cp = v;
        ++numClosedPolyline;
        v = polyline[v];
        if (v == polylineStart)
        {
            break;
        }
    }
    closedPolyline.resize(numClosedPolyline);

    // This avoids redundant face testing in the O(n^2) or O(n) algorithms
    // and it simplifies the O(n) implementation.
    RemoveCollinearPoints(supportNormal, closedPolyline);

    // Compute the box coincident to the hull triangle that has minimum
    // area on the face coincident with the triangle.
    Box faceBox;
    if (mUseRotatingCalipers)
    {
        ComputeBoxForFaceOrderN(supportNormal, closedPolyline, faceBox);
    }
    else
    {
        ComputeBoxForFaceOrderNSqr(supportNormal, closedPolyline, faceBox);
    }

    // Update the minimum-volume box candidate.
    if (localMinBox.volume == mNegOne || faceBox.volume < localMinBox.volume)
    {
        localMinBox = faceBox;
    }
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
void MinimumVolumeBox3<InputType, ComputeType>::RemoveCollinearPoints(
    Vector3<ComputeType> const& N, std::vector<int>& polyline)
{
    std::vector<int> tmpPolyline = polyline;

    int const numPolyline = static_cast<int>(polyline.size());
    int numNoncollinear = 0;
    Vector3<ComputeType> ePrev =
        mComputePoints[tmpPolyline[0]] - mComputePoints[tmpPolyline.back()];

    for (int i0 = 0, i1 = 1; i0 < numPolyline; ++i0)
    {
        Vector3<ComputeType> eNext =
            mComputePoints[tmpPolyline[i1]] - mComputePoints[tmpPolyline[i0]];

        ComputeType tsp = DotCross(ePrev, eNext, N);
        if (tsp != mZero)
        {
            polyline[numNoncollinear++] = tmpPolyline[i0];
        }

        ePrev = eNext;
        if (++i1 == numPolyline)
        {
            i1 = 0;
        }
    }

    polyline.resize(numNoncollinear);
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
void MinimumVolumeBox3<InputType, ComputeType>::ComputeBoxForFaceOrderNSqr(
    Vector3<ComputeType> const& N, std::vector<int> const& polyline,
    Box& box)
{
    // This code processes the polyline terminator associated with a convex
    // hull face of inner-pointing normal N.  The polyline is usually not
    // contained by a plane, and projecting the polyline to a convex polygon
    // in a plane perpendicular to N introduces floating-point rounding
    // errors.  The minimum-area box for the projected polyline is computed
    // indirectly to support exact rational arithmetic.

    box.P = mComputePoints[polyline[0]];
    box.U[2] = N;
    box.sqrLenU[2] = Dot(N, N);
    box.range[1][0] = mZero;
    box.volume = mNegOne;
    int const numPolyline = static_cast<int>(polyline.size());
    for (int i0 = numPolyline - 1, i1 = 0; i1 < numPolyline; i0 = i1++)
    {
        // Create a coordinate system for the plane perpendicular to the face
        // normal and containing a polyline vertex.
        Vector3<ComputeType> const& P = mComputePoints[polyline[i0]];
        Vector3<ComputeType> E =
            mComputePoints[polyline[i1]] - mComputePoints[polyline[i0]];

        Vector3<ComputeType> U1 = Cross(N, E);
        Vector3<ComputeType> U0 = Cross(U1, N);

        // Compute the smallest rectangle containing the projected polyline.
        ComputeType min0 = mZero, max0 = mZero, max1 = mZero;
        for (int j = 0; j < numPolyline; ++j)
        {
            Vector3<ComputeType> diff = mComputePoints[polyline[j]] - P;
            ComputeType dot = Dot(U0, diff);
            if (dot < min0)
            {
                min0 = dot;
            }
            else if (dot > max0)
            {
                max0 = dot;
            }

            dot = Dot(U1, diff);
            if (dot > max1)
            {
                max1 = dot;
            }
        }

        // The true area is Area(rectangle)*Length(N).  After the smallest
        // scaled-area rectangle is computed and returned, the box.volume is
        // updated to be the actual squared volume of the box.
        ComputeType sqrLenU1 = Dot(U1, U1);
        ComputeType volume = (max0 - min0) * max1 / sqrLenU1;
        if (box.volume == mNegOne || volume < box.volume)
        {
            box.P = P;
            box.U[0] = U0;
            box.U[1] = U1;
            box.sqrLenU[0] = sqrLenU1 * box.sqrLenU[2];
            box.sqrLenU[1] = sqrLenU1;
            box.range[0][0] = min0;
            box.range[0][1] = max0;
            box.range[1][1] = max1;
            box.volume = volume;
        }
    }

    // Compute the range of points in the support-normal direction.
    box.range[2][0] = mZero;
    box.range[2][1] = mZero;
    for (auto i : mUniqueIndices)
    {
        Vector3<ComputeType> diff = mComputePoints[i] - box.P;
        ComputeType height = Dot(box.U[2], diff);
        if (height < box.range[2][0])
        {
            box.range[2][0] = height;
        }
        else if (height > box.range[2][1])
        {
            box.range[2][1] = height;
        }
    }

    // Compute the actual volume.
    box.volume *= (box.range[2][1] - box.range[2][0]) / box.sqrLenU[2];
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
void MinimumVolumeBox3<InputType, ComputeType>::ComputeBoxForFaceOrderN(
    Vector3<ComputeType> const& N, std::vector<int> const& polyline, Box& box)
{
    // This code processes the polyline terminator associated with a convex
    // hull face of inner-pointing normal N.  The polyline is usually not
    // contained by a plane, and projecting the polyline to a convex polygon
    // in a plane perpendicular to N introduces floating-point rounding
    // errors.  The minimum-area box for the projected polyline is computed
    // indirectly to support exact rational arithmetic.

    // When the bounding box corresponding to a polyline edge is computed,
    // we mark the edge as visited.  If the edge is encountered later, the
    // algorithm terminates.
    int const numPolyline = static_cast<int>(polyline.size());
    std::vector<bool> visited(numPolyline);
    std::fill(visited.begin(), visited.end(), false);

    // Start the minimum-area rectangle search with the edge from the last
    // polyline vertex to the first.  When updating the extremes, we want the
    // bottom-most point on the left edge, the top-most point on the right
    // edge, the left-most point on the top edge, and the right-most point
    // on the bottom edge.  The polygon edges starting at these points are
    // then guaranteed not to coincide with a box edge except when an extreme
    // point is shared by two box edges (at a corner).
    ExtrudeRectangle minRct;
    Vector3<ComputeType> E = mComputePoints[polyline[0]] -
        mComputePoints[polyline[numPolyline - 1]];
    minRct.U[1] = Cross(N, E);
    minRct.U[0] = Cross(minRct.U[1], N);
    UpdateRectangle(numPolyline, &polyline[0], minRct);
    visited[minRct.index[EXT_B]] = true;

    // Execute the rotating calipers algorithm.
    ExtrudeRectangle rct = minRct;
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
        Vector3<ComputeType> Dmax = rct.U[0];
        Vector3<ComputeType> Emax = -Dmax, Emaxperp{ mZero, mZero, mZero };
        for (int i = 0; i < 4; ++i)
        {
            int k0 = rct.index[i], k1 = k0 + 1;
            if (k1 == numPolyline)
            {
                k1 = 0;
            }

            // The box edges are ordered in i as U[0], U[1], -U[0], -U[1].
            Vector3<ComputeType> D = ((i & 2) ? -rct.U[i & 1] : rct.U[i & 1]);
            Vector3<ComputeType> E =
                mComputePoints[polyline[k1]] - mComputePoints[polyline[k0]];
            Vector3<ComputeType> Eperp = Cross(N, E);
            E = Cross(Eperp, N);
            if (IsLarger(D, E, Dmax, Emax))
            {
                Dmax = D;
                Emax = E;
                Emaxperp = Eperp;
                extreme = i;
            }
        }

        if (extreme == -1)
        {
            // The projected polyline is a rectangle, so the search is over.
            break;
        }

        // Rotate the calipers and compute the bounding box.
        rct.U[0] = Emax;
        rct.U[1] = Emaxperp;

        // The right endpoint of the edge forming smallest angle with its
        // box edge becomes the new "bottom" extreme for the next pass.
        int bottom = rct.index[extreme] + 1;
        if (bottom == numPolyline)
        {
            bottom = 0;
        }

        if (visited[bottom])
        {
            // We have already processed this polyline edge, so the search
            // is over.
            break;
        }
        visited[bottom] = true;

        // We need to update only a subset of the polyline.  To share the code
        // for UpdateRectangle, we need a level of indirection to recapture
        // rct.index[] in {0..numPolyline-1}.  The new bottom point is used to
        // initialize several quantities in UpdateRectangle.  The four old
        // support points are included because a subset must support the new
        // rectangle.  However, if two or more support points have a 'next'
        // edge that ties the minimum angle, we need to select the endpoint
        // of that next edge as the new support point.  Thus, we have a total
        // of nine points to process.
        std::array<int, 9> indexIndirect, supportPolyline;
        indexIndirect[0] = bottom;
        supportPolyline[0] = polyline[bottom];
        for (int i = 0, j = 1; i < 4; ++i)
        {
            indexIndirect[j] = rct.index[i];
            supportPolyline[j] = polyline[indexIndirect[j]];
            ++j;

            indexIndirect[j] = rct.index[i] + 1;
            if (indexIndirect[j] == numPolyline)
            {
                indexIndirect[j] = 0;
            }
            supportPolyline[j] = polyline[indexIndirect[j]];
            ++j;
        }
        UpdateRectangle(9, &supportPolyline[0], rct); // rct.index[] in {0..4}
        rct.index[EXT_B] = bottom;
        for (int i = 1; i < 4; ++i)
        {
            rct.index[i] = indexIndirect[rct.index[i]];
            // rct.index[i] in {0..numPolyline-1}
        }

        if (rct.area < minRct.area)
        {
            minRct = rct;
        }
    }

    // Store relevant box information for computing volume and converting to
    // an InputType bounding box.
    box.P = mComputePoints[polyline[minRct.index[EXT_B]]];
    box.U[0] = minRct.U[0];
    box.U[1] = minRct.U[1];
    box.U[2] = N;
    box.sqrLenU[0] = Dot(box.U[0], box.U[0]);
    box.sqrLenU[1] = Dot(box.U[1], box.U[1]);
    box.sqrLenU[2] = Dot(box.U[2], box.U[2]);

    // Compute the range of points in the plane perpendicular to the support
    // normal.
    box.range[0][0] = Dot(box.U[0],
        mComputePoints[polyline[minRct.index[EXT_L]]] - box.P);
    box.range[0][1] = Dot(box.U[0],
        mComputePoints[polyline[minRct.index[EXT_R]]] - box.P);
    box.range[1][0] = mZero;
    box.range[1][1] = Dot(box.U[1],
        mComputePoints[polyline[minRct.index[EXT_T]]] - box.P);

    // Compute the range of points in the support-normal direction.
    box.range[2][0] = mZero;
    box.range[2][1] = mZero;
    for (auto i : mUniqueIndices)
    {
        Vector3<ComputeType> diff = mComputePoints[i] - box.P;
        ComputeType height = Dot(box.U[2], diff);
        if (height < box.range[2][0])
        {
            box.range[2][0] = height;
        }
        else if (height > box.range[2][1])
        {
            box.range[2][1] = height;
        }
    }

    // Compute the actual volume.
    box.volume =
        (box.range[0][1] - box.range[0][0]) *
        ((box.range[1][1] - box.range[1][0]) / box.sqrLenU[1]) *
        ((box.range[2][1] - box.range[2][0]) / box.sqrLenU[2]);
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
void MinimumVolumeBox3<InputType, ComputeType>::UpdateRectangle(
    int numPolyline, int const* polyline, ExtrudeRectangle& rct)
{
    Vector3<ComputeType> const& origin = mComputePoints[polyline[0]];
    rct.index = { 0, 0, 0, 0 };

    Vector2<ComputeType> support[4];
    support[EXT_B] = { mZero, mZero };
    support[EXT_R] = { mZero, mZero };
    support[EXT_T] = { mZero, mZero };
    support[EXT_L] = { mZero, mZero };

    for (int i = 0; i < numPolyline; ++i)
    {
        Vector3<ComputeType> diff = mComputePoints[polyline[i]] - origin;
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
        Dot(rct.U[1], rct.U[1]);
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
bool MinimumVolumeBox3<InputType, ComputeType>::IsLarger(
    Vector3<ComputeType> const& D0, Vector3<ComputeType> const& E0,
    Vector3<ComputeType> const& D1, Vector3<ComputeType> const& E1)
{
    ComputeType d0e0 = Dot(D0, E0);
    ComputeType d1e1 = Dot(D1, E1);
    ComputeType d0d0, e0e0, d1d1, e1e1, tmp0, tmp1;

    if (d0e0 > mZero)
    {
        if (d1e1 <= mZero)
        {
            return true;
        }

        d0d0 = Dot(D0, D0);
        e0e0 = Dot(E0, E0);
        d1d1 = Dot(D1, D1);
        e1e1 = Dot(E1, E1);
        tmp0 = (d0e0 / d0d0) * (d0e0 / e0e0);
        tmp1 = (d1e1 / d1d1) * (d1e1 / e1e1);
        return tmp0 > tmp1;
    }

    if (d0e0 < mZero)
    {
        if (d1e1 >= mZero)
        {
            return false;
        }

        d0d0 = Dot(D0, D0);
        e0e0 = Dot(E0, E0);
        d1d1 = Dot(D1, D1);
        e1e1 = Dot(E1, E1);
        tmp0 = (d0e0 / d0d0) * (d0e0 / e0e0);
        tmp1 = (d1e1 / d1d1) * (d1e1 / e1e1);
        return tmp0 < tmp1;
    }

    return d1e1 < mZero;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
void MinimumVolumeBox3<InputType, ComputeType>::ConvertTo(
    OrientedBox3<InputType>& itMinBox)
{
    Vector3<ComputeType> center = mMinBox.P;
    for (int i = 0; i < 3; ++i)
    {
        ComputeType average =
            mHalf * (mMinBox.range[i][0] + mMinBox.range[i][1]);
        center += (average / mMinBox.sqrLenU[i]) * mMinBox.U[i];
    }

    for (int i = 0; i < 3; ++i)
    {
        itMinBox.center[i] = (InputType)center[i];

        // Calculate the squared extent using ComputeType to avoid loss of
        // precision before computing a squared root.
        ComputeType sqrExtent =
            mHalf * (mMinBox.range[i][1] - mMinBox.range[i][0]);
        sqrExtent *= sqrExtent;
        sqrExtent /= mMinBox.sqrLenU[i];
        itMinBox.extent[i] = sqrt((InputType)sqrExtent);

        // Before converting to floating-point, factor out the maximum
        // component using ComputeType to generate rational numbers in a
        // range that avoids loss of precision during the conversion and
        // normalization.
        Vector3<ComputeType> const& axis = mMinBox.U[i];
        ComputeType cmax = std::max(std::abs(axis[0]), std::abs(axis[1]));
        cmax = std::max(cmax, std::abs(axis[2]));
        ComputeType invCMax = mOne / cmax;
        for (int j = 0; j < 3; ++j)
        {
            itMinBox.axis[i][j] = (InputType)(axis[j] * invCMax);
        }
        Normalize(itMinBox.axis[i]);
    }
}
//----------------------------------------------------------------------------
} // namespace computationalgeometry
} // namespace CmnMath

#endif /* CMNMATH_GEOMETRICPRIMITIVE_LINE2D_HPP__ */