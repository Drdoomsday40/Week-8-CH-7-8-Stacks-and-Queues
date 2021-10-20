// FILE: things.cxx
// CLASSES implemented: BooleanSource, Averager, Washer
//
// INVARIANT for the BooleanSource ADT:
//   1. The member variable probability is the appoximate probability that
//      query( ) returns true.
// INVARIANT for the Averager ADT:
//   1. The member variable count indicates how many numbers the Averager has
//      been given.
//   2. The member variable sum is the sum of all the numbers that the
//      Averager has been given.
// INVARIANT for the Washer class:
//   1. The member variable seconds_for_wash is the number of seconds required
//      for one wash.
//   2. The member varible wash_time_left is 0 if the washer is not busy;
//      otherwise it is the number of seconds until the washer is free.
//
// INVARIANT for the TrafficLight class:
//   1. The member variable now_red is true if the light is now red, and it
//      is false if the light is now green.
//   2. The member variable red_span indicates how many seconds a red light
//      lasts.
//   3. The member variable green_span indicates how many seconds a green
//      light lasts.
//   4. The member variable seconds_until_change tells how many more seconds
//      until the next change (from red to green, or vice versa) and this
//      value is always positive.

#include <assert.h>   // Provides assert
#include <stdlib.h>   // Provides rand, RAND_MAX, size_t
#include "things.h"

BooleanSource::BooleanSource(double p)
// Library facilities used: assert.h
{
    assert(p >= 0);
    assert(p <= 1);
    probability = p;
}

bool BooleanSource::query( ) const
// Library facilities used: stdlib.h
{
    return (rand( ) < probability*RAND_MAX);
}

Averager::Averager( )
{
    count = 0;
    sum = 0;
}

void Averager::next_number(double value)
{
    count++;
    sum += value;
}

double Averager::average( ) const
// Library facilities used: assert.h
{
    assert(how_many_numbers( ) > 0);
    return sum/count;
}

Washer::Washer(unsigned int s)
{
    seconds_for_wash = s;
    wash_time_left = 0;
}

void Washer::one_second( )
{
    if (is_busy( ))
        wash_time_left--;
}

void Washer::start_washing( )
//Library facilities used: assert.h
{
    assert(!is_busy( ));
    wash_time_left = seconds_for_wash;
}

TrafficLight::TrafficLight(unsigned int r, unsigned int g)
//Library facilities used: assert.h
{
    assert(r > 0);
    assert(g > 0);
    
    red_span = r;
    green_span = g;
    now_red = true;
    seconds_until_change = r;
}

void TrafficLight::simulate_time(unsigned int t)
{
    while (t >= seconds_until_change)
    {
	t -= seconds_until_change;
	now_red = !now_red;
	seconds_until_change = now_red ? red_span : green_span;
    }
    seconds_until_change -= t;
}

