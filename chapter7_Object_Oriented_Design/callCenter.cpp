#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

struct customerCall {
    string caller_name;
    string caller_number;
    int require_level;

    bool resolved;
    bool isSpam;
    bool escalated;

    string respondent_name;

    customerCall(const string& na, const string& nu, const int& l)
        : caller_name(na),
          caller_number(nu),
          require_level(l),
          resolved(false),
          isSpam(false),
          escalated(false) {}
};

struct callCenterEmployee {
    enum response { resolveIt, spamIt, escalateIt };

    string name;

    int myLevel;

    bool busy;

    callCenterEmployee(const string& n, const int& pl)
        : name(n), myLevel(pl), busy(false) {}

    customerCall processCall(customerCall& call) {
        if (not busy) {
            busy = true;
            call.escalated = false;

            string msg = "Employee Name: " + name +
                         " lv: " + to_string(myLevel) +
                         " is answering the call...";

            call.respondent_name = name;

            report(msg);

            if (call.require_level < 0 or
                call.require_level > 2) {  // this is spam
                report("It's a Spam! hanging up...");
                hangUpPhoneCall(spamIt, call);
                return call;
            }

            // if not a spam
            if (canHandleTheCall(call)) {
                report("I can handle it. resolving...");
                hangUpPhoneCall(resolveIt, call);
                report("resolved!");
                return call;
            } else {  // requires higher level respondent
                report("I CAN'T handle it. escalating it...");
                hangUpPhoneCall(escalateIt, call);
                return call;
            }
        } else {  // try to let a busy respondent take another phone call
            string error_msg = "Employee name: " + name +
                               "\nPriority level: " + to_string(myLevel) +
                               "\nis busy.";
            throw runtime_error(error_msg.c_str());
        }
    }

    void hangUpPhoneCall(response res, customerCall& call) {
        if (res == resolveIt) {
            call.resolved = true;
            call.escalated = false;
        } else if (res == spamIt) {
            call.isSpam = true;
        } else if (res == escalateIt) {
            call.escalated = true;
        } else {
            throw runtime_error("undefined response");
        }

        report("Call is over");

        busy = false;
    }

    bool canHandleTheCall(const customerCall& call) {
        return call.require_level <= myLevel;
    }

    void report(const string& msg) { cout << msg << endl; }
};

struct respondent : callCenterEmployee {
    respondent(const string& name) : callCenterEmployee(name, 0) {}
};

struct manager : callCenterEmployee {
    manager(const string& name) : callCenterEmployee(name, 1) {}
};

struct director : callCenterEmployee {
    director(const string& name) : callCenterEmployee(name, 2) {}
};

struct CallCenter {
    // int nRespondent;
    // int nManager;
    // int nDirector;

    const int nLevel = 3;

    vector<customerCall> resolvedCalls;
    vector<customerCall> spamCalls;

    vector<queue<callCenterEmployee*>> respondQueue;

    CallCenter(const vector<string>& respondent_roster,
               const vector<string>& manager_roster,
               const vector<string>& director_roster)
        : respondQueue(vector<queue<callCenterEmployee*>>(nLevel)) {
        for (auto name : respondent_roster) {
            respondQueue[0].push(new respondent(name));
        }

        for (auto name : manager_roster) {
            respondQueue[1].push(new manager(name));
        }

        for (auto name : director_roster) {
            respondQueue[2].push(new director(name));
        }

        // more levels can be added by increasing
        // the dimensions of respondQueue
    }

    void dispatchCall(customerCall& call);
};

void CallCenter::dispatchCall(customerCall& call) {
    cout << "Incoming call from:\ncaller name: " << call.caller_name
         << "\ncaller number: " << call.caller_number
         << "\nlv required: " << call.require_level << endl;

    // first let the respondent take the call
    int lv = 0;

    callCenterEmployee* respondentInCharge = respondQueue[lv].front();
    respondQueue[lv].pop();
    call = respondentInCharge->processCall(call);
    respondQueue[lv].push(respondentInCharge);

    // let higher level ppl answer it
    while (call.escalated) {
        lv++;
        respondentInCharge = respondQueue[lv].front();
        respondQueue[lv].pop();
        call = respondentInCharge->processCall(call);
        respondQueue[lv].push(respondentInCharge);
    }

    if (call.isSpam) {
        spamCalls.push_back(call);
    } else if (call.resolved) {
        resolvedCalls.push_back(call);
    } else {
        throw runtime_error("respondent missed a call");
    }
}

int main() try {
    vector<string> respondent_roster{"Anne", "Bill",  "Constance", "Joe",
                                     "Rose", "Cindy", "Mindy",     "Reachel",
                                     "Tom",  "Bob",   "Jose",      "Jason",
                                     "Jim",  "Andy",  "Ben"};

    vector<string> manager_roster{"Smith", "Sun", "Zuck", "Yamamoto"};

    vector<string> director_roster{"Yushi"};

    vector<customerCall> calls{
        customerCall("aa", "1296y348", 0),
        customerCall("afas", "123fr239348", 1),
        customerCall("aasf", "12fda139348", 2),
        customerCall("awq", "12239348", 3),
        customerCall("adasf", "12af19348", 2),
        customerCall("aff", "1293f48", 1),
        customerCall("aadsf", "12qwe9348", 2),
        customerCall("aoi", "129f348", 0),
        customerCall("apqow", "1f29348", 0),
        customerCall("afhk", "12934as8", 3),
        customerCall("aaso", "5293f548", 1),
        customerCall("afsf", "12q1249348", 0),
        customerCall("aopo", "1291f348", 2),
        customerCall("aiww", "1f2qw9348", 0),
        customerCall("akok", "12as4as8", 0),
    };

    CallCenter cc(respondent_roster, manager_roster, director_roster);

    for (auto call : calls) {
        cc.dispatchCall(call);
    }

    cout << "<<<<Resolved Calls<<<<" << endl;
    for (auto call : cc.resolvedCalls) {
        cout << call.caller_name << endl;
        cout << call.caller_number << endl;
        cout << call.require_level << endl;
        cout << "respondent: " << call.respondent_name << endl;
    }

    cout << "<<<<Spam Calls<<<<" << endl;
    for (auto call : cc.spamCalls) {
        cout << call.caller_name << endl;
        cout << call.caller_number << endl;
        cout << call.require_level << endl;
        cout << "respondent: " << call.respondent_name << endl;
    }

    return 0;
} catch (runtime_error& re) {
    cout << re.what() << endl;
}