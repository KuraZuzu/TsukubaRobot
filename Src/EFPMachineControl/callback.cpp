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

namespace wheel{
    Test test_wheel(mslh::WheelControl(mslh::Motor(htim1, TIM_CHANNEL_1, GPIOC, GPIO_PIN_0, false),mslh::Encoder(htim3, 500 * 6 * 23 * 4, true), 300, 1),mslh::WheelControl(mslh::Motor(htim1, TIM_CHANNEL_2, GPIOC, GPIO_PIN_3, true),mslh::Encoder(htim4, 500 * 6 * 23 * 4, false), 300, 1));
}

/**
 *
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {

    /**
     * @note
     *     90 M[Hz]（APB1）/ 9000 (Prescaler) = 10000 [Hz]（TIM7）
     *     10000 [Hz] / 10（Period）= 1000 [Hz]
     *     1000 [Hz] = 1 m[sec]
     */
    if(htim == &htim6) {
        wheel::test_wheel.measureSpeedCallback();
    }
}
