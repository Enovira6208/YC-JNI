#ifndef _JYW6100_H_
#define _JYW6100_H_

#include "../public/public.h"

typedef struct {
    uint8_t head;
    uint8_t Addr[2];
    uint8_t Length[2];
    uint8_t status;
    uint8_t data[1000];
    uint8_t XorCheck;
    uint8_t tail;
} JYW6100MessageType;

typedef struct {
    uint8_t Ur_a[9];
    uint8_t Ur_b[9];
    uint8_t Ur_c[9];
    uint8_t Ur_mean[9];
    uint8_t Um_a[9];
    uint8_t Um_b[9];
    uint8_t Um_c[9];
    uint8_t Um_mean[9];
    uint8_t Ir_a[9];
    uint8_t Ir_b[9];
    uint8_t Ir_c[9];
    uint8_t Ir_mean[9];
    uint8_t P_a[9];
    uint8_t P_b[9];
    uint8_t P_c[9];
    uint8_t P_mean[9];
    uint8_t y_a[9];
    uint8_t y_b[9];
    uint8_t y_c[9];
    uint8_t y_mean[9];
    uint8_t Ur_ab[9];
    uint8_t Ur_bc[9];
    uint8_t Ur_ca[9];
    uint8_t Ur_mean_abc[9];
    uint8_t Um_ab[9];
    uint8_t Um_bc[9];
    uint8_t Um_ca[9];
    uint8_t Um_mean_abc[9];
    uint8_t p_[9];
    uint8_t io[9];
    uint8_t Umean[9];
    uint8_t P[9];
    uint8_t D[9];
    uint8_t y[9];
    uint8_t F[9];
    uint8_t Iorms[9];
    uint8_t Uorms[9];
    uint8_t Uk[9];
    uint8_t Imean[9];
} JYW6100ValueType;

typedef struct {
    double Ur_a;
    double Ur_b;
    double Ur_c;
    double Ur_mean;
    double Um_a;
    double Um_b;
    double Um_c;
    double Um_mean;
    double Ir_a;
    double Ir_b;
    double Ir_c;
    double Ir_mean;
    double P_a;
    double P_b;
    double P_c;
    double P_mean;
    double y_a;
    double y_b;
    double y_c;
    double y_mean;
    double Ur_ab;
    double Ur_bc;
    double Ur_ca;
    double Ur_mean_abc;
    double Um_ab;
    double Um_bc;
    double Um_ca;
    double Um_mean_abc;
    double p_;
    double io;
    double Umean;
    double P;
    double D;
    double y;
    double F;
    double Iorms;
    double Uorms;
    double Uk;
    double Imean;
} JYW6100DataType;

uint16_t JYW6100ReadData(uint8_t *ascllBuff, int cnt);
char *JYW6100RecvMessage(uint8_t *buff, uint16_t size);

#endif