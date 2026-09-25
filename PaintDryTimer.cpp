
#include <ctime> // for time(0)
#include <iostream> // for cin and cout
#include <cmath> // for M_PI and others
#include <vector> // for vectors (duh)
#include <cstdlib> // for random
#include <cassert> // for assert in the tests() function
#include "TimeCode.h" // for timecode's (duh)

using namespace std;


struct DryingSnapShot {
	// This is a struct, it's like an object
	// that doesn't have any methods.
	// You can read more about them in the ZyBook
	// just search for "struct"
	string name;
	time_t startTime;
	TimeCode *timeToDry;
};


long long int get_time_remaining(DryingSnapShot dss){
	time_t now = time(0);

    long long int elapsed = now - dss.startTime;

    long long int total = dss.timeToDry->GetTimeCodeAsSeconds();
	// timeToDry is a pointer to a TimeCode.
	// That's why -> is used instead of .

    return total - elapsed;
}


string drying_snap_shot_to_string(DryingSnapShot dss){
	long long int remaining = get_time_remaining(dss);

    string result = dss.name + " (takes " + dss.timeToDry->ToString() + " to dry) ";

    if (remaining <= 0) {
        result += "DONE!";
    } 
	else {
        TimeCode remainingTC(0, 0, remaining);
        result += "time remaining: " + remainingTC.ToString();
    }

    return result;
}


double get_sphere_sa(double rad){
	return 4 * M_PI * rad * rad;
}


TimeCode *compute_time_code(double surfaceArea){
	long long unsigned int seconds = static_cast<long long unsigned int>(surfaceArea);
	// Gets rid of any decimal part instead of rounding.
	// Same approach was used in operators in TimeCode.
	return new TimeCode(0, 0, seconds);
	// new always gives back a pointer to the object it just created.
	// That's why compute_time_code's return type is TimeCode * (a pointer), not TimeCode
}


void tests(){
	// get_time_remaining
	DryingSnapShot dss;
	dss.startTime = time(0);
	TimeCode tc = TimeCode(0, 0, 7);
	dss.timeToDry = &tc;
	long long int ans = get_time_remaining(dss);
	assert(ans > 6 && ans < 8);

	// add more tests here
	DryingSnapShot dss2;
    dss2.startTime = time(0) - 3;
    TimeCode tc2b = TimeCode(0, 0, 10);
    dss2.timeToDry = &tc2b;
    long long int ans2 = get_time_remaining(dss2);
    assert(ans2 > 6 && ans2 < 8);

	DryingSnapShot dss3;
    dss3.startTime = time(0) - 100;
    TimeCode tc3 = TimeCode(0, 0, 5);
    dss3.timeToDry = &tc3;
    assert(get_time_remaining(dss3) < 0);


	// get_sphere_sa
	double sa = get_sphere_sa(2.0);
	assert (50.2654 < sa && sa < 50.2655);

	// add more tests here
	double sa2 = get_sphere_sa(1.0);
    assert(12.566 < sa2 && sa2 < 12.567);

	double sa3 = get_sphere_sa(0.0);
    assert(sa3 == 0.0);


	// compute_time_code
	TimeCode *tc2 = compute_time_code(1.0);
	//cout << "tc: " << tc.GetTimeCodeAsSeconds() << endl;
	assert(tc2->GetTimeCodeAsSeconds() == 1);
	delete tc2;

	// add more tests here
	TimeCode *tc4 = compute_time_code(50.9);
    assert(tc4->GetTimeCodeAsSeconds() == 50);
    delete tc4;

	TimeCode *tc5 = compute_time_code(0.0);
    assert(tc5->GetTimeCodeAsSeconds() == 0);
    delete tc5;

	//drying_snap_shot_to_string
	DryingSnapShot dss4;
    dss4.name = "drying_snap_shot_to_string-test";
    dss4.startTime = time(0);
    TimeCode tc6 = TimeCode(0, 0, 50);
    dss4.timeToDry = &tc6;
    string result = drying_snap_shot_to_string(dss4);
    assert(result == "drying_snap_shot_to_string-test (takes 0:0:50 to dry) time remaining: 0:0:50");

	DryingSnapShot dss5;
    dss5.name = "drying_snap_shot_to_string-test2";
    dss5.startTime = time(0) - 100;
    TimeCode tc7 = TimeCode(0, 0, 5);
    dss5.timeToDry = &tc7;
    string resultDone = drying_snap_shot_to_string(dss5);
    assert(resultDone == "drying_snap_shot_to_string-test2 (takes 0:0:5 to dry) DONE!");

	cout << "ALL TESTS PASSED!" << endl;

}


int main(){
	tests();

	vector<DryingSnapShot> tracker;
	char choice;

	while (true) {
		cout << "Choose an option: (A)dd, (V)iew Current Items, (Q)uit: ";
		cin >> choice;

		if (choice == 'a' || choice == 'A') {
			cout << "radius: ";
			double radius;
			cin >> radius;

			double sa = get_sphere_sa(radius);
			TimeCode *tc = compute_time_code(sa);
			// compute_time_code returns pointer

			DryingSnapShot dss;
			dss.name = "Batch-" + to_string(rand());
			dss.startTime = time(0);
			dss.timeToDry = tc;

			tracker.push_back(dss);

			cout << drying_snap_shot_to_string(dss) << endl;
		}

		else if (choice == 'v' || choice == 'V') {

			for (vector<DryingSnapShot>::iterator it = tracker.begin(); it != tracker.end();) {
				cout << drying_snap_shot_to_string(*it) << endl;

				long long int remaining = get_time_remaining(*it);

				if (remaining <= 0) {
					delete it->timeToDry; 
					it = tracker.erase(it);
				} 
				else {
					++it;
				}
			}
			cout << tracker.size() << " batches being tracked." << endl;
		}

		else if (choice == 'q' || choice == 'Q') {
			break;
		}
	}

	for (DryingSnapShot& dss : tracker) {
		delete dss.timeToDry;
	}
	// the while loop ends when user chooses 'q', for any batches still active this is needed to guarantee every TimeCode* created by new gets freed

	return 0;
}

// I read the notes in the assignment instructions :)