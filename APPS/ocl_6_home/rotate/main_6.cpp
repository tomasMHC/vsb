/** *************************************************************************
 *
 * Demo program for teaching the course
 * Computer Architectures and Parallel Systems.
 *
 * GPU Programming using OpenCL
 *
 * 02/2026, Petr Olivka, Dep. of Computer Science, FEI, VSB-TU Ostrava
 * petr.olivka@vsb.cz
 * https:/poli.cs.vsb.cz/edu/apps
 *
 * Animation with bouncing ball.
 *
 ***************************************************************************/

#include <cstdlib>
#include <ostream>
#include <unistd.h>
#include <iostream>
#include <math.h>
#include <sys/time.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core_c.h>
#include <opencv2/core/mat.hpp>

#include <CL/opencl.hpp>

#include "ocl_utils.h"
#include "ocl_image.h"
#include "ocl_svm_mat_allocator.h"

#define KERNEL_SPV      "kernel_6.spv"
#define KERNEL_PREFIX   "gpu_"

// **************************************************************************
// gpu_ function for kernel.
// Kernel name is automatically created from this function name
// removing prefix gpu_.
//
// Kernel for creating chessboard
// Kernel header from kernel*.cl:
// __kernel void create_chessboard(          __global OCLImage *t_ocl_img, 
//                                                    int t_sq_size )
void fillOCLImageFromMat(OCLImage &img, const cv::Mat &mat)
{
    img.m_data = mat.data;
    img.m_size.x = mat.size().width;
    img.m_size.y = mat.size().height;
}

cv::Mat loadImage( const char *t_filename )
{
    // load image 
    cv::Mat l_cv_img = cv::imread( t_filename, cv::IMREAD_UNCHANGED );

    // image read?
    if ( l_cv_img.empty() )
    {
        std::cerr << "Unable to open image '" << t_filename << "'." << std::endl;
        exit( EXIT_FAILURE );
    }

    // 3 or 4 channels?
    if ( l_cv_img.channels() != 4 )
    {
        // convert to 4 channels
        cv::cvtColor( l_cv_img, l_cv_img, cv::COLOR_BGR2BGRA );
    }

    return l_cv_img;
}

cl_int gpu_create_chessboard( cl::Program &t_program, OCLImage *t_ocl_img,
                                                      int t_sq_size )
{
    cl_int l_err;

    // removing prefix gpu_
    std::string l_kern_name( __FUNCTION__ );
    if ( l_kern_name.find( KERNEL_PREFIX ) == 0 )
    {
        l_kern_name.erase( 0, strlen( KERNEL_PREFIX ) );
    }

    // select the kernel from opencl program
    cl::Kernel l_kern_create_chessboard( t_program, l_kern_name.c_str(), &l_err );  CL_ERR_R( l_err );

    // set kernel arguments
    l_err = l_kern_create_chessboard.setArg( 0, t_ocl_img );                    CL_ERR_R( l_err );
    l_err = l_kern_create_chessboard.setArg( 1, t_sq_size );                    CL_ERR_R( l_err );

    // list of SVM pointers for data synchronization
    l_kern_create_chessboard.setSVMPointers( {
            t_ocl_img,
            t_ocl_img->m_data,
            } );

    // get default Queue
    cl::CommandQueue defQueue = cl::CommandQueue::getDefault();

    // size of workgroup, should be multiple of 64, so 256 is OK
    int l_wg_size_x = 16;
    int l_wg_size_y = 16;
    // global range
    int l_gr_size_x = ( t_ocl_img->m_size.x + ( l_wg_size_x - 1 ) ) / l_wg_size_x * l_wg_size_x;
    int l_gr_size_y = ( t_ocl_img->m_size.y + ( l_wg_size_y - 1 ) ) / l_wg_size_y * l_wg_size_y;

    // Submitting kernel for execution
    l_err = defQueue.enqueueNDRangeKernel( l_kern_create_chessboard,
            // offset
            cl::NDRange( 0, 0 ),
            // global range
            cl::NDRange( l_gr_size_x, l_gr_size_y ),
            // work-group
            cl::NDRange( l_wg_size_x, l_wg_size_y ) );                          CL_ERR_R( l_err );

    // waiting for completion
    defQueue.finish();

    return CL_SUCCESS;
}

