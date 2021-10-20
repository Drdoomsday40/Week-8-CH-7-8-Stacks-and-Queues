// #include "stdafx.h"
// FILE: traffic.cxx
// Written by: --------(Put your name and email address here)--------
// A simple program to simulate two synchronized traffic lights. The
// program prints a table indicating the average wait-time for cars coming
// through the two lights.

#include <iomanip>   // Provides setw
#include <iostream>  // Provides cout
#include "things.h"    // Provides the Averager, BooleanSource & TrafficLight
#include "queue2.h"    // The queue template class (with a peek function)

using namespace std;
using namespace main_savitch_8C;
// This is a function to simulate traffic flowing through two synchronized
// traffic lights.
// Parameters and return value:
// Offset:
//   This is the number of seconds between the time that the
//   first light changes to green and the time that the second light changes to
//   green. For example, if offset is zero, then the two lights change to green
//   at the same time. If offset is 10 then the first light changes to green
//   10 seconds ahead of the second.
// Span:
//   This is the length of time that each light stays red or green. For
//   example, if span is 30, then each light stays red for 30 seconds then
//   switches to green for 30 seconds, and so on.
// Arrival_prob:
//   This is the probability during any given second that a car arrives at
//   the first traffic light. For example, if arrival_prob is 0.25, then there
//   is a 25% chance that a car arrives at the first light during any given
//   second and a 75% chance that no car arrives. (There will never be more
//   than one car arriving during a single second.)
// Travel_time:
//   This is the number of seconds that it takes a car to travel from the
//   first traffic light to the second.
// Total_time:
//   This is the total number of seconds that the function will simulate
//   at the traffic lights. (At the start of this simulation, there are no
//   cars waiting at either light).
// Computation and Return value:
//   The function simulates cars arriving at the first stop light, waiting
//   for a green light, moving to the second stoplight, waiting again, and
//   moving through the second light. During a green light, at most one car
//   can move through the the light per second. As the computation proceeds,
//   the function uses an Averager to keep track of the average waiting time
//   for cars that arrived and pass through the first light. A second
//   Averager keeps track of the average waiting time for cars that arrived
//   and passed through the second light. The function's return value is the
//   sum of these two averages.
// Special Case:
//   If no cars make it through the second light, then the return value is -1.
double traffic(
	unsigned int offset,
	unsigned int span,
	double arrival_prob,
	unsigned int travel_time,
	unsigned int total_time
);

int main()
{
	const double ARRIVAL_PROB = 0.1;      // Prob. of car arrival in a second.
	const unsigned int TRAVEL_TIME = 40;  // Seconds to travel between lights.
	const unsigned int TOTAL_TIME = 6000; // Total seconds in the simulation.
	const unsigned int SPAN = 30;         // How long is a light red or green?

	unsigned int offset;

	for (offset = 0; offset < 2 * SPAN; offset++)
	{
		cout << "Offset of " << setw(2) << offset << " seconds ";
		cout << "results in average wait of ";
		cout << traffic(offset, SPAN, ARRIVAL_PROB, TRAVEL_TIME, TOTAL_TIME);
		cout << " seconds." << endl;
	}
	system("pause");
	return EXIT_SUCCESS;
}

double traffic(
	unsigned int offset,
	unsigned int span,
	double arrival_prob,
	unsigned int travel_time,
	unsigned int total_time
)
{
	queue<unsigned int> q1, q2;
	BooleanSource arrival(arrival_prob);
	TrafficLight light1(span, span);
	TrafficLight light2(span, span);
	unsigned int current_second;
	unsigned int wait;
	Averager waiting1, waiting2;

	light1.simulate_time(offset);
	for (current_second = 1; current_second <= total_time; current_second++)
	{
		// A new car might be added to the first queue.
		if (arrival.query())
			q1.push(current_second);

		// Let one car through the first light (if it's green)
		if (light1.is_green() && !q1.empty())
		{
			wait = current_second - q1.front();
			q1.pop();
			waiting1.next_number(wait);
			q2.push(current_second + travel_time);
		}

		// Let one car through the second light (if it's green)
		if (light2.is_green() && !q2.empty() && q2.front() <= current_second)
		{
			wait = current_second - q2.front();
			q2.pop();
			waiting2.next_number(wait);
		}

		// Simulate the passage of one second of time for the lights.
		light1.simulate_time();
		light2.simulate_time();
	}

	if (waiting2.how_many_numbers() == 0)
		return -1;
	else
		return waiting1.average() + waiting2.average();
}
