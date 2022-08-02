// ~/riscv/riscv_newlib/bin/clang -S saxpy-riscv.c

//OpenCL kernel which is run for every work item created.
#define __global __attribute__((address_space(1)))
int get_global_id(int index);
int get_local_id(int index);

//__kernel: mask for LT's DSL
void saxpy_kernel(float alpha,    
                  __global float *A,      
                  __global float *B,      
                  __global float *C)      
{
  // global: DRAM, local: SRM
  //Get the index of the work-item
  // size_t get_global_id(uint dimension): Returns the index of the current work-item in the global space in the requested dimension
  // The call to get_global_id() returns different values for each work-item referring to different points in the iteration space 
  // PE0: index=0, PE1: index=1024
  int from = get_global_id(0);
  // size_t get_local_id(uint dimension): Returns the index of the current work-item as an offset from the beginning of the current work-group
  //int from = get_local_id(0);
  int to = from + 1024;
#ifdef riscv_scalar
  for (int i = from; i < to; i++) {   
    C[i] = alpha* A[i] + B[i];
  }
#elif riscv_rvv
    // riscv vector vmul and vadd
#elif BMC
    // BMC vmul
#endif
}                                         

