/*!
* @file callback.cpp v1.0
* @Copyright © 2021 Kazushi Kurasawa
* @date 2021.10.15
*
* Released under the MIT license.
* see https://opensource.org/licenses/MIT
*/

#include "../MSLH/defines.h"
#include "stm32f4xx.h"
#include "test.h"
#include "main.h"

extern Test machine_test;

// タイマーコールバック
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {

    /**
     * @note
     *     90 M[Hz]（APB1）/ 9000 (Prescaler) = 10000 [Hz]（TIM7）
     *     10000 [Hz] / 10（Period）= 1000 [Hz]
     *     1000 [Hz] = 1 m[sec]
     */
    if(htim == &htim6) {
//        Test::measureSpeedCallback();
        machine_test.measureSpeedCallback();
    }
}