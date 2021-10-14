/*!
 * @file application.h v1.0
 * @Copyright © 2021 Kazushi Kurasawa
 * @date 2021.07.19
 *
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 */

#ifndef TSUKUBAROBOT_APPLICATION_H
#define TSUKUBAROBOT_APPLICATION_H

#include "../MSLH/motor.h"
#include "../MSLH/encoder.h"
#include "Test.h"

#ifdef __cplusplus
extern "C" {
#endif

    Test machine_test;

    void encoderTest() {
        MX_GPIO_Init();
        MX_TIM3_Init();
        MX_TIM4_Init();
        MX_USART2_UART_Init();

        mslh::Encoder _encoder_1(htim3, 500*6*23, true);
        mslh::Encoder _encoder_2(htim4, 500*6*23, false);
        _encoder_1.start();
        _encoder_2.start();
        _encoder_1.reset();
        _encoder_2.reset();
        while (1) {
            _encoder_1.update();
            _encoder_2.update();
//            printf("1: [回転数]%d   [パルス]%lld , 2: [回転数]%d  [パルス]%lld\r\n",_encoder_1.getRotationCount(), _encoder_1.getTotalPulse(), _encoder_2.getRotationCount(),  _encoder_2.getTotalPulse());
            printf("LT:%d  LC:%d  LD:%d    RT:%d  RC:%d  RD:%d\r\n"
                    , static_cast<int>(_encoder_1.getTotalPulse())
                    , static_cast<int>(_encoder_1.getRotationCount())
                    , static_cast<int>(_encoder_1.getDeltaPulse())
                    , static_cast<int>(_encoder_2.getTotalPulse())
                    , static_cast<int>(_encoder_2.getRotationCount())
                    , static_cast<int>(_encoder_2.getDeltaPulse()) );
            HAL_Delay(10);
        }

    }

    void motorTest() {
        MX_GPIO_Init();
        MX_TIM1_Init();
        mslh::Motor _motor_1(htim1, TIM_CHANNEL_1, GPIOC, GPIO_PIN_0, false);
        mslh::Motor _motor_2(htim1, TIM_CHANNEL_2, GPIOC, GPIO_PIN_3, true);

        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
        _motor_1.start();
        _motor_2.start();
        _motor_1.update(0.0);
        _motor_2.update(0.0);
        HAL_Delay(5000);
        double speed = 0.2;
        while(1) {
            _motor_1.update(speed);
            _motor_2.update(speed);
            HAL_Delay(3000);
            _motor_1.update(0.0);
            _motor_2.update(0.0);
            HAL_Delay(500);
            speed *= -2;
        }
    }

//// ここ(グローバルスコープ内)でインスタンスを生成するとコンストラクタが呼ばれないので注意。



#ifdef __cplusplus
}
#endif


#endif // TSUKUBAROBOT_APPLICATION_H