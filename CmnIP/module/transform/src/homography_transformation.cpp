/**

THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY 
APPLICABLE LAW. EXCEPT WHEN OTHERWISE STATED IN WRITING THE 
COPYRIGHT HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM 
ÅgAS ISÅh WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR 
IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM 
IS WITH YOU. SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE 
COST OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION.

*/


#include "transform/inc/transform/homography_transformation.hpp"

//-----------------------------------------------------------------------------
//	[class] HomographyTransformation
//-----------------------------------------------------------------------------

namespace CmnIP
{
namespace transform
{


//-----------------------------------------------------------------------------
int HomographyTransformation::homography(
	std::vector< cv::Point2f > &v_src1, 
	std::vector< cv::Point2f > &v_src2, 
	int method, double threshold)	{
	if (v_src1.size() < 4 || v_src2.size() < 4 || 
		v_src1.size() != v_src2.size()) return 0;
	homography_ = cv::findHomography(cv::Mat(v_src1), 
				                        cv::Mat(v_src2), method, 
										threshold);
	return 1;
}
//-----------------------------------------------------------------------------
int HomographyTransformation::homography(
	const std::vector< cv::Point2f > &v_src1, 
			    const std::vector< cv::Point2f > &v_src2, 
				int method, double threshold)	{
	if (v_src1.size() < 4 || v_src2.size() < 4 || 
		v_src1.size() != v_src2.size()) return 0;
	homography_ = cv::findHomography(cv::Mat(v_src1), 
				                        cv::Mat(v_src2), method, 
										threshold);
	return 1;
}
//-----------------------------------------------------------------------------
void HomographyTransformation::find_homography(
	std::vector< cv::Point2f > &v_src1, 
			    std::vector< cv::Point2f > &v_src2, 
				int method, double threshold)	{
	homography_ = cv::findHomography(cv::Mat(v_src1), 
				                        cv::Mat(v_src2), method, 
										threshold);
}
//-----------------------------------------------------------------------------
bool HomographyTransformation::find_good_homography(
	std::vector< cv::Point2f > &v_src1, 
	std::vector< cv::Point2f > &v_src2, 
	int method, double threshold, 
	double homography_threshold)	{
	
	// Find the homography matrix
	homography_ = cv::findHomography(cv::Mat(v_src1), 
				                        cv::Mat(v_src2), method, 
										threshold);
	// Check if the homography matrix is good
	if (check_homography(homography_threshold) ==
		HomographyTransformation::kHomographyBad) {
		return false;
	}
	return true;
}
//-----------------------------------------------------------------------------
void HomographyTransformation::find_homography(
	const std::vector< cv::Point2f > &v_src1, 
	const std::vector< cv::Point2f > &v_src2, 
	int method, double threshold)	{
	
	homography_ = cv::findHomography(cv::Mat(v_src1), 
				                        cv::Mat(v_src2), method, 
										threshold);
}
//-----------------------------------------------------------------------------
void HomographyTransformation::transform(
	cv::Mat &src, cv::Mat &dst, cv::Size &dsize)	{
	cv::warpPerspective(src, dst, homography_, dsize, cv::INTER_LINEAR, 
		cv::BORDER_CONSTANT);
}
//-----------------------------------------------------------------------------
void HomographyTransformation::transform(
	const cv::Mat &src, cv::Mat &dst, cv::Size &dsize)	{
	cv::warpPerspective(src, dst, homography_, dsize, cv::INTER_LINEAR, 
		cv::BORDER_CONSTANT);
}
//-----------------------------------------------------------------------------
void HomographyTransformation::warp_affine(cv::Mat &src, 
	cv::Mat &dst, cv::Size &dsize)	{
	cv::warpAffine(src, dst, homography_, dsize, cv::INTER_LINEAR, 
		cv::BORDER_TRANSPARENT);
}
//-----------------------------------------------------------------------------
void HomographyTransformation::warp_affine(
	const cv::Mat &src, cv::Mat &dst, cv::Size &dsize)	{
	cv::warpAffine(src, dst, homography_, dsize, cv::INTER_LINEAR, 
		cv::BORDER_TRANSPARENT);
}
//-----------------------------------------------------------------------------
int HomographyTransformation::IsAcceptable(double &fMatch, 
	double fMinDeterminant, double fMaxDeterminant)	{
	fMatch = 0;
	cv::SVD svd(homography_);
	cv::Mat dst;
	svd.solveZ(homography_, dst);
	//std::string msg = std::string("SVD::u");
	//Show::mat(svd.u, msg);
	//msg = std::string("SVD::vt");
	//Show::mat(svd.vt, msg);
	//msg = std::string("SVD::w");
	//Show::mat(svd.w, msg);
	//msg = std::string("SVD::dst");
	//Show::mat(dst, msg);
	double det = cv::determinant(homography_);
	//std::cout << "Determinant: " << det << std::endl;

	// calculate the values of the diagonal for u and vt to estimate which is the best solution (if it exist).
	double f1 = (abs(svd.u.at<double>(0,0)) + abs(svd.u.at<double>(1,1))
			    + abs(svd.u.at<double>(2,2))) / 3;
	double f2 = (abs(svd.vt.at<double>(0,2)) + abs(svd.vt.at<double>(1,1))
			    + abs(svd.vt.at<double>(2,0))) / 3;
	//std::cout << "u value: " << f1 << " " << f2 << std::endl;
	//cout << "--> " << svd.u.at<double>(0,2) << " " << svd.u.at<double>(1,1) << " " << svd.u.at<double>(2,0) << endl;
	//cout << "--> " << svd.vt.at<double>(0,2) << " " << svd.vt.at<double>(1,1) << " " << svd.vt.at<double>(2,0) << endl;

	//Mat_<double> R = svd.u * Mat(W) * svd.vt; //HZ 9.19
	//Mat_<double> t = svd.u.col(2); //u3

	//if (f1 > 0.95f && f2 > .95f) {
	//	fMatch = (f1 + f2) / 2;
	//	return 1;
	//}


	//// Estimate the fudge factor
	////cv::Point3f A(-320, -240, 1), B(320, -240, 1), C(-320, 240, 1), D(320, 240, 1);
	//float fA[3] = {-320, -240, 1}, fB[3] = {320, -240, 1}, fC[3] = {-320, 240, 1}, fD[3] = {320, 240, 1};
	//cv::Mat A(3, 1, CV_32FC1, fA), B(3, 1, CV_32FC1, fB), C(3, 1, CV_32FC1, fC), D(3, 1, CV_32FC1, fD);
	//Show::mat_(A, string("A"));

	//cv::Mat _h(3,3,CV_32FC1);
	//for (int y = 0; y < 3; y++)
	//{
	//	for (int x = 0; x < 3; x++)
	//	{
	//		_h.at<float>(y,x) = homography_.at<double>(y,x);
	//	}
	//}
	//cv::Mat A1 = _h * A;
	//cv::Mat B1 = _h * B;
	//cv::Mat C1 = _h * C;
	//cv::Mat D1 = _h * D;

	//cv::Mat u = (D1 - A1);
	//cv::Mat v = (C1 - B1);
	//float t = ((B1.at<float>(1,0) - A1.at<float>(1,0)) * u.at<float>(0,0) - (B1.at<float>(0,0) - A1.at<float>(0,0)) * u.at<float>(1,0));
	//float s = ((A1.at<float>(0,0) - B1.at<float>(0,0)) * v.at<float>(1,0) - (A1.at<float>(1,0) - B1.at<float>(1,0)) * v.at<float>(1,0));

	//cout << "##########################################################################" << endl;
	//cout << "t s : " << t << " " << s << " " << min(abs(t / s), abs(s / t)) << endl;

	//det = min(abs(t / s), abs(s / t));

	//if (det > 0.3f && det <= 1.0f)
	if (det >= fMinDeterminant && det <= fMaxDeterminant)
	{
		fMatch = det;
		return 1;
	}

	return 0;
}
//-----------------------------------------------------------------------------
int HomographyTransformation::IsAcceptable(
	std::vector<cv::Point2f> &v_ch, int xmin, int ymin, int xmax, int ymax)	{


	cv::Mat _h(3,3,CV_64FC1);
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			_h.at<double>(y,x) = homography_.at<double>(y,x);
		}
	}

