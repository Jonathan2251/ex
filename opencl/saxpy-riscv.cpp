// ~/riscv/riscv_newlib/bin/clang -S saxpy-riscv.c

// 14 PEs. BMC and RISCV is one-to-one in a PE. oMac is one-to-all PEs.

//OpenCL kernel which is run for every work item created.
#define __global __attribute__((address_space(1)))
int get_global_id(int index);
int get_local_id(int index);
int oMacAvailable = 1;
void runOMAC();
int isBMCIdx(int idx);
void runBMC(int idx);
int isRISCVIdx(int idx);

#define OMAC_WORK_IDX 16*1024

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
  // PE0: BMC:index=0, RISCV:index=512
  // PE1: BMC:index=1024, RISCV:index=1024+512
  int from = get_global_id(0);
  // size_t get_local_id(uint dimension): Returns the index of the current work-item as an offset from the beginning of the current work-group
  //int from = get_local_id(0);
  int to = from + 1024;
  if (oMacAvailable) {
    if (from >= OMAC_WORK_IDX) {
      runOMAC();
    }
  }
  if (isBMCIdx(from)) {
    runBMC(from);
  }
  else if (isRISCVIdx(from)) {
  #ifdef riscv_scalar
    for (int i = from; i < to; i++) {   
      C[i] = alpha* A[i] + B[i];
    }
  #elif riscv_rvv
    // riscv vector vmul and vadd
  #endif
  }
}                                         

