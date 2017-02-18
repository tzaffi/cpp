//
// Created by zeph on 2/18/17.
//

/**
 *
Shows how to use regex.

EG. INPUT:

2
<p><a href="http://www.quackit.com/html/tutorial/html_links.cfm">Example Link</a></p>
<div class="more-info"><a href="http://www.quackit.com/html/examples/html_links_examples.cfm">More Link Examples...</a></div>

EG. OUTPUT:
a;div;p
 */

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

#include <sstream>
#include <regex>
#include <set>

using namespace std;


int main() {
    unsigned N;
    cin >> N;
    string line;
    getline(cin, line); //throw away

    regex tagExp("\\s*(\\w+).*");  //tag("(\\+|-)?[[:digit:]]+");
    set<string> tags;
    for(unsigned i=1; i<=N; ++i)
    {
        getline(cin, line);
        stringstream ss(line);
        string tag;
        while (getline(ss, tag, '<'))
        {
//            cout << tag << '\n'; //":-->";
            smatch m;
            if (regex_search(tag, m, tagExp))
            {
//                cout << "Match\n";
//                std::cout << "match[1] = " << m[1] << '\n';
                tags.insert(m[1]);
            }
        }
    }
    size_t i = 0;
    for(auto x: tags){
        ++i;
        cout << x << (i == tags.size() ? "" : ";");
    }
    return 0;
}
