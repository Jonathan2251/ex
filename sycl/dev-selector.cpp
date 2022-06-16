#include <CL/sycl.hpp>

int main() {
  class NEOGPUDeviceSelector : public cl::sycl::device_selector {
  public:
    int operator()(const cl::sycl::device &Device) const override {
      using namespace cl::sycl::info;

      const std::string DeviceName = Device.get_info<device::name>();
      const std::string DeviceVendor = Device.get_info<device::vendor>();

      std::cout << "in operator()" << std::endl;
      std::cout << "DeviceName: " << DeviceName << std::endl;
      std::cout << "DeviceVendor: " << DeviceVendor << std::endl;
      return Device.is_gpu() && (DeviceName.find("HD Graphics NEO") != std::string::npos);
    }
  };

  NEOGPUDeviceSelector Selector;
  try {
    cl::sycl::queue Queue(Selector);
    cl::sycl::device Device(Selector);
    std::cout << "in try" << std::endl;
  } catch (cl::sycl::invalid_parameter_error &E) {
    std::cout << E.what() << std::endl;
    std::cout << "in catch" << std::endl;
  }
  std::cout << "end" << std::endl;
}
