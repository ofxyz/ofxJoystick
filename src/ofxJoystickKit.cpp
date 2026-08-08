#include "ofxJoystickKit.h"

#include "ofxJoystick.h"
#include "component_editor_registration.h"
#include "components/input_components.h"
#include "systems/input_system.h"

#include <algorithm>
#include <unordered_map>

namespace ofxjoystick {
namespace {

struct DeviceSlot {
	ofxJoystick joy;
	bool        ready = false;
};

DeviceSlot& slotFor(int joyId) {
	static std::unordered_map<int, DeviceSlot> slots;
	return slots[joyId];
}

void pollFromDevice(ecs::joystick_input_component& joy, const ofxJoystick& dev) {
	joy.connected   = dev.isConnect();
	joy.name        = dev.getName();
	joy.buttonCount = std::min(dev.getButtonNum(), ecs::joystick_input_component::kMaxButtons);
	joy.axisCount   = std::min(dev.getAxisNum(), ecs::joystick_input_component::kMaxAxes);

	for (int i = 0; i < joy.axisCount; ++i) {
		joy.axes[i] = dev.getAxis(i);
	}

	for (int i = 0; i < joy.buttonCount; ++i) {
		joy.buttonPressed[i]  = dev.isPressed(i);
		joy.buttonPushing[i]  = dev.isPushing(i);
		joy.buttonReleased[i] = dev.isRelease(i);
		joy.buttonDown[i]     = joy.buttonPushing[i];
	}
}

} // namespace

void poll(ecs::joystick_input_component& joy) {
	auto& slot = slotFor(joy.joyId);
	if (!slot.ready) {
		slot.joy.setup(joy.joyId);
		slot.ready = true;
	}
	pollFromDevice(joy, slot.joy);
}

void attachInputHook() {
	ecs::InputSystem::setJoystickPollHook([](ecs::joystick_input_component& joy) {
		ofxjoystick::poll(joy);
	});
}

void registerComponentMenu() {
	static bool registered = false;
	if (registered) return;
	registered = true;

	ecs::registerComponent<ecs::joystick_input_component>(
		"Joystick Input", "Input");
}

namespace {
const struct RegisterJoystickMenu {
	RegisterJoystickMenu() { registerComponentMenu(); }
} kRegisterJoystickMenu;
} // namespace

void attach() {
	attachInputHook();
}

} // namespace ofxjoystick
