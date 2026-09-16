#include <iostream>
#include <assert.h>

using namespace std;

#include "TimeCode.h"


void TestComponentsToSeconds(){
    cout << "Testing ComponentsToSeconds" << endl;
    
    // Random but "safe" inputs
    long long unsigned int t = TimeCode::ComponentsToSeconds(3, 17, 42);
    assert(t == 11862);

    // More tests go here!
    assert(TimeCode::ComponentsToSeconds(0, 0, 0) == 0);
    assert(TimeCode::ComponentsToSeconds(0, 59, 59) == 3599);
    assert(TimeCode::ComponentsToSeconds(0, 81, 0) == 4860);
    assert(TimeCode::ComponentsToSeconds(0, 0, 5606) == 5606);
    assert(TimeCode::ComponentsToSeconds(2, 71, 234719572143) == 234719583603);
    assert(TimeCode::ComponentsToSeconds(1000, 0, 0) == 3600000);

    cout << "PASSED!" << endl << endl;
}


void TestDefaultConstructor(){
    cout << "Testing Default Constructor" << endl;
    TimeCode tc;

    //cout << "Testing ToString()" << endl;
    //cout << "tc: " << tc.ToString() << endl;
    assert(tc.ToString() == "0:0:0");
    assert(tc.GetTimeCodeAsSeconds() == 0);

    cout << "PASSED!" << endl << endl;
}


void TestComponentConstructor(){
    cout << "Testing Component Constructor" << endl;
    TimeCode tc = TimeCode(0, 0, 0);
    //cout << "Testing ToString()" << endl;
    //cout << "tc: " << tc.ToString() << endl;
    assert(tc.ToString() == "0:0:0");

    // more tests go here!
    TimeCode tc2 = TimeCode(4, 15, 32);
    assert(tc2.ToString() == "4:15:32");
    assert(tc2.GetTimeCodeAsSeconds() == 15332);

    TimeCode tc2b = TimeCode(0, 0, 15332);
    assert(tc2b.ToString() == "4:15:32");

    // Roll-over inputs
    TimeCode tc3 = TimeCode(3, 71, 3801);
    //cout << "tc3: " << tc3.ToString() << endl;
    assert(tc3.ToString() == "5:14:21");

    // More tests go here!
    TimeCode tc4 = TimeCode(0, 61, 0);
    assert(tc4.ToString() == "1:1:0");

    TimeCode tc5 = TimeCode(187, 53, 27);
    assert(tc5.ToString() == "187:53:27");

    TimeCode tc6 = TimeCode(2, 71, 234719572143);
    assert(tc6.GetTimeCodeAsSeconds() == 234719583603);

    TimeCode tc7 = TimeCode(0, 59, 59);
    assert(tc7.ToString() == "0:59:59");

    TimeCode tc8 = TimeCode();
    assert(tc8.ToString() == "0:0:0");

    TimeCode tc9 = TimeCode(10);
    assert(tc9.ToString() == "10:0:0");

    cout << "PASSED!" << endl << endl;
}


void TestGetComponents(){
    cout << "Testing GetComponents" << endl;

    unsigned int h;
    unsigned int m;
    unsigned int s;

    // Regular values
    TimeCode tc = TimeCode(5, 2, 18);
    tc.GetComponents(h, m, s);
    assert(h == 5 && m == 2 && s == 18);

    // More tests go here!
    TimeCode tc2;
    tc2.GetComponents(h, m, s);
    assert(h == 0 && m == 0 && s == 0);

    TimeCode tc3 = TimeCode(3, 71, 3801);
    tc3.GetComponents(h, m, s);
    assert(h == 5 && m == 14 && s == 21);

    TimeCode tc4 = TimeCode(500, 30, 45);
    tc4.GetComponents(h, m, s);
    assert(h == 500 && m == 30 && s == 45);

    TimeCode tc5 = TimeCode(0, 59, 59);
    tc5.GetComponents(h, m, s);
    assert(h == 0 && m == 59 && s == 59);

    cout << "PASSED!" << endl << endl;
}