	int isAcceptable = 1;
	// Check that all the convexHull points transformed are still inside the image
	for (std::vector<cv::Point2f>::const_iterator it = v_ch.begin(); it != v_ch.end(); it++)
	{
		cv::Mat tmp(3, 1, CV_64FC1);
		tmp.at<double>(0,0) = it->x;
		tmp.at<double>(1,0) = it->y;
		tmp.at<double>(2,0) = 1.0f;

		cv::Mat transform = _h * tmp;

		//Show::mat_(transform, string("cv_t"));
		if (transform.at<double>(0,0) < xmin || 
			transform.at<double>(0,0) > xmax || 
			transform.at<double>(1,0) < ymin || 
			transform.at<double>(1,0) > ymax) isAcceptable = 0;
	}

	//std::cout << "is acceptable: " << isAcceptable << std::endl;

	return isAcceptable;
}
//-----------------------------------------------------------------------------
HomographyTransformation::HomographyTransformationResult 
	HomographyTransformation::check_homography(
	const double bad_threshold)
{
  cv::SVD svd(homography_);	
  if (verbose_)
  {
	std::cout << "svd u: " << svd.u << std::endl;
	std::cout << "svd w: " << svd.w << std::endl;
	std::cout << "svd vt: " << svd.vt << std::endl;
  }
  if (svd.w.at<double>(0,0) > bad_threshold) return kHomographyBad;
  return kHomographyGood;
}