// **************************************************************************
// gpu_ function for kernel.
// Kernel name is automatically created from this function name
// removing prefix gpu_.
//
// Kernel for inserting image into image
// Kernel header from kernel*.cl:
// __kernel void insert_image(          __global OCLImage *t_ocl_big_img, 
//                                      __global OCLImage *t_ocl_small_img, 
//                                               int2 t_position )
cl_int gpu_insert_image( cl::Program &t_program, OCLImage *t_ocl_big_img,
                                                 OCLImage *t_ocl_small_img,
                                                 cl_int2 t_position )
{
    cl_int l_err;

    // removing prefix gpu_
    std::string l_kern_name( __FUNCTION__ );
    if ( l_kern_name.find( KERNEL_PREFIX ) == 0 )
    {
        l_kern_name.erase( 0, strlen( KERNEL_PREFIX ) );
    }

    // select the kernel from opencl program
    cl::Kernel l_kern_insert_image( t_program, l_kern_name.c_str(), &l_err );  CL_ERR_R( l_err );

    // set kernel arguments
    l_err = l_kern_insert_image.setArg( 0, t_ocl_big_img );                     CL_ERR_R( l_err );
    l_err = l_kern_insert_image.setArg( 1, t_ocl_small_img );                   CL_ERR_R( l_err );
    l_err = l_kern_insert_image.setArg( 2, t_position );                        CL_ERR_R( l_err );

    // list of SVM pointers for data synchronization
    l_kern_insert_image.setSVMPointers( {
            t_ocl_big_img,
            t_ocl_big_img->m_data,
            t_ocl_small_img,
            t_ocl_small_img->m_data,
            } );

    // get default Queue
    cl::CommandQueue defQueue = cl::CommandQueue::getDefault();

    // size of workgroup, should be multiple of 64, so 256 is OK
    int l_wg_size_x = 16;
    int l_wg_size_y = 16;
    // global range
    int l_gr_size_x = ( t_ocl_small_img->m_size.x + ( l_wg_size_x - 1 ) ) / l_wg_size_x * l_wg_size_x;
    int l_gr_size_y = ( t_ocl_small_img->m_size.y + ( l_wg_size_y - 1 ) ) / l_wg_size_y * l_wg_size_y;

    // Submitting kernel for execution
    l_err = defQueue.enqueueNDRangeKernel( l_kern_insert_image,
            // offset
            cl::NDRange( 0, 0 ),
            // global range
            cl::NDRange( l_gr_size_x, l_gr_size_y ),
            // work-group
            cl::NDRange( l_wg_size_x, l_wg_size_y ) );                          CL_ERR_R( l_err );

    // waiting for completion
    defQueue.finish();

    return CL_SUCCESS;
}

cl_int gpu_flip_image( cl::Program &t_program, OCLImage *t_ocl_img )
{
    cl_int l_err;

    // removing prefix gpu_
    std::string l_kern_name( __FUNCTION__ );
    if ( l_kern_name.find( KERNEL_PREFIX ) == 0 )
    {
        l_kern_name.erase( 0, strlen( KERNEL_PREFIX ) );
    }

    // select the kernel from opencl program
    cl::Kernel l_kern_flip_image( t_program, l_kern_name.c_str(), &l_err );  CL_ERR_R( l_err );

    // set kernel arguments
    l_err = l_kern_flip_image.setArg( 0, t_ocl_img );                     CL_ERR_R( l_err );

    // list of SVM pointers for data synchronization
    l_kern_flip_image.setSVMPointers( {
            t_ocl_img,
            t_ocl_img->m_data,
            } );

    // get default Queue
    cl::CommandQueue defQueue = cl::CommandQueue::getDefault();

    // size of workgroup, should be multiple of 64, so 256 is OK
    int l_wg_size_x = 16;
    int l_wg_size_y = 16;
    // global range
    int l_gr_size_x = ( t_ocl_img->m_size.x + ( l_wg_size_x - 1 ) ) / l_wg_size_x * l_wg_size_x;
    int l_gr_size_y = ( t_ocl_img->m_size.y + ( l_wg_size_y - 1 ) ) / l_wg_size_y * l_wg_size_y;

    // Submitting kernel for execution
    l_err = defQueue.enqueueNDRangeKernel( l_kern_flip_image,
            // offset
            cl::NDRange( 0, 0 ),
            // global range
            cl::NDRange( l_gr_size_x, l_gr_size_y ),
            // work-group
            cl::NDRange( l_wg_size_x, l_wg_size_y ) );                          CL_ERR_R( l_err );

    // waiting for completion
    defQueue.finish();

    return CL_SUCCESS;
}

