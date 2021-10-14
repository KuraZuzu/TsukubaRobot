/*!
 * @file application.h v1.0
 * @Copyright © 2021 Kazushi Kurasawa
 * @date 2021.10.14
 *
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 */

#ifndef TSUKUBAROBOT_TEST_H
#define TSUKUBAROBOT_TEST_H

#include "../MSLH/wheel_control.h"

// モーターの直径
class Test {
public:
    Test()
    : _left_wheel(mslh::Motor(htim1, TIM_CHANNEL_1, GPIOC, GPIO_PIN_0, false), mslh::Encoder(htim3, 500*6*23, true), 3000, 1)
    , _right_wheel(mslh::Motor(htim1, TIM_CHANNEL_2, GPIOC, GPIO_PIN_3, true), mslh::Encoder(htim4, 500*6*23, false), 3000, 1)
    , _speed(0) {
    }

    inline int32_t getSpeed() const {
        return _speed;
    }

    // callback関数で呼ばないと動作しない
    inline void measureSpeedCallback() {
        _left_wheel.measureSpeed();
        _right_wheel.measureSpeed();
        _speed = ( _left_wheel.getSpeed() + _right_wheel.getSpeed() ) / 2;
    }

private:
    mslh::WheelControl _left_wheel;
    mslh::WheelControl _right_wheel;
    int32_t _speed; // [mm]/[s]
};


#endif //TSUKUBAROBOT_TEST_H
