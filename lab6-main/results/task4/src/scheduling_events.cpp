#include <CL/sycl.hpp>
using namespace sycl;

static const int N = 256;

int main() {
  queue q;
  std::cout << "Device : " << q.get_device().get_info<info::device::name>()
            << std::endl;

  int *data = malloc_shared<int>(N, q);

  for (int i = 0; i < N; i++) data[i] = 10;

  // Submitting kernels and capturing events
  auto e1 = q.submit([&] (handler& h) {
    h.parallel_for(range<1>(N), [=] (id<1> ID) {
      auto i = ID[0];
      data[i] += 2;
    });
  });

  auto e2 = q.submit([&] (handler& h) {
    h.depends_on(e1);
    h.parallel_for(range<1>(N), [=] (id<1> ID) {
      auto i = ID[0];
      data[i] += 3;
    });
  });

  auto e3 = q.submit([&] (handler& h) {
    h.depends_on(e2);
    h.parallel_for(range<1>(N), [=] (id<1> ID) {
      auto i = ID[0];
      data[i] += 5;
    });
  });

  // Wait for the last event to ensure all tasks are completed
  e3.wait();

  for (int i = 0; i < N; i++) std::cout << data[i] << " ";
  std::cout << std::endl;
  free(data, q);
  return 0;
}

