#ifndef INCLUDE_UTILS_HPP_
#define INCLUDE_UTILS_HPP_

#include <vector>
#include <string>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>

namespace acmebot {
/**
 * @brief Structure to store the pose of an object in (x, y, z)
 * 
 */
struct Pose{
        /**
         * @brief Construct a new Pose object with default values
         * 
         */
        Pose() {
                x = -1.0;
                y = -1.0;
                z = -1.0;
        }

        /**
         * @brief Construct a new Pose object wtih user specified values
         * 
         * @param x1 
         * @param y1 
         * @param z1 
         */
        Pose(double x1, double y1, double z1) {
                x = x1;
                y = y1;
                z = z1;
        }
        double x;
        double y;
        double z;
};

/**
 * @brief Utils class for generic function
 * 
 */
class Utils{
 public:
    /**
     * @brief Draws bbox on the frame
     * 
     * @param img
     * @param vector of bbox
     * @return cv::Mat
     */
    static cv::Mat DrawBbox(cv::Mat i, const cv::Rect& b,
        const std::string &l);

    /**
     * @brief Get the Bbox Center
     * 
     * @param bbox
     * @return cv::Point
     */
    static cv::Point GetBboxCenter(const cv::Rect &bbox);

    /**
     * @brief Get the Bbox Area
     * 
     * @param bbox
     * @return double
     */
    static double GetBboxArea(const cv::Rect &bbox);

    /**
     * @brief Resizes the input img to the specified size
     * 
     * @param img
     * @param size
     * @return cv::Mat 
     */
    static cv::Mat ResizeImage(const cv::Mat &i, const cv::Size &s);

    /**
     * @brief Calculates intersection over union for the specified bboxes
     * 
     * @param bbox1
     * @param bbox2
     * @return double iou
     */
    static double CalculateIOU(const cv::Rect& b1, const cv::Rect& b2);

    /**
     * @brief Converts bbox pixels in (x, y, z) in another frame of ref
     * 
     * @param bbox
     * @param calib_factor 
     * @return Pose 
     */
    static Pose PixelsToPose(const cv::Rect &b, double calib_factor);
};
}  // namespace acme
#endif  // INCLUDE_UTILS_HPP_

