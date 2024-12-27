### Guía para realizar las modificaciones y responder a las preguntas

#### Paso 1: Modificar el código según los comentarios

1. **Obtener información del dispositivo**:
   - En la función `DpcppParallel`, imprime información sobre el dispositivo seleccionado.
   ```cpp
   std::cout << "Target Device: " << q.get_device().get_info<info::device::name>() << std::endl;
   ```

2. **Configurar los accesores**:
   - Para los buffers `bufin_vect1` y `bufin_vect2`, usa `read_only` ya que solo se leen.
   - Para el buffer `bufout_vect`, usa `write_only` ya que solo se escribe.
   ```cpp
   accessor V1(bufin_vect1, h, read_only);
   accessor V2(bufin_vect2, h, read_only);
   accessor V3(bufout_vect, h, write_only);
   ```

3. **Esperar a que el trabajo termine**:
   - Añade `q.wait();` después de la llamada a `q.submit` para asegurarte de que todas las tareas se completen antes de continuar.
   ```cpp
   q.wait();
   ```

#### Código modificado

```cpp
#include <CL/sycl.hpp>
#include <iomanip>
#include <vector>
#include "dpc_common.hpp"
#include "Complex.hpp"

using namespace sycl;
using namespace std;

// Number of complex numbers passing to the DPC++ code
static const int num_elements = 10000;

// in_vect1 and in_vect2 are the vectors with num_elements complex numbers and
// are inputs to the parallel function
void DpcppParallel(queue &q, std::vector<Complex2> &in_vect1,
                   std::vector<Complex2> &in_vect2,
                   std::vector<Complex2> &out_vect)
{
  auto R = range(in_vect1.size());

  buffer bufin_vect1(in_vect1);
  buffer bufin_vect2(in_vect2);
  buffer bufout_vect(out_vect);

  std::cout << "Target Device: " << q.get_device().get_info<info::device::name>() << std::endl;

  q.submit(&
           {
             accessor V1(bufin_vect1, h, read_only);
             accessor V2(bufin_vect2, h, read_only);
             accessor V3(bufout_vect, h, write_only);
             h.parallel_for(R, =
                            {
                              V3[i] = V1[i].complex_mul(V2[i]);
                            });
           });
  q.wait();
}

void DpcppScalar(std::vector<Complex2> &in_vect1,
                 std::vector<Complex2> &in_vect2,
                 std::vector<Complex2> &out_vect)
{
  for (int i = 0; i < in_vect1.size(); i++)
  {
    out_vect[i] = in_vect1[i].complex_mul(in_vect2[i]);
  }
}

// Compare the results of the two output vectors from parallel and scalar. They
// should be equal
int Compare(std::vector<Complex2> &v1, std::vector<Complex2> &v2)
{
  int ret_code = 1;
  if (v1.size() != v2.size())
  {
    ret_code = -1;
  }
  for (int i = 0; i < v1.size(); i++)
  {
    if (v1[i] != v2[i])
    {
      ret_code = -1;
      break;
    }
  }
  return ret_code;
}

int main()
{
  vector<Complex2> input_vect1;
  vector<Complex2> input_vect2;
  vector<Complex2> out_vect_parallel;
  vector<Complex2> out_vect_scalar;

  for (int i = 0; i < num_elements; i++)
  {
    input_vect1.push_back(Complex2(i + 2, i + 4));
    input_vect2.push_back(Complex2(i + 4, i + 6));
    out_vect_parallel.push_back(Complex2(0, 0));
    out_vect_scalar.push_back(Complex2(0, 0));
  }

  cpu_selector selector;
  queue q(selector, dpc_common::exception_handler);
  DpcppParallel(q, input_vect1, input_vect2, out_vect_parallel);

  std::cout << "****************************************Multiplying Complex numbers "
               "in Parallel********************************************************"
            << std::endl;

  int indices[]{0, 1, 2, 3, 4, (num_elements - 1)};
  constexpr size_t indices_size = sizeof(indices) / sizeof(int);

  for (int i = 0; i < indices_size; i++)
  {
    int j = indices[i];
    if (i == indices_size - 1)
      std::cout << "...\n";
    std::cout << "[" << j << "] " << input_vect1[j] << " * " << input_vect2[j]
              << " = " << out_vect_parallel[j] << "\n";
  }

  DpcppScalar(input_vect1, input_vect2, out_vect_scalar);

  int ret_code = Compare(out_vect_parallel, out_vect_scalar);
  if (ret_code == 1)
  {
    std::cout << "Complex multiplication successfully run on the device"
              << "\n";
  }
  else
    std::cout
        << "*********************************************Verification Failed. Results are "
           "not matched**************************"
        << "\n";

  return 0;
}
```

### Paso 2: Mostrar el resultado de salida
Compila y ejecuta el programa modificado para verificar los resultados.

```bash
dpcpp -o mult_complex mult_complex.cpp
./mult_complex
```

### Paso 3: Responder a las preguntas

1. **Resultado de salida**:
   - El resultado de salida debería mostrar la multiplicación de los números complejos en paralelo y verificar que los resultados coinciden con la multiplicación escalar.

2. **Abstracción para los contenedores de datos**:
   - Se están utilizando **buffers** (`buffer<int> A{R}, B{R};`) como abstracción para los contenedores de datos. Los buffers en SYCL gestionan la memoria y permiten la transferencia de datos entre el host y los dispositivos.

3. **Formación del DAG**:
   - El **DAG (Directed Acyclic Graph)** se forma **implícitamente**. SYCL gestiona las dependencias entre las tareas automáticamente a través del uso de accesores y buffers. Las dependencias se resuelven en función de los accesos de lectura y escritura especificados en los accesores.

4. **Dependencias y tipo de dependencias**:
   - **Kernel 1**: No tiene dependencias previas.
   - **Kernel 2**: Depende de la finalización de **Kernel 1** porque ambos escriben en el buffer `A`.
   - **Kernel 3**: No tiene dependencias previas.
   - **Kernel 4**: Depende de la finalización de **Kernel 2** (lectura de `A`) y **Kernel 3** (lectura y escritura de `B`).

Espero que esta guía te sea útil. Si tienes alguna pregunta adicional o necesitas más detalles, ¡no dudes en preguntar!
