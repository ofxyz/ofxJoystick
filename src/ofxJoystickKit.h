#pragma once

#include "ofMain.h"

namespace ecs {
struct joystick_input_component;
}

namespace ofxjoystick {

/// Poll one ecs::joystick_input_component from ofxJoystick devices.
void poll(ecs::joystick_input_component& joy);

/// Register picker row + default poll hook with ofxEnTTKit.
void attach();

/// Register the default ofxJoystick poll implementation with ecs::InputSystem.
void attachInputHook();

/// Add "Joystick Input" to the kit component picker (via ecs::registerComponent).
void registerComponentMenu();

} // namespace ofxjoystick
