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
#include "stm32f4xx_it.h"

#ifdef __cplusplus
extern "C" {
#endif

    void motor_test() {
        MX_GPIO_Init();
        MX_TIM1_Init();
        mslh::Motor _l_motor(htim1, TIM_CHANNEL_1, GPIOA, GPIO_PIN_6, true);

        _l_motor.start();
        _l_motor.update(0.0);
        HAL_Delay(5000);
        double speed = 0.2;
        while(1) {
            _l_motor.update(speed);
            HAL_Delay(3000);
            _l_motor.update(0.0);
            HAL_Delay(500);
            speed *= -2;
        }
    }

//// ここ(グローバルスコープ内)でインスタンスを生成するとコンストラクタが呼ばれないので注意。
//void test_myself_wait_led() {
//    MX_GPIO_Init();
//    MX_TIM6_Init();
//    while (1) {
////        printf("%d\r\n", my_timer::time_us_count);
//        my_timer::wait_us(1000000);
////        HAL_Delay(1000);
//        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_3);
//    }
//}




#ifdef __cplusplus
}
#endif


#endif // TSUKUBAROBOT_APPLICATION_H