//-----------------------------------------------------------------------------
//	[class] HomographyMatrixManipulation
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void HomographyMatrixManipulation::scale_fix_top_left(
	const cv::Mat &homography, 
	const cv::Rect &original,
	float xscale, float yscale,
	cv::Mat &dst) {

	// Modify the homography matrix in order to be rescaled 
	// without be recomputed.
	// original four vertex and expected (clockwise top-left)
	std::vector< cv::Point2f > original_vertex;
	std::vector< cv::Point2f > expected_vertex;
	original_vertex.push_back(cv::Point2f(original.x,original.y));
	original_vertex.push_back(cv::Point2f(original.x + original.width,
											original.y));
	original_vertex.push_back(cv::Point2f(original.x + original.width,
											original.y + original.height));
	original_vertex.push_back(cv::Point2f(original.x,
											original.y + original.height));

	expected_vertex.push_back(cv::Point2f(original.x,original.y));
	expected_vertex.push_back(cv::Point2f(
								(original.x + original.width) * xscale,
								original.y));
	expected_vertex.push_back(cv::Point2f(
								(original.x + original.width) * xscale,
								(original.y + original.height) * yscale));
	expected_vertex.push_back(cv::Point2f(
								original.x,
								(original.y + original.height) * yscale));

	cv::Mat perspective = cv::getPerspectiveTransform(original_vertex, 
														expected_vertex);
	dst = perspective * homography;
}
//-----------------------------------------------------------------------------
void HomographyMatrixManipulation::scale_fix_top_left(
	const cv::Mat &homography, 
	const cv::Size &original,
	float xscale, float yscale,
	cv::Mat &dst) {

	// Modify the homography matrix in order to be rescaled 
	// without be recomputed.
	// original four vertex and expected (clockwise top-left)
	std::vector< cv::Point2f > original_vertex;
	std::vector< cv::Point2f > expected_vertex;
	original_vertex.push_back(cv::Point2f(0,0));
	original_vertex.push_back(cv::Point2f(original.width, 0));
	original_vertex.push_back(cv::Point2f(original.width, original.height));
	original_vertex.push_back(cv::Point2f(0, original.height));

	expected_vertex.push_back(cv::Point2f(0,0));
	expected_vertex.push_back(cv::Point2f(original.width * xscale, 0));
	expected_vertex.push_back(cv::Point2f(original.width * xscale, 
											original.height * yscale));
	expected_vertex.push_back(cv::Point2f(0, original.height * yscale));

	cv::Mat perspective = cv::getPerspectiveTransform(original_vertex, 
														expected_vertex);
	dst = perspective * homography;
}
//-----------------------------------------------------------------------------
void HomographyMatrixManipulation::scale_fix_center(
	const cv::Mat &homography, 
	const cv::Size &original,
	float xscale, float yscale,
	cv::Mat &dst) {

	// Modify the homography matrix in order to be rescaled 
	// without be recomputed.
	// original four vertex and expected (clockwise top-left)
	std::vector< cv::Point2f > original_vertex;
	std::vector< cv::Point2f > expected_vertex;
	original_vertex.push_back(cv::Point2f(0,0));
	original_vertex.push_back(cv::Point2f(original.width, 0));
	original_vertex.push_back(cv::Point2f(original.width, original.height));
	original_vertex.push_back(cv::Point2f(0, original.height));

	int w = original.width, h = original.height;
	int w_2 = original.width / 2, h_2 = original.height / 2;
	float xs = xscale, ys = yscale;
	expected_vertex.push_back(cv::Point2f( w_2 - (w_2 * xs), h_2 - (h_2 * ys) ) );
	expected_vertex.push_back(cv::Point2f( w * xs, h_2 - (h_2 * ys) ) );
	expected_vertex.push_back(cv::Point2f( w * xs, h * ys ) );
	expected_vertex.push_back(cv::Point2f( w_2 - (w_2 * xs), h * ys ) );

	cv::Mat perspective = cv::getPerspectiveTransform(original_vertex, 
														expected_vertex);
	dst = perspective * homography;
}
//-----------------------------------------------------------------------------
void HomographyMatrixManipulation::translate(
	const cv::Mat &homography, 
	const cv::Point2f &pt,
	cv::Mat &dst) {

	// Projection 2D -> 3D matrix
	cv::Mat T = (cv::Mat_<double>(3,3) <<
		1, 0, pt.x,
		0, 1, pt.y,
		0, 0,    1);

	dst = T * homography;
}
//-----------------------------------------------------------------------------
void HomographyMatrixManipulation::add(
	const cv::Mat &homography, 
	const cv::Mat &m,
	cv::Mat &dst) {

	dst = m + homography;
	dst.at<double>(2,2) = 1;
}


