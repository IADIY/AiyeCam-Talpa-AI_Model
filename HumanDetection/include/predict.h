#ifndef PREDICT_H
#define PREDICT_H

#include "stdint.h"

/**
 * @brief RC滤波器结构体
 * 
 * @author karl (karl.zhang@neuronBasic.com)
 * @date 2023-07-05
 * @version 1.0
 * 
 * 
 */
struct RCLowPassFilter {
    uint32_t mask;      //< 辅助变量,用于提取小数部分
    int32_t last;       //< 上一次的滤波结果
    uint32_t level;     //< 滤波等级
    uint32_t remainder;     //< 小数部分
    int32_t data;       //< 滤波结果
};
/**
 * @brief 记录拟合的多项式的系数
 * 
 * @author karl (karl.zhang@neuronBasic.com)
 * @date 2023-08-14
 * @version 1.0
 * 
 * 
 */
struct LeastSqaureFactor3 {
    int64_t m;      //< 系数矩阵行列式
    int64_t a[4];   //< 多项式系数(放大了LeastSqaureFactor3.m倍)
};
/**
 * @brief 提供多项式拟合用的上下文
 * 
 * @author karl (karl.zhang@neuronBasic.com)
 * @date 2023-08-14
 * @version 1.0
 * 
 * 
 */
struct Predictor {
    uint8_t filterLevel;    //< 滤波等级
    uint8_t predictLevel;   //< 预测程度,1 - 一次, 2 - 二次. 3 - 三次, 其他 - 一次
    struct LeastSqaureFactor3 result;   //< 记录拟合的结果
    struct RCLowPassFilter s_filter;    //滤波器
};

void predict(int16_t *x, int16_t *y, uint32_t len, struct Predictor *predictor);

#endif