cl_int gpu_rotate_img( cl::Program &t_program, OCLImage *t_ocl_orig_img, OCLImage *t_ocl_rotated_img, float t_angle )
{
    cl_int l_err;

    // removing prefix gpu_
    std::string l_kern_name( __FUNCTION__ );
    if ( l_kern_name.find( KERNEL_PREFIX ) == 0 )
    {
        l_kern_name.erase( 0, strlen( KERNEL_PREFIX ) );
    }

    // select the kernel from opencl program
    cl::Kernel l_kern_rotate_img( t_program, l_kern_name.c_str(), &l_err );  CL_ERR_R( l_err );

    float s = sinf(t_angle);
    float c = cosf(t_angle);

    // set kernel arguments
    l_err = l_kern_rotate_img.setArg( 0, t_ocl_orig_img );                     CL_ERR_R( l_err );
    l_err = l_kern_rotate_img.setArg( 1, t_ocl_rotated_img );                   CL_ERR_R( l_err );
    l_err = l_kern_rotate_img.setArg( 2, s );                                  CL_ERR_R( l_err );
    l_err = l_kern_rotate_img.setArg( 3, c );                                  CL_ERR_R( l_err );

    // list of SVM pointers for data synchronization
    l_kern_rotate_img.setSVMPointers( {
            t_ocl_orig_img,
            t_ocl_orig_img->m_data,
            t_ocl_rotated_img,
            t_ocl_rotated_img->m_data,
            } );

    // get default Queue
    cl::CommandQueue defQueue = cl::CommandQueue::getDefault();

    // size of workgroup, should be multiple of 64, so 256 is OK
    int l_wg_size_x = 16;
    int l_wg_size_y = 16;
    // global range
    int l_gr_size_x = ( t_ocl_rotated_img->m_size.x + ( l_wg_size_x - 1 ) ) / l_wg_size_x * l_wg_size_x;
    int l_gr_size_y = ( t_ocl_rotated_img->m_size.y + ( l_wg_size_y - 1 ) ) / l_wg_size_y * l_wg_size_y;

    // Submitting kernel for execution
    l_err = defQueue.enqueueNDRangeKernel( l_kern_rotate_img,
            // offset
            cl::NDRange( 0, 0 ),
            // global range
            cl::NDRange( l_gr_size_x, l_gr_size_y ),
            // work-group
            cl::NDRange( l_wg_size_x, l_wg_size_y ) );              CL_ERR_R( l_err );
    
    // waiting for completion
    defQueue.finish();

    return CL_SUCCESS;
}


// **************************************************************************
#define IMG_SIZEX   876
#define IMG_SIZEY   765

int main( int t_narg, char **t_args )
{
    if ( t_narg < 2 )
    {
        std::cout << "Enter image name!" << std::endl;
        exit( EXIT_FAILURE );
    }

    cl_int l_err;

    l_err = ocl_init( 1 );                                                      CL_ERR_E( l_err );

    std::cout << "\nInitialization done." << std::endl;

    cl::Program l_program( ocl_load_program( KERNEL_SPV ) );

    if ( l_program() == nullptr )
    {
        std::cerr << "Program not built!" << std::endl;
        exit( EXIT_FAILURE );
    }

    std::cout << "Program loaded.\n" << std::endl;

    // creating SVM allocator for cv::Mat
    SVMMatAllocator svmallocator;
    cv::Mat::setDefaultAllocator( &svmallocator );
    cv::Mat l_cv_load_img; // empty image

    l_cv_load_img = loadImage( t_args[ 1 ] );

    std::cout << "Opening image: '" << t_args[ 1 ] << "'." << std::endl;
    // load image from file?
    if ( !l_cv_load_img.empty() )
    {
        std::cout << "Image loaded." << std::endl;
    }
    else
    {
        std::cout << "Unable to read image!" << std::endl;
        exit( EXIT_FAILURE );
    }



    OCLImage *l_ocl_load_img = ocl_svm_malloc< OCLImage >();
    fillOCLImageFromMat( *l_ocl_load_img, l_cv_load_img );

    // 1. cast : Flip image horizontally
    // gpu_flip_image( l_program, l_ocl_load_img );

    // 2. cast : Rotate image by angle
    cv::Mat l_cv_img_rotated(l_cv_load_img.rows, l_cv_load_img.cols, CV_8UC4);
    OCLImage *l_ocl_img_rotated = ocl_svm_malloc<OCLImage>();
    fillOCLImageFromMat(*l_ocl_img_rotated, l_cv_img_rotated);

    float angle_deg = 90;
    float angle = angle_deg * M_PI / 180.0f; // in radians
    gpu_rotate_img( l_program, l_ocl_load_img, l_ocl_img_rotated, angle );

    cv::imshow( "Rotated image", l_cv_img_rotated );
    cv::imwrite( "rotated_image.png", l_cv_img_rotated );
    // wait for key
    cv::waitKey( 0 );
}