void TestSubtract(){
    cout << "Testing Subtract" << endl;
    TimeCode tc1 = TimeCode(1, 0, 0);
    TimeCode tc2 = TimeCode(0, 50, 0);
    TimeCode tc3 = tc1 - tc2;
    assert(tc3.ToString() == "0:10:0");

    TimeCode tc4 = TimeCode(1, 15, 45);
    try{
        TimeCode tc5 = tc1 - tc4;
        cout << "tc5: " << tc5.ToString() << endl;
        assert(false);
    }
    catch(const invalid_argument& e){
        // just leave this empty
        // and keep doing more tests
    }

    // more tests
    TimeCode tc6 = TimeCode(3, 3, 3);
    TimeCode tc7 = TimeCode(3, 3, 3);
    TimeCode tc8 = tc6 - tc7;
    assert(tc8.ToString() == "0:0:0");

    TimeCode tc9 = TimeCode(4, 4, 4);
    TimeCode tc10 = TimeCode(0, 0, 0);
    TimeCode tc11 = tc9 - tc10;
    assert(tc11.ToString() == "4:4:4");

    TimeCode tc12 = TimeCode(9, 8, 7);
    TimeCode tc13 = tc12 - tc12;
    assert(tc13.ToString() == "0:0:0");

    TimeCode tc14 = TimeCode(1, 0, 0);
    TimeCode tc15 = TimeCode(0, 0, 1);
    TimeCode tc16 = tc14 - tc15;
    assert(tc16.ToString() == "0:59:59");

    TimeCode tc17 = TimeCode(0, 0, 0);
    TimeCode tc18 = TimeCode(0, 0, 1);
    try {
        TimeCode tc19 = tc17 - tc18;
        cout << "tc19: " << tc19.ToString() << endl;
        assert(false);
    }
    catch (const invalid_argument& e) {
    
    }

    cout << "PASSED!" << endl << endl;
}


void TestSetMinutes()
{
    cout << "Testing SetMinutes" << endl;

    TimeCode tc = TimeCode(8, 5, 9);
    tc.SetMinutes(15); // test valid change
    assert(tc.ToString() == "8:15:9");

    try
    {
        tc.SetMinutes(80); // test invalid change
        assert(false);
        cout << "tc: " << tc.ToString() << endl;
    }
    catch (const invalid_argument &e)
    {

    }

    assert(tc.ToString() == "8:15:9");

    cout << "PASSED!" << endl << endl;
}

// Many More Tests...
void TestCopyConstructor(){
    cout << "Testing Copy Constructor" << endl;

    TimeCode tc1 = TimeCode(2, 30, 15);
    TimeCode tc2 = TimeCode(tc1);
    assert(tc2.ToString() == "2:30:15");
    assert(tc2 == tc1);

    tc2.SetHours(99);
    assert(tc2.ToString() == "99:30:15");
    assert(tc1.ToString() == "2:30:15");

    TimeCode tc3 = TimeCode(0, 0, 0);
    TimeCode tc4 = TimeCode(tc3);
    assert(tc4.ToString() == "0:0:0");

    cout << "PASSED!" << endl << endl;
}

void TestGetters(){
    cout << "Testing GetHours/GetMinutes/GetSeconds/GetTimeCodeAsSeconds" << endl;

    TimeCode tc = TimeCode(7, 22, 33);
    assert(tc.GetHours() == 7);
    assert(tc.GetMinutes() == 22);
    assert(tc.GetSeconds() == 33);
    assert(tc.GetTimeCodeAsSeconds() == 26553);

    TimeCode tc2 = TimeCode(0, 61, 0);
    assert(tc2.GetHours() == 1);
    assert(tc2.GetMinutes() == 1);
    assert(tc2.GetSeconds() == 0);

    TimeCode tc3;
    assert(tc3.GetHours() == 0);
    assert(tc3.GetMinutes() == 0);
    assert(tc3.GetSeconds() == 0);
    assert(tc3.GetTimeCodeAsSeconds() == 0);

    TimeCode tc4 = TimeCode(1000, 0, 0);
    assert(tc4.GetHours() == 1000);
    assert(tc4.GetMinutes() == 0);
    assert(tc4.GetSeconds() == 0);

    cout << "PASSED!" << endl << endl;
}

