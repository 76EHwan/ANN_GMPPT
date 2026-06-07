#include "ll_aton_NN_interface.h"
#include "ll_aton.h"
#include "ll_aton_ec_trace.h"

#if 0
// Workaround: the tracer does not know the target at this moment
// and cannot call the functions since are used in static code
#define ATON_LIB_PHYSICAL_TO_VIRTUAL_ADDR(address) LL_Address_Physical2Virtual(address)
#define ATON_LIB_VIRTUAL_TO_PHYSICAL_ADDR(address) LL_Address_Virtual2Physical(address)
#else
#define ATON_LIB_PHYSICAL_TO_VIRTUAL_ADDR(address) (address)
#define ATON_LIB_VIRTUAL_TO_PHYSICAL_ADDR(address) (address)
#endif

#define _mem_pool_xSPI2_network 1

// MCU cache line size: 32 (bytes)
// NPU cache line size: 64 (bytes)
// MCU+NPU cache line size equal to 64 bytes (power of 2 not less than 8)
unsigned int cache_line_size = 64;

mpool_reloc_info_t mpool_reloc_info[] = {
  {"AXISRAM6", "_mem_pool_AXISRAM6_network", 0x34350000, 1, 0},
  {"AXISRAM5", "_mem_pool_AXISRAM5_network", 0x342e0000, 1, 0},
  {"AXISRAM4", "_mem_pool_AXISRAM4_network", 0x34270000, 1, 0},
  {"AXISRAM3", "_mem_pool_AXISRAM3_network", 0x34200000, 1, 0},
  {"AXISRAM2", "_mem_pool_AXISRAM2_network", 0x34100000, 1, 0},
  {"AXISRAM1", "_mem_pool_AXISRAM1_network", 0x34064000, 1, 0},
  {"AXIFLEXMEM", "_mem_pool_AXIFLEXMEM_network", 0x34000000, 1, 0},
  {"xSPI1", "_mem_pool_xSPI1_network", 0x90000000, 1, 0},
  {"xSPI2", "_mem_pool_xSPI2_network", 0x1, 0, 0},
  {"AXISRAM2_AXISRAM3_AXISRAM4_AXISRAM5_AXISRAM6", "_mem_pool_AXISRAM2_AXISRAM3_AXISRAM4_AXISRAM5_AXISRAM6_network", 0x34100000, 1, 0},
  {NULL, NULL, 0, 0, 0}
};


static const uint64_t __ec_params_memory_pool_base[67] = {
0x000015002AAB0000ULL,0x300000001A252DB7ULL,0x21CD333300001DA0ULL,0x004723EB35550000ULL,0x2E21FFB926B33F96ULL,0x230033330000224DULL,0xFDDE22E030000000ULL,0x2AAB00001CA65889ULL,
0x1C77467AFF3D2455ULL,0x0000440000000000ULL,0x4000000013004000ULL,0x1100400000001200ULL,0x0000490000000000ULL,0x000000004A000000ULL,0x4C00000000004B00ULL,0x00004D0000000000ULL,
0x400000004E000000ULL,0x0A00400000000B00ULL,0x0000090040000000ULL,0x0000000052000000ULL,0x5400000000005300ULL,0xFF8932B71B6E0000ULL,0x1555000010AF4861ULL,0x0000000000003C55ULL,
0xF8D030F2F8000000ULL,0xF771A642F8000000ULL,0xF81E4C5FF7F31F02ULL,0xF79B60E1F82598BDULL,0xF80BD008F8B2CE76ULL,0xF8000000F7DE3A50ULL,0xF8000000F81B1707ULL,0xF86F167AF8354725ULL,
0xF7AA8014F6E39BB3ULL,0xF7ED36BCF7FC47BAULL,0xF754759CF82B81BEULL,0xF7C223EAF8000000ULL,0xF7EE0C8CF7F208C3ULL,0xF8C38405F765796AULL,0xF7ECD695F8950646ULL,0xF8000000F8000000ULL,
0xFBD9D006FBFB63FAULL,0xFC0385C3FBF7AB3EULL,0xFC1BF60DFBD8F4AAULL,0xFC2BD89EFC397A94ULL,0xFC0F0616FC28C756ULL,0xFC071D26FC25B933ULL,0xFBE0F76DFBA64F01ULL,0xFC623579FBF6EC6DULL,
0x4C143E61366A2830ULL,0x40F74931419821FDULL,0x33B0321F384346F8ULL,0x3B67482A31A243FEULL,0x43FA4AB030223DB6ULL,0x3AD13AFA42362E75ULL,0x4C2726E84D8F3737ULL,0x2D8732EE34534EBEULL,
0x5C7D136F3F952611ULL,0x470B3B464FFA24A6ULL,0x1FAC1E22170866DAULL,0x5495228D14523E4FULL,0x0706050403020100ULL,0x1E1D1CD4CC0B4908ULL,0x0000000000000071ULL,0x0000000000000000ULL,
0x0000000000000000ULL,0x0000000000000000ULL,0x0000000000000000ULL,
};

void trace_ec__ec_blob_network_1(void) {
  ec_trace_start_blob("_ec_blob_network_1");
  ec_trace_start_epoch(1);
  {
  }
  {
  }
  ec_trace_end_epoch(1);
  ec_trace_start_epoch(2);
  {
    /* Unit= 10 [CONV_ACC_V2 0] */
    /* kind=Conv node=Gemm_2_conv_4 */
    static const LL_Convacc_InitTypeDef Gemm_2_conv_4_init2 = {
      .simd = 2,
      .fsub = -118,
      .vshift = 0,
      .accumulate = 0,
      .rounding_f = 0,
      .saturation_f = 0,
      .round_mode_f = 0,
      .f_unsigned = 0,
      .k_unsigned = 0,
      .deepmode = 0,
      .dss2mode = 0,
      .kseten = 0,
      .zfbias = 0,
      .inbytes_f = 2,
      .shift_f = 0,
      .shift_a = 2,
      .rounding_o = 1,
      .saturation_o = 1,
      .round_mode_o = 1,
      .relu_mode_o = 0,
      .outbytes_o = 2,
      .shift_o = 2,
      .raw_o = 0,
      .fWidth = 1,
      .fHeight = 1,
      .kernelWidth = 1,
      .kernelHeight = 1,
      .nKernels = 16,
      .batchDepth = 16,
      .hstride = 1,
      .vstride = 1,
      .left_padding = 0,
      .right_padding = 0,
      .top_padding = 0,
      .bot_padding = 0,
      .left_crop = 0,
      .right_crop = 0,
      .top_crop = 0,
      .bot_crop = 0,
    };

    /* Unit=CONV_ACC_V2 */
    LL_Convacc_Init(0, &Gemm_2_conv_4_init2);


    /* Unit= 18 [ARITH_ACC_V2 0] */
    /* kind=Add node=Gemm_2_conv_4_off_bias_24 */
    static const LL_Arithacc_InitTypeDef Gemm_2_conv_4_off_bias_24_init2 = {
      .rounding_x = 0,
      .saturation_x = 0,
      .round_mode_x = 0,
      .inbytes_x = 2,
      .outbytes_x = 2,
      .shift_x = 0,
      .rounding_y = 0,
      .saturation_y = 0,
      .round_mode_y = 0,
      .inbytes_y = 2,
      .outbytes_y = 2,
      .combinebc = 1,
      .clipout = 0,
      .shift_y = 0,
      .rounding_o = 1,
      .saturation_o = 1,
      .round_mode_o = 1,
      .relu_mode_o = 0,
      .outbytes_o = 1,
      .shift_o = 20,
      .scalar = 0,
      .dualinput = 0,
      .operation = ARITH_AFFINE,
      .bcast = ARITH_BCAST_CHAN,
      .Ax_shift = 0,
      .By_shift = 0,
      .C_shift = 0,
      .fWidth = 1,
      .fHeight = 1,
      .fChannels = 32,
      .batchDepth = 16,
      .clipmin = 0,
      .clipmax = 0,
      .A_scalar = 0,
      .B_scalar = 0,
      .C_scalar = (short)0,
      .A_vector = {((unsigned char *)((((uintptr_t)(__ec_params_memory_pool_base)) + 384))) /* Equivalent hex offset = 0x180 */},
      .B_vector = {0},
      .C_vector = {((unsigned char *)((((uintptr_t)(__ec_params_memory_pool_base)) + 192))) /* Equivalent hex offset = 0xc0 */},
      .vec_precision = {16, 16, 32},
    };

    /* Unit=ARITH_ACC_V2 */
    LL_Arithacc_Init(0, &Gemm_2_conv_4_off_bias_24_init2);


    /* Unit= 19 [ARITH_ACC_V2 1] */
    /* kind=Sub node=Gemm_6_conv_10_suboff_27 */
    static const LL_Arithacc_InitTypeDef Gemm_6_conv_10_suboff_27_init2 = {
      .rounding_x = 0,
      .saturation_x = 0,
      .round_mode_x = 0,
      .inbytes_x = 1,
      .outbytes_x = 1,
      .shift_x = 0,
      .rounding_y = 0,
      .saturation_y = 0,
      .round_mode_y = 0,
      .inbytes_y = 1,
      .outbytes_y = 1,
      .combinebc = 1,
      .clipout = 0,
      .shift_y = 0,
      .rounding_o = 0,
      .saturation_o = 0,
      .round_mode_o = 1,
      .relu_mode_o = 0,
      .outbytes_o = 1,
      .shift_o = 14,
      .scalar = 1,
      .dualinput = 0,
      .operation = ARITH_AFFINE,
      .bcast = ARITH_BCAST_SCALAR,
      .Ax_shift = 0,
      .By_shift = 0,
      .C_shift = 0,
      .fWidth = 1,
      .fHeight = 1,
      .fChannels = 32,
      .batchDepth = 16,
      .clipmin = 0,
      .clipmax = 0,
      .A_scalar = 16384,
      .B_scalar = 32,
      .C_scalar = (short)0,
      .A_vector = {0},
      .B_vector = {0},
      .C_vector = {0},
      .vec_precision = {8, 8, 8},
    };

    /* Unit=ARITH_ACC_V2 */
    LL_Arithacc_Init(1, &Gemm_6_conv_10_suboff_27_init2);


    /* Dma inputs units to cycle: */
    /* Unit= 0 [STREAM_ENG_V2 0] */
    /* Emit conf for STREAM_ENG_V2 node=Gemm_2_conv_4 input ports=0 range=1[0,16] */

    static const LL_Streng_TensorInitTypeDef Gemm_2_conv_4_dma_init_in_0_2 = {
      /* 1x1x16(8 bits) */
      .dir = 0,
      .raw = 1,
      .noblk = 0,
      .align_right = 1,
      .nbits_unsigned = 0,
      .addr_base = {(unsigned char *)(0x342e0000UL) /* Equivalent hex address = 0x342e0000UL */}, /* Gemm_2_conv_4_zero_off_out_19 */
      .offset_start = 0,
      .offset_end = 16,
      .offset_limit = 80,
      .frame_count = 0,
      .fwidth = 0,
      .fheight = 0,
      .batch_depth = 0,
      .batch_offset = 0,
      .frame_offset = 16,
      .line_offset = 0,
      .loop_offset = 0,
      .frame_loop_cnt = 1,
      .frame_tot_cnt = 2,
      .nbits_in = 8,
      .nbits_out = 16,
    };

    /* Unit=STREAM_ENG_V2 */
    LL_Streng_TensorInit(0, &Gemm_2_conv_4_dma_init_in_0_2, 1);

    /* Unit= 1 [STREAM_ENG_V2 1] */
    /* Emit conf for STREAM_ENG_V2 node=Gemm_2_conv_4 input ports=1 range=8[528,1040] */

    static const LL_Streng_TensorInitTypeDef Gemm_2_conv_4_dma_init_in_1_2 = {
      /* 32x1x1x16(8 bits) */
      .dir = 0,
      .raw = 1,
      .continuous = 1,
      .noblk = 0,
      .align_right = 1,
      .nbits_unsigned = 0,
      .cacheable = 1,
      .cache_allocate = 0,
      .addr_base = {(unsigned char *)ATON_LIB_VIRTUAL_TO_PHYSICAL_ADDR((uintptr_t)_mem_pool_xSPI2_network)}, /* Gemm_2_weights_transposed_3 */
      .offset_start = 528,
      .offset_end = 1040,
      .offset_limit = 1104,
      .frame_count = 0,
      .fwidth = 0,
      .fheight = 0,
      .batch_depth = 0,
      .batch_offset = 0,
      .frame_offset = 0,
      .line_offset = 0,
      .loop_offset = 0,
      .frame_loop_cnt = 0,
      .frame_tot_cnt = 1,
      .nbits_in = 8,
      .nbits_out = 8,
    };

    /* Unit=STREAM_ENG_V2 */
    LL_Streng_TensorInit(1, &Gemm_2_conv_4_dma_init_in_1_2, 1);


    /* Dma input bandwidth from memory pools: */
    /* npuRAM5 -> 16 */
    /* octoFlash -> 512 */

    /* Dma output units from cycle: */
    /* Unit= 8 [STREAM_ENG_V2 8] */
    /* Emit conf for STREAM_ENG_V2 node=Gemm_6_conv_10_suboff_27 output ports=0 range=1[16,48] */

    static const LL_Streng_TensorInitTypeDef Gemm_6_conv_10_suboff_27_dma_init_out_0_2 = {
      /* to memory with batch=16 */
      .dir = 1,
      .raw = 1,
      .noblk = 0,
      .align_right = 0,
      .nbits_unsigned = 1,
      .addr_base = {(unsigned char *)(0x342e0000UL) /* Equivalent hex address = 0x342e0000UL */}, /* Gemm_6_conv_10_zero_off_out_28 */
      .offset_start = 16,
      .offset_end = 32,
      .offset_limit = 112,
      .frame_count = 0,
      .fwidth = 0,
      .fheight = 0,
      .batch_depth = 0,
      .batch_offset = 0,
      .frame_offset = 16,
      .line_offset = 0,
      .loop_offset = 0,
      .frame_loop_cnt = 0,
      .frame_tot_cnt = 2,
      .nbits_in = 8,
      .nbits_out = 8,
    };

    /* Unit=STREAM_ENG_V2 */
    LL_Streng_TensorInit(8, &Gemm_6_conv_10_suboff_27_dma_init_out_0_2, 1);


    /* Dma output bandwidth to memory pools: */
    /* npuRAM5 <- 32 */

    static const LL_Switch_InitTypeDef STREAM_SWITCH_0_init_in_2[] = {
      { LL_Switch_Init_Dest() = ATONN_DSTPORT(STRSWITCH, 0, CONVACC, 0, 0), LL_Switch_Init_Source(0) = ATONN_SRCPORT(STRSWITCH, 0, STRENG, 0, 0), LL_Switch_Init_Context(0) = 1, LL_Switch_Init_Frames(0) = 0, }, /* Gemm_2_conv_4 IN: in unit=CONV_ACC_V2 0 in port=0 out unit=STREAM_ENG_V2 0 out port=0 */
      { LL_Switch_Init_Dest() = ATONN_DSTPORT(STRSWITCH, 0, CONVACC, 0, 1), LL_Switch_Init_Source(0) = ATONN_SRCPORT(STRSWITCH, 0, STRENG, 1, 0), LL_Switch_Init_Context(0) = 1, LL_Switch_Init_Frames(0) = 0, }, /* Gemm_2_conv_4 IN: in unit=CONV_ACC_V2 0 in port=1 out unit=STREAM_ENG_V2 1 out port=0 */
      { LL_Switch_Init_Dest() = ATONN_DSTPORT(STRSWITCH, 0, ARITH, 0, 0), LL_Switch_Init_Source(0) = ATONN_SRCPORT(STRSWITCH, 0, CONVACC, 0, 0), LL_Switch_Init_Context(0) = 1, LL_Switch_Init_Frames(0) = 0, }, /* Gemm_2_conv_4_off_bias_24 IN: in unit=ARITH_ACC_V2 0 in port=0 out unit=CONV_ACC_V2 0 out port=0 */
      { LL_Switch_Init_Dest() = ATONN_DSTPORT(STRSWITCH, 0, ARITH, 1, 0), LL_Switch_Init_Source(0) = ATONN_SRCPORT(STRSWITCH, 0, ARITH, 0, 0), LL_Switch_Init_Context(0) = 1, LL_Switch_Init_Frames(0) = 0, }, /* Gemm_6_conv_10_suboff_27 IN: in unit=ARITH_ACC_V2 1 in port=0 out unit=ARITH_ACC_V2 0 out port=0 */
      { LL_Switch_Init_Dest() = ATONN_DSTPORT(STRSWITCH, 0, STRENG, 8, 0), LL_Switch_Init_Source(0) = ATONN_SRCPORT(STRSWITCH, 0, ARITH, 1, 0), LL_Switch_Init_Context(0) = 1, LL_Switch_Init_Frames(0) = 0, }, /* Gemm_6_conv_10_suboff_27 OUT: in unit=STREAM_ENG_V2 8 in port=0 out unit=ARITH_ACC_V2 1 out port=0 */
    };


    /* epoch=2 */
    LL_Switch_Init(STREAM_SWITCH_0_init_in_2, 5);

    static const LL_ATON_EnableUnits_InitTypeDef Enable_epoch_2_all_units[] = {
      { {STRENG, 8} }, /* STREAM_ENG_V2 */
      { {CONVACC, 0} }, /* CONV_ACC_V2 */
      { {ARITH, 0} }, /* ARITH_ACC_V2 */
      { {ARITH, 1} }, /* ARITH_ACC_V2 */
      { {STRENG, 0} }, /* STREAM_ENG_V2 */
      { {STRENG, 1} }, /* STREAM_ENG_V2 */
    };


    LL_ATON_EnableUnits_Init(Enable_epoch_2_all_units, 6);

  }

  ec_trace_wait_epoch_end(0x100);

  {
    static const LL_Switch_DeinitTypeDef STREAM_SWITCH_0_deinit_in_2[] = {
      { LL_Switch_Init_Dest() = ATONN_DSTPORT(STRSWITCH, 0, CONVACC, 0, 0), LL_Switch_Init_Source(0) = ATONN_SRCPORT(STRSWITCH, 0, STRENG, 0, 0), LL_Switch_Init_Context(0) = 1, LL_Switch_Init_Frames(0) = 0, }, /* Gemm_2_conv_4 IN: in unit=CONV_ACC_V2 0 in port=0 out unit=STREAM_ENG_V2 0 out port=0 */
      { LL_Switch_Init_Dest() = ATONN_DSTPORT(STRSWITCH, 0, CONVACC, 0, 1), LL_Switch_Init_Source(0) = ATONN_SRCPORT(STRSWITCH, 0, STRENG, 1, 0), LL_Switch_Init_Context(0) = 1, LL_Switch_Init_Frames(0) = 0, }, /* Gemm_2_conv_4 IN: in unit=CONV_ACC_V2 0 in port=1 out unit=STREAM_ENG_V2 1 out port=0 */
      { LL_Switch_Init_Dest() = ATONN_DSTPORT(STRSWITCH, 0, ARITH, 0, 0), LL_Switch_Init_Source(0) = ATONN_SRCPORT(STRSWITCH, 0, CONVACC, 0, 0), LL_Switch_Init_Context(0) = 1, LL_Switch_Init_Frames(0) = 0, }, /* Gemm_2_conv_4_off_bias_24 IN: in unit=ARITH_ACC_V2 0 in port=0 out unit=CONV_ACC_V2 0 out port=0 */
      { LL_Switch_Init_Dest() = ATONN_DSTPORT(STRSWITCH, 0, ARITH, 1, 0), LL_Switch_Init_Source(0) = ATONN_SRCPORT(STRSWITCH, 0, ARITH, 0, 0), LL_Switch_Init_Context(0) = 1, LL_Switch_Init_Frames(0) = 0, }, /* Gemm_6_conv_10_suboff_27 IN: in unit=ARITH_ACC_V2 1 in port=0 out unit=ARITH_ACC_V2 0 out port=0 */
      { LL_Switch_Init_Dest() = ATONN_DSTPORT(STRSWITCH, 0, STRENG, 8, 0), LL_Switch_Init_Source(0) = ATONN_SRCPORT(STRSWITCH, 0, ARITH, 1, 0), LL_Switch_Init_Context(0) = 1, LL_Switch_Init_Frames(0) = 0, }, /* Gemm_6_conv_10_suboff_27 OUT: in unit=STREAM_ENG_V2 8 in port=0 out unit=ARITH_ACC_V2 1 out port=0 */
    };


    /* epoch=2 */
    LL_Switch_Deinit(STREAM_SWITCH_0_deinit_in_2, 5);

    static const LL_ATON_DisableUnits_InitTypeDef Disable_epoch_2_all_units[] = {
      { {STRENG, 8} }, /* STREAM_ENG_V2 */
      { {CONVACC, 0} }, /* CONV_ACC_V2 */
      { {ARITH, 0} }, /* ARITH_ACC_V2 */
      { {ARITH, 1} }, /* ARITH_ACC_V2 */
      { {STRENG, 0} }, /* STREAM_ENG_V2 */
      { {STRENG, 1} }, /* STREAM_ENG_V2 */
    };


    LL_ATON_DisableUnits_Init(Disable_epoch_2_all_units, 6);

  }
  ec_trace_end_epoch(2);
  ec_trace_start_epoch(3);
  {
    /* Unit= 11 [CONV_ACC_V2 1] */
    /* kind=Conv node=Gemm_6_conv_10 */
    static const LL_Convacc_InitTypeDef Gemm_6_conv_10_init3 = {
      .simd = 1,
      .fsub = 0,
      .vshift = 0,
      .accumulate = 0,
      .rounding_f = 0,
      .saturation_f = 0,
      .round_mode_f = 0,
      .f_unsigned = 1,
      .k_unsigned = 0,
      .deepmode = 1,
      .dss2mode = 0,
      .kseten = 3,
      .zfbias = 0,
      .inbytes_f = 3,
      .shift_f = 0,
      .shift_a = 2,
      .rounding_o = 1,
      .saturation_o = 1,
      .round_mode_o = 1,
      .relu_mode_o = 0,
      .outbytes_o = 2,
      .shift_o = 2,
      .raw_o = 0,
      .fWidth = 1,
      .fHeight = 1,
      .kernelWidth = 1,
      .kernelHeight = 1,
      .nKernels = 16,
      .batchDepth = 32,
      .hstride = 1,
      .vstride = 1,
      .left_padding = 0,
      .right_padding = 0,
      .top_padding = 0,
      .bot_padding = 0,
      .left_crop = 0,
      .right_crop = 0,
      .top_crop = 0,
      .bot_crop = 0,
    };

    /* Unit=CONV_ACC_V2 */
    LL_Convacc_Init(1, &Gemm_6_conv_10_init3);


    /* Unit= 20 [ARITH_ACC_V2 2] */
    /* kind=Add node=Gemm_6_conv_10_off_bias_33 */
    static const LL_Arithacc_InitTypeDef Gemm_6_conv_10_off_bias_33_init3 = {
      .rounding_x = 0,
      .saturation_x = 0,
      .round_mode_x = 0,
      .inbytes_x = 2,
      .outbytes_x = 2,
      .shift_x = 0,
      .rounding_y = 0,
      .saturation_y = 0,
      .round_mode_y = 0,
      .inbytes_y = 2,
      .outbytes_y = 2,
      .combinebc = 1,
      .clipout = 0,
      .shift_y = 0,
      .rounding_o = 1,
      .saturation_o = 1,
      .round_mode_o = 1,
      .relu_mode_o = 0,
      .outbytes_o = 1,
      .shift_o = 19,
      .scalar = 0,
      .dualinput = 0,
      .operation = ARITH_AFFINE,
      .bcast = ARITH_BCAST_CHAN,
      .Ax_shift = 0,
      .By_shift = 0,
      .C_shift = 0,
      .fWidth = 1,
      .fHeight = 1,
      .fChannels = 16,
      .batchDepth = 16,
      .clipmin = 0,
      .clipmax = 0,
      .A_scalar = 0,
      .B_scalar = 0,
      .C_scalar = (short)0,
      .A_vector = {((unsigned char *)((((uintptr_t)(__ec_params_memory_pool_base)) + 448))) /* Equivalent hex offset = 0x1c0 */},
      .B_vector = {0},
      .C_vector = {((unsigned char *)((((uintptr_t)(__ec_params_memory_pool_base)) + 320))) /* Equivalent hex offset = 0x140 */},
      .vec_precision = {16, 16, 32},
    };

    /* Unit=ARITH_ACC_V2 */
    LL_Arithacc_Init(2, &Gemm_6_conv_10_off_bias_33_init3);


    /* Unit= 21 [ARITH_ACC_V2 3] */
    /* kind=Sub node=Gemm_10_conv_16_suboff_36 */
    static const LL_Arithacc_InitTypeDef Gemm_10_conv_16_suboff_36_init3 = {
      .rounding_x = 0,
      .saturation_x = 0,
      .round_mode_x = 0,
      .inbytes_x = 1,
      .outbytes_x = 1,
      .shift_x = 0,
      .rounding_y = 0,
      .saturation_y = 0,
      .round_mode_y = 0,
      .inbytes_y = 1,
      .outbytes_y = 1,
      .combinebc = 1,
      .clipout = 0,
      .shift_y = 0,
      .rounding_o = 0,
      .saturation_o = 0,
      .round_mode_o = 1,
      .relu_mode_o = 0,
      .outbytes_o = 1,
      .shift_o = 14,
      .scalar = 1,
      .dualinput = 0,
      .operation = ARITH_AFFINE,
      .bcast = ARITH_BCAST_SCALAR,
      .Ax_shift = 0,
      .By_shift = 0,
      .C_shift = 0,
      .fWidth = 1,
      .fHeight = 1,
      .fChannels = 16,
      .batchDepth = 16,
      .clipmin = 0,
      .clipmax = 0,
      .A_scalar = 16384,
      .B_scalar = 32,
      .C_scalar = (short)0,
      .A_vector = {0},
      .B_vector = {0},
      .C_vector = {0},
      .vec_precision = {8, 8, 8},
    };

    /* Unit=ARITH_ACC_V2 */
    LL_Arithacc_Init(3, &Gemm_10_conv_16_suboff_36_init3);


    /* Unit= 12 [CONV_ACC_V2 2] */
    /* kind=Conv node=Gemm_10_conv_16 */
    static const LL_Convacc_InitTypeDef Gemm_10_conv_16_init3 = {
      .simd = 1,
      .fsub = 0,
      .vshift = 0,
      .accumulate = 0,
      .rounding_f = 0,
      .saturation_f = 0,
      .round_mode_f = 0,
      .f_unsigned = 1,
      .k_unsigned = 0,
      .deepmode = 0,
      .dss2mode = 0,
      .kseten = 0,
      .zfbias = 0,
      .inbytes_f = 1,
      .shift_f = 0,
      .shift_a = 1,
      .rounding_o = 1,
      .saturation_o = 1,
      .round_mode_o = 1,
      .relu_mode_o = 0,
      .outbytes_o = 2,
      .shift_o = 1,
      .raw_o = 1,
      .fWidth = 1,
      .fHeight = 1,
      .kernelWidth = 1,
      .kernelHeight = 1,
      .nKernels = 1,
      .batchDepth = 16,
      .hstride = 1,
      .vstride = 1,
      .left_padding = 0,
      .right_padding = 0,
      .top_padding = 0,
      .bot_padding = 0,
      .left_crop = 0,
      .right_crop = 0,
      .top_crop = 0,
      .bot_crop = 0,
    };

    /* Unit=CONV_ACC_V2 */
    LL_Convacc_Init(2, &Gemm_10_conv_16_init3);


    /* Unit= 18 [ARITH_ACC_V2 0] */
    /* kind=Add node=Gemm_10_conv_16_off_bias_42 */
    static const LL_Arithacc_InitTypeDef Gemm_10_conv_16_off_bias_42_init3 = {
      .rounding_x = 0,
      .saturation_x = 0,
      .round_mode_x = 0,
      .inbytes_x = 2,
      .outbytes_x = 2,
      .shift_x = 0,
      .rounding_y = 0,
      .saturation_y = 0,
      .round_mode_y = 0,
      .inbytes_y = 2,
      .outbytes_y = 2,
      .combinebc = 1,
      .clipout = 0,
      .shift_y = 0,
      .rounding_o = 1,
      .saturation_o = 1,
      .round_mode_o = 1,
      .relu_mode_o = 0,
      .outbytes_o = 1,
      .shift_o = 19,
      .scalar = 1,
      .dualinput = 0,
      .operation = ARITH_AFFINE,
      .bcast = ARITH_BCAST_SCALAR,
      .Ax_shift = 0,
      .By_shift = 13,
      .C_shift = 0,
      .fWidth = 1,
      .fHeight = 1,
      .fChannels = 1,
      .batchDepth = 1,
      .clipmin = 0,
      .clipmax = 0,
      .A_scalar = 17686,
      .B_scalar = -327,
      .C_scalar = (short)103,
      .A_vector = {0},
      .B_vector = {0},
      .C_vector = {0},
      .vec_precision = {16, 16, 16},
    };

    /* Unit=ARITH_ACC_V2 */
    LL_Arithacc_Init(0, &Gemm_10_conv_16_off_bias_42_init3);


    /* Unit= 16 [ACTIV_ACC_V2 0] */
    /* kind=Sigmoid node=Sigmoid_13 */
    static const LL_Activacc_InitTypeDef Sigmoid_13_init3 = {
      .rounding_f = 0,
      .saturation_f = 0,
      .round_mode_f = 0,
      .inbytes_f = 1,
      .outbytes_f = 1,
      .rounding_o = 1,
      .saturation_o = 1,
      .round_mode_o = 1,
      .relu_mode_o = 0,
      .outbytes_o = 1,
      .signedop = 1,
      .shift_f = 0,
      .shift_o = 15,
      .parameter = 32640,
      .parameter_2 = 0,
      .ROM0_vector = {((unsigned char *)(ATON_LIB_VIRTUAL_TO_PHYSICAL_ADDR(((uintptr_t)(__ec_params_memory_pool_base)) + 480))) /* Equivalent hex offset = 0x1e0 */},
      .ROM1_vector = {((unsigned char *)(ATON_LIB_VIRTUAL_TO_PHYSICAL_ADDR(((uintptr_t)(__ec_params_memory_pool_base)) + 0))) /* Equivalent hex offset = 0x0 */},
      .ROM0_nbytes = 16,
      .ROM1_nbytes = 186,
      .shift_b = 1,
      .shift_c = 7,
      .shift_norm = 8,
      .bwidth = 4,
      .fsub = 0,
      .operation = ACTIV_FUNC,
    };

    /* Unit=ACTIV_ACC_V2 */
    LL_Activacc_Init(0, &Sigmoid_13_init3);


    /* Dma inputs units to cycle: */
    /* Unit= 6 [STREAM_ENG_V2 6] */
    /* Emit conf for STREAM_ENG_V2 node=Gemm_6_conv_10 input ports=0 range=1[16,48] */

    static const LL_Streng_TensorInitTypeDef Gemm_6_conv_10_dma_init_in_0_3 = {
      /* 1x1x32(8 bits) */
      .dir = 0,
      .raw = 1,
      .raw_out = 1,
      .noblk = 0,
      .align_right = 0,
      .nbits_unsigned = 1,
      .addr_base = {(unsigned char *)(0x342e0000UL) /* Equivalent hex address = 0x342e0000UL */}, /* Gemm_6_conv_10_zero_off_out_28 */
      .offset_start = 16,
      .offset_end = 49,
      .offset_limit = 112,
      .frame_count = 0,
      .fwidth = 0,
      .fheight = 0,
      .batch_depth = 0,
      .batch_offset = 0,
      .frame_offset = 0,
      .line_offset = 0,
      .loop_offset = 32,
      .frame_loop_cnt = 1,
      .frame_tot_cnt = 1,
      .nbits_in = 24,
      .nbits_out = 24,
    };

    /* Unit=STREAM_ENG_V2 */
    LL_Streng_TensorInit(6, &Gemm_6_conv_10_dma_init_in_0_3, 1);

    /* Unit= 4 [STREAM_ENG_V2 4] */
    /* Emit conf for STREAM_ENG_V2 node=Gemm_6_conv_10 input ports=1 range=8[0,513] */

    static const LL_Streng_TensorInitTypeDef Gemm_6_conv_10_dma_init_in_1_3 = {
      /* 16x1x1x32(8 bits) */
      .dir = 0,
      .raw = 1,
      .continuous = 1,
      .noblk = 0,
      .align_right = 0,
      .nbits_unsigned = 0,
      .cacheable = 1,
      .cache_allocate = 0,
      .addr_base = {(unsigned char *)ATON_LIB_VIRTUAL_TO_PHYSICAL_ADDR((uintptr_t)_mem_pool_xSPI2_network)}, /* Gemm_6_weights_transposed_9 */
      .offset_start = 0,
      .offset_end = 513,
      .offset_limit = 584,
      .frame_count = 0,
      .fwidth = 0,
      .fheight = 0,
      .batch_depth = 0,
      .batch_offset = 0,
      .frame_offset = 0,
      .line_offset = 0,
      .loop_offset = 0,
      .frame_loop_cnt = 0,
      .frame_tot_cnt = 1,
      .nbits_in = 24,
      .nbits_out = 24,
    };

    /* Unit=STREAM_ENG_V2 */
    LL_Streng_TensorInit(4, &Gemm_6_conv_10_dma_init_in_1_3, 1);

    /* Unit= 9 [STREAM_ENG_V2 9] */
    /* Emit conf for STREAM_ENG_V2 node=Gemm_10_conv_16 input ports=1 range=8[1040,1056] */

    static const LL_Streng_TensorInitTypeDef Gemm_10_conv_16_dma_init_in_1_3 = {
      /* 1x1x1x16(8 bits) */
      .dir = 0,
      .raw = 1,
      .continuous = 1,
      .noblk = 0,
      .align_right = 0,
      .nbits_unsigned = 0,
      .cacheable = 1,
      .cache_allocate = 0,
      .addr_base = {(unsigned char *)ATON_LIB_VIRTUAL_TO_PHYSICAL_ADDR((uintptr_t)_mem_pool_xSPI2_network)}, /* Gemm_10_weights_transposed_15 */
      .offset_start = 1040,
      .offset_end = 1056,
      .offset_limit = 1120,
      .frame_count = 0,
      .fwidth = 0,
      .fheight = 0,
      .batch_depth = 0,
      .batch_offset = 0,
      .frame_offset = 0,
      .line_offset = 0,
      .loop_offset = 0,
      .frame_loop_cnt = 0,
      .frame_tot_cnt = 1,
      .nbits_in = 8,
      .nbits_out = 8,
    };

    /* Unit=STREAM_ENG_V2 */
    LL_Streng_TensorInit(9, &Gemm_10_conv_16_dma_init_in_1_3, 1);


    /* Dma input bandwidth from memory pools: */
    /* npuRAM5 -> 32 */
    /* octoFlash -> 528 */

    /* Dma output units from cycle: */
    /* Unit= 2 [STREAM_ENG_V2 2] */
    /* Emit conf for STREAM_ENG_V2 node=Sigmoid_13 output ports=0 range=1[0,1] */

    static const LL_Streng_TensorInitTypeDef Sigmoid_13_dma_init_out_0_3 = {
      /* to memory with batch=1 */
      .dir = 1,
      .raw = 1,
      .noblk = 0,
      .align_right = 0,
      .nbits_unsigned = 0,
      .addr_base = {(unsigned char *)(0x342e0000UL) /* Equivalent hex address = 0x342e0000UL */}, /* Quantize_14_out_0 */
      .offset_start = 0,
      .offset_end = 1,
      .offset_limit = 72,
      .frame_count = 0,
      .fwidth = 0,
      .fheight = 0,
      .batch_depth = 0,
      .batch_offset = 0,
      .frame_offset = 1,
      .line_offset = 0,
      .loop_offset = 0,
      .frame_loop_cnt = 0,
      .frame_tot_cnt = 1,
      .nbits_in = 8,
      .nbits_out = 8,
    };

    /* Unit=STREAM_ENG_V2 */
    LL_Streng_TensorInit(2, &Sigmoid_13_dma_init_out_0_3, 1);


    /* Dma output bandwidth to memory pools: */
    /* npuRAM5 <- 1 */

    static const LL_Switch_InitTypeDef STREAM_SWITCH_0_init_in_3[] = {
      { LL_Switch_Init_Dest() = ATONN_DSTPORT(STRSWITCH, 0, CONVACC, 1, 0), LL_Switch_Init_Source(0) = ATONN_SRCPORT(STRSWITCH, 0, STRENG, 6, 0), LL_Switch_Init_Context(0) = 1, LL_Switch_Init_Frames(0) = 0, }, /* Gemm_6_conv_10 IN: in unit=CONV_ACC_V2 1 in port=0 out unit=STREAM_ENG_V2 6 out port=0 */
      { LL_Switch_Init_Dest() = ATONN_DSTPORT(STRSWITCH, 0, CONVACC, 1, 1), LL_Switch_Init_Source(0) = ATONN_SRCPORT(STRSWITCH, 0, STRENG, 4, 0), LL_Switch_Init_Context(0) = 1, LL_Switch_Init_Frames(0) = 0, }, /* Gemm_6_conv_10 IN: in unit=CONV_ACC_V2 1 in port=1 out unit=STREAM_ENG_V2 4 out port=0 */
      { LL_Switch_Init_Dest() = ATONN_DSTPORT(STRSWITCH, 0, ARITH, 2, 0), LL_Switch_Init_Source(0) = ATONN_SRCPORT(STRSWITCH, 0, CONVACC, 1, 0), LL_Switch_Init_Context(0) = 1, LL_Switch_Init_Frames(0) = 0, }, /* Gemm_6_conv_10_off_bias_33 IN: in unit=ARITH_ACC_V2 2 in port=0 out unit=CONV_ACC_V2 1 out port=0 */
      { LL_Switch_Init_Dest() = ATONN_DSTPORT(STRSWITCH, 0, ARITH, 3, 0), LL_Switch_Init_Source(0) = ATONN_SRCPORT(STRSWITCH, 0, ARITH, 2, 0), LL_Switch_Init_Context(0) = 1, LL_Switch_Init_Frames(0) = 0, }, /* Gemm_10_conv_16_suboff_36 IN: in unit=ARITH_ACC_V2 3 in port=0 out unit=ARITH_ACC_V2 2 out port=0 */
      { LL_Switch_Init_Dest() = ATONN_DSTPORT(STRSWITCH, 0, CONVACC, 2, 0), LL_Switch_Init_Source(0) = ATONN_SRCPORT(STRSWITCH, 0, ARITH, 3, 0), LL_Switch_Init_Context(0) = 1, LL_Switch_Init_Frames(0) = 1, LL_Switch_Init_Source(1) = ATONN_SRCPORT(STRSWITCH, 0, ARITH, 3, 0), LL_Switch_Init_Context(1) = 0, LL_Switch_Init_Frames(1) = 255, }, /* Gemm_10_conv_16 IN: in unit=CONV_ACC_V2 2 in port=0 out unit=ARITH_ACC_V2 3 out port=0 */
      { LL_Switch_Init_Dest() = ATONN_DSTPORT(STRSWITCH, 0, CONVACC, 2, 1), LL_Switch_Init_Source(0) = ATONN_SRCPORT(STRSWITCH, 0, STRENG, 9, 0), LL_Switch_Init_Context(0) = 1, LL_Switch_Init_Frames(0) = 0, }, /* Gemm_10_conv_16 IN: in unit=CONV_ACC_V2 2 in port=1 out unit=STREAM_ENG_V2 9 out port=0 */
      { LL_Switch_Init_Dest() = ATONN_DSTPORT(STRSWITCH, 0, ARITH, 0, 0), LL_Switch_Init_Source(0) = ATONN_SRCPORT(STRSWITCH, 0, CONVACC, 2, 0), LL_Switch_Init_Context(0) = 1, LL_Switch_Init_Frames(0) = 0, }, /* Gemm_10_conv_16_off_bias_42 IN: in unit=ARITH_ACC_V2 0 in port=0 out unit=CONV_ACC_V2 2 out port=0 */
      { LL_Switch_Init_Dest() = ATONN_DSTPORT(STRSWITCH, 0, ACTIV, 0, 0), LL_Switch_Init_Source(0) = ATONN_SRCPORT(STRSWITCH, 0, ARITH, 0, 0), LL_Switch_Init_Context(0) = 1, LL_Switch_Init_Frames(0) = 0, }, /* Sigmoid_13 IN: in unit=ACTIV_ACC_V2 0 in port=0 out unit=ARITH_ACC_V2 0 out port=0 */
      { LL_Switch_Init_Dest() = ATONN_DSTPORT(STRSWITCH, 0, STRENG, 2, 0), LL_Switch_Init_Source(0) = ATONN_SRCPORT(STRSWITCH, 0, ACTIV, 0, 0), LL_Switch_Init_Context(0) = 1, LL_Switch_Init_Frames(0) = 0, }, /* Sigmoid_13 OUT: in unit=STREAM_ENG_V2 2 in port=0 out unit=ACTIV_ACC_V2 0 out port=0 */
    };


    /* epoch=3 */
    LL_Switch_Init(STREAM_SWITCH_0_init_in_3, 9);

    static const LL_ATON_EnableUnits_InitTypeDef Enable_epoch_3_all_units[] = {
      { {STRENG, 2} }, /* STREAM_ENG_V2 */
      { {CONVACC, 1} }, /* CONV_ACC_V2 */
      { {CONVACC, 2} }, /* CONV_ACC_V2 */
      { {ACTIV, 0} }, /* ACTIV_ACC_V2 */
      { {ARITH, 0} }, /* ARITH_ACC_V2 */
      { {ARITH, 2} }, /* ARITH_ACC_V2 */
      { {ARITH, 3} }, /* ARITH_ACC_V2 */
      { {STRENG, 4} }, /* STREAM_ENG_V2 */
      { {STRENG, 6} }, /* STREAM_ENG_V2 */
      { {STRENG, 9} }, /* STREAM_ENG_V2 */
    };


    LL_ATON_EnableUnits_Init(Enable_epoch_3_all_units, 10);

  }

  ec_trace_wait_epoch_end(0x4);

  {
    static const LL_Switch_DeinitTypeDef STREAM_SWITCH_0_deinit_in_3[] = {
      { LL_Switch_Init_Dest() = ATONN_DSTPORT(STRSWITCH, 0, CONVACC, 1, 0), LL_Switch_Init_Source(0) = ATONN_SRCPORT(STRSWITCH, 0, STRENG, 6, 0), LL_Switch_Init_Context(0) = 1, LL_Switch_Init_Frames(0) = 0, }, /* Gemm_6_conv_10 IN: in unit=CONV_ACC_V2 1 in port=0 out unit=STREAM_ENG_V2 6 out port=0 */
      { LL_Switch_Init_Dest() = ATONN_DSTPORT(STRSWITCH, 0, CONVACC, 1, 1), LL_Switch_Init_Source(0) = ATONN_SRCPORT(STRSWITCH, 0, STRENG, 4, 0), LL_Switch_Init_Context(0) = 1, LL_Switch_Init_Frames(0) = 0, }, /* Gemm_6_conv_10 IN: in unit=CONV_ACC_V2 1 in port=1 out unit=STREAM_ENG_V2 4 out port=0 */
      { LL_Switch_Init_Dest() = ATONN_DSTPORT(STRSWITCH, 0, ARITH, 2, 0), LL_Switch_Init_Source(0) = ATONN_SRCPORT(STRSWITCH, 0, CONVACC, 1, 0), LL_Switch_Init_Context(0) = 1, LL_Switch_Init_Frames(0) = 0, }, /* Gemm_6_conv_10_off_bias_33 IN: in unit=ARITH_ACC_V2 2 in port=0 out unit=CONV_ACC_V2 1 out port=0 */
      { LL_Switch_Init_Dest() = ATONN_DSTPORT(STRSWITCH, 0, ARITH, 3, 0), LL_Switch_Init_Source(0) = ATONN_SRCPORT(STRSWITCH, 0, ARITH, 2, 0), LL_Switch_Init_Context(0) = 1, LL_Switch_Init_Frames(0) = 0, }, /* Gemm_10_conv_16_suboff_36 IN: in unit=ARITH_ACC_V2 3 in port=0 out unit=ARITH_ACC_V2 2 out port=0 */
      { LL_Switch_Init_Dest() = ATONN_DSTPORT(STRSWITCH, 0, CONVACC, 2, 0), LL_Switch_Init_Source(0) = ATONN_SRCPORT(STRSWITCH, 0, ARITH, 3, 0), LL_Switch_Init_Context(0) = 1, LL_Switch_Init_Frames(0) = 1, LL_Switch_Init_Source(1) = ATONN_SRCPORT(STRSWITCH, 0, ARITH, 3, 0), LL_Switch_Init_Context(1) = 0, LL_Switch_Init_Frames(1) = 255, }, /* Gemm_10_conv_16 IN: in unit=CONV_ACC_V2 2 in port=0 out unit=ARITH_ACC_V2 3 out port=0 */
      { LL_Switch_Init_Dest() = ATONN_DSTPORT(STRSWITCH, 0, CONVACC, 2, 1), LL_Switch_Init_Source(0) = ATONN_SRCPORT(STRSWITCH, 0, STRENG, 9, 0), LL_Switch_Init_Context(0) = 1, LL_Switch_Init_Frames(0) = 0, }, /* Gemm_10_conv_16 IN: in unit=CONV_ACC_V2 2 in port=1 out unit=STREAM_ENG_V2 9 out port=0 */
      { LL_Switch_Init_Dest() = ATONN_DSTPORT(STRSWITCH, 0, ARITH, 0, 0), LL_Switch_Init_Source(0) = ATONN_SRCPORT(STRSWITCH, 0, CONVACC, 2, 0), LL_Switch_Init_Context(0) = 1, LL_Switch_Init_Frames(0) = 0, }, /* Gemm_10_conv_16_off_bias_42 IN: in unit=ARITH_ACC_V2 0 in port=0 out unit=CONV_ACC_V2 2 out port=0 */
      { LL_Switch_Init_Dest() = ATONN_DSTPORT(STRSWITCH, 0, ACTIV, 0, 0), LL_Switch_Init_Source(0) = ATONN_SRCPORT(STRSWITCH, 0, ARITH, 0, 0), LL_Switch_Init_Context(0) = 1, LL_Switch_Init_Frames(0) = 0, }, /* Sigmoid_13 IN: in unit=ACTIV_ACC_V2 0 in port=0 out unit=ARITH_ACC_V2 0 out port=0 */
      { LL_Switch_Init_Dest() = ATONN_DSTPORT(STRSWITCH, 0, STRENG, 2, 0), LL_Switch_Init_Source(0) = ATONN_SRCPORT(STRSWITCH, 0, ACTIV, 0, 0), LL_Switch_Init_Context(0) = 1, LL_Switch_Init_Frames(0) = 0, }, /* Sigmoid_13 OUT: in unit=STREAM_ENG_V2 2 in port=0 out unit=ACTIV_ACC_V2 0 out port=0 */
    };


    /* epoch=3 */
    LL_Switch_Deinit(STREAM_SWITCH_0_deinit_in_3, 9);

    static const LL_ATON_DisableUnits_InitTypeDef Disable_epoch_3_all_units[] = {
      { {STRENG, 2} }, /* STREAM_ENG_V2 */
      { {CONVACC, 1} }, /* CONV_ACC_V2 */
      { {CONVACC, 2} }, /* CONV_ACC_V2 */
      { {ACTIV, 0} }, /* ACTIV_ACC_V2 */
      { {ARITH, 0} }, /* ARITH_ACC_V2 */
      { {ARITH, 2} }, /* ARITH_ACC_V2 */
      { {ARITH, 3} }, /* ARITH_ACC_V2 */
      { {STRENG, 4} }, /* STREAM_ENG_V2 */
      { {STRENG, 6} }, /* STREAM_ENG_V2 */
      { {STRENG, 9} }, /* STREAM_ENG_V2 */
    };


    LL_ATON_DisableUnits_Init(Disable_epoch_3_all_units, 10);

  }
  ec_trace_end_epoch(3);
  ec_trace_start_epoch(4);
  {
    /* Dma input bandwidth from memory pools: */
    /* npuRAM5 -> 0 */

  }
  {
  }
  ec_trace_end_epoch(4);
  ec_trace_end_blob("_ec_blob_network_1");
}


int main () {
  ec_trace_init("network_ecblobs.h", "network", false, 0, false);
  trace_ec__ec_blob_network_1();
  ec_trace_all_blobs_done();
}
