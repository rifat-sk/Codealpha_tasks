#include <bits/stdc++.h>
#define ll long long
using namespace std;
double total_grade_point_all = 0, total_credit_all = 0;
map<string, double> grade_to_point = {{"A+", 4.00},
                                      {"A", 3.75},
                                      {"A-", 3.50},
                                      {"B+", 3.25},
                                      {"B", 3.00},
                                      {"B-", 2.75},
                                      {"C+", 2.50},
                                      {"C", 2.25},
                                      {"D", 2.00},
                                      {"F", 0.00}};

struct courses
{
  string name;
  string grade;
  double credit;
};

int main()
{
  ll semester_number;
  cout << "\033[32mWelcome to CGPA Calculator\n\033[0m";
  cout << "\033[33mInstructions:\n\033[0m";
    cout << "\033[33m1. Enter the number of semesters completed.\n\033[0m";
    cout << "\033[33m2. For each course, provide:\n\033[0m";
    cout << "\033[33m   - Course name\n\033[0m";
    cout << "\033[33m   - Grade (e.g., A+, A, B, C, D, F)\n\033[0m";
    cout << "\033[33m   - Credit hours\n\033[0m";
    cout << "\033[33m3. The program will calculate GPA for each semester and your overall CGPA.\n\n\033[0m";
  cout << "Enter the number of semesters passed: ";
  cin >> semester_number;                          // semester input
  vector<vector<courses>> course(semester_number); // store data
  vector<double> gpa(semester_number);             // store all semester gpa
  for (int semester_index = 0; semester_index < semester_number; semester_index++)
  {
    cout << "Semester " << semester_index + 1 << ":" << endl;
    ll course_number;
    double total_grade_point = 0, total_credit = 0;
    cout << "Write the number of courses: ";
    cin >> course_number; // input course number
    cin.ignore();
    course[semester_index].resize(course_number);
    for (int course_index = 0; course_index < course_number; course_index++)
    {
      cout << "Course " << course_index + 1 << ":\n";
      cout << "Enter course name: ";
      getline(cin, course[semester_index][course_index].name); // input course name
      while (true)
      {
        cout << "Enter grade: ";
        cin >> course[semester_index][course_index].grade;
        if (!grade_to_point.count(course[semester_index][course_index].grade)) // valid grade check
        {
          cout << "\033[31mYou entered an invalid grade! Please try again.\033[0m" << endl;
        }
        else
          break;
      }
      cout << "Enter course credit: ";
      cin >> course[semester_index][course_index].credit; // credit input
      cin.ignore();
      total_credit += course[semester_index][course_index].credit;
      total_grade_point += (course[semester_index][course_index].credit * grade_to_point[course[semester_index][course_index].grade]); // calculate grade point and credit
    }
    if (total_credit == 0)
      gpa[semester_index] = 0;
    else
      gpa[semester_index] = total_grade_point / total_credit; // store it into the vector
    total_grade_point_all += total_grade_point;
    total_credit_all += total_credit;
  }
  cout << "\033[33m>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<\033[0m"<<endl;
  
  for (int i = 0; i < semester_number; i++) {
    cout << "\n\033[36mSemester " << i + 1 << " Results:\033[0m\n";

    cout << left << setw(25) << "Course Name"
         << setw(10) << "Grade"
         << setw(10) << "Credit"                       //make table
         << setw(15) << "Grade Point" << endl;

    cout << "\033[33m---------------------------------------------------------\033[0m\n";

    for (auto &num : course[i]) {
        cout << left << setw(25) << num.name
             << setw(10) << num.grade
             << setw(10) << num.credit                 //make table
             << setw(15) << grade_to_point[num.grade] << endl;
    }

    cout << "\033[33m---------------------------------------------------------\033[0m\n";
    cout << "Semester GPA: " << fixed << setprecision(2) << gpa[i] << "\n";
    cout << "\033[33m>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<\033[0m\n";
}
  
  cout << "\n\033[36mSummary of Semester GPAs:\033[0m\n";
    for (int i = 0; i < semester_number; i++) {
        cout << "Semester " << i + 1 << " GPA: " << fixed << setprecision(2) << gpa[i] << endl;
    }
    cout << "\033[33m------------------------------------------\033[0m\n";

    if (total_credit_all == 0)
        cout << "Your Overall CGPA: " << fixed << setprecision(2) << 0 << endl;
    else
        cout << "Your Overall CGPA: " << fixed << setprecision(2)
             << total_grade_point_all / total_credit_all << endl;

    cout << "\033[33m>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<\033[0m\n";
    cout << "\033[32mThank you for using the CGPA Calculator! Best of luck in your studies.\033[0m\n";
}
