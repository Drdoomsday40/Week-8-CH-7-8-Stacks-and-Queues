// FILE: things.h
// CLASSES PROVIDED: BooleanSource, Averager, Washer, TrafficLight.
//
// CONSTRUCTOR for the BooleanSource class:
//   BooleanSource(double p = 0.5)
//     Precondition: 0 <= p <= 1.
//     Postcondition: The BooleanSource has been initialized so that p is the
//     approximate probability of returning true in any subsequent activation
//     of query( ).
//
// CONSTANT MEMBER FUNCTION for the BooleanSource class:
//   bool query( ) const
//     Postcondition: The return value is either true or false, with the
//     probability of a true value being approximately p (from the constructor).
//
// CONSTRUCTOR for the Averager class:
//   Averager( )
//     Postcondition: The Averager has been initialized so that it
//     is ready to accept a sequence of numbers to average.
//
// MODIFICATION MEMBER FUNCTION for the Averager class:
//   void next_number(double value)
//     Postcondition: The Averager has accepted value as the next
//     number in the sequence of numbers which it is averaging.
//
// CONSTANT MEMBER FUNCTIONS for the Averager class:
//   size_t how_many_numbers( ) const
//     Postcondition: The value returned is a count of how many
//     times next_number has been activated.
//
//   double average( ) const
//     Precondition: how_many_numbers > 0.
//     Postcondition: The value returned is the average of all the
//     numbers which have been given to the Averager.
//
// CONSTRUCTOR for the Washer class:
//   Washer(unsigned int s = 60)
//     Precondition: The value of s is the number of seconds needed for
//     the completion of one wash cycle.
//     Postcondition: The Washer has been initialized so that all
//     other member functions may be used.
//
// MODIFICATION MEMBER FUNCTIONS for the Washer class:
//   void one_second( )
//     Postcondition: The washer has recorded (and simulated) the
//     passage of one more second of time.
//
//   void start_washing( )
//     Precondition: The washer is not busy.
//     Postcondition: The washer has started simulating one wash
//     cycle. Therefore, is_busy( ) will return true until
//     the required number of simulated seconds have occured.
//
// CONSTANT MEMBER FUNCTIONS for the Washer class:
//   bool is_busy( ) const
//     Postcondition: Return value is true if the washer is busy
//     (in a wash cycle); otherwise the return value is false.
//
// CONSTRUCTOR for the TrafficLight class:
//   TrafficLight(unsigned int r = 30, unsigned int g = 30)
//     Precondition: The value of r is the number of seconds that a red light
//     lasts; the value of g is the number of seconds that a green light lasts.
//     Both r and g are positive.
//     Postcondition: The traffic light has been initialized. It starts
//     red at the time of zero seconds. Then it switches to green for g secs,
//     back to red for r seconds, back to green for g seconds and so on.
//
// MODIFICATION MEMBER FUNCTIONS for the TrafficLight class:
//   void simulate_time(unsigned int t)
//     Postcondition: The traffic light has recorded (and simulated) the
//     passage of t more second of time.
//
// CONSTANT MEMBER FUNCTIONS for the TrafficLight class:
//   bool is_green( ) const
//     Postcondition: Return value is true if the traffic light is green;
//     otherwise the return value is false.
//
//   bool is_red( ) const
//     Postcondition: Return value is true if the traffic light is red;
//     otherwise the return value is false.
//
// VALUE SEMANTICS for the classes:
//   Assignments and the copy constructor may be used with all the classes.
//

#ifndef THINGS_H
#define THINGS_H

#include <stdlib.h> // Provides size_t

    class BooleanSource
    {
    public:
        // CONSTRUCTOR
        BooleanSource(double p = 0.5);
        // CONSTANT function
        bool query( ) const;
    private:
        double probability; // Probability of query( ) returning true
    };

    class Averager
    {
    public:
        // CONSTRUCTOR
        Averager( );
        // MODIFICATION function
        void next_number(double value);
        // CONSTANT functions
        size_t how_many_numbers( ) const { return count; }
        double average( ) const;
    private:
        size_t count; // How many numbers have been given to the Averager
        double sum;   // Sum of all the numbers given to the Averager
    };

    class Washer
    {
    public:
        // CONSTRUCTOR
        Washer(unsigned int s = 60);
        // MODIFICATION functions
        void one_second( );
        void start_washing( );
        // CONSTANT function
        bool is_busy( ) const { return (wash_time_left > 0); }
    private:
        unsigned int seconds_for_wash; // Seconds for a single wash
        unsigned int wash_time_left;   // Seconds until washer no longer busy
    };

    class TrafficLight
    {
    public:
	// CONSTRUCTOR
	TrafficLight(unsigned int r = 30, unsigned int g = 30);
	// MODIFICATION functions
	void simulate_time(unsigned int t = 1);
	// CONSTANT functions
	bool is_green( ) const { return !now_red; }
	bool is_red( ) const   { return now_red;  }
    private:
	unsigned int red_span;
	unsigned int green_span;
	bool now_red;
	unsigned int seconds_until_change;
    };

#endif


