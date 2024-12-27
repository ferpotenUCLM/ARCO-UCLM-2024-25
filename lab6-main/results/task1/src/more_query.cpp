#include <CL/sycl.hpp>


// This allow us to remove cl::sycl:: from all invokations
using namespace cl::sycl;

int main() {
    cpu_selector selector;

    queue q(selector);

    std::cout << "Device: " << q.get_device().get_info<info::device::name>()<< std::endl;
    std::cout << "Vendor: " << q.get_device().get_info<info::device::vendor>() << std::endl;
    std::cout << "Driver version: " << q.get_device().get_info<info::device::driver_version>() << std::endl;
    std::cout << "Global memory size: " << q.get_device().get_info<info::device::global_mem_size>() / (1024 * 1024) << " MB" << std::endl;
    std::cout << "Max compute units: " << q.get_device().get_info<info::device::max_compute_units>() << std::endl;
    std::cout << "Max work group size: " << q.get_device().get_info<info::device::max_work_group_size>() << std::endl;
    std::cout << "Max work item dimensions: " << q.get_device().get_info<info::device::max_work_item_dimensions>() << std::endl;

    return 0;
}




