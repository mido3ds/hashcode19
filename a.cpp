////////////includes/////////////////
#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <functional>
#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <chrono>
#include <cstdint>
using namespace std;
///////////shortname/////////////
using ll = long long;
using ull = unsigned long long;
using uint = unsigned int;
using vi = vector<int>;
using vd = vector<double>;
#define vec vector
#define dict unordered_map
#define uset unordered_set
#define endl '\n'
const int INF = 1 << 29;
///////////functions/////////////
inline bool equal(const double& a, const double& b) { return fabs(a - b) < 1e-9; }
inline int two(const int& n) { return 1 << n; }
inline int test(const int& n, const int& b) { return (n >> b) & 1; }
inline void set_bit(int& n, const int& b) { n |= two(b); }
inline void unset_bit(int& n, const int& b) { n &= ~two(b); }
inline int last_bit(const int& n) { return n & (-n); }
inline int ones(int n)
{
    int res = 0;
    while (n && ++res)
        n -= n & (-n);
    return res;
}
template <class T>
void chmax(T& a, const T& b) { a = max(a, b); }
template <class T>
void chmin(T& a, const T& b) { a = min(a, b); }
////////////operator overloading////////////
#ifndef ONLINE_JUDGE
    #define debug(x) cerr << "> " << #x << " = " << x << endl;
#else
    #define debug(x)
#endif

template <typename F, typename S>
ostream& operator<<(ostream& os, const pair<F, S>& p)
{
    return os << "(" << p.first << ", " << p.second << ")";
}

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    os << "[";
    typename vector<T>::const_iterator it;
    for (it = v.begin(); it != v.end(); it++) {
        if (it != v.begin())
            os << ", ";
        os << *it;
    }
    return os << "]";
}

template <typename T>
ostream& operator<<(ostream& os, const set<T>& v)
{
    os << "[";
    typename set<T>::const_iterator it;
    for (it = v.begin(); it != v.end(); it++) {
        if (it != v.begin())
            os << ", ";
        os << *it;
    }
    return os << "]";
}

template <typename T>
ostream& operator<<(ostream& os, const uset<T>& v)
{
    os << "[";
    typename uset<T>::const_iterator it;
    for (it = v.begin(); it != v.end(); it++) {
        if (it != v.begin())
            os << ", ";
        os << *it;
    }
    return os << "]";
}

template <typename F, typename S>
ostream& operator<<(ostream& os, const map<F, S>& v)
{
    os << "{";
    typename map<F, S>::const_iterator it;
    for (it = v.begin(); it != v.end(); it++) {
        if (it != v.begin())
            os << ", ";
        os << it->first << ": " << it->second;
    }
    return os << "}";
}

template <typename F, typename S>
ostream& operator<<(ostream& os, const unordered_map<F, S>& v)
{
    os << "{";
    typename unordered_map<F, S>::const_iterator it;
    for (it = v.begin(); it != v.end(); it++) {
        if (it != v.begin())
            os << ", ";
        os << it->first << ": " << it->second;
    }
    return os << "}";
}
////////////main////////////
uint64_t allScore = 0;
void solve(fstream in, fstream out);
int main() {
    for (char file = 'a'; file <= 'e'; file++) {
        cout << "::" << file << "::Start\n";

        auto start = std::chrono::high_resolution_clock::now();
        solve(
            fstream(string("in/") + file + string(".in"), ios::in), 
            fstream(string("out/") + file + string(".out"), ios::out)
        );
        auto finish = std::chrono::high_resolution_clock::now();

        cout << "::" << file << "::Elapsed time: " 
            << std::chrono::duration<double>(finish - start).count() << " s\n";
    }

    return 0;
}
/////////////////////////////////////////////////solve////////////////////////////////////////////////////////////

struct Photo {int id; bool visited; set<int> tags;};