//-----------------------------------------------------------------------------
//	[class] HomographyPointTransformation
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
cv::Mat HomographyPointTransformation::getMapPoint(
	cv::Mat &pt, cv::Mat &map_matrix)    {
	cv::Mat ptDst;
	ptDst = map_matrix * pt;
	return ptDst;
}
//-----------------------------------------------------------------------------
cv::Mat HomographyPointTransformation::getMapPoint(
	cv::Point2f &pt, cv::Mat &map_matrix)    {
	cv::Mat ptSrc(3,1,CV_64FC1);
	ptSrc.at<double>(0,0) = (double)pt.x;
	ptSrc.at<double>(1,0) = (double)pt.y;
	ptSrc.at<double>(2,0) = 1.0f;
	return getMapPoint(ptSrc, map_matrix);
}
//-----------------------------------------------------------------------------
cv::Mat HomographyPointTransformation::getMapPoint(double x, 
	double y, cv::Mat &map_matrix)    {
	cv::Mat pt(3,1,CV_64FC1);
	pt.at<double>(0,0) = x;
	pt.at<double>(1,0) = y;
	pt.at<double>(2,0) = 1.0f;
	return getMapPoint(pt, map_matrix);
}
//-----------------------------------------------------------------------------
cv::Mat HomographyPointTransformation::normalizePoint(
	cv::Mat &ptSrc)    {
	cv::Mat pt(3,1,CV_64FC1);
	pt.at<double>(0,0) = ptSrc.at<double>(0,0) / ptSrc.at<double>(2,0);
	pt.at<double>(1,0) = ptSrc.at<double>(1,0) / ptSrc.at<double>(2,0);
	pt.at<double>(2,0) = 1.0f;
	return pt;
}

} // namespace transform
} // namespace CmnIP
