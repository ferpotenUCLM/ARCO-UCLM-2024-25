#include <CL/sycl.hpp>
using namespace sycl;

static const int N = 256;

int main() {
  queue q;
  
  auto R = range<1>{N};
  
  std::cout << "Device : " << q.get_device().get_info<info::device::name>()
            << std::endl;

  int *data = malloc_shared<int>(N, q);

  for (int i = 0; i < N; i++) data[i] = 10;

  // Submitting kernels and capturing events
  q.submit([&] (handler& h) {
    h.parallel_for(R, [=] (id<1> ID) {
      auto i = ID[0];
      data[i] += 2;
    });
  }).wait();

  q.submit([&] (handler& h) {
    h.parallel_for(R, [=] (id<1> ID) {
      auto i = ID[0];
      data[i] += 3;
    });
  }).wait();

  q.submit([&] (handler& h) {
    h.parallel_for(R, [=] (id<1> ID) {
      auto i = ID[0];
      data[i] += 5;
    });
  }).wait();

  // Wait for the last event to ensure all tasks are completed


  for (int i = 0; i < N; i++) std::cout << data[i] << " ";
  std::cout << std::endl;
  free(data, q);
  return 0;
}

