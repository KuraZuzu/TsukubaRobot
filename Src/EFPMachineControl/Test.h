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

//static int32_t wheel_speed;
//void define_wheel();

/**
 * @brief
 *   Declare this class as static in the global scope.
 *   You can then call Test::measureSpeedCallback() in the callback function to measure the speed.
 *
 * Example:
 * @code

 * @endcode
 */
class Test {
public:

    Test(mslh::WheelControl left_wheel, mslh::WheelControl right_wheel)
    : _left_wheel(left_wheel)
    , _right_wheel(right_wheel)
    , _speed(0) {
    }


    inline int32_t getSpeed() const {
        return _speed;
    }

    // !!!!!!!!! なぜかそもそもソースコードが呼ばれない !!!!!!
    // callback関数で呼ばないと動作しない
    inline void measureSpeedCallback() {
        _left_wheel.measureSpeed();
        _right_wheel.measureSpeed();
        _speed = ( _left_wheel.getSpeed() + _right_wheel.getSpeed() ) / 2;
//        HAL_GPIO_TogglePin(GPIOA, LD2_Pin);
    }

    void start() {
        _left_wheel.start();
        _right_wheel.start();
    }

private:
    mslh::WheelControl _left_wheel;
    mslh::WheelControl _right_wheel;
    int32_t _speed; // [mm]/[s]
};

//void define_wheel() {
//    static Test test_wheel(mslh::WheelControl(mslh::Motor(htim1, TIM_CHANNEL_1, GPIOC, GPIO_PIN_0, false),
//                                              mslh::Encoder(htim3, 500 * 6 * 23 * 4, true), 300, 1),
//                           mslh::WheelControl(mslh::Motor(htim1, TIM_CHANNEL_2, GPIOC, GPIO_PIN_3, true),
//                                              mslh::Encoder(htim4, 500 * 6 * 23 * 4, false), 300, 1));
//    test_wheel.measureSpeedCallback();
//    wheel_speed = test_wheel.getSpeed();
//}

//static Test test_wheel(mslh::WheelControl(mslh::Motor(htim1, TIM_CHANNEL_1, GPIOC, GPIO_PIN_0, false),
//                                          mslh::Encoder(htim3, 500 * 6 * 23 * 4, true), 300, 1),
//                       mslh::WheelControl(mslh::Motor(htim1, TIM_CHANNEL_2, GPIOC, GPIO_PIN_3, true),
//                                          mslh::Encoder(htim4, 500 * 6 * 23 * 4, false), 300, 1));

#endif //TSUKUBAROBOT_TEST_H