void solve(fstream in, fstream out) {
    uint64_t n;
    in >> n;

    vector<Photo> vp, hp;
    map<string, int> tagsmap;

    for (int i = 0; i < n; i++) {
        char t; in >> t;
        int nt; in >> nt;
        Photo p{i, false, set<int>()};
        for (int j = 0; j < nt; j++) {
            string tt; in >> tt;
            if (tagsmap.find(tt) == tagsmap.end()) {tagsmap[tt] = tagsmap.count();} 
            p.tags.insert(tagsmap[tt]);
        }
        if (t == 'H') hp.push_back(p);
        else vp.push_back(p);
    }

    sort(hp.begin(), hp.end(), [](Photo& a, Photo& b) {return a.tags.size() > b.tags.size();});
    sort(vp.begin(), vp.end(), [](Photo& a, Photo& b) {return a.tags.size() > b.tags.size();});

    //////////////

    vector<vector<int>> ids;

    for (int j = 0; j < hp.size(); j++) {
        auto& p = hp[j];

        if (!p.visited) {
            p.visited = true;
            int32_t mini=INT32_MAX, imini=-1, maxi=-1, imaxi=-1;
            for (int i = 0; i < vp.size(); i++) {
                auto& p2 = vp[i];
                if (!p2.visited) {
                    vector<int> output(min(p.tags.size(), p2.tags.size()));
                    int size = set_intersection(p.tags.begin(), p.tags.end(), p2.tags.begin(), p2.tags.end(), output.begin()) - output.begin();
                    int t = min(size, (int)min(p.tags.size()-size, p2.tags.size()-size));
                    if (t==0) break;
                    if (size < mini) {
                        mini = size;
                        imini = i;
                    } else if (size > maxi) {
                        maxi = size;
                        imaxi = i;
                    }
                }
            }

            ids.push_back(vector<int>{p.id, -1});
            if (imaxi != -1 && imini != -1) {
                vp[imaxi].visited = true;
                vp[imini].visited = true;
                // cout << imaxi << ' ' << imini << endl;
                ids.push_back(vector<int>{vp[imaxi].id, vp[imini].id});
            } else if (j < hp.size() - 1) {
                hp[j+1].visited = true;
                    // cout << imaxi << ' ' << imini << endl;

                ids.push_back(vector<int>{hp[j+1].id, -1});
            }
            // else {
            //     int32_t maxi=-1, imaxi=-1;
            //     for (int jj = j+1; jj < hp.size(); jj++) {
            //         auto& p3 = hp[jj];

            //         if (!p3.visited) {
            //             vector<int> output(min(p.tags.size(), p3.tags.size()));
            //             int size = set_intersection(p.tags.begin(), p.tags.end(), p3.tags.begin(), p3.tags.end(), output.begin()) - output.begin();
            //             int t = min(size, (int)min(p.tags.size()-size, p3.tags.size()-size));
            //             if (t > maxi) {
            //                 maxi = t;
            //                 imaxi = jj;
            //             }
            //         }
            //     }
            //     if (imaxi != -1) {
            //         hp[imaxi].visited = true;
            //         ids.push_back({hp[imaxi].id});
            //         cout << hp[imaxi].id << endl;
            //     }
            // }
        }
    }

    for (int i = 0; i < vp.size(); i++) {
        int32_t maxi=-1,imaxi=-1, mini=INT32_MAX,imini=-1;
        auto& p = vp[i];

        if (!p.visited) {
            for (int j = i+1; j<vp.size();j++) {
                auto& p2 = vp[j];

                if (!p2.visited) {
                    vector<int> output(min(p.tags.size(), p2.tags.size()));
                    int size = set_intersection(p.tags.begin(), p.tags.end(), p2.tags.begin(), p2.tags.end(), output.begin()) - output.begin();
                    if (size == 0) break;
                    if (size > maxi) {
                        maxi = size;
                        imaxi = j;
                    }
                }
            }
            for (int j = i+1; j<vp.size();j++) {
                auto& p2 = vp[j];

                if (!p2.visited) {
                    vector<int> output(min(p.tags.size(), p2.tags.size()));
                    int size = set_intersection(p.tags.begin(), p.tags.end(), p2.tags.begin(), p2.tags.end(), output.begin()) - output.begin();
                    if (p2.tags.size()-size == 0) break;
                    if (size < mini) {
                        mini = size;
                        imini = j;
                    }
                }
            }

            if (mini != -1) {
                ids.push_back(vector<int>{p.id, vp[imini].id});
                vp[imini].visited = true;
            } else if (i < vp.size() - 1) {
                ids.push_back(vector<int>{p.id, vp[i+1].id});
                vp[i+1].visited = true;
            }
            mini = imini = -1;
            for (int j = i+1; j<vp.size();j++) {
                auto& p2 = vp[j];

                if (!p2.visited) {
                    vector<int> output(min(p.tags.size(), p2.tags.size()));
                    int size = set_intersection(p.tags.begin(), p.tags.end(), p2.tags.begin(), p2.tags.end(), output.begin()) - output.begin();
                    if (p2.tags.size()-size == 0) break;
                    if (size < mini) {
                        mini = size;
                        imini = j;
                    }
                }
            }
            if (maxi != -1 && mini != -1) {
                ids.push_back(vector<int>{vp[imini].id, vp[imaxi].id});
                vp[imaxi].visited = true;
                vp[imini].visited = true;
            }
        }
    }

    out << ids.size() << endl;
    for (auto& id : ids) {
        // if (id.size() == 0) out << id[0] << endl;
        // else out << id[0] << ' ' << id[1] << endl;
        out << id[0] << ' ';
        if (id[1] != -1) out << id[1];
        out << endl;
    }
}
