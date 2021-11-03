//
// Created by 倉澤　一詩 on 2021/10/14.
//

#include "test.h"

void define_wheel() {
    static Test test_wheel(mslh::WheelControl(mslh::Motor(htim1, TIM_CHANNEL_1, GPIOC, GPIO_PIN_0, false),mslh::Encoder(htim3, 500 * 6 * 23 * 4, true), 300, 1),mslh::WheelControl(mslh::Motor(htim1, TIM_CHANNEL_2, GPIOC, GPIO_PIN_3, true),mslh::Encoder(htim4, 500 * 6 * 23 * 4, false), 300, 1));
    test_wheel.measureSpeedCallback();
    wheel_speed = test_wheel.getSpeed();
}