/** *************************************************************************
 *
 * @internal
 *   Demo program for teaching the course 
 *   Computer Architectures and Parallel Systems.
 *
 *   GPU Programming using OpenCL
 *
 *   02/2026, Petr Olivka, Dep. of Computer Science, FEI, VSB-TU Ostrava
 *   petr.olivka@vsb.cz
 *   https:/poli.cs.vsb.cz/edu/apps
 * @endinternal
 *
 * @file ocl_utils.cpp
 * @brief OpenCL Utils for initialization, load program and SVM allocation.
 * 
 ***************************************************************************/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <filesystem>

#include <CL/opencl.hpp> 

#include "ocl_utils.h"

/// @copydoc _out_error
void _out_error( std::ostream &t_stream, int t_error, std::string t_func_name, int t_line_num )
{
    t_stream << 
        "Error: " << t_error << 
        " in function '" << t_func_name << 
        "' on line "<< t_line_num << "." << std::endl;
}


// @copydoc ocl_init
cl_int ocl_init(int t_verbose, int t_gpu_dev_index)
{
    const char * l_dev_types[17] =
        { nullptr, "DEFAULT", "CPU", nullptr, "GPU", nullptr, nullptr, nullptr, "ACCELERATOR",
          nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, "CUSTOM" };

    cl_int l_err;

    // --- Get all platforms ---
    std::vector<cl::Platform> l_platforms;
    l_err = cl::Platform::get(&l_platforms);  CL_ERR_R(l_err);

    if (l_platforms.empty()) {
        std::cerr << "No OpenCL platforms found!" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (t_verbose > 1)
        std::cout << "Platforms found: " << l_platforms.size() << std::endl;

    // --- Collect usable devices (NVIDIA GPU OR POCL CPU) ---
    std::vector<std::pair<cl::Platform, cl::Device>> l_devices_ok;

    for (size_t ip = 0; ip < l_platforms.size(); ip++)
    {
        cl::Platform &p = l_platforms[ip];
        std::vector<cl::Device> devs;
        p.getDevices(CL_DEVICE_TYPE_ALL, &devs);

        if (t_verbose > 1) {
            std::cout << "  Platform[" << ip << "] " << p.getInfo<CL_PLATFORM_NAME>() << std::endl;
            std::cout << "    Vendor:  " << p.getInfo<CL_PLATFORM_VENDOR>() << std::endl;
            std::cout << "    Version: " << p.getInfo<CL_PLATFORM_VERSION>() << std::endl;
            std::cout << "    Devices: " << devs.size() << std::endl;
        }

        for (size_t id = 0; id < devs.size(); id++)
        {
            cl::Device &d = devs[id];
            cl_device_type dtype = d.getInfo<CL_DEVICE_TYPE>();
            std::string platName   = p.getInfo<CL_PLATFORM_NAME>();
            std::string platVendor = p.getInfo<CL_PLATFORM_VENDOR>();

            bool isNvidiaGPU =
                (dtype == CL_DEVICE_TYPE_GPU) &&
                (platVendor.find("NVIDIA") != std::string::npos);

            bool isPoclCPU =
                (platName.find("Portable Computing Language") != std::string::npos) &&
                (dtype == CL_DEVICE_TYPE_CPU);

            if (t_verbose > 1) {
                std::cout << "      Device[" << id << "] " << d.getInfo<CL_DEVICE_NAME>() << std::endl;
                std::cout << "        Type:   " << l_dev_types[dtype] << std::endl;
                std::cout << "        Vendor: " << d.getInfo<CL_DEVICE_VENDOR>() << std::endl;
            }

            // Accept NVIDIA GPU OR POCL CPU
            if (isNvidiaGPU || isPoclCPU) {
                l_devices_ok.push_back({p, d});
            }
        }
    }

    if (l_devices_ok.empty()) {
        std::cerr << "No usable OpenCL devices found (NVIDIA GPU or POCL CPU)." << std::endl;
        exit(EXIT_FAILURE);
    }

    // --- Prefer POCL CPU if available (SPIR-V compatible) ---
    int selected = -1;
    for (size_t i = 0; i < l_devices_ok.size(); i++) {
        auto &p = l_devices_ok[i].first;
        if (p.getInfo<CL_PLATFORM_NAME>().find("Portable Computing Language") != std::string::npos) {
            selected = i;
            break;
        }
    }

    // If no POCL, fall back to user index
    if (selected < 0) {
        if (t_gpu_dev_index >= (int)l_devices_ok.size()) {
            std::cerr << "Device index out of range!" << std::endl;
            exit(EXIT_FAILURE);
        }
        selected = t_gpu_dev_index;
    }

    auto l_pair = l_devices_ok[selected];

    if (t_verbose > 0) {
        std::cout << "Selected device: " 
                  << l_pair.second.getInfo<CL_DEVICE_NAME>() << std::endl;
    }

    // --- Set defaults ---
    cl::Platform::setDefault(l_pair.first);
    cl::Device::setDefault(l_pair.second);

    if (t_verbose > 0) {
        std::cout << "Default Platform created." << std::endl;
        std::cout << "Default Device created." << std::endl;
    }

    // --- Create context ---
    cl_context_properties props[] = {
        CL_CONTEXT_PLATFORM, (cl_context_properties)l_pair.first(), 0
    };

    cl::Context defCont(l_pair.second, props, nullptr, nullptr, &l_err);
    CL_ERR_R(l_err);
    cl::Context::setDefault(defCont);

    if (t_verbose > 0)
        std::cout << "Default Context created." << std::endl;

    // --- Create queue ---
    cl::CommandQueue defQueue((cl_command_queue_properties)0U, &l_err);
    CL_ERR_R(l_err);
    cl::CommandQueue::setDefault(defQueue);

    if (t_verbose > 0)
        std::cout << "Default Queue created." << std::endl;

    return CL_SUCCESS;
}



// @copydoc ocl_load_program
cl::Program ocl_load_program(const std::string t_kernel_filename)
{
    cl::Program l_program;

    // --- Load SPIR-V file ---
    size_t l_filesize = 0;
    try {
        l_filesize = std::filesystem::file_size(t_kernel_filename);
    }
    catch (std::filesystem::filesystem_error &e) {
        std::cerr << "Filesize '" << t_kernel_filename << "' error: " << e.what() << std::endl;
        return l_program;
    }

    std::vector<char> l_spirv_data(l_filesize);
    std::ifstream l_spirv_istr(t_kernel_filename, std::ios::binary);
    l_spirv_istr.read(l_spirv_data.data(), l_filesize);
    if ((size_t)l_spirv_istr.gcount() != l_filesize) {
        std::cerr << "Unable to read file `" << t_kernel_filename << "`." << std::endl;
        return l_program;
    }

    // --- Create program from IL (SPIR-V) ---
// --- Create program from IL (SPIR-V) ---
cl_int l_err;
l_program = cl::Program(cl::Context::getDefault(), l_spirv_data, false, &l_err);
CL_ERR_C(l_err);

// --- Build program with NO extra options ---
cl::Device dev = cl::Device::getDefault();
l_err = l_program.build({ dev }, nullptr);
if (l_err != CL_SUCCESS) {
    std::cerr << "Build of '" << t_kernel_filename << "' failed!" << std::endl;
    auto out = l_program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(&l_err);
    for (auto &pair : out)
        std::cerr << pair.second << std::endl << std::endl;
    return l_program;
}


    return l_program;
}