void TestSetHours(){
    cout << "Testing SetHours" << endl;

    TimeCode tc = TimeCode(3, 10, 20);
    tc.SetHours(99);
    assert(tc.ToString() == "99:10:20");

    tc.SetHours(0);
    assert(tc.ToString() == "0:10:20");

    tc.SetHours(999999);
    assert(tc.ToString() == "999999:10:20");

    TimeCode tc2;
    tc2.SetHours(5);
    assert(tc2.ToString() == "5:0:0");

    cout << "PASSED!" << endl << endl;
}

void TestSetSeconds(){
    cout << "Testing SetSeconds" << endl;

    TimeCode tc = TimeCode(1, 2, 3);
    tc.SetSeconds(45);
    assert(tc.ToString() == "1:2:45");

    tc.SetSeconds(59);
    assert(tc.ToString() == "1:2:59");

    tc.SetSeconds(0);
    assert(tc.ToString() == "1:2:0");

    try {
        tc.SetSeconds(60);
        assert(false);
        cout << "tc: " << tc.ToString() << endl;
    }
    catch (const invalid_argument& e) {
    }
    assert(tc.ToString() == "1:2:0");

    try {
        tc.SetSeconds(9999);
        assert(false);
        cout << "tc: " << tc.ToString() << endl;
    }
    catch (const invalid_argument& e) {
    }
    assert(tc.ToString() == "1:2:0");

    cout << "PASSED!" << endl << endl;
}

void TestReset(){
    cout << "Testing reset" << endl;

    TimeCode tc = TimeCode(12, 34, 56);
    tc.reset();
    assert(tc.ToString() == "0:0:0");
    assert(tc.GetTimeCodeAsSeconds() == 0);

    TimeCode tc2;
    tc2.reset();
    assert(tc2.ToString() == "0:0:0");

    TimeCode tc3 = TimeCode(999, 59, 59);
    tc3.reset();
    assert(tc3.ToString() == "0:0:0");

    cout << "PASSED!" << endl << endl;
}

void TestToString(){
    cout << "Testing ToString" << endl;

    assert(TimeCode(0, 0, 0).ToString() == "0:0:0");

    assert(TimeCode(1, 2, 3).ToString() == "1:2:3");

    assert(TimeCode(100, 5, 7).ToString() == "100:5:7");

    assert(TimeCode(4, 15, 32).ToString() == "4:15:32");

    assert(TimeCode(0, 59, 59).ToString() == "0:59:59");

    cout << "PASSED!" << endl << endl;
}

void TestAdd(){
    cout << "Testing Add" << endl;

    TimeCode tc1 = TimeCode(1, 15, 22);
    TimeCode tc2 = TimeCode(2, 9, 5);
    TimeCode tc3 = tc1 + tc2;
    assert(tc3.ToString() == "3:24:27");

    TimeCode tc4 = TimeCode(1, 15, 55);
    TimeCode tc5 = TimeCode(0, 1, 25);
    TimeCode tc6 = tc4 + tc5;
    assert(tc6.ToString() == "1:17:20");

    TimeCode tc7 = TimeCode(5, 5, 5);
    TimeCode tc8 = TimeCode(0, 0, 0);
    TimeCode tc9 = tc7 + tc8;
    assert(tc9.ToString() == "5:5:5");

    TimeCode tc10 = TimeCode(0, 0, 0) + TimeCode(0, 0, 0);
    assert(tc10.ToString() == "0:0:0");

    TimeCode tc11 = TimeCode(1000, 0, 0);
    TimeCode tc12 = TimeCode(2000, 0, 0);
    TimeCode tc13 = tc11 + tc12;
    assert(tc13.ToString() == "3000:0:0");

    cout << "PASSED!" << endl << endl;
}

