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

    // callback関数で呼ばないと動作しない
    inline void measureSpeedCallback() {
        _left_wheel.measureSpeed();
        _right_wheel.measureSpeed();
        _speed = ( _left_wheel.getSpeed() + _right_wheel.getSpeed() ) / 2;
    }

    void start() {
        _left_wheel.start();
        _right_wheel.start();
    }

    void run(int32_t speed_mm_s, int32_t distance_mm) {
        _left_wheel.run(speed_mm_s, distance_mm);
        _right_wheel.run(speed_mm_s, distance_mm);
    }

private:
    mslh::WheelControl _left_wheel;
    mslh::WheelControl _right_wheel;
    int32_t _speed; // [mm]/[s]
};

#endif //TSUKUBAROBOT_TEST_H
