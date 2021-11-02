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
#include "test.h"

#ifdef __cplusplus
extern "C" {
#endif

//    Test machine_test; //このままではコンストラクタも動かないし危険

//    void measureSpeed() {
//        MX_TIM3_Init();
//        MX_TIM4_Init();
//        MX_GPIO_Init();
//        MX_USART2_UART_Init();
//        MX_TIM6_Init();
//        Test wheel;
//
//        HAL_TIM_Base_Start_IT(&htim6);
//        while(1) {
//            printf("%d [mm/s]\r\n",wheel.getSpeed());
//            HAL_Delay(10);
//        }
//    }

    void measureSpeed() {
        MX_TIM3_Init();
        MX_TIM4_Init();
        MX_GPIO_Init();
        MX_USART2_UART_Init();
        MX_TIM6_Init();
        HAL_TIM_Base_Start_IT(&htim6);
        Test test_wheel(mslh::WheelControl(mslh::Motor(htim1, TIM_CHANNEL_1, GPIOC, GPIO_PIN_0, false),
                                                  mslh::Encoder(htim3, 500 * 6 * 23 * 4, true), 300, 1),
                               mslh::WheelControl(mslh::Motor(htim1, TIM_CHANNEL_2, GPIOC, GPIO_PIN_3, true),
                                                  mslh::Encoder(htim4, 500 * 6 * 23 * 4, false), 300, 1));
        test_wheel.start();
        while(1) {
            printf("%d [mm/s]\r\n",test_wheel.getSpeed());
            HAL_Delay(1);
        }
    }

    void encoderTest() {
        MX_GPIO_Init();
        MX_TIM3_Init();
        MX_TIM4_Init();
        MX_USART2_UART_Init();

        mslh::Encoder _encoder_1(htim3, 500*6*23*4, true);
        mslh::Encoder _encoder_2(htim4, 500*6*23*4, false);
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

        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
        HAL_Delay(5000);


        MX_GPIO_Init();
        MX_TIM1_Init();
        mslh::Motor _motor_1(htim1, TIM_CHANNEL_1, GPIOC, GPIO_PIN_0, false);
        mslh::Motor _motor_2(htim1, TIM_CHANNEL_2, GPIOC, GPIO_PIN_3, true);

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
            speed *= -2.0;
        }
    }

//// ここ(グローバルスコープ内)でインスタンスを生成するとコンストラクタが呼ばれないので注意。



#ifdef __cplusplus
}
#endif


#endif // TSUKUBAROBOT_APPLICATION_H