void TestMultiply(){
    cout << "Testing Multiply" << endl;

    TimeCode tc1 = TimeCode(1, 0, 0);
    TimeCode tc2 = tc1 * 0.5;
    assert(tc2.ToString() == "0:30:0");

    TimeCode tc3 = tc1 * 0.0;
    assert(tc3.ToString() == "0:0:0");

    TimeCode tc4 = tc1 * 1.0;
    assert(tc4.ToString() == "1:0:0");

    TimeCode tc5 = TimeCode(0, 30, 0);
    TimeCode tc6 = tc5 * 3.0;
    assert(tc6.ToString() == "1:30:0");

    TimeCode tc7 = TimeCode(0, 0, 101);
    TimeCode tc8 = tc7 * 0.5;
    assert(tc8.ToString() == "0:0:50");

    TimeCode tc9 = TimeCode(0, 0, 0);
    TimeCode tc10 = tc9 * 100.0;
    assert(tc10.ToString() == "0:0:0");

    try {
        TimeCode tc11 = tc1 * -1.0;
        cout << "tc11: " << tc11.ToString() << endl;
        assert(false);
    }
    catch (const invalid_argument& e) {

    }

    try {
        TimeCode tc12 = tc1 * -0.001;
        assert(false);
    }
    catch (const invalid_argument& e) {

    }

    cout << "PASSED!" << endl << endl;
}

void TestDivide(){
    cout << "Testing Divide" << endl;

    TimeCode tc1 = TimeCode(1, 0, 0);
    TimeCode tc2 = tc1 / 2.0;
    assert(tc2.ToString() == "0:30:0");

    TimeCode tc3 = tc1 / 1.0;
    assert(tc3.ToString() == "1:0:0");

    TimeCode tc4 = TimeCode(0, 0, 101);
    TimeCode tc5 = tc4 / 2.0;
    assert(tc5.ToString() == "0:0:50");

    TimeCode tc6 = TimeCode(10, 0, 0);
    TimeCode tc7 = tc6 / 10.0;
    assert(tc7.ToString() == "1:0:0");

    TimeCode tc8 = TimeCode(0, 0, 0);
    TimeCode tc9 = tc8 / 5.0;
    assert(tc9.ToString() == "0:0:0");

    try {
        TimeCode tc10 = tc1 / 0.0;
        cout << "tc10: " << tc10.ToString() << endl;
        assert(false);
    }
    catch (const invalid_argument& e) {

    }

    try {
        TimeCode tc11 = tc1 / -2.0;
        cout << "tc11: " << tc11.ToString() << endl;
        assert(false);
    }
    catch (const invalid_argument& e) {
  
    }

    cout << "PASSED!" << endl << endl;
}

void TestComparisonOperators(){
    cout << "Testing Comparison Operators" << endl;

    TimeCode tc1 = TimeCode(1, 0, 0);
    TimeCode tc2 = TimeCode(1, 0, 0);
    TimeCode tc3 = TimeCode(2, 0, 0);

    assert(tc1 == tc2);
    assert(!(tc1 == tc3));

    assert(tc1 != tc3);
    assert(!(tc1 != tc2));

    assert(tc1 < tc3);
    assert(!(tc3 < tc1));
    assert(!(tc1 < tc2));

    assert(tc1 <= tc2);
    assert(tc1 <= tc3);
    assert(!(tc3 <= tc1));

    assert(tc3 > tc1);
    assert(!(tc1 > tc3));
    assert(!(tc1 > tc2));

    assert(tc1 >= tc2);
    assert(tc3 >= tc1);
    assert(!(tc1 >= tc3));

    assert(tc1 == tc1);
    assert(tc1 <= tc1);
    assert(tc1 >= tc1);
    assert(!(tc1 < tc1));
    assert(!(tc1 > tc1));
    assert(!(tc1 != tc1));

    cout << "PASSED!" << endl << endl;
}


int main(){
    TestComponentsToSeconds();
    TestDefaultConstructor();
    TestComponentConstructor();
    TestGetComponents();

    // These functions were included in the code template but not in the main function 
    // I added them here to ensure they are called and tested
    TestSubtract(); 
    TestSetMinutes();

    // Many othere test functions...
    TestCopyConstructor();
    TestGetters();
    TestSetHours();
    TestSetSeconds();
    TestReset();
    TestToString();
    TestAdd();
    TestMultiply();
    TestDivide();
    TestComparisonOperators();

    cout << "PASSED ALL TESTS!!!" << endl;
    return 0;
}

// I used AI (ChatGPT) to double check my math for test case results after getting errors related to that.