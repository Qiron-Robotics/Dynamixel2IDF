#ifndef DYNAMIXEL_CONFIG_H_
#define DYNAMIXEL_CONFIG_H_

#define ENABLE_ACTUATOR_AX              0
#define ENABLE_ACTUATOR_DX              0
#define ENABLE_ACTUATOR_RX              0
#define ENABLE_ACTUATOR_EX              0
#define ENABLE_ACTUATOR_MX12W           0
#define ENABLE_ACTUATOR_MX28            0
#define ENABLE_ACTUATOR_MX64            0
#define ENABLE_ACTUATOR_MX106           0
#define ENABLE_ACTUATOR_MX28_PROTOCOL2  0
#define ENABLE_ACTUATOR_MX64_PROTOCOL2  0
#define ENABLE_ACTUATOR_MX106_PROTOCOL2 0
#define ENABLE_ACTUATOR_XL320           1
#define ENABLE_ACTUATOR_XL330           1
#define ENABLE_ACTUATOR_XC330           0
#define ENABLE_ACTUATOR_XL430           0  // includes 2XL430
#define ENABLE_ACTUATOR_XC430           0  // includes 2XC430
#define ENABLE_ACTUATOR_XM430           0
#define ENABLE_ACTUATOR_XH430           0  // includes V lineup
#define ENABLE_ACTUATOR_XD430           0
#define ENABLE_ACTUATOR_XM540           0
#define ENABLE_ACTUATOR_XH540           0  // includes V lineup
#define ENABLE_ACTUATOR_XD540           0
#define ENABLE_ACTUATOR_XW430           0
#define ENABLE_ACTUATOR_XW540           0
#define ENABLE_ACTUATOR_PRO_R           0
#define ENABLE_ACTUATOR_PRO_RA          0
#define ENABLE_ACTUATOR_PRO_PLUS        0
#define ENABLE_ACTUATOR_Y               0

#define DXL_BYTE_STUFF_SAFE_CNT         8
#define DEFAULT_DXL_BUF_LENGTH       1024
#define DXL_MAX_NODE                   16
#define DXL_MAX_NODE_BUFFER_SIZE       16

// 11 = Header(3)+Reserved(1)+ID(1)+Length(2)+Instruction(1)+Error(1)+crc(2)
#define DXL_BUF_LENGTH (DXL_MAX_NODE*DXL_MAX_NODE_BUFFER_SIZE + 11) 

#define PGM_P         const char *
#define PGM_VOID_P    const void *
#define PSTR(s)       (s)
#define _SFR_BYTE(n)  (n)

#define pgm_read_byte(addr)   (*(const unsigned char *)(addr))
#define pgm_read_word(addr) ({ \
  typeof(addr) _addr = (addr); \
  *(const unsigned short *)(_addr); \
})
#define pgm_read_dword(addr) ({ \
  typeof(addr) _addr = (addr); \
  *(const unsigned long *)(_addr); \
})
#define pgm_read_float(addr) ({ \
  typeof(addr) _addr = (addr); \
  *(const float *)(_addr); \
})
#define pgm_read_ptr(addr) ({ \
  typeof(addr) _addr = (addr); \
  *(void * const *)(_addr); \
})

#define pgm_get_far_address(x) ((uint32_t)(&(x)))
#define pgm_read_byte_near(addr)  pgm_read_byte(addr)
#define pgm_read_word_near(addr)  pgm_read_word(addr)
#define pgm_read_dword_near(addr) pgm_read_dword(addr)
#define pgm_read_float_near(addr) pgm_read_float(addr)
#define pgm_read_ptr_near(addr)   pgm_read_ptr(addr)
#define pgm_read_byte_far(addr)   pgm_read_byte(addr)
#define pgm_read_word_far(addr)   pgm_read_word(addr)
#define pgm_read_dword_far(addr)  pgm_read_dword(addr)
#define pgm_read_float_far(addr)  pgm_read_float(addr)
#define pgm_read_ptr_far(addr)    pgm_read_ptr(addr)


typedef void prog_void;
typedef char prog_char;
typedef unsigned char prog_uchar;
typedef char prog_int8_t;
typedef unsigned char prog_uint8_t;
typedef short prog_int16_t;
typedef unsigned short prog_uint16_t;
typedef long prog_int32_t;
typedef unsigned long prog_uint32_t;

#endif /* DYNAMIXEL_CONFIG_H_ */