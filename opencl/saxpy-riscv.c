// ~/riscv/riscv_newlib/bin/clang -S saxpy-riscv.c

//OpenCL kernel which is run for every work item created.
#define __global __attribute__((address_space(1)))
int get_global_id(int index);

//__kernel: mask for LT's DSL
void saxpy_kernel(float alpha,    
                  __global float *A,      
                  __global float *B,      
                  __global float *C)      
{                                         
    //Get the index of the work-item      
    int index = get_global_id(0);         
    C[index] = alpha* A[index] + B[index];
}                                         

