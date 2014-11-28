
#ifndef CIRCLECOLORMODE_H
#define CIRCLECOLORMODE_H

#include <mode.h>
#include <algorithm>

class CircleColorMode : public Mode
{
public:
   CircleColorMode(std::vector<color::rgba> colors, size_t num_leds, int priority = 0, double freq = 5, int pulses = 0, double timeout = 0)
    :Mode(priority, freq, pulses, timeout), _toggle(false), _timer_inc(0), _num_leds(num_leds)
  {
    _colors = colors;
    _colors.resize(num_leds);
    if(_pulses != 0)
    {
      _pulses *=2;
      _pulses +=1;
    }
    _inc = (1. / UPDATE_RATE_HZ) * _freq;
  }

  void execute()
  {
    if(_timer_inc >= 1.0)
    {
      std::rotate(_colors.begin(), _colors.begin()+1, _colors.end());
      _pulsed++;
      m_sigColorsReady(_colors);
      _timer_inc = 0.0;
    }
    else
      _timer_inc += _inc;
  }

  std::string getName(){ return std::string("FlashMode"); }

private:
  bool _toggle;
  double _timer_inc;
  double _inc;
  size_t _num_leds;
};

#endif
