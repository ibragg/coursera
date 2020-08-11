
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <sstream>

using namespace std;

class Date {
public:
    Date(int new_year, int new_month, int new_day) {
        if (new_month < 1 || new_month > 12) {
            throw out_of_range("Month value is invalid: " + to_string(new_month));
        } else if (new_day < 1 || new_day > 31) {
            throw out_of_range("Day value is invalid: " + to_string(new_day));
        }
        year = new_year;
        month = new_month;
        day = new_day;

    }


    int GetYear() const {
        return year;
    };

    int GetMonth() const {
        return month;
    };

    int GetDay() const {
        return day;
    };
private:
    int year;
    int month;
    int day;
};

ostream &operator<<(ostream &is, const Date &date) {
    is << setfill('0') << setw(4) << to_string(date.GetYear());
    is << "-";
    is << setfill('0') << setw(2) << to_string(date.GetMonth());
    is << "-";
    is << setfill('0') << setw(2) << to_string(date.GetDay());
    return is;
}


bool operator<(const Date &lhs, const Date &rhs) {
    if (lhs.GetYear() != rhs.GetYear()) {
        return lhs.GetYear() < rhs.GetYear();
    } else if (lhs.GetMonth() != rhs.GetMonth()) {
        return lhs.GetMonth() < rhs.GetMonth();
    } else {
        return lhs.GetDay() < rhs.GetDay();
    }
};

Date ParseDate(const string &date) {
    istringstream stream(date);
    bool is_true = true;
    int year;
    is_true = is_true && (stream >> year);
    is_true = is_true && (stream.peek() == '-');
    stream.ignore(1);

    int month;
    is_true = is_true && (stream >> month);
    is_true = is_true && (stream.peek() == '-');
    stream.ignore(1);

    int day;
    is_true = is_true && (stream >> day);
    is_true = is_true && stream.eof();

    if (!is_true) {
        throw logic_error("Wrong date format: " + date);
    }
    return Date(year, month, day);

}

class Database {
public:
    void AddEvent(const Date &date, const string &event) {
        if (!event.empty()) {
            db[date].insert(event);
        }
    };

    bool DeleteEvent(const Date &date, const string &event) {
        if (db.count(date) > 0 && db[date].count(event) > 0) {
            db[date].erase(event);
            return true;
        }
        return false;
    };

    int DeleteDate(const Date &date) {
        int n = 0;
        if (db.count(date) > 0) {
            n = db.at(date).size();
            db.erase(date);
        }
        return n;
    };

    set<string> Find(const Date &date) const {
        set<string> events;
        if (db.count(date) > 0) {
            events = db.at(date);
        }
        return events;
    };

    void Print() const {
        for (const auto &x: db) {
            for (const auto &y: x.second) {
                cout << x.first << " " << y << endl;
            }
        }
    };

private:
    map<Date, set<string>> db;
};

int main() {
    Database db;
    try {
        string command;
        while (getline(cin, command)) {
            // Считайте команды с потока ввода и обработайте каждую
            if (command == "") continue;
            stringstream fk(command);
            string operation;
            fk >> operation;
            if (operation == "Add") {
                string date_s, event;
                fk >> date_s >> event;
                const Date date = ParseDate(date_s);
                if (event != "" || event != " ") {
                    db.AddEvent(date, event);
                }
            } else if (operation == "Find") {
                string date_s, event;
                fk >> date_s >> event;
                const Date date = ParseDate(date_s);
                set<string> events = db.Find(date);
                for (const auto &u: events) {
                    cout << u << endl;
                }
            } else if (operation == "Del") {
                string date_s, event;
                fk >> date_s;
                if (!fk.eof()) {
                    fk >> event;
                }
                const Date date = ParseDate(date_s);
                if (event.empty()) {
                    int num_of_events_to_del = db.DeleteDate(date);
                    cout << "Deleted " << num_of_events_to_del << " events" << endl;
                } else {
                    if (db.DeleteEvent(date, event)) {
                        cout << "Deleted successfully" << endl;
                    } else {
                        cout << "Event not found" << endl;
                    }
                }
            } else if (operation == "Print") {
                db.Print();
            } else {
                cout << "Unknown command: " << operation << endl;
            }
        }
    }
    catch (exception &exp) {
        cout << exp.what() << endl;
        return 0;
    }
    return 0;
}
