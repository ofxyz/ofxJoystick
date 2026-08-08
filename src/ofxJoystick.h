
#pragma once
#include "ofMain.h"

#include <set>
#include <string>
#include <vector>

#include "GLFW/glfw3.h"
struct axis_state {
    short x, y;
};

class ofxJoystick {
private:
  bool isConnect_;
#ifdef __linux__
    int js_{-1};


    struct axis_state axes[8] = {0};
    unsigned char button[256] = {0};

#endif // __linux__
  int    id_;
  std::string name_;

  int buttonNum_;
  int axisNum_;

  std::set<int> pressed_;
  std::set<int> pushing_;
  std::set<int> release_;

  std::vector<float> axis_;

  void updateState();
  void updateAxis();
  void updateButton();

  void update(ofEventArgs &args);

public:
  ofxJoystick() = default;
  ~ofxJoystick();

  // JoyId : usually give GLFW_SOYSTICK_1
  // when you connect only one Gamepad
  void setup(int JoyId);

  // if connected return true
  // disconnected return false
  bool isConnect() const;

  int getId() const;

  // return your Gamepad name
  const std::string& getName() const;

  // return number of Button and Axis
  int getButtonNum() const;
  int getAxisNum() const;

  // return axis, if disconnected return 0
  float getAxis(int num) const;

  // button func
  bool isPressed(int button) const;
  bool isPushing(int button) const;
  bool isRelease(int button) const;

  bool anyButton() const;